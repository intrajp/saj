/*
 *  common.c - common functions 
 *  This file contains the contents of saj.
 *
 *  Copyright (C) 2019 Shintaro Fujiwara
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 *  02110-1301 USA
 */

#include <errno.h>
#include <ctype.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "common.h"
#include "../libsaj-sosreport-analyzer/line_data.h"
#include "setter_getter.h"
#include "../common/global.c"
#include "check.c"

void initialize_block_device_name(void)
{
    int x = 0;

    /* for sar_analyzer_obj */
    strcpy(sar_analyzer_obj->device_names[0], "first");
    for (x = 1; x <= MAX_BLOCK_DEVICE_NUMBERS; x++)
        strcpy(sar_analyzer_obj->device_names[x], "ignore");

    /* for sar_analyzer_all_obj */
    strcpy(sar_analyzer_all_obj->device_names[0], "first");
    for (x = 1; x <= MAX_BLOCK_DEVICE_NUMBERS; x++)
        strcpy(sar_analyzer_all_obj->device_names[x], "ignore");
}

void initialize_network_device_name(void)
{
    int x = 0;

    /* for sar_analyzer_obj */
    strcpy(sar_analyzer_obj->network_device_names[0], "first");
    for (x = 1; x <= MAX_NETWORK_DEVICE_NUMBERS; x++)
        strcpy(sar_analyzer_obj->network_device_names[x], "ignore");

    /* for sar_analyzer_all_obj */
    strcpy(sar_analyzer_all_obj->network_device_names[0], "first");
    for (x = 1; x <= MAX_NETWORK_DEVICE_NUMBERS; x++)
        strcpy(sar_analyzer_all_obj->network_device_names[x], "ignore");
}

int search_network_device_name(const char *network_device_name)
{
    int x = 0;
    for (x = 1; x <= get_network_device_numbers(); x++) {
        if (strcmp((char *)get_network_device_names(x), network_device_name) == 0)
            return x;
    }
    return 0;
}

void set_dir_name_analyze(const char *dname)
{
    sar_analyzer_obj->dir_name_analyze = dname;
}

void set_hostname(char *hostname)
{
    strcpy(sar_analyzer_all_obj->hostname, hostname);
}

void set_files_n(int var)
{
    sar_analyzer_obj->files_n = var;
}

void read_sa_dir(const char *dname, int SAR_OPTION, int REPORT,
    int MESSAGE_ONLY, const char *time_span)
{
    DIR *dir;
    struct dirent *dp;
    dir = opendir(dname); 
    char *str, *str_tmp;
    struct stat buf;
    char fullpath[MAX_FILE_NAME_LENGTH];
    int ret, mtime, int_tmp;
    int i = 0, ii = 0 , j = 0, files_n = 0;

    /* limit of sar files to be analyzed */
    char *str_arr[MAX_ANALYZE_FILES];
    int int_arr[MAX_ANALYZE_FILES];

    int str_arr_valid_size = 0;

    /* read from directory and set in an array */
    for (dp = readdir(dir); dp != NULL; dp = readdir(dir)) {
        if (dp->d_type != DT_REG)
            continue;
        str = dp->d_name;
        snprintf(fullpath, MAX_FILE_NAME_LENGTH + 2, "%s/%s", dname, str);
        ret = stat(fullpath, &buf);
        if (ret < 0) {
            free_sar_analyzer_obj();
            free_sosreport_analyzer_obj(0);
            exit(EXIT_FAILURE);
        }
        /*
         *  find files with name sar
         *  skip reading "sar_all" file 
         */
        if (strstr(str, "sar_all") != 0)
            continue;
        if (strstr(str, "sar") != 0) {
            /* exclude files with name tar or bz */
            if (strstr(str, "tar") == 0 && strstr(str, "bz") == 0) {
                /* so, only sar[0-9][0-9] files will remain */
                /* we also check mtime to sort files as time */
                mtime = (int)buf.st_mtime;
                int_arr[str_arr_valid_size] = mtime;
                str_arr[str_arr_valid_size] = str;
                str_arr_valid_size++;
                if (str_arr_valid_size == MAX_ANALYZE_FILES -1)
                    break;
            }
        }
    }

    /* Check the number of files in the directory and if 0, exit */
    if (str_arr_valid_size == 0) {
        fprintf(stderr, "-There are no sar files in this directory (%s):%s\n", dname, strerror(errno));
        fprintf(stderr, "-If you are not in sar-analyzer only mode, check file in saj-results dir.\n");
        /* freeing object and setting it to NULL */
        free_sar_analyzer_obj();
        free_sosreport_analyzer_obj(0);
        exit(EXIT_FAILURE);
    }

    /* bubble sort the array */

    for (j= 0; j < str_arr_valid_size; j++) {
        /* This makes largest item to the end of an array. */
        for (i = 0; i < str_arr_valid_size - (1 + j); i++) {
            ii = i + 1;
            if (int_arr[i] > int_arr[ii]) {
                str_tmp = str_arr[i]; 
                int_tmp = int_arr[i]; 
                str_arr[i] = str_arr[ii]; 
                int_arr[i] = int_arr[ii]; 
                str_arr[ii] = str_tmp; 
                int_arr[ii] = int_tmp; 
            }
        }
    }

    /* end bubble sort */

    /* sets total file numbers to the struct */
    files_n = str_arr_valid_size;
    set_files_n(files_n);

    /* now pass an array to the function, this will be done by passing first pointer of an array */
    read_write_file(dir, dname, str_arr, files_n, SAR_OPTION, REPORT, MESSAGE_ONLY, time_span);

    /* freeing memory */
    for (i = 0; i < MAX_ANALYZE_FILES; i++) {
        str_arr[i] = NULL;
        int_arr[i] = 0;
    }
}

void read_write_file(DIR *dir, const char *dname, char *sar_arr[], int files_n,
    int SAR_OPTION, int REPORT, int MESSAGE_ONLY, const char *time_span)
{
    size_t dname_len = 0;
    dname_len = strlen(dname);
    int i = 0;

    if (dname_len <= 0) {
        fprintf(stderr, "no dir name supplied (%s): %ld %s\n", dname, dname_len, strerror(errno));
        /* freeing object and setting it to NULL */
        for (i = 0; i < files_n; i++)
            sar_arr[i]=NULL;
        free_sar_analyzer_obj();
        free_sosreport_analyzer_obj(0);
        exit(EXIT_FAILURE);
    }
    if (dname_len > MAX_DIR_NAME_LENGTH) {
        fprintf(stderr, "directory name too long (%s): %ld %s\n",dname,dname_len,strerror(errno));
        /* freeing object and setting it to NULL */
        for (i = 0; i < files_n; i++)
            sar_arr[i]=NULL;
        free_sar_analyzer_obj();
        free_sosreport_analyzer_obj(0);
        exit(EXIT_FAILURE);
    }
    /* stripping last slash if any */
    /* new array: MAX_ANALYZE_FILES tupples with MAX_DIR_NAME_LENGTH characters */

    char sar_full_path_arr[MAX_ANALYZE_FILES][MAX_DIR_NAME_LENGTH] = {{0}};
    
    int ii = 0;
    char full_path[MAX_FULL_PATH_LENGTH];
    memset(full_path, '\0', sizeof(full_path)); 
    for (i = 0; i < files_n; i++) {
        /* this is needed for initializing */
        for (ii = 0; ii < MAX_FULL_PATH_LENGTH; ii++)
            full_path[ii] = '\0';
        strncpy(full_path, dname, MAX_DIR_NAME_LENGTH - 1);
        strncat(full_path, "/", MAX_DIR_NAME_LENGTH - 1 );
        strncat(full_path, sar_arr[i], MAX_DIR_NAME_LENGTH - 1);
        strncpy(sar_full_path_arr[i], full_path, MAX_FULL_PATH_LENGTH);
        /* freeing memory */
        sar_arr[i]=NULL;
    }
    /* read sar files for sanity check */
    for (i = 0; i < files_n; i++) {
        char str_tmp[17] = "--------file no.";
        char str_num[50] = {'\0'};
        snprintf(str_num, MAX_INPUT, "%s%d", str_tmp, i + 1);
        /* let 'read_sar_check()' do the job */
        initialize_avg_checked_int();
        read_sar_check(i, sar_full_path_arr[i], SAR_OPTION);
    }

    if (SAR_OPTION == 'Z') {
        append_list(&header_obj, "");
        append_list(&header_obj, "sar file sanity check PASS");
    } else {
        append_list(&line_obj, "");
        append_list(&line_obj, "sar file sanity check PASS");
    }

    /* read one sar file and set cpu paragraph to CHECK_AS_PARAGRAPH */
    /* let 'read_cpu_each()' do the job */
    initialize_avg_checked_int();
    read_sar_cpu_as_paragraph(sar_full_path_arr[0]);

    FILE *fp_svg_w;

    /* open svg dummy file here just to set data to the each object */
    /* -------- svg file -------- */
    if ((fp_svg_w = fopen("dummy.svg", "a")) == NULL) {
        fprintf(stderr, "can't open file (%s): %s\n", "dummy.svg", strerror(errno));
        for (i = 0; i < files_n; i++)
            sar_arr[i]=NULL;
        free_sar_analyzer_obj();
        free_sosreport_analyzer_obj(0);
        exit(EXIT_FAILURE);
    }
    unlink("dummy.svg");

    pclose(fp_svg_w);

    /* read sar files */
    for (i = 0; i < files_n; i++) {
        char str_tmp[17] = "--------file no.";
        char str_num[50] = {'\0'};
        snprintf (str_num, MAX_INPUT, "%s%d", str_tmp, i + 1);
        if (SAR_OPTION == 'Z')
            append_list(&line_all_obj, str_num);
        else
            append_list(&line_obj, str_num);
        /* let 'read_sar()' do the job */
        read_sar(i, sar_full_path_arr[i], SAR_OPTION, REPORT, MESSAGE_ONLY, time_span);
        /* doing average anlyzing also even in Z option, results should be treated in make_report function later on */
        if (SAR_OPTION == 'Z')
            read_sar(i, sar_full_path_arr[i], 'A', REPORT, MESSAGE_ONLY, time_span);
    }
    /* closing dir pointer here */
    closedir(dir);

    make_report(SAR_OPTION, REPORT, files_n, time_span);
}

void read_sar_cpu_as_paragraph(const char *filename)
{
    FILE *fp;
    int lnr = 0;
    struct stat;
    char linebuf[MAX_LINE_LENGTH];
    char *line;
    int i;
    int _cpu_as_paragraph = 0;

    /* open sar file */
    if ((fp=fopen (filename,"r")) == NULL) {
        fprintf(stderr, "can't open file (%s): %s\n", filename, strerror(errno));
        /* freeing object and setting it to NULL */
        free_sar_analyzer_obj ();
        free_sosreport_analyzer_obj(0);
        exit (EXIT_FAILURE);
    }
    /* read file and parse lines */
    while (fgets (linebuf,sizeof (linebuf),fp) != NULL) {
        lnr++;
        line = linebuf;
        /* strip newline */
        i = (int) strlen(line);
        if ((i <= 0) || (line[i - 1] != '\n')) {
            fprintf(stderr, "%s:%d: line too long or last line missing newline\n Hint:$sed -i 's/\\x00//g' <sar_file>\n",filename,lnr);
            /* freeing object and setting it to NULL */
            free_sar_analyzer_obj ();
            free_sosreport_analyzer_obj(0);
            exit (EXIT_FAILURE);
        }
        line[i - 1] = '\0';
        /* ignore comment lines */
        if (line[0] == '#')
            continue;
        /* strip trailing spaces */
        for (i--; (i > 0) && isspace (line[i -1]) ; i--)
            line[i -1] = '\0';
        /* count cpu all line and set numbers to cpu_as_paragraph */
        if ( strstr ( *(&line), "Average" ) != 0 )
            break;
        if ((strstr (*(&line), "all") != 0)) 
            _cpu_as_paragraph++;
        set_cpu_as_paragraph (_cpu_as_paragraph);
    }
    /* after reading all lines, close the file pointer */
    fclose (fp);
}

void read_sar(int file_number, const char *filename, int SAR_OPTION,
    int REPORT, int MESSAGE_ONLY, const char *time_span)
{
    size_t filename_len = 0;
    filename_len = strlen (filename);
    if (filename_len <= 0) {
        fprintf(stderr, "no file name supplied (%s): %ld %s\n", filename, filename_len, strerror(errno));
        /* freeing object and setting it to NULL */
        free_sar_analyzer_obj();
        free_sosreport_analyzer_obj(0);
        exit(EXIT_FAILURE);
    }
    if (filename_len > MAX_FULL_PATH_LENGTH) {
        fprintf(stderr, "file name too long (%s): %ld %s\n", filename, filename_len, strerror(errno));
        /* freeing object and setting it to NULL */
        free_sar_analyzer_obj();
        free_sosreport_analyzer_obj(0);
        exit(EXIT_FAILURE);
    }
    FILE *fp;
    int lnr = 0;
    struct stat;
    char linebuf[MAX_LINE_LENGTH];
    char *line;
    size_t i;

    /* open sar file */
    if ((fp=fopen(filename, "r")) == NULL)
    {
        fprintf(stderr, "can't open file (%s): %s\n", filename, strerror(errno));
        /* freeing object and setting it to NULL */
        free_sar_analyzer_obj();
        free_sosreport_analyzer_obj(0);
        exit(EXIT_FAILURE);
    } else {
        char str_num[MAX_FILE_NAME_LENGTH + 1] = {'\0'};
        char str_tmp[18] = "--------filename:";
        strncpy(str_num, str_tmp, 18);
        strncat(str_num, filename, MAX_FILE_NAME_LENGTH);
        if (SAR_OPTION == 'Z')
            append_list(&line_obj, str_num);
        else
            append_list(&line_all_obj, str_num);
    }

    /* read file and parse lines */
    while (fgets(linebuf,sizeof(linebuf),fp) != NULL) {
        lnr++;
        line = linebuf;
        /* strip newline */
        i = strlen(line);
        if ((i <= 0) || (line[i - 1] != '\n')) {
            fprintf(stderr, "%s:%d: line too long or last line missing newline\n Hint:$sed -i 's/\\x00//g' <sar_file>\n", filename, lnr);
            /* freeing object and setting it to NULL */
            free_sar_analyzer_obj();
            free_sosreport_analyzer_obj(0);
            exit(EXIT_FAILURE);
        }
        line[i - 1] = '\0';
        /* ignore comment lines */
        if (line[0] == '#')
            continue;
        /* strip trailing spaces */
        for (i--; (i > 0) && isspace (line[i -1]) ; i--)
            line[i -1] = '\0';
        /* file sanity check */
        sanity_check_file(line, filename);
        /* get keyword from line and ignore empty lines */
        if (get_word_line(file_number, &line, SAR_OPTION, MESSAGE_ONLY, time_span) != 0)
            continue;
    }
    /* after reading all lines, close the file pointer */
    fclose(fp);
}

