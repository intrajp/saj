/*
 * sar_analyzer.c - analyzing functions 
 * This file contains the contents of saj.
 *
 * Copyright (C) 2019 Shintaro Fujiwara
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301 USA
 */

/* how to convert sa to sar file
 * example:
 * LC_ALL=C sar -f sa01 -A -t > ./sar01
 *
 * how to remove ^@
 * sed -i 's/\x00//g' <sar01>
 */

/*
 * Program Sequence
 *
 * 1. main() <------> 2. sar_analyzer_init() <--> 3. create_sar_analyzer_obj() 
 *       ^                     ^
 *       |                     |
 *       v                     |
 * 15. file_to_write()         |
 * 16. print_list()            |
 * 17. file_write_list()       |
 * 18. print_and_file_write_analyzed_files ()
 * 19. free_sar_analyzer_obj() |
 *                             |
 *                             v
 * 4.read_sa_dir() <--> 5. read_write_file() --> 13. read_sar_cpu_as_paragraph() --> 14. make_report()
 *                             ^
 *                             |
 *                             v
 * 6. read_sar_check() <--> 7. sanity_check_file()
 *                             ^
 *                             |
 * 8. read_sar()
 *                             |
 *                ------------>+
 *                |            |
 *                |            v 
 *                |   9. get_word_line() <--> 10. initialize_check_int()
 *                |            ^
 *                |            |
 *                |            v 
 *                |   11. set_token_column()
 *                |             
 *                |-----> 12. set_token_items() 
 * 
 * setter and getter functions are also be used.
 * free_sar_analyzer_obj() will be called when error.
 * line_data object will be manipulated by functions related.
 */

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <limits.h>
#include "sar_analyzer.h"
#include "setter_getter.h"

int linux_restart_count[MAX_ANALYZE_FILES]= {0};

void initialize_check_int(void)
{
    CHK_CORES_N = 0;
    SHOW_AVG = 1;
    CHECK_CPU_EACH = 0;
    CHK_A = 0x00000000;
    CHK_Z = 0x00000000;
}

int set_token_column(int file_number, char *line, const char *item_name_for_column,
    int restart, int SAR_OPTION)
{
    const char s[4]= " \t"; /* this is the delimiter */
    char *token = ""; /* line would be set into this variable in while loop */
    char buff[50];
    int i = 0, ii = 0;
    int PM = 0;
    /* initialize the string array (this is needed) */
    for (ii = 0; ii < MAX_DATE_STRINGS; ii++)
        sar_analyzer_obj->title_strings[i][ii]= '\0';
    memset(buff, '\0', sizeof(buff));

    /* get the first token */
    token = strtok(line, s);
    /* walk throuth other tokens and set into struct what's needed */
    while (token != NULL) {
        /* this part, set the  title string as char array and date information to the struct member */
        if (strcmp(item_name_for_column, "Linux") == 0) {
            /*  setting hostname */
            if ((strstr(token, "(") != NULL) &&(strstr(token, ")") != NULL))
                set_hostname(token);
            /*  setting file title */
            /*  this clause is not used anywhere anymore i guess */
            if (restart == 0) {
                /*  setting file title of first file */
                if (file_number== 1)
                    set_title_strings_first_file(i, token);
                /*  setting file title each time except first file */
                else
                    set_title_strings(i, token);
            }

            strncpy(buff, token, 10);

            /* we want to know former date*/
            char str_date_former[MAX_DATE_STRINGS];
            char str_date_all_former[MAX_DATE_STRINGS];
            char str_date_all_former2[MAX_DATE_STRINGS];
            memset(str_date_former, '\0', sizeof(str_date_former));
            memset(str_date_all_former, '\0', sizeof(str_date_all_former));
            memset(str_date_all_former2, '\0', sizeof(str_date_all_former2));

            /* if it was the date stging set into the struct */
            if (
               ((buff[0]== '2') &&(buff[1]== '0') &&(buff[4]== '-')) ||
               ((buff[0]== '1') &&(buff[1]== '9') &&(buff[4]== '-')) ||
               ((buff[2]== '/') &&(buff[5]== '/'))
            ) {
                if (SAR_OPTION == 'Z') {
                    strncpy(str_date_all_former, get_this_date_all(), MAX_DATE_STRINGS -1);
                    set_this_date_all_former(str_date_all_former);
                    set_this_date_all(token);
                } else {
                    strncpy(str_date_former, get_this_date(), MAX_DATE_STRINGS -1);
                    set_this_date_former(str_date_former);
                    set_this_date(token);
                }
            }
        }
        /* if AM or PM will appear, column number should be decremented, unless, segfault in set_column_item() */
        if (SAR_OPTION != 'Z') {
            if ((strstr(token, "AM") != NULL) || (strstr(token, "PM") != NULL))
                i--;
        }
        /* this item name is set by get_word_line() */
        if (strcmp(item_name_for_column, "cpu") == 0) {
            if (strstr(token, "CPU") != NULL) {
                set_column_cpu(i, "CPU");
            } else if ((strstr(token, "%usr") != NULL) ||(strstr(token, "%user") != NULL)) {
                set_column_cpu(i, "usr");
            } else if ((strstr(token, "%sys") != NULL) ||(strstr(token, "%system") != NULL)) {
                set_column_cpu(i, "sys");
            } else if (strstr(token, "%iowait") != NULL) {
                set_column_cpu(i, "iowait");
            } else if (strstr(token, "%idle") != NULL) {
                set_column_cpu(i, "idle");
            }
        /* this item name is set by get_word_line() */
        } else if (strcmp(item_name_for_column, "proc") == 0) {
            if (strstr(token, "proc") != NULL) {
                set_column_tasks(i, "proc");
            } else if (strstr(token, "cswch") != NULL) {
                set_column_tasks(i, "cswch");
            }
        /* this item name is set by get_word_line() */
        } else if (strcmp(item_name_for_column, "pswpin/s") == 0) {
            if ((strstr(token, "pswpin") != NULL)) {
                set_column_pswap(i, "pswpin");
            } else if ((strstr(token, "pswpout") != NULL)) {
                set_column_pswap(i, "pswpout");
            }
        /* this item name is set by get_word_line() */
        } else if (strcmp(item_name_for_column, "fault") == 0) {
            if (strstr(token, "pgpgin") != NULL) {
                set_column_paging(i, "pgpgin");
            } else if (strstr(token, "pgpgout") != NULL) {
                set_column_paging(i, "pgpgout");
            } else if (strstr(token, "fault") != NULL) {
                set_column_paging(i, "fault");
            } else if (strstr(token, "majflt") != NULL) {
                set_column_paging(i, "majflt");
            } else if (strstr(token, "vmeff") != NULL) {
                set_column_paging(i, "vmeff");
            }
        /* this item name is set by get_word_line() */
        } else if (strcmp(item_name_for_column, "bread/s") == 0) {
            if ((strstr(token, "tps") != NULL) && (strstr(token, "rtps") == NULL) && (strstr(token, "wtps") == NULL) && (strstr(token, "dtps") == NULL)) {
                set_column_io_transfer_rate(i, "tps");
            } else if (strstr(token, "bread") != NULL) {
                set_column_io_transfer_rate(i, "bread");
            } else if (strstr(token, "bwrtn") != NULL) {
                set_column_io_transfer_rate(i, "bwrtn");
            }
        /* this item name is set by get_word_line() */
        } else if (strcmp(item_name_for_column, "kbmemfree") == 0) {
            if (strstr(token, "memused") != NULL) {
                set_column_memory(i, "memused");
            } else if (strstr(token, "kbcommit") != NULL) {
                set_column_memory(i, "kbcommit");
            } else if (strstr(token, "commit") != NULL) {
                set_column_memory(i, "commit");
            }
        /* this item name is set by get_word_line() */
        } else if (strcmp(item_name_for_column, "kbswpfree") == 0) {
            if ((strstr(token, "swpused") != NULL)) {
                set_column_swpused(i);
            }
        /* this item name is set by get_word_line() */
        } else if (strcmp(item_name_for_column, "dentunusd") == 0) {
            if ((strstr(token, "dentunusd") != NULL)) {
                set_column_kernel_table(i, "dentunusd");
            } else if ((strstr(token, "file") != NULL)) {
                set_column_kernel_table(i, "file");
            } else if ((strstr(token, "inode") != NULL)) {
                set_column_kernel_table(i, "inode");
            }
        /* this item name is set by get_word_line() */
        } else if (strcmp(item_name_for_column, "runq") == 0) {
            if (strstr(token, "runq-sz") != NULL) {
                set_column_ldavg(i, "runq_sz");
            } else if (strstr(token, "plist-sz") != NULL) {
                set_column_ldavg(i, "plist_sz");
            } else if ((strstr(token, "ldavg-1") != NULL) &&(strstr(token, "ldavg-15") == 0)) {
                set_column_ldavg(i, "ldavg_one");
            } else if (strstr(token, "ldavg-5") != NULL) {
                set_column_ldavg(i,"ldavg_five");
            } else if (strstr(token, "ldavg-15") != NULL) { 
                set_column_ldavg(i, "ldavg_15");
            }
        /* this item name is set by get_word_line() */
        } else if (strcmp(item_name_for_column, "DEV") == 0) {
            if ((strstr(token, "areq-sz") != NULL) ||(strstr(token, "avgrq-sz") != NULL)) {
                set_column_block_device(i, "areqsz");
            } else if (strstr(token, "util") != NULL) {
                set_column_block_device(i, "util");
            }
        /* this item name is set by get_word_line() */
        } else if (strcmp(item_name_for_column, "rxpck") == 0) {
            if ((strstr(token, "rxpck") != NULL)) {
                set_column_network(i, "rxpck");
            } else if ((strstr(token, "txpck") != NULL)) {
                set_column_network(i, "txpck");
            } else if ((strstr(token, "rxkB") != NULL)) {
                set_column_network(i, "rxkb");
            } else if ((strstr(token, "txkB") != NULL)) {
                set_column_network(i, "txkb");
            }
        /* this item name is set by get_word_line() */
        } else if (strcmp(item_name_for_column, "rxerr") == 0) {
            if ((strstr(token, "rxerr") != NULL)) {
                set_column_network(i, "rxerr");
            } else if ((strstr(token, "txerr") != NULL)) {
                set_column_network(i, "txerr");
            } else if ((strstr(token, "rxdrop") != NULL)) {
                set_column_network(i, "rxdrop");
            } else if ((strstr(token, "txdrop") != NULL)) {
                set_column_network(i, "txdrop");
            }
        }
        token = strtok(NULL, s);
        i++;
    }
    if (PM == 1)
        return 1;
    else
        return 0;
}

double check_time_value(double initial_val, double horizontal_notch, int count,
    char *time_value)
{
    const char s[2]= ":"; /* this is the delimiter */
    int l=0, x = 0, y = 0, z = 0;
    char *token = NULL;
    /* get the first token */
    token = strtok(time_value, s);
    while (token != NULL) {
        if (l == 0) {
            if (strcmp("00", token) == 0)
                x = 0;
            else if (strcmp("01", token) == 0)
                x = 6 * 1;
            else if (strcmp("02", token) == 0)
                x = 6 * 2;
            else if (strcmp("03", token) == 0)
                x = 6 * 3;
            else if (strcmp("04", token) == 0)
                x = 6 * 4;
            else if (strcmp("05", token) == 0)
                x = 6 * 5;
            else if (strcmp("06", token) == 0)
                x = 6 * 6;
            else if (strcmp("07", token) == 0)
                x = 6 * 7;
            else if (strcmp("08", token) == 0)
                x = 6 * 8;
            else if (strcmp("09", token) == 0)
                x = 6 * 9;
            else if (strcmp("10", token) == 0)
                x = 6 * 10;
            else if (strcmp("11", token) == 0)
                x = 6 * 11;
            else if (strcmp("12", token) == 0)
                x = 6 * 12;
            else if (strcmp("13", token) == 0)
                x = 6 * 13;
            else if (strcmp("14", token) == 0)
                x = 6 * 14;
            else if (strcmp("15", token) == 0)
                x = 6 * 15;
            else if (strcmp("16", token) == 0)
                x = 6 * 16;
            else if (strcmp("17", token) == 0)
                x = 6 * 17;
            else if (strcmp("18", token) == 0)
                x = 6 * 18;
            else if (strcmp("19", token) == 0)
                x = 6 * 19;
            else if (strcmp("20", token) == 0)
                x = 6 * 20;
            else if (strcmp("21", token) == 0)
                x = 6 * 21;
            else if (strcmp("22", token) == 0)
                x = 6 * 22;
            else if (strcmp("23", token) == 0)
                x = 6 * 23;
            else
                x = -1;
        } else if (l == 1) {
            if (strcmp("00", token) == 0)
                y = 0;
            else if (strcmp("10", token) == 0)
                y = 1;
            else if (strcmp("20", token) == 0)
                y = 2;
            else if (strcmp("30", token) == 0)
                y = 3;
            else if (strcmp("40", token) == 0)
                y = 4;
            else if (strcmp("50", token) == 0)
                y = 5;
            else
                y = -1;
    }
    token = strtok(NULL, s);
        l++;
    }

    if ((x == -1) ||(y == -1))
        z = count;
    else
        z = x + y;
    return (initial_val + horizontal_notch * z);
}

static void set_pm_to_abs_time(char *time_value)
{
    if ((time_value[0]== '0') &&
        (
          (time_value[1]== '1') ||
          (time_value[1]== '2') ||
          (time_value[1]== '3') ||
          (time_value[1]== '4') ||
          (time_value[1]== '5') ||
          (time_value[1]== '6') ||
          (time_value[1]== '7')
        )
      ) {
        time_value[0]= '1';
        if (time_value[1]== '1')
            time_value[1]= '3';
        else if (time_value[1]== '2')
            time_value[1]= '4';
        else if (time_value[1]== '3')
            time_value[1]= '5';
        else if (time_value[1]== '4')
            time_value[1]= '6';
        else if (time_value[1]== '5')
            time_value[1]= '7';
        else if (time_value[1]== '6')
            time_value[1]= '8';
        else if (time_value[1]== '7')
            time_value[1]= '9';
    } else if ((time_value[0]== '0') &&
              (
               (time_value [1]== '8') ||
               (time_value [1]== '9')
             )
           ) {
        time_value[0]= '2';
        if (time_value[1]== '8')
            time_value[1]= '0';
        else if (time_value[1]== '9')
            time_value[1]= '1';
    } else if ((time_value[0]== '1') &&(time_value[1]== '0')) {
        time_value[0]= '2';
        time_value[1]= '2';
    } else if ((time_value[ 0 ]== '1') &&(time_value[1]== '1')) {
        time_value[0]= '2';
        time_value[1]= '3';
    }
}

