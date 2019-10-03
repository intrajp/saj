/*
 *  cmp-saj.c - compare functions 
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

#include <unistd.h> /* should be above for declaring macro */
#include <sys/stat.h>
#include <sys/types.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>
#include <errno.h>
#include "../libsaj-sosreport-analyzer/line_data.h"

/* sos_cmp_1_obj */
struct line_data sos_cmp_1_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* sos_cmp_2_obj */
struct line_data sos_cmp_2_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* sos_cmp_3_obj */
struct line_data sos_cmp_3_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

struct line_data* sos_cmp_1_obj = &sos_cmp_1_obj_raw;
struct line_data* sos_cmp_2_obj = &sos_cmp_2_obj_raw;
struct line_data* sos_cmp_3_obj = &sos_cmp_3_obj_raw;

static void __delete_obj(void) 
{
    if (sos_cmp_1_obj != NULL) 
        clear_list(&sos_cmp_1_obj); 
    if (sos_cmp_2_obj != NULL) 
        clear_list(&sos_cmp_2_obj); 
    if (sos_cmp_3_obj != NULL) 
        clear_list(&sos_cmp_3_obj); 
}

/* brief Print help for this application */
static void __print_help(void)
{
    printf("\n VERSION %d.%d.%d\n", PROGRAM_VERSION, PROGRAM_RELEASE, PROGRAM_SUB_RELEASE);
    puts("\n Usage:\n");
    puts("   cmp-saj <file-a> <file-b> <item>");
    puts("   These items are valid.");
    puts("   samba, resolv.conf, networkmanager, route, ifcfg, kerb5.conf");
    puts("   Ex. cmp-saj <file-a> <file-b> resolv.conf\n");
}

static int __cmp_obj(node** obj_1, node** obj_2, node** obj_3) 
{
    node* ptr_tmp_1 = *obj_1;
    node* ptr_tmp_2 = *obj_2;
    int differences = 0;
    int list_cmp = 0;
    int list_1 = 0;
    int list_2 = 0;
    int list_max = 500;
    char arr_1[list_max][MAX_LINE_LENGTH];
    char arr_2[list_max][MAX_LINE_LENGTH];
    for (int i = 0; i< list_max; i++) {
        memset(arr_1[i], '\0', sizeof(arr_1[i])); 
        memset(arr_2[i], '\0', sizeof(arr_2[i])); 
    }
    while (ptr_tmp_1 != NULL) {
        strncpy((char *)arr_1[list_1], ptr_tmp_1->_line, MAX_LINE_LENGTH -1);
        list_1++;
        if (list_1 > list_max)
            break;
        ptr_tmp_1 = ptr_tmp_1->next;
    }
    while (ptr_tmp_2 != NULL) {
        strncpy((char*)arr_2[list_2], ptr_tmp_2->_line, MAX_LINE_LENGTH -1);
        list_2++;
        if (list_2 > list_max)
            break;
        ptr_tmp_2 = ptr_tmp_2->next;
    }
    if (list_1 < list_2)
        list_cmp = list_2;
    else
        list_cmp = list_1;
    char result_tmp_1[MAX_LINE_LENGTH]; 
    memset(result_tmp_1, '\0', sizeof(result_tmp_1)); 
    char result_tmp_2[MAX_LINE_LENGTH]; 
    memset(result_tmp_2, '\0', sizeof(result_tmp_2)); 
    for (int i = 0; i < list_cmp; i++) {
        if (strcmp((char*)arr_1[i],(char*)arr_2[i]) != 0) {
            if (strcmp(arr_1[i], "") == 0)
                snprintf(result_tmp_1, MAX_LINE_LENGTH - 1,"file_a:%s", "\n");
            else
                snprintf(result_tmp_1, MAX_LINE_LENGTH - 1,"file_a:%s", (char *)arr_1[i]);
            if (strcmp(arr_2[i], "") == 0)
                snprintf(result_tmp_2, MAX_LINE_LENGTH - 1,"file_b:%s", "\n");
            else
                snprintf(result_tmp_2, MAX_LINE_LENGTH - 1,"file_b:%s", (char *)arr_2[i]);
            append_list(obj_3, result_tmp_1);
            append_list(obj_3, result_tmp_2);
            differences++;
        }
    }
    puts("----------------");
    if (differences == 0)
        puts("There are no differences on these files.");
    else
        puts("There are differences on these files.");
    if (ptr_tmp_1 != NULL) 
        clear_list(&ptr_tmp_1); 
    if (ptr_tmp_2 != NULL) 
        clear_list(&ptr_tmp_2); 
    return 0;
}