void read_sar_check(int file_number, const char *filename, int SAR_OPTION)
{
    size_t filename_len = 0;
    filename_len = strlen(filename);
    if (filename_len <= 0) {
        fprintf(stderr, "no file name supplied (%s): %ld %s\n", filename, filename_len, strerror(errno));
        /* freeing object and setting it to NULL */
        free_sar_analyzer_obj();
        free_sosreport_analyzer_obj(0);
        exit(EXIT_FAILURE);
    }
    if (filename_len > MAX_FULL_PATH_LENGTH) {
        fprintf(stderr, "file name too long (%s): %ld %s\n", filename, filename_len, strerror(errno));
        /* freeing object and setting it to NULL */
        free_sar_analyzer_obj();
        free_sosreport_analyzer_obj(0);
        exit(EXIT_FAILURE);
    }
    FILE *fp;
    int lnr = 0;
    struct stat;
    char linebuf[MAX_LINE_LENGTH];
    char *line;
    size_t i;

    /* open sar file */
    if ((fp=fopen(filename,"r")) == NULL) {
        fprintf(stderr, "can't open file (%s): %s\n", filename, strerror(errno));
        /* freeing object and setting it to NULL */
        free_sar_analyzer_obj();
        free_sosreport_analyzer_obj(0);
        exit(EXIT_FAILURE);
    }
    else
        append_list(&line_obj, "");

    /* read file and check healthness */
    while (fgets(linebuf,sizeof (linebuf),fp) != NULL) {
        lnr++;
        line = linebuf;
        /* strip newline */
        i = strlen(line);
        if ((i <= 0) || (line[i - 1] != '\n')) {
            fprintf(stderr, "%s:%d: line too long or last line missing newline\n Hint:$sed -i 's/\\x00//g' <sar_file>\n", filename, lnr);
            /* freeing object and setting it to NULL */
            free_sar_analyzer_obj();
            free_sosreport_analyzer_obj(0);
            exit(EXIT_FAILURE);
        }
        line[i - 1] = '\0';
        /* ignore comment lines */
        if (line[0] == '#')
            continue;
        /* strip trailing spaces */
        for (i--; (i > 0) && isspace (line[i -1]) ; i--)
            line[i -1] = '\0';
        /* file sanity check */
        sanity_check_file(line, filename);
    }
    /* after reading all lines, close the file pointer */
    fclose(fp);
    if (cpu_avg_checked_int == 0 || proc_s_avg_checked_int == 0 || pswpin_s_avg_checked_int == 0 ||
        pgpgin_s_avg_checked_int == 0 || tps_avg_checked_int == 0 || kbmemfree_avg_checked_int == 0 ||
        kbswpfree_avg_checked_int == 0 || kbhugfree_avg_checked_int == 0 || dentunusd_avg_checked_int == 0 ||
        runq_sz_avg_checked_int == 0 || dev_avg_checked_int == 0 || rxpck_s_avg_checked_int == 0 ||
        rxerr_s_avg_checked_int == 0 || call_s_avg_checked_int == 0 || scall_s_avg_checked_int == 0 ||
        totsck_avg_checked_int == 0 || squeezd_avg_checked_int == 0) {
        fprintf(stderr, "'Average' line lacks in file (%s)'\n", filename);
        puts("Please check below items in file.");
        puts("Or, your locale is en_US and still try to read ja_JP file?");
        puts("If that is the case, you can tweak libsar-analyzer/Makefile.am to use jp files.");
        puts("Sanity check faild!");
        puts("--------");
        free_sar_analyzer_obj();
        free_sosreport_analyzer_obj(0);
        printf("cpu_avg_checked (%s)\n", cpu_avg_checked);
        printf("proc_s_avg_checked (%s)\n", proc_s_avg_checked);
        printf("pswpin_s_avg_checked (%s)\n", pswpin_s_avg_checked);
        printf("pgpgin_s_avg_checked (%s)\n", pgpgin_s_avg_checked);
        printf("tps_avg_checked (%s)\n", tps_avg_checked);
        printf("kbmemfree_avg_checked (%s)\n", kbmemfree_avg_checked);
        printf("kbswpfree_avg_checked (%s)\n", kbswpfree_avg_checked);
        printf("kbhugfree_avg_checked (%s)\n", kbhugfree_avg_checked);
        printf("dentunusd_avg_checked (%s)\n", dentunusd_avg_checked);
        printf("runq_sz_avg_checked (%s)\n", runq_sz_avg_checked);
        printf("dev_avg_checked (%s)\n", dev_avg_checked);
        printf("rxpck_s_avg_checked (%s)\n", rxpck_s_avg_checked);
        printf("rxerr_s_avg_checked (%s)\n", rxerr_s_avg_checked);
        printf("call_s_avg_checked (%s)\n", call_s_avg_checked);
        printf("scall_s_avg_checked (%s)\n", scall_s_avg_checked);
        printf("totsck_avg_checked (%s)\n", totsck_avg_checked);
        printf("squeezd_avg_checked (%s)\n", squeezd_avg_checked);
        puts("--------");
        printf("cpu_avg_checked_int (%d)\n", cpu_avg_checked_int);
        printf("proc_s_avg_checked_int (%d)\n", proc_s_avg_checked_int);
        printf("pswpin_s_avg_checked_int (%d)\n", pswpin_s_avg_checked_int);
        printf("pgpgin_s_avg_checked_int (%d)\n", pgpgin_s_avg_checked_int);
        printf("tps_avg_checked_int (%d)\n", tps_avg_checked_int);
        printf("kbmemfree_avg_checked_int (%d)\n", kbmemfree_avg_checked_int);
        printf("kbswpfree_avg_checked_int (%d)\n", kbswpfree_avg_checked_int);
        printf("kbhugfree_avg_checked_int (%d)\n", kbhugfree_avg_checked_int);
        printf("dentunusd_avg_checked_int (%d)\n", dentunusd_avg_checked_int);
        printf("runq_sz_avg_checked_int (%d)\n", runq_sz_avg_checked_int);
        printf("dev_avg_checked_int (%d)\n", dev_avg_checked_int);
        printf("rxpck_s_avg_checked_int (%d)\n", rxpck_s_avg_checked_int);
        printf("rxerr_s_avg_checked_int (%d)\n", rxerr_s_avg_checked_int);
        printf("call_s_avg_checked_int (%d)\n", call_s_avg_checked_int);
        printf("scall_s_avg_checked_int (%d)\n", scall_s_avg_checked_int);
        printf("totsck_avg_checked_int (%d)\n", totsck_avg_checked_int);
        printf("squeezd_avg_checked_int (%d)\n",squeezd_avg_checked_int);
        exit(EXIT_FAILURE);
    }
}

const char *get_dir_name_analyze(void)
{
    return sar_analyzer_obj->dir_name_analyze;
}

char *get_hostname(void)
{
    return sar_analyzer_all_obj->hostname;
}

int get_core_numbers(void)
{
    return sar_analyzer_obj->cores_n;
}

int get_network_device_numbers(void)
{
    /* ask get_network_device_names () string 'ignore' and it's number minus 1 should be the max network devices */
    int x = 0;
    for (x = 1; x < MAX_NETWORK_DEVICE_NUMBERS; x++)
        if (strcmp ((char *)get_network_device_names(x), "ignore") == 0)
            return x;
    return 1;
}

const char *get_network_device_names(int x)
{
    return sar_analyzer_obj->network_device_names[x];
}

int get_block_device_numbers(void)
{
    /* ask get_block_device_names () string 'ignore' and it's number minus 1 should be the max block devices */
    int x = 0;
    for (x = 1; x < MAX_BLOCK_DEVICE_NUMBERS; x++)
        if (strcmp((char *)get_block_device_names(x), "ignore") == 0)
            return x;
    return 1;
}

const char *get_block_device_names(int x)
{
    return sar_analyzer_obj->device_names[x];
}

void set_network_device_names(const char *network_device_name)
{
    if (search_network_device_name (network_device_name) == 0)
        strcpy(sar_analyzer_obj->network_device_names[get_network_device_numbers ()], network_device_name);
}

int get_files_n(void)
{
    return sar_analyzer_obj->files_n;
}

int file_to_write (int SAR_OPTION)
{
    char buff[MAX_FILE_NAME_LENGTH]; 
    char buff2[MAX_FILE_NAME_LENGTH]; 
    char f_t[40];
    memset(buff, '\0', MAX_FILE_NAME_LENGTH); 
    memset(buff2, '\0', MAX_FILE_NAME_LENGTH); 
    memset(f_t, '\0', 40); 
    strncpy(buff, "saj-results", MAX_FILE_NAME_LENGTH);
    strncpy(buff2, "saj-results", MAX_FILE_NAME_LENGTH);
    strncat(buff, "/sar_result_all", 16);
    strncat(buff2, "/sar_result_all", 16);

    struct tm *timenow;
    time_t now = time(NULL);
    timenow = localtime(&now);

    strftime(f_t, sizeof(f_t), "_%Y%m%d%H%M%S", timenow);

    strncat(buff, f_t, MAX_FILE_NAME_LENGTH - 1);
    strncat(buff2, f_t, MAX_FILE_NAME_LENGTH - 1);

    /* here, we ommit .ps for buff2, which will be added later on in main.c */
    if (SAR_OPTION ==  'u') {
        strncat (buff, "_CPU_utilization.txt", MAX_FILE_NAME_LENGTH - 1);
        strncat (buff2, "_CPU_utilization", MAX_FILE_NAME_LENGTH - 1);
    } else if (SAR_OPTION ==  'B') {
        strncat (buff, "_paging_statistics.txt", MAX_FILE_NAME_LENGTH - 1);
        strncat (buff2, "_paging_statistics", MAX_FILE_NAME_LENGTH - 1);
    } else if (SAR_OPTION ==  'd') {
        strncat (buff, "_activity_for_each_block_device.txt", MAX_FILE_NAME_LENGTH - 1);
        strncat (buff2, "_activity_for_each_block_device", MAX_FILE_NAME_LENGTH - 1);
    } else if (SAR_OPTION ==  'b') {
        strncat (buff, "_IO_and_transfer_rate_statistics.txt", MAX_FILE_NAME_LENGTH - 1);
        strncat (buff2, "_IO_and_transfer_rate_statistics", MAX_FILE_NAME_LENGTH - 1);
    } else if (SAR_OPTION ==  'H') {
        strncat (buff, "_hugepages_utilization_statistics.txt", MAX_FILE_NAME_LENGTH - 1);
        strncat (buff2, "_hugepages_utilization_statistics", MAX_FILE_NAME_LENGTH - 1);
    } else if (SAR_OPTION ==  'n') {
        strncat (buff, "_network_statistics.txt", MAX_FILE_NAME_LENGTH - 1);
        strncat (buff2, "_network_statistics", MAX_FILE_NAME_LENGTH - 1);
    } else if (SAR_OPTION ==  'm') {
        strncat (buff, "_network_statistics_error.txt", MAX_FILE_NAME_LENGTH - 1);
        strncat (buff2, "_network_statistics_error", MAX_FILE_NAME_LENGTH - 1);
    } else if (SAR_OPTION ==  'q') {
        strncat (buff, "_queue_length_and_load_averages.txt", MAX_FILE_NAME_LENGTH - 1);
        strncat (buff2, "_queue_length_and_load_averages", MAX_FILE_NAME_LENGTH - 1);
    } else if (SAR_OPTION ==  'r') {
        strncat (buff, "_memory_utilization_statistics.txt", MAX_FILE_NAME_LENGTH - 1);
        strncat (buff2, "_memory_utilization_statistics", MAX_FILE_NAME_LENGTH - 1);
    } else if (SAR_OPTION ==  'S') {
        strncat (buff, "_swap_space_utilization_statistics.txt", MAX_FILE_NAME_LENGTH - 1);
        strncat (buff2, "_swap_space_utilization_statistics", MAX_FILE_NAME_LENGTH - 1);
    } else if (SAR_OPTION ==  'v') {
        strncat (buff, "_kernel_tables.txt", MAX_FILE_NAME_LENGTH - 1);
        strncat (buff2, "_kernel_tables", MAX_FILE_NAME_LENGTH - 1);
    } else if (SAR_OPTION ==  'W') {
        strncat (buff, "_swapping_statistics.txt", MAX_FILE_NAME_LENGTH - 1);
        strncat (buff2, "_swapping_statistics", MAX_FILE_NAME_LENGTH - 1);

    } else if (SAR_OPTION ==  'w') {
        strncat (buff, "_task_creation_and_system_switching_activity.txt", MAX_FILE_NAME_LENGTH - 1);
        strncat (buff2, "_task_creation_and_system_switching_activity", MAX_FILE_NAME_LENGTH - 1);
    } else if (SAR_OPTION ==  'y') {
        strncat (buff, "_TTY_devices_activity.txt", MAX_FILE_NAME_LENGTH - 1);
        strncat (buff2, "_TTY_devices_activity", MAX_FILE_NAME_LENGTH - 1);
    }
    else
        strncat(buff, ".txt", MAX_FILE_NAME_LENGTH - 1);

    /* Here we use strcpy. No worry, buff is surely under MAX_FILE_NAME_LENGTH */
    strcpy(sar_analyzer_obj->file_name_to_be_written, buff);
    /* We create postscript file name too */
    strcpy(sar_analyzer_all_obj->file_name_to_be_written, buff2);

    return 0;
}

void sanity_check_file(char * line, const char * filename)
{
    if (strstr(line, "LINUX RESTART") != 0)
        initialize_avg_checked_int ();

    if ((cpu == 1) && (proc_s == 0) && (strstr(line, "Average") != 0)) {
        cpu_avg_checked_int = 1;
        cpu_avg_checked = "Checked";
    }
    if ((proc_s == 1) && (pswpin_s == 0) && (strstr(line, "Average") != 0)) {
        proc_s_avg_checked_int = 1;
        proc_s_avg_checked = "Checked";
    }
    if ((pswpin_s == 1) && (pgpgin_s == 0) && (strstr(line, "Average") != 0)) {
        pswpin_s_avg_checked_int = 1;
        pswpin_s_avg_checked = "Checked";
    }
    if ((pgpgin_s == 1) && (tps == 0) && (strstr(line, "Average") != 0)) {
        pgpgin_s_avg_checked_int = 1;
        pgpgin_s_avg_checked = "Checked";
    }
    if ((tps == 1) && (kbmemfree == 0) && (strstr(line, "Average") != 0)) {
        tps_avg_checked_int = 1;
        tps_avg_checked = "Checked";
    }
    if ((kbmemfree == 1) && (kbswpfree == 0) && (strstr(line, "Average") != 0)) {
        kbmemfree_avg_checked_int = 1;
        kbmemfree_avg_checked = "Checked";
    }
    if ((kbswpfree == 1) && (strstr(line, "Average") != 0)) {
        if ((kbhugfree == 1) || (dentunusd == 0)) {
            kbswpfree_avg_checked_int = 1;
            kbswpfree_avg_checked = "Checked";
            kbhugfree_avg_checked_int = 1;
            kbhugfree_avg_checked = "Checked";
        }
    }
    if ((kbhugfree == 1) && (dentunusd == 0) && (strstr(line, "Average") != 0)) {
        kbhugfree_avg_checked_int = 1;
        kbhugfree_avg_checked = "Checked";
    }
    if ((dentunusd == 1) && (runq_sz == 0) && (strstr(line, "Average") != 0)) {
        dentunusd_avg_checked_int = 1;
        dentunusd_avg_checked = "Checked";
    }
    if ((runq_sz == 1) && (dev == 0) && (strstr(line, "Average") != 0)) {
        runq_sz_avg_checked_int = 1;
        runq_sz_avg_checked = "Checked";
    }
    if ((dev == 1) && (rxpck_s == 0) && (strstr(line, "Average") != 0)) {
        dev_avg_checked_int = 1;
        dev_avg_checked = "Checked";
    }
    if ((rxpck_s == 1) && (rxerr_s == 0) && (strstr(line, "Average") != 0)) {
        rxpck_s_avg_checked_int = 1;
        rxpck_s_avg_checked = "Checked";
    }
    if ((rxerr_s == 1) && (call_s == 0) && (strstr(line, "Average") != 0)) {
        rxerr_s_avg_checked_int = 1;
        rxerr_s_avg_checked = "Checked";
    }
    if ((call_s == 1) && (scall_s == 0) && (strstr(line, "Average") != 0)) {
        call_s_avg_checked_int = 1;
        call_s_avg_checked = "Checked";
    }
    if ((scall_s == 1) && (totsck == 0) && (strstr(line, "Average") != 0)) {
        scall_s_avg_checked_int = 1;
        scall_s_avg_checked = "Checked";
    }
    if ((totsck == 1) && (strstr(line, "Average") != 0)) {
        if (squeezd == 0) {
            totsck_avg_checked_int = 1;
            totsck_avg_checked = "Checked";
            squeezd_avg_checked_int = 1;
            squeezd_avg_checked = "Checked";
        }
    }
    if ((squeezd == 1) && (strstr(line, "Average") != 0)) {
        squeezd_avg_checked_int = 1;
        squeezd_avg_checked = "Checked";
    }
    if (strstr(line, "iowait") != 0)
        cpu = 1;
    if (strstr(line, "proc/s") != 0 )
        proc_s = 1;
    if (strstr(line, "pswpin/s") != 0)
        pswpin_s = 1;
    if (strstr(line, "pgpgin/s") != 0)
        pgpgin_s = 1;
    if (strstr(line, "tps") != 0)
        tps = 1;
    if (strstr(line, "kbmemfree") != 0)
        kbmemfree = 1;
    if (strstr(line, "kbswpfree") != 0)
        kbswpfree = 1;
    if (strstr(line, "kbhugfree") != 0)
        kbhugfree = 1;
    if (strstr(line, "dentunusd") != 0)
        dentunusd = 1;
    if (strstr(line, "runq-sz") != 0)
        runq_sz = 1;
    if (strstr(line, "DEV") != 0)
        dev = 1;
    if (strstr(line, "rxpck/s") != 0)
        rxpck_s = 1;
    if (strstr(line, "rxerr/s") != 0)
        rxerr_s = 1;
    if (strstr(line, "retrans") != 0)
        call_s = 1;
    if (strstr(line, "scall/s") != 0)
        scall_s = 1;
    if (strstr(line, "totsck") != 0)
        totsck = 1;
    if (strstr(line, "squeezd") != 0)
        squeezd = 1;
}