int set_token_items(int file_number, char **line, const char *item_name, int utility, int SAR_OPTION, const char *time_span, int PM)
{
    char this_date_all[MAX_DATE_STRINGS];
    memset(this_date_all, '\0', MAX_DATE_STRINGS); 
    char this_date[MAX_DATE_STRINGS];
    memset(this_date, '\0', MAX_DATE_STRINGS); 
    const char s[4]= "  \t"; /* this is the delimiter */
    char *endp;
    int i = 0, network_device_setter = 0;
    int set_to_struct = 1; /* set 0 when setting values to the struct */
    char *token = NULL;
    char time_value[20]= {'\0'};

    double t2 = 0, t3 = 0, t4 = 0;
    double t = 0, h = 0, l = 0; /* means this value, highest value, lowest value */
    double h0 = 0, h1 = 0, h2 = 0, h3 = 0, h4 = 0, l0 = 0, l1 = 0, l2 = 0, l3 = 0, l4 = 0; /* highest value, lowest value for Z option */
    double s0 = 0, s1 = 0, s2 = 0, s3 = 0, s4 = 0, f0 = 0, f1 = 0, f2 = 0, f3 = 0, f4 = 0; /* spike value, former value for Z option */
    double ss0 = 0, ss1 = 0, ss2 = 0, ss3 = 0, ss4 = 0, ff0 = 0, ff1 = 0, ff2 = 0, ff3 = 0, ff4 = 0; /* spike each file value for Z option */
    double hh0 = 0, hh1 = 0, hh2 = 0, hh3 = 0, hh4 = 0, ll0 = 0, ll1 = 0, ll2 = 0, ll3 = 0, ll4 = 0; /* spike each file value for Z option */
    double t_ss0 = 0, t_ss1 = 0, t_ss2 = 0, t_ss3 = 0, t_ss4 = 0, t_ff0 = 0, t_ff1 = 0, t_ff2 = 0, t_ff3 = 0, t_ff4 = 0; /* time-span spike each file value for Z option */
    double t_hh0 = 0, t_hh1 = 0, t_hh2 = 0, t_hh3 = 0, t_hh4 = 0, t_ll0 = 0, t_ll1 = 0, t_ll2 = 0, t_ll3 = 0, t_ll4 = 0; /* time-span spike each file value for Z option */
    int time_span_checked = 0;

    /* get the first token */
    token = strtok(*line, s);
    /* this should be the first token, which is time value, so, copying time value to variable for the future use */
    strncpy(time_value, token, 19);
    /* converting am-pm style to abs style */ 
    if (PM == 1)
        set_pm_to_abs_time(time_value);
    if (time_span != NULL)
        time_span_checked = check_time_value_is_in_time_span (time_span,time_value);

    /* set time_value and its former value here */
    char str_time_former[MAX_DATE_STRINGS];
    memset(str_time_former, '\0', sizeof(str_time_former));

    /* if second field (column) are not these, set time value and its former value to the struct */
    if (SAR_OPTION == 'Z') {
        strncpy(str_time_former, get_this_time_all(), MAX_DATE_STRINGS -1);
        set_this_time_all_former(str_time_former);
        set_this_time_all(time_value);
    } else {
        strncpy(str_time_former, get_this_time(), MAX_DATE_STRINGS -1);
        set_this_time_former(str_time_former);
        set_this_time(time_value);
    }

    i++;
    /* walk throuth other tokens */
    while (token != NULL) {
        /* get this date for this loop */
        strncpy(this_date_all, get_this_date_all(), MAX_DATE_STRINGS - 1);
        strncpy(this_date, get_this_date(), MAX_DATE_STRINGS - 1);

        token = strtok(NULL, s);
        if (token == NULL)
            break;
        if (i == 1) {
            const char* cpu_check_str = "";
            if (SAR_OPTION == 'Z')
                cpu_check_str = "CPU";
            else 
                cpu_check_str = "all";
            /* if second field (column) are these, set set_to_struct to 0 and ready to set item values to the struct */
            if ((!strcmp(token, cpu_check_str)) ||(!strstr(token, "runq")) || 
               (!strstr(token, "proc")) ||(!strstr(token, "fault")) || 
               (!strstr(token, "kbmemfree")) ||(!strstr(token, "tps")) ||
               (!strstr(token, "DEV")) ||(!strstr(token, "kbswpfree")) || 
               (!strstr(token, "pswpin")) || 
               (!strstr(token, "dentunusd")) ||(!strstr(token, "rxpck")) || 
               (!strstr(token, "rxerr"))) {
                set_to_struct = 0;
            }
        }        

        /* At this point, argument 'utility' is definitely a wrong value because devices are easily attached or released,
         * Imagine some devices were attached and left several days and pulled off. sar will record those devices and
         * the record will become inconsistent to be analyzed.
         * So, we discard argument 'utility' here and search if device name already exists in the object.
         * If not, adding device name in the hope to set sane values for each device below.
         * After that, we set 'utility' the sane number as an array element number to accomodate token value for the struct to be set.
         *
         * **** Note that we use if, if in setting highest and lowest ****
         *
         */
        /* setting block device names and setting utility the proper array element number */
        if (!strcmp(item_name, "DEV") && ((strstr(token, "dev")) || (strstr(token, "sd")) ||
            (strstr(token, "sr")) || (strstr(token, "ram")) || (strstr(token, "dm")))) {
            set_block_device_names(token);
            utility = search_block_device_name(token);
        /* setting network device names and setting utility the proper array element number */
        } else if (!strcmp(item_name, "rxpck") && ((strstr(token, "lo")) ||(strstr(token, "eth")) ||(strstr(token, "brq")) ||
           (strstr(token, "en")) ||(strstr(token, "vir")) ||(strstr(token, "wl"))  ||(strstr(token, "tap")) ||
           (strstr(token, "docker")) ||(strstr(token, "bond")) ||(strstr(token, "team")))) {
            set_network_device_names(token);
            network_device_setter = 1;
            utility = search_network_device_name(token);
        /* network device names are already set with above, so just utilize it to get array element number */
        } else if (!strcmp(item_name, "rxerr") &&((strstr(token, "lo")) ||(strstr(token, "eth")) ||(strstr(token, "brq")) ||
           (strstr(token, "en")) ||(strstr(token, "vir")) ||(strstr(token, "wl")) ||(strstr(token, "tap")) ||
           (strstr(token, "docker")) ||(strstr(token, "bond")) ||(strstr(token, "team")))) {
            /* this is needed if -m option is called */
            if (network_device_setter == 0)
                set_network_device_names(token);
            utility = search_network_device_name(token);
        /* ---- end utility things ---- */

        /* setting values when 'all' and below line */
        } else if ((strcmp(item_name, "cpu") == 0) &&(set_to_struct == 0)) {
            s0 = get_cpu_spike_val(utility, "usr");
            f0 = get_cpu_former_val(utility, "usr");
            h0 = get_cpu_highest_val(utility, "usr");
            l0 = get_cpu_lowest_val(utility, "usr");
            s1 = get_cpu_spike_val(utility, "sys");
            f1 = get_cpu_former_val(utility, "sys");
            h1 = get_cpu_highest_val(utility, "sys");
            l1 = get_cpu_lowest_val(utility, "sys");
            s2 = get_cpu_spike_val(utility, "iowait");
            f2 = get_cpu_former_val(utility, "iowait");
            h2 = get_cpu_highest_val(utility, "iowait");
            l2 = get_cpu_lowest_val(utility, "iowait");
            s3 = get_cpu_spike_val(utility, "idle");
            f3 = get_cpu_former_val(utility, "idle");
            h3 = get_cpu_highest_val(utility, "idle");
            l3 = get_cpu_lowest_val(utility, "idle");
            ss0 = get_cpu_spike_val_each_file(file_number, utility, "usr", "spike");
            ss1 = get_cpu_spike_val_each_file(file_number, utility, "sys", "spike");
            ss2 = get_cpu_spike_val_each_file(file_number, utility, "iowait", "spike");
            ss3 = get_cpu_spike_val_each_file(file_number, utility, "idle", "spike");
            ff0 = get_cpu_former_val_each_file(file_number, utility, "usr");
            ff1 = get_cpu_former_val_each_file(file_number, utility, "sys");
            ff2 = get_cpu_former_val_each_file(file_number, utility, "iowait");
            ff3 = get_cpu_former_val_each_file(file_number, utility, "idle");
            hh0 = get_cpu_spike_val_each_file(file_number, utility, "usr", "highest");
            hh1 = get_cpu_spike_val_each_file(file_number, utility, "sys", "highest");
            hh2 = get_cpu_spike_val_each_file(file_number, utility, "iowait", "highest");
            hh3 = get_cpu_spike_val_each_file(file_number, utility, "idle", "highest");
            ll0 = get_cpu_spike_val_each_file(file_number, utility, "usr", "lowest");
            ll1 = get_cpu_spike_val_each_file(file_number, utility, "sys", "lowest");
            ll2 = get_cpu_spike_val_each_file(file_number, utility, "iowait", "lowest");
            ll3 = get_cpu_spike_val_each_file(file_number, utility, "idle", "lowest");
            t_ss0 = get_cpu_time_span_spike_val_each_file(file_number, utility, "usr", "spike");
            t_ss1 = get_cpu_time_span_spike_val_each_file(file_number, utility, "sys", "spike");
            t_ss2 = get_cpu_time_span_spike_val_each_file(file_number, utility, "iowait", "spike");
            t_ss3 = get_cpu_time_span_spike_val_each_file(file_number, utility, "idle", "spike");
            t_ff0 = get_cpu_time_span_former_val_each_file(file_number, utility, "usr");
            t_ff1 = get_cpu_time_span_former_val_each_file(file_number, utility, "sys");
            t_ff2 = get_cpu_time_span_former_val_each_file(file_number, utility, "iowait");
            t_ff3 = get_cpu_time_span_former_val_each_file(file_number, utility, "idle");
            t_hh0 = get_cpu_time_span_spike_val_each_file(file_number, utility, "usr", "highest");
            t_hh1 = get_cpu_time_span_spike_val_each_file(file_number, utility, "sys", "highest");
            t_hh2 = get_cpu_time_span_spike_val_each_file(file_number, utility, "iowait", "highest");
            t_hh3 = get_cpu_time_span_spike_val_each_file(file_number, utility, "idle", "highest");
            t_ll0 = get_cpu_time_span_spike_val_each_file(file_number, utility, "usr", "lowest");
            t_ll1 = get_cpu_time_span_spike_val_each_file(file_number, utility, "sys", "lowest");
            t_ll2 = get_cpu_time_span_spike_val_each_file(file_number, utility, "iowait", "lowest");
            t_ll3 = get_cpu_time_span_spike_val_each_file(file_number, utility, "idle", "lowest");

            /* CPU All and %usr, set the value to struct, us intends 'usr' or 'user'
             * utility is used for core number here 
             */
            if ((i == get_column_cpu("usr")) &&(strstr(token, "us") == 0)) {

                if (SAR_OPTION == 'Z') {
                    t = strtod(token, &endp);
                    if (strstr(time_value, "Average") != NULL)
                        return 0;
                    set_tmp_val(t);
                    t = get_tmp_val();
                    set_tmp2_val(t - ff0);
                    t2 = get_tmp2_val();
                    set_tmp3_val(t - f0);
                    t3 = get_tmp3_val();
                    set_tmp4_val(t - t_ff0);
                    t4 = get_tmp4_val();
                    if (t > INT_MAX || t < 0)
                        return 0;
                    if ((t3 > s0) && (f0 != 0)) {
                        set_cpu_spike_val(t3, utility, "usr");
                        set_cpu_spike_date(this_date_all, utility, "usr");
                        set_cpu_spike_time(time_value, utility, "usr");
                    }
                    set_cpu_former_val(t, utility, "usr");
                    if ((t2 > ss0) && (ff0 != 0)) {
                        set_cpu_spike_val_each_file(file_number, t2, utility, "usr", "spike");
                        set_cpu_spike_date_each_file(file_number, this_date_all, utility, "usr", "spike");
                        set_cpu_spike_time_each_file(file_number, time_value, utility, "usr", "spike");
                    }
                    if (t > hh0) {
                        set_cpu_spike_val_each_file(file_number, t, utility, "usr", "highest");
                        set_cpu_spike_date_each_file(file_number, this_date_all, utility, "usr", "highest");
                        set_cpu_spike_time_each_file(file_number, time_value, utility, "usr", "highest");
                    }
                    if (t < ll0) {
                        set_cpu_spike_val_each_file(file_number, t, utility, "usr", "lowest");
                        set_cpu_spike_date_each_file(file_number, this_date_all, utility, "usr", "lowest");
                        set_cpu_spike_time_each_file(file_number, time_value, utility, "usr", "lowest");
                    }
                    set_cpu_former_val_each_file(file_number, t, utility, "usr");
                    if (time_span_checked == 1) {
                        if ((t4 > t_ss0) && (t_ff0 != 0)) {
                            set_cpu_time_span_spike_val_each_file(file_number, t4, utility, "usr", "spike");
                            set_cpu_time_span_spike_date_each_file(file_number, this_date_all, utility, "usr", "spike");
                            set_cpu_time_span_spike_time_each_file(file_number, time_value, utility, "usr", "spike");
                        }
                        if (t > t_hh0) {
                            set_cpu_time_span_spike_val_each_file(file_number, t, utility, "usr", "highest");
                            set_cpu_time_span_spike_date_each_file(file_number, this_date_all, utility, "usr", "highest");
                            set_cpu_time_span_spike_time_each_file(file_number, time_value, utility, "usr", "highest");
                        }
                        if (t < t_ll0) {
                            set_cpu_time_span_spike_val_each_file(file_number, t, utility, "usr", "lowest");
                            set_cpu_time_span_spike_date_each_file(file_number, this_date_all, utility, "usr", "lowest");
                            set_cpu_time_span_spike_time_each_file(file_number, time_value, utility, "usr", "lowest");
                        }
                        set_cpu_time_span_former_val_each_file(file_number, t, utility, "usr");
                    }
                    if (t > h0) {
                        set_cpu_highest_val(t, utility, "usr");
                        set_cpu_highest_date(this_date_all, utility, "usr");
                        set_cpu_highest_time(time_value, utility, "usr");
                    }
                    if (l0 > t) {
                        set_cpu_lowest_val(t, utility, "usr");
                        set_cpu_lowest_date(this_date_all, utility, "usr");
                        set_cpu_lowest_time(time_value, utility, "usr");
                    }
                    /* code for graph */
                    if ((strstr(time_value, ":00:") != NULL) ||
                        (strstr(time_value, ":10:") != NULL) ||
                        (strstr(time_value, ":20:") != NULL) ||
                        (strstr(time_value, ":30:") != NULL) ||
                        (strstr(time_value, ":40:") != NULL) ||
                        (strstr(time_value, ":50:") != NULL)) {
                        char str_tmp_echo[MAX_LINE_LENGTH - 100] = {'\0'};
                        char str_tmp_echo2[MAX_LINE_LENGTH] = {'\0'};
                        char str_tmp_null[MAX_LINE_LENGTH] = {'\0'};
                        char str_tmp_null2[MAX_LINE_LENGTH + 100] = {'\0'};
                        memset(str_tmp_null, '\0', sizeof(str_tmp_null));
                        memset(str_tmp_null2, '\0', sizeof(str_tmp_null2));
                        memset(str_tmp_echo, '\0', sizeof(str_tmp_echo));
                        memset(str_tmp_echo2, '\0', sizeof(str_tmp_echo2));
                        int difference = 0;
                        snprintf(str_tmp_echo, sizeof(str_tmp_echo), "%f", t);
                        snprintf(str_tmp_null, sizeof(str_tmp_null), "%f", 0.0);
                        if (utility == 0) {
                            snprintf(str_tmp_echo2, sizeof(str_tmp_echo2), "%s,%s,%s,%s,%s", "CPU All", "cpu_usr", this_date_all, time_value, str_tmp_echo);
                            snprintf(str_tmp_null2, sizeof(str_tmp_null2), "%s,%s,%s,%s,%s", "CPU All", "cpu_usr", this_date_all, "", str_tmp_null);
                            difference = check_time_continuity(file_number, (char*)get_this_time_all(), (char*)get_this_time_all_former());
                            // absense of data should be zero
                            if (difference > 1)
                                for(int i=0; i<difference; i++)
                                    append_list2(&svg_cpu_usr_obj, str_tmp_null2, str_tmp_null);
                            else
                                append_list2(&svg_cpu_usr_obj, str_tmp_echo2, str_tmp_echo);
                        }
                    }
                    /* end code for graph */
                } else {
                    t = strtod(token, &endp);
                    h = get_cpu_avg_highest_val(utility, "usr");
                    l = get_cpu_avg_lowest_val(utility, "usr");
                    if (h < t) { 
                        set_cpu_avg_highest_val(t, utility, "usr");
                        set_cpu_avg_highest_date(this_date, utility, "usr");
                    }
                    if (l > t) {
                        set_cpu_avg_lowest_val(t, utility, "usr");
                        set_cpu_avg_lowest_date(this_date, utility, "usr");
                    }
                }
            /* CPU All and %sys, set the value to struct */
            } else if ((i == get_column_cpu("sys")) &&(strstr(token, "%sys") == 0)) {
                if (SAR_OPTION == 'Z') {
                    t = strtod(token, &endp);
                    if (strstr(time_value, "Average") != NULL)
                        return 0;
                    set_tmp_val(t);
                    t = get_tmp_val();
                    set_tmp2_val(t - ff1);
                    t2 = get_tmp2_val();
                    set_tmp3_val(t - f1);
                    t3 = get_tmp3_val();
                    set_tmp4_val(t - t_ff1);
                    t4 = get_tmp4_val();
                    if (t > INT_MAX || t < 0)
                        return 0;
                    if ((t3 > s1) &&(f1 != 0)) {
                        set_cpu_spike_val(t3, utility, "sys");
                        set_cpu_spike_date(this_date_all, utility, "sys");
                        set_cpu_spike_time(time_value, utility, "sys");
                    }
                    set_cpu_former_val(t, utility, "sys");
                    if ((t2 > ss1) &&(ff1 != 0)) {
                        set_cpu_spike_val_each_file(file_number, t2, utility, "sys", "spike");
                        set_cpu_spike_date_each_file(file_number, this_date_all, utility, "sys", "spike");
                        set_cpu_spike_time_each_file(file_number, time_value, utility, "sys", "spike");
                    }
                    if (t > hh1) {
                        set_cpu_spike_val_each_file(file_number, t, utility, "sys", "highest");
                        set_cpu_spike_date_each_file(file_number, this_date_all, utility, "sys", "highest");
                        set_cpu_spike_time_each_file(file_number, time_value, utility, "sys", "highest");
                    }
                    if (t < ll1) {
                        set_cpu_spike_val_each_file(file_number, t, utility, "sys", "lowest");
                        set_cpu_spike_date_each_file(file_number, this_date_all, utility, "sys", "lowest");
                        set_cpu_spike_time_each_file(file_number, time_value, utility, "sys", "lowest");
                    }
                    set_cpu_former_val_each_file(file_number, t, utility, "sys");
                    if (time_span_checked == 1) {
                        if ((t4 > t_ss1) &&(t_ff1 != 0)) {
                            set_cpu_time_span_spike_val_each_file(file_number, t4, utility, "sys", "spike");
                            set_cpu_time_span_spike_date_each_file(file_number, this_date_all, utility, "sys", "spike");
                            set_cpu_time_span_spike_time_each_file(file_number, time_value, utility, "sys", "spike");
                        }
                        if (t > t_hh1) {
                            set_cpu_time_span_spike_val_each_file(file_number, t, utility, "sys", "highest");
                            set_cpu_time_span_spike_date_each_file(file_number, this_date_all, utility, "sys", "highest");
                            set_cpu_time_span_spike_time_each_file(file_number, time_value, utility, "sys", "highest");
                        }
                        if (t < t_ll1) {
                            set_cpu_time_span_spike_val_each_file(file_number, t, utility, "sys", "lowest");
                            set_cpu_time_span_spike_date_each_file(file_number, this_date_all, utility, "sys", "lowest");
                            set_cpu_time_span_spike_time_each_file(file_number, time_value, utility, "sys", "lowest");
                        }
                        set_cpu_time_span_former_val_each_file(file_number, t, utility, "sys");
                    }
                    if (t > h1) {
                        set_cpu_highest_val(t, utility, "sys");
                        set_cpu_highest_date(this_date_all, utility, "sys");
                        set_cpu_highest_time(time_value, utility, "sys");
                    }
                    if (l1 > t) {
                        set_cpu_lowest_val(t, utility, "sys");
                        set_cpu_lowest_date(this_date_all, utility, "sys");
                        set_cpu_lowest_time(time_value, utility, "sys");
                    }
                    /* code for graph */
                    if ((strstr(time_value, ":00:") != NULL) ||
                        (strstr(time_value, ":10:") != NULL) ||
                        (strstr(time_value, ":20:") != NULL) ||
                        (strstr(time_value, ":30:") != NULL) ||
                        (strstr(time_value, ":40:") != NULL) ||
                        (strstr(time_value, ":50:") != NULL)) {
                        char str_tmp_echo[MAX_LINE_LENGTH - 100] = {'\0'};
                        char str_tmp_echo2[MAX_LINE_LENGTH] = {'\0'};
                        char str_tmp_null[MAX_LINE_LENGTH] = {'\0'};
                        char str_tmp_null2[MAX_LINE_LENGTH + 100] = {'\0'};
                        memset(str_tmp_echo, '\0', sizeof(str_tmp_echo));
                        memset(str_tmp_echo2, '\0', sizeof(str_tmp_echo2));
                        memset(str_tmp_null, '\0', sizeof(str_tmp_null));
                        memset(str_tmp_null2, '\0', sizeof(str_tmp_null2));
                        int difference = 0;
                        snprintf(str_tmp_echo, sizeof(str_tmp_echo), "%f", t);
                        snprintf(str_tmp_null, sizeof(str_tmp_null), "%f", 0.0);
                        if (utility == 0) {
                            snprintf(str_tmp_echo2, sizeof(str_tmp_echo2), "%s,%s,%s,%s,%s", "CPU All", "cpu_sys", this_date_all, time_value, str_tmp_echo);
                            snprintf(str_tmp_null2, sizeof(str_tmp_null2), "%s,%s,%s,%s,%s", "CPU All", "cpu_sys", this_date_all, "", str_tmp_null);
                            difference = check_time_continuity(file_number, (char*)get_this_time_all(), (char*)get_this_time_all_former());
                            // absense of data should be zero
                            if (difference > 1)
                                for(int i=0; i<difference; i++)
                                    append_list2(&svg_cpu_sys_obj, str_tmp_null2, str_tmp_null);
                            else
                                append_list2(&svg_cpu_sys_obj, str_tmp_echo2, str_tmp_echo);
                        }
                    }
                    /* end code for graph */
                } else {
                    h = get_cpu_avg_highest_val(utility, "sys");
                    l = get_cpu_avg_lowest_val(utility, "sys");
                    t = strtod(token, &endp);
                    if (h < t) {
                        set_cpu_avg_highest_val(t, utility, "sys");
                        set_cpu_avg_highest_date(this_date, utility, "sys");
                    }
                    if (l > t) { 
                        set_cpu_avg_lowest_val(t, utility, "sys");
                        set_cpu_avg_lowest_date(this_date, utility, "sys");
                    }
                }
            /* CPU All and %iowait, set the value to struct */
            } else if ((i == get_column_cpu("iowait")) &&(strstr(token, "%iowait") == 0)) {
                if (SAR_OPTION == 'Z') {
                    t = strtod(token, &endp);
                    if (strstr(time_value, "Average") != NULL)
                        return 0;
                    set_tmp_val(t);
                    t = get_tmp_val();
                    set_tmp2_val(t - ff2);
                    t2 = get_tmp2_val();
                    set_tmp3_val(t - f2);
                    t3 = get_tmp3_val();
                    set_tmp4_val(t - t_ff2);
                    t4 = get_tmp4_val();
                    if (t > INT_MAX || t < 0)
                        return 0;
                    if ((t3 > s2) && (f2 != 0)) {
                        set_cpu_spike_val(t3, utility, "iowait");
                        set_cpu_spike_date(this_date_all, utility, "iowait");
                        set_cpu_spike_time(time_value, utility, "iowait");
                    }
                    set_cpu_former_val(t, utility, "iowait");
                    if ((t2 > ss2) && (ff2 != 0)) {
                        set_cpu_spike_val_each_file(file_number, t2, utility, "iowait", "spike");
                        set_cpu_spike_date_each_file(file_number, this_date_all, utility, "iowait", "spike");
                        set_cpu_spike_time_each_file(file_number, time_value, utility, "iowait", "spike");
                    }
                    if (t > hh2) {
                        set_cpu_spike_val_each_file(file_number, t, utility, "iowait", "highest");
                        set_cpu_spike_date_each_file(file_number, this_date_all, utility, "iowait", "highest");
                        set_cpu_spike_time_each_file(file_number, time_value, utility, "iowait", "highest");
                    }
                    if (t < ll2) {
                        set_cpu_spike_val_each_file(file_number, t, utility, "iowait", "lowest");
                        set_cpu_spike_date_each_file(file_number, this_date_all, utility, "iowait", "lowest");
                        set_cpu_spike_time_each_file(file_number, time_value, utility, "iowait", "lowest");
                    }
                    set_cpu_former_val_each_file(file_number, t, utility, "iowait");
                    if (time_span_checked == 1) {
                        if ((t4 > t_ss2) &&(t_ff2 != 0)) {
                            set_cpu_time_span_spike_val_each_file(file_number, t4, utility, "iowait", "spike");
                            set_cpu_time_span_spike_date_each_file(file_number, this_date_all, utility, "iowait", "spike");
                            set_cpu_time_span_spike_time_each_file(file_number, time_value, utility, "iowait", "spike");
                        }
                        if (t > t_hh2) {
                            set_cpu_time_span_spike_val_each_file(file_number, t, utility, "iowait", "highest");
                            set_cpu_time_span_spike_date_each_file(file_number, this_date_all, utility, "iowait", "highest");
                            set_cpu_time_span_spike_time_each_file(file_number, time_value, utility, "iowait", "highest");
                        }
                        if (t < t_ll2) {
                            set_cpu_time_span_spike_val_each_file(file_number, t, utility, "iowait", "lowest");
                            set_cpu_time_span_spike_date_each_file(file_number, this_date_all, utility, "iowait", "lowest");
                            set_cpu_time_span_spike_time_each_file(file_number, time_value, utility, "iowait", "lowest");
                        }
                        set_cpu_time_span_former_val_each_file(file_number, t, utility, "iowait");
                    }
                    if (t > h2) {
                        set_cpu_highest_val(t, utility, "iowait");
                        set_cpu_highest_date(this_date_all, utility, "iowait");
                        set_cpu_highest_time(time_value, utility, "iowait");
                    }
                    if (l2 > t) {
                        set_cpu_lowest_val(t, utility, "iowait");
                        set_cpu_lowest_date(this_date_all, utility, "iowait");
                        set_cpu_lowest_time(time_value, utility, "iowait");
                    }
                    /* code for graph */
                    if ((strstr(time_value, ":00:") != NULL) ||
                        (strstr(time_value, ":10:") != NULL) ||
                        (strstr(time_value, ":20:") != NULL) ||
                        (strstr(time_value, ":30:") != NULL) ||
                        (strstr(time_value, ":40:") != NULL) ||
                        (strstr(time_value, ":50:") != NULL)) {
                        char str_tmp_echo[MAX_LINE_LENGTH - 100] = {'\0'};
                        char str_tmp_echo2[MAX_LINE_LENGTH] = {'\0'};
                        char str_tmp_null[MAX_LINE_LENGTH] = {'\0'};
                        char str_tmp_null2[MAX_LINE_LENGTH + 100] = {'\0'};
                        memset(str_tmp_echo, '\0', sizeof(str_tmp_echo));
                        memset(str_tmp_echo2, '\0', sizeof(str_tmp_echo2));
                        memset(str_tmp_null, '\0', sizeof(str_tmp_null));
                        memset(str_tmp_null2, '\0', sizeof(str_tmp_null2));
                        int difference = 0;
                        snprintf(str_tmp_echo, sizeof(str_tmp_echo), "%f", t);
                        snprintf(str_tmp_null, sizeof(str_tmp_null), "%f", 0.0);
                        if (utility == 0) {
                            snprintf(str_tmp_echo2, sizeof(str_tmp_echo2), "%s,%s,%s,%s,%s", "CPU All", "cpu_iowait", this_date_all, time_value, str_tmp_echo);
                            snprintf(str_tmp_null2, sizeof(str_tmp_null2), "%s,%s,%s,%s,%s", "CPU All", "cpu_iowait", this_date_all, "", str_tmp_null);
                            difference = check_time_continuity(file_number, (char*)get_this_time_all(), (char*)get_this_time_all_former());
                            // absense of data should be zero
                            if (difference > 1)
                                for(int i=0; i<difference; i++)
                                    append_list2(&svg_cpu_iowait_obj, str_tmp_null2, str_tmp_null);
                            else
                                append_list2(&svg_cpu_iowait_obj, str_tmp_echo2, str_tmp_echo);
                        }
                    }
                    /* end code for graph */
                } else {
                    h = get_cpu_avg_highest_val(utility, "iowait");
                    l = get_cpu_avg_lowest_val(utility, "iowait");
                    t = strtod(token, &endp);
                    if (h < t) { 
                        set_cpu_avg_highest_val(t, utility, "iowait");
                        set_cpu_avg_highest_date(this_date, utility, "iowait");
                    }
                    if (l > t) {
                        set_cpu_avg_lowest_val(t, utility, "iowait");
                        set_cpu_avg_lowest_date(this_date, utility, "iowait");
                    }
                }
            /* CPU All and %idle, set the value to struct */
            } else if ((i == get_column_cpu("idle")) &&(strstr(token, "%idle") == 0)) {
                if (SAR_OPTION == 'Z') {
                    t = strtod(token, &endp);
                    if (strstr(time_value, "Average") != NULL)
                        return 0;
                    set_tmp_val(t);
                    t = get_tmp_val();
                    set_tmp2_val(t - ff3);
                    t2 = get_tmp2_val();
                    set_tmp3_val(t - f3);
                    t3 = get_tmp3_val();
                    set_tmp4_val(t - t_ff3);
                    t4 = get_tmp4_val();
                    if (t > INT_MAX || t < 0)
                        return 0;
                    if ((t3 > s3) && (f3 != 0)) {
                        set_cpu_spike_val(t3, utility, "idle");
                        set_cpu_spike_date(this_date_all, utility, "idle");
                        set_cpu_spike_time(time_value, utility, "idle");
                    }
                    set_cpu_former_val(t, utility, "idle");
                    if ((t2 > ss3) && (ff3 != 0)) {
                        set_cpu_spike_val_each_file(file_number, t2, utility, "idle", "spike");
                        set_cpu_spike_date_each_file(file_number, this_date_all, utility, "idle", "spike");
                        set_cpu_spike_time_each_file(file_number, time_value, utility, "idle", "spike");
                    }
                    if (t > hh3) {
                        set_cpu_spike_val_each_file(file_number, t, utility, "idle", "highest");
                        set_cpu_spike_date_each_file(file_number, this_date_all, utility, "idle", "highest");
                        set_cpu_spike_time_each_file(file_number, time_value, utility, "idle", "highest");
                    }
                    if (t < ll3) {
                        set_cpu_spike_val_each_file(file_number, t, utility, "idle", "lowest");
                        set_cpu_spike_date_each_file(file_number, this_date_all, utility, "idle", "lowest");
                        set_cpu_spike_time_each_file(file_number, time_value, utility, "idle", "lowest");
                    }
                    set_cpu_former_val_each_file(file_number, t, utility, "idle");
                    if (time_span_checked == 1) {
                        if ((t4 > t_ss3) &&(t_ff3 != 0)) {
                            set_cpu_time_span_spike_val_each_file(file_number, t4, utility, "idle", "spike");
                            set_cpu_time_span_spike_date_each_file(file_number, this_date_all, utility, "idle", "spike");
                            set_cpu_time_span_spike_time_each_file(file_number, time_value, utility, "idle", "spike");
                        }
                        if (t > t_hh3) {
                            set_cpu_time_span_spike_val_each_file(file_number, t, utility, "idle", "highest");
                            set_cpu_time_span_spike_date_each_file(file_number, this_date_all, utility, "idle", "highest");
                            set_cpu_time_span_spike_time_each_file(file_number, time_value, utility, "idle", "highest");
                        }
                        if (t < t_ll3) {
                            set_cpu_time_span_spike_val_each_file(file_number, t, utility, "idle", "lowest");
                            set_cpu_time_span_spike_date_each_file(file_number, this_date_all, utility, "idle", "lowest");
                            set_cpu_time_span_spike_time_each_file(file_number, time_value, utility, "idle", "lowest");
                        }
                        set_cpu_time_span_former_val_each_file(file_number, t, utility, "idle");
                    }
                    if (t > h3) { 
                        set_cpu_highest_val(t, utility, "idle");
                        set_cpu_highest_date(this_date_all, utility, "idle");
                        set_cpu_highest_time(time_value, utility, "idle");
                    }
                    if (l3 > t) {
                        set_cpu_lowest_val(t, utility, "idle");
                        set_cpu_lowest_date(this_date_all, utility, "idle");
                        set_cpu_lowest_time(time_value, utility, "idle");
                    }
                    /* code for graph */
                    if ((strstr(time_value, ":00:") != NULL) ||
                        (strstr(time_value, ":10:") != NULL) ||
                        (strstr(time_value, ":20:") != NULL) ||
                        (strstr(time_value, ":30:") != NULL) ||
                        (strstr(time_value, ":40:") != NULL) ||
                        (strstr(time_value, ":50:") != NULL)) {
                        char str_tmp_echo[MAX_LINE_LENGTH - 100] = {'\0'};
                        char str_tmp_echo2[MAX_LINE_LENGTH] = {'\0'};
                        char str_tmp_null[MAX_LINE_LENGTH] = {'\0'};
                        char str_tmp_null2[MAX_LINE_LENGTH + 100] = {'\0'};
                        memset(str_tmp_echo, '\0', sizeof(str_tmp_echo));
                        memset(str_tmp_echo2, '\0', sizeof(str_tmp_echo2));
                        memset(str_tmp_null, '\0', sizeof(str_tmp_null));
                        memset(str_tmp_null2, '\0', sizeof(str_tmp_null2));
                        int difference = 0;
                        snprintf(str_tmp_echo, sizeof(str_tmp_echo), "%f", t);
                        snprintf(str_tmp_null, sizeof(str_tmp_null), "%f", 100.0);
                        if (utility == 0) {
                            snprintf(str_tmp_echo2, sizeof(str_tmp_echo2), "%s,%s,%s,%s,%s", "CPU All", "cpu_idle", this_date_all, time_value, str_tmp_echo);
                            snprintf(str_tmp_null2, sizeof(str_tmp_null2), "%s,%s,%s,%s,%s", "CPU All", "cpu_idle", this_date_all, "", str_tmp_null);
                            difference = check_time_continuity(file_number, (char*)get_this_time_all(), (char*)get_this_time_all_former());
                            // absense of data should be zero
                            if (difference > 1)
                                for(int i=0; i<difference; i++)
                                    append_list2(&svg_cpu_idle_obj, str_tmp_null2, str_tmp_null);
                            else
                                append_list2(&svg_cpu_idle_obj, str_tmp_echo2, str_tmp_echo);
                        }
                    }
                    /* end code for graph */
                } else {
                    h = get_cpu_avg_highest_val(utility, "idle");
                    l = get_cpu_avg_lowest_val(utility, "idle");
                    t = strtod(token, &endp);
                    if (h < t) {
                        set_cpu_avg_highest_val(t, utility, "idle");
                        set_cpu_avg_highest_date(this_date, utility, "idle");
                    }
                    if (l > t) {
                        set_cpu_avg_lowest_val(t, utility, "idle");
                        set_cpu_avg_lowest_date(this_date, utility, "idle");
                    }
                }
            }
        /* setting values when proc line */
        } else if ((strcmp(item_name, "proc") == 0) &&(set_to_struct == 0)) {
            s0 = get_tasks_spike_val("proc");
            f0 = get_tasks_former_val("proc");
            h0 = get_tasks_highest_val("proc");
            l0 = get_tasks_lowest_val("proc");
            s1 = get_tasks_spike_val("cswch");
            f1 = get_tasks_former_val("cswch");
            h1 = get_tasks_highest_val("cswch");
            l1 = get_tasks_lowest_val("cswch");
            ss0 = get_tasks_spike_val_each_file(file_number, "proc", "spike");
            ss1 = get_tasks_spike_val_each_file(file_number, "cswch", "spike");
            ff0 = get_tasks_former_val_each_file(file_number, "proc");
            ff1 = get_tasks_former_val_each_file(file_number, "cswch");
            hh0 = get_tasks_spike_val_each_file(file_number, "proc", "highest");
            hh1 = get_tasks_spike_val_each_file(file_number, "cswch", "highest");
            ll0 = get_tasks_spike_val_each_file(file_number, "proc", "lowest");
            ll1 = get_tasks_spike_val_each_file(file_number, "cswch", "lowest");
            t_ss0 = get_tasks_time_span_spike_val_each_file(file_number, "proc", "spike");
            t_ss1 = get_tasks_time_span_spike_val_each_file(file_number, "cswch", "spike");
            t_ff0 = get_tasks_time_span_former_val_each_file(file_number, "proc");
            t_ff1 = get_tasks_time_span_former_val_each_file(file_number, "cswch");
            t_hh0 = get_tasks_time_span_spike_val_each_file(file_number, "proc", "highest");
            t_hh1 = get_tasks_time_span_spike_val_each_file(file_number, "cswch", "highest");
            t_ll0 = get_tasks_time_span_spike_val_each_file(file_number, "proc", "lowest");
            t_ll1 = get_tasks_time_span_spike_val_each_file(file_number, "cswch", "lowest");

            /* proc, set the value to struct */
            if (i == get_column_tasks("proc")) {
                if (SAR_OPTION == 'Z') {
                    t = strtod(token, &endp);
                    if (strstr(time_value, "Average") != NULL)
                        return 0;
                    set_tmp_val(t);
                    t = get_tmp_val();
                    set_tmp2_val(t - ff0);
                    t2 = get_tmp2_val();
                    set_tmp3_val(t - f0);
                    t3 = get_tmp3_val();
                    set_tmp4_val(t - t_ff0);
                    t4 = get_tmp4_val();
                    if (t > INT_MAX || t < 0)
                        return 0;
                    if ((t3 > s0) && (f0 != 0)) {
                        set_tasks_spike_val(t3, "proc");
                        set_tasks_spike_date(this_date_all, "proc");
                        set_tasks_spike_time(time_value, "proc");
                    }
                    set_tasks_former_val(t, "proc");
                    if ((t2 > ss0) && (ff0 != 0)) {
                        set_tasks_spike_val_each_file(file_number, t2, "proc", "spike");
                        set_tasks_spike_date_each_file(file_number, this_date_all, "proc", "spike");
                        set_tasks_spike_time_each_file(file_number, time_value, "proc", "spike");
                    }
                    if (t > hh0) {
                        set_tasks_spike_val_each_file(file_number, t, "proc", "highest");
                        set_tasks_spike_date_each_file(file_number, this_date_all, "proc", "highest");
                        set_tasks_spike_time_each_file(file_number, time_value, "proc", "highest");
                    }
                    if (t < ll0) {
                        set_tasks_spike_val_each_file(file_number, t, "proc", "lowest");
                        set_tasks_spike_date_each_file(file_number, this_date_all, "proc", "lowest");
                        set_tasks_spike_time_each_file(file_number, time_value, "proc", "lowest");
                    }
                    set_tasks_former_val_each_file(file_number, t, "proc");
                    if (time_span_checked == 1) {
                        if ((t4 > t_ss0) && (t_ff0 != 0)) {
                            set_tasks_time_span_spike_val_each_file(file_number, t4, "proc", "spike");
                            set_tasks_time_span_spike_date_each_file(file_number, this_date_all, "proc", "spike");
                            set_tasks_time_span_spike_time_each_file(file_number, time_value, "proc", "spike");
                        }
                        if (t > t_hh0) {
                            set_tasks_time_span_spike_val_each_file(file_number, t, "proc", "highest");
                            set_tasks_time_span_spike_date_each_file(file_number, this_date_all, "proc", "highest");
                            set_tasks_time_span_spike_time_each_file(file_number, time_value, "proc", "highest");
                        }
                        if (t < t_ll0) {
                            set_tasks_time_span_spike_val_each_file(file_number, t, "proc", "lowest");
                            set_tasks_time_span_spike_date_each_file(file_number, this_date_all, "proc", "lowest");
                            set_tasks_time_span_spike_time_each_file(file_number, time_value, "proc", "lowest");
                        }
                        set_tasks_time_span_former_val_each_file(file_number, t, "proc");
                    }
                    if (t > h0) { 
                        set_tasks_highest_val(t, "proc");
                        set_tasks_highest_date(this_date_all, "proc");
                        set_tasks_highest_time(time_value, "proc");
                    }
                    if (l0 > t) { 
                        set_tasks_lowest_val(t, "proc");
                        set_tasks_lowest_date(this_date_all, "proc");
                        set_tasks_lowest_time(time_value, "proc");
                    }
                    /* code for graph */
                } else {
                    h = get_tasks_avg_highest_val("proc");
                    l = get_tasks_avg_lowest_val("proc");
                    t = strtod(token, &endp);
                    if (h < t) {
                        set_tasks_avg_highest_val(t, "proc");
                        set_tasks_avg_highest_date(this_date, "proc");
                    }
                    if (l > t) {
                        set_tasks_avg_lowest_val(t, "proc");
                        set_tasks_avg_lowest_date(this_date, "proc");
                    }
                }
            /* cswch, set the value to struct */
            } else if (i == get_column_tasks("cswch")) {
                if (SAR_OPTION == 'Z') {
                    t = strtod(token, &endp);
                    if (strstr(time_value, "Average") != NULL)
                        return 0;
                    set_tmp_val(t);
                    t = get_tmp_val();
                    set_tmp2_val(t - ff1);
                    t2 = get_tmp2_val();
                    set_tmp3_val(t - f1);
                    t3 = get_tmp3_val();
                    set_tmp4_val(t - t_ff1);
                    t4 = get_tmp4_val();
                    if (t > INT_MAX || t < 0)
                        return 0;
                    if ((t3 > s1) && (f1 != 0)) {
                        set_tasks_spike_val(t3, "cswch");
                        set_tasks_spike_date(this_date_all, "cswch");
                        set_tasks_spike_time(time_value, "cswch");
                    }
                    set_tasks_former_val(t, "cswch");
                    if ((t2 > ss1) && (ff1 != 0)) {
                        set_tasks_spike_val_each_file(file_number, t2, "cswch", "spike");
                        set_tasks_spike_date_each_file(file_number, this_date_all, "cswch", "spike");
                        set_tasks_spike_time_each_file(file_number, time_value, "cswch", "spike");
                    }
                    if (t > hh1) {
                        set_tasks_spike_val_each_file(file_number, t, "cswch", "highest");
                        set_tasks_spike_date_each_file(file_number, this_date_all, "cswch", "highest");
                        set_tasks_spike_time_each_file(file_number, time_value, "cswch", "highest");
                    }
                    if (t < ll1) {
                        set_tasks_spike_val_each_file(file_number, t, "cswch", "lowest");
                        set_tasks_spike_date_each_file(file_number, this_date_all, "cswch", "lowest");
                        set_tasks_spike_time_each_file(file_number, time_value, "cswch", "lowest");
                    }
                    set_tasks_former_val_each_file(file_number, t, "cswch");
                    if (time_span_checked == 1) {
                        if ((t4 > t_ss1) && (t_ff1 != 0)) {
                            set_tasks_time_span_spike_val_each_file(file_number, t4, "cswch", "spike");
                            set_tasks_time_span_spike_date_each_file(file_number, this_date_all, "cswch", "spike");
                            set_tasks_time_span_spike_time_each_file(file_number, time_value, "cswch", "spike");
                        }
                        if (t > t_hh1) {
                            set_tasks_time_span_spike_val_each_file(file_number, t, "cswch", "highest");
                            set_tasks_time_span_spike_date_each_file(file_number, this_date_all, "cswch", "highest");
                            set_tasks_time_span_spike_time_each_file(file_number, time_value, "cswch", "highest");
                        }
                        if (t < t_ll1) {
                            set_tasks_time_span_spike_val_each_file(file_number, t, "cswch", "lowest");
                            set_tasks_time_span_spike_date_each_file(file_number, this_date_all, "cswch", "lowest");
                            set_tasks_time_span_spike_time_each_file(file_number, time_value, "cswch", "lowest");
                        }
                        set_tasks_time_span_former_val_each_file(file_number, t, "cswch");
                    }
                    if (t > h1) { 
                        set_tasks_highest_val(t, "cswch");
                        set_tasks_highest_date(this_date_all, "cswch");
                        set_tasks_highest_time(time_value, "cswch");
                    }
                    if (l1 > t) {
                        set_tasks_lowest_val(t, "cswch");
                        set_tasks_lowest_date(this_date_all, "cswch");
                        set_tasks_lowest_time(time_value, "cswch");
                    }
                    /* code for graph */
                } else {
                    h = get_tasks_avg_highest_val("cswch");
                    l = get_tasks_avg_lowest_val("cswch");
                    t = strtod(token, &endp);
                    if (h < t) {
                        set_tasks_avg_highest_val(t, "cswch");
                        set_tasks_avg_highest_date(this_date, "cswch");
                    }
                    if (l > t) { 
                        set_tasks_avg_lowest_val(t, "cswch");
                        set_tasks_avg_lowest_date(this_date, "cswch");
                    }
                }
            }
       /* setting values when  pswpin line */
       } else if ((strcmp(item_name, "pswpin/s") == 0) &&(set_to_struct == 0)) {
            s0 = get_pswap_spike_val("pwpin");
            f0 = get_pswap_former_val("pswpin");
            h0 = get_pswap_highest_val("pswpin");
            l0 = get_pswap_lowest_val("pswpin");
            s1 = get_pswap_spike_val("pswpout");
            f1 = get_pswap_former_val("pswpout");
            h1 = get_pswap_highest_val("pswpout");
            l1 = get_pswap_lowest_val("pswpout");
            ss0 = get_pswap_spike_val_each_file(file_number, "pswpin", "spike");
            ss1 = get_pswap_spike_val_each_file(file_number, "pswpout", "spike");
            ff0 = get_pswap_former_val_each_file(file_number, "pswpin");
            ff1 = get_pswap_former_val_each_file(file_number, "pswpout");
            hh0 = get_pswap_spike_val_each_file(file_number, "pswpin", "highest");
            hh1 = get_pswap_spike_val_each_file(file_number, "pswpout", "highest");
            ll0 = get_pswap_spike_val_each_file(file_number, "pswpin", "lowest");
            ll1 = get_pswap_spike_val_each_file(file_number, "pswpout", "lowest");
            t_ss0 = get_pswap_time_span_spike_val_each_file(file_number, "pswpin", "spike");
            t_ss1 = get_pswap_time_span_spike_val_each_file(file_number, "pswpout", "spike");
            t_ff0 = get_pswap_time_span_former_val_each_file(file_number, "pswpin");
            t_ff1 = get_pswap_time_span_former_val_each_file(file_number, "pswpout");
            t_hh0 = get_pswap_time_span_spike_val_each_file(file_number, "pswpin", "highest");
            t_hh1 = get_pswap_time_span_spike_val_each_file(file_number, "pswpout", "highest");
            t_ll0 = get_pswap_time_span_spike_val_each_file(file_number, "pswpin", "lowest");
            t_ll1 = get_pswap_time_span_spike_val_each_file(file_number, "pswpout", "lowest");

            /* pswpin, set the value to struct */
            if (i == get_column_pswap("pswpin")) {
                if (SAR_OPTION == 'Z') {
                    t = strtod(token, &endp);
                    if (strstr(time_value, "Average") != NULL)
                        return 0;
                    set_tmp_val(t);
                    t = get_tmp_val();
                    set_tmp2_val(t - ff0);
                    t2 = get_tmp2_val();
                    set_tmp3_val(t - f0);
                    t3 = get_tmp3_val();
                    set_tmp4_val(t - t_ff0);
                    t4 = get_tmp4_val();
                    if (t > INT_MAX || t < 0)
                        return 0;
                    if ((t3 > s0) && (f0 != 0)) {
                        set_pswap_spike_val(t3, "pswpin");
                        set_pswap_spike_date(this_date_all, "pswpin");
                        set_pswap_spike_time(time_value, "pswpin");
                    }
                    set_pswap_former_val(t, "pswpin");
                    if ((t2 > ss0) && (ff0 != 0)) {
                        set_pswap_spike_val_each_file(file_number, t2, "pswpin", "spike");
                        set_pswap_spike_date_each_file(file_number, this_date_all, "pswpin", "spike");
                        set_pswap_spike_time_each_file(file_number, time_value, "pswpin", "spike");
                    }
                    if (t  > hh0) {
                        set_pswap_spike_val_each_file(file_number, t, "pswpin", "highest");
                        set_pswap_spike_date_each_file(file_number, this_date_all, "pswpin", "highest");
                        set_pswap_spike_time_each_file(file_number, time_value, "pswpin", "highest");
                    }
                    if (t  < ll0) {
                        set_pswap_spike_val_each_file(file_number, t, "pswpin", "lowest");
                        set_pswap_spike_date_each_file(file_number, this_date_all, "pswpin", "lowest");
                        set_pswap_spike_time_each_file(file_number, time_value, "pswpin", "lowest");
                    }
                    set_pswap_former_val_each_file(file_number, t, "pswpin");
                    if (time_span_checked == 1) {
                        if ((t4 > t_ss0) && (t_ff0 != 0)) {
                            set_pswap_time_span_spike_val_each_file(file_number, t4, "pswpin", "spike");
                            set_pswap_time_span_spike_date_each_file(file_number, this_date_all, "pswpin", "spike");
                            set_pswap_time_span_spike_time_each_file(file_number, time_value, "pswpin", "spike");
                        }
                        if (t  > t_hh0) {
                            set_pswap_time_span_spike_val_each_file(file_number, t, "pswpin", "highest");
                            set_pswap_time_span_spike_date_each_file(file_number, this_date_all, "pswpin", "highest");
                            set_pswap_time_span_spike_time_each_file(file_number, time_value, "pswpin", "highest");
                        }
                        if (t  < t_ll0) {
                            set_pswap_time_span_spike_val_each_file(file_number, t, "pswpin", "lowest");
                            set_pswap_time_span_spike_date_each_file(file_number, this_date_all, "pswpin", "lowest");
                            set_pswap_time_span_spike_time_each_file(file_number, time_value, "pswpin", "lowest");
                        }
                        set_pswap_time_span_former_val_each_file(file_number, t, "pswpin");
                    }
                    if (t > h0) { 
                        set_pswap_highest_val(t, "pswpin");
                        set_pswap_highest_date(this_date_all, "pswpin");
                        set_pswap_highest_time(time_value, "pswpin");
                    }
                    if (l0 > t) {
                        set_pswap_lowest_val(t, "pswpin");
                        set_pswap_lowest_date(this_date_all, "pswpin");
                        set_pswap_lowest_time(time_value, "pswpin");
                    }
                    /* code for graph */
                } else {
                    h = get_pswap_avg_highest_val("pswpin");
                    l = get_pswap_avg_lowest_val("pswpin");
                    t = strtod(token, &endp);
                    if (h < t) {
                        set_pswap_avg_highest_val(t, "pswpin");
                        set_pswap_avg_highest_date(this_date, "pswpin");
                    }
                    if (l > t) {
                        set_pswap_avg_lowest_val(t, "pswpin");
                        set_pswap_avg_lowest_date(this_date, "pswpin");
                    }
                }
            /* pswpout, set the value to struct */
            } else if (i == get_column_pswap("pswpout")) {
                if (SAR_OPTION == 'Z') {
                    t = strtod(token, &endp);
                    if (strstr(time_value, "Average") != NULL)
                        return 0;
                    set_tmp_val(t);
                    t = get_tmp_val();
                    set_tmp2_val(t - ff1);
                    t2 = get_tmp2_val();
                    set_tmp3_val(t - f1);
                    t3 = get_tmp3_val();
                    set_tmp4_val(t - t_ff1);
                    t4 = get_tmp4_val();
                    if (t > INT_MAX || t < 0)
                        return 0;
                    if ((t3 > s1) && (f1 != 0)) {
                        set_pswap_spike_val(t3, "pswpout");
                        set_pswap_spike_date(this_date_all, "pswpout");
                        set_pswap_spike_time(time_value, "pswpout");
                    }
                    set_pswap_former_val(t, "pswpout");
                    if ((t2 > ss1) && (ff1 != 0)) {
                        set_pswap_spike_val_each_file(file_number, t2, "pswpout", "spike");
                        set_pswap_spike_date_each_file(file_number, this_date_all, "pswpout", "spike");
                        set_pswap_spike_time_each_file(file_number, time_value, "pswpout", "spike");
                    }
                    if (t  > hh1) {
                        set_pswap_spike_val_each_file(file_number, t, "pswpout", "highest");
                        set_pswap_spike_date_each_file(file_number, this_date_all, "pswpout", "highest");
                        set_pswap_spike_time_each_file(file_number, time_value, "pswpout", "highest");
                    }
                    if (t  < ll1) {
                        set_pswap_spike_val_each_file(file_number, t, "pswpout", "lowest");
                        set_pswap_spike_date_each_file(file_number, this_date_all, "pswpout", "lowest");
                        set_pswap_spike_time_each_file(file_number, time_value, "pswpout", "lowest");
                    }
                    set_pswap_former_val_each_file(file_number, t, "pswpout");
                    if (time_span_checked == 1) {
                        if ((t4 > t_ss1) && (t_ff1 != 0)) {
                            set_pswap_time_span_spike_val_each_file(file_number, t4, "pswpout", "spike");
                            set_pswap_time_span_spike_date_each_file(file_number, this_date_all, "pswpout", "spike");
                            set_pswap_time_span_spike_time_each_file(file_number, time_value, "pswpout", "spike");
                        }
                        if (t  > t_hh1) {
                            set_pswap_time_span_spike_val_each_file(file_number, t, "pswpout", "highest");
                            set_pswap_time_span_spike_date_each_file(file_number, this_date_all, "pswpout", "highest");
                            set_pswap_time_span_spike_time_each_file(file_number, time_value, "pswpout", "highest");
                        }
                        if (t  < t_ll1) {
                            set_pswap_time_span_spike_val_each_file(file_number, t, "pswpout", "lowest");
                            set_pswap_time_span_spike_date_each_file(file_number, this_date_all, "pswpout", "lowest");
                            set_pswap_time_span_spike_time_each_file(file_number, time_value, "pswpout", "lowest");
                        }
                        set_pswap_time_span_former_val_each_file(file_number, t, "pswpout");
                    }
                    if (t > h1) { 
                        set_pswap_highest_val(t, "pswpout");
                        set_pswap_highest_date(this_date_all, "pswpout");
                        set_pswap_highest_time(time_value, "pswpout");
                    }
                    if (l1 > t) {
                        set_pswap_lowest_val(t, "pswpout");
                        set_pswap_lowest_date(this_date_all, "pswpout");
                        set_pswap_lowest_time(time_value, "pswpout");
                    }
                    /* code for graph */
                } else {
                    h = get_pswap_avg_highest_val("pswpout");
                    l = get_pswap_avg_lowest_val("pswpout");
                    t = strtod(token, &endp);
                    if (h < t) {
                        set_pswap_avg_highest_val(t, "pswpout");
                        set_pswap_avg_highest_date(this_date, "pswpout");
                    }
                    if (l > t) { 
                        set_pswap_avg_lowest_val(t, "pswpout");
                        set_pswap_avg_lowest_date(this_date, "pswpout");
                    }
                }
            }
       /* setting values when fault line */
       } else if ((strcmp(item_name, "fault") == 0) &&(set_to_struct == 0)) {
            s0 = get_paging_spike_val("pgpgin");
            f0 = get_paging_former_val("pgpgin");
            h0 = get_paging_highest_val("pgpgin");
            l0 = get_paging_lowest_val("pgpgin");
            s1 = get_paging_spike_val("pgpgout");
            f1 = get_paging_former_val("pgpgout");
            h1 = get_paging_highest_val("pgpgout");
            l1 = get_paging_lowest_val("pgpgout");
            s2 = get_paging_spike_val("fault");
            f2 = get_paging_former_val("fault");
            h2 = get_paging_highest_val("fault");
            l2 = get_paging_lowest_val("fault");
            s3 = get_paging_spike_val("majflt");
            f3 = get_paging_former_val("majflt");
            h3 = get_paging_highest_val("majflt");
            l3 = get_paging_lowest_val("majflt");
            s4 = get_paging_spike_val("vmeff");
            f4 = get_paging_former_val("vmeff");
            h4 = get_paging_highest_val("vmeff");
            l4 = get_paging_lowest_val("vmeff");
            ss0 = get_paging_spike_val_each_file(file_number, "pgpgin", "spike");
            ss1 = get_paging_spike_val_each_file(file_number, "pgpgout", "spike");
            ss2 = get_paging_spike_val_each_file(file_number, "fault", "spike");
            ss3 = get_paging_spike_val_each_file(file_number, "majflt", "spike");
            ss4 = get_paging_spike_val_each_file(file_number, "vmeff", "spike");
            ff0 = get_paging_former_val_each_file(file_number, "pgpgin");
            ff1 = get_paging_former_val_each_file(file_number, "pgpgout");
            ff2 = get_paging_former_val_each_file(file_number, "fault");
            ff3 = get_paging_former_val_each_file(file_number, "majflt");
            ff4 = get_paging_former_val_each_file(file_number, "vmeff");
            hh0 = get_paging_spike_val_each_file(file_number, "pgpgin", "highest");
            hh1 = get_paging_spike_val_each_file(file_number, "pgpgout", "highest");
            hh2 = get_paging_spike_val_each_file(file_number, "fault", "highest");
            hh3 = get_paging_spike_val_each_file(file_number, "majflt", "highest");
            hh4 = get_paging_spike_val_each_file(file_number, "vmeff", "highest");
            ll0 = get_paging_spike_val_each_file(file_number, "pgpgin", "lowest");
            ll1 = get_paging_spike_val_each_file(file_number, "pgpgout", "lowest");
            ll2 = get_paging_spike_val_each_file(file_number, "fault", "lowest");
            ll3 = get_paging_spike_val_each_file(file_number, "majflt", "lowest");
            ll4 = get_paging_spike_val_each_file(file_number, "vmeff", "lowest");
            t_ss0 = get_paging_time_span_spike_val_each_file(file_number, "pgpgin", "spike");
            t_ss1 = get_paging_time_span_spike_val_each_file(file_number, "pgpgout", "spike");
            t_ss2 = get_paging_time_span_spike_val_each_file(file_number, "fault", "spike");
            t_ss3 = get_paging_time_span_spike_val_each_file(file_number, "majflt", "spike");
            t_ss4 = get_paging_time_span_spike_val_each_file(file_number, "vmeff", "spike");
            t_ff0 = get_paging_time_span_former_val_each_file(file_number, "pgpgin");
            t_ff1 = get_paging_time_span_former_val_each_file(file_number, "pgpgout");
            t_ff2 = get_paging_time_span_former_val_each_file(file_number, "fault");
            t_ff3 = get_paging_time_span_former_val_each_file(file_number, "majflt");
            t_ff4 = get_paging_time_span_former_val_each_file(file_number, "vmeff");
            t_hh0 = get_paging_time_span_spike_val_each_file(file_number, "pgpgin", "highest");
            t_hh1 = get_paging_time_span_spike_val_each_file(file_number, "pgpgout", "highest");
            t_hh2 = get_paging_time_span_spike_val_each_file(file_number, "fault", "highest");
            t_hh3 = get_paging_time_span_spike_val_each_file(file_number, "majflt", "highest");
            t_hh4 = get_paging_spike_val_each_file(file_number, "vmeff", "highest");
            t_ll0 = get_paging_time_span_spike_val_each_file(file_number, "pgpgin", "lowest");
            t_ll1 = get_paging_time_span_spike_val_each_file(file_number, "pgpgout", "lowest");
            t_ll2 = get_paging_time_span_spike_val_each_file(file_number, "fault", "lowest");
            t_ll3 = get_paging_time_span_spike_val_each_file(file_number, "majflt", "lowest");
            t_ll4 = get_paging_spike_val_each_file(file_number, "vmeff", "lowest");

            /* pgpgin, set the value to struct */
            if (i == get_column_paging("pgpgin")) {
                if (SAR_OPTION == 'Z') {
                    t = strtod(token, &endp);
                    if (strstr(time_value, "Average") != NULL)
                        return 0;
                    set_tmp_val(t);
                    t = get_tmp_val();
                    set_tmp2_val(t - ff0);
                    t2 = get_tmp2_val();
                    set_tmp3_val(t - f0);
                    t3 = get_tmp3_val();
                    set_tmp4_val(t - t_ff0);
                    t4 = get_tmp4_val();
                    if (t > INT_MAX || t < 0)
                        return 0;
                    if ((t3 > s0) && (f0 != 0)) {
                        set_paging_spike_val(t3, "pgpgin");
                        set_paging_spike_date(this_date_all, "pgpgin");
                        set_paging_spike_time(time_value, "pgpgin");
                    }
                    set_paging_former_val(t, "pgpgin");
                    if ((t2 > ss0) && (ff0 != 0)) {
                        set_paging_spike_val_each_file(file_number, t2, "pgpgin", "spike");
                        set_paging_spike_date_each_file(file_number, this_date_all, "pgpgin", "spike");
                        set_paging_spike_time_each_file(file_number, time_value, "pgpgin", "spike");
                    }
                    if (t  > hh0) {
                        set_paging_spike_val_each_file(file_number, t, "pgpgin", "highest");
                        set_paging_spike_date_each_file(file_number, this_date_all, "pgpgin", "highest");
                        set_paging_spike_time_each_file(file_number, time_value, "pgpgin", "highest");
                    }
                    if (t  < ll0) {
                        set_paging_spike_val_each_file(file_number, t, "pgpgin", "lowest");
                        set_paging_spike_date_each_file(file_number, this_date_all, "pgpgin", "lowest");
                        set_paging_spike_time_each_file(file_number, time_value, "pgpgin", "lowest");
                    }
                    set_paging_former_val_each_file(file_number, t, "pgpgin");
                    if (time_span_checked == 1) {
                        if ((t4 > t_ss0) && (t_ff0 != 0)) {
                            set_paging_time_span_spike_val_each_file(file_number, t4, "pgpgin", "spike");
                            set_paging_time_span_spike_date_each_file(file_number, this_date_all, "pgpgin", "spike");
                            set_paging_time_span_spike_time_each_file(file_number, time_value, "pgpgin", "spike");
                        }
                        if (t  > t_hh0) {
                            set_paging_time_span_spike_val_each_file(file_number, t, "pgpgin", "highest");
                            set_paging_time_span_spike_date_each_file(file_number, this_date_all, "pgpgin", "highest");
                            set_paging_time_span_spike_time_each_file(file_number, time_value, "pgpgin", "highest");
                        }
                        if (t  < t_ll0) {
                            set_paging_time_span_spike_val_each_file(file_number, t, "pgpgin", "lowest");
                            set_paging_time_span_spike_date_each_file(file_number, this_date_all, "pgpgin", "lowest");
                            set_paging_time_span_spike_time_each_file(file_number, time_value, "pgpgin", "lowest");
                        }
                        set_paging_time_span_former_val_each_file(file_number, t, "pgpgin");
                    }
                    if (t > h0) {
                        set_paging_highest_val(t, "pgpgin");
                        set_paging_highest_date(this_date_all, "pgpgin");
                        set_paging_highest_time(time_value, "pgpgin");
                    }
                    if (l0 > t) {
                        set_paging_lowest_val(t, "pgpgin");
                        set_paging_lowest_date(this_date_all, "pgpgin");
                        set_paging_lowest_time(time_value, "pgpgin");
                    }
                    /* code for graph */
                } else {
                    h = get_paging_avg_highest_val("pgpgin");
                    l = get_paging_avg_lowest_val("pgpgin");
                    t = strtod(token, &endp);
                    if (h < t) { 
                        set_paging_avg_highest_val(t, "pgpgin");
                        set_paging_avg_highest_date(this_date, "pgpgin");
                    }
                    if (l > t) {
                        set_paging_avg_lowest_val(t, "pgpgin");
                        set_paging_avg_lowest_date(this_date, "pgpgin");
                    }
                }
            }
            /* pgpgout, set the value to struct */
            if (i == get_column_paging("pgpgout")) {
                if (SAR_OPTION == 'Z') {
                    t = strtod(token, &endp);
                    if (strstr(time_value, "Average") != NULL)
                        return 0;
                    set_tmp_val(t);
                    t = get_tmp_val();
                    set_tmp2_val(t - ff1);
                    t2 = get_tmp2_val();
                    set_tmp3_val(t - f1);
                    t3 = get_tmp3_val();
                    set_tmp4_val(t - t_ff1);
                    t4 = get_tmp4_val();
                    if (t > INT_MAX || t < 0)
                        return 0;
                    if ((t3 > s1) && (f1 != 0)) {
                        set_paging_spike_val(t3, "pgpgout");
                        set_paging_spike_date(this_date_all, "pgpgout");
                        set_paging_spike_time(time_value, "pgpgout");
                    }
                    set_paging_former_val(t, "pgpgout");
                    if ((t2 > ss1) && (ff1 != 0)) {
                        set_paging_spike_val_each_file(file_number, t2, "pgpgout", "spike");
                        set_paging_spike_date_each_file(file_number, this_date_all, "pgpgout", "spike");
                        set_paging_spike_time_each_file(file_number, time_value, "pgpgout", "spike");
                    }
                    if (t  > hh1) {
                        set_paging_spike_val_each_file(file_number, t, "pgpgout", "highest");
                        set_paging_spike_date_each_file(file_number, this_date_all, "pgpgout", "highest");
                        set_paging_spike_time_each_file(file_number, time_value, "pgpgout", "highest");
                    }
                    if (t  < ll1) {
                        set_paging_spike_val_each_file(file_number, t, "pgpgout", "lowest");
                        set_paging_spike_date_each_file(file_number, this_date_all, "pgpgout", "lowest");
                        set_paging_spike_time_each_file(file_number, time_value, "pgpgout", "lowest");
                    }
                    set_paging_former_val_each_file(file_number, t, "pgpgout");
                    if (time_span_checked == 1) {
                        if ((t4 > t_ss1) && (t_ff1 != 0)) {
                            set_paging_time_span_spike_val_each_file(file_number, t4, "pgpgout", "spike");
                            set_paging_time_span_spike_date_each_file(file_number, this_date_all, "pgpgout", "spike");
                            set_paging_time_span_spike_time_each_file(file_number, time_value, "pgpgout", "spike");
                        }
                        if (t  > t_hh1) {
                            set_paging_time_span_spike_val_each_file(file_number, t, "pgpgout", "highest");
                            set_paging_time_span_spike_date_each_file(file_number, this_date_all, "pgpgout", "highest");
                            set_paging_time_span_spike_time_each_file(file_number, time_value, "pgpgout", "highest");
                        }
                        if (t  < t_ll1) {
                            set_paging_time_span_spike_val_each_file(file_number, t, "pgpgout", "lowest");
                            set_paging_time_span_spike_date_each_file(file_number, this_date_all, "pgpgout", "lowest");
                            set_paging_time_span_spike_time_each_file(file_number, time_value, "pgpgout", "lowest");
                        }
                        set_paging_time_span_former_val_each_file(file_number, t, "pgpgout");
                    }
                    if (t > h1) { 
                        set_paging_highest_val(t, "pgpgout");
                        set_paging_highest_date(this_date_all, "pgpgout");
                        set_paging_highest_time(time_value, "pgpgout");
                    }
                    if (l1 > t) {
                        set_paging_lowest_val(t, "pgpgout");
                        set_paging_lowest_date(this_date_all, "pgpgout");
                        set_paging_lowest_time(time_value, "pgpgout");
                    }
                    /* code for graph */
                } else {
                    h = get_paging_avg_highest_val("pgpgout");
                    l = get_paging_avg_lowest_val("pgpgout");
                    t = strtod(token, &endp);
                    if (h < t) {
                        set_paging_avg_highest_val(t, "pgpgout");
                        set_paging_avg_highest_date(this_date, "pgpgout");
                    }
                    if (l > t) {
                        set_paging_avg_lowest_val(t, "pgpgout");
                        set_paging_avg_lowest_date(this_date, "pgpgout");
                    }
                }
            }
            /* fault, set the value to struct */
            if (i == get_column_paging("fault")) {
                if (SAR_OPTION == 'Z') {
                    t = strtod(token, &endp);
                    if (strstr(time_value, "Average") != NULL)
                        return 0;
                    set_tmp_val(t);
                    t = get_tmp_val();
                    set_tmp2_val(t - ff2);
                    t2 = get_tmp2_val();
                    set_tmp3_val(t - f2);
                    t3 = get_tmp3_val();
                    set_tmp4_val(t - t_ff2);
                    t4 = get_tmp4_val();
                    if (t > INT_MAX || t < 0)
                        return 0;
                    if ((t3 > s2) && (f2 != 0)) {
                        set_paging_spike_val(t3, "fault");
                        set_paging_spike_date(this_date_all, "fault");
                        set_paging_spike_time(time_value, "fault");
                    }
                    set_paging_former_val(t, "fault");
                    if ((t2 > ss2) &&(ff2 != 0)) {
                        set_paging_spike_val_each_file(file_number, t2, "fault", "spike");
                        set_paging_spike_date_each_file(file_number, this_date_all, "fault", "spike");
                        set_paging_spike_time_each_file(file_number, time_value, "fault", "spike");
                    }
                    if (t  > hh2) {
                        set_paging_spike_val_each_file(file_number, t, "fault", "highest");
                        set_paging_spike_date_each_file(file_number, this_date_all, "fault", "highest");
                        set_paging_spike_time_each_file(file_number, time_value, "fault", "highest");
                    }
                    if (t  < ll2) {
                        set_paging_spike_val_each_file(file_number, t, "fault", "lowest");
                        set_paging_spike_date_each_file(file_number, this_date_all, "fault", "lowest");
                        set_paging_spike_time_each_file(file_number, time_value, "fault", "lowest");
                    }
                    set_paging_former_val_each_file(file_number, t, "fault");
                    if (time_span_checked == 1) {
                        if ((t4 > t_ss2) &&(t_ff2 != 0)) {
                            set_paging_time_span_spike_val_each_file(file_number, t4, "fault", "spike");
                            set_paging_time_span_spike_date_each_file(file_number, this_date_all, "fault", "spike");
                            set_paging_time_span_spike_time_each_file(file_number, time_value, "fault", "spike");
                        }
                        if (t  > t_hh2) {
                            set_paging_time_span_spike_val_each_file(file_number, t, "fault", "highest");
                            set_paging_time_span_spike_date_each_file(file_number, this_date_all, "fault", "highest");
                            set_paging_time_span_spike_time_each_file(file_number, time_value, "fault", "highest");
                        }
                        if (t  < t_ll2) {
                            set_paging_time_span_spike_val_each_file(file_number, t, "fault", "lowest");
                            set_paging_time_span_spike_date_each_file(file_number, this_date_all, "fault", "lowest");
                            set_paging_time_span_spike_time_each_file(file_number, time_value, "fault", "lowest");
                        }
                        set_paging_time_span_former_val_each_file(file_number, t, "fault");
                    }
                    if (h2 < t) {
                        set_paging_highest_val(t, "fault");
                        set_paging_highest_date(this_date_all, "fault");
                        set_paging_highest_time(time_value, "fault");
                    }
                    if (l2 > t) {
                        set_paging_lowest_val(t, "fault");
                        set_paging_lowest_date(this_date_all, "fault");
                        set_paging_lowest_time(time_value, "fault");
                    }
                    /* code for graph */
                } else {
                    h = get_paging_avg_highest_val("fault");
                    l = get_paging_avg_lowest_val("fault");
                    t = strtod(token, &endp);
                    if (h < t) { 
                        set_paging_avg_highest_val(t, "fault");
                        set_paging_avg_highest_date(this_date, "fault");
                    }
                    if (l > t) {
                        set_paging_avg_lowest_val(t, "fault");
                        set_paging_avg_lowest_date(this_date, "fault");
                    }
                }
            /* majflt, set the value to struct */
            } else if (i == get_column_paging("majflt")) {
                if (SAR_OPTION == 'Z') {
                    t = strtod(token, &endp);
                    if (strstr(time_value, "Average") != NULL)
                        return 0;
                    set_tmp_val(t);
                    t = get_tmp_val();
                    set_tmp2_val(t - ff3);
                    t2 = get_tmp2_val();
                    set_tmp3_val(t - f3);
                    t3 = get_tmp3_val();
                    set_tmp4_val(t - t_ff3);
                    t4 = get_tmp4_val();
                    if (t > INT_MAX || t < 0)
                        return 0;
                    if ((t3 > s3) && (f3 != 0)) {
                        set_paging_spike_val(t3, "majflt");
                        set_paging_spike_date(this_date_all, "majflt");
                        set_paging_spike_time(time_value, "majflt");
                    }
                    set_paging_former_val(t, "majflt");
                    if ((t2 > ss3) && (ff3 != 0)) {
                        set_paging_spike_val_each_file(file_number, t2, "majflt", "spike");
                        set_paging_spike_date_each_file(file_number, this_date_all, "majflt", "spike");
                        set_paging_spike_time_each_file(file_number, time_value, "majflt", "spike");
                    }
                    if (t  > hh3) {
                        set_paging_spike_val_each_file(file_number, t, "majflt", "highest");
                        set_paging_spike_date_each_file(file_number, this_date_all, "majflt", "highest");
                        set_paging_spike_time_each_file(file_number, time_value, "majflt", "highest");
                    }
                    if (t  < ll3) {
                        set_paging_spike_val_each_file(file_number, t, "majflt", "lowest");
                        set_paging_spike_date_each_file(file_number, this_date_all, "majflt", "lowest");
                        set_paging_spike_time_each_file(file_number, time_value, "majflt", "lowest");
                    }
                    set_paging_former_val_each_file(file_number, t, "majflt");
                    if (time_span_checked == 1) {
                        if ((t4 > t_ss3) && (t_ff3 != 0)) {
                            set_paging_time_span_spike_val_each_file(file_number, t4, "majflt", "spike");
                            set_paging_time_span_spike_date_each_file(file_number, this_date_all, "majflt", "spike");
                            set_paging_time_span_spike_time_each_file(file_number, time_value, "majflt", "spike");
                        }
                        if (t  > t_hh3) {
                            set_paging_time_span_spike_val_each_file(file_number, t, "majflt", "highest");
                            set_paging_time_span_spike_date_each_file(file_number, this_date_all, "majflt", "highest");
                            set_paging_time_span_spike_time_each_file(file_number, time_value, "majflt", "highest");
                        }
                        if (t  < t_ll3) {
                            set_paging_time_span_spike_val_each_file(file_number, t, "majflt", "lowest");
                            set_paging_time_span_spike_date_each_file(file_number, this_date_all, "majflt", "lowest");
                            set_paging_time_span_spike_time_each_file(file_number, time_value, "majflt", "lowest");
                        }
                        set_paging_time_span_former_val_each_file(file_number, t, "majflt");
                    }
                    if (t > h3) { 
                        set_paging_highest_val(t, "majflt");
                        set_paging_highest_date(this_date_all, "majflt");
                        set_paging_highest_time(time_value, "majflt");
                    }
                    if (l3 > t) {
                        set_paging_lowest_val(t, "majflt");
                        set_paging_lowest_date(this_date_all, "majflt");
                        set_paging_lowest_time(time_value, "majflt");
                    }
                    /* code for graph */
                } else {
                    h = get_paging_avg_highest_val("majflt");
                    l = get_paging_avg_lowest_val("majflt");
                    t = strtod(token, &endp);
                    if (h < t) { 
                        set_paging_avg_highest_val(t, "majflt");
                        set_paging_avg_highest_date(this_date, "majflt");
                    }
                    if (l > t) {
                        set_paging_avg_lowest_val(t, "majflt");
                        set_paging_avg_lowest_date(this_date, "majflt");
                    }
                }
            /* vmeff, set the value to struct */
            } else if (i == get_column_paging("vmeff")) {
                if (SAR_OPTION == 'Z') {
                    t = strtod(token, &endp);
                    if (strstr(time_value, "Average") != NULL)
                        return 0;
                    set_tmp_val(t);
                    t = get_tmp_val();
                    set_tmp2_val(t - ff4);
                    t2 = get_tmp2_val();
                    set_tmp3_val(t - f4);
                    t3 = get_tmp3_val();
                    set_tmp4_val(t - t_ff4);
                    t4 = get_tmp4_val();
                    if (t > INT_MAX || t < 0)
                        return 0;
                    if ((t3 > s4) &&(f4 != 0)) {
                        set_paging_spike_val(t3, "vmeff");
                        set_paging_spike_date(this_date_all, "vmeff");
                        set_paging_spike_time(time_value, "vmeff");
                    }
                    set_paging_former_val(t, "vmeff");
                    if ((t2 > ss4) &&(ff4 != 0)) {
                        set_paging_spike_val_each_file(file_number, t2, "vmeff", "spike");
                        set_paging_spike_date_each_file(file_number, this_date_all, "vmeff", "spike");
                        set_paging_spike_time_each_file(file_number, time_value, "vmeff", "spike");
                    }
                    if (t  > hh4) {
                        set_paging_spike_val_each_file(file_number, t, "vmeff", "highest");
                        set_paging_spike_date_each_file(file_number, this_date_all, "vmeff", "highest");
                        set_paging_spike_time_each_file(file_number, time_value, "vmeff", "highest");
                    }
                    if (t  < ll4) {
                        set_paging_spike_val_each_file(file_number, t, "vmeff", "lowest");
                        set_paging_spike_date_each_file(file_number, this_date_all, "vmeff", "lowest");
                        set_paging_spike_time_each_file(file_number, time_value, "vmeff", "lowest");
                    }
                    set_paging_former_val_each_file(file_number, t, "vmeff");
                    if (time_span_checked == 1) {
                        if ((t4 > t_ss4) &&(t_ff4 != 0)) {
                            set_paging_time_span_spike_val_each_file(file_number, t4, "vmeff", "spike");
                            set_paging_time_span_spike_date_each_file(file_number, this_date_all, "vmeff", "spike");
                            set_paging_time_span_spike_time_each_file(file_number, time_value, "vmeff", "spike");
                        }
                        if (t  > t_hh4) {
                            set_paging_time_span_spike_val_each_file(file_number, t, "vmeff", "highest");
                            set_paging_time_span_spike_date_each_file(file_number, this_date_all, "vmeff", "highest");
                            set_paging_time_span_spike_time_each_file(file_number, time_value, "vmeff", "highest");
                        }
                        if (t  < t_ll4) {
                            set_paging_time_span_spike_val_each_file(file_number, t, "vmeff", "lowest");
                            set_paging_time_span_spike_date_each_file(file_number, this_date_all, "vmeff", "lowest");
                            set_paging_time_span_spike_time_each_file(file_number, time_value, "vmeff", "lowest");
                        }
                        set_paging_time_span_former_val_each_file(file_number, t, "vmeff");
                    }
                    if (h4 < t) { 
                        set_paging_highest_val(t, "vmeff");
                        set_paging_highest_date(this_date_all, "vmeff");
                        set_paging_highest_time(time_value, "vmeff");
                    }
                    if (l4 > t) {
                        set_paging_lowest_val(t, "vmeff");
                        set_paging_lowest_date(this_date_all, "vmeff");
                        set_paging_lowest_time(time_value, "vmeff");
                    }
                    /* code for graph */
                } else {
                    h = get_paging_avg_highest_val("vmeff");
                    l = get_paging_avg_lowest_val("vmeff");
                    t = strtod(token, &endp);
                    if (h < t) { 
                        set_paging_avg_highest_val(t, "vmeff");
                        set_paging_avg_highest_date(this_date, "vmeff");
                    }
                    if (l > t) {
                        set_paging_avg_lowest_val(t, "vmeff");
                        set_paging_avg_lowest_date(this_date, "vmeff");
                    }

                }
            }
       /* setting values when bread/s line */
       } else if ((strcmp(item_name, "bread/s") == 0) &&(set_to_struct == 0)) {
            s0 = get_io_transfer_rate_spike_val("tps");
            f0 = get_io_transfer_rate_former_val("tps");
            h0 = get_io_transfer_rate_highest_val("tps");
            l0 = get_io_transfer_rate_lowest_val("tps");
            s1 = get_io_transfer_rate_spike_val("bread");
            f1 = get_io_transfer_rate_former_val("bread");
            h1 = get_io_transfer_rate_highest_val("bread");
            l1 = get_io_transfer_rate_lowest_val("bread");
            s2 = get_io_transfer_rate_spike_val("bwrtn");
            f2 = get_io_transfer_rate_former_val("bwrtn");
            h2 = get_io_transfer_rate_highest_val("bwrtn");
            l2 = get_io_transfer_rate_lowest_val("bwrtn");
            ss0 = get_io_transfer_rate_spike_val_each_file(file_number, "tps", "spike");
            ss1 = get_io_transfer_rate_spike_val_each_file(file_number, "bread", "spike");
            ss2 = get_io_transfer_rate_spike_val_each_file(file_number, "bwrtn", "spike");
            ff0 = get_io_transfer_rate_former_val_each_file(file_number, "tps");
            ff1 = get_io_transfer_rate_former_val_each_file(file_number, "bread");
            ff2 = get_io_transfer_rate_former_val_each_file(file_number, "bwrtn");
            hh0 = get_io_transfer_rate_spike_val_each_file(file_number, "tps", "highest");
            hh1 = get_io_transfer_rate_spike_val_each_file(file_number, "bread", "highest");
            hh2 = get_io_transfer_rate_spike_val_each_file(file_number, "bwrtn", "highest");
            ll0 = get_io_transfer_rate_spike_val_each_file(file_number, "tps", "lowest");
            ll1 = get_io_transfer_rate_spike_val_each_file(file_number, "bread", "lowest");
            ll2 = get_io_transfer_rate_spike_val_each_file(file_number, "bwrtn", "lowest");
            t_ss0 = get_io_transfer_rate_time_span_spike_val_each_file(file_number, "tps", "spike");
            t_ss1 = get_io_transfer_rate_time_span_spike_val_each_file(file_number, "bread", "spike");
            t_ss2 = get_io_transfer_rate_time_span_spike_val_each_file(file_number, "bwrtn", "spike");
            t_ff0 = get_io_transfer_rate_time_span_former_val_each_file(file_number, "tps");
            t_ff1 = get_io_transfer_rate_time_span_former_val_each_file(file_number, "bread");
            t_ff2 = get_io_transfer_rate_time_span_former_val_each_file(file_number, "bwrtn");
            t_hh0 = get_io_transfer_rate_time_span_spike_val_each_file(file_number, "tps", "highest");
            t_hh1 = get_io_transfer_rate_time_span_spike_val_each_file(file_number, "bread", "highest");
            t_hh2 = get_io_transfer_rate_time_span_spike_val_each_file(file_number, "bwrtn", "highest");
            t_ll0 = get_io_transfer_rate_time_span_spike_val_each_file(file_number, "tps", "lowest");
            t_ll1 = get_io_transfer_rate_time_span_spike_val_each_file(file_number, "bread", "lowest");
            t_ll2 = get_io_transfer_rate_time_span_spike_val_each_file(file_number, "bwrtn", "lowest");

           /* tps, set the value to struct */
           if (i == get_column_io_transfer_rate("tps")) {
                if (SAR_OPTION == 'Z') {
                    t = strtod(token, &endp);
                    if (strstr(time_value, "Average") != NULL)
                        return 0;
                    set_tmp_val(t);
                    t = get_tmp_val();
                    set_tmp2_val(t - ff0);
                    t2 = get_tmp2_val();
                    set_tmp3_val(t - f0);
                    t3 = get_tmp3_val();
                    set_tmp4_val(t - t_ff0);
                    t4 = get_tmp4_val();
                    if (t > INT_MAX || t < 0)
                        return 0;
                    if ((t3 > s0) && (f0 != 0)) {
                        set_io_transfer_rate_spike_val(t3, "tps");
                        set_io_transfer_rate_spike_date(this_date_all, "tps");
                        set_io_transfer_rate_spike_time(time_value, "tps");
                    }
                    set_io_transfer_rate_former_val(t, "tps");
                    if ((t2 > ss0) && (ff0 != 0)) {
                        set_io_transfer_rate_spike_val_each_file(file_number, t2, "tps", "spike");
                        set_io_transfer_rate_spike_date_each_file(file_number, this_date_all, "tps", "spike");
                        set_io_transfer_rate_spike_time_each_file(file_number, time_value, "tps", "spike");
                    }
                    if (t  > hh0) {
                        set_io_transfer_rate_spike_val_each_file(file_number, t, "tps", "highest");
                        set_io_transfer_rate_spike_date_each_file(file_number, this_date_all, "tps", "highest");
                        set_io_transfer_rate_spike_time_each_file(file_number, time_value, "tps", "highest");
                    }
                    if (t  < ll0) {
                        set_io_transfer_rate_spike_val_each_file(file_number, t, "tps", "lowest");
                        set_io_transfer_rate_spike_date_each_file(file_number, this_date_all, "tps", "lowest");
                        set_io_transfer_rate_spike_time_each_file(file_number, time_value, "tps", "lowest");
                    }
                    set_io_transfer_rate_former_val_each_file(file_number, t, "tps");
                    if (time_span_checked == 1) {
                        if ((t4 > t_ss0) && (t_ff0 != 0)) {
                            set_io_transfer_rate_time_span_spike_val_each_file(file_number, t4, "tps", "spike");
                            set_io_transfer_rate_time_span_spike_date_each_file(file_number, this_date_all, "tps", "spike");
                            set_io_transfer_rate_time_span_spike_time_each_file(file_number, time_value, "tps", "spike");
                        }
                        if (t  > t_hh0) {
                            set_io_transfer_rate_time_span_spike_val_each_file(file_number, t, "tps", "highest");
                            set_io_transfer_rate_time_span_spike_date_each_file(file_number, this_date_all, "tps", "highest");
                            set_io_transfer_rate_time_span_spike_time_each_file(file_number, time_value, "tps", "highest");
                        }
                        if (t  < t_ll0) {
                            set_io_transfer_rate_time_span_spike_val_each_file(file_number, t, "tps", "lowest");
                            set_io_transfer_rate_time_span_spike_date_each_file(file_number, this_date_all, "tps", "lowest");
                            set_io_transfer_rate_time_span_spike_time_each_file(file_number, time_value, "tps", "lowest");
                        }
                        set_io_transfer_rate_time_span_former_val_each_file(file_number, t, "tps");
                    }
                    if (t > h0) {
                        set_io_transfer_rate_highest_val(t, "tps");
                        set_io_transfer_rate_highest_date(this_date_all, "tps");
                        set_io_transfer_rate_highest_time(time_value, "tps");
                    }
                    if (l0 > t) {
                        set_io_transfer_rate_lowest_val(t, "tps");
                        set_io_transfer_rate_lowest_date(this_date_all, "tps");
                        set_io_transfer_rate_lowest_time(time_value, "tps");
                    }
                    /* code for graph */
                } else {
                    h = get_io_transfer_rate_avg_highest_val("tps");
                    l = get_io_transfer_rate_avg_lowest_val("tps");
                    t = strtod(token, &endp);
                    if (h < t) { 
                        set_io_transfer_rate_avg_highest_val(t, "tps");
                        set_io_transfer_rate_avg_highest_date(this_date, "tps");
                    }
                    if (l > t) { 
                        set_io_transfer_rate_avg_lowest_val(t, "tps");
                        set_io_transfer_rate_avg_lowest_date(this_date, "tps");
                    }
                }
           /* bread, set the value to struct */
           } else if (i == get_column_io_transfer_rate( "bread")) {
                if (SAR_OPTION == 'Z') {
                    t = strtod(token, &endp);
                    if (strstr(time_value, "Average") != NULL)
                        return 0;
                    set_tmp_val(t);
                    t = get_tmp_val();
                    set_tmp2_val(t - ff1);
                    t2 = get_tmp2_val();
                    set_tmp3_val(t - f1);
                    t3 = get_tmp3_val();
                    set_tmp4_val(t - t_ff1);
                    t4 = get_tmp4_val();
                    if (t > INT_MAX || t < 0)
                        return 0;
                    if ((t3 > s1) && (f1 != 0)) {
                        set_io_transfer_rate_spike_val(t3, "bread");
                        set_io_transfer_rate_spike_date(this_date_all, "bread");
                        set_io_transfer_rate_spike_time(time_value, "bread");
                    }
                    set_io_transfer_rate_former_val(t, "bread");
                    if ((t2 > ss1) && (ff1 != 0)) {
                        set_io_transfer_rate_spike_val_each_file(file_number, t2, "bread", "spike");
                        set_io_transfer_rate_spike_date_each_file(file_number, this_date_all, "bread", "spike");
                        set_io_transfer_rate_spike_time_each_file(file_number, time_value, "bread", "spike");
                    }
                    if (t  > hh1) {
                        set_io_transfer_rate_spike_val_each_file(file_number, t, "bread", "highest");
                        set_io_transfer_rate_spike_date_each_file(file_number, this_date_all, "bread", "highest");
                        set_io_transfer_rate_spike_time_each_file(file_number, time_value, "bread", "highest");
                    }
                    if (t  < ll1) {
                        set_io_transfer_rate_spike_val_each_file(file_number, t, "bread", "lowest");
                        set_io_transfer_rate_spike_date_each_file(file_number, this_date_all, "bread", "lowest");
                        set_io_transfer_rate_spike_time_each_file(file_number, time_value, "bread", "lowest");
                    }
                    set_io_transfer_rate_former_val_each_file(file_number, t, "bread");
                    if (time_span_checked == 1) {
                        if ((t4 > t_ss1) &&(t_ff1 != 0)) {
                            set_io_transfer_rate_time_span_spike_val_each_file(file_number, t4, "bread", "spike");
                            set_io_transfer_rate_time_span_spike_date_each_file(file_number, this_date_all, "bread", "spike");
                            set_io_transfer_rate_time_span_spike_time_each_file(file_number, time_value, "bread", "spike");
                        }
                        if (t  > t_hh1) {
                            set_io_transfer_rate_time_span_spike_val_each_file(file_number, t, "bread", "highest");
                            set_io_transfer_rate_time_span_spike_date_each_file(file_number, this_date_all, "bread", "highest");
                            set_io_transfer_rate_time_span_spike_time_each_file(file_number, time_value, "bread", "highest");
                        }
                        if (t  < t_ll1) {
                            set_io_transfer_rate_time_span_spike_val_each_file(file_number, t, "bread", "lowest");
                            set_io_transfer_rate_time_span_spike_date_each_file(file_number, this_date_all, "bread", "lowest");
                            set_io_transfer_rate_time_span_spike_time_each_file(file_number, time_value, "bread", "lowest");
                        }
                        set_io_transfer_rate_time_span_former_val_each_file(file_number, t, "bread");
                    }
                    if (h1 < t) {
                        set_io_transfer_rate_highest_val(t, "bread");
                        set_io_transfer_rate_highest_date(this_date_all, "bread");
                        set_io_transfer_rate_highest_time(time_value, "bread");
                    }
                    if (l1 > t) {
                        set_io_transfer_rate_lowest_val(t, "bread");
                        set_io_transfer_rate_lowest_date(this_date_all, "bread");
                        set_io_transfer_rate_lowest_time(time_value, "bread");
                    }
                    /* code for graph */
                } else {
                    h = get_io_transfer_rate_avg_highest_val("bread");
                    l = get_io_transfer_rate_avg_lowest_val("bread");
                    t = strtod(token, &endp);
                    if (h < t) { 
                        set_io_transfer_rate_avg_highest_val(t, "bread");
                        set_io_transfer_rate_avg_highest_date(this_date, "bread");
                    }
                    if (l > t) {
                        set_io_transfer_rate_avg_lowest_val(t, "bread");
                        set_io_transfer_rate_avg_lowest_date(this_date, "bread");
                    }
                }
           /* bwrtn, set the value to struct */
           } else if (i == get_column_io_transfer_rate("bwrtn")) {
                if (SAR_OPTION == 'Z') {
                    t = strtod(token, &endp);
                    if (strstr(time_value, "Average") != NULL)
                        return 0;
                    set_tmp_val(t);
                    t = get_tmp_val();
                    set_tmp2_val(t - ff2);
                    t2 = get_tmp2_val();
                    set_tmp3_val(t - f2);
                    t3 = get_tmp3_val();
                    set_tmp4_val(t - t_ff2);
                    t4 = get_tmp4_val();
                    if (t > INT_MAX || t < 0)
                        return 0;
                    if ((t3 > s2) &&(f2 != 0)) {
                        set_io_transfer_rate_spike_val(t3, "bwrtn");
                        set_io_transfer_rate_spike_date(this_date_all, "bwrtn");
                        set_io_transfer_rate_spike_time(time_value, "bwrtn");
                    }
                    set_io_transfer_rate_former_val(t, "bwrtn");
                    if ((t2 > ss2) &&(ff2 != 0)) {
                        set_io_transfer_rate_spike_val_each_file(file_number, t2, "bwrtn", "spike");
                        set_io_transfer_rate_spike_date_each_file(file_number, this_date_all, "bwrtn", "spike");
                        set_io_transfer_rate_spike_time_each_file(file_number, time_value, "bwrtn", "spike");
                    }
                    if (t  > hh2) {
                        set_io_transfer_rate_spike_val_each_file(file_number, t, "bwrtn", "highest");
                        set_io_transfer_rate_spike_date_each_file(file_number, this_date_all, "bwrtn", "highest");
                        set_io_transfer_rate_spike_time_each_file(file_number, time_value, "bwrtn", "highest");
                    }
                    if (t  < ll2) {
                        set_io_transfer_rate_spike_val_each_file(file_number, t, "bwrtn", "lowest");
                        set_io_transfer_rate_spike_date_each_file(file_number, this_date_all, "bwrtn", "lowest");
                        set_io_transfer_rate_spike_time_each_file(file_number, time_value, "bwrtn", "lowest");
                    }
                    set_io_transfer_rate_former_val_each_file(file_number, t, "bwrtn");
                    if (time_span_checked == 1) {
                        if ((t4 > t_ss2) &&(t_ff2 != 0)) {
                            set_io_transfer_rate_time_span_spike_val_each_file(file_number, t4, "bwrtn", "spike");
                            set_io_transfer_rate_time_span_spike_date_each_file(file_number, this_date_all, "bwrtn", "spike");
                            set_io_transfer_rate_time_span_spike_time_each_file(file_number, time_value, "bwrtn", "spike");
                        }
                        if (t  > t_hh2) {
                            set_io_transfer_rate_time_span_spike_val_each_file(file_number, t, "bwrtn", "highest");
                            set_io_transfer_rate_time_span_spike_date_each_file(file_number, this_date_all, "bwrtn", "highest");
                            set_io_transfer_rate_time_span_spike_time_each_file(file_number, time_value, "bwrtn", "highest");
                        }
                        if (t  < t_ll2) {
                            set_io_transfer_rate_time_span_spike_val_each_file(file_number, t, "bwrtn", "lowest");
                            set_io_transfer_rate_time_span_spike_date_each_file(file_number, this_date_all, "bwrtn", "lowest");
                            set_io_transfer_rate_time_span_spike_time_each_file(file_number, time_value, "bwrtn", "lowest");
                        }
                        set_io_transfer_rate_time_span_former_val_each_file(file_number, t, "bwrtn");
                    }
                    if (t > h2) {
                        set_io_transfer_rate_highest_val(t, "bwrtn");
                        set_io_transfer_rate_highest_date(this_date_all, "bwrtn");
                        set_io_transfer_rate_highest_time(time_value, "bwrtn");
                    }
                    if (l2 > t) {
                        set_io_transfer_rate_lowest_val(t, "bwrtn");
                        set_io_transfer_rate_lowest_date(this_date_all, "bwrtn");
                        set_io_transfer_rate_lowest_time(time_value, "bwrtn");
                    }
                    /* code for graph */
                } else {
                    h = get_io_transfer_rate_avg_highest_val("bwrtn");
                    l = get_io_transfer_rate_avg_lowest_val("bwrtn");
                    t = strtod(token, &endp);
                    if (h < t) {
                        set_io_transfer_rate_avg_highest_val(t, "bwrtn");
                        set_io_transfer_rate_avg_highest_date(this_date, "bwrtn");
                    }
                    if (l > t) {
                        set_io_transfer_rate_avg_lowest_val(t, "bwrtn");
                        set_io_transfer_rate_avg_lowest_date(this_date, "bwrtn");
                    }
                }
           }
       /* setting values when kbmemfree line */
       } else if ((strcmp(item_name, "kbmemfree") == 0) &&(set_to_struct == 0)) {
            s0 = get_memory_spike_val("memused");
            f0 = get_memory_former_val("memused");
            h0 = get_memory_highest_val("memused");
            l0 = get_memory_lowest_val("memused");
            s1 = get_memory_spike_val("kbcommit");
            f1 = get_memory_former_val("kbcommit");
            h1 = get_memory_highest_val("kbcommit");
            l1 = get_memory_lowest_val("kbcommit");
            s2 = get_memory_spike_val("commit");
            f2 = get_memory_former_val("commit");
            h2 = get_memory_highest_val("commit");
            l2 = get_memory_lowest_val("commit");
            ss0 = get_memory_spike_val_each_file(file_number, "memused", "spike");
            ss1 = get_memory_spike_val_each_file(file_number, "kbcommit", "spike");
            ss2 = get_memory_spike_val_each_file(file_number, "commit", "spike");
            ff0 = get_memory_former_val_each_file(file_number, "memused");
            ff1 = get_memory_former_val_each_file(file_number, "kbcommit");
            ff2 = get_memory_former_val_each_file(file_number, "commit");
            hh0 = get_memory_spike_val_each_file(file_number, "memused", "highest");
            hh1 = get_memory_spike_val_each_file(file_number, "kbcommit", "highest");
            hh2 = get_memory_spike_val_each_file(file_number, "commit", "highest");
            ll0 = get_memory_spike_val_each_file(file_number, "memused", "lowest");
            ll1 = get_memory_spike_val_each_file(file_number, "kbcommit", "lowest");
            ll2 = get_memory_spike_val_each_file(file_number, "commit", "lowest");
            t_ss0 = get_memory_time_span_spike_val_each_file(file_number, "memused", "spike");
            t_ss1 = get_memory_time_span_spike_val_each_file(file_number, "kbcommit", "spike");
            t_ss2 = get_memory_time_span_spike_val_each_file(file_number, "commit", "spike");
            t_ff0 = get_memory_time_span_former_val_each_file(file_number, "memused");
            t_ff1 = get_memory_time_span_former_val_each_file(file_number, "kbcommit");
            t_ff2 = get_memory_time_span_former_val_each_file(file_number, "commit");
            t_hh0 = get_memory_time_span_spike_val_each_file(file_number, "memused", "highest");
            t_hh1 = get_memory_time_span_spike_val_each_file(file_number, "kbcommit", "highest");
            t_hh2 = get_memory_time_span_spike_val_each_file(file_number, "commit", "highest");
            t_ll0 = get_memory_time_span_spike_val_each_file(file_number, "memused", "lowest");
            t_ll1 = get_memory_time_span_spike_val_each_file(file_number, "kbcommit", "lowest");
            t_ll2 = get_memory_time_span_spike_val_each_file(file_number, "commit", "lowest");

            /* memused, set the value to struct */
            if (i == get_column_memory("memused")) {
                if (SAR_OPTION == 'Z') {
                    t = strtod(token, &endp);
                    if (strstr(time_value, "Average") != NULL)
                        return 0;
                    set_tmp_val(t);
                    t = get_tmp_val();
                    set_tmp2_val(t - ff0);
                    t2 = get_tmp2_val();
                    set_tmp3_val(t - f0);
                    t3 = get_tmp3_val();
                    set_tmp4_val(t - t_ff0);
                    t4 = get_tmp4_val();
                    if (t > INT_MAX || t < 0)
                        return 0;
                    if ((t3 > s0) &&(f0 != 0)) {
                        set_memory_double_spike_val(t3, "memused");
                        set_memory_spike_date(this_date_all, "memused");
                        set_memory_spike_time(time_value, "memused");

                    }
                    set_memory_double_former_val(t, "memused");
                    if ((t2 > ss0) &&(ff0 != 0)) {
                        set_memory_double_spike_val_each_file(file_number, t2, "memused", "spike");
                        set_memory_spike_date_each_file(file_number, this_date_all, "memused", "spike");
                        set_memory_spike_time_each_file(file_number, time_value, "memused", "spike");
                    }
                    if (t  > hh0) {
                        set_memory_double_spike_val_each_file(file_number, t, "memused", "highest");
                        set_memory_spike_date_each_file(file_number, this_date_all, "memused", "highest");
                        set_memory_spike_time_each_file(file_number, time_value, "memused", "highest");
                    }
                    if (t  < ll0) {
                        set_memory_double_spike_val_each_file(file_number, t, "memused", "lowest");
                        set_memory_spike_date_each_file(file_number, this_date_all, "memused", "lowest");
                        set_memory_spike_time_each_file(file_number, time_value, "memused", "lowest");
                    }
                    set_memory_double_former_val_each_file(file_number, t, "memused");
                    if (time_span_checked == 1) {
                        if ((t4 > t_ss0) &&(t_ff0 != 0)) {
                            set_memory_double_time_span_spike_val_each_file(file_number, t4, "memused", "spike");
                            set_memory_time_span_spike_date_each_file(file_number, this_date_all, "memused", "spike");
                            set_memory_time_span_spike_time_each_file(file_number, time_value, "memused", "spike");
                        }
                        if (t  > t_hh0) {
                            set_memory_double_time_span_spike_val_each_file(file_number, t, "memused", "highest");
                            set_memory_time_span_spike_date_each_file(file_number, this_date_all, "memused", "highest");
                            set_memory_time_span_spike_time_each_file(file_number, time_value, "memused", "highest");
                        }
                        if (t  < t_ll0) {
                            set_memory_double_time_span_spike_val_each_file(file_number, t, "memused", "lowest");
                            set_memory_time_span_spike_date_each_file(file_number, this_date_all, "memused", "lowest");
                            set_memory_time_span_spike_time_each_file(file_number, time_value, "memused", "lowest");
                        }
                        set_memory_double_time_span_former_val_each_file(file_number, t, "memused");
                    }
                    if (t > h0) {
                        set_memory_double_highest_val(t, "memused");
                        set_memory_highest_date(this_date_all, "memused");
                        set_memory_highest_time(time_value, "memused");
                    }
                    if (l0 > t) {
                        set_memory_double_lowest_val(t, "memused");
                        set_memory_lowest_date(this_date_all, "memused");
                        set_memory_lowest_time(time_value, "memused");
                    }
                    /* code for graph */
                    if ((strstr(time_value, ":00:") != NULL) ||
                        (strstr(time_value, ":10:") != NULL) ||
                        (strstr(time_value, ":20:") != NULL) ||
                        (strstr(time_value, ":30:") != NULL) ||
                        (strstr(time_value, ":40:") != NULL) ||
                        (strstr(time_value, ":50:") != NULL)) {
                        char str_tmp_echo[MAX_LINE_LENGTH - 100] = {'\0'};
                        char str_tmp_echo2[MAX_LINE_LENGTH] = {'\0'};
                        char str_tmp_null[MAX_LINE_LENGTH] = {'\0'};
                        char str_tmp_null2[MAX_LINE_LENGTH + 100] = {'\0'};
                        memset(str_tmp_echo, '\0', sizeof(str_tmp_echo));
                        memset(str_tmp_echo2, '\0', sizeof(str_tmp_echo2));
                        memset(str_tmp_null, '\0', sizeof(str_tmp_null));
                        memset(str_tmp_null2, '\0', sizeof(str_tmp_null2));
                        int difference = 0;
                        snprintf(str_tmp_echo, sizeof(str_tmp_echo), "%f", t);
                        snprintf(str_tmp_echo2, sizeof(str_tmp_echo2), "%s,%s,%s,%s,%s", "memused", "memused", this_date_all, time_value, str_tmp_echo);
                        snprintf(str_tmp_null, sizeof(str_tmp_null), "%f", 0.0);
                        snprintf(str_tmp_null2, sizeof(str_tmp_null2), "%s,%s,%s,%s,%s", "memused", "memused", this_date_all, "", str_tmp_null);
                        difference = check_time_continuity(file_number, (char*)get_this_time_all(), (char*)get_this_time_all_former());
                        // absense of data should be zero
                        if (difference > 1)
                            for(int i=0; i<difference; i++)
                                append_list2(&svg_memory_memused_obj, str_tmp_null2, str_tmp_null);
                        else
                            append_list2(&svg_memory_memused_obj, str_tmp_echo2, str_tmp_echo);
                    }
                    /* end code for graph */
                } else {
                    h = get_memory_avg_highest_val("memused");
                    l = get_memory_avg_lowest_val("memused");
                    t = strtod(token, &endp);
                    if (h < t) {
                        set_memory_double_avg_highest_val(t, "memused");
                        set_memory_avg_highest_date(this_date, "memused");
                    }
                    if (l > t) {
                        set_memory_double_avg_lowest_val(t, "memused");
                        set_memory_avg_lowest_date(this_date, "memused");
                    }
                }
            /* kbcommit, set the value to struct */
            } else if (i == get_column_memory("kbcommit")) {
                if (SAR_OPTION == 'Z') {
                    t = strtod(token, &endp);
                    if (strstr(time_value, "Average") != NULL)
                        return 0;
                    set_tmp_val(t);
                    t = get_tmp_val();
                    set_tmp2_val(t - ff1);
                    t2 = get_tmp2_val();
                    set_tmp3_val(t - f1);
                    t3 = get_tmp3_val();
                    set_tmp4_val(t - t_ff1);
                    t4 = get_tmp4_val();
                    if (t > INT_MAX || t < 0)
                        return 0;
                    if ((t3 > s1) && (f1 != 0)) {
                        set_memory_int_spike_val(t3, "kbcommit");
                        set_memory_spike_date(this_date_all, "kbcommit");
                        set_memory_spike_time(time_value, "kbcommit");
                    }
                    set_memory_int_former_val(t, "kbcommit");
                    if ((t2 > ss1) && (ff1 != 0)) {
                        set_memory_int_spike_val_each_file(file_number, t2, "kbcommit", "spike");
                        set_memory_spike_date_each_file(file_number, this_date_all, "kbcommit", "spike");
                        set_memory_spike_time_each_file(file_number, time_value, "kbcommit", "spike");
                    }
                    if (t  > hh1) {
                        set_memory_int_spike_val_each_file(file_number, t, "kbcommit", "highest");
                        set_memory_spike_date_each_file(file_number, this_date_all, "kbcommit", "highest");
                        set_memory_spike_time_each_file(file_number, time_value, "kbcommit", "highest");
                    }
                    if (t  < ll1) {
                        set_memory_int_spike_val_each_file(file_number, t, "kbcommit", "lowest");
                        set_memory_spike_date_each_file(file_number, this_date_all, "kbcommit", "lowest");
                        set_memory_spike_time_each_file(file_number, time_value, "kbcommit", "lowest");
                    }
                    set_memory_int_former_val_each_file(file_number, t, "kbcommit");
                    if (time_span_checked == 1) {
                        if ((t4 > t_ss1) &&(t_ff1 != 0)) {
                            set_memory_int_time_span_spike_val_each_file(file_number, t4, "kbcommit", "spike");
                            set_memory_time_span_spike_date_each_file(file_number, this_date_all, "kbcommit", "spike");
                            set_memory_time_span_spike_time_each_file(file_number, time_value, "kbcommit", "spike");
                        }
                        if (t  > t_hh1) {
                            set_memory_int_time_span_spike_val_each_file(file_number, t, "kbcommit", "highest");
                            set_memory_time_span_spike_date_each_file(file_number, this_date_all, "kbcommit", "highest");
                            set_memory_time_span_spike_time_each_file(file_number, time_value, "kbcommit", "highest");
                        }
                        if (t  < t_ll1) {
                            set_memory_int_time_span_spike_val_each_file(file_number, t, "kbcommit", "lowest");
                            set_memory_time_span_spike_date_each_file(file_number, this_date_all, "kbcommit", "lowest");
                            set_memory_time_span_spike_time_each_file(file_number, time_value, "kbcommit", "lowest");
                        }
                        set_memory_int_time_span_former_val_each_file(file_number, t, "kbcommit");
                    }
                    if (h1 < t) {
                        set_memory_int_highest_val(t, "kbcommit");
                        set_memory_highest_date(this_date_all, "kbcommit");
                        set_memory_highest_time(time_value, "kbcommit");
                    }
                    if (l1 > t) {
                        set_memory_int_lowest_val(t, "kbcommit");
                        set_memory_lowest_date(this_date_all, "kbcommit");
                        set_memory_lowest_time(time_value, "kbcommit");
                    }
                    /* code for graph */
                } else {
                    h = get_memory_avg_highest_val("kbcommit");
                    l = get_memory_avg_lowest_val("kbcommit");
                    t = strtod(token, &endp);
                    if (h < t) {
                        set_memory_int_avg_highest_val(t, "kbcommit");
                        set_memory_avg_highest_date(this_date, "kbcommit");
                    }
                    if (l > t) {
                        set_memory_int_avg_lowest_val(t, "kbcommit");
                        set_memory_avg_lowest_date(this_date, "kbcommit");
                    }
                }
            /* commit, set the value to struct */
            } else if (i == get_column_memory("commit")) {
                if (SAR_OPTION == 'Z') {
                    t = strtod(token, &endp);
                    if (strstr(time_value, "Average") != NULL)
                        return 0;
                    set_tmp_val(t);
                    t = get_tmp_val();
                    set_tmp2_val(t - ff2);
                    t2 = get_tmp2_val();
                    set_tmp3_val(t - f2);
                    t3 = get_tmp3_val();
                    set_tmp4_val(t - t_ff2);
                    t4 = get_tmp4_val();
                    if (t > INT_MAX || t < 0)
                        return 0;
                    if ((t3 > s2) &&(f2 != 0)) {
                        set_memory_double_spike_val(t3, "commit");
                        set_memory_spike_date(this_date_all, "commit");
                        set_memory_spike_time(time_value, "commit");
                    }
                    set_memory_double_former_val(t, "commit");
                    if ((t2 > ss2) &&(ff2 != 0)) {
                        set_memory_double_spike_val_each_file(file_number, t2, "commit", "spike");
                        set_memory_spike_date_each_file(file_number, this_date_all, "commit", "spike");
                        set_memory_spike_time_each_file(file_number, time_value, "commit", "spike");
                    }
                    if (t  > hh2) {
                        set_memory_double_spike_val_each_file(file_number, t, "commit", "highest");
                        set_memory_spike_date_each_file(file_number, this_date_all, "commit", "highest");
                        set_memory_spike_time_each_file(file_number, time_value, "commit", "highest");
                    }
                    if (t  < ll2) {
                        set_memory_double_spike_val_each_file(file_number, t, "commit", "lowest");
                        set_memory_spike_date_each_file(file_number, this_date_all, "commit", "lowest");
                        set_memory_spike_time_each_file(file_number, time_value, "commit", "lowest");
                    }
                    set_memory_double_former_val_each_file(file_number, t, "commit");
                    if (time_span_checked == 1) {
                        if ((t4 > t_ss2) &&(t_ff2 != 0)) {
                            set_memory_double_time_span_spike_val_each_file(file_number, t4, "commit", "spike");
                            set_memory_time_span_spike_date_each_file(file_number, this_date_all, "commit", "spike");
                            set_memory_time_span_spike_time_each_file(file_number, time_value, "commit", "spike");
                        }
                        if (t  > t_hh2) {
                            set_memory_double_time_span_spike_val_each_file(file_number, t, "commit", "highest");
                            set_memory_time_span_spike_date_each_file(file_number, this_date_all, "commit", "highest");
                            set_memory_time_span_spike_time_each_file(file_number, time_value, "commit", "highest");
                        }
                        if (t  < t_ll2) {
                            set_memory_double_time_span_spike_val_each_file(file_number, t, "commit", "lowest");
                            set_memory_time_span_spike_date_each_file(file_number, this_date_all, "commit", "lowest");
                            set_memory_time_span_spike_time_each_file(file_number, time_value, "commit", "lowest");
                        }
                        set_memory_double_time_span_former_val_each_file(file_number, t, "commit");
                    }
                    if (h2 < t) {
                        set_memory_double_highest_val(t, "commit");
                        set_memory_highest_date(this_date_all, "commit");
                        set_memory_highest_time(time_value, "commit");
                    }
                    if (l2 > t) {
                        set_memory_double_lowest_val(t, "commit");
                        set_memory_lowest_date(this_date_all, "commit");
                        set_memory_lowest_time(time_value, "commit");
                    }
                    /* code for graph */
                } else {
                    h = get_memory_avg_highest_val("commit");
                    l = get_memory_avg_lowest_val("commit");
                    t = strtod(token, &endp);
                    if (h < t) {
                        set_memory_double_avg_highest_val(t, "commit");
                        set_memory_avg_highest_date(this_date, "commit");
                    }
                    if (l > t) {
                        set_memory_double_avg_lowest_val(t, "commit");
                        set_memory_avg_lowest_date(this_date, "commit");
                    }
                }
            }
       /* setting values when  kbswpfree line */
       } else if ((strcmp(item_name, "kbswpfree") == 0) &&(set_to_struct == 0)) {
            s0 = get_swpused_spike_val();
            f0 = get_swpused_former_val();
            h0 = get_swpused_highest_val();
            l0 = get_swpused_lowest_val();
            ss0 = get_swpused_spike_val_each_file(file_number, "spike");
            ff0 = get_swpused_former_val_each_file (file_number);
            hh0 = get_swpused_spike_val_each_file(file_number, "highest");
            ll0 = get_swpused_spike_val_each_file(file_number, "lowest");
            t_ss0 = get_swpused_time_span_spike_val_each_file(file_number, "spike");
            t_ff0 = get_swpused_time_span_former_val_each_file (file_number);
            t_hh0 = get_swpused_time_span_spike_val_each_file(file_number, "highest");
            t_ll0 = get_swpused_time_span_spike_val_each_file(file_number, "lowest");

            /* swpused, set the value to struct */
            if (i == get_column_swpused()) {
                if (SAR_OPTION == 'Z') {
                    t = strtod(token, &endp);
                    if (strstr(time_value, "Average") != NULL)
                        return 0;
                    set_tmp_val(t);
                    t = get_tmp_val();
                    set_tmp2_val(t - ff0);
                    t2 = get_tmp2_val();
                    set_tmp3_val(t - f0);
                    t3 = get_tmp3_val();
                    set_tmp4_val(t - t_ff0);
                    t4 = get_tmp4_val();
                    if (t > INT_MAX || t < 0)
                        return 0;
                    if ((t3 > s0) && (f0 != 0)) {
                        set_swpused_spike_val(t3);
                        set_swpused_spike_date(this_date_all);
                        set_swpused_spike_time(time_value);
                    }
                    set_swpused_former_val(t);
                    if ((t2 > ss0) && (ff0 != 0)) {
                        set_swpused_spike_val_each_file(file_number, t2, "spike");
                        set_swpused_spike_date_each_file(file_number, this_date_all, "spike");
                        set_swpused_spike_time_each_file(file_number, time_value, "spike");
                    }
                    if (t  > hh0) {
                        set_swpused_spike_val_each_file(file_number, t, "highest");
                        set_swpused_spike_date_each_file(file_number, this_date_all, "highest");
                        set_swpused_spike_time_each_file(file_number, time_value, "highest");
                    }
                    if (t  < ll0) {
                        set_swpused_spike_val_each_file(file_number, t, "lowest");
                        set_swpused_spike_date_each_file(file_number, this_date_all, "lowest");
                        set_swpused_spike_time_each_file(file_number, time_value, "lowest");
                    }
                    set_swpused_former_val_each_file(file_number, t);
                    if (time_span_checked == 1) {
                        if ((t4 > t_ss0) && (t_ff0 != 0)) {
                            set_swpused_time_span_spike_val_each_file(file_number, t4, "spike");
                            set_swpused_time_span_spike_date_each_file(file_number, this_date_all, "spike");
                            set_swpused_time_span_spike_time_each_file(file_number, time_value, "spike");
                        }
                        if (t  > t_hh0) {
                            set_swpused_time_span_spike_val_each_file(file_number, t, "highest");
                            set_swpused_time_span_spike_date_each_file(file_number, this_date_all, "highest");
                            set_swpused_time_span_spike_time_each_file(file_number, time_value, "highest");
                        }
                        if (t  < t_ll0) {
                            set_swpused_time_span_spike_val_each_file(file_number, t, "lowest");
                            set_swpused_time_span_spike_date_each_file(file_number, this_date_all, "lowest");
                            set_swpused_time_span_spike_time_each_file(file_number, time_value, "lowest");
                        }
                        set_swpused_time_span_former_val_each_file(file_number, t);
                    }
                    if (h0 < t) {
                        set_swpused_highest_val(t);
                        set_swpused_highest_date(this_date_all);
                        set_swpused_highest_time(time_value);
                    }
                    if (l0 > t) {
                        set_swpused_lowest_val(t);
                        set_swpused_lowest_date(this_date_all);
                        set_swpused_lowest_time(time_value);
                    }
                    /* code for graph */
                    if ((strstr(time_value, ":00:") != NULL) ||
                        (strstr(time_value, ":10:") != NULL) ||
                        (strstr(time_value, ":20:") != NULL) ||
                        (strstr(time_value, ":30:") != NULL) ||
                        (strstr(time_value, ":40:") != NULL) ||
                        (strstr(time_value, ":50:") != NULL)) {
                        char str_tmp_echo[MAX_LINE_LENGTH - 100] = {'\0'};
                        char str_tmp_echo2[MAX_LINE_LENGTH] = {'\0'};
                        char str_tmp_null[MAX_LINE_LENGTH] = {'\0'};
                        char str_tmp_null2[MAX_LINE_LENGTH + 100] = {'\0'};
                        memset(str_tmp_echo, '\0', sizeof(str_tmp_echo));
                        memset(str_tmp_echo2, '\0', sizeof(str_tmp_echo2));
                        memset(str_tmp_null, '\0', sizeof(str_tmp_null));
                        memset(str_tmp_null2, '\0', sizeof(str_tmp_null2));
                        int difference = 0;
                        snprintf(str_tmp_echo, sizeof(str_tmp_echo), "%f", t);
                        snprintf(str_tmp_null, sizeof(str_tmp_null), "%f", 0.0);
                        snprintf(str_tmp_echo2, sizeof(str_tmp_echo2), "%s,%s,%s,%s,%s", "swpused", "swpused", this_date_all, time_value, str_tmp_echo);
                        snprintf(str_tmp_null2, sizeof(str_tmp_null2), "%s,%s,%s,%s,%s", "swpused", "swpused", this_date_all, "", str_tmp_null);
                        difference = check_time_continuity(file_number, (char*)get_this_time_all(), (char*)get_this_time_all_former());
                        // absense of data should be zero
                        if (difference > 1)
                            for(int i=0; i<difference; i++)
                                append_list2(&svg_memory_swpused_obj, str_tmp_null2, str_tmp_null);
                        else
                            append_list2(&svg_memory_swpused_obj, str_tmp_echo2, str_tmp_echo);
                    }
                    /* end code for graph */
                } else {
                    h = get_swpused_avg_highest_val();
                    l = get_swpused_avg_lowest_val();
                    t = strtod(token, &endp);
                    if (h < t) { 
                        set_swpused_avg_highest_val(t);
                        set_swpused_avg_highest_date(this_date);
                    }
                    if (l > t) {
                        set_swpused_avg_lowest_val(t);
                        set_swpused_avg_lowest_date(this_date);
                    }
                }
            }
       /* setting values when  dentunusd line */
       } else if ((strcmp(item_name, "dentunusd") == 0) &&(set_to_struct == 0)) {
            s0 = get_kernel_table_spike_val("dentunusd");
            f0 = get_kernel_table_former_val("dentunusd");
            h0 = get_kernel_table_highest_val("dentunusd");
            l0 = get_kernel_table_lowest_val("dentunusd");
            s1 = get_kernel_table_spike_val("file");
            f1 = get_kernel_table_former_val("file");
            h1 = get_kernel_table_highest_val("file");
            l1 = get_kernel_table_lowest_val("file");
            s2 = get_kernel_table_spike_val("inode");
            f2 = get_kernel_table_former_val("inode");
            h2 = get_kernel_table_highest_val("inode");
            l2 = get_kernel_table_lowest_val("inode");
            ss0 = get_kernel_table_spike_val_each_file(file_number, "dentunusd", "spike");
            ss1 = get_kernel_table_spike_val_each_file(file_number, "file", "spike");
            ss2 = get_kernel_table_spike_val_each_file(file_number, "inode", "spike");
            ff0 = get_kernel_table_former_val_each_file(file_number, "dentunusd");
            ff1 = get_kernel_table_former_val_each_file(file_number, "file");
            ff2 = get_kernel_table_former_val_each_file(file_number, "inode");
            hh0 = get_kernel_table_spike_val_each_file(file_number, "dentunusd", "highest");
            hh1 = get_kernel_table_spike_val_each_file(file_number, "file", "highest");
            hh2 = get_kernel_table_spike_val_each_file(file_number, "inode", "highest");
            ll0 = get_kernel_table_spike_val_each_file(file_number, "dentunusd", "lowest");
            ll1 = get_kernel_table_spike_val_each_file(file_number, "file", "lowest");
            ll2 = get_kernel_table_spike_val_each_file(file_number, "inode", "lowest");
            t_ss0 = get_kernel_table_time_span_spike_val_each_file(file_number, "dentunusd", "spike");
            t_ss1 = get_kernel_table_time_span_spike_val_each_file(file_number, "file", "spike");
            t_ss2 = get_kernel_table_time_span_spike_val_each_file(file_number, "inode", "spike");
            t_ff0 = get_kernel_table_time_span_former_val_each_file(file_number, "dentunusd");
            t_ff1 = get_kernel_table_time_span_former_val_each_file(file_number, "file");
            t_ff2 = get_kernel_table_time_span_former_val_each_file(file_number, "inode");
            t_hh0 = get_kernel_table_time_span_spike_val_each_file(file_number, "dentunusd", "highest");
            t_hh1 = get_kernel_table_time_span_spike_val_each_file(file_number, "file", "highest");
            t_hh2 = get_kernel_table_time_span_spike_val_each_file(file_number, "inode", "highest");
            t_ll0 = get_kernel_table_time_span_spike_val_each_file(file_number, "dentunusd", "lowest");
            t_ll1 = get_kernel_table_time_span_spike_val_each_file(file_number, "file", "lowest");
            t_ll2 = get_kernel_table_time_span_spike_val_each_file(file_number, "inode", "lowest");

            /* dentunusd, set the value to struct */
            if (i == get_column_kernel_table("dentunusd")) {
                if (SAR_OPTION == 'Z') {
                    t = strtod(token, &endp);
                    if (strstr(time_value, "Average") != NULL)
                        return 0;
                    set_tmp_val(t);
                    t = get_tmp_val();
                    set_tmp2_val(t - ff0);
                    t2 = get_tmp2_val();
                    set_tmp3_val(t - f0);
                    t3 = get_tmp3_val();
                    set_tmp4_val(t - t_ff0);
                    t4 = get_tmp4_val();
                    if (t > INT_MAX || t < 0)
                        return 0;
                    if ((t3 > s0) &&(f0 != 0)) {
                        set_kernel_table_spike_val(t3, "dentunusd");
                        set_kernel_table_spike_date(this_date_all, "dentunusd");
                        set_kernel_table_spike_time(time_value, "dentunusd");
                    }
                    set_kernel_table_former_val(t, "dentunusd");
                    if ((t2 > ss0) && (ff0 != 0)) {
                        set_kernel_table_spike_val_each_file(file_number, t2, "dentunusd", "spike");
                        set_kernel_table_spike_date_each_file(file_number, this_date_all, "dentunusd", "spike");
                        set_kernel_table_spike_time_each_file(file_number, time_value, "dentunusd", "spike");
                    }
                    if (t  > hh0) {
                        set_kernel_table_spike_val_each_file(file_number, t, "dentunusd", "highest");
                        set_kernel_table_spike_date_each_file(file_number, this_date_all, "dentunusd", "highest");
                        set_kernel_table_spike_time_each_file(file_number, time_value, "dentunusd", "highest");
                    }
                    if (t  < ll0) {
                        set_kernel_table_spike_val_each_file(file_number, t, "dentunusd", "lowest");
                        set_kernel_table_spike_date_each_file(file_number, this_date_all, "dentunusd", "lowest");
                        set_kernel_table_spike_time_each_file(file_number, time_value, "dentunusd", "lowest");
                    }
                    set_kernel_table_former_val_each_file(file_number, t, "dentunusd");
                    if (time_span_checked == 1) {
                        if ((t4 > t_ss0) && (t_ff0 != 0)) {
                            set_kernel_table_time_span_spike_val_each_file(file_number, t4, "dentunusd", "spike");
                            set_kernel_table_time_span_spike_date_each_file(file_number, this_date_all, "dentunusd", "spike");
                            set_kernel_table_time_span_spike_time_each_file(file_number, time_value, "dentunusd", "spike");
                        }
                        if (t  > t_hh0) {
                            set_kernel_table_time_span_spike_val_each_file(file_number, t, "dentunusd", "highest");
                            set_kernel_table_time_span_spike_date_each_file(file_number, this_date_all, "dentunusd", "highest");
                            set_kernel_table_time_span_spike_time_each_file(file_number, time_value, "dentunusd", "highest");
                        }
                        if (t  < t_ll0) {
                            set_kernel_table_time_span_spike_val_each_file(file_number, t, "dentunusd", "lowest");
                            set_kernel_table_time_span_spike_date_each_file(file_number, this_date_all, "dentunusd", "lowest");
                            set_kernel_table_time_span_spike_time_each_file(file_number, time_value, "dentunusd", "lowest");
                        }
                        set_kernel_table_time_span_former_val_each_file(file_number, t, "dentunusd");
                    }
                    if (t > h0) { 
                        set_kernel_table_highest_val(t, "dentunusd");
                        set_kernel_table_highest_date(this_date_all, "dentunusd");
                        set_kernel_table_highest_time(time_value, "dentunusd");
                    }
                    if (l0 > t) {
                        set_kernel_table_lowest_val(t, "dentunusd");
                        set_kernel_table_lowest_date(this_date_all, "dentunusd");
                        set_kernel_table_lowest_time(time_value, "dentunusd");
                    }
                    /* code for graph */
                } else {
                    h = get_kernel_table_avg_highest_val("dentunusd");
                    l = get_kernel_table_avg_lowest_val("dentunusd");
                    t = strtod(token, &endp);
                    if (h < t) { 
                        set_kernel_table_avg_highest_val(t, "dentunusd");
                        set_kernel_table_avg_highest_date(this_date, "dentunusd");
                    }
                    if (l > t) {
                        set_kernel_table_avg_lowest_val(t, "dentunusd");
                        set_kernel_table_avg_lowest_date(this_date, "dentunusd");
                    }
                }
            /* file, set the value to struct */
            } else if (i == get_column_kernel_table("file")) {
                if (SAR_OPTION == 'Z') {
                    t = strtod(token, &endp);
                    if (strstr(time_value, "Average") != NULL)
                        return 0;
                    set_tmp_val(t);
                    t = get_tmp_val();
                    set_tmp2_val(t - ff1);
                    t2 = get_tmp2_val();
                    set_tmp3_val(t - f1);
                    t3 = get_tmp3_val();
                    set_tmp4_val(t - t_ff1);
                    t4 = get_tmp4_val();
                    if (t > INT_MAX || t < 0)
                        return 0;
                    if ((t3 > s1) && (f1 != 0)) {
                        set_kernel_table_spike_val(t3, "file");
                        set_kernel_table_spike_date(this_date_all, "file");
                        set_kernel_table_spike_time(time_value, "file");
                    }
                    set_kernel_table_former_val(t, "file");
                    if ((t2 > ss1) && (ff1 != 0)) {
                        set_kernel_table_spike_val_each_file(file_number, t2, "file", "spike");
                        set_kernel_table_spike_date_each_file(file_number, this_date_all, "file", "spike");
                        set_kernel_table_spike_time_each_file(file_number, time_value, "file", "spike");
                    }
                    if (t  > hh1) {
                        set_kernel_table_spike_val_each_file(file_number, t, "file", "highest");
                        set_kernel_table_spike_date_each_file(file_number, this_date_all, "file", "highest");
                        set_kernel_table_spike_time_each_file(file_number, time_value, "file", "highest");
                    }
                    if (t  < ll1) {
                        set_kernel_table_spike_val_each_file(file_number, t, "file", "lowest");
                        set_kernel_table_spike_date_each_file(file_number, this_date_all, "file", "lowest");
                        set_kernel_table_spike_time_each_file(file_number, time_value, "file", "lowest");
                    }
                    set_kernel_table_former_val_each_file(file_number, t, "file");
                    if (time_span_checked == 1) {
                        if ((t4 > t_ss1) && (t_ff1 != 0)) {
                            set_kernel_table_time_span_spike_val_each_file(file_number, t4, "file", "spike");
                            set_kernel_table_time_span_spike_date_each_file(file_number, this_date_all, "file", "spike");
                            set_kernel_table_time_span_spike_time_each_file(file_number, time_value, "file", "spike");
                        }
                        if (t  > hh1) {
                            set_kernel_table_time_span_spike_val_each_file(file_number, t, "file", "highest");
                            set_kernel_table_time_span_spike_date_each_file(file_number, this_date_all, "file", "highest");
                            set_kernel_table_time_span_spike_time_each_file(file_number, time_value, "file", "highest");
                        }
                        if (t  < ll1) {
                            set_kernel_table_time_span_spike_val_each_file(file_number, t, "file", "lowest");
                            set_kernel_table_time_span_spike_date_each_file(file_number, this_date_all, "file", "lowest");
                            set_kernel_table_time_span_spike_time_each_file(file_number, time_value, "file", "lowest");
                        }
                        set_kernel_table_time_span_former_val_each_file(file_number, t, "file");
                    }
                    if (t > h1) { 
                        set_kernel_table_highest_val(t, "file");
                        set_kernel_table_highest_date(this_date_all, "file");
                        set_kernel_table_highest_time(time_value, "file");
                    }
                    if (l1 > t) {
                        set_kernel_table_lowest_val(t, "file");
                        set_kernel_table_lowest_date(this_date_all, "file");
                        set_kernel_table_lowest_time(time_value, "file");
                    }
                    /* code for graph */
                } else {
                    h = get_kernel_table_avg_highest_val("file");
                    l = get_kernel_table_avg_lowest_val("file");
                    t = strtod(token, &endp);
                    if (h < t) {
                        set_kernel_table_avg_highest_val(t, "file");
                        set_kernel_table_avg_highest_date(this_date, "file");
                    }
                    if (l > t) {
                        set_kernel_table_avg_lowest_val(t, "file");
                        set_kernel_table_avg_lowest_date(this_date, "file");
                    }
                }
            /* inode, set the value to struct */
            } else if (i == get_column_kernel_table("inode")) {
                if (SAR_OPTION == 'Z') {
                    t = strtod(token, &endp);
                    if (strstr(time_value, "Average") != NULL)
                        return 0;
                    set_tmp_val(t);
                    t = get_tmp_val();
                    set_tmp2_val(t - ff2);
                    t2 = get_tmp2_val();
                    set_tmp3_val(t - f2);
                    t3 = get_tmp3_val();
                    set_tmp4_val(t - t_ff2);
                    t4 = get_tmp4_val();
                    if (t > INT_MAX || t < 0)
                        return 0;
                    if ((t3 > s2) && (f2 != 0)) {
                        set_kernel_table_spike_val(t3, "inode");
                        set_kernel_table_spike_date(this_date_all, "inode");
                        set_kernel_table_spike_time(time_value, "inode");
                    }
                    set_kernel_table_former_val(t, "inode");
                    if ((t2 > ss2) && (ff2 != 0)) {
                        set_kernel_table_spike_val_each_file(file_number, t2, "inode", "spike");
                        set_kernel_table_spike_date_each_file(file_number, this_date_all, "inode", "spike");
                        set_kernel_table_spike_time_each_file(file_number, time_value, "inode", "spike");
                    }
                    if (t  > hh2) {
                        set_kernel_table_spike_val_each_file(file_number, t, "inode", "highest");
                        set_kernel_table_spike_date_each_file(file_number, this_date_all, "inode", "highest");
                        set_kernel_table_spike_time_each_file(file_number, time_value, "inode", "highest");
                    }
                    if (t  < ll2) {
                        set_kernel_table_spike_val_each_file(file_number, t, "inode", "lowest");
                        set_kernel_table_spike_date_each_file(file_number, this_date_all, "inode", "lowest");
                        set_kernel_table_spike_time_each_file(file_number, time_value, "inode", "lowest");
                    }
                    set_kernel_table_former_val_each_file(file_number, t, "inode");
                    if (time_span_checked == 1) {
                        if ((t4 > t_ss2) && (t_ff2 != 0)) {
                            set_kernel_table_time_span_spike_val_each_file(file_number, t4, "inode", "spike");
                            set_kernel_table_time_span_spike_date_each_file(file_number, this_date_all, "inode", "spike");
                            set_kernel_table_time_span_spike_time_each_file(file_number, time_value, "inode", "spike");
                        }
                        if (t  > t_hh2) {
                            set_kernel_table_time_span_spike_val_each_file(file_number, t, "inode", "highest");
                            set_kernel_table_time_span_spike_date_each_file(file_number, this_date_all, "inode", "highest");
                            set_kernel_table_time_span_spike_time_each_file(file_number, time_value, "inode", "highest");
                        }
                        if (t  < t_ll2) {
                            set_kernel_table_time_span_spike_val_each_file(file_number, t, "inode", "lowest");
                            set_kernel_table_time_span_spike_date_each_file(file_number, this_date_all, "inode", "lowest");
                            set_kernel_table_time_span_spike_time_each_file(file_number, time_value, "inode", "lowest");
                        }
                        set_kernel_table_time_span_former_val_each_file(file_number, t, "inode");
                    }
                    if (t > h2) { 
                        set_kernel_table_highest_val(t, "inode");
                        set_kernel_table_highest_date(this_date_all, "inode");
                        set_kernel_table_highest_time(time_value, "inode");
                    }
                    if (l2 > t) {
                        set_kernel_table_lowest_val(t, "inode");
                        set_kernel_table_lowest_date(this_date_all, "inode");
                        set_kernel_table_lowest_time(time_value, "inode");
                    }
                    /* code for graph */
                } else {
                    h = get_kernel_table_avg_highest_val("inode");
                    l = get_kernel_table_avg_lowest_val("inode");
                    t = strtod(token, &endp);
                    if (h < t) {
                        set_kernel_table_avg_highest_val(t, "inode");
                        set_kernel_table_avg_highest_date(this_date, "inode");
                    }
                    if (l > t) {
                        set_kernel_table_avg_lowest_val(t, "inode");
                        set_kernel_table_avg_lowest_date(this_date, "inode");
                    }
                }
            }
        /* setting values when runq line */
        } else if ((strcmp(item_name, "runq") == 0) &&(set_to_struct == 0)) {

            s0 = get_ldavg_spike_val("runq_sz");
            f0 = get_ldavg_former_val("runq_sz");
            h0 = get_ldavg_highest_val("runq_sz");
            l0 = get_ldavg_lowest_val("runq_sz");
            s1 = get_ldavg_spike_val("plist_sz");
            f1 = get_ldavg_former_val("plist_sz");
            h1 = get_ldavg_highest_val("plist_sz");
            l1 = get_ldavg_lowest_val("plist_sz");
            s2 = get_ldavg_spike_val("ldavg_one");
            f2 = get_ldavg_former_val("ldavg_one");
            h2 = get_ldavg_highest_val("ldavg_one");
            l2 = get_ldavg_lowest_val("ldavg_one");
            s3 = get_ldavg_spike_val("ldavg_five");
            f3 = get_ldavg_former_val("ldavg_five");
            h3 = get_ldavg_highest_val("ldavg_five");
            l3 = get_ldavg_lowest_val("ldavg_five");
            s4 = get_ldavg_spike_val("ldavg_15");
            f4 = get_ldavg_former_val("ldavg_15");
            h4 = get_ldavg_highest_val("ldavg_15");
            l4 = get_ldavg_lowest_val("ldavg_15");
            ss0 = get_ldavg_spike_val_each_file(file_number, "runq_sz", "spike");
            ss1 = get_ldavg_spike_val_each_file(file_number, "plist_sz", "spike");
            ss2 = get_ldavg_spike_val_each_file(file_number, "ldavg_one", "spike");
            ss3 = get_ldavg_spike_val_each_file(file_number, "ldavg_five", "spike");
            ss4 = get_ldavg_spike_val_each_file(file_number, "ldavg_15", "spike");
            ff0 = get_ldavg_former_val_each_file(file_number, "runq_sz");
            ff1 = get_ldavg_former_val_each_file(file_number, "plist_sz");
            ff2 = get_ldavg_former_val_each_file(file_number, "ldavg_one");
            ff3 = get_ldavg_former_val_each_file(file_number, "ldavg_five");
            ff4 = get_ldavg_former_val_each_file(file_number, "ldavg_15");
            hh0 = get_ldavg_spike_val_each_file(file_number, "runq_sz", "highest");
            hh1 = get_ldavg_spike_val_each_file(file_number, "plist_sz", "highest");
            hh2 = get_ldavg_spike_val_each_file(file_number, "ldavg_one", "highest");
            hh3 = get_ldavg_spike_val_each_file(file_number, "ldavg_five", "highest");
            hh4 = get_ldavg_spike_val_each_file(file_number, "ldavg_15", "highest");
            ll0 = get_ldavg_spike_val_each_file(file_number, "runq_sz", "lowest");
            ll1 = get_ldavg_spike_val_each_file(file_number, "plist_sz", "lowest");
            ll2 = get_ldavg_spike_val_each_file(file_number, "ldavg_one", "lowest");
            ll3 = get_ldavg_spike_val_each_file(file_number, "ldavg_five", "lowest");
            ll4 = get_ldavg_spike_val_each_file(file_number, "ldavg_15", "highest");
            t_ss0 = get_ldavg_time_span_spike_val_each_file(file_number, "runq_sz", "spike");
            t_ss1 = get_ldavg_time_span_spike_val_each_file(file_number, "plist_sz", "spike");
            t_ss2 = get_ldavg_time_span_spike_val_each_file(file_number, "ldavg_one", "spike");
            t_ss3 = get_ldavg_time_span_spike_val_each_file(file_number, "ldavg_five", "spike");
            t_ss4 = get_ldavg_time_span_spike_val_each_file(file_number, "ldavg_15", "spike");
            t_ff0 = get_ldavg_time_span_former_val_each_file(file_number, "runq_sz");
            t_ff1 = get_ldavg_time_span_former_val_each_file(file_number, "plist_sz");
            t_ff2 = get_ldavg_time_span_former_val_each_file(file_number, "ldavg_one");
            t_ff3 = get_ldavg_time_span_former_val_each_file(file_number, "ldavg_five");
            t_ff4 = get_ldavg_time_span_former_val_each_file(file_number, "ldavg_15");
            t_hh0 = get_ldavg_time_span_spike_val_each_file(file_number, "runq_sz", "highest");
            t_hh1 = get_ldavg_time_span_spike_val_each_file(file_number, "plist_sz", "highest");
            t_hh2 = get_ldavg_time_span_spike_val_each_file(file_number, "ldavg_one", "highest");
            t_hh3 = get_ldavg_time_span_spike_val_each_file(file_number, "ldavg_five", "highest");
            t_hh4 = get_ldavg_time_span_spike_val_each_file(file_number, "ldavg_15", "highest");
            t_ll0 = get_ldavg_time_span_spike_val_each_file(file_number, "runq_sz", "lowest");
            t_ll1 = get_ldavg_time_span_spike_val_each_file(file_number, "plist_sz", "lowest");
            t_ll2 = get_ldavg_time_span_spike_val_each_file(file_number, "ldavg_one", "lowest");
            t_ll3 = get_ldavg_time_span_spike_val_each_file(file_number, "ldavg_five", "lowest");
            t_ll4 = get_ldavg_time_span_spike_val_each_file(file_number, "ldavg_15", "lowest");


            /* runq_sz, set the value to struct */
            if (i == get_column_ldavg("runq_sz")) {
                if (SAR_OPTION == 'Z') {
                    t = atoi(token);
                    if (strstr(time_value, "Average") != NULL)
                        return 0;
                    set_tmp_val(t);
                    t = get_tmp_val();
                    set_tmp2_val(t - ff0);
                    t2 = get_tmp2_val();
                    set_tmp3_val(t - f0);
                    t3 = get_tmp3_val();
                    set_tmp4_val(t - t_ff0);
                    t4 = get_tmp4_val();
                    if (t > INT_MAX || t < 0)
                        return 0;
                    if ((t3 > s0) && (f0 != 0)) {
                        set_ldavg_int_spike_val(t3, "runq_sz");
                        set_ldavg_spike_date(this_date_all, "runq_sz");
                        set_ldavg_spike_time(time_value, "runq_sz");
                    }
                    set_ldavg_int_former_val(t, "runq_sz");
                    if ((t2 > ss0) && (ff0 != 0)) {
                        set_ldavg_int_spike_val_each_file(file_number, t2, "runq_sz", "spike");
                        set_ldavg_spike_date_each_file(file_number, this_date_all, "runq_sz", "spike");
                        set_ldavg_spike_time_each_file(file_number, time_value, "runq_sz", "spike");
                    }
                    if (t  > hh0) {
                        set_ldavg_int_spike_val_each_file(file_number, t, "runq_sz", "highest");
                        set_ldavg_spike_date_each_file(file_number, this_date_all, "runq_sz", "highest");
                        set_ldavg_spike_time_each_file(file_number, time_value, "runq_sz", "highest");
                    }
                    if (t  < ll0) {
                        set_ldavg_int_spike_val_each_file(file_number, t, "runq_sz", "lowest");
                        set_ldavg_spike_date_each_file(file_number, this_date_all, "runq_sz", "lowest");
                        set_ldavg_spike_time_each_file(file_number, time_value, "runq_sz", "lowest");
                    }
                    set_ldavg_int_former_val_each_file(file_number, t, "runq_sz");
                    if (time_span_checked == 1) {
                        if ((t4 > t_ss0) && (t_ff0 != 0)) {
                            set_ldavg_int_time_span_spike_val_each_file(file_number, t4, "runq_sz", "spike");
                            set_ldavg_time_span_spike_date_each_file(file_number, this_date_all, "runq_sz", "spike");
                            set_ldavg_time_span_spike_time_each_file(file_number, time_value, "runq_sz", "spike");
                        }
                        if (t  > t_hh0) {
                            set_ldavg_int_time_span_spike_val_each_file(file_number, t, "runq_sz", "highest");
                            set_ldavg_time_span_spike_date_each_file(file_number, this_date_all, "runq_sz", "highest");
                            set_ldavg_time_span_spike_time_each_file(file_number, time_value, "runq_sz", "highest");
                        }
                        if (t  < t_ll0) {
                            set_ldavg_int_time_span_spike_val_each_file(file_number, t, "runq_sz", "lowest");
                            set_ldavg_time_span_spike_date_each_file(file_number, this_date_all, "runq_sz", "lowest");
                            set_ldavg_time_span_spike_time_each_file(file_number, time_value, "runq_sz", "lowest");
                        }
                        set_ldavg_int_time_span_former_val_each_file(file_number, t, "runq_sz");
                    }
                    if (t > h0) { 
                        set_ldavg_int_highest_val(t, "runq_sz");
                        set_ldavg_highest_date(this_date_all, "runq_sz");
                        set_ldavg_highest_time(time_value, "runq_sz");
                    }
                    if (l0 > t) {
                        set_ldavg_int_lowest_val(t, "runq_sz");
                        set_ldavg_lowest_date(this_date_all, "runq_sz");
                        set_ldavg_lowest_time(time_value, "runq_sz");
                    }
                    /* code for graph */
                } else {
                    h = get_ldavg_avg_highest_val("runq_sz");
                    l = get_ldavg_avg_lowest_val("runq_sz");
                    t = atoi(token);
                    if (h < t) {
                        set_ldavg_int_avg_highest_val(t, "runq_sz");
                        set_ldavg_avg_highest_date(this_date, "runq_sz");
                    }
                    if (l > t) {
                        set_ldavg_int_avg_lowest_val(t, "runq_sz");
                        set_ldavg_avg_lowest_date(this_date, "runq_sz");
                    }
                }

            /* plist_sz, set the value to struct */
            } else if (i == get_column_ldavg("plist_sz")) {
                if (SAR_OPTION == 'Z') {
                    t = atoi(token);
                    if (strstr(time_value, "Average") != NULL)
                        return 0;
                    set_tmp_val(t);
                    t = get_tmp_val();
                    set_tmp2_val(t - ff1);
                    t2 = get_tmp2_val();
                    set_tmp3_val(t - f1);
                    t3 = get_tmp3_val();
                    set_tmp4_val(t - t_ff1);
                    t4 = get_tmp4_val();
                    if (t > INT_MAX || t < 0)
                        return 0;
                    if ((t3 > s1) && (f1 != 0)) {
                        set_ldavg_int_spike_val(t3, "plist_sz");
                        set_ldavg_spike_date(this_date_all, "plist_sz");
                        set_ldavg_spike_time(time_value, "plist_sz");
                    }
                    set_ldavg_int_former_val(t, "plist_sz");
                    if ((t2 > ss1) && (ff1 != 0)) {
                        set_ldavg_int_spike_val_each_file(file_number, t2, "plist_sz", "spike");
                        set_ldavg_spike_date_each_file(file_number, this_date_all, "plist_sz", "spike");
                        set_ldavg_spike_time_each_file(file_number, time_value, "plist_sz", "spike");
                    }
                    if (t  > hh1) {
                        set_ldavg_int_spike_val_each_file(file_number, t, "plist_sz", "highest");
                        set_ldavg_spike_date_each_file(file_number, this_date_all, "plist_sz", "highest");
                        set_ldavg_spike_time_each_file(file_number, time_value, "plist_sz", "highest");
                    }
                    if (t  < ll1) {
                        set_ldavg_int_spike_val_each_file(file_number, t, "plist_sz", "lowest");
                        set_ldavg_spike_date_each_file(file_number, this_date_all, "plist_sz", "lowest");
                        set_ldavg_spike_time_each_file(file_number, time_value, "plist_sz", "lowest");
                    }
                    set_ldavg_int_former_val_each_file(file_number, t, "plist_sz");
                    if (time_span_checked == 1) {
                        if ((t4 > t_ss1) && (t_ff1 != 0)) {
                            set_ldavg_int_time_span_spike_val_each_file(file_number, t4, "plist_sz", "spike");
                            set_ldavg_time_span_spike_date_each_file(file_number, this_date_all, "plist_sz", "spike");
                            set_ldavg_time_span_spike_time_each_file(file_number, time_value, "plist_sz", "spike");
                        }
                        if (t  > t_hh1) {
                            set_ldavg_int_time_span_spike_val_each_file(file_number, t, "plist_sz", "highest");
                            set_ldavg_time_span_spike_date_each_file(file_number, this_date_all, "plist_sz", "highest");
                            set_ldavg_time_span_spike_time_each_file(file_number, time_value, "plist_sz", "highest");
                        }
                        if (t  < t_ll1) {
                            set_ldavg_int_time_span_spike_val_each_file(file_number, t, "plist_sz", "lowest");
                            set_ldavg_time_span_spike_date_each_file(file_number, this_date_all, "plist_sz", "lowest");
                            set_ldavg_time_span_spike_time_each_file(file_number, time_value, "plist_sz", "lowest");
                        }
                        set_ldavg_int_time_span_former_val_each_file(file_number, t, "plist_sz");
                    }
                    if (t > h1) {
                        set_ldavg_int_highest_val(t, "plist_sz");
                        set_ldavg_highest_date(this_date_all, "plist_sz");
                        set_ldavg_highest_time(time_value, "plist_sz");
                    }
                    if (l1 > t) {
                        set_ldavg_int_lowest_val(t, "plist_sz");
                        set_ldavg_lowest_date(this_date_all, "plist_sz");
                        set_ldavg_lowest_time(time_value, "plist_az");
                    }
                    /* code for graph */
                } else {
                    h = get_ldavg_avg_highest_val("plist_sz");
                    l = get_ldavg_avg_lowest_val("plist_sz");
                    t = atoi(token);
                    if (h < t) {
                        set_ldavg_int_avg_highest_val(t, "plist_sz");
                        set_ldavg_avg_highest_date(this_date, "plist_sz");
                    }
                    if (l > t) {
                        set_ldavg_int_avg_lowest_val(t, "plist_sz");
                        set_ldavg_avg_lowest_date(this_date, "plist_sz");
                    }

                }
            /* ldavg_1, set the value to struct */
            } else if (i == get_column_ldavg("ldavg_one")) {
                if (SAR_OPTION == 'Z') {
                    t = strtod(token, &endp);
                    if (strstr(time_value, "Average") != NULL)
                        return 0;
                    set_tmp_val(t);
                    t = get_tmp_val();
                    set_tmp2_val(t - ff2);
                    t2 = get_tmp2_val();
                    set_tmp3_val(t - f2);
                    t3 = get_tmp3_val();
                    set_tmp4_val(t - t_ff2);
                    t4 = get_tmp4_val();
                    if (t > INT_MAX || t < 0)
                        return 0;
                    if ((t3 > s2) && (f2 != 0)) {
                        set_ldavg_double_spike_val(t3, "ldavg_one");
                        set_ldavg_spike_date(this_date_all, "ldavg_one");
                        set_ldavg_spike_time(time_value, "ldavg_one");
                    }
                    set_ldavg_double_former_val(t, "ldavg_one");
                    if ((t2 > ss2) && (ff2 != 0)) {
                        set_ldavg_double_spike_val_each_file(file_number, t2, "ldavg_one", "spike");
                        set_ldavg_spike_date_each_file(file_number, this_date_all, "ldavg_one", "spike");
                        set_ldavg_spike_time_each_file(file_number, time_value, "ldavg_one", "spike");
                    }
                    if (t  > hh2) {
                        set_ldavg_double_spike_val_each_file(file_number, t, "ldavg_one", "highest");
                        set_ldavg_spike_date_each_file(file_number, this_date_all, "ldavg_one", "highest");
                        set_ldavg_spike_time_each_file(file_number, time_value, "ldavg_one", "highest");
                    }
                    if (t  < ll2) {
                        set_ldavg_double_spike_val_each_file(file_number, t, "ldavg_one", "lowest");
                        set_ldavg_spike_date_each_file(file_number, this_date_all, "ldavg_one", "lowest");
                        set_ldavg_spike_time_each_file(file_number, time_value, "ldavg_one", "lowest");
                    }
                    set_ldavg_double_former_val_each_file(file_number, t, "ldavg_one");
                    if (time_span_checked == 1) {
                        if ((t4 > t_ss2) && (t_ff2 != 0)) {
                            set_ldavg_double_time_span_spike_val_each_file(file_number, t4, "ldavg_one", "spike");
                            set_ldavg_time_span_spike_date_each_file(file_number, this_date_all, "ldavg_one", "spike");
                            set_ldavg_time_span_spike_time_each_file(file_number, time_value, "ldavg_one", "spike");
                        }
                        if (t  > t_hh2) {
                            set_ldavg_double_time_span_spike_val_each_file(file_number, t, "ldavg_one", "highest");
                            set_ldavg_time_span_spike_date_each_file(file_number, this_date_all, "ldavg_one", "highest");
                            set_ldavg_time_span_spike_time_each_file(file_number, time_value, "ldavg_one", "highest");
                        }
                        if (t  < t_hh2) {
                            set_ldavg_double_time_span_spike_val_each_file(file_number, t, "ldavg_one", "lowest");
                            set_ldavg_time_span_spike_date_each_file(file_number, this_date_all, "ldavg_one", "lowest");
                            set_ldavg_time_span_spike_time_each_file(file_number, time_value, "ldavg_one", "lowest");
                        }
                        set_ldavg_double_time_span_former_val_each_file(file_number, t, "ldavg_one");
                    }
                    if (t > h2) {
                        set_ldavg_double_highest_val(t, "ldavg_one");
                        set_ldavg_highest_date(this_date_all, "ldavg_one");
                        set_ldavg_highest_time(time_value, "ldavg_one");
                    }
                    if (l2 > t) {
                        set_ldavg_double_lowest_val(t, "ldavg_one");
                        set_ldavg_lowest_date(this_date_all, "ldavg_one");
                        set_ldavg_lowest_time(time_value, "ldavg_one");
                    }
                    /* code for graph */
                    if ((strstr(time_value, ":00:") != NULL) ||
                        (strstr(time_value, ":10:") != NULL) ||
                        (strstr(time_value, ":20:") != NULL) ||
                        (strstr(time_value, ":30:") != NULL) ||
                        (strstr(time_value, ":40:") != NULL) ||
                        (strstr(time_value, ":50:") != NULL)) {
                        char str_tmp_echo[MAX_LINE_LENGTH - 100] = {'\0'};
                        char str_tmp_echo2[MAX_LINE_LENGTH] = {'\0'};
                        char str_tmp_null[MAX_LINE_LENGTH] = {'\0'};
                        char str_tmp_null2[MAX_LINE_LENGTH + 100] = {'\0'};
                        memset(str_tmp_echo, '\0', sizeof(str_tmp_echo));
                        memset(str_tmp_echo2, '\0', sizeof(str_tmp_echo2));
                        memset(str_tmp_null, '\0', sizeof(str_tmp_null));
                        memset(str_tmp_null2, '\0', sizeof(str_tmp_null2));
                        int difference = 0;
                        snprintf(str_tmp_echo, sizeof(str_tmp_echo), "%f", t);
                        snprintf(str_tmp_null, sizeof(str_tmp_null), "%f", 0.0);
                        snprintf(str_tmp_echo2, sizeof(str_tmp_echo2), "%s,%s,%s,%s,%s", "ldavg_one", "ldavg_one", this_date_all, time_value, str_tmp_echo);
                        snprintf(str_tmp_null2, sizeof(str_tmp_null2), "%s,%s,%s,%s,%s", "ldavg_one", "ldavg_one", this_date_all, "", str_tmp_null);
                        difference = check_time_continuity(file_number, (char*)get_this_time_all(), (char*)get_this_time_all_former());
                        // absense of data should be zero
                        if (difference > 1)
                            for(int i=0; i<difference; i++)
                                append_list2(&svg_ldavg_one_obj, str_tmp_null2, str_tmp_null);
                        else
                            append_list2(&svg_ldavg_one_obj, str_tmp_echo2, str_tmp_echo);
                    }
                    /* end code for graph */
                } else {
                    h = get_ldavg_avg_highest_val("ldavg_one");
                    l = get_ldavg_avg_lowest_val("ldavg_one");
                    t = strtod(token, &endp);
                    if (h < t) {
                        set_ldavg_double_avg_highest_val(t, "ldavg_one");
                        set_ldavg_avg_highest_date(this_date, "ldavg_one");
                    }
                    if (l > t) {
                        set_ldavg_double_avg_lowest_val(t, "ldavg_one");
                        set_ldavg_avg_lowest_date(this_date, "ldavg_one");
                    }
                }
            /* ldavg_5, set the value to struct */
            } else if (i == get_column_ldavg("ldavg_five")) {
                if (SAR_OPTION == 'Z') {
                    t = strtod(token, &endp);
                    if (strstr(time_value, "Average") != NULL)
                        return 0;
                    set_tmp_val(t);
                    t = get_tmp_val();
                    set_tmp2_val(t - ff3);
                    t2 = get_tmp2_val();
                    set_tmp3_val(t - f3);
                    t3 = get_tmp3_val();
                    set_tmp4_val(t - t_ff3);
                    t4 = get_tmp4_val();
                    if (t > INT_MAX || t < 0)
                        return 0;
                    if ((t3 > s3) && (f3 != 0)) {
                        set_ldavg_double_spike_val(t3, "ldavg_five");
                        set_ldavg_spike_date(this_date_all, "ldavg_five");
                        set_ldavg_spike_time(time_value, "ldavg_five");
                    }
                    set_ldavg_double_former_val(t, "ldavg_five");
                    if ((t2 > ss3) && (ff3 != 0)) {
                        set_ldavg_double_spike_val_each_file(file_number, t2, "ldavg_five", "spike");
                        set_ldavg_spike_date_each_file(file_number, this_date_all, "ldavg_five", "spike");
                        set_ldavg_spike_time_each_file(file_number, time_value, "ldavg_five", "spike");
                    }
                    if (t  > hh3) {
                        set_ldavg_double_spike_val_each_file(file_number, t, "ldavg_five", "highest");
                        set_ldavg_spike_date_each_file(file_number, this_date_all, "ldavg_five", "highest");
                        set_ldavg_spike_time_each_file(file_number, time_value, "ldavg_five", "highest");
                    }
                    if (t  < ll3) {
                        set_ldavg_double_spike_val_each_file(file_number, t, "ldavg_five", "lowest");
                        set_ldavg_spike_date_each_file(file_number, this_date_all, "ldavg_five", "lowest");
                        set_ldavg_spike_time_each_file(file_number, time_value, "ldavg_five", "lowest");
                    }
                    set_ldavg_double_former_val_each_file(file_number, t, "ldavg_five");
                    if (time_span_checked == 1) {
                        if ((t4 > t_ss3) && (t_ff3 != 0)) {
                            set_ldavg_double_time_span_spike_val_each_file(file_number, t4, "ldavg_five", "spike");
                            set_ldavg_time_span_spike_date_each_file(file_number, this_date_all, "ldavg_five", "spike");
                            set_ldavg_time_span_spike_time_each_file(file_number, time_value, "ldavg_five", "spike");
                        }
                        if (t  > t_hh3) {
                            set_ldavg_double_time_span_spike_val_each_file(file_number, t, "ldavg_five", "highest");
                            set_ldavg_time_span_spike_date_each_file(file_number, this_date_all, "ldavg_five", "highest");
                            set_ldavg_time_span_spike_time_each_file(file_number, time_value, "ldavg_five", "highest");
                        }
                        if (t  < t_ll3) {
                            set_ldavg_double_time_span_spike_val_each_file(file_number, t, "ldavg_five", "lowest");
                            set_ldavg_time_span_spike_date_each_file(file_number, this_date_all, "ldavg_five", "lowest");
                            set_ldavg_time_span_spike_time_each_file(file_number, time_value, "ldavg_five", "lowest");
                        }
                        set_ldavg_double_time_span_former_val_each_file(file_number, t, "ldavg_five");
                    }
                    if (t > h3) { 
                        set_ldavg_double_highest_val(t, "ldavg_five");
                        set_ldavg_highest_date(this_date_all, "ldavg_five");
                        set_ldavg_highest_time(time_value, "ldavg_five");
                    }
                    if (l3 > t) {
                        set_ldavg_double_lowest_val(t, "ldavg_five");
                        set_ldavg_lowest_date( this_date_all, "ldavg_five");
                        set_ldavg_lowest_time( time_value, "ldavg_five");
                    }
                    /* code for graph */
                    if ((strstr(time_value, ":00:") != NULL) ||
                        (strstr(time_value, ":10:") != NULL) ||
                        (strstr(time_value, ":20:") != NULL) ||
                        (strstr(time_value, ":30:") != NULL) ||
                        (strstr(time_value, ":40:") != NULL) ||
                        (strstr(time_value, ":50:") != NULL)) {
                        char str_tmp_echo[MAX_LINE_LENGTH - 100] = {'\0'};
                        char str_tmp_echo2[MAX_LINE_LENGTH] = {'\0'};
                        char str_tmp_null[MAX_LINE_LENGTH] = {'\0'};
                        char str_tmp_null2[MAX_LINE_LENGTH + 100] = {'\0'};
                        memset(str_tmp_echo, '\0', sizeof(str_tmp_echo));
                        memset(str_tmp_echo2, '\0', sizeof(str_tmp_echo2));
                        memset(str_tmp_null, '\0', sizeof(str_tmp_null));
                        memset(str_tmp_null2, '\0', sizeof(str_tmp_null2));
                        int difference = 0;
                        snprintf(str_tmp_echo, sizeof(str_tmp_echo), "%f", t);
                        snprintf(str_tmp_null, sizeof(str_tmp_null), "%f", 0.0);
                        snprintf(str_tmp_echo2, sizeof(str_tmp_echo2), "%s,%s,%s,%s,%s", "ldavg_five", "ldavg_five", this_date_all, time_value, str_tmp_echo);
                        snprintf(str_tmp_null2, sizeof(str_tmp_null2), "%s,%s,%s,%s,%s", "ldavg_five", "ldavg_five", this_date_all, "", str_tmp_null);
                        difference = check_time_continuity(file_number, (char*)get_this_time_all(), (char*)get_this_time_all_former());
                        // absense of data should be zero
                        if (difference > 1)
                            for(int i=0; i<difference; i++)
                                append_list2(&svg_ldavg_five_obj, str_tmp_null2, str_tmp_null);
                        else
                            append_list2(&svg_ldavg_five_obj, str_tmp_echo2, str_tmp_echo);
                    }
                    /* end code for graph */
                } else {
                    h = get_ldavg_avg_highest_val("ldavg_five");
                    l = get_ldavg_avg_lowest_val("ldavg_five");
                    t = strtod(token, &endp);
                    if (h < t) {
                        set_ldavg_double_avg_highest_val(t, "ldavg_five");
                        set_ldavg_avg_highest_date(this_date, "ldavg_five");
                    }
                    if (l > t) {
                        set_ldavg_double_avg_lowest_val(t, "ldavg_five");
                        set_ldavg_avg_lowest_date( this_date, "ldavg_five");
                    }
                }
            /* ldavg_15, set the value to struct */
            } else if (i == get_column_ldavg("ldavg_15")) {
                if (SAR_OPTION == 'Z') {
                    t = strtod(token, &endp);
                    if (strstr(time_value, "Average") != NULL)
                        return 0;
                    set_tmp_val(t);
                    t = get_tmp_val();
                    set_tmp2_val(t - ff4);
                    t2 = get_tmp2_val();
                    set_tmp3_val(t - f4);
                    t3 = get_tmp3_val();
                    set_tmp4_val(t - t_ff4);
                    t4 = get_tmp4_val();
                    if (t > INT_MAX || t < 0)
                        return 0;
                    if ((t3 > s4) && (f4 != 0)) {
                        set_ldavg_double_spike_val(t3, "ldavg_15");
                        set_ldavg_spike_date(this_date_all, "ldavg_15");
                        set_ldavg_spike_time(time_value, "ldavg_15");
                    }
                    set_ldavg_double_former_val(t, "ldavg_15");
                    if ((t2 > ss4) && (ff4 != 0)) {
                        set_ldavg_double_spike_val_each_file(file_number, t2, "ldavg_15", "spike");
                        set_ldavg_spike_date_each_file(file_number, this_date_all, "ldavg_15", "spike");
                        set_ldavg_spike_time_each_file(file_number, time_value, "ldavg_15", "spike");
                    }
                    if (t  > hh4) {
                        set_ldavg_double_spike_val_each_file(file_number, t, "ldavg_15", "highest");
                        set_ldavg_spike_date_each_file(file_number, this_date_all, "ldavg_15", "highest");
                        set_ldavg_spike_time_each_file(file_number, time_value, "ldavg_15", "highest");
                    }
                    if (t  < ll4) {
                        set_ldavg_double_spike_val_each_file(file_number, t, "ldavg_15", "lowest");
                        set_ldavg_spike_date_each_file(file_number, this_date_all, "ldavg_15", "lowest");
                        set_ldavg_spike_time_each_file(file_number, time_value, "ldavg_15", "lowest");
                    }
                    set_ldavg_double_former_val_each_file(file_number, t, "ldavg_15");
                    if (time_span_checked == 1) {
                        if ((t4 > t_ss4) && (t_ff4 != 0)) {
                            set_ldavg_double_time_span_spike_val_each_file(file_number, t4, "ldavg_15", "spike");
                            set_ldavg_time_span_spike_date_each_file(file_number, this_date_all, "ldavg_15", "spike");
                            set_ldavg_time_span_spike_time_each_file(file_number, time_value, "ldavg_15", "spike");
                        }
                        if (t  > t_hh4) {
                            set_ldavg_double_time_span_spike_val_each_file(file_number, t, "ldavg_15", "highest");
                            set_ldavg_time_span_spike_date_each_file(file_number, this_date_all, "ldavg_15", "highest");
                            set_ldavg_time_span_spike_time_each_file(file_number, time_value, "ldavg_15", "highest");
                        }
                        if (t  < t_ll4) {
                            set_ldavg_double_time_span_spike_val_each_file(file_number, t, "ldavg_15", "lowest");
                            set_ldavg_time_span_spike_date_each_file(file_number, this_date_all, "ldavg_15", "lowest");
                            set_ldavg_time_span_spike_time_each_file(file_number, time_value, "ldavg_15", "lowest");
                        }
                        set_ldavg_double_time_span_former_val_each_file(file_number, t, "ldavg_15");
                    }
                    if (t > h4) { 
                        set_ldavg_double_highest_val(t, "ldavg_15");
                        set_ldavg_highest_date(this_date_all, "ldavg_15");
                        set_ldavg_highest_time(time_value, "ldavg_15");
                    }
                    if (l4 > t) {
                        set_ldavg_double_lowest_val(t, "ldavg_15");
                        set_ldavg_lowest_date(this_date_all, "ldavg_15");
                        set_ldavg_lowest_time(time_value, "ldavg_15");
                    }
                    /* code for graph */
                    if ((strstr(time_value, ":00:") != NULL) ||
                        (strstr(time_value, ":10:") != NULL) ||
                        (strstr(time_value, ":20:") != NULL) ||
                        (strstr(time_value, ":30:") != NULL) ||
                        (strstr(time_value, ":40:") != NULL) ||
                        (strstr(time_value, ":50:") != NULL)) {
                        char str_tmp_echo[MAX_LINE_LENGTH - 100] = {'\0'};
                        char str_tmp_echo2[MAX_LINE_LENGTH] = {'\0'};
                        char str_tmp_null[MAX_LINE_LENGTH] = {'\0'};
                        char str_tmp_null2[MAX_LINE_LENGTH + 100] = {'\0'};
                        memset(str_tmp_echo, '\0', sizeof(str_tmp_echo));
                        memset(str_tmp_echo2, '\0', sizeof(str_tmp_echo2));
                        memset(str_tmp_null, '\0', sizeof(str_tmp_null));
                        memset(str_tmp_null2, '\0', sizeof(str_tmp_null2));
                        int difference = 0;
                        snprintf(str_tmp_echo, sizeof(str_tmp_echo), "%f", t);
                        snprintf(str_tmp_null, sizeof(str_tmp_null), "%f", 0.0);
                        snprintf(str_tmp_echo2, sizeof(str_tmp_echo2), "%s,%s,%s,%s,%s", "ldavg_15", "ldavg_15", this_date_all, time_value, str_tmp_echo);
                        snprintf(str_tmp_null2, sizeof(str_tmp_null2), "%s,%s,%s,%s,%s", "ldavg_15", "ldavg_15", this_date_all, "", str_tmp_null);
                        difference = check_time_continuity(file_number, (char*)get_this_time_all(), (char*)get_this_time_all_former());
                        // absense of data should be zero
                        if (difference > 1)
                            for(int i=0; i<difference; i++)
                                append_list2(&svg_ldavg_15_obj, str_tmp_null2, str_tmp_null);
                        else
                            append_list2(&svg_ldavg_15_obj, str_tmp_echo2, str_tmp_echo);
                    }
                    /* end code for graph */
                } else {
                    h = get_ldavg_avg_highest_val("ldavg_15");
                    l = get_ldavg_avg_lowest_val("ldavg_15");
                    t = strtod(token, &endp);
                    if (h < t) {
                        set_ldavg_double_avg_highest_val(t, "ldavg_15");
                        set_ldavg_avg_highest_date(this_date, "ldavg_15");
                    }
                    if (l > t) {
                        set_ldavg_double_avg_lowest_val(t, "ldavg_15");
                        set_ldavg_avg_lowest_date(this_date, "ldavg_15");
                    }
                }
            }
       /* setting values when areq-sz line */
       } else if ((strcmp(item_name, "DEV") == 0) &&(set_to_struct == 0)) {
            s0 = get_block_device_spike_val(utility, "areqsz");
            f0 = get_block_device_former_val(utility, "areqsz");
            h0 = get_block_device_highest_val(utility, "areqsz");
            l0 = get_block_device_lowest_val(utility, "areqsz");
            s1 = get_block_device_spike_val(utility, "util");
            f1 = get_block_device_former_val(utility, "util");
            h1 = get_block_device_highest_val(utility, "util");
            l1 = get_block_device_lowest_val(utility, "util");
            ss0 = get_block_device_spike_val_each_file(file_number, utility, "areqsz", "spike");
            ss1 = get_block_device_spike_val_each_file(file_number, utility, "util", "spike");
            ff0 = get_block_device_former_val_each_file(file_number, utility, "areqsz");
            ff1 = get_block_device_former_val_each_file(file_number, utility, "util");
            hh0 = get_block_device_spike_val_each_file(file_number, utility, "areqsz", "highest");
            hh1 = get_block_device_spike_val_each_file(file_number, utility, "util", "highest");
            ll0 = get_block_device_spike_val_each_file(file_number, utility, "areqsz", "lowest");
            ll1 = get_block_device_spike_val_each_file(file_number, utility, "util", "lowest");

           /* areq-sz, set the value to struct */
           if (i == get_column_block_device("areqsz")) {
                if (SAR_OPTION == 'Z') {
                    t = strtod(token, &endp);
                    if (strstr(time_value, "Average") != NULL)
                        return 0;
                    set_tmp_val(t);
                    t = get_tmp_val();
                    set_tmp2_val(t - ff0);
                    t2 = get_tmp2_val();
                    set_tmp3_val(t - f0);
                    t3 = get_tmp3_val();
                    set_tmp4_val(t - t_ff0);
                    t4 = get_tmp4_val();
                    if (t > INT_MAX || t < 0)
                        return 0;
                    if ((t3 > s0) && (f0 != 0)) {
                        set_block_device_spike_val(t3, utility, "areqsz");
                        set_block_device_spike_date(this_date_all, utility, "areqsz");
                        set_block_device_spike_time(time_value, utility, "areqsz");
                    }
                    set_block_device_former_val(t, utility, "areqsz");
                    if ((t2 > ss0) && (ff0 != 0)) {
                        set_block_device_spike_val_each_file(file_number, t2, utility, "areqsz", "spike");
                        set_block_device_spike_date_each_file(file_number, this_date_all, utility, "areqsz", "spike");
                        set_block_device_spike_time_each_file(file_number, time_value, utility, "areqsz", "spike");
                    }
                    if (t  > hh0) {
                        set_block_device_spike_val_each_file(file_number, t, utility, "areqsz", "highest");
                        set_block_device_spike_date_each_file(file_number, this_date_all, utility, "areqsz", "highest");
                        set_block_device_spike_time_each_file(file_number, time_value, utility, "areqsz", "highest");
                    }
                    if (t  < ll0) {
                        set_block_device_spike_val_each_file(file_number, t, utility, "areqsz", "lowest");
                        set_block_device_spike_date_each_file(file_number, this_date_all, utility, "areqsz", "lowest");
                        set_block_device_spike_time_each_file(file_number, time_value, utility, "areqsz", "lowest");
                    }
                    set_block_device_former_val_each_file(file_number, t, utility, "areqsz");
                    if (h0 < t) {
                        set_block_device_highest_val(t, utility, "areqsz");
                        set_block_device_highest_date(this_date_all, utility, "areqsz");
                        set_block_device_highest_time(time_value, utility, "areqsz");
                    }
                    if (l0 > t) {
                        set_block_device_lowest_val(t, utility, "areqsz");
                        set_block_device_lowest_date(this_date_all, utility, "areqsz");
                        set_block_device_lowest_time(time_value, utility, "areqsz");
                    }
                } else {
                    h = get_block_device_avg_highest_val(utility, "areqsz");
                    l = get_block_device_avg_lowest_val(utility, "areqsz");
                    t = strtod(token, &endp);
                    if (h < t) {
                        set_block_device_avg_highest_val(t, utility, "areqsz");
                        set_block_device_avg_highest_date(this_date, utility, "areqsz");
                    }
                    if (l > t) {
                        set_block_device_avg_lowest_val(t, utility, "areqsz");
                        set_block_device_avg_lowest_date(this_date, utility, "areqsz");
                    }
                }
           /* util, set the value to struct */
           } else if (i == get_column_block_device("util")) {
                if (SAR_OPTION == 'Z') {
                    t = strtod(token, &endp);
                    if (strstr(time_value, "Average") != NULL)
                        return 0;
                    set_tmp_val(t);
                    t = get_tmp_val();
                    set_tmp2_val(t - ff1);
                    t2 = get_tmp2_val();
                    set_tmp3_val(t - f1);
                    t3 = get_tmp3_val();
                    set_tmp4_val(t - t_ff1);
                    t4 = get_tmp4_val();
                    if (t > INT_MAX || t < 0)
                        return 0;
                    if ((t3 > s1) && (f1 != 0)) {
                        set_block_device_spike_val(t3, utility, "util");
                        set_block_device_spike_date(this_date_all, utility, "util");
                        set_block_device_spike_time(time_value, utility, "util");
                    }
                    set_block_device_former_val(t, utility, "util");
                    if ((t2 > ss1) && (ff1 != 0)) {
                        set_block_device_spike_val_each_file(file_number, t2, utility, "util", "spike");
                        set_block_device_spike_date_each_file(file_number, this_date_all, utility, "util", "spike");
                        set_block_device_spike_time_each_file(file_number, time_value, utility, "util", "spike");
                    }
                    if (t  > hh1) {
                        set_block_device_spike_val_each_file(file_number, t, utility, "util", "highest");
                        set_block_device_spike_date_each_file(file_number, this_date_all, utility, "util", "highest");
                        set_block_device_spike_time_each_file(file_number, time_value, utility, "util", "highest");
                    }
                    if (t  < ll1) {
                        set_block_device_spike_val_each_file(file_number, t, utility, "util", "lowest");
                        set_block_device_spike_date_each_file(file_number, this_date_all, utility, "util", "lowest");
                        set_block_device_spike_time_each_file(file_number, time_value, utility, "util", "lowest");
                    }
                    set_block_device_former_val_each_file(file_number, t, utility, "util");
                    if (h1 < t) {
                        set_block_device_highest_val(t, utility, "util");
                        set_block_device_highest_date(this_date_all, utility, "util");
                        set_block_device_highest_time(time_value, utility, "util");
                    }
                    if (l1 > t) {
                        set_block_device_lowest_val(t, utility, "util");
                        set_block_device_lowest_date(this_date_all, utility, "util");
                        set_block_device_lowest_time(time_value, utility, "util");
                    }
                    /* code for graph */
                    if ((strstr(time_value, ":00:") != NULL) ||
                        (strstr(time_value, ":10:") != NULL) ||
                        (strstr(time_value, ":20:") != NULL) ||
                        (strstr(time_value, ":30:") != NULL) ||
                        (strstr(time_value, ":40:") != NULL) ||
                        (strstr(time_value, ":50:") != NULL)) {
                        char str_tmp_echo[MAX_LINE_LENGTH - 100] = {'\0'};
                        char str_tmp_echo2[MAX_LINE_LENGTH] = {'\0'};
                        char str_tmp_null[MAX_LINE_LENGTH] = {'\0'};
                        char str_tmp_null2[MAX_LINE_LENGTH + 100] = {'\0'};
                        memset(str_tmp_echo, '\0', sizeof(str_tmp_echo));
                        memset(str_tmp_echo2, '\0', sizeof(str_tmp_echo2));
                        memset(str_tmp_null, '\0', sizeof(str_tmp_null));
                        memset(str_tmp_null2, '\0', sizeof(str_tmp_null2));
                        int difference = 0;
                        snprintf(str_tmp_echo, sizeof(str_tmp_echo), "%f", t);
                        snprintf(str_tmp_null, sizeof(str_tmp_null), "%f", 0.0);
                        // block device utility starts from value 1
                        if (utility >= 1) {
                            snprintf(str_tmp_echo2, sizeof(str_tmp_echo2), "%s,%s,%s,%s,%s", get_block_device_names(utility),
                                "block_device_util", this_date_all, time_value, str_tmp_echo);
                            snprintf(str_tmp_null2, sizeof(str_tmp_null2), "%s,%s,%s,%s,%s", get_block_device_names(utility),
                                "block_device_util", this_date_all, "", str_tmp_null);
                            difference = check_time_continuity(file_number, (char*)get_this_time_all(), (char*)get_this_time_all_former());
                            // absense of data should be zero
                            if (difference > 1)
                                for(int i=0; i<difference; i++)
                                    append_list2(&svg_block_device_util_obj[utility], str_tmp_null2, str_tmp_null);
                            else
                                append_list2(&svg_block_device_util_obj[utility], str_tmp_echo2, str_tmp_echo);
                        }
                    }
                    /* end code for graph */
                } else {
                    h = get_block_device_avg_highest_val(utility, "util");
                    l = get_block_device_avg_lowest_val(utility, "util");
                    t = strtod(token, &endp);
                    if (h < t) {
                        set_block_device_avg_highest_val(t, utility, "util");
                        set_block_device_avg_highest_date(this_date, utility, "util");
                    }
                    if (l > t) {
                        set_block_device_avg_lowest_val(t, utility, "util");
                        set_block_device_avg_lowest_date(this_date, utility, "util");
                    }
                }
           }
       /* setting values when  rxpck line */
       } else if ((strcmp(item_name, "rxpck") == 0) &&(set_to_struct == 0)) {
            s0 = get_network_spike_val(utility, "rxpck");
            f0 = get_network_former_val(utility, "rxpck");
            h0 = get_network_highest_val(utility, "rxpck");
            l0 = get_network_lowest_val(utility, "rxpck");
            s1 = get_network_spike_val(utility, "txpck");
            f1 = get_network_former_val(utility, "txpck");
            h1 = get_network_highest_val(utility, "txpck");
            l1 = get_network_lowest_val(utility, "txpck");
            s2 = get_network_spike_val(utility, "rxkb");
            f2 = get_network_former_val(utility, "rxkb");
            h2 = get_network_highest_val(utility, "rxkb");
            l2 = get_network_lowest_val(utility, "rxkb");
            s3 = get_network_spike_val(utility, "txkb");
            f3 = get_network_former_val(utility, "txkb");
            h3 = get_network_highest_val(utility, "txkb");
            l3 = get_network_lowest_val(utility, "txkb");
            ss0 = get_network_spike_val_each_file(file_number, utility, "rxpck", "spike");
            ss1 = get_network_spike_val_each_file(file_number, utility, "txpck", "spike");
            ss2 = get_network_spike_val_each_file(file_number, utility, "rxkb", "spike");
            ss3 = get_network_spike_val_each_file(file_number, utility, "txkb", "spike");
            ff0 = get_network_former_val_each_file(file_number, utility, "rxpck");
            ff1 = get_network_former_val_each_file(file_number, utility, "txpck");
            ff2 = get_network_former_val_each_file(file_number, utility, "rxkb");
            ff3 = get_network_former_val_each_file(file_number, utility, "txkb");
            hh0 = get_network_spike_val_each_file(file_number, utility, "rxpck", "highest");
            hh1 = get_network_spike_val_each_file(file_number, utility, "txpck", "highest");
            hh2 = get_network_spike_val_each_file(file_number, utility, "rxkb", "highest");
            hh3 = get_network_spike_val_each_file(file_number, utility, "txkb", "highest");
            ll0 = get_network_spike_val_each_file(file_number, utility, "rxpck", "lowest");
            ll1 = get_network_spike_val_each_file(file_number, utility, "txpck", "lowest");
            ll2 = get_network_spike_val_each_file(file_number, utility, "rxkb", "lowest");
            ll3 = get_network_spike_val_each_file(file_number, utility, "txkb", "lowest");

            /* rxpck, set the value to struct */
            if (i == get_column_network("rxpck")) {
                if (SAR_OPTION == 'Z') {
                    t = strtod(token, &endp);
                    if (strstr(time_value, "Average") != NULL)
                        return 0;
                    set_tmp_val(t);
                    t = get_tmp_val();
                    set_tmp2_val(t - ff0);
                    t2 = get_tmp2_val();
                    set_tmp3_val(t - f0);
                    t3 = get_tmp3_val();
                    set_tmp4_val(t - t_ff0);
                    t4 = get_tmp4_val();
                    if (t > INT_MAX || t < 0)
                        return 0;
                    if ((t3 > s0) && (f0 != 0)) {
                        set_network_spike_val(t3, utility, "rxpck");
                        set_network_spike_date(this_date_all, utility, "rxpck");
                        set_network_spike_time(time_value, utility, "rxpck");
                    }
                    set_network_former_val(t, utility, "rxpck");
                    if ((t2 > ss0) && (ff0 != 0)) {
                        set_network_spike_val_each_file(file_number, t2, utility, "rxpck", "spike");
                        set_network_spike_date_each_file(file_number, this_date_all, utility, "rxpck", "spike");
                        set_network_spike_time_each_file(file_number, time_value, utility, "rxpck", "spike");
                    }
                    if (t  > hh0) {
                        set_network_spike_val_each_file(file_number, t, utility, "rxpck", "highest");
                        set_network_spike_date_each_file(file_number, this_date_all, utility, "rxpck", "highest");
                        set_network_spike_time_each_file(file_number, time_value, utility, "rxpck", "highest");
                    }
                    if (t  < ll0) {
                        set_network_spike_val_each_file(file_number, t, utility, "rxpck", "lowest");
                        set_network_spike_date_each_file(file_number, this_date_all, utility, "rxpck", "lowest");
                        set_network_spike_time_each_file(file_number, time_value, utility, "rxpck", "lowest");
                    }
                    if ((t  == 0) && (ff0 > 0)) {
                        set_network_spike_val_each_file(file_number, t, utility, "rxpck", "down");
                        set_network_spike_date_each_file(file_number, this_date_all, utility, "rxpck", "down");
                        set_network_spike_time_each_file(file_number, time_value, utility, "rxpck", "down");
                    }
                    set_network_former_val_each_file(file_number, t, utility, "rxpck");
                    if (h0 < t) {
                        set_network_highest_val(t, utility, "rxpck");
                        set_network_highest_date(this_date_all, utility, "rxpck");
                        set_network_highest_time(time_value, utility, "rxpck");
                    }
                    if (l0 > t) {
                        set_network_lowest_val(t, utility, "rxpck");
                        set_network_lowest_date(this_date_all, utility, "rxpck");
                        set_network_lowest_time(time_value, utility, "rxpck");
                    }
                } else {
                    h = get_network_avg_highest_val(utility, "rxpck");
                    l = get_network_avg_lowest_val(utility, "rxpck");
                    t = strtod(token, &endp);
                    if (h < t) {
                        set_network_avg_highest_val(t, utility, "rxpck");
                        set_network_avg_highest_date(this_date, utility, "rxpck");
                    }
                    if (l > t) {
                        set_network_avg_lowest_val(t, utility, "rxpck");
                        set_network_avg_lowest_date(this_date, utility, "rxpck");
                    }
                }
            /* txpck, set the value to struct */
            } else if (i == get_column_network("txpck")) {
                if (SAR_OPTION == 'Z') {
                    t = strtod(token, &endp);
                    if (strstr(time_value, "Average") != NULL)
                        return 0;
                    set_tmp_val(t);
                    t = get_tmp_val();
                    set_tmp2_val(t - ff1);
                    t2 = get_tmp2_val();
                    set_tmp3_val(t - f1);
                    t3 = get_tmp3_val();
                    set_tmp4_val(t - t_ff1);
                    t4 = get_tmp4_val();
                    if (t > INT_MAX || t < 0)
                        return 0;
                    if ((t3 > s1) && (f1 != 0)) {
                        set_network_spike_val(t3, utility, "txpck");
                        set_network_spike_date(this_date_all, utility, "txpck");
                        set_network_spike_time(time_value, utility, "txpck");
                    }
                    set_network_former_val(t, utility, "txpck");
                    if ((t2 > ss1) &&(ff1 != 0)) {
                        set_network_spike_val_each_file(file_number, t2, utility, "txpck", "spike");
                        set_network_spike_date_each_file(file_number, this_date_all, utility, "txpck", "spike");
                        set_network_spike_time_each_file(file_number, time_value, utility, "txpck", "spike");
                    }
                    if (t  > hh1) {
                        set_network_spike_val_each_file(file_number, t, utility, "txpck", "highest");
                        set_network_spike_date_each_file(file_number, this_date_all, utility, "txpck", "highest");
                        set_network_spike_time_each_file(file_number, time_value, utility, "txpck", "highest");
                    }
                    if (t  < ll1) {
                        set_network_spike_val_each_file(file_number, t, utility, "txpck", "lowest");
                        set_network_spike_date_each_file(file_number, this_date_all, utility, "txpck", "lowest");
                        set_network_spike_time_each_file(file_number, time_value, utility, "txpck", "lowest");
                    }
                    if ((t  == 0) &&(ff1 > 0)) {
                        set_network_spike_val_each_file(file_number, t, utility, "txpck", "down");
                        set_network_spike_date_each_file(file_number, this_date_all, utility, "txpck", "down");
                        set_network_spike_time_each_file(file_number, time_value, utility, "txpck", "down");
                    }
                    set_network_former_val_each_file(file_number, t, utility, "txpck");
                    if (h1 < t) {
                        set_network_highest_val(t ,utility, "txpck");
                        set_network_highest_date(this_date_all, utility, "txpck");
                        set_network_highest_time(time_value, utility, "txpck");
                    }
                    if (l1 > t) {
                        set_network_lowest_val(t, utility, "txpck");
                        set_network_lowest_date(this_date_all, utility, "txpck");
                        set_network_lowest_time(time_value, utility, "txpck");
                    }
                } else {
                    h = get_network_avg_highest_val(utility, "txpck");
                    l = get_network_avg_lowest_val(utility, "txpck");
                    t = strtod(token, &endp);
                    if (h < t) {
                        set_network_avg_highest_val(t ,utility, "txpck");
                        set_network_avg_highest_date(this_date, utility, "txpck");
                    }
                    if (l > t) {
                        set_network_avg_lowest_val(t, utility, "txpck");
                        set_network_avg_lowest_date(this_date, utility, "txpck");
                    }
                }
            /* rxkb, set the value to struct */
            } else if (i == get_column_network("rxkb")) {
                if (SAR_OPTION == 'Z') {
                    t = strtod(token, &endp);
                    if (strstr(time_value, "Average") != NULL)
                        return 0;
                    set_tmp_val(t);
                    t = get_tmp_val();
                    set_tmp2_val(t - ff2);
                    t2 = get_tmp2_val();
                    set_tmp3_val(t - f2);
                    t3 = get_tmp3_val();
                    set_tmp4_val(t - t_ff2);
                    t4 = get_tmp4_val();
                    if (t > INT_MAX || t < 0)
                        return 0;
                    if ((t3 > s2) && (f2 != 0)) {
                        set_network_spike_val(t3, utility, "rxkb");
                        set_network_spike_date(this_date_all, utility, "rxkb");
                        set_network_spike_time(time_value, utility, "rxkb");
                    }
                    set_network_former_val(t, utility, "rxkb");
                    if ((t2 > ss2) && (ff2 != 0)) {
                        set_network_spike_val_each_file(file_number, t2, utility, "rxkb", "spike");
                        set_network_spike_date_each_file(file_number, this_date_all, utility, "rxkb", "spike");
                        set_network_spike_time_each_file(file_number, time_value, utility, "rxkb", "spike");
                    }
                    if (t  > hh2) {
                        set_network_spike_val_each_file(file_number, t, utility, "rxkb", "highest");
                        set_network_spike_date_each_file(file_number, this_date_all, utility, "rxkb", "highest");
                        set_network_spike_time_each_file(file_number, time_value, utility, "rxkb", "highest");
                    }
                    if (t  < ll2) {
                        set_network_spike_val_each_file(file_number, t, utility, "rxkb", "lowest");
                        set_network_spike_date_each_file(file_number, this_date_all, utility, "rxkb", "lowest");
                        set_network_spike_time_each_file(file_number, time_value, utility, "rxkb", "lowest");
                    }
                    if ((t  == 0) && (ff2 > 0)) {
                        set_network_spike_val_each_file(file_number, t, utility, "rxkb", "down");
                        set_network_spike_date_each_file(file_number, this_date_all, utility, "rxkb", "down");
                        set_network_spike_time_each_file(file_number, time_value, utility, "rxkb", "down");
                    }
                    set_network_former_val_each_file(file_number, t, utility, "rxkb");
                    if (h2 < t) {
                        set_network_highest_val(t , utility, "rxkb");
                        set_network_highest_date(this_date_all, utility, "rxkb");
                        set_network_highest_time(time_value, utility, "rxkb");
                    }
                    if (l2 > t) {
                        set_network_lowest_val(t, utility, "rxkb");
                        set_network_lowest_date(this_date_all, utility, "rxkb");
                        set_network_lowest_time(time_value, utility, "rxkb");
                    }
                } else {
                    h = get_network_avg_highest_val(utility, "rxkb");
                    l = get_network_avg_lowest_val(utility, "rxkb");
                    t = strtod(token, &endp);
                    if (h < t) {
                        set_network_avg_highest_val(t , utility, "rxkb");
                        set_network_avg_highest_date(this_date, utility, "rxkb");
                    }
                    if (l > t) {
                        set_network_avg_lowest_val(t, utility, "rxkb");
                        set_network_avg_lowest_date(this_date, utility, "rxkb");
                    }
                }
            /* txkb, set the value to struct */
            } else if (i == get_column_network("txkb")) {
                if (SAR_OPTION == 'Z') {
                    t = strtod(token, &endp);
                    if (strstr(time_value, "Average") != NULL)
                        return 0;
                    set_tmp_val(t);
                    t = get_tmp_val();
                    set_tmp2_val(t - ff3);
                    t2 = get_tmp2_val();
                    set_tmp3_val(t - f3);
                    t3 = get_tmp3_val();
                    set_tmp4_val(t - t_ff3);
                    t4 = get_tmp4_val();
                    if (t > INT_MAX || t < 0)
                        return 0;
                    if ((t3 > s3) && (f3 != 0)) {
                        set_network_spike_val(t3, utility, "txkb");
                        set_network_spike_date(this_date_all, utility, "txkb");
                        set_network_spike_time(time_value, utility, "txkb");
                    }
                    set_network_former_val(t, utility, "txkb");
                    if ((t2 > ss3) && (ff3 != 0)) {
                        set_network_spike_val_each_file(file_number, t2, utility, "txkb", "spike");
                        set_network_spike_date_each_file(file_number, this_date_all, utility, "txkb", "spike");
                        set_network_spike_time_each_file(file_number, time_value, utility, "txkb", "spike");
                    }
                    if (t  > hh3) {
                        set_network_spike_val_each_file(file_number, t , utility, "txkb", "highest");
                        set_network_spike_date_each_file(file_number, this_date_all, utility, "txkb", "highest");
                        set_network_spike_time_each_file(file_number, time_value, utility, "txkb", "highest");
                    }
                    if (t  < ll3) {
                        set_network_spike_val_each_file(file_number, t , utility, "txkb", "lowest");
                        set_network_spike_date_each_file(file_number, this_date_all, utility, "txkb", "lowest");
                        set_network_spike_time_each_file(file_number, time_value, utility, "txkb", "lowest");
                    }
                    if ((t  == 0) &&(ff3 > 0)) {
                        set_network_spike_val_each_file(file_number, t , utility, "txkb", "down");
                        set_network_spike_date_each_file(file_number, this_date_all, utility, "txkb", "down");
                        set_network_spike_time_each_file(file_number, time_value, utility, "txkb", "down");
                    }
                    set_network_former_val_each_file(file_number, t, utility, "txkb");
                    if (h3 < t) {
                        set_network_highest_val(t, utility, "txkb");
                        set_network_highest_date(this_date_all, utility, "txkb");
                        set_network_highest_time(time_value, utility, "txkb");
                    }
                    if (l3 > t) {
                        set_network_lowest_val(t, utility, "txkb");
                        set_network_lowest_date(this_date_all, utility, "txkb");
                        set_network_lowest_time(time_value, utility, "txkb");
                    }
                } else {
                    h = get_network_avg_highest_val(utility, "txkb");
                    l = get_network_avg_lowest_val(utility, "txkb");
                    t = strtod(token, &endp);
                    if (h < t) {
                        set_network_avg_highest_val(t, utility, "txkb");
                        set_network_avg_highest_date(this_date, utility, "txkb");
                    }
                    if (l > t) {
                        set_network_avg_lowest_val(t, utility, "txkb");
                        set_network_avg_lowest_date(this_date, utility, "txkb");
                    }
                }
            }
       /* setting values when  rxerr line */
       } else if ((strcmp(item_name, "rxerr") == 0) &&(set_to_struct == 0)) {
            s0 = get_network_spike_val(utility, "rxerr");
            f0 = get_network_former_val(utility, "rxerr");
            h0 = get_network_highest_val(utility, "rxerr");
            l0 = get_network_lowest_val(utility, "rxerr");
            s1 = get_network_spike_val(utility, "txerr");
            f1 = get_network_former_val(utility, "txerr");
            h1 = get_network_highest_val(utility, "txerr");
            l1 = get_network_lowest_val(utility, "txerr");
            s2 = get_network_spike_val(utility, "rxdrop");
            f2 = get_network_former_val(utility, "rxdrop");
            h2 = get_network_highest_val(utility, "rxdrop");
            l2 = get_network_lowest_val(utility, "rxdrop");
            s3 = get_network_spike_val(utility, "txdrop");
            f3 = get_network_former_val(utility, "txdrop");
            h3 = get_network_highest_val(utility, "txdrop");
            l3 = get_network_lowest_val(utility, "txdrop");
            ss0 = get_network_spike_val_each_file(file_number, utility, "rxerr", "spike");
            ss1 = get_network_spike_val_each_file(file_number, utility, "txerr", "spike");
            ss2 = get_network_spike_val_each_file(file_number, utility, "rxdrop", "spike");
            ss3 = get_network_spike_val_each_file(file_number, utility, "txdrop", "spike");
            ff0 = get_network_former_val_each_file(file_number, utility, "rxerr");
            ff1 = get_network_former_val_each_file(file_number, utility, "txerr");
            ff2 = get_network_former_val_each_file(file_number, utility, "rxdrop");
            ff3 = get_network_former_val_each_file(file_number, utility, "txdrop");
            hh0 = get_network_spike_val_each_file(file_number, utility, "rxerr", "highest");
            hh1 = get_network_spike_val_each_file(file_number, utility, "txerr", "highest");
            hh2 = get_network_spike_val_each_file(file_number, utility, "rxdrop", "highest");
            hh3 = get_network_spike_val_each_file(file_number, utility, "txdrop", "highest");
            ll0 = get_network_spike_val_each_file(file_number, utility, "rxerr", "lowest");
            ll1 = get_network_spike_val_each_file(file_number, utility, "txerr", "lowest");
            ll2 = get_network_spike_val_each_file(file_number, utility, "rxdrop", "lowest");
            ll3 = get_network_spike_val_each_file(file_number, utility, "txdrop", "lowest");

            /* rxerr, set the value to struct */
            if (i == get_column_network("rxerr")) {
                if (SAR_OPTION == 'Z') {
                    t = strtod(token, &endp);
                    if (strstr(time_value, "Average") != NULL)
                        return 0;
                    set_tmp_val(t);
                    t = get_tmp_val();
                    set_tmp2_val(t - ff0);
                    t2 = get_tmp2_val();
                    set_tmp3_val(t - f0);
                    t3 = get_tmp3_val();
                    set_tmp4_val(t - t_ff0);
                    t4 = get_tmp4_val();
                    if (t > INT_MAX || t < 0)
                        return 0;
                    if ((t3 > s0) && (f0 != 0)) {
                        set_network_spike_val(t3, utility, "rxerr");
                        set_network_spike_date(this_date_all, utility, "rxerr");
                        set_network_spike_time(time_value, utility, "rxerr");
                    }
                    set_network_former_val(t, utility, "rxerr");
                    if ((t2 > ss0) && (ff0 != 0)) {
                        set_network_spike_val_each_file(file_number, t2, utility, "rxerr", "spike");
                        set_network_spike_date_each_file(file_number, this_date_all, utility, "rxerr", "spike");
                        set_network_spike_time_each_file(file_number, time_value, utility, "rxerr", "spike");
                    }
                    if (t  > hh0) {
                        set_network_spike_val_each_file(file_number, t, utility, "rxerr", "highest");
                        set_network_spike_date_each_file(file_number, this_date_all, utility, "rxerr", "highest");
                        set_network_spike_time_each_file(file_number, time_value, utility, "rxerr", "highest");
                    }
                    if (t  < ll0) {
                        set_network_spike_val_each_file(file_number, t, utility, "rxerr", "lowest");
                        set_network_spike_date_each_file(file_number, this_date_all, utility, "rxerr", "lowest");
                        set_network_spike_time_each_file(file_number, time_value, utility, "rxerr", "lowest");
                    }
                    if (h0 < t) {
                        set_network_highest_val(t, utility, "rxerr");
                        set_network_highest_date(this_date_all, utility, "rxerr");
                        set_network_highest_time(time_value, utility, "rxerr");
                    }
                    if (l0 > t) {
                        set_network_lowest_val(t, utility, "rxerr");
                        set_network_lowest_date(this_date_all, utility, "rxerr");
                        set_network_lowest_time(time_value, utility, "rxerr");
                    }
                } else {
                    h = get_network_avg_highest_val(utility, "rxerr");
                    l = get_network_avg_lowest_val(utility, "rxerr");
                    t = strtod(token, &endp);
                    if (h < t) {
                        set_network_avg_highest_val(t, utility, "rxerr");
                        set_network_avg_highest_date(this_date, utility, "rxerr");
                    }
                    if (l > t) {
                        set_network_avg_lowest_val(t, utility, "rxerr");
                        set_network_avg_lowest_date(this_date, utility, "rxerr");
                    }
                }
            /* txerr, set the value to struct */
            } else if (i == get_column_network("txerr")) {
                if (SAR_OPTION == 'Z') {
                    t = strtod(token, &endp);
                    if (strstr(time_value, "Average") != NULL)
                        return 0;
                    set_tmp_val(t);
                    t = get_tmp_val();
                    set_tmp2_val(t - ff1);
                    t2 = get_tmp2_val();
                    set_tmp3_val(t - f1);
                    t3 = get_tmp3_val();
                    set_tmp4_val(t - t_ff1);
                    t4 = get_tmp4_val();
                    if (t > INT_MAX || t < 0)
                        return 0;
                    if ((t3 > s1) && (f1 != 0)) {
                        set_network_spike_val(t3, utility, "txerr");
                        set_network_spike_date(this_date_all, utility, "txerr");
                        set_network_spike_time(time_value, utility, "txerr");
                    }
                    set_network_former_val(t, utility, "txerr");
                    if ((t2 > ss1) && (ff1 != 0)) {
                        set_network_spike_val_each_file(file_number, t2, utility, "txerr", "spike");
                        set_network_spike_date_each_file(file_number, this_date_all, utility, "txerr", "spike");
                        set_network_spike_time_each_file(file_number, time_value, utility, "txerr", "spike");
                    }
                    if (t  > hh1) {
                        set_network_spike_val_each_file(file_number, t, utility, "txerr", "highest");
                        set_network_spike_date_each_file(file_number, this_date_all, utility, "txerr", "highest");
                        set_network_spike_time_each_file(file_number, time_value, utility, "txerr", "highest");
                    }
                    if (t  < ll1) {
                        set_network_spike_val_each_file(file_number, t, utility, "txerr", "lowest");
                        set_network_spike_date_each_file(file_number, this_date_all, utility, "txerr", "lowest");
                        set_network_spike_time_each_file(file_number, time_value, utility, "txerr", "lowest");
                    }
                    set_network_former_val_each_file(file_number, t, utility, "txerr");
                    if (h1 < t) {
                        set_network_highest_val(t ,utility, "txerr");
                        set_network_highest_date(this_date_all, utility, "txerr");
                        set_network_highest_time(time_value, utility, "txerr");
                    }
                    if (l1 > t) {
                        set_network_lowest_val(t, utility, "txerr");
                        set_network_lowest_date(this_date_all, utility, "txerr");
                        set_network_lowest_time(time_value, utility, "txerr");
                    }
                } else {
                    h = get_network_avg_highest_val(utility, "txerr");
                    l = get_network_avg_lowest_val(utility, "txerr");
                    t = strtod(token, &endp);
                    if (h < t) {
                        set_network_avg_highest_val(t ,utility, "txerr");
                        set_network_avg_highest_date(this_date, utility, "txerr");
                    }
                    if (l > t) {
                        set_network_avg_lowest_val(t, utility, "txerr");
                        set_network_avg_lowest_date(this_date, utility, "txerr");
                    }
                }
            /* rxdrop, set the value to struct */
            } else if (i == get_column_network("rxdrop")) {
                if (SAR_OPTION == 'Z') {
                    t = strtod(token, &endp);
                    if (strstr(time_value, "Average") != NULL)
                        return 0;
                    set_tmp_val(t);
                    t = get_tmp_val();
                    set_tmp2_val(t - ff2);
                    t2 = get_tmp2_val();
                    set_tmp3_val(t - f2);
                    t3 = get_tmp3_val();
                    set_tmp4_val(t - t_ff2);
                    t4 = get_tmp4_val();
                    if (t > INT_MAX || t < 0)
                        return 0;
                    if ((t3 > s2) && (f2 != 0)) {
                        set_network_spike_val(t3, utility, "rxdrop");
                        set_network_spike_date(this_date_all, utility, "rxdrop");
                        set_network_spike_time(time_value, utility, "rxdrop");
                    }
                    set_network_former_val(t, utility, "rxdrop");
                    if ((t2 > ss2) && (ff2 != 0)) {
                        set_network_spike_val_each_file(file_number, t2, utility, "rxdrop", "spike");
                        set_network_spike_date_each_file(file_number, this_date_all, utility, "rxdrop", "spike");
                        set_network_spike_time_each_file(file_number, time_value, utility, "rxdrop", "spike");
                    }
                    if (t  > hh2) {
                        set_network_spike_val_each_file(file_number, t, utility, "rxdrop", "highest");
                        set_network_spike_date_each_file(file_number, this_date_all, utility, "rxdrop", "highest");
                        set_network_spike_time_each_file(file_number, time_value, utility, "rxdrop", "highest");
                    }
                    if (t  < ll2) {
                        set_network_spike_val_each_file(file_number, t, utility, "rxdrop", "lowest");
                        set_network_spike_date_each_file(file_number, this_date_all, utility, "rxdrop", "lowest");
                        set_network_spike_time_each_file(file_number, time_value, utility, "rxdrop", "lowest");
                    }
                    set_network_former_val_each_file(file_number, t, utility, "rxdrop");
                    if (h2 < t) {
                        set_network_highest_val(t , utility, "rxdrop");
                        set_network_highest_date(this_date_all, utility, "rxdrop");
                        set_network_highest_time(time_value, utility, "rxdrop");
                    }
                    if (l2 > t) {
                        set_network_lowest_val(t, utility, "rxdrop");
                        set_network_lowest_date(this_date_all, utility, "rxdrop");
                        set_network_lowest_time(time_value, utility, "rxdrop");
                    }
                } else {
                    h = get_network_avg_highest_val(utility, "rxdrop");
                    l = get_network_avg_lowest_val(utility, "rxdrop");
                    t = strtod(token, &endp);
                    if (h < t) {
                        set_network_avg_highest_val(t , utility, "rxdrop");
                        set_network_avg_highest_date(this_date, utility, "rxdrop");
                    }
                    if (l > t) {
                        set_network_avg_lowest_val(t, utility, "rxdrop");
                        set_network_avg_lowest_date(this_date, utility, "rxdrop");
                    }
                }
            /* txdrop, set the value to struct */
            } else if (i == get_column_network("txdrop")) {
                if (SAR_OPTION == 'Z') {
                    t = strtod(token, &endp);
                    if (strstr(time_value, "Average") != NULL)
                        return 0;
                    set_tmp_val(t);
                    t = get_tmp_val();
                    set_tmp2_val(t - ff3);
                    t2 = get_tmp2_val();
                    set_tmp3_val(t - f3);
                    t3 = get_tmp3_val();
                    set_tmp4_val(t - t_ff3);
                    t4 = get_tmp4_val();
                    if (t > INT_MAX || t < 0)
                        return 0;
                    if ((t3 > s3) && (f3 != 0)) {
                        set_network_spike_val(t3, utility, "txdrop");
                        set_network_spike_date(this_date_all, utility, "txdrop");
                        set_network_spike_time(time_value, utility, "txdrop");
                    }
                    set_network_former_val(t, utility, "txdrop");
                    if ((t2 > ss3) && (ff3 != 0)) {
                        set_network_spike_val_each_file(file_number, t2, utility, "txdrop", "spike");
                        set_network_spike_date_each_file(file_number, this_date_all, utility, "txdrop", "spike");
                        set_network_spike_time_each_file(file_number, time_value, utility, "txdrop", "spike");
                    }
                    if (t  > hh3) {
                        set_network_spike_val_each_file(file_number, t, utility, "txdrop", "highest");
                        set_network_spike_date_each_file(file_number, this_date_all, utility, "txdrop", "highest");
                        set_network_spike_time_each_file(file_number, time_value, utility, "txdrop", "highest");
                    }
                    if (t  < ll3) {
                        set_network_spike_val_each_file(file_number, t, utility, "txdrop", "lowest");
                        set_network_spike_date_each_file(file_number, this_date_all, utility, "txdrop", "lowest");
                        set_network_spike_time_each_file(file_number, time_value, utility, "txdrop", "lowest");
                    }
                    set_network_former_val_each_file(file_number, t, utility, "txdrop");
                    if (h3 < t) {
                        set_network_highest_val(t, utility, "txdrop");
                        set_network_highest_date(this_date_all, utility, "txdrop");
                        set_network_highest_time(time_value, utility, "txdrop");
                    }
                    if (l3 > t) {
                        set_network_lowest_val(t, utility, "txdrop");
                        set_network_lowest_date(this_date_all, utility, "txdrop");
                        set_network_lowest_time(time_value, utility, "txdrop");
                    }
                } else {
                    h = get_network_avg_highest_val(utility, "txdrop");
                    l = get_network_avg_lowest_val(utility, "txdrop");
                    t = strtod(token, &endp);
                    if (h < t) { 
                        set_network_avg_highest_val(t, utility, "txdrop");
                        set_network_avg_highest_date(this_date, utility, "txdrop");
                    }
                    if (l > t) {
                        set_network_avg_lowest_val(t, utility, "txdrop");
                        set_network_avg_lowest_date(this_date, utility, "txdrop");
                    }
                }
            }
       }
       i++;
    }
    return 0;
}

