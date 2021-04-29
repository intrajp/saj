/*
 * saj.c - main file for saj.
 * This file contains the contents of saj.
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

#include <unistd.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <errno.h>
#include "../libsaj-sosreport-analyzer/cfg.h"
#include "../libsaj-sosreport-analyzer/common.h"
#include "../libsaj-sosreport-analyzer/line_data.h"
#include "../libsaj-sosreport-analyzer/member_data.h"
#include "../libsaj-sar-analyzer/common.h"

/* configuration file of this program/library */
static const char* fname = "~/.saj/saj.conf";
static const char* fname_mcinfo = "~/.saj/saj-mcinfo.conf";
static const char* fname_example =
    "/usr/share/saj/saj.conf.example";
static const char* fname_mcinfo_example =
    "/usr/share/saj/saj-mcinfo.conf.example";

const char* app_name = "saj";

/* this function delete files when got SIGINT or SIGHUP */
int delete_files(void);

/* brief Print help for this application */
static void __print_help(int mcinfo)
{
    printf("\n VERSION %d.%d.%d\n", PROGRAM_VERSION, PROGRAM_RELEASE, PROGRAM_SUB_RELEASE);
    puts("\n Configuration:");
    if (mcinfo == 0) {
        puts("\n   For sosreport");
        printf("\n     Edit '%s'. \n", fname);
        printf("     If you are unsure, \n   copy from '%s' \n   to %s.\n", fname_example, fname);
    } else if (mcinfo == 1) {
        puts("\n   For mcinfo");
        printf("\n     Edit '%s'.\n", fname_mcinfo);
        printf("     If you are unsure, \n   copy from '%s' \n   to %s.\n", fname_mcinfo_example, fname_mcinfo);
    }
    puts("\n Options:\n");
    puts("   -V|--version");
    puts("   -D|--directory <path_to_sosreport_directory>");
    puts("                     Analyze files in the directory");
    puts("   -M|--mcinfo       Analyze mcinfo files");
    puts("   -S|--sar-only     Analyze sar files only");
    puts("   -T|--time-span    Analyze time-span on sar files");
    puts("   -h|--help         Print this help");
    puts("\n Usage:\n");
    puts("   To analyze sosreport (including sar analyzing)\n");
    printf("     $ %s -D <path_to_sosreport_directory>\n\n", app_name);
    puts("   To analyze  mcinfo (including sar analyzing)\n");
    printf("     $ %s -M -D <path_to_mcinfo_directory>\n\n", app_name);
    puts("   For only sar analyzing\n");
    printf("     $ %s -S -D <path_to_sa_directory>\n\n", app_name);
    puts("   For time-span sar analyzing\n");
    printf("     ex. $ %s -T 09:00-10:00 -D <path_to_sa_directory>\n\n", app_name);
    puts("   Directory 'saj-results' will be made \n   in the current directory with files.");
    puts("\n Note:\n");
    puts("   Use appropriate config file which is \n   stored in /usr/share/saj");
    puts("   and copy it as '~/.saj/saj.conf'.");
    puts("   You can set items to each member in conf file.\n");
}

const char msg_sigint[30] ="I caught SIGINT\n";
const char msg_sighup[30] ="I caught SIGHUP\n";
const char msg_sigchld[30] ="I caught SIGCHLD\n";

/*
 * brief Callback function for handling signal(s).
 */
void handle_signal(int sig)
{
    if (sig == SIGINT) {
        /*showing this is SIGINT process*/
        write(STDOUT_FILENO, msg_sigint, sizeof(msg_sigint) - 1);
        printf("%s",msg_sigint);
        /* this is needed, kernel don't care these stuff, you know... */
        delete_files();
        /* Reset signal handling to default behavior */
        signal(SIGINT, SIG_DFL);
        exit(EXIT_FAILURE); 
    }
    if (sig == SIGHUP) {
        /*showing this is SIGHUP process*/
        write(STDOUT_FILENO, msg_sighup, sizeof(msg_sighup) - 1);
        printf("%s",msg_sighup);
        /* this is needed, kernel don't care these stuff, you know... */
        delete_files();
        /* Reset signal handling to default behavior */
        signal(SIGHUP, SIG_DFL);
        exit(EXIT_FAILURE); 
    }
}