int check_result_dir(const char *dname, int sar_only, int tmp)
{
    if (dname != NULL)
    {
        /* if open directory fails, create it, if it fails, exit with error message */
        if (!opendir (dname)) 
        {
            fprintf(stderr, "can't open directory %s\n", dname);
            printf("Creating directory %s\n", dname);
            if (mkdir (dname, 0755) == 0)
                printf("Created directory %s\n", dname);
            else
            {
                fprintf(stderr, "can't open directory %s\n", dname);
                free_sar_analyzer_obj();
                free_sosreport_analyzer_obj(0);
                exit(EXIT_FAILURE);
            }
        }
    }
    return 0;
}

void remove_unneeded_files (const char *filename, const char *extension)
{
    int err;
    char buff[MAX_FILE_NAME_LENGTH]; 
    memset (buff, '\0', MAX_FILE_NAME_LENGTH); 
    snprintf (buff, MAX_FILE_NAME_LENGTH, "rm -f %s*.%s", filename, extension);
    err = system (buff);
    if (err)
    {
        fprintf(stderr, "command failed: %s (%d)\n", buff, err);
        free_sar_analyzer_obj ();
        free_sosreport_analyzer_obj(0);
        exit(EXIT_FAILURE);
    }
    else 
        printf ("Did %s\n", buff);
}

void sar_analyzer_init(const char *dname, const char *fname, int SAR_OPTION,
    int REPORT, int MESSAGE_ONLY, const char *time_span)
{
    if (dname != NULL) {
        /* if open directory fails, exit with error message */
        DIR *dir;
        if ((dir = opendir(dname)) == NULL) 
        {
            fprintf(stderr, "cannot open directory (%s): %s\n", dname, strerror(errno));
            free_sar_analyzer_obj();
            free_sosreport_analyzer_obj(0);
            exit(EXIT_FAILURE);
        }
        /* this is needed to suppress memory leak */
        closedir(dir);
        /* now, creating object */
        create_sar_analyzer_obj();
        /* setting directory name */
        set_dir_name_analyze(dname);

        /* read sa directory */
        read_sa_dir(dname, SAR_OPTION, REPORT, MESSAGE_ONLY, time_span);
    }
    else if (fname != NULL) {
        puts("this function is almost done, but right now, please use directory option...");
        free_sar_analyzer_obj ();
        free_sosreport_analyzer_obj(0);
        exit (EXIT_FAILURE);
    } else {
        fprintf(stderr, "file or directory name not present\n");
        free_sar_analyzer_obj();
        free_sosreport_analyzer_obj(0);
        exit(EXIT_FAILURE);
    }
}