int get_word_line(int file_number, char **line, int SAR_OPTION, int MESSAGE_ONLY, const char *time_span)
{
    int PM = 0;
    /* for analyzing all data */
    if (SAR_OPTION == 'Z') {
        if (strstr(*line, "PM") != NULL)
            PM = 1;
        /* testing */
        char *str_tmp = "";
        str_tmp = *line;
        if (strstr(*line, "Linux") || strstr(*line, "LINUX")) {
            append_list(&line_all_obj, str_tmp);
            /* this clause will be save for future use maybe */
            if (strstr(*line, "RESTART")) {
                set_token_column(file_number, *line, "Linux", 1, SAR_OPTION);
                /* for ps file */
                linux_restart_count[file_number]++;
            }
            else
                set_token_column(file_number, *line, "Linux", 0, SAR_OPTION);

            /* This is essential and master of this program.
             * In every Linux start, this function should be called.
             */
            initialize_check_int();
        /* first, we are setting column number of interests */
        } else if ((strstr(*line, "Average")) == 0 && (strstr(*line, "usr") || strstr(*line, "sys")   != NULL)) {
            if (MESSAGE_ONLY == 0)
                append_list(&line_all_obj, str_tmp);

            /* calls set_token_column(), call set_token_items() in appropriate manner */
            PM = set_token_column(file_number, *line, "cpu", 0, SAR_OPTION);
            CHECK_CPU_EACH = 1; /* this means to analyze cpus specifically */
            /* this means, skip this clause on next loop, it's enough to set set_token_column() one time */
            CHK_Z = _CPU;
        } else if (strstr(*line,"proc/s") != NULL) {
            if (MESSAGE_ONLY == 0)
                append_list(&line_all_obj, str_tmp);

            /* calls set_token_column(), call set_token_items() in appropriate manner */
            PM = set_token_column(file_number, *line, "proc", 0, SAR_OPTION);
            /* this means, skip this clause on next loop, it's enough to set set_token_column() one time */
            CHK_Z = _TASKS;
        } else if (strstr(*line,"pswpin/s") != NULL) {
            if (MESSAGE_ONLY == 0)
                append_list(&line_all_obj, str_tmp);

            /* calls set_token_column(), call set_token_items() in appropriate manner */
            PM = set_token_column(file_number, *line, "pswpin/s", 0, SAR_OPTION);
            /* this means, skip this clause on next loop, it's enough to set set_token_column() one time */
            CHK_Z = _PSWAP;
        } else if (strstr(*line,"pgpgin/s") != NULL) {
            if (MESSAGE_ONLY == 0)
                append_list(&line_all_obj, str_tmp);

            /* calls set_token_column(), call set_token_items() in appropriate manner */
            PM = set_token_column(file_number, *line, "fault", 0, SAR_OPTION);
            /* this means, skip this clause on next loop, it's enough to set set_token_column() one time */
            CHK_Z = _PAGING;
        } else if (strstr(*line,"bread/s") != NULL) {
            if (MESSAGE_ONLY == 0)
                append_list(&line_all_obj, str_tmp);

            /* calls set_token_column(), call set_token_items() in appropriate manner */
            PM = set_token_column(file_number, *line, "bread/s", 0, SAR_OPTION);
            /* this means, skip this clause on next loop, it's enough to set set_token_column() one time */
            CHK_Z = _IO_TRANSFER_RATE;
        } else if (strstr(*line,"kbmemfree") != NULL) {
            if (MESSAGE_ONLY == 0)
                append_list(&line_all_obj, str_tmp);

            /* calls set_token_column(), call set_token_items() in appropriate manner */
            PM = set_token_column(file_number, *line, "kbmemfree", 0, SAR_OPTION);
            /* this means, skip this clause on next loop, it's enough to set set_token_column() one time */
            CHK_Z = _MEMORY;
        } else if (strstr(*line,"kbswpfree") != NULL) {
            if (MESSAGE_ONLY == 0)
                append_list(&line_all_obj, str_tmp);

            /* calls set_token_column(), call set_token_items() in appropriate manner */
            PM = set_token_column(file_number, *line, "kbswpfree", 0, SAR_OPTION);
            /* this means, skip this clause on next loop, it's enough to set set_token_column() one time */
            CHK_Z = _SWPUSED;
        } else if (strstr(*line,"dentunusd") != NULL) {
            if (MESSAGE_ONLY == 0)
                append_list(&line_all_obj, str_tmp);

            /* calls set_token_column(), call set_token_items() in appropriate manner */
            PM = set_token_column(file_number, *line, "dentunusd", 0, SAR_OPTION);
            /* this means, skip this clause on next loop, it's enough to set set_token_column() one time */
            CHK_Z = _KERNEL_TABLE;
        } else if (strstr(*line,"runq-sz") != NULL) {
            if (MESSAGE_ONLY == 0)
                append_list(&line_all_obj, str_tmp);

            /* calls set_token_column(), call set_token_items() in appropriate manner */
            PM = set_token_column(file_number, *line, "runq", 0, SAR_OPTION);
            /* this means, skip this clause on next loop, it's enough to set set_token_column() one time */
            CHK_Z = _LDAVG;
        } else if ((strstr(*line, "Average")) == 0 && strstr(*line,"DEV") != NULL) {
            if (MESSAGE_ONLY == 0)
                append_list(&line_all_obj, str_tmp);

            /* calls set_token_column(), call set_token_items() in appropriate manner */
            PM = set_token_column(file_number, *line, "DEV", 0, SAR_OPTION);
            /* this means, skip this clause on next loop, it's enough to set set_token_column() one time */
            CHK_Z = _BLOCK_DEVICE;
        } else if ((strstr(*line, "Average")) == 0 && strstr(*line,"rxpck/s") != NULL) {
            if (MESSAGE_ONLY == 0)
                append_list(&line_all_obj, str_tmp);

            /* calls set_token_column(), call set_token_items() in appropriate manner */
            PM = set_token_column(file_number, *line, "rxpck", 0, SAR_OPTION);
            /* this means, skip this clause on next loop, it's enough to set set_token_column() one time */
            CHK_Z = _NETWORK;
        } else if ((strstr(*line, "Average")) == 0 && strstr (*line,"rxerr/s") != NULL) {
            if (MESSAGE_ONLY == 0)
                append_list(&line_all_obj, str_tmp);

            /* calls set_token_column(), call set_token_items() in appropriate manner */
            PM = set_token_column(file_number, *line, "rxerr", 0, SAR_OPTION);
            /* this means, skip this clause on next loop, it's enough to set set_token_column() one time */
            CHK_Z = _NETWORK_ERROR;
        }
        /* end -- first, we are setting column number of interests */

        /* THIS IS THE MAIN FEATURE OF THIS PROGRAM */

        /* for cpus setting values to arrays
         * during the while loop, if CHK_CORES_N is under MAX_CORE_NUMBERS,
         * this clause will be called and sets item values for each
         * cpu and sets core number every time. core number is incremented,
         * so, lately, core number could be known (including all line)  
         * stop calling this clause if reached up to MAX_CORE_NUMBERS, anyway,
         * it will not be called very soon   
         */
        if (CHK_Z == _CPU) {
            /* ignore empty line */
            if (strcmp(*line, "") == 0) 
                return 0;
            if (strstr(*line, "all") != NULL) {
                CHK_CORES_N = 0;
                if (MESSAGE_ONLY == 0)
                    append_list(&line_all_obj, str_tmp);
                set_token_items(file_number, line, "cpu" , CHK_CORES_N, SAR_OPTION, time_span, PM);
                /* as counted cpu as paragraph, if it's up to it, stop echoeing lines */
                if (CHECK_CPU_EACH == get_cpu_as_paragraph()) {
                    /* CHK_Z &= ~(1 << 0); */ /* this means, skip this clause on next loop */
                    CHK_CORES_N = 0;
                }
                CHECK_CPU_EACH++;
            } else if (strstr(*line, "Average") != 0) {
                CHK_Z &= ~(1 << 0);  /* this means, skip this clause on next loop */
                CHK_CORES_N = 0;
                /* set_token_items(file_number, line, "cpu" , CHK_CORES_N, SAR_OPTION); */
                /* we want to let ps that this is the end of the sequence */
            } else {
                CHK_CORES_N++;
                if (MESSAGE_ONLY == 0)
                    append_list(&line_all_obj, str_tmp);

                set_core_numbers(CHK_CORES_N);
                set_token_items(file_number, line, "cpu" , CHK_CORES_N, SAR_OPTION, time_span, PM);

                if (CHK_CORES_N == MAX_CORE_NUMBERS)
                    CHK_Z &= ~(1 << 0);  /* this means, skip this clause on next loop */
            }
        /* setting utility arguments to meaningless value like -999 */
        } else if (CHK_Z == _TASKS) {
            if (strstr (*line, "Average") != 0)
                CHK_Z &= ~(1 << 1);  /* this means, skip this clause on next loop */
            else {
                if (MESSAGE_ONLY == 0)
                    append_list(&line_all_obj, str_tmp);

                set_token_items(file_number, line, "proc", -999, SAR_OPTION, time_span, PM);
            }
        } else if (CHK_Z == _PSWAP) {
            if (strstr (*line, "Average") != 0)
                CHK_Z &= ~(1 << 2);  /* this means, skip this clause on next loop */
            else {
                if (MESSAGE_ONLY == 0)
                    append_list(&line_all_obj, str_tmp);

                set_token_items(file_number, line, "pswpin/s", -999, SAR_OPTION, time_span, PM);
            }
        } else if (CHK_Z == _PAGING) {
            if (strstr (*line, "Average") != 0)
                CHK_Z &= ~(1 << 3);  /* this means, skip this clause on next loop */
            else {
                if (MESSAGE_ONLY == 0)
                    append_list(&line_all_obj, str_tmp);

                set_token_items(file_number, line, "fault", -999, SAR_OPTION, time_span, PM);
            }
        } else if (CHK_Z == _IO_TRANSFER_RATE) {
            if (strstr (*line, "Average") != 0)
                CHK_Z &= ~(1 << 4);  /* this means, skip this clause on next loop */
            else {
                if (MESSAGE_ONLY == 0)
                    append_list(&line_all_obj, str_tmp);

                set_token_items(file_number, line, "bread/s", -999, SAR_OPTION, time_span, PM);
            }
        } else if (CHK_Z == _MEMORY) {
            if (strstr (*line, "Average") != 0)
                CHK_Z &= ~(1 << 5);  /* this means, skip this clause on next loop */
            else {
                if (MESSAGE_ONLY == 0)
                    append_list(&line_all_obj, str_tmp);

                set_token_items(file_number, line, "kbmemfree", -999, SAR_OPTION, time_span, PM);
            }
        } else if (CHK_Z == _SWPUSED) {
            if (strstr (*line, "Average") != 0)
                CHK_Z &= ~(1 << 6);  /* this means, skip this clause on next loop */
            else {
                if (MESSAGE_ONLY == 0)
                    append_list(&line_all_obj, str_tmp);

                set_token_items(file_number, line, "kbswpfree", -999, SAR_OPTION, time_span, PM);
            }
        } else if (CHK_Z == _KERNEL_TABLE) {
            if (strstr (*line, "Average") != 0)
                CHK_Z &= ~(1 << 7);  /* this means, skip this clause on next loop */
            else {
                if (MESSAGE_ONLY == 0)
                    append_list(&line_all_obj, str_tmp);

                set_token_items(file_number, line, "dentunusd", -999, SAR_OPTION, time_span, PM);
            }
        } else if (CHK_Z == _LDAVG) {
            if (strstr (*line, "Average") != 0)
                CHK_Z &= ~(1 << 8);  /* this means, skip this clause on next loop */
            else {
                if (MESSAGE_ONLY == 0)
                    append_list(&line_all_obj, str_tmp);

                set_token_items(file_number, line, "runq", -999, SAR_OPTION, time_span, PM);
            }
        /* for devices (DEV) setting values to arrays
         * just because not knowing which block device will appear every time this clause is called,
         * setting each name to the object for future use 
         */ 
        } else if (CHK_Z == _BLOCK_DEVICE) {
            if (strstr (*line, "Average") != 0)
                CHK_Z &= ~(1 << 9);  /* this means, skip this clause on next loop */
            else {
                if (MESSAGE_ONLY == 0)
                    append_list(&line_all_obj, str_tmp);

                set_token_items(file_number, line, "DEV" , -999, SAR_OPTION, time_span, PM);
            }
        /* for devices (NET rxpck/s) setting values to arrays
         * just because not knowing which network device will appear every time this clause is called,
         * setting each name to the object for future use 
         */ 
        } else if (CHK_Z == _NETWORK) {
            if (strstr (*line, "Average") != 0)
                CHK_Z &= ~(1 << 10);  /* this means, skip this clause on next loop */
            else {
                if (MESSAGE_ONLY == 0)
                    append_list(&line_all_obj, str_tmp);

                set_token_items(file_number, line, "rxpck" , -999, SAR_OPTION, time_span, PM);
            }
        } else if (CHK_Z == _NETWORK_ERROR) {
            if (strstr (*line, "Average") != 0)
                CHK_Z &= ~(1 << 11);  /* this means, skip this clause on next loop */
            else {
                if (MESSAGE_ONLY == 0)
                    append_list(&line_all_obj, str_tmp);

                /* setting utility arguments to meaningless value */
                set_token_items(file_number, line, "rxerr", -999, SAR_OPTION, time_span, PM);
            }
        }
        /* end -- THIS IS THE MAIN FEATURE OF THIS PROGRAM */
    } else {
        /* if these words do not match, skipping, means each line with timestamp on it and blank lines */
        if (strstr(*line, "Linux") == 0 && strstr(*line, "LINUX") == 0 && strstr(*line, "%idle") == 0 
            && strstr(*line, "pgpgin/s") == 0 && strstr(*line, "DEV") == 0 
            && strstr(*line, "bread/s") == 0 && strstr(*line, "kbhugfree") == 0 
            && strstr(*line, "rxpck/s") == 0 && strstr(*line, "rxerr/s") == 0 
            && strstr(*line, "runq-sz") == 0 && strstr(*line, "kbmemfree") == 0 
            && strstr(*line, "kbswpfree") == 0 && strstr(*line, "dentunusd") == 0 
            && strstr(*line, "pswpin/s") == 0 && strstr(*line, "procs/s") == 0 
            && strstr(*line, "rcvin/s") == 0 && strstr(*line, "cswch/s") == 0 
            && strstr(*line, "frmpg/s") == 0 && strstr(*line, "call/s") == 0 
            && strstr(*line, "scall/s") == 0 && strstr(*line, "totsck") == 0 
            && strstr(*line, "total/s") == 0 && strstr(*line, "Average") == 0) {
            /* no match */
            return 0;
        } else {
            int PM = 0;
            char *str_tmp = "";
            str_tmp = *line;

            if (strstr(*line, "Linux") || strstr(*line, "LINUX")) {
                append_list(&line_obj, str_tmp);
                /* this clause will be save for future use maybe */
                if (strstr(*line, "RESTART"))
                    set_token_column(file_number, *line, "Linux", 1, SAR_OPTION);
                else
                    set_token_column(file_number, *line, "Linux", 0, SAR_OPTION);

                /* This is essential and master of this program.
                 * In every Linux start, this function should be called.
                 */
                initialize_check_int();
            /* for this item, there may be many cpus, so Average clause should be special one */
            } else if ((!( CHK_A >> 0) & 1) &&(strstr(*line, "usr") ||(strstr(*line, "sys"))) != 0) {
                CHK_A &= ~(1 << 2);
                CHK_A &= ~(1 << 5);
                CHK_A &= ~(1 << 6);
                SHOW_AVG = 1;
                if (SAR_OPTION == 'u' || SAR_OPTION == 'A') {
                    append_list(&line_obj, "");
                    append_list(&line_obj, str_tmp);
                    if (strstr(*line, "CPU") != NULL)
                        /* calls set_token_column(), call set_token_items() in appropriate manner */
                        PM = set_token_column(file_number, *line, "cpu", 0, SAR_OPTION);
                    SHOW_AVG = 2; /* this means to analyze cpus specifically */
                    CHK_A |=(1 << 0); /* this means, skip this clause on next loop */
                }
            } else if ((!((CHK_A >> 12) & 1)) && strstr(*line,"proc/s") != NULL) {
                CHK_CORES_N = 0;
                CHK_A &= ~(1 << 0);
                CHK_A &= ~(1 << 2);
                CHK_A &= ~(1 << 5);
                CHK_A &= ~(1 << 6);
                SHOW_AVG =1;
                if (SAR_OPTION == 'w' || SAR_OPTION == 'A') {
                    append_list(&line_obj, "");
                    append_list(&line_obj, str_tmp);
                    /* calls set_token_column(), call set_token_items() in appropriate manner */
                    set_token_column(file_number, *line, "proc", 0, SAR_OPTION);
                    SHOW_AVG = 0;
                    CHK_A |=(1 << 12); /* this means, skip this clause on next loop */
                }
            } else if ((!((CHK_A >> 1) & 1)) && strstr(*line,"pgpgin/s") != NULL) {
                CHK_CORES_N = 0;
                CHK_A &= ~(1 << 0);
                CHK_A &= ~(1 << 2);
                CHK_A &= ~(1 << 5);
                CHK_A &= ~(1 << 6);
                SHOW_AVG = 1;
                if (SAR_OPTION == 'B' || SAR_OPTION == 'A') {
                    append_list(&line_obj, "");
                    append_list(&line_obj, str_tmp);
                    if (strstr(*line, "fault") != NULL)
                        /* calls set_token_column(), call set_token_items() in appropriate manner */
                        set_token_column(file_number, *line, "fault", 0, SAR_OPTION);
                    SHOW_AVG = 0;
                    CHK_A |=(1 << 1); /* this means, skip this clause on next loop */
                }
            } else if ((!((CHK_A >> 8) & 1)) && strstr(*line,"kbmemfree") != NULL) {
                CHK_CORES_N = 0;
                CHK_A &= ~(1 << 0);
                CHK_A &= ~(1 << 2);
                CHK_A &= ~(1 << 5);
                CHK_A &= ~(1 << 6);
                SHOW_AVG = 1;
                if (SAR_OPTION == 'r' || SAR_OPTION == 'A') {
                    append_list(&line_obj, "");
                    append_list(&line_obj, str_tmp);
                    /* calls set_token_column(), call set_token_items() in appropriate manner */
                    set_token_column(file_number, *line, "kbmemfree", 0, SAR_OPTION);
                    SHOW_AVG = 0;
                    CHK_A |=(1 << 8); /* this means, skip this clause on next loop */
                }
            } else if ((!((CHK_A >> 3) & 1)) && strstr(*line,"bread/s") != NULL) {
                CHK_CORES_N = 0;
                CHK_A &= ~(1 << 0);
                CHK_A &= ~(1 << 2);
                CHK_A &= ~(1 << 5);
                CHK_A &= ~(1 << 6);
                SHOW_AVG = 1;
                if (SAR_OPTION == 'b' || SAR_OPTION == 'A') {
                    append_list(&line_obj, "");
                    append_list(&line_obj, str_tmp);
                    /* calls set_token_column(), call set_token_items() in appropriate manner */
                    set_token_column(file_number, *line, "bread/s", 0, SAR_OPTION);
                    SHOW_AVG = 0;
                    CHK_A |=(1 << 3); /* this means, skip this clause on next loop */
                }
            } else if ((!((CHK_A >> 4) & 1)) && strstr(*line,"kbhugfree") != NULL) {
                CHK_CORES_N = 0;
                CHK_A &= ~(1 << 0);
                CHK_A &= ~(1 << 2);
                CHK_A &= ~(1 << 5);
                CHK_A &= ~(1 << 6);
                SHOW_AVG = 1;
                if (SAR_OPTION == 'H' || SAR_OPTION == 'A') {
                    append_list(&line_obj, "");
                    append_list(&line_obj, str_tmp);
                    SHOW_AVG = 0;
                    CHK_A |=(1 << 4); /* this means, skip this clause on next loop */
                }
            } else if ((!((CHK_A >> 7) & 1)) && strstr(*line,"runq-sz") != NULL) {
                CHK_CORES_N = 0;
                CHK_A &= ~(1 << 0);
                CHK_A &= ~(1 << 2);
                CHK_A &= ~(1 << 5);
                CHK_A &= ~(1 << 6);
                SHOW_AVG = 1;
                if (SAR_OPTION == 'q' || SAR_OPTION == 'A') {
                    append_list(&line_obj, "");
                    append_list(&line_obj, str_tmp);
                    /* calls set_token_column(), call set_token_items() in appropriate manner */
                    set_token_column(file_number, *line, "runq", 0, SAR_OPTION);
                    SHOW_AVG = 0;
                    CHK_A |=(1 << 7); /* this means, skip this clause on next loop */
                }
            } else if ((!((CHK_A >> 9) & 1)) && strstr(*line,"kbswpfree") != NULL) {
                CHK_CORES_N = 0;
                CHK_A &= ~(1 << 0);
                CHK_A &= ~(1 << 2);
                CHK_A &= ~(1 << 5);
                CHK_A &= ~(1 << 6);
                SHOW_AVG = 1;
                if (SAR_OPTION == 'S' || SAR_OPTION == 'A') {
                    append_list(&line_obj, "");
                    append_list(&line_obj, str_tmp);
                    /* calls set_token_column(), call set_token_items() in appropriate manner */
                    set_token_column(file_number, *line, "kbswpfree", 0, SAR_OPTION);
                    SHOW_AVG = 0;
                    CHK_A |=(1 << 9); /* this means, skip this clause on next loop */
                }
            } else if ((!((CHK_A >> 10) & 1)) && strstr(*line,"dentunusd") != NULL) {
                CHK_CORES_N = 0;
                CHK_A &= ~(1 << 0);
                CHK_A &= ~(1 << 2);
                CHK_A &= ~(1 << 5);
                CHK_A &= ~(1 << 6);
                SHOW_AVG = 1;
                if (SAR_OPTION == 'v' || SAR_OPTION == 'A') {
                    append_list(&line_obj, "");
                    append_list(&line_obj, str_tmp);
                    /* calls set_token_column(), call set_token_items() in appropriate manner */
                    set_token_column(file_number, *line, "dentunusd", 0, SAR_OPTION);
                    SHOW_AVG = 0;
                    CHK_A |=(1 << 10); /* this means, skip this clause on next loop */
                }
            } else if ((!((CHK_A >> 11) & 1)) && strstr(*line,"pswpin/s") != NULL) {
                CHK_CORES_N = 0;
                CHK_A &= ~(1 << 0);
                CHK_A &= ~(1 << 2);
                CHK_A &= ~(1 << 5);
                CHK_A &= ~(1 << 6);
                SHOW_AVG = 1;
                if (SAR_OPTION == 'W' || SAR_OPTION == 'A')
                {
                    append_list(&line_obj, "");
                    append_list(&line_obj, str_tmp);
                    /* calls set_token_column(), call set_token_items() in appropriate manner */
                    set_token_column(file_number, *line, "pswpin/s", 0, SAR_OPTION);
                    SHOW_AVG = 0;
                    CHK_A |=(1 << 11); /* this means, skip this clause on next loop */
                }
            /* for this item, there may be many devices, so Average clause should be special one */
            } else if ((!((CHK_A >> 2) & 1)) && strstr(*line,"DEV") != NULL) {
                CHK_CORES_N = 0;
                CHK_A &= ~(1 << 0);
                CHK_A &= ~(1 << 5);
                CHK_A &= ~(1 << 6);
                SHOW_AVG = 1;
                if (SAR_OPTION == 'd' || SAR_OPTION == 'A')
                {
                    append_list(&line_obj, "");
                    append_list(&line_obj, str_tmp);
                    /* calls set_token_column(), call set_token_items() in appropriate manner */
                    set_token_column(file_number, *line, "DEV", 0, SAR_OPTION);
                    SHOW_AVG = 3;
                    CHK_A |=(1 << 2); /* this means, skip this clause on next loop */
                }
            } else if ((!((CHK_A >> 5) & 1)) && strstr(*line,"rxpck/s") != NULL) {
                CHK_CORES_N = 0;
                CHK_A &= ~(1 << 0);
                CHK_A &= ~(1 << 2);
                CHK_A &= ~(1 << 6);
                SHOW_AVG = 1;
                if (SAR_OPTION == 'n' || SAR_OPTION == 'A')
                {
                    append_list(&line_obj, "");
                    append_list(&line_obj, str_tmp);
                    /* calls set_token_column(), call set_token_items() in appropriate manner */
                    set_token_column(file_number, *line, "rxpck", 0, SAR_OPTION);
                    SHOW_AVG = 4;
                    CHK_A |=(1 << 5); /* this means, skip this clause on next loop */
                }
            } else if ((!((CHK_A >> 6) & 1)) && strstr(*line,"rxerr/s") != NULL) {
                CHK_CORES_N = 0;
                CHK_A &= ~(1 << 0);
                CHK_A &= ~(1 << 2);
                CHK_A &= ~(1 << 5);
                SHOW_AVG = 1;
                if (SAR_OPTION == 'm' || SAR_OPTION == 'A') {
                    append_list(&line_obj, "");
                    append_list(&line_obj, str_tmp);
                    /* calls set_token_column(), call set_token_items() in appropriate manner */
                    set_token_column(file_number, *line, "rxerr", 0, SAR_OPTION);
                    SHOW_AVG = 5;
                    CHK_A |=(1 << 6); /* this means, skip this clause on next loop */
                }
            } else if ((!((CHK_A >> 13) & 1)) && strstr(*line,"rcvin/s") != NULL) {
                CHK_CORES_N = 0;
                CHK_A &= ~(1 << 0);
                CHK_A &= ~(1 << 2);
                CHK_A &= ~(1 << 5);
                CHK_A &= ~(1 << 6);
                SHOW_AVG = 1;
                if (SAR_OPTION == 'y' || SAR_OPTION == 'A') {
                    append_list(&line_obj, "");
                    append_list(&line_obj, str_tmp);
                    SHOW_AVG = 0;
                    CHK_A |=(1 << 13); /* this means, skip this clause on next loop */
                }
            } else if ((!((CHK_A >> 14) & 1)) && strstr(*line,"frmpg/s") != NULL) {
                CHK_CORES_N = 0;
                CHK_A &= ~(1 << 0);
                CHK_A &= ~(1 << 2);
                CHK_A &= ~(1 << 5);
                CHK_A &= ~(1 << 6);
                SHOW_AVG = 1;
                if (SAR_OPTION == 'x' || SAR_OPTION == 'A') {
                    append_list(&line_obj, "");
                    append_list(&line_obj, str_tmp);
                    SHOW_AVG=0;
                    CHK_A |=(1 << 14); /* this means, skip this clause on next loop */
                }
            } else if ((!((CHK_A >> 15) & 1)) && strstr(*line,"call/s") != NULL) {
                CHK_CORES_N = 0;
                CHK_A &= ~(1 << 0);
                CHK_A &= ~(1 << 2);
                CHK_A &= ~(1 << 5);
                CHK_A &= ~(1 << 6);
                SHOW_AVG = 1;
                if (SAR_OPTION == 'x' || SAR_OPTION == 'A') {
                    append_list(&line_obj, "");
                    append_list(&line_obj, str_tmp);
                    SHOW_AVG = 0;
                    CHK_A |=(1 << 15); /* this means, skip this clause on next loop */
                }
            } else if ((!((CHK_A >> 16) & 1)) && strstr(*line,"scall/s") != NULL) {
                CHK_CORES_N = 0;
                CHK_A &= ~(1 << 0);
                CHK_A &= ~(1 << 2);
                CHK_A &= ~(1 << 5);
                CHK_A &= ~(1 << 6);
                SHOW_AVG = 1;
                if (SAR_OPTION == 'x' || SAR_OPTION == 'A')
                {
                    append_list(&line_obj, "");
                    append_list(&line_obj, str_tmp);
                    SHOW_AVG = 0;
                    CHK_A |=(1 << 16); /* this means, skip this clause on next loop */
                }
            } else if ((!((CHK_A >> 17) & 1)) && strstr(*line,"totsck") != NULL) {
                CHK_CORES_N = 0;
                CHK_A &= ~(1 << 0);
                CHK_A &= ~(1 << 2);
                CHK_A &= ~(1 << 5);
                CHK_A &= ~(1 << 6);
                SHOW_AVG = 1;
                if (SAR_OPTION == 'x' || SAR_OPTION == 'A') {
                    append_list(&line_obj, "");
                    append_list(&line_obj, str_tmp);
                    SHOW_AVG = 0;
                    CHK_A |=(1 << 17); /* this means, skip this clause on next loop */
                }
            } else if ((!((CHK_A >> 18) & 1)) && strstr(*line,"total/s") != NULL) {
                CHK_CORES_N = 0;
                CHK_A &= ~(1 << 0);
                CHK_A &= ~(1 << 2);
                CHK_A &= ~(1 << 5);
                CHK_A &= ~(1 << 6);
                SHOW_AVG=1;
                if (SAR_OPTION == 'x' || SAR_OPTION == 'A') {
                    append_list(&line_obj, "");
                    append_list(&line_obj, str_tmp);
                    SHOW_AVG = 0;
                    CHK_A |=(1 << 18); /* this means, skip this clause on next loop */
                }
            }
            /* for cpus setting values to arrays
             * during the while loop, if CHK_CORES_N is under MAX_CORE_NUMBERS, this clause will be called and sets item values for each
             * cpu and sets core number every time. core number is incremented, so, lately, core number could be known (including all line)  
             * stop calling this clause if reached up to MAX_CORE_NUMBERS, anyway, it will no be called very soon   
             */
            if (strstr(*line, "Average") && !strstr(*line, "CPU") && (SHOW_AVG == 2) && (CHK_CORES_N <= MAX_CORE_NUMBERS)) {
                append_list(&line_obj, str_tmp);
                set_token_items(file_number, line, "cpu" , CHK_CORES_N, SAR_OPTION, time_span, PM); /* setting each cpu values to the object */
                if (CHK_CORES_N == MAX_CORE_NUMBERS)
                    SHOW_AVG = 0;
                set_core_numbers(CHK_CORES_N);
                CHK_CORES_N++;
            /* for devices (DEV) setting values to arrays
             * just because not knowing which block device will appear every time this clause is called,
             * setting each name to the object for future use 
             */ 
            } else if (strstr(*line, "Average")  && !strstr(*line, "DEV") && (SHOW_AVG == 3)) {
                if ((strstr(*line, "dev") != 0) || (strstr(*line, "sd") != 0) || (strstr(*line, "sr") != 0) ||
                    (strstr(*line, "ram") != 0) || (strstr(*line, "dm") != 0)) {
                    append_list(&line_obj, str_tmp);
                    set_token_items(file_number, line, "DEV" , -999, SAR_OPTION, time_span, PM);
                }
            /* for devices (NET rxpck/s) setting values to arrays
             * just because not knowing which network device will appear every time this clause is called,
             * setting each name to the object for future use 
             */ 
            } else if (strstr(*line, "Average")  && !strstr(*line, "rxpck") && (SHOW_AVG == 4)) {
                append_list(&line_obj, str_tmp);
                set_token_items(file_number, line, "rxpck" , -999, SAR_OPTION, time_span, PM);
            } else if (strstr(*line, "Average")  && !strstr(*line, "rxerr") && (SHOW_AVG == 5)) {
                append_list(&line_obj, str_tmp);
                set_token_items(file_number, line, "rxerr" , -999, SAR_OPTION, time_span, PM);

            /* Call set_token_items() here
             * this clause is for others which only have one line to be analyzed 
             */
            } else if (strstr(*line, "Average")  && ((SHOW_AVG == 0)) && (strstr(*line, "CPU") == NULL)) {
                append_list(&line_obj, str_tmp);
                /* setting utility arguments to meaningless value line -999 */
                if (((CHK_A >> 1) & 1)) {
                    set_token_items(file_number, line, "fault", -999, SAR_OPTION, time_span, PM);
                    CHK_A &= ~(1 << 1);
                }
                if (((CHK_A >> 3) & 1)) {
                    set_token_items(file_number, line, "bread/s", -999, SAR_OPTION, time_span, PM);
                    CHK_A &= ~(1 << 3);
                }
                if (((CHK_A >> 7) & 1)) {
                    set_token_items(file_number, line, "runq", -999, SAR_OPTION, time_span, PM);
                    CHK_A &= ~(1 << 7);
                }
                if (((CHK_A >> 8) & 1)) {
                    set_token_items(file_number, line, "kbmemfree", -999, SAR_OPTION, time_span, PM);
                    CHK_A &= ~(1 << 8);
                }
                if (((CHK_A >> 9) & 1)) {
                    set_token_items(file_number, line, "kbswpfree", -999, SAR_OPTION, time_span, PM);
                    CHK_A &= ~(1 << 9);
                }
                if (((CHK_A >> 10) & 1)) {
                    set_token_items(file_number, line, "dentunusd", -999, SAR_OPTION, time_span, PM);
                    CHK_A &= ~(1 << 10);
                }
                if (((CHK_A >> 11) & 1)) {
                    set_token_items(file_number, line, "pswpin/s", -999, SAR_OPTION, time_span, PM);
                    CHK_A &= ~(1 << 11);
                }
                if (((CHK_A >> 12) & 1)) {
                    set_token_items(file_number, line, "proc", -999, SAR_OPTION, time_span, PM);
                    CHK_A &= ~(1 << 12);
                }
            }
        }
    }
    return 0;
}