static int __append_list_item_lines(node** obj, FILE* fp, const char* item) 
{
    int print_go = 0;
    char linebuf[MAX_LINE_LENGTH];
    char* hairline = "########";
    while (fgets(linebuf, sizeof(linebuf), fp) != NULL) {
        if (strcmp(item, "samba") == 0) {
            if (strstr(linebuf, "config setting is etc/samba/") != NULL )
                print_go = 1;
            if (strstr(linebuf, "config setting is sos_commands/samba/") != NULL )
                print_go = 2;
            if ((print_go == 2) && (strstr(linebuf, hairline) != NULL )) {
                print_go = 3;
                break;
            }
        }
        else if (strcmp(item, "resolv.conf") == 0) {
            if (strstr(linebuf, "config setting is etc/resolv.conf") != NULL )
                print_go = 1;
            if ((print_go == 1) && (strstr(linebuf, hairline) != NULL )) {
                print_go = 3;
                break;
            }
        }
        else if (strcmp(item, "networkmanager") == 0) {
            if (strstr(linebuf, "config setting is etc/NetworkManager/") != NULL )
                print_go = 1;
            if (strstr(linebuf, "config setting is sos_commands/networkmanager/") != NULL )
                print_go = 2;
            if ((print_go == 2) && (strstr(linebuf, hairline) != NULL )) {
                print_go = 3;
                break;
            }
        }
        else if (strcmp(item, "route") == 0) {
            if (strstr(linebuf, "config setting is route") != NULL )
                print_go = 1;
            if ((print_go == 1) && (strstr(linebuf, hairline) != NULL )) {
                print_go = 3;
                break;
            }
        }
        else if (strcmp(item, "ifcfg") == 0) {
            if (strstr(linebuf, "config setting is etc/sysconfig/network-scripts/ifcfg") != NULL )
                print_go = 1;
            if ((print_go == 1) && (strstr(linebuf, hairline) != NULL )) {
                print_go = 3;
                break;
            }
        }
        else if (strcmp(item, "krb5.conf") == 0) {
            if (strstr(linebuf, "config setting is etc/krb5.conf") != NULL )
                print_go = 1;
            if ((print_go == 1) && (strstr(linebuf, hairline) != NULL )) {
                print_go = 3;
                break;
            }
        }
        if ((print_go == 1) || (print_go == 2)) {
            printf("%s", linebuf);
            append_list(obj, linebuf);
        }
    }
    return 0;
}

static FILE* file_open_check(FILE* fp, const char* file_name, const char* mode) 
{
    fp = NULL;
    if ((fp = fopen(file_name, mode)) == NULL) {
        fprintf(stderr, "can't open file (%s): %s\n", file_name, strerror(errno));
        __delete_obj();
        exit(EXIT_FAILURE);
    }
    return fp;
}

static int __read_file_cmp(const char* file_name1, const char* file_name2, const char* item) 
{
    FILE* fp_a = NULL;
    FILE* fp_b = NULL;
    FILE* fp_a_w = NULL;
    FILE* fp_b_w = NULL;
    const char* file_a_w = "file_a";
    const char* file_b_w = "file_b";
    fp_a = file_open_check(fp_a, file_name1, "r");
    fp_b = file_open_check(fp_b, file_name2, "r");
    fp_a_w = file_open_check(fp_a_w, file_a_w, "w");
    fp_b_w = file_open_check(fp_b_w, file_b_w, "w");
    init_list(&sos_cmp_1_obj);
    init_list(&sos_cmp_2_obj);
    init_list(&sos_cmp_3_obj);
    __append_list_item_lines(&sos_cmp_1_obj, fp_a, item); 
    __append_list_item_lines(&sos_cmp_2_obj, fp_b, item); 
    file_write_list_(&sos_cmp_1_obj, fp_a_w);
    file_write_list_(&sos_cmp_2_obj, fp_b_w);
    __cmp_obj(&sos_cmp_1_obj, &sos_cmp_2_obj, &sos_cmp_3_obj);
    fclose(fp_a);
    fclose(fp_b);
    fclose(fp_a_w);
    fclose(fp_b_w);
    return 0;
}

/* Main function */
int main(int argc, char* argv[])
{
    char value = 0;
    while(1) {
        int option_index = 0;
        static struct option long_options[] = {
            {"help", no_argument, 0, 'h'},
            {NULL, 0, 0, 0}
        };
        char str_tmp[MAX_LINE_LENGTH]; 
        memset(str_tmp, '\0', sizeof(str_tmp)); 
        value = getopt_long(argc, argv, "h", long_options, &option_index);
        if (value == -1)
            break;
        switch(value) {
            case 'h':
              __print_help();
                return 0;
                break;
            case '?':
              __print_help();
                return 0;
                break;
            default:
              __print_help();
                return 0;
                break;
        }
    }
    if (argv[3] == NULL || ((! strcmp(argv[3], "samba") == 0) &&
        (! strcmp(argv[3], "resolv.conf") == 0) &&
        (! strcmp(argv[3], "networkmanager") == 0) &&
        (! strcmp(argv[3], "route") == 0) &&
        (! strcmp(argv[3], "ifcfg") == 0) &&
        (! strcmp(argv[3], "krb5.conf") == 0))) {
        __print_help();
        return 0;
    }
    __read_file_cmp(argv[1], argv[2], argv[3]);
    const char* cmp_file_sosreport_analyzer = "cmp_file_sosreport_analyzer.txt";
    FILE* fp_w;
    unlink(cmp_file_sosreport_analyzer);
    fp_w = file_open_check(fp_w, cmp_file_sosreport_analyzer, "a");
    file_write_list_(&sos_cmp_3_obj, fp_w);
    fclose(fp_w);
    puts("----------------");
    puts("Results are written in file_a, file_b");
    puts("So, you can diff 2 files.\n");
    printf("Also check %s\n\n", cmp_file_sosreport_analyzer);
    __delete_obj();
    return 0;
}