int create_sar_analyzer_obj()
{
    int i = 0;
    int x = 0;

    /* initialize some of the items here */

    initialize_block_device_name();
    initialize_network_device_name();

    /* for dates and time */
    set_this_date("1970/1/1");
    set_this_date_all("1970/1/1");
    set_this_date_former("1970/1/1");
    set_this_date_all_former("1970/1/1");
    set_this_time("00:00:00");
    set_this_time_all("00:00:00");
    set_this_time_former("00:00:00");
    set_this_time_all_former("00:00:00");
    set_this_time_former2("00:00:00");
    set_this_time_all_former2("00:00:00");

    /* these values should be small enough for the comparison */

    /* ---- Averages highest ---- */

    /* CPU all, 0 to MAX_CORE_NUMBERS */
    for (i = 0; i <= MAX_CORE_NUMBERS; i++) {
        set_cpu_avg_highest_val(0.00, i, "usr");
        set_cpu_avg_highest_val(0.00, i, "sys");
        set_cpu_avg_highest_val(0.00, i, "iowait");
        set_cpu_avg_highest_val(0.00, i, "idle");
    }

    set_tasks_avg_highest_val(0.00, "proc");
    set_tasks_avg_highest_val(0.00, "cswch");
    set_pswap_avg_highest_val(0, "pswpin");
    set_pswap_avg_highest_val(0, "pswpout");
    set_paging_avg_highest_val(0.00, "pgpgin");
    set_paging_avg_highest_val(0.00, "pgpgout");
    set_paging_avg_highest_val(0.00, "fault");
    set_paging_avg_highest_val(0.00, "majflt");
    set_paging_avg_highest_val(0.00, "vmeff");
    set_io_transfer_rate_avg_highest_val(0.00, "tps");
    set_io_transfer_rate_avg_highest_val(0.00, "bread");
    set_io_transfer_rate_avg_highest_val(0.00, "bwrtn");
    set_memory_double_avg_highest_val(0.00, "memused");
    set_memory_double_avg_highest_val(0.00, "commit");
    set_memory_int_avg_highest_val(0.00, "kbcommit");
    set_swpused_avg_highest_val(0.00);
    set_kernel_table_avg_highest_val(0, "dentunusd");
    set_kernel_table_avg_highest_val(0, "file");
    set_kernel_table_avg_highest_val(0, "inode");
    set_ldavg_int_avg_highest_val(0, "runq_sz");
    set_ldavg_int_avg_highest_val(0, "plist_sz");
    set_ldavg_double_avg_highest_val(0.00, "ldavg_one");
    set_ldavg_double_avg_highest_val(0.00, "ldavg_five");
    set_ldavg_double_avg_highest_val(0.00, "ldavg_15");

    /* up to MAX_DEVICE_NUMBERS */
    for (i = 0; i < MAX_BLOCK_DEVICE_NUMBERS; i++) {
        set_block_device_avg_highest_val(0.00, i, "areqsz");
        set_block_device_avg_highest_val(0.00, i, "util");
    }

    /* up to MAX_NETWORK_DEVICE_NUMBERS */
    for (i = 0; i < MAX_NETWORK_DEVICE_NUMBERS; i++) {
        set_network_avg_highest_val(0.00, i, "rxpck");
        set_network_avg_highest_val(0.00, i, "txpck");
        set_network_avg_highest_val(0.00, i, "rxkb");
        set_network_avg_highest_val(0.00, i, "txkb");
        set_network_avg_highest_val(0.00, i, "rxerr");
        set_network_avg_highest_val(0.00, i, "txerr");
        set_network_avg_highest_val(0.00, i, "rxdrop");
        set_network_avg_highest_val(0.00, i, "txdrop");
        set_network_former_val(0.00, i, "rxpck");
        set_network_former_val(0.00, i, "txpck");
        set_network_former_val(0.00, i, "rxkb");
        set_network_former_val(0.00, i, "txkb");
        set_network_former_val(0.00, i, "rxerr");
        set_network_former_val(0.00, i, "txerr");
        set_network_former_val(0.00, i, "rxdrop");
        set_network_former_val(0.00, i, "txdrop");
    }

    /*  initialize spike and former each file */

    for (x = 0; x < MAX_ANALYZE_FILES ; x++) {
        for (i = 0; i <= MAX_CORE_NUMBERS; i++) {
            set_cpu_spike_val_each_file(x, 0.00, i, "usr", "spike");
            set_cpu_spike_date_each_file(x, "", i, "usr", "spike");
            set_cpu_spike_time_each_file(x, "", i, "usr", "spike");
            set_cpu_spike_val_each_file(x, 0.00, i, "usr", "highest");
            set_cpu_spike_date_each_file(x, "", i, "usr", "highest");
            set_cpu_spike_time_each_file(x, "", i, "usr", "highest");
            set_cpu_spike_val_each_file(x, 100.00, i, "usr", "lowest");
            set_cpu_spike_date_each_file(x, "", i, "usr", "lowest");
            set_cpu_spike_time_each_file(x, "", i, "usr", "lowest");
            set_cpu_spike_val_each_file(x, 0.00, i, "sys", "spike");
            set_cpu_spike_date_each_file(x, "", i, "sys", "spike");
            set_cpu_spike_time_each_file(x, "", i, "sys", "spike");
            set_cpu_spike_val_each_file(x, 0.00, i, "sys", "highest");
            set_cpu_spike_date_each_file(x, "", i, "sys", "highest");
            set_cpu_spike_time_each_file(x, "", i, "sys", "highest");
            set_cpu_spike_val_each_file(x, 100.00, i, "sys", "lowest");
            set_cpu_spike_date_each_file(x, "", i, "sys", "lowest");
            set_cpu_spike_time_each_file(x, "", i, "sys", "lowest");
            set_cpu_spike_val_each_file(x, 0.00, i, "iowait", "spike");
            set_cpu_spike_date_each_file(x, "", i, "iowait", "spike");
            set_cpu_spike_time_each_file(x, "", i, "iowait", "spike");
            set_cpu_spike_val_each_file(x, 0.00, i, "iowait", "highest");
            set_cpu_spike_date_each_file(x, "", i, "iowait", "highest");
            set_cpu_spike_time_each_file(x, "", i, "iowait", "highest");
            set_cpu_spike_val_each_file(x, 100.00, i, "iowait", "lowest");
            set_cpu_spike_date_each_file(x, "", i, "iowait", "lowest");
            set_cpu_spike_time_each_file(x, "", i, "iowait", "lowest");
            set_cpu_spike_val_each_file(x, 0.00, i, "idle", "spike");
            set_cpu_spike_date_each_file(x, "", i, "idle", "spike");
            set_cpu_spike_time_each_file(x, "", i, "idle", "spike");
            set_cpu_spike_val_each_file(x, 0.00, i, "idle", "highest");
            set_cpu_spike_date_each_file(x, "", i, "idle", "highest");
            set_cpu_spike_time_each_file(x, "", i, "idle", "highest");
            set_cpu_spike_val_each_file(x, 100.00, i, "idle", "lowest");
            set_cpu_spike_date_each_file(x, "", i, "idle", "lowest");
            set_cpu_spike_time_each_file(x, "", i, "idle", "lowest");

            set_cpu_time_span_spike_val_each_file(x, 0.00, i, "usr", "spike");
            set_cpu_time_span_spike_date_each_file(x, "", i, "usr", "spike");
            set_cpu_time_span_spike_time_each_file(x, "", i, "usr", "spike");
            set_cpu_time_span_spike_val_each_file(x, 0.00, i, "usr", "highest");
            set_cpu_time_span_spike_date_each_file(x, "", i, "usr", "highest");
            set_cpu_time_span_spike_time_each_file(x, "", i, "usr", "highest");
            set_cpu_time_span_spike_val_each_file(x, 100.00, i, "usr", "lowest");
            set_cpu_time_span_spike_date_each_file(x, "", i, "usr", "lowest");
            set_cpu_time_span_spike_time_each_file(x, "", i, "usr", "lowest");
            set_cpu_time_span_spike_val_each_file(x, 0.00, i, "sys", "spike");
            set_cpu_time_span_spike_date_each_file(x, "", i, "sys", "spike");
            set_cpu_time_span_spike_time_each_file(x, "", i, "sys", "spike");
            set_cpu_time_span_spike_val_each_file(x, 0.00, i, "sys", "highest");
            set_cpu_time_span_spike_date_each_file(x, "", i, "sys", "highest");
            set_cpu_time_span_spike_time_each_file(x, "", i, "sys", "highest");
            set_cpu_time_span_spike_val_each_file(x, 100.00, i, "sys", "lowest");
            set_cpu_time_span_spike_date_each_file(x, "", i, "sys", "lowest");
            set_cpu_time_span_spike_time_each_file(x, "", i, "sys", "lowest");
            set_cpu_time_span_spike_val_each_file(x, 0.00, i, "iowait", "spike");
            set_cpu_time_span_spike_date_each_file(x, "", i, "iowait", "spike");
            set_cpu_time_span_spike_time_each_file(x, "", i, "iowait", "spike");
            set_cpu_time_span_spike_val_each_file(x, 0.00, i, "iowait", "highest");
            set_cpu_time_span_spike_date_each_file(x, "", i, "iowait", "highest");
            set_cpu_time_span_spike_time_each_file(x, "", i, "iowait", "highest");
            set_cpu_time_span_spike_val_each_file(x, 100.00, i, "iowait", "lowest");
            set_cpu_time_span_spike_date_each_file(x, "", i, "iowait", "lowest");
            set_cpu_time_span_spike_time_each_file(x, "", i, "iowait", "lowest");
            set_cpu_time_span_spike_val_each_file(x, 0.00, i, "idle", "spike");
            set_cpu_time_span_spike_date_each_file(x, "", i, "idle", "spike");
            set_cpu_time_span_spike_time_each_file(x, "", i, "idle", "spike");
            set_cpu_time_span_spike_val_each_file(x, 0.00, i, "idle", "highest");
            set_cpu_time_span_spike_date_each_file(x, "", i, "idle", "highest");
            set_cpu_time_span_spike_time_each_file(x, "", i, "idle", "highest");
            set_cpu_time_span_spike_val_each_file(x, 100.00, i, "idle", "lowest");
        }
        set_tasks_spike_val_each_file(x, 0.00, "proc", "spike");
        set_tasks_spike_date_each_file(x, "", "proc", "spike");
        set_tasks_spike_time_each_file(x, "", "proc", "spike");
        set_tasks_spike_val_each_file(x, 0.00, "proc", "highest");
        set_tasks_spike_date_each_file(x, "", "proc", "highest");
        set_tasks_spike_time_each_file(x, "", "proc", "highest");
        set_tasks_spike_val_each_file(x, 1999999.00, "proc", "lowest");
        set_tasks_spike_date_each_file(x, "", "proc", "lowest");
        set_tasks_spike_time_each_file(x, "", "proc", "lowest");
        set_tasks_spike_val_each_file(x, 0.00, "cswch", "spike");
        set_tasks_spike_date_each_file(x, "", "cswch", "spike");
        set_tasks_spike_time_each_file(x, "", "cswch", "spike");
        set_tasks_spike_val_each_file(x, 0.00, "cswch", "highest");
        set_tasks_spike_date_each_file(x, "", "cswch", "highest");
        set_tasks_spike_time_each_file(x, "", "cswch", "highest");
        set_tasks_spike_val_each_file(x, 19999999.00, "cswch", "lowest");
        set_tasks_spike_date_each_file(x, "", "cswch", "lowest");
        set_tasks_spike_time_each_file(x, "", "cswch", "lowest");

        set_tasks_time_span_spike_val_each_file(x, 0.00, "proc", "spike");
        set_tasks_time_span_spike_date_each_file(x, "", "proc", "spike");
        set_tasks_time_span_spike_time_each_file(x, "", "proc", "spike");
        set_tasks_time_span_spike_val_each_file(x, 0.00, "proc", "highest");
        set_tasks_time_span_spike_date_each_file(x, "", "proc", "highest");
        set_tasks_time_span_spike_time_each_file(x, "", "proc", "highest");
        set_tasks_time_span_spike_val_each_file(x, 1999999.00, "proc", "lowest");
        set_tasks_time_span_spike_date_each_file(x, "", "proc", "lowest");
        set_tasks_time_span_spike_time_each_file(x, "", "proc", "lowest");
        set_tasks_time_span_spike_val_each_file(x, 0.00, "cswch", "spike");
        set_tasks_time_span_spike_date_each_file(x, "", "cswch", "spike");
        set_tasks_time_span_spike_time_each_file(x, "", "cswch", "spike");
        set_tasks_time_span_spike_val_each_file(x, 0.00, "cswch", "highest");
        set_tasks_time_span_spike_date_each_file(x, "", "cswch", "highest");
        set_tasks_time_span_spike_time_each_file(x, "", "cswch", "highest");
        set_tasks_time_span_spike_val_each_file(x, 19999999.00, "cswch", "lowest");
        set_tasks_time_span_spike_date_each_file(x, "", "cswch", "lowest");
        set_tasks_time_span_spike_time_each_file(x, "", "cswch", "lowest");

        set_pswap_spike_val_each_file(x, 0.00, "pswpin", "spike");
        set_pswap_spike_date_each_file(x, "", "pswpin", "spike");
        set_pswap_spike_time_each_file(x, "", "pswpin", "spike");
        set_pswap_spike_val_each_file(x, 0.00, "pswpin", "highest");
        set_pswap_spike_date_each_file(x, "", "pswpin", "highest");
        set_pswap_spike_time_each_file(x, "", "pswpin", "highest");
        set_pswap_spike_val_each_file(x, 9999999.00, "pswpin", "lowest");
        set_pswap_spike_date_each_file(x, "", "pswpin", "lowest");
        set_pswap_spike_time_each_file(x, "", "pswpin", "lowest");
        set_pswap_spike_val_each_file(x, 0.00, "pswpout", "spike");
        set_pswap_spike_date_each_file(x, "", "pswpout", "spike");
        set_pswap_spike_time_each_file(x, "", "pswpout", "spike");
        set_pswap_spike_val_each_file(x, 0.00, "pswpout", "highest");
        set_pswap_spike_date_each_file(x, "", "pswpout", "highest");
        set_pswap_spike_time_each_file(x, "", "pswpout", "highest");
        set_pswap_spike_val_each_file(x, 9999999.00, "pswpout", "lowest");
        set_pswap_spike_date_each_file(x, "", "pswpout", "lowest");
        set_pswap_spike_time_each_file(x, "", "pswpout", "lowest");

        set_pswap_time_span_spike_val_each_file(x, 0.00, "pswpin", "spike");
        set_pswap_time_span_spike_date_each_file(x, "", "pswpin", "spike");
        set_pswap_time_span_spike_time_each_file(x, "", "pswpin", "spike");
        set_pswap_time_span_spike_val_each_file(x, 0.00, "pswpin", "highest");
        set_pswap_time_span_spike_date_each_file(x, "", "pswpin", "highest");
        set_pswap_time_span_spike_time_each_file(x, "", "pswpin", "highest");
        set_pswap_time_span_spike_val_each_file(x, 9999999.00, "pswpin", "lowest");
        set_pswap_time_span_spike_date_each_file(x, "", "pswpin", "lowest");
        set_pswap_time_span_spike_time_each_file(x, "", "pswpin", "lowest");
        set_pswap_time_span_spike_val_each_file(x, 0.00, "pswpout", "spike");
        set_pswap_time_span_spike_date_each_file(x, "", "pswpout", "spike");
        set_pswap_time_span_spike_time_each_file(x, "", "pswpout", "spike");
        set_pswap_time_span_spike_val_each_file(x, 0.00, "pswpout", "highest");
        set_pswap_time_span_spike_date_each_file(x, "", "pswpout", "highest");
        set_pswap_time_span_spike_time_each_file(x, "", "pswpout", "highest");
        set_pswap_time_span_spike_val_each_file(x, 9999999.00, "pswpout", "lowest");
        set_pswap_time_span_spike_date_each_file(x, "", "pswpout", "lowest");
        set_pswap_time_span_spike_time_each_file(x, "", "pswpout", "lowest");

        set_paging_spike_val_each_file(x, 0.00, "pgpgin", "spike");
        set_paging_spike_date_each_file(x, "", "pgpgin", "spike");
        set_paging_spike_time_each_file(x, "", "pgpgin", "spike");
        set_paging_spike_val_each_file(x, 0.00, "pgpgin", "highest");
        set_paging_spike_date_each_file(x, "", "pgpgin", "highest");
        set_paging_spike_time_each_file(x, "", "pgpgin", "highest");
        set_paging_spike_val_each_file(x, 9999999.00, "pgpgin", "lowest");
        set_paging_spike_date_each_file(x, "", "pgpgin", "lowest");
        set_paging_spike_time_each_file(x, "", "pgpgin", "lowest");
        set_paging_spike_val_each_file(x, 0.00, "pgpgout", "spike");
        set_paging_spike_date_each_file(x, "", "pgpgout", "spike");
        set_paging_spike_time_each_file(x, "", "pgpgout", "spike");
        set_paging_spike_val_each_file(x, 0.00, "pgpgout", "highest");
        set_paging_spike_date_each_file(x, "", "pgpgout", "highest");
        set_paging_spike_time_each_file(x, "", "pgpgout", "highest");
        set_paging_spike_val_each_file(x, 9999999.00, "pgpgout", "lowest");
        set_paging_spike_date_each_file(x, "", "pgpgout", "lowest");
        set_paging_spike_time_each_file(x, "", "pgpgout", "lowest");
        set_paging_spike_val_each_file(x, 0.00, "fault", "spike");
        set_paging_spike_date_each_file(x, "", "fault", "spike");
        set_paging_spike_time_each_file(x, "", "fault", "spike");
        set_paging_spike_val_each_file(x, 0.00, "fault", "highest");
        set_paging_spike_date_each_file(x, "", "fault", "highest");
        set_paging_spike_time_each_file(x, "", "fault", "highest");
        set_paging_spike_val_each_file(x, 19999999.00, "fault", "lowest");
        set_paging_spike_date_each_file(x, "", "fault", "lowest");
        set_paging_spike_time_each_file(x, "", "fault", "lowest");
        set_paging_spike_val_each_file(x, 0.00, "majflt", "spike");
        set_paging_spike_date_each_file(x, "", "majflt", "spike");
        set_paging_spike_time_each_file(x, "", "majflt", "spike");
        set_paging_spike_val_each_file(x, 0.00, "majflt", "highest");
        set_paging_spike_date_each_file(x, "", "majflt", "highest");
        set_paging_spike_time_each_file(x, "", "majflt", "highest");
        set_paging_spike_val_each_file(x, 19999999.00, "majflt", "lowest");
        set_paging_spike_date_each_file(x, "", "majflt", "lowest");
        set_paging_spike_time_each_file(x, "", "majflt", "lowest");
        set_paging_spike_val_each_file(x, 0.00, "vmeff", "spike");
        set_paging_spike_date_each_file(x, "", "vmeff", "spike");
        set_paging_spike_time_each_file(x, "", "vmeff", "spike");
        set_paging_spike_val_each_file(x, 0.00, "vmeff", "highest");
        set_paging_spike_date_each_file(x, "", "vmeff", "highest");
        set_paging_spike_time_each_file(x, "", "vmeff", "highest");
        set_paging_spike_val_each_file(x, 100.00, "vmeff", "lowest");
        set_paging_spike_date_each_file(x, "", "vmeff", "lowest");
        set_paging_spike_time_each_file(x, "", "vmeff", "lowest");

        set_paging_time_span_spike_val_each_file(x, 0.00, "pgpgin", "spike");
        set_paging_time_span_spike_date_each_file(x, "", "pgpgin", "spike");
        set_paging_time_span_spike_time_each_file(x, "", "pgpgin", "spike");
        set_paging_time_span_spike_val_each_file(x, 0.00, "pgpgin", "highest");
        set_paging_time_span_spike_date_each_file(x, "", "pgpgin", "highest");
        set_paging_time_span_spike_time_each_file(x, "", "pgpgin", "highest");
        set_paging_time_span_spike_val_each_file(x, 9999999.00, "pgpgin", "lowest");
        set_paging_time_span_spike_date_each_file(x, "", "pgpgin", "lowest");
        set_paging_time_span_spike_time_each_file(x, "", "pgpgin", "lowest");
        set_paging_time_span_spike_val_each_file(x, 0.00, "pgpgout", "spike");
        set_paging_time_span_spike_date_each_file(x, "", "pgpgout", "spike");
        set_paging_time_span_spike_time_each_file(x, "", "pgpgout", "spike");
        set_paging_time_span_spike_val_each_file(x, 0.00, "pgpgout", "highest");
        set_paging_time_span_spike_date_each_file(x, "", "pgpgout", "highest");
        set_paging_time_span_spike_time_each_file(x, "", "pgpgout", "highest");
        set_paging_time_span_spike_val_each_file(x, 9999999.00, "pgpgout", "lowest");
        set_paging_time_span_spike_date_each_file(x, "", "pgpgout", "lowest");
        set_paging_time_span_spike_time_each_file(x, "", "pgpgout", "lowest");
        set_paging_time_span_spike_val_each_file(x, 0.00, "fault", "spike");
        set_paging_time_span_spike_date_each_file(x, "", "fault", "spike");
        set_paging_time_span_spike_time_each_file(x, "", "fault", "spike");
        set_paging_time_span_spike_val_each_file(x, 0.00, "fault", "highest");
        set_paging_time_span_spike_date_each_file(x, "", "fault", "highest");
        set_paging_time_span_spike_time_each_file(x, "", "fault", "highest");
        set_paging_time_span_spike_val_each_file(x, 19999999.00, "fault", "lowest");
        set_paging_time_span_spike_date_each_file(x, "", "fault", "lowest");
        set_paging_time_span_spike_time_each_file(x, "", "fault", "lowest");
        set_paging_time_span_spike_val_each_file(x, 0.00, "majflt", "spike");
        set_paging_time_span_spike_date_each_file(x, "", "majflt", "spike");
        set_paging_time_span_spike_time_each_file(x, "", "majflt", "spike");
        set_paging_time_span_spike_val_each_file(x, 0.00, "majflt", "highest");
        set_paging_time_span_spike_date_each_file(x, "", "majflt", "highest");
        set_paging_time_span_spike_time_each_file(x, "", "majflt", "highest");
        set_paging_time_span_spike_val_each_file(x, 19999999.00, "majflt", "lowest");
        set_paging_time_span_spike_date_each_file(x, "", "majflt", "lowest");
        set_paging_time_span_spike_time_each_file(x, "", "majflt", "lowest");
        set_paging_time_span_spike_val_each_file(x, 0.00, "vmeff", "spike");
        set_paging_time_span_spike_date_each_file(x, "", "vmeff", "spike");
        set_paging_time_span_spike_time_each_file(x, "", "vmeff", "spike");
        set_paging_time_span_spike_val_each_file(x, 0.00, "vmeff", "highest");
        set_paging_time_span_spike_date_each_file(x, "", "vmeff", "highest");
        set_paging_time_span_spike_time_each_file(x, "", "vmeff", "highest");
        set_paging_time_span_spike_val_each_file(x, 100.00, "vmeff", "lowest");
        set_paging_time_span_spike_date_each_file(x, "", "vmeff", "lowest");
        set_paging_time_span_spike_time_each_file(x, "", "vmeff", "lowest");

        set_io_transfer_rate_spike_val_each_file(x, 0.00, "tps", "spike");
        set_io_transfer_rate_spike_date_each_file(x, "", "tps", "spike");
        set_io_transfer_rate_spike_time_each_file(x, "", "tps", "spike");
        set_io_transfer_rate_spike_val_each_file(x, 0.00, "tps", "highest");
        set_io_transfer_rate_spike_date_each_file(x, "", "tps", "highest");
        set_io_transfer_rate_spike_time_each_file(x, "", "tps", "highest");
        set_io_transfer_rate_spike_val_each_file(x, 9999999.00, "tps", "lowest");
        set_io_transfer_rate_spike_date_each_file(x, "", "tps", "lowest");
        set_io_transfer_rate_spike_time_each_file(x, "", "tps", "lowest");
        set_io_transfer_rate_spike_val_each_file(x, 0.00, "bread", "spike");
        set_io_transfer_rate_spike_date_each_file(x, "", "bread", "spike");
        set_io_transfer_rate_spike_time_each_file(x, "", "bread", "spike");
        set_io_transfer_rate_spike_val_each_file(x, 0.00, "bread", "highest");
        set_io_transfer_rate_spike_date_each_file(x, "", "bread", "highest");
        set_io_transfer_rate_spike_time_each_file(x, "", "bread", "highest");
        set_io_transfer_rate_spike_val_each_file(x, 9999999.00, "bread", "lowest");
        set_io_transfer_rate_spike_date_each_file(x, "", "bread", "lowest");
        set_io_transfer_rate_spike_time_each_file(x, "", "bread", "lowest");
        set_io_transfer_rate_spike_val_each_file(x, 0.00, "bwrtn", "spike");
        set_io_transfer_rate_spike_date_each_file(x, "", "bwrtn", "spike");
        set_io_transfer_rate_spike_time_each_file(x, "", "bwrtn", "spike");
        set_io_transfer_rate_spike_val_each_file(x, 0.00, "bwrtn", "highest");
        set_io_transfer_rate_spike_date_each_file(x, "", "bwrtn", "highest");
        set_io_transfer_rate_spike_time_each_file(x, "", "bwrtn", "highest");
        set_io_transfer_rate_spike_val_each_file(x, 9999999.00, "bwrtn", "lowest");
        set_io_transfer_rate_spike_date_each_file(x, "", "bwrtn", "lowest");
        set_io_transfer_rate_spike_time_each_file(x, "", "bwrtn", "lowest");

        set_io_transfer_rate_time_span_spike_val_each_file(x, 0.00, "tps", "spike");
        set_io_transfer_rate_time_span_spike_date_each_file(x, "", "tps", "spike");
        set_io_transfer_rate_time_span_spike_time_each_file(x, "", "tps", "spike");
        set_io_transfer_rate_time_span_spike_val_each_file(x, 0.00, "tps", "highest");
        set_io_transfer_rate_time_span_spike_date_each_file(x, "", "tps", "highest");
        set_io_transfer_rate_time_span_spike_time_each_file(x, "", "tps", "highest");
        set_io_transfer_rate_time_span_spike_val_each_file(x, 9999999.00, "tps", "lowest");
        set_io_transfer_rate_time_span_spike_date_each_file(x, "", "tps", "lowest");
        set_io_transfer_rate_time_span_spike_time_each_file(x, "", "tps", "lowest");
        set_io_transfer_rate_time_span_spike_val_each_file(x, 0.00, "bread", "spike");
        set_io_transfer_rate_time_span_spike_date_each_file(x, "", "bread", "spike");
        set_io_transfer_rate_time_span_spike_time_each_file(x, "", "bread", "spike");
        set_io_transfer_rate_time_span_spike_val_each_file(x, 0.00, "bread", "highest");
        set_io_transfer_rate_time_span_spike_date_each_file(x, "", "bread", "highest");
        set_io_transfer_rate_time_span_spike_time_each_file(x, "", "bread", "highest");
        set_io_transfer_rate_time_span_spike_val_each_file(x, 9999999.00, "bread", "lowest");
        set_io_transfer_rate_time_span_spike_date_each_file(x, "", "bread", "lowest");
        set_io_transfer_rate_time_span_spike_time_each_file(x, "", "bread", "lowest");
        set_io_transfer_rate_time_span_spike_val_each_file(x, 0.00, "bwrtn", "spike");
        set_io_transfer_rate_time_span_spike_date_each_file(x, "", "bwrtn", "spike");
        set_io_transfer_rate_time_span_spike_time_each_file(x, "", "bwrtn", "spike");
        set_io_transfer_rate_time_span_spike_val_each_file(x, 0.00, "bwrtn", "highest");
        set_io_transfer_rate_time_span_spike_date_each_file(x, "", "bwrtn", "highest");
        set_io_transfer_rate_time_span_spike_time_each_file(x, "", "bwrtn", "highest");
        set_io_transfer_rate_time_span_spike_val_each_file(x, 9999999.00, "bwrtn", "lowest");
        set_io_transfer_rate_time_span_spike_date_each_file(x, "", "bwrtn", "lowest");
        set_io_transfer_rate_time_span_spike_time_each_file(x, "", "bwrtn", "lowest");

        set_memory_double_spike_val_each_file(x, 0.00, "memused", "spike");
        set_memory_spike_date_each_file(x, "", "memused", "spike");
        set_memory_spike_time_each_file(x, "", "memused", "spike");
        set_memory_double_spike_val_each_file(x, 0.00, "memused", "highest");
        set_memory_spike_date_each_file(x, "", "memused", "highest");
        set_memory_spike_time_each_file(x, "", "memused", "highest");
        set_memory_double_spike_val_each_file(x, 100.00, "memused", "lowest");
        set_memory_spike_date_each_file(x, "", "memused", "lowest");
        set_memory_spike_time_each_file(x, "", "memused", "lowest");
        set_memory_double_spike_val_each_file(x, 0.00, "commit", "spike");
        set_memory_spike_date_each_file(x, "", "commit", "spike");
        set_memory_spike_time_each_file(x, "", "commit", "spike");
        set_memory_double_spike_val_each_file(x, 0.00, "commit", "highest");
        set_memory_spike_date_each_file(x, "", "commit", "highest");
        set_memory_spike_time_each_file(x, "", "commit", "highest");
        set_memory_double_spike_val_each_file(x, 100.00, "commit", "lowest");
        set_memory_spike_date_each_file(x, "", "commit", "lowest");
        set_memory_spike_time_each_file(x, "", "commit", "lowest");

        set_memory_double_time_span_spike_val_each_file(x, 0.00, "memused", "spike");
        set_memory_time_span_spike_date_each_file(x, "", "memused", "spike");
        set_memory_time_span_spike_time_each_file(x, "", "memused", "spike");
        set_memory_double_time_span_spike_val_each_file(x, 0.00, "memused", "highest");
        set_memory_time_span_spike_date_each_file(x, "", "memused", "highest");
        set_memory_time_span_spike_time_each_file(x, "", "memused", "highest");
        set_memory_double_time_span_spike_val_each_file(x, 100.00, "memused", "lowest");
        set_memory_time_span_spike_date_each_file(x, "", "memused", "lowest");
        set_memory_time_span_spike_time_each_file(x, "", "memused", "lowest");
        set_memory_double_time_span_spike_val_each_file(x, 0.00, "commit", "spike");
        set_memory_time_span_spike_date_each_file(x, "", "commit", "spike");
        set_memory_time_span_spike_time_each_file(x, "", "commit", "spike");
        set_memory_double_time_span_spike_val_each_file(x, 0.00, "commit", "highest");
        set_memory_time_span_spike_date_each_file(x, "", "commit", "highest");
        set_memory_time_span_spike_time_each_file(x, "", "commit", "highest");
        set_memory_double_time_span_spike_val_each_file(x, 100.00, "commit", "lowest");
        set_memory_time_span_spike_date_each_file(x, "", "commit", "lowest");
        set_memory_time_span_spike_time_each_file(x, "", "commit", "lowest");

        set_memory_int_spike_val_each_file(x, 0.00, "kbcommit", "spike");
        set_memory_spike_date_each_file(x, "", "kbcommit", "spike");
        set_memory_spike_time_each_file(x, "", "kbcommit", "spike");
        set_memory_int_spike_val_each_file(x, 0.00, "kbcommit", "highest");
        set_memory_spike_date_each_file(x, "", "kbcommit", "highest");
        set_memory_spike_time_each_file(x, "", "kbcommit", "highest");
        set_memory_int_spike_val_each_file(x, 199999999.00, "kbcommit", "lowest");
        set_memory_spike_date_each_file(x, "", "kbcommit", "lowest");
        set_memory_spike_time_each_file(x, "", "kbcommit", "lowest");

        set_memory_int_time_span_spike_val_each_file(x, 0.00, "kbcommit", "spike");
        set_memory_time_span_spike_date_each_file(x, "", "kbcommit", "spike");
        set_memory_time_span_spike_time_each_file(x, "", "kbcommit", "spike");
        set_memory_int_time_span_spike_val_each_file(x, 0.00, "kbcommit", "highest");
        set_memory_time_span_spike_date_each_file(x, "", "kbcommit", "highest");
        set_memory_time_span_spike_time_each_file(x, "", "kbcommit", "highest");
        set_memory_int_time_span_spike_val_each_file(x, 199999999.00, "kbcommit", "lowest");
        set_memory_time_span_spike_date_each_file(x, "", "kbcommit", "lowest");
        set_memory_time_span_spike_time_each_file(x, "", "kbcommit", "lowest");

        set_swpused_spike_val_each_file(x, 0.00, "spike");
        set_swpused_spike_date_each_file(x, "", "spike");
        set_swpused_spike_time_each_file(x, "", "spike");
        set_swpused_spike_val_each_file(x, 0.00, "highest");
        set_swpused_spike_date_each_file(x, "", "highest");
        set_swpused_spike_time_each_file(x, "", "highest");
        set_swpused_spike_val_each_file(x, 100.00, "lowest");
        set_swpused_spike_date_each_file(x, "", "lowest");
        set_swpused_spike_time_each_file(x, "", "lowest");

        set_swpused_time_span_spike_val_each_file(x, 0.00, "spike");
        set_swpused_time_span_spike_date_each_file(x, "", "spike");
        set_swpused_time_span_spike_time_each_file(x, "", "spike");
        set_swpused_time_span_spike_val_each_file(x, 0.00, "highest");
        set_swpused_time_span_spike_date_each_file(x, "", "highest");
        set_swpused_time_span_spike_time_each_file(x, "", "highest");
        set_swpused_time_span_spike_val_each_file(x, 100.00, "lowest");
        set_swpused_time_span_spike_date_each_file(x, "", "lowest");
        set_swpused_time_span_spike_time_each_file(x, "", "lowest");

        set_kernel_table_spike_val_each_file(x, 0.00, "dentunusd", "spike");
        set_kernel_table_spike_date_each_file(x, "", "dentunusd", "spike");
        set_kernel_table_spike_time_each_file(x, "", "dentunusd", "spike");
        set_kernel_table_spike_val_each_file(x, 0.00, "dentunusd", "highest");
        set_kernel_table_spike_date_each_file(x, "", "dentunusd", "highest");
        set_kernel_table_spike_time_each_file(x, "", "dentunusd", "highest");
        set_kernel_table_spike_val_each_file(x, 9999999.00, "dentunusd", "lowest");
        set_kernel_table_spike_date_each_file(x, "", "dentunusd", "lowest");
        set_kernel_table_spike_time_each_file(x, "", "dentunusd", "lowest");
        set_kernel_table_spike_val_each_file(x, 0.00, "file", "spike");
        set_kernel_table_spike_date_each_file(x, "", "file", "spike");
        set_kernel_table_spike_time_each_file(x, "", "file", "spike");
        set_kernel_table_spike_val_each_file(x, 0.00, "file", "highest");
        set_kernel_table_spike_date_each_file(x, "", "file", "highest");
        set_kernel_table_spike_time_each_file(x, "", "file", "highest");
        set_kernel_table_spike_val_each_file(x, 9999999.00, "file", "lowest");
        set_kernel_table_spike_date_each_file(x, "", "file", "lowest");
        set_kernel_table_spike_time_each_file(x, "", "file", "lowest");
        set_kernel_table_spike_val_each_file(x, 0.00, "inode", "spike");
        set_kernel_table_spike_date_each_file(x, "", "inode", "spike");
        set_kernel_table_spike_time_each_file(x, "", "inode", "spike");
        set_kernel_table_spike_val_each_file(x, 0.00, "inode", "highest");
        set_kernel_table_spike_date_each_file(x, "", "inode", "highest");
        set_kernel_table_spike_time_each_file(x, "", "inode", "highest");
        set_kernel_table_spike_val_each_file(x, 9999999.00, "inode", "lowest");
        set_kernel_table_spike_date_each_file(x, "", "inode", "lowest");
        set_kernel_table_spike_time_each_file(x, "", "inode", "lowest");

        set_kernel_table_time_span_spike_val_each_file(x, 0.00, "dentunusd", "spike");
        set_kernel_table_time_span_spike_date_each_file(x, "", "dentunusd", "spike");
        set_kernel_table_time_span_spike_time_each_file(x, "", "dentunusd", "spike");
        set_kernel_table_time_span_spike_val_each_file(x, 0.00, "dentunusd", "highest");
        set_kernel_table_time_span_spike_date_each_file(x, "", "dentunusd", "highest");
        set_kernel_table_time_span_spike_time_each_file(x, "", "dentunusd", "highest");
        set_kernel_table_time_span_spike_val_each_file(x, 9999999.00, "dentunusd", "lowest");
        set_kernel_table_time_span_spike_date_each_file(x, "", "dentunusd", "lowest");
        set_kernel_table_time_span_spike_time_each_file(x, "", "dentunusd", "lowest");
        set_kernel_table_time_span_spike_val_each_file(x, 0.00, "file", "spike");
        set_kernel_table_time_span_spike_date_each_file(x, "", "file", "spike");
        set_kernel_table_time_span_spike_time_each_file(x, "", "file", "spike");
        set_kernel_table_time_span_spike_val_each_file(x, 0.00, "file", "highest");
        set_kernel_table_time_span_spike_date_each_file(x, "", "file", "highest");
        set_kernel_table_time_span_spike_time_each_file(x, "", "file", "highest");
        set_kernel_table_time_span_spike_val_each_file(x, 9999999.00, "file", "lowest");
        set_kernel_table_time_span_spike_date_each_file(x, "", "file", "lowest");
        set_kernel_table_time_span_spike_time_each_file(x, "", "file", "lowest");
        set_kernel_table_time_span_spike_val_each_file(x, 0.00, "inode", "spike");
        set_kernel_table_time_span_spike_date_each_file(x, "", "inode", "spike");
        set_kernel_table_time_span_spike_time_each_file(x, "", "inode", "spike");
        set_kernel_table_time_span_spike_val_each_file(x, 0.00, "inode", "highest");
        set_kernel_table_time_span_spike_date_each_file(x, "", "inode", "highest");
        set_kernel_table_time_span_spike_time_each_file(x, "", "inode", "highest");
        set_kernel_table_time_span_spike_val_each_file(x, 9999999.00, "inode", "lowest");
        set_kernel_table_time_span_spike_date_each_file(x, "", "inode", "lowest");
        set_kernel_table_time_span_spike_time_each_file(x, "", "inode", "lowest");

        set_ldavg_int_spike_val_each_file(x, 0, "runq_sz", "spike");
        set_ldavg_spike_date_each_file(x, "", "runq_sz", "spike");
        set_ldavg_spike_time_each_file(x, "", "runq_sz", "spike");
        set_ldavg_int_spike_val_each_file(x, 0, "runq_sz", "highest");
        set_ldavg_spike_date_each_file(x, "", "runq_sz", "highest");
        set_ldavg_spike_time_each_file(x, "", "runq_sz", "highest");
        set_ldavg_int_spike_val_each_file(x, 9999999, "runq_sz", "lowest");
        set_ldavg_spike_date_each_file(x, "", "runq_sz", "lowest");
        set_ldavg_spike_time_each_file(x, "", "runq_sz", "lowest");
        set_ldavg_int_spike_val_each_file(x, 0, "plist_sz", "spike");
        set_ldavg_spike_date_each_file(x, "", "plist_sz", "spike");
        set_ldavg_spike_time_each_file(x, "", "plist_sz", "spike");
        set_ldavg_int_spike_val_each_file(x, 0, "plist_sz", "highest");
        set_ldavg_spike_date_each_file(x, "", "plist_sz", "highest");
        set_ldavg_spike_time_each_file(x, "", "plist_sz", "highest");
        set_ldavg_int_spike_val_each_file(x, 9999999, "plist_sz", "lowest");
        set_ldavg_spike_date_each_file(x, "", "plist_sz", "lowest");
        set_ldavg_spike_time_each_file(x, "", "plist_sz", "lowest");

        set_ldavg_int_time_span_spike_val_each_file(x, 0, "runq_sz", "spike");
        set_ldavg_time_span_spike_date_each_file(x, "", "runq_sz", "spike");
        set_ldavg_time_span_spike_time_each_file(x, "", "runq_sz", "spike");
        set_ldavg_int_time_span_spike_val_each_file(x, 0, "runq_sz", "highest");
        set_ldavg_time_span_spike_date_each_file(x, "", "runq_sz", "highest");
        set_ldavg_time_span_spike_time_each_file(x, "", "runq_sz", "highest");
        set_ldavg_int_time_span_spike_val_each_file(x, 9999999, "runq_sz", "lowest");
        set_ldavg_time_span_spike_date_each_file(x, "", "runq_sz", "lowest");
        set_ldavg_time_span_spike_time_each_file(x, "", "runq_sz", "lowest");
        set_ldavg_int_time_span_spike_val_each_file(x, 0, "plist_sz", "spike");
        set_ldavg_time_span_spike_date_each_file(x, "", "plist_sz", "spike");
        set_ldavg_time_span_spike_time_each_file(x, "", "plist_sz", "spike");
        set_ldavg_int_time_span_spike_val_each_file(x, 0, "plist_sz", "highest");
        set_ldavg_time_span_spike_date_each_file(x, "", "plist_sz", "highest");
        set_ldavg_time_span_spike_time_each_file(x, "", "plist_sz", "highest");
        set_ldavg_int_time_span_spike_val_each_file(x, 9999999, "plist_sz", "lowest");
        set_ldavg_time_span_spike_date_each_file(x, "", "plist_sz", "lowest");
        set_ldavg_time_span_spike_time_each_file(x, "", "plist_sz", "lowest");

        set_ldavg_double_spike_val_each_file(x, 0.00, "ldavg_one", "spike");
        set_ldavg_spike_date_each_file(x, "", "ldavg_one", "spike");
        set_ldavg_spike_time_each_file(x, "", "ldavg_one", "spike");
        set_ldavg_double_spike_val_each_file(x, 0.00, "ldavg_one", "highest");
        set_ldavg_spike_date_each_file(x, "", "ldavg_one", "highest");
        set_ldavg_spike_time_each_file(x, "", "ldavg_one", "highest");
        set_ldavg_double_spike_val_each_file(x, 9999999.00, "ldavg_one", "lowest");
        set_ldavg_spike_date_each_file(x, "", "ldavg_one", "lowest");
        set_ldavg_spike_time_each_file(x, "", "ldavg_one", "lowest");
        set_ldavg_double_spike_val_each_file(x, 0.00, "ldavg_five", "spike");
        set_ldavg_spike_date_each_file(x, "", "ldavg_five", "spike");
        set_ldavg_spike_time_each_file(x, "", "ldavg_five", "spike");
        set_ldavg_double_spike_val_each_file(x, 0.00, "ldavg_five", "highest");
        set_ldavg_spike_date_each_file(x, "", "ldavg_five", "highest");
        set_ldavg_spike_time_each_file(x, "", "ldavg_five", "highest");
        set_ldavg_double_spike_val_each_file(x, 9999999.00, "ldavg_five", "lowest");
        set_ldavg_spike_date_each_file(x, "", "ldavg_five", "lowest");
        set_ldavg_spike_time_each_file(x, "", "ldavg_five", "lowest");
        set_ldavg_double_spike_val_each_file(x, 0.00, "ldavg_15", "spike");
        set_ldavg_spike_date_each_file(x, "", "ldavg_15", "spike");
        set_ldavg_spike_time_each_file(x, "", "ldavg_15", "spike");
        set_ldavg_double_spike_val_each_file(x, 0.00, "ldavg_15", "highest");
        set_ldavg_spike_date_each_file(x, "", "ldavg_15", "highest");
        set_ldavg_spike_time_each_file(x, "", "ldavg_15", "highest");
        set_ldavg_double_spike_val_each_file(x, 9999999.00, "ldavg_15", "lowest");
        set_ldavg_spike_date_each_file(x, "", "ldavg_15", "lowest");
        set_ldavg_spike_time_each_file(x, "", "ldavg_15", "lowest");

        set_ldavg_double_time_span_spike_val_each_file(x, 0.00, "ldavg_one", "spike");
        set_ldavg_time_span_spike_date_each_file(x, "", "ldavg_one", "spike");
        set_ldavg_time_span_spike_time_each_file(x, "", "ldavg_one", "spike");
        set_ldavg_double_time_span_spike_val_each_file(x, 0.00, "ldavg_one", "highest");
        set_ldavg_time_span_spike_date_each_file(x, "", "ldavg_one", "highest");
        set_ldavg_time_span_spike_time_each_file(x, "", "ldavg_one", "highest");
        set_ldavg_double_time_span_spike_val_each_file(x, 9999999.00, "ldavg_one", "lowest");
        set_ldavg_time_span_spike_date_each_file(x, "", "ldavg_one", "lowest");
        set_ldavg_time_span_spike_time_each_file(x, "", "ldavg_one", "lowest");
        set_ldavg_double_time_span_spike_val_each_file(x, 0.00, "ldavg_five", "spike");
        set_ldavg_time_span_spike_date_each_file(x, "", "ldavg_five", "spike");
        set_ldavg_time_span_spike_time_each_file(x, "", "ldavg_five", "spike");
        set_ldavg_double_time_span_spike_val_each_file(x, 0.00, "ldavg_five", "highest");
        set_ldavg_time_span_spike_date_each_file(x, "", "ldavg_five", "highest");
        set_ldavg_time_span_spike_time_each_file(x, "", "ldavg_five", "highest");
        set_ldavg_double_time_span_spike_val_each_file(x, 9999999.00, "ldavg_five", "lowest");
        set_ldavg_time_span_spike_date_each_file(x, "", "ldavg_five", "lowest");
        set_ldavg_time_span_spike_time_each_file(x, "", "ldavg_five", "lowest");
        set_ldavg_double_time_span_spike_val_each_file(x, 0.00, "ldavg_15", "spike");
        set_ldavg_time_span_spike_date_each_file(x, "", "ldavg_15", "spike");
        set_ldavg_time_span_spike_time_each_file(x, "", "ldavg_15", "spike");
        set_ldavg_double_time_span_spike_val_each_file(x, 0.00, "ldavg_15", "highest");
        set_ldavg_time_span_spike_date_each_file(x, "", "ldavg_15", "highest");
        set_ldavg_time_span_spike_time_each_file(x, "", "ldavg_15", "highest");
        set_ldavg_double_time_span_spike_val_each_file(x, 9999999.00, "ldavg_15", "lowest");
        set_ldavg_time_span_spike_date_each_file(x, "", "ldavg_15", "lowest");
        set_ldavg_time_span_spike_time_each_file(x, "", "ldavg_15", "lowest");

        for (i = 0; i < MAX_BLOCK_DEVICE_NUMBERS; i++) {
            set_block_device_spike_val_each_file(x, 0.00, i, "areqsz", "spike");
            set_block_device_spike_date_each_file(x, "", i, "areqsz", "spike");
            set_block_device_spike_time_each_file(x, "", i, "areqsz", "spike");
            set_block_device_spike_val_each_file(x, 0.00, i, "areqsz", "highest");
            set_block_device_spike_date_each_file(x, "", i, "areqsz", "highest");
            set_block_device_spike_time_each_file(x, "", i, "areqsz", "highest");
            set_block_device_spike_val_each_file(x, 9999999.00, i, "areqsz", "lowest");
            set_block_device_spike_date_each_file(x, "", i, "areqsz", "lowest");
            set_block_device_spike_time_each_file(x, "", i, "areqsz", "lowest");
            set_block_device_spike_val_each_file(x, 0.00, i, "util", "spike");
            set_block_device_spike_date_each_file(x, "", i, "util", "spike");
            set_block_device_spike_time_each_file(x, "", i, "util", "spike");
            set_block_device_spike_val_each_file(x, 0.00, i, "util", "highest");
            set_block_device_spike_date_each_file(x, "", i, "util", "highest");
            set_block_device_spike_time_each_file(x, "", i, "util", "highest");
            set_block_device_spike_val_each_file(x, 100.00, i, "util", "lowest");
            set_block_device_spike_date_each_file(x, "", i, "util", "lowest");
            set_block_device_spike_time_each_file(x, "", i, "util", "lowest");

            set_block_device_time_span_spike_val_each_file(x, 0.00, i, "areqsz", "spike");
            set_block_device_time_span_spike_date_each_file(x, "", i, "areqsz", "spike");
            set_block_device_time_span_spike_time_each_file(x, "", i, "areqsz", "spike");
            set_block_device_time_span_spike_val_each_file(x, 0.00, i, "areqsz", "highest");
            set_block_device_time_span_spike_date_each_file(x, "", i, "areqsz", "highest");
            set_block_device_time_span_spike_time_each_file(x, "", i, "areqsz", "highest");
            set_block_device_time_span_spike_val_each_file(x, 9999999.00, i, "areqsz", "lowest");
            set_block_device_time_span_spike_date_each_file(x, "", i, "areqsz", "lowest");
            set_block_device_time_span_spike_time_each_file(x, "", i, "areqsz", "lowest");
            set_block_device_time_span_spike_val_each_file(x, 0.00, i, "util", "spike");
            set_block_device_time_span_spike_date_each_file(x, "", i, "util", "spike");
            set_block_device_time_span_spike_time_each_file(x, "", i, "util", "spike");
            set_block_device_time_span_spike_val_each_file(x, 0.00, i, "util", "highest");
            set_block_device_time_span_spike_date_each_file(x, "", i, "util", "highest");
            set_block_device_time_span_spike_time_each_file(x, "", i, "util", "highest");
            set_block_device_time_span_spike_val_each_file(x, 100.00, i, "util", "lowest");
            set_block_device_time_span_spike_date_each_file(x, "", i, "util", "lowest");
            set_block_device_time_span_spike_time_each_file(x, "", i, "util", "lowest");
        }

        for (i = 0; i < MAX_NETWORK_DEVICE_NUMBERS; i++) {
            set_network_spike_val_each_file(x, 0.00, i, "rxpck", "spike");
            set_network_spike_date_each_file(x, "", i, "rxpck", "spike");
            set_network_spike_time_each_file(x, "", i, "rxpck", "spike");
            set_network_spike_val_each_file(x, 0.00, i, "rxpck", "highest");
            set_network_spike_date_each_file(x, "", i, "rxpck", "highest");
            set_network_spike_time_each_file(x, "", i, "rxpck", "highest");
            set_network_spike_val_each_file(x, 19999999.00, i, "rxpck", "lowest");
            set_network_spike_date_each_file(x, "", i, "rxpck", "lowest");
            set_network_spike_time_each_file(x, "", i, "rxpck", "lowest");
            set_network_spike_val_each_file(x, 0.00, i, "txpck", "spike");
            set_network_spike_date_each_file(x, "", i, "txpck", "spike");
            set_network_spike_time_each_file(x, "", i, "txpck", "spike");
            set_network_spike_val_each_file(x, 0.00, i, "txpck", "highest");
            set_network_spike_date_each_file(x, "", i, "txpck", "highest");
            set_network_spike_time_each_file(x, "", i, "txpck", "highest");
            set_network_spike_val_each_file(x, 19999999.00, i, "txpck", "lowest");
            set_network_spike_date_each_file(x, "", i, "txpck", "lowest");
            set_network_spike_time_each_file(x, "", i, "txpck", "lowest");
            set_network_spike_val_each_file(x, 0.00, i, "rxkb", "spike");
            set_network_spike_date_each_file(x, "", i, "rxkb", "spike");
            set_network_spike_time_each_file(x, "", i, "rxkb", "spike");
            set_network_spike_val_each_file(x, 0.00, i, "rxkb", "highest");
            set_network_spike_date_each_file(x, "", i, "rxkb", "highest");
            set_network_spike_time_each_file(x, "", i, "rxkb", "highest");
            set_network_spike_val_each_file(x, 19999999.00, i, "rxkb", "lowest");
            set_network_spike_date_each_file(x, "", i, "rxkb", "lowest");
            set_network_spike_time_each_file(x, "", i, "rxkb", "lowest");
            set_network_spike_val_each_file(x, 0.00, i, "txkb", "spike");
            set_network_spike_date_each_file(x, "", i, "txkb", "spike");
            set_network_spike_time_each_file(x, "", i, "txkb", "spike");
            set_network_spike_val_each_file(x, 0.00, i, "txkb", "highest");
            set_network_spike_date_each_file(x, "", i, "txkb", "highest");
            set_network_spike_time_each_file(x, "", i, "txkb", "highest");
            set_network_spike_val_each_file(x, 19999999.00, i, "txkb", "lowest");
            set_network_spike_date_each_file(x, "", i, "txkb", "lowest");
            set_network_spike_time_each_file(x, "", i, "txkb", "lowest");
            set_network_spike_val_each_file(x, 0.00, i, "rxerr", "spike");
            set_network_spike_date_each_file(x, "", i, "rxerr", "spike");
            set_network_spike_time_each_file(x, "", i, "rxerr", "spike");
            set_network_spike_val_each_file(x, 0.00, i, "rxerr", "highest");
            set_network_spike_date_each_file(x, "", i, "rxerr", "highest");
            set_network_spike_time_each_file(x, "", i, "rxerr", "highest");
            set_network_spike_val_each_file(x, 19999999.00, i, "rxerr", "lowest");
            set_network_spike_date_each_file(x, "", i, "rxerr", "lowest");
            set_network_spike_time_each_file(x, "", i, "rxerr", "lowest");
            set_network_spike_val_each_file(x, 0.00, i, "txerr", "spike");
            set_network_spike_date_each_file(x, "", i, "txerr", "spike");
            set_network_spike_time_each_file(x, "", i, "txerr", "spike");
            set_network_spike_val_each_file(x, 0.00, i, "txerr", "highest");
            set_network_spike_date_each_file(x, "", i, "txerr", "highest");
            set_network_spike_time_each_file(x, "", i, "txerr", "highest");
            set_network_spike_val_each_file(x, 19999999.00, i, "txerr", "lowest");
            set_network_spike_date_each_file(x, "", i, "txerr", "lowest");
            set_network_spike_time_each_file(x, "", i, "txerr", "lowest");
            set_network_spike_val_each_file(x, 0.00, i, "rxdrop", "spike");
            set_network_spike_date_each_file(x, "", i, "rxdrop", "spike");
            set_network_spike_time_each_file(x, "", i, "rxdrop", "spike");
            set_network_spike_val_each_file(x, 0.00, i, "rxdrop", "highest");
            set_network_spike_date_each_file(x, "", i, "rxdrop", "highest");
            set_network_spike_time_each_file(x, "", i, "rxdrop", "highest");
            set_network_spike_val_each_file(x, 19999999.00, i, "rxdrop", "lowest");
            set_network_spike_date_each_file(x, "", i, "rxdrop", "lowest");
            set_network_spike_time_each_file(x, "", i, "rxdrop", "lowest");
            set_network_spike_val_each_file(x, 0.00, i, "txdrop", "spike");
            set_network_spike_date_each_file(x, "", i, "txdrop", "spike");
            set_network_spike_time_each_file(x, "", i, "txdrop", "spike");
            set_network_spike_val_each_file(x, 0.00, i, "txdrop", "highest");
            set_network_spike_date_each_file(x, "", i, "txdrop", "highest");
            set_network_spike_time_each_file(x, "", i, "txdrop", "highest");
            set_network_spike_val_each_file(x, 19999999.00, i, "txdrop", "lowest");
            set_network_spike_date_each_file(x, "", i, "txdrop", "lowest");
            set_network_spike_time_each_file(x, "", i, "txdrop", "lowest");

            set_network_former_val_each_file(x, 0.00, i, "rxerr");
            set_network_former_val_each_file(x, 0.00, i, "txerr");
            set_network_former_val_each_file(x, 0.00, i, "rxdrop");
            set_network_former_val_each_file(x, 0.00, i, "txdrop");
        }
    }

    /* ---- spike and former---- */

    /* CPU all, 0 to MAX_CORE_NUMBERS */
    for (i = 0; i <= MAX_CORE_NUMBERS; i++) {
        set_cpu_spike_val(0.00, i, "usr");
        set_cpu_former_val(0.00, i, "usr");
        set_cpu_spike_val(0.00, i, "sys");
        set_cpu_former_val(0.00, i, "sys");
        set_cpu_spike_val(0.00, i, "iowait");
        set_cpu_former_val(0.00, i, "iowait");
        set_cpu_spike_val(0.00, i, "idle");
        set_cpu_former_val(0.00, i, "idle");
    }

    set_tasks_spike_val(0.00, "proc");
    set_tasks_former_val(0.00, "proc");
    set_tasks_spike_val(0.00, "cswch");
    set_tasks_former_val(0.00, "cswch");
    set_pswap_spike_val(0.00, "pswpin");
    set_pswap_former_val(0.00, "pswpin");
    set_pswap_spike_val(0.00, "pswpout");
    set_pswap_former_val(0.00, "pswpout");
    set_paging_spike_val(0.00, "pgpgin");
    set_paging_former_val(0.00, "pgpgin");
    set_paging_spike_val(0.00, "pgpgout");
    set_paging_former_val(0.00, "pgpgout");
    set_paging_spike_val(0.00, "fault");
    set_paging_former_val(0.00, "fault");
    set_paging_spike_val(0.00, "majflt");
    set_paging_former_val(0.00, "majflt");
    set_paging_spike_val(0.00, "vmeff");
    set_paging_former_val(0.00, "vmeff");
    set_io_transfer_rate_spike_val(0.00, "tps");
    set_io_transfer_rate_former_val(0.00, "tps");
    set_io_transfer_rate_spike_val(0.00, "bread");
    set_io_transfer_rate_former_val(0.00, "bread");
    set_io_transfer_rate_spike_val(0.00, "bwrtn");
    set_io_transfer_rate_former_val(0.00, "bwrtn");
    set_memory_double_spike_val(0.00, "memused");
    set_memory_double_former_val(0.00, "memused");
    set_memory_double_spike_val(0.00, "commit");
    set_memory_double_former_val(0.00, "commit");
    set_memory_int_spike_val(0, "kbcommit");
    set_memory_int_former_val(0, "kbcommit");
    set_swpused_spike_val(0.00);
    set_swpused_former_val(0.00);
    set_kernel_table_spike_val(0, "dentunusd");
    set_kernel_table_former_val(0, "dentunusd");
    set_kernel_table_spike_val(0, "file");
    set_kernel_table_former_val(0, "file");
    set_kernel_table_spike_val(0, "inode");
    set_kernel_table_former_val(0, "inode");

    set_ldavg_int_spike_val(0, "runq_sz");
    set_ldavg_int_former_val(0, "runq_sz");
    set_ldavg_int_spike_val(0, "plist_sz");
    set_ldavg_int_former_val(0, "plist_sz");
    set_ldavg_double_spike_val(0.00, "ldavg_one");
    set_ldavg_double_former_val(0.00, "ldavg_one");
    set_ldavg_double_spike_val(0.00, "ldavg_five");
    set_ldavg_double_former_val(0.00, "ldavg_five");
    set_ldavg_double_spike_val(0.00, "ldavg_15");
    set_ldavg_double_former_val(0.00, "ldavg_15");

    /* up to MAX_DEVICE_NUMBERS */
    for (i = 0; i < MAX_BLOCK_DEVICE_NUMBERS; i++) {
        set_block_device_spike_val(0.00, i, "areqsz");
        set_block_device_former_val(0.00, i, "areqsz");
        set_block_device_spike_val(0.00, i, "util");
        set_block_device_former_val(0.00, i, "util");
    }

    /* up to MAX_NETWORK_DEVICE_NUMBERS */
    for (i = 0; i < MAX_NETWORK_DEVICE_NUMBERS; i++) {
        set_network_spike_val(0.00, i, "rxpck");
        set_network_former_val(0.00, i, "rxpck");
        set_network_spike_val(0.00, i, "txpck");
        set_network_former_val(0.00, i, "txpck");
        set_network_spike_val(0.00, i, "rxkb");
        set_network_former_val(0.00, i, "rxkb");
        set_network_spike_val(0.00, i, "txkb");
        set_network_former_val(0.00, i, "txkb");
        set_network_spike_val(0.00, i, "rxerr");
        set_network_former_val(0.00, i, "rxerr");
        set_network_spike_val(0.00, i, "txerr");
        set_network_former_val(0.00, i, "txerr");
        set_network_spike_val(0.00, i, "rxdrop");
        set_network_former_val(0.00, i, "rxdrop");
        set_network_spike_val(0.00, i, "txdrop");
        set_network_former_val(0.00, i, "txdrop");
    }

    /* ---- All highest ---- */

    /* CPU all, 0 to MAX_CORE_NUMBERS */
    for (i = 0; i <= MAX_CORE_NUMBERS; i++) {
        set_cpu_highest_val(0.00, i, "usr");
        set_cpu_highest_val(0.00, i, "sys");
        set_cpu_highest_val(0.00, i, "iowait");
        set_cpu_highest_val(0.00, i, "idle");
    }

    set_tasks_highest_val(0.00, "proc");
    set_tasks_highest_val(0.00, "cswch");
    set_pswap_highest_val(0, "pswpin");
    set_pswap_highest_val(0, "pswpout");
    set_paging_highest_val(0.00, "pgpgin");
    set_paging_highest_val(0.00, "pgpgout");
    set_paging_highest_val(0.00, "fault");
    set_paging_highest_val(0.00, "majflt");
    set_paging_highest_val(0.00, "vmeff");
    set_io_transfer_rate_highest_val(0.00, "tps");
    set_io_transfer_rate_highest_val(0.00, "bread");
    set_io_transfer_rate_highest_val(0.00, "bwrtn");
    set_memory_double_highest_val(0.00, "memused");
    set_memory_double_highest_val(0.00, "commit");
    set_memory_int_highest_val(0, "kbcommit");
    set_swpused_highest_val(0.00);
    set_kernel_table_highest_val(0, "dentunusd");
    set_kernel_table_highest_val(0, "file");
    set_kernel_table_highest_val(0, "inode");

    set_ldavg_int_highest_val(0, "runq_sz");
    set_ldavg_int_highest_val(0, "plist_sz");
    set_ldavg_double_highest_val(0.00, "ldavg_one");
    set_ldavg_double_highest_val(0.00, "ldavg_five");
    set_ldavg_double_highest_val(0.00, "ldavg_15");

    /* up to MAX_DEVICE_NUMBERS */
    for (i = 0; i < MAX_BLOCK_DEVICE_NUMBERS; i++) {
        set_block_device_highest_val (-0.01, i, "areqsz");
        set_block_device_highest_val (-0.01, i, "util");
    }

    /* up to MAX_NETWORK_DEVICE_NUMBERS */
    for (i = 0; i < MAX_NETWORK_DEVICE_NUMBERS; i++) {
        set_network_highest_val(0.00, i, "rxpck");
        set_network_highest_val(0.00, i, "txpck");
        set_network_highest_val(0.00, i, "rxkb");
        set_network_highest_val(0.00, i, "txkb");
        set_network_highest_val(0.00, i, "rxerr");
        set_network_highest_val(0.00, i, "txerr");
        set_network_highest_val(0.00, i, "rxdrop");
        set_network_highest_val(0.00, i, "txdrop");
    }

    /* these values should be big enough for the comparison */

    /* ---- Averages lowest ---- */

    /* CPU all, 0 to MAX_CORE_NUMBERS */
    for (i = 0; i <= MAX_CORE_NUMBERS; i++) {
        set_cpu_avg_lowest_val(100.01, i, "usr");
        set_cpu_avg_lowest_val(100.01, i, "sys");
        set_cpu_avg_lowest_val(100.01, i, "iowait");
        set_cpu_avg_lowest_val(100.01, i, "idle");
    }

    set_tasks_avg_lowest_val(9999999999.99, "proc");
    set_tasks_avg_lowest_val(9999999999.99, "cswch");
    set_pswap_avg_lowest_val(999999999, "pswpin");
    set_pswap_avg_lowest_val(999999999, "pswpout");
    set_paging_avg_lowest_val(9999999999.99, "pgpgin");
    set_paging_avg_lowest_val(9999999999.99, "pgpgout");
    set_paging_avg_lowest_val(9999999999.99, "fault");
    set_paging_avg_lowest_val(9999999999.99, "majflt");
    set_paging_avg_lowest_val(100.01, "vmeff");
    set_io_transfer_rate_avg_lowest_val(9999999999.99, "tps");
    set_io_transfer_rate_avg_lowest_val(9999999999.99, "bread");
    set_io_transfer_rate_avg_lowest_val(9999999999.99, "bwrtn");
    set_memory_double_avg_lowest_val(100.01, "memused");
    set_memory_double_avg_lowest_val(10000.01, "commit");
    set_memory_int_avg_lowest_val(999999999, "kbcommit");
    set_swpused_avg_lowest_val(100.01);
    set_kernel_table_avg_lowest_val(999999999, "dentunusd");
    set_kernel_table_avg_lowest_val(999999999, "file");
    set_kernel_table_avg_lowest_val(999999999, "inode");
    set_ldavg_int_avg_lowest_val(999999999, "runq_sz");
    set_ldavg_int_avg_lowest_val(999999999, "plist_sz");
    set_ldavg_double_avg_lowest_val(9999999999.99, "ldavg_one");
    set_ldavg_double_avg_lowest_val(9999999999.99, "ldavg_five");
    set_ldavg_double_avg_lowest_val(9999999999.99, "ldavg_15");

    /* up to MAX_BLOCK_DEVICE_NUMBERS */
    for (i = 0; i < MAX_BLOCK_DEVICE_NUMBERS; i++) {
        set_block_device_avg_lowest_val(9999999999.99, i, "areqsz");
        set_block_device_avg_lowest_val(9999999999.99, i, "util");
    }

    /* up to MAX_NETWORK_DEVICE_NUMBERS */
    for (i = 0; i < MAX_NETWORK_DEVICE_NUMBERS; i++) {
        set_network_avg_lowest_val(999999999.99, i, "rxpck");
        set_network_avg_lowest_val(999999999.99, i, "txpck");
        set_network_avg_lowest_val(999999999.99, i, "rxkb");
        set_network_avg_lowest_val(999999999.99, i, "txkb");
        set_network_avg_lowest_val(999999999.99, i, "rxerr");
        set_network_avg_lowest_val(999999999.99, i, "txerr");
        set_network_avg_lowest_val(999999999.99, i, "rxdrop");
        set_network_avg_lowest_val(999999999.99, i, "txdrop");
    }

    /* ---- All lowest ---- */

    /* CPU all, 0 to MAX_CORE_NUMBERS */
    for (i = 0; i <= MAX_CORE_NUMBERS; i++) {
        set_cpu_lowest_val(100.01, i, "usr");
        set_cpu_lowest_val(100.01, i, "sys");
        set_cpu_lowest_val(100.01, i, "iowait");
        set_cpu_lowest_val(100.01, i, "idle");
    }

    set_tasks_lowest_val(9999999999.99, "proc");
    set_tasks_lowest_val(9999999999.99, "cswch");
    set_pswap_lowest_val(999999999, "pswpin");
    set_pswap_lowest_val(999999999, "pswpout");
    set_paging_lowest_val(9999999999.99, "pgpgin");
    set_paging_lowest_val(9999999999.99, "pgpgout");
    set_paging_lowest_val(9999999999.99, "fault");
    set_paging_lowest_val(9999999999.99, "majflt");
    set_paging_lowest_val(100.01, "vmeff");
    set_io_transfer_rate_lowest_val(9999999999.99, "tps");
    set_io_transfer_rate_lowest_val(9999999999.99, "bread");
    set_io_transfer_rate_lowest_val(9999999999.99, "bwrtn");
    set_memory_double_lowest_val(100.01, "memused");
    set_memory_double_lowest_val(10000.01, "commit");
    set_memory_int_lowest_val(999999999, "kbcommit");
    set_swpused_lowest_val(100.01);
    set_kernel_table_lowest_val(999999999, "dentunusd");
    set_kernel_table_lowest_val(999999999, "file");
    set_kernel_table_lowest_val(999999999, "inode");
    set_ldavg_int_lowest_val(999999999, "runq_sz");
    set_ldavg_int_lowest_val(999999999, "plist_sz");
    set_ldavg_double_lowest_val(9999999999.99, "ldavg_one");
    set_ldavg_double_lowest_val(9999999999.99, "ldavg_five");
    set_ldavg_double_lowest_val(9999999999.99, "ldavg_15");

    /* up to MAX_BLOCK_DEVICE_NUMBERS */
    for (i = 0; i < MAX_BLOCK_DEVICE_NUMBERS; i++) {
        set_block_device_lowest_val(9999999999.99, i, "areqsz");
        set_block_device_lowest_val(9999999999.99, i, "util");
    }

    /* up to MAX_NETWORK_DEVICE_NUMBERS */
    for (i = 0; i < MAX_NETWORK_DEVICE_NUMBERS; i++) {
        set_network_lowest_val(999999999.99, i, "rxpck");
        set_network_lowest_val(999999999.99, i, "txpck");
        set_network_lowest_val(999999999.99, i, "rxkb");
        set_network_lowest_val(999999999.99, i, "txkb");
        set_network_lowest_val(999999999.99, i, "rxerr");
        set_network_lowest_val(999999999.99, i, "txerr");
        set_network_lowest_val(999999999.99, i, "rxdrop");
        set_network_lowest_val(999999999.99, i, "txdrop");
    }

    set_cpu_as_paragraph(0);
    set_tmp_val(0);
    set_tmp2_val(0);
    set_tmp3_val(0);

    /* initialize the line list object (node) */
    init_list(&line_obj);
    init_list(&line_all_obj);
    init_list(&header_obj);
    init_list(&report_obj);
    init_list(&report_cpu_obj);

    int v = 0;
    for (v = 0; v < MAX_CORE_NUMBERS; v++) {
        init_list(&report_cpu_spike_obj[v]);
        init_list(&report_cpu_time_span_spike_obj[v]);
    }
    init_list(&report_cpu_explanation_obj);
    init_list(&report_tasks_obj);
    init_list(&report_tasks_spike_obj);
    init_list(&report_tasks_time_span_spike_obj);
    init_list(&report_tasks_explanation_obj);
    init_list(&report_pswap_obj);
    init_list(&report_pswap_spike_obj);
    init_list(&report_pswap_time_span_spike_obj);
    init_list(&report_pswap_explanation_obj);
    init_list(&report_paging_obj);
    init_list(&report_paging_spike_obj);
    init_list(&report_paging_time_span_spike_obj);
    init_list(&report_paging_explanation_obj);
    init_list(&report_io_transfer_rate_obj);
    init_list(&report_io_transfer_rate_spike_obj);
    init_list(&report_io_transfer_rate_time_span_spike_obj);
    init_list(&report_io_transfer_rate_explanation_obj);
    init_list(&report_memory_obj);
    init_list(&report_memory_spike_obj);
    init_list(&report_memory_time_span_spike_obj);
    init_list(&report_memory_explanation_obj);
    init_list(&report_swpused_obj);
    init_list(&report_swpused_spike_obj);
    init_list(&report_swpused_time_span_spike_obj);
    init_list(&report_swpused_explanation_obj);
    init_list(&report_kernel_table_obj);
    init_list(&report_kernel_table_spike_obj);
    init_list(&report_kernel_table_time_span_spike_obj);
    init_list(&report_kernel_table_explanation_obj);
    init_list(&report_ldavg_obj);
    init_list(&report_ldavg_spike_obj);
    init_list(&report_ldavg_time_span_spike_obj);
    init_list(&report_ldavg_explanation_obj);
    init_list(&report_block_device_obj);
    for (v = 0; v < MAX_BLOCK_DEVICE_NUMBERS; v++) {
        init_list(&report_block_device_spike_obj[v]);
        init_list(&report_block_device_time_span_spike_obj[v]);
    }
    init_list(&report_block_device_explanation_obj);
    init_list(&report_network_obj);
    for (v = 0; v < MAX_NETWORK_DEVICE_NUMBERS; v++) {
        init_list(&report_network_spike_obj[v]);
        init_list(&report_network_time_span_spike_obj[v]);
    }
    init_list(&report_network_explanation_obj);
    init_list(&report_network_error_obj);
    for (v = 0; v < MAX_NETWORK_DEVICE_NUMBERS; v++) {
        init_list(&report_network_error_spike_obj[v]);
        init_list(&report_network_error_time_span_spike_obj[v]);
    }
    init_list(&report_network_error_explanation_obj);
    init_list(&report_thrashing_obj);
    for (v = 0; v < MAX_NETWORK_DEVICE_NUMBERS; v++)
        init_list(&report_network_down_obj[v]);
    init_list(&report_overall_judgement_obj);
    init_list(&svg_common_cpu_obj);
    init_list2(&svg_cpu_usr_obj);
    init_list2(&svg_cpu_sys_obj);
    init_list2(&svg_cpu_iowait_obj);
    init_list2(&svg_cpu_idle_obj);
    init_list2(&svg_memory_memused_obj);
    init_list2(&svg_memory_swpused_obj);
    for (v = 0; v < MAX_BLOCK_DEVICE_NUMBERS; v++) {
        init_list2(&svg_block_device_util_obj[v]);
    }
    init_list2(&svg_ldavg_one_obj);
    init_list2(&svg_ldavg_five_obj);
    init_list2(&svg_ldavg_15_obj);

    return 0;
}