static int __write_version_to_analyze_file(node **obj, FILE *fp)
{
    char version_string[200];
    memset(version_string,'\0',sizeof(version_string));
    snprintf(version_string, 200, "Created by saj: Version-%d.%d.%d",
        PROGRAM_VERSION, PROGRAM_RELEASE, PROGRAM_SUB_RELEASE);
    append_list(&sos_version_obj, "####");
    append_list(&sos_version_obj, version_string);
    append_list(&sos_version_obj, "####");
    file_write_list(obj, fp);
    return 0;
}

/* written files */
const char* sos_file_all_write = "";
const char* log_file_write = "";
int file_part = 0;

/* Main function */
int main(int argc, char* argv[])
{
    struct timeval  tv1, tv2;
    gettimeofday(&tv1, NULL);

    if (! isatty(fileno(stdout))) {
        fprintf(stderr, "You are not a terminal!\n");
        fprintf(stderr, "You are not allowed to redirect to a file.\n");
        /* return 0; */
    }
    /* Here, we first allow asking only the version. */
    int value = 0;
    const char* dir_name = NULL;
    if (argc <= 2) {
        while (1) {
            int option_index = 0;
            static struct option long_options[] = {
                {"help", no_argument, 0, 'h'},
                {"version", no_argument, 0, 'V'},
                {"directory", required_argument, 0, 'D'},
                {"mcinfo", no_argument, 0, 'M'},
                {"sar-only", no_argument, 0, 'S'},
                {"time-span", required_argument, 0, 'T'},
                {NULL, 0, 0, 0}
            };
            /* Try to process all command line arguments */
            value = getopt_long(argc, argv, "hVDMST", long_options, &option_index);
            if (value == -1)
                break;
            switch(value) {
                case 'h':
                    __print_help(0);
                    return 0;
                    break;
                case 'V':
                    printf("Version-%d.%d.%d\n", PROGRAM_VERSION, PROGRAM_RELEASE, PROGRAM_SUB_RELEASE);
                    return 0;
                    break;
                case '?':
                    __print_help(0);
                    return 0;
                    break;
                case 'D':
                    dir_name = optarg;
                    if (dir_name == NULL) {
                        printf("\n Please set directory name.\n");
                        __print_help(0);
                        return 0;
                    }
                    break;
                case 'M':
                    printf("\n Please also set -D <directory_name> | --directory <directory_name>.\n");
                    printf(" ex. $ saj -M -D <path_to_mcinfo_directory>\n");
                    __print_help(0);
                    return 0;
                    break;
                case 'S':
                    printf("\n Please also set -D <directory_name> | --directory <directory_name>.\n");
                    printf(" ex. $ saj -S -D <path_to_sa_directory>\n");
                    __print_help(0);
                    return 0;
                    break;
                case 'T':
                    printf("\n Please also set -D <directory_name> | --directory <directory_name>.\n");
                    printf(" ex. $ saj -T 09:00-10:00 -D <path_to_sosreport_or_mcinfo_directory>\n");
                    printf(" ex. $ saj -S -T 09:00-10:00 -D <path_to_sa_directory>\n");
                    __print_help(0);
                    return 0;
                    break;
            }
        }
        __print_help(0);
        return 0;
    }

    /* sosreport-analyzer */

    /* initialize the objects */
    initialize_objects();

    char str_tmp[MAX_FILE_NAME_LENGTH];
    char str_tmp2[MAX_FILE_NAME_LENGTH];
    char str_tmp3[MAX_FILE_NAME_LENGTH];
    char dir_sa[MAX_FILE_NAME_LENGTH];
    memset(str_tmp, '\0', sizeof(str_tmp));
    memset(str_tmp2, '\0', sizeof(str_tmp2));
    memset(str_tmp3, '\0', sizeof(str_tmp3));
    memset(dir_sa, '\0', sizeof(dir_sa));
    append_list(&sos_header_obj, "####");
    snprintf(str_tmp2, MAX_FILE_NAME_LENGTH, "%s: Version-%d.%d.%d", app_name, PROGRAM_VERSION,
        PROGRAM_RELEASE, PROGRAM_SUB_RELEASE);
    append_list(&sos_header_obj, str_tmp2);
    append_list(&sos_header_obj, "####");
    append_list(&sos_tail_obj, "####");
    memset(str_tmp2, '\0', sizeof(str_tmp2));
    snprintf(str_tmp2, MAX_FILE_NAME_LENGTH, "%s ends.", app_name);
    append_list(&sos_tail_obj, str_tmp2);

    int dir_len_check = 255;
    size_t dir_len = 0;
    int mcinfo = 0;
    int sar_only = 0;
    int v = 0;
    size_t time_span_str_len = 0;
    const char* time_span = NULL;

    while (1) {
        int option_index = 0;
        static struct option long_options[] = {
            {"directory", required_argument, 0, 'D'},
            {"mcinfo", no_argument, 0, 'M'},
            {"sar-only", no_argument, 0, 'S'},
            {"time-span", required_argument, 0, 'T'},
            {NULL, 0, 0, 0}
        };

        /* Try to process all command line arguments */
        value = getopt_long(argc, argv, "MST:D:", long_options, &option_index);
        if (value == -1)
            break;
        switch(value) {
            case 'D':
                dir_name = optarg;
                if (dir_name == NULL) {
                    printf("Please set directory name.\n");
                    __print_help(mcinfo);
                    return 0;
                }
                dir_len = strlen(dir_name);
                if (dir_len <= 0) {
                    __print_help(mcinfo);
                    return 0;
                }
                if (strstr(dir_name, "\n") != NULL || (dir_len > dir_len_check)) {
                    fprintf(stderr, "Can't analyze this directory.\n");
                    __print_help(mcinfo);
                    return 0;
                } else {
                    if (is_dir_present(dir_name, sar_only) == 1) {
                        __print_help(mcinfo);
                        return 0;
                    }
                    strncpy(sos_dir_file_obj->dir_file_names.dirname, dir_name,
                        MAX_FILE_NAME_LENGTH - 1);
                    char str_dir_tmp[MAX_FILE_NAME_LENGTH];
                    memset(str_dir_tmp, '\0', sizeof(str_dir_tmp));
                    remove_the_last_slash_from_dir_name(get_dirname(str_dir_tmp));
                    snprintf(str_tmp2, MAX_FILE_NAME_LENGTH, "dirname:%s", get_dirname(str_dir_tmp));
                    append_list(&sos_header_obj, str_tmp2);
                    append_list(&sos_header_obj, "");
                }
                break;
            case 'M':
                fname = "~/.saj/saj-mcinfo.conf";
                mcinfo = 1;
                break;
            case 'S':
                sar_only = 1;
                break;
            case 'T':
                time_span = optarg;
                time_span_str_len = strlen(time_span );
                if ((time_span_str_len <= 0) || (time_span_str_len > 11)) {
                    __print_help(mcinfo);
                    return 0;
                }
                if (!(check_time_span_str(time_span))) {
                    __print_help(mcinfo);
                    return 0;
                }
                break;
            default:
                __print_help(mcinfo);
                return 0;
                break;
        }
    }

    if (dir_name == NULL) {
        fprintf(stderr, "\nYou forgot setting directory...");
        __print_help(mcinfo);
        return 0;
    }

    char str_dir_tmp[MAX_FILE_NAME_LENGTH];
    memset(str_dir_tmp, '\0', sizeof(str_dir_tmp));
    if (sar_only == 0 && is_sos_dir_present(get_dirname(str_dir_tmp), sar_only, mcinfo) == 1) {
        fprintf(stderr, "This should not be a proper directory to be analyzed:\n%s\n",
            sos_dir_file_obj->dir_file_names.dirname);
        __print_help(mcinfo);
        exit(EXIT_FAILURE);
    }

    /* sosreport-analyzer */

    /* first, append members */
    append_members();
    /* read sosreport files */
    cfg_read(fname, mcinfo, sar_only);
    /* initializing directory to be written */
    sos_file_to_write(sar_only);

    FILE* fp_all_w = NULL;
    sos_file_all_write = get_sos_file_name_to_be_written();

    FILE* fp_analyze_w = NULL;
    fp_analyze_w = file_open_check(fp_analyze_w,
        get_sos_analyze_file_name_to_be_written(),"a", sar_only); 
    __write_version_to_analyze_file(&sos_version_obj, fp_analyze_w);
    fclose(fp_analyze_w);

    fp_all_w = file_open_check(fp_all_w, sos_file_all_write,"a", sar_only); 
    /* header and config related lines and 'also read these files' stuff */
    file_write_list(&sos_header_obj, fp_all_w);
    fclose(fp_all_w);

    /* log file */
    FILE* fp_log_w = NULL;
    /* --------  for file write --------*/
    log_file_write = get_log_file_name_to_be_written();
    /* open result file */
    fp_log_w = file_open_check(fp_log_w, log_file_write,"a", sar_only); 
    file_write_list(&log_obj, fp_log_w);
    fclose(fp_log_w);

    puts("\nNotice: You can set 'skip' to the member in the conf file when directory\
 is not present.\n");
    if (sar_only != 1) {
        signal(SIGINT, handle_signal);
        signal(SIGHUP, handle_signal);
        pid_t cpid;
        pid_t wpid;
        int status = 0;
        /* Read files */
        volatile node_m *ptr_tmp_m = member_obj;
        while (ptr_tmp_m != NULL) {
            if (ptr_tmp_m->mcinfo == mcinfo) {
                cpid = fork();
                if (cpid == -1) {
                    perror("fork");
                    free_sosreport_analyzer_obj(sar_only);
                    exit(EXIT_FAILURE);
                }
                if (cpid == 0) {
                    printf("---- member:%s\n", ptr_tmp_m->_member);
                    char str_dir_tmp[MAX_FILE_NAME_LENGTH];
                    memset(str_dir_tmp, '\0', sizeof(str_dir_tmp));
                    read_file_pre(ptr_tmp_m->_member, get_dirname(str_dir_tmp), mcinfo, sar_only, sos_file_all_write,
                        log_file_write, file_part);
                    _exit(EXIT_SUCCESS);
                }
                file_part++;
            }
            ptr_tmp_m = ptr_tmp_m->next;
        }
        /* wait all the children to finish */
        while ((wpid = waitpid(-1, &status, 0)) > 0);
    }

    /* again we open file here */
    fp_all_w = file_open_check(fp_all_w, sos_file_all_write, "a", sar_only);

    /* Copy contents of part file to all */
    for (int i = 0; i < file_part; i++) {
        char sos_file_all_write_tmp[ MAX_FILE_NAME_LENGTH ];
        snprintf(sos_file_all_write_tmp, MAX_LINE_LENGTH - 1, "%s_%d", sos_file_all_write, i);

        FILE* fp_all_part;
        /* We ignore the part file which could not been opened assuming the directory is not present. */
        if ((fp_all_part = fopen(sos_file_all_write_tmp, "r")) != NULL) {
            char c;
            while ((c = fgetc(fp_all_part)) != EOF) 
                fputc(c, fp_all_w);
            fclose(fp_all_part);
            unlink(sos_file_all_write_tmp);
        }
    }
    /* writing tail lines to a file */
    file_write_list(&sos_tail_obj, fp_all_w);
    fclose(fp_all_w);

    signal(SIGINT, handle_signal);
    signal(SIGHUP, handle_signal);
    /* open result directory */
    char str_dir_result[MAX_FILE_NAME_LENGTH];
    memset(str_dir_result, '\0', sizeof(str_dir_result));
    strncpy(str_dir_result, "./saj-results", MAX_FILE_NAME_LENGTH);
    if (check_result_dir(str_dir_result, sar_only, 0) != 0) {
        fprintf(stderr, "can't open dir %s (%s)\n", str_dir_result, strerror(errno));
        free_sosreport_analyzer_obj(sar_only);
        exit(EXIT_FAILURE);
    }

    /* for sar-analyzer stuff */
    memset(str_dir_tmp, '\0', sizeof(str_dir_tmp));
    if (sar_only == 0)
        snprintf(dir_sa, MAX_FILE_NAME_LENGTH, "%s/var/log/sa", get_dirname(str_dir_tmp));
    else
        snprintf(dir_sa, MAX_FILE_NAME_LENGTH, "%s", get_dirname(str_dir_tmp));

    if (is_dir_present(dir_sa, sar_only) == 1 && sar_only == 0) {
        printf("Please check result file ./%s\n", sos_file_all_write);
        printf("%s does not exist. Program ends.\n", dir_sa);
        /* freeing sosreport-analyzer objects */
        free_sosreport_analyzer_obj(sar_only);
        exit(EXIT_FAILURE);
    }

    puts("analyzing sar files.");
    int SAR_OPTION = 'Z';
    int REPORT = 0;
    int MESSAGE_ONLY = 1;
    /*
     *  initialize sar_analyzer object, line object
     *  also, starts analyzing
     */
    const char* file_name = NULL;
    memset(str_tmp, '\0', sizeof(str_tmp));

    if (sar_only == 1) {
        char str_dir_tmp[MAX_FILE_NAME_LENGTH];
        memset(str_dir_tmp, '\0', sizeof(str_dir_tmp));
        snprintf(str_tmp, MAX_FILE_NAME_LENGTH, "%s", (char *)get_dirname(str_dir_tmp));
    } else if (sar_only == 0) {
        snprintf(str_tmp, MAX_FILE_NAME_LENGTH, "%s/var/log/sa", (char *)get_dirname(str_tmp3));
    }

    sar_analyzer_init(str_tmp, file_name, SAR_OPTION, REPORT, MESSAGE_ONLY, time_span);

    char str_num[MAX_FILE_NAME_LENGTH + 1] = {'\0'};
    char str_tmp_sar[10] = "dir_name:";
    strncpy(str_num, str_tmp_sar, 10);
    strncat(str_num, get_dir_name_analyze(), MAX_DIR_NAME_LENGTH);
    append_list(&report_obj, "--------");
    append_list(&report_obj, str_num);
    append_list(&report_obj, "--------");

    /* creating file name to be written from SAR_OPTION */
    file_to_write(SAR_OPTION);

    const char* sar_file_write = "";
    char* file_svg_write = "";
    /* --------  for file write --------*/
    sar_file_write = get_sar_file_name_to_be_written();
    file_svg_write = (char *)get_svg_file_name_to_be_written();
    FILE* fp_sar_w = NULL;
    FILE* fp_svg_w = NULL;

    /* open result file */
    fp_sar_w = file_open_check(fp_sar_w, sar_file_write,"a", sar_only);

    print_and_file_write_analyzed_files(&line_all_obj, "filename", NULL, fp_sar_w);

    /* writing report object to result file */
    file_write_list(&line_all_obj, fp_sar_w);
    file_write_list(&header_obj, fp_sar_w);
    file_write_list(&report_cpu_obj, fp_sar_w);
    for (v = 0; v <= get_core_numbers(); v++) {
        file_write_list(&report_cpu_spike_obj[v], fp_sar_w);
        file_write_list(&report_cpu_time_span_spike_obj[v], fp_sar_w);
    }
    file_write_list(&report_cpu_explanation_obj, fp_sar_w);
    file_write_list(&report_tasks_obj, fp_sar_w);
    file_write_list(&report_tasks_spike_obj, fp_sar_w);
    file_write_list(&report_tasks_time_span_spike_obj, fp_sar_w);
    file_write_list(&report_tasks_explanation_obj, fp_sar_w);
    file_write_list(&report_pswap_obj, fp_sar_w);
    file_write_list(&report_pswap_spike_obj, fp_sar_w);
    file_write_list(&report_pswap_time_span_spike_obj, fp_sar_w);
    file_write_list(&report_pswap_explanation_obj, fp_sar_w);
    file_write_list(&report_paging_obj, fp_sar_w);
    file_write_list(&report_paging_spike_obj, fp_sar_w);
    file_write_list(&report_paging_time_span_spike_obj, fp_sar_w);
    file_write_list(&report_paging_explanation_obj, fp_sar_w);
    file_write_list(&report_io_transfer_rate_obj, fp_sar_w);
    file_write_list(&report_io_transfer_rate_spike_obj, fp_sar_w);
    file_write_list(&report_io_transfer_rate_time_span_spike_obj, fp_sar_w);
    file_write_list(&report_io_transfer_rate_explanation_obj, fp_sar_w);
    file_write_list(&report_memory_obj, fp_sar_w);
    file_write_list(&report_memory_spike_obj, fp_sar_w);
    file_write_list(&report_memory_time_span_spike_obj, fp_sar_w);
    file_write_list(&report_memory_explanation_obj, fp_sar_w);
    file_write_list(&report_swpused_obj, fp_sar_w);
    file_write_list(&report_swpused_spike_obj, fp_sar_w);
    file_write_list(&report_swpused_time_span_spike_obj, fp_sar_w);
    file_write_list(&report_swpused_explanation_obj, fp_sar_w);
    file_write_list(&report_kernel_table_obj, fp_sar_w);
    file_write_list(&report_kernel_table_spike_obj, fp_sar_w);
    file_write_list(&report_kernel_table_time_span_spike_obj, fp_sar_w);
    file_write_list(&report_kernel_table_explanation_obj, fp_sar_w);
    file_write_list(&report_ldavg_obj, fp_sar_w);
    file_write_list(&report_ldavg_spike_obj, fp_sar_w);
    file_write_list(&report_ldavg_time_span_spike_obj, fp_sar_w);
    file_write_list(&report_ldavg_explanation_obj, fp_sar_w);
    file_write_list(&report_block_device_obj, fp_sar_w);
    for (v = 0; v <= get_block_device_numbers(); v++) {
        file_write_list(&report_block_device_spike_obj[v], fp_sar_w);
        file_write_list(&report_block_device_time_span_spike_obj[v], fp_sar_w);
    }
    file_write_list(&report_block_device_explanation_obj, fp_sar_w);
    file_write_list(&report_network_obj, fp_sar_w);
    for (v = 0; v <= get_network_device_numbers(); v++) {
        file_write_list(&report_network_spike_obj[v], fp_sar_w);
        file_write_list(&report_network_time_span_spike_obj[v], fp_sar_w);
    }
    file_write_list(&report_network_explanation_obj, fp_sar_w);
    file_write_list(&report_network_error_obj, fp_sar_w);
    for (v = 0; v <= get_network_device_numbers(); v++) {
        file_write_list(&report_network_error_spike_obj[v], fp_sar_w);
        file_write_list(&report_network_error_time_span_spike_obj[v], fp_sar_w);
    }
    file_write_list(&report_network_error_explanation_obj, fp_sar_w);
    file_write_list(&report_thrashing_obj, fp_sar_w);
    for (v = 0; v <= get_network_device_numbers(); v++)
        file_write_list(&report_network_down_obj[v], fp_sar_w);
    file_write_list(&report_overall_judgement_obj, fp_sar_w);
    file_write_list(&report_obj, fp_sar_w);

    /* writing "Linux" lines (top of sar file) to result file */
    print_and_file_write_analyzed_files(&line_all_obj, "Linux", NULL, fp_sar_w);

    puts("------------------------");

    if (sar_only == 1) {
        printf("Please check sar result file ./%s\n", sar_file_write);
        free_sosreport_analyzer_obj(sar_only);
    }
    if (sar_only == 0) {
        printf("Please check result file ./%s\n", sos_file_all_write);
        printf("And check result file ./%s\n", get_sos_analyze_file_name_to_be_written());
        printf("Also check sar result file ./%s\n\n", sar_file_write);
        printf("Program log is written in ./%s\n\n", log_file_write);
        puts("You can try reading all files which is set 'skip' by setting 'all' in conf file.");
        puts("Note that when you done that, it'll take many minutes to be finished depending\
 on cpu power.\n");
        /* freeing sosreport-analyzer objects */
        free_sosreport_analyzer_obj(sar_only);
    }

    /* close the file pointer */
    fclose(fp_sar_w);

    char str_tmp_svg[MAX_LINE_LENGTH] = {'\0'};
    memset(str_tmp_svg, '\0', sizeof(str_tmp_svg));
    snprintf(str_tmp_svg,MAX_LINE_LENGTH, "%s%s", file_svg_write, "-cpu-.svg");
    fp_svg_w = file_open_check(fp_svg_w, str_tmp_svg,"a", sar_only);

    /* create svg files */
    void create_svg_file(node2** obj, char* item, FILE* fp_w);
    create_svg_file(&svg_cpu_usr_obj, "cpu_usr", fp_svg_w);
    create_svg_file(&svg_cpu_sys_obj, "cpu_sys", fp_svg_w);
    create_svg_file(&svg_cpu_iowait_obj, "cpu_iowait", fp_svg_w);
    create_svg_file(&svg_cpu_idle_obj, "cpu_idle", fp_svg_w);
    /* end create svg files */

    char str_tmp_echo[MAX_LINE_LENGTH] = {'\0'};
    memset(str_tmp_echo, '\0', sizeof(str_tmp_echo));
    snprintf(str_tmp_echo, MAX_LINE_LENGTH, "%s%s", file_svg_write, "-<item>.svg");
    printf("Please check graphs in the svg file: %s\n\n", str_tmp_echo);
    /* close the file pointers */
    fclose(fp_svg_w);

    /* freeing sar-analyzer objects */
    free_sar_analyzer_obj();

    gettimeofday(&tv2, NULL);

    printf("Total time = %f seconds\n",
         (double)(tv2.tv_usec - tv1.tv_usec) / 1000000 +
         (double)(tv2.tv_sec - tv1.tv_sec));

    exit(EXIT_SUCCESS);
}