int free_sar_analyzer_obj()
{
    int v = 0;

    /* clear list */
    clear_list(&line_obj);
    clear_list(&line_all_obj);
    clear_list(&header_obj);
    clear_list(&report_obj);
    clear_list(&report_cpu_obj);
    for (v = 0; v < MAX_CORE_NUMBERS; v++) {
        clear_list(&report_cpu_spike_obj[v]);
        clear_list(&report_cpu_time_span_spike_obj[v]);
    }
    clear_list(&report_cpu_explanation_obj);
    clear_list(&report_tasks_obj);
    clear_list(&report_tasks_spike_obj);
    clear_list(&report_tasks_time_span_spike_obj);
    clear_list(&report_tasks_explanation_obj);
    clear_list(&report_pswap_obj);
    clear_list(&report_pswap_spike_obj);
    clear_list(&report_pswap_time_span_spike_obj);
    clear_list(&report_pswap_explanation_obj);
    clear_list(&report_paging_obj);
    clear_list(&report_paging_spike_obj);
    clear_list(&report_paging_time_span_spike_obj);
    clear_list(&report_paging_explanation_obj);
    clear_list(&report_io_transfer_rate_obj);
    clear_list(&report_io_transfer_rate_spike_obj);
    clear_list(&report_io_transfer_rate_time_span_spike_obj);
    clear_list(&report_io_transfer_rate_explanation_obj);
    clear_list(&report_memory_obj);
    clear_list(&report_memory_spike_obj);
    clear_list(&report_memory_time_span_spike_obj);
    clear_list(&report_memory_explanation_obj);
    clear_list(&report_swpused_obj);
    clear_list(&report_swpused_spike_obj);
    clear_list(&report_swpused_time_span_spike_obj);
    clear_list(&report_swpused_explanation_obj);
    clear_list(&report_kernel_table_obj);
    clear_list(&report_kernel_table_spike_obj);
    clear_list(&report_kernel_table_time_span_spike_obj);
    clear_list(&report_kernel_table_explanation_obj);
    clear_list(&report_ldavg_obj);
    clear_list(&report_ldavg_spike_obj);
    clear_list(&report_ldavg_time_span_spike_obj);
    clear_list(&report_ldavg_explanation_obj);
    clear_list(&report_block_device_obj);
    for (v = 0; v < MAX_BLOCK_DEVICE_NUMBERS; v++) {
        clear_list(&report_block_device_spike_obj[v]);
        clear_list(&report_block_device_time_span_spike_obj[v]);
    }
    clear_list(&report_block_device_explanation_obj);
    clear_list(&report_network_obj);
    for (v = 0; v < MAX_NETWORK_DEVICE_NUMBERS; v++) {
        clear_list(&report_network_spike_obj[v]);
        clear_list(&report_network_time_span_spike_obj[v]);
    }
    clear_list(&report_network_explanation_obj);
    clear_list(&report_network_error_obj);
    for (v = 0; v < MAX_NETWORK_DEVICE_NUMBERS; v++) {
        clear_list(&report_network_error_spike_obj[v]);
        clear_list(&report_network_error_time_span_spike_obj[v]);
    }
    clear_list(&report_network_error_explanation_obj);
    clear_list(&report_thrashing_obj);
    for (v = 0; v < MAX_NETWORK_DEVICE_NUMBERS; v++)
        clear_list(&report_network_down_obj[v]);
    clear_list(&report_overall_judgement_obj);
    clear_list(&svg_common_cpu_obj);
    clear_list2(&svg_cpu_usr_obj);
    clear_list2(&svg_cpu_sys_obj);
    clear_list2(&svg_cpu_iowait_obj);
    clear_list2(&svg_cpu_idle_obj);
    clear_list2(&svg_memory_memused_obj);
    clear_list2(&svg_memory_swpused_obj);
    for (v = 0; v < MAX_BLOCK_DEVICE_NUMBERS; v++) {
        clear_list2(&svg_block_device_util_obj[v]);
    }
    clear_list2(&svg_ldavg_one_obj);
    clear_list2(&svg_ldavg_five_obj);
    clear_list2(&svg_ldavg_15_obj);

    return 0;
}

int check_time_value_is_in_time_span(const char *time_span_str, const char *time_value)
{
    char str_spn[12];
    char str_now[9];
    memset(str_spn, '\0', sizeof(str_spn)); 
    memset(str_now, '\0', sizeof(str_now)); 
    strncpy(str_spn, time_span_str, 11);
    strncpy(str_now, time_value, 8);

    int span_start_hour_l = 0;
    int span_start_hour_r = 0;
    int span_start_minute_l = 0;
    int span_start_minute_r = 0;
    int span_start_seconds = 0;

    int span_end_hour_l = 0;
    int span_end_hour_r = 0;
    int span_end_minute_l = 0;
    int span_end_minute_r = 0;
    int span_end_seconds = 0;

    int now_hour_l = 0;
    int now_hour_r = 0;
    int now_minute_l = 0;
    int now_minute_r = 0;
    int now_seconds = 0;

    if (str_spn[0] == '0')
        span_start_hour_l = 0;
    if (str_spn[0] == '1')
        span_start_hour_l = 1;
    if (str_spn[0] == '2')
        span_start_hour_l = 2;

    if (str_spn[1] == '0')
        span_start_hour_r = 0;
    if (str_spn[1] == '1')
        span_start_hour_r = 1;
    if (str_spn[1] == '2')
        span_start_hour_r = 2;
    if (str_spn[1] == '3')
        span_start_hour_r = 3;
    if (str_spn[1] == '4')
        span_start_hour_r = 4;
    if (str_spn[1] == '5')
        span_start_hour_r = 5;
    if (str_spn[1] == '6')
        span_start_hour_r = 6;
    if (str_spn[1] == '7')
        span_start_hour_r = 7;
    if (str_spn[1] == '8')
        span_start_hour_r = 8;
    if (str_spn[1] == '9')
        span_start_hour_r = 9;

    if (str_spn[3] == '0')
        span_start_minute_l = 0;
    if (str_spn[3] == '1')
        span_start_minute_l = 1;
    if (str_spn[3] == '2')
        span_start_minute_l = 2;
    if (str_spn[3] == '3')
        span_start_minute_l = 3;
    if (str_spn[3] == '4')
        span_start_minute_l = 4;
    if (str_spn[3] == '5')
        span_start_minute_l = 5;

    if (str_spn[4] == '0')
        span_start_minute_r = 0;
    if (str_spn[4] == '1')
        span_start_minute_r = 1;
    if (str_spn[4] == '2')
        span_start_minute_r = 2;
    if (str_spn[4] == '3')
        span_start_minute_r = 3;
    if (str_spn[4] == '4')
        span_start_minute_r = 4;
    if (str_spn[4] == '5')
        span_start_minute_r = 5;
    if (str_spn[4] == '6')
        span_start_minute_r = 6;
    if (str_spn[4] == '7')
        span_start_minute_r = 7;
    if (str_spn[4] == '8')
        span_start_minute_r = 8;
    if (str_spn[4] == '9')
        span_start_minute_r = 9;

    if (str_spn[6] == '0')
        span_end_hour_l = 0;
    if (str_spn[6] == '1')
        span_end_hour_l = 1;
    if (str_spn[6] == '2')
        span_end_hour_l = 2;

    if (str_spn[7] == '0')
        span_end_hour_r = 0;
    if (str_spn[7] == '1')
        span_end_hour_r = 1;
    if (str_spn[7] == '2')
        span_end_hour_r = 2;
    if (str_spn[7] == '3')
        span_end_hour_r = 3;
    if (str_spn[7] == '4')
        span_end_hour_r = 4;
    if (str_spn[7] == '5')
        span_end_hour_r = 5;
    if (str_spn[7] == '6')
        span_end_hour_r = 6;
    if (str_spn[7] == '7')
        span_end_hour_r = 7;
    if (str_spn[7] == '8')
        span_end_hour_r = 8;
    if (str_spn[7] == '9')
        span_end_hour_r = 9;

    if (str_spn[9] == '0')
        span_end_minute_l = 0;
    if (str_spn[9] == '1')
        span_end_minute_l = 1;
    if (str_spn[9] == '2')
        span_end_minute_l = 2;
    if (str_spn[9] == '3')
        span_end_minute_l = 3;
    if (str_spn[9] == '4')
        span_end_minute_l = 4;
    if (str_spn[9] == '5')
        span_end_minute_l = 5;

    if (str_spn[10] == '0')
        span_end_minute_r = 0;
    if (str_spn[10] == '1')
        span_end_minute_r = 1;
    if (str_spn[10] == '2')
        span_end_minute_r = 2;
    if (str_spn[10] == '3')
        span_end_minute_r = 3;
    if (str_spn[10] == '4')
        span_end_minute_r = 4;
    if (str_spn[10] == '5')
        span_end_minute_r = 5;
    if (str_spn[10] == '6')
        span_end_minute_r = 6;
    if (str_spn[10] == '7')
        span_end_minute_r = 7;
    if (str_spn[10] == '8')
        span_end_minute_r = 8;
    if (str_spn[10] == '9')
        span_end_minute_r = 9;

    if (str_now[0] == '0')
        now_hour_l = 0;
    if (str_now[0] == '1')
        now_hour_l = 1;
    if (str_now[0] == '2')
        now_hour_l = 2;

    if (str_now[1] == '0')
        now_hour_r = 0;
    if (str_now[1] == '1')
        now_hour_r = 1;
    if (str_now[1] == '2')
        now_hour_r = 2;
    if (str_now[1] == '3')
        now_hour_r = 3;
    if (str_now[1] == '4')
        now_hour_r = 4;
    if (str_now[1] == '5')
        now_hour_r = 5;
    if (str_now[1] == '6')
        now_hour_r = 6;
    if (str_now[1] == '7')
        now_hour_r = 7;
    if (str_now[1] == '8')
        now_hour_r = 8;
    if (str_now[1] == '9')
        now_hour_r = 9;

    if (str_now[3] == '0')
        now_minute_l = 0;
    if (str_now[3] == '1')
        now_minute_l = 1;
    if (str_now[3] == '2')
        now_minute_l = 2;
    if (str_now[3] == '3')
        now_minute_l = 3;
    if (str_now[3] == '4')
        now_minute_l = 4;
    if (str_now[3] == '5')
        now_minute_l = 5;

    if (str_now[4] == '0')
        now_minute_r = 0;
    if (str_now[4] == '1')
        now_minute_r = 1;
    if (str_now[4] == '2')
        now_minute_r = 2;
    if (str_now[4] == '3')
        now_minute_r = 3;
    if (str_now[4] == '4')
        now_minute_r = 4;
    if (str_now[4] == '5')
        now_minute_r = 5;
    if (str_now[4] == '6')
        now_minute_r = 6;
    if (str_now[4] == '7')
        now_minute_r = 7;
    if (str_now[4] == '8')
        now_minute_r = 8;
    if (str_now[4] == '9')
        now_minute_r = 9;

    span_start_seconds =(span_start_hour_l * 3600 * 10) + (span_start_hour_r * 3600) +
        (span_start_minute_l * 60 * 10) + (span_start_minute_r * 60);
    span_end_seconds = (span_end_hour_l * 3600 * 10) + (span_end_hour_r * 3600) +
        (span_end_minute_l * 60 * 10) + (span_end_minute_r * 60);
    now_seconds = (now_hour_l * 3600 * 10) + (now_hour_r * 3600) +
        (now_minute_l * 60 * 10) + (now_minute_r * 60);
        
    if (now_seconds >= span_start_seconds && now_seconds <= span_end_seconds)
        return 1;

    return 0;
}