void write_linux_line_to_file(node** obj, FILE* fp_w)
{
    char* str_thisbox_pre;
    char str_thisbox[MAX_LINE_LENGTH];
    memset(str_thisbox, '\0', sizeof(str_thisbox));
    char* str_linux_first = "   <text x=\"320\" y=\"130\">";
    char* str_linux_last = "</text>";
    str_thisbox_pre = search_first_string(obj, "Linux");
    char* cpus = get_cpus_from_string(str_thisbox_pre);
    terminate_string(str_thisbox_pre, 3, " ");
    snprintf(str_thisbox, MAX_LINE_LENGTH, "%s%s %s%s%s\n", str_linux_first, str_thisbox_pre,
        cpus, " CPU All ", str_linux_last);
    fprintf(fp_w, "%s", str_thisbox);
}

void create_svg_file(node2** obj, char* item, FILE* fp_w)
{
    /* bubble sort svg obj */
    char* str_svg[20000] = { NULL };
    memset(str_svg, '\0', sizeof(str_svg));
    double size = bubble_sort_object_by_the_string2(str_svg, obj);
    /* end bubble sort svg obj */
    double horizontal_notch = 1000/size;
    double width = 10.0;
    char str_svg_draw[200000];
    memset(str_svg_draw, '\0', sizeof(str_svg_draw));
    if (strcmp(item, "cpu_usr") == 0) {
        strncat(str_svg_draw, "  <path stroke=\"green\" fill=\"none\" d=\"M 10 110 L " , 200000 - 1);
    } else if (strcmp(item, "cpu_sys") == 0) {
        strncat(str_svg_draw, "  <path stroke=\"blue\" fill=\"none\" d=\"M 10 110 L " , 200000 - 1);
    } else if (strcmp(item, "cpu_iowait") == 0) {
        strncat(str_svg_draw, "  <path stroke=\"red\" fill=\"none\" d=\"M 10 110 L " , 200000 - 1);
    } else if (strcmp(item, "cpu_idle") == 0) {
        strncat(str_svg_draw, "  <path stroke=\"orange\" fill=\"none\" d=\"M 10 10 L " , 200000 - 1);
    }
    char str_horizontal_notch[256];
    memset(str_horizontal_notch, '\0', sizeof(str_horizontal_notch));
    char str_hundred[4];
    char str_fifty[3];
    char str_zero[2];
    char str_hight[256];
    char str_date[256];
    char str_date_only[256];
    char str_date_only_pre[256];
    char str_time_only[512];
    memset(str_hundred, '\0', sizeof(str_hundred));
    memset(str_fifty, '\0', sizeof(str_fifty));
    memset(str_zero, '\0', sizeof(str_zero));
    memset(str_hight, '\0', sizeof(str_hight));
    memset(str_date, '\0', sizeof(str_date));
    memset(str_date_only, '\0', sizeof(str_date_only));
    memset(str_date_only_pre, '\0', sizeof(str_date_only_pre));
    memset(str_time_only, '\0', sizeof(str_time_only));
    double j = 0.0;
    for(int i=0; i<size; i++) {
        if (strstr(str_svg[i], "CPU All")) {
            width = width + horizontal_notch;
            snprintf(str_horizontal_notch, MAX_FILE_NAME_LENGTH, "%f ", width);
            strncat(str_svg_draw, str_horizontal_notch, 200000 - 1);
            snprintf(str_hight, MAX_FILE_NAME_LENGTH, "%s ", get_sar_value_from_string(str_svg[i]));
            snprintf(str_date, MAX_FILE_NAME_LENGTH, "%s ", get_date_from_string(str_svg[i]));
            snprintf(str_date_only_pre, MAX_FILE_NAME_LENGTH, "%s ", terminate_string(str_date, 2, ","));
            snprintf(str_date_only, MAX_FILE_NAME_LENGTH, "%s ", terminate_string(str_date, 1, ","));
            snprintf(str_time_only, MAX_FILE_NAME_LENGTH, "%s ", get_str_from_string(str_date_only_pre, 1, ","));
            strncat(str_svg_draw, str_hight, 200000 - 1);
            if (strcmp(item, "cpu_usr") == 0) {
                if (j == 0.0) {
                    file_write_svg(item, str_svg_draw, 0, width, fp_w); 
                    // start date and time
                    file_write_date_svg(item, str_date_only, 0, width, "start", fp_w); 
                    // percentage string 
                    fprintf(fp_w, "%s\n", "   <text x=\"0\" y=\"10\">100</text>");
                    fprintf(fp_w, "%s\n", "   <text x=\"00\" y=\"60\">50</text>");
                    fprintf(fp_w, "%s\n", "   <text x=\"0\" y=\"110\">0</text>");
                    file_write_time_svg(item, str_time_only, 0, width, "start", fp_w); 
                }
            }
            j = j + 1.0;
        }           
    }
    // end date and time
    file_write_date_svg(item, str_date_only, 0, width, "end", fp_w); 
    file_write_time_svg(item, str_time_only, 0, width, "end", fp_w); 
    strncat(str_svg_draw, "\"/>", 200000 - 1);
    fprintf(fp_w, "%s\n", str_svg_draw);
    if (strcmp(item, "cpu_idle") == 0) {
        fprintf(fp_w, "%s\n", "<g font-family=\"sans-serif\" fill=\"black\" font-size=\"10\">");
        fprintf(fp_w, "%s\n", "   <text x=\"10\" y=\"140\" fill=\"green\">green cpu_usr</text>");
        fprintf(fp_w, "%s\n", "   <text x=\"10\" y=\"155\" fill=\"blue\">blue cpu_sys</text>");
        fprintf(fp_w, "%s\n", "   <text x=\"90\" y=\"140\" fill=\"red\">red cpu_iowait</text>");
        fprintf(fp_w, "%s\n", "   <text x=\"90\" y=\"155\" fill=\"orange\">orange cpu_idle</text>");
        write_linux_line_to_file(&line_all_obj, fp_w);
        fprintf(fp_w, "%s\n", "   <text x=\"900\" y=\"155\">Powered by saj.</text>");
        fprintf(fp_w, "%s\n", "</g>");
        fprintf(fp_w, "%s\n", "</svg>");
    }
}


int delete_files(void)
{
    sos_file_all_write = get_sos_file_name_to_be_written();
    for (int i = 0; i < file_part; i++) {
        char sos_file_all_write_tmp[MAX_FILE_NAME_LENGTH];
        snprintf(sos_file_all_write_tmp, MAX_LINE_LENGTH - 1, "%s_%d", sos_file_all_write, i);
        unlink(sos_file_all_write_tmp);
    }
    unlink(sos_file_all_write);
    unlink(get_sos_analyze_file_name_to_be_written());
    unlink(log_file_write);
    return 0;
}