int check_time_continuity(int file_number, char* this_time, char* this_time_former)
{
    char time_this[6];
    char minutes_this[6];
    char time_this_former[6];
    char minutes_this_former[6];

    memset(time_this,'\0',sizeof(time_this));
    memset(minutes_this,'\0',sizeof(minutes_this));
    memset(time_this_former,'\0',sizeof(time_this_former));
    memset(minutes_this_former,'\0',sizeof(minutes_this_former));

    strncpy(time_this, this_time, 5);
    strncpy(time_this_former, this_time_former, 5);
    time_this[2] = '\0';
    time_this_former[2] = '\0';
    minutes_this[0] = this_time[3];
    minutes_this[1] = this_time[4];
    minutes_this[2] = '\0';
    minutes_this_former[0] = this_time_former[3];
    minutes_this_former[1] = this_time_former[4];
    minutes_this_former[2] = '\0';

    int time_this_i =atoi(time_this);
    int time_this_former_i =atoi(time_this_former);
    int minutes_this_i =atoi(minutes_this);
    int minutes_this_former_i =atoi(minutes_this_former);
    int time_difference = 0;
    int minutes_difference = 0;
    int difference = 0;

    if (time_this_i == time_this_former_i) {
        if (minutes_this_i - minutes_this_former_i > 10)
            difference = (minutes_this_i - minutes_this_former_i / 10) - 1;
    }

    time_difference = time_this_i - time_this_former_i; 

    if (minutes_this_i > minutes_this_former_i) {
        minutes_difference = ((minutes_this_i - minutes_this_former_i) / 10) - 1;
    } else {
        if (minutes_this_former_i - minutes_this_i == 10)
            minutes_difference = 4;
        if (minutes_this_former_i - minutes_this_i == 20)
            minutes_difference = 3;
        if (minutes_this_former_i - minutes_this_i == 30)
            minutes_difference = 2;
        if (minutes_this_former_i - minutes_this_i == 40)
            minutes_difference = 1;
    }

    difference = time_difference * minutes_difference;

    return difference;
}
