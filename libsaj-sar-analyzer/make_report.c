/*
 *  make_report.c - report functions 
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

#include <dirent.h>
#include <string.h>
#include "../common/global.h"
#include "../libsaj-sosreport-analyzer/line_data.h"
#include "make_report.h"
#include "setter_getter.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int make_report(int SAR_OPTION, int REPORT, int files_n, const char *time_span)
{
    if (REPORT != 0)
        return 0;

    /* report the result */
    if (SAR_OPTION == 'Z') {
        char str_tmp[MAX_LINE_LENGTH - 1000];
        char s[4];

        /* filling up with '\0' */
        memset(str_tmp, '\0', MAX_LINE_LENGTH - 1000);
        memset(s, '\0', 4);

        snprintf(str_tmp, MAX_LINE_LENGTH, "\n#### Report by sar-analyzer enforced by saj %d.%d.%d ####",
            PROGRAM_VERSION, PROGRAM_RELEASE, PROGRAM_SUB_RELEASE);
        append_list(&header_obj, str_tmp);

        int i = 0, ii = -1, j = 1;

        /**** cpu ****/

        append_list(&report_cpu_obj, "\n-- Report of CPU utilization --");
        for (i = 0, ii = -1; i <= MAX_CORE_NUMBERS; i++, ii++) {
            if (i > get_core_numbers())
                break;
            if (ii == -1)
                snprintf(s, 4, "%s", "all"); 
            else
                snprintf(s, 4, "%d", ii); 
            append_list(&report_cpu_obj, "");
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest value of '%%usr(%%user)'   for CPU %s is %8.2f (%s %s)",
                s, get_cpu_highest_val(i, "usr"), get_cpu_highest_date(i, "usr"), get_cpu_highest_time(i, "usr"));
            append_list(&report_cpu_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  value of '%%usr(%%user)'   for CPU %s is %8.2f (%s %s)",
                s, get_cpu_lowest_val(i, "usr"), get_cpu_lowest_date(i, "usr"), get_cpu_lowest_time(i, "usr"));
            append_list(&report_cpu_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Spike   value of '%%usr(%%user)'   for CPU %s is %8.2f (%s %s)",
                s, get_cpu_spike_val(i, "usr"), get_cpu_spike_date(i, "usr"), get_cpu_spike_time(i, "usr"));
            append_list(&report_cpu_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest value of '%%sys(%%system)' for CPU %s is %8.2f (%s %s)",
                s, get_cpu_highest_val(i, "sys"), get_cpu_highest_date(i, "sys"), get_cpu_highest_time(i, "sys"));
            append_list(&report_cpu_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  value of '%%sys(%%system)' for CPU %s is %8.2f (%s %s)",
                s, get_cpu_lowest_val(i, "sys"), get_cpu_lowest_date(i, "sys"), get_cpu_lowest_time(i, "sys"));
            append_list(&report_cpu_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Spike   value of '%%sys(%%system)' for CPU %s is %8.2f (%s %s)",
                s, get_cpu_spike_val(i, "sys"), get_cpu_spike_date(i, "sys"), get_cpu_spike_time(i, "sys"));
            append_list(&report_cpu_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest value of '%%iowait'       for CPU %s is %8.2f (%s %s)",
                s, get_cpu_highest_val(i, "iowait"), get_cpu_highest_date(i, "iowait"), get_cpu_highest_time(i, "iowait"));
            append_list(&report_cpu_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  value of '%%iowait'       for CPU %s is %8.2f (%s %s)",
                s, get_cpu_lowest_val(i, "iowait"), get_cpu_lowest_date(i, "iowait"), get_cpu_lowest_time(i, "iowait"));
            append_list(&report_cpu_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Spike   value of '%%iowait'       for CPU %s is %8.2f (%s %s)",
                s, get_cpu_spike_val(i, "iowait"), get_cpu_spike_date(i, "iowait"), get_cpu_spike_time(i, "iowait"));
            append_list(&report_cpu_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest value of '%%idle'         for CPU %s is %8.2f (%s %s)",
                s, get_cpu_highest_val(i, "idle"), get_cpu_highest_date(i, "idle"), get_cpu_highest_time(i, "idle"));
            append_list(&report_cpu_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  value of '%%idle'         for CPU %s is %8.2f (%s %s)",
                s, get_cpu_lowest_val(i, "idle"), get_cpu_lowest_date(i, "idle"), get_cpu_lowest_time(i, "idle"));
            append_list(&report_cpu_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Spike   value of '%%idle'         for CPU %s is %8.2f (%s %s)",
                s, get_cpu_spike_val(i, "idle"), get_cpu_spike_date(i, "idle"), get_cpu_spike_time(i, "idle"));
            append_list(&report_cpu_obj, str_tmp);
            /* averages */
            append_list(&report_cpu_obj, "");
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest Average value of '%%usr(%%user)'   for CPU %s is %8.2f (%s)",
                s, get_cpu_avg_highest_val(i, "usr") , get_cpu_avg_highest_date(i, "usr"));
            append_list(&report_cpu_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  Average value of '%%usr(%%user)'   for CPU %s is %8.2f (%s)",
                s, get_cpu_avg_lowest_val(i, "usr"), get_cpu_avg_lowest_date(i, "usr"));
            append_list(&report_cpu_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest Average value of '%%sys(%%system)' for CPU %s is %8.2f (%s)",
                s, get_cpu_avg_highest_val(i, "sys"), get_cpu_avg_highest_date(i, "sys"));
            append_list(&report_cpu_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  Average value of '%%sys(%%system)' for CPU %s is %8.2f (%s)",
                s, get_cpu_avg_lowest_val(i, "sys"), get_cpu_avg_lowest_date(i, "sys"));
            append_list(&report_cpu_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest Average value of '%%iowait'       for CPU %s is %8.2f (%s)",
                s, get_cpu_avg_highest_val(i, "iowait"), get_cpu_avg_highest_date(i, "iowait"));
            append_list(&report_cpu_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  Average value of '%%iowait'       for CPU %s is %8.2f (%s)",
                s, get_cpu_avg_lowest_val(i,"iowait"), get_cpu_avg_lowest_date(i, "iowait"));
            append_list(&report_cpu_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest Average value of '%%idle'         for CPU %s is %8.2f (%s)",
                s, get_cpu_avg_highest_val(i, "idle"), get_cpu_avg_highest_date(i, "idle"));
            append_list(&report_cpu_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  Average value of '%%idle'         for CPU %s is %8.2f (%s)",
                s, get_cpu_avg_lowest_val(i, "idle"), get_cpu_avg_lowest_date(i, "idle"));
            append_list(&report_cpu_obj, str_tmp);
            /* end averages */
        }
        memset(str_tmp, '\0', MAX_LINE_LENGTH - 1000);
        memset(s, '\0', 4);
        /* spikes for each file */
        append_list ( &report_cpu_obj, "\n-- Report spikes for each file of CPU utilization --");
        for (i = 0, ii = -1; i <= MAX_CORE_NUMBERS; i++, ii++) {
            if (i > get_core_numbers())
                break;
            if (ii == -1)
                snprintf(s, 4, "%s", "all"); 
            else
                snprintf(s, 4, "%d", ii); 

            for (j = 0; j < files_n; j++) {
                append_list(&report_cpu_spike_obj[i], "");
                /* set for declaring file no in case -O option is set*/
                char str_cpu[7];
                memset(str_cpu, '\0', 7);
                char str_cpu_tmp [12];
                memset(str_cpu_tmp, '\0', 12);
                char str_num [34];
                memset(str_num, '\0', 34);
                char str_fileno[11];
                memset(str_fileno, '\0', 11);
                strncpy(str_cpu, "--CPU ", 7);
                strncpy(str_cpu_tmp, "-- file no.", 12);
                snprintf(str_fileno, 11, "%d", j + 1); 
                snprintf(str_num, 34, "%s%s%s%s", str_cpu, s, str_cpu_tmp, str_fileno);
                append_list(&report_cpu_spike_obj[i], str_num);
                /* end -- set for declaring file no in case -O option is set */
                snprintf(str_tmp, MAX_LINE_LENGTH, "  Spike   value of '%%usr(%%user)'   for CPU %s is %8.2f (%s %s)",
                    s, get_cpu_spike_val_each_file(j, i, "usr", "spike"),
                        get_cpu_spike_date_each_file(j, i, "usr", "spike"),
                            get_cpu_spike_time_each_file(j, i, "usr", "spike"));
                append_list(&report_cpu_spike_obj[i], str_tmp);
                snprintf (str_tmp, MAX_LINE_LENGTH, "  Spike   value of '%%sys(%%system)' for CPU %s is %8.2f (%s %s)",
                    s, get_cpu_spike_val_each_file(j, i, "sys", "spike"),
                        get_cpu_spike_date_each_file(j, i, "sys", "spike"),
                            get_cpu_spike_time_each_file(j, i, "sys", "spike"));
                append_list(&report_cpu_spike_obj[i], str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, "  Spike   value of '%%iowait'       for CPU %s is %8.2f (%s %s)",
                    s, get_cpu_spike_val_each_file(j, i, "iowait", "spike"),
                        get_cpu_spike_date_each_file(j, i, "iowait", "spike"),
                            get_cpu_spike_time_each_file(j, i, "iowait", "spike"));
                append_list(&report_cpu_spike_obj[i], str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, "  Spike   value of '%%idle'         for CPU %s is %8.2f (%s %s)",
                    s, get_cpu_spike_val_each_file(j, i, "idle", "spike"),
                        get_cpu_spike_date_each_file(j, i, "idle", "spike"),
                            get_cpu_spike_time_each_file(j, i, "idle", "spike"));
                append_list(&report_cpu_spike_obj[i], str_tmp);
                append_list(&report_cpu_spike_obj[i], "");

                snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest value of '%%usr(%%user)'   for CPU %s is %8.2f (%s %s)",
                    s, get_cpu_spike_val_each_file(j, i, "usr", "highest"),
                        get_cpu_spike_date_each_file(j, i, "usr", "highest"),
                            get_cpu_spike_time_each_file(j, i, "usr", "highest"));
                append_list(&report_cpu_spike_obj[i], str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest value of '%%sys(%%system)' for CPU %s is %8.2f (%s %s)",
                    s, get_cpu_spike_val_each_file(j, i, "sys", "highest"),
                        get_cpu_spike_date_each_file(j, i, "sys", "highest"),
                            get_cpu_spike_time_each_file(j, i, "sys", "highest"));
                append_list(&report_cpu_spike_obj[i], str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest value of '%%iowait'       for CPU %s is %8.2f (%s %s)",
                    s, get_cpu_spike_val_each_file(j, i, "iowait", "highest"),
                        get_cpu_spike_date_each_file(j, i, "iowait", "highest"),
                            get_cpu_spike_time_each_file(j, i, "iowait", "highest"));
                append_list(&report_cpu_spike_obj[i], str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest value of '%%idle'         for CPU %s is %8.2f (%s %s)",
                    s, get_cpu_spike_val_each_file(j, i, "idle", "highest"),
                        get_cpu_spike_date_each_file(j, i, "idle", "highest"),
                            get_cpu_spike_time_each_file(j, i, "idle", "highest"));
                append_list(&report_cpu_spike_obj[i], str_tmp);

                append_list(&report_cpu_spike_obj[i], "");

                snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  value of '%%usr(%%user)'   for CPU %s is %8.2f (%s %s)",
                    s, get_cpu_spike_val_each_file(j, i, "usr", "lowest"),
                        get_cpu_spike_date_each_file(j, i, "usr", "lowest"),
                            get_cpu_spike_time_each_file(j, i, "usr", "lowest"));
                append_list(&report_cpu_spike_obj[i], str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  value of '%%sys(%%system)' for CPU %s is %8.2f (%s %s)",
                    s, get_cpu_spike_val_each_file(j, i, "sys", "lowest"),
                        get_cpu_spike_date_each_file(j, i, "sys", "lowest"),
                            get_cpu_spike_time_each_file(j, i, "sys", "lowest"));
                append_list(&report_cpu_spike_obj[i], str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  value of '%%iowait'       for CPU %s is %8.2f (%s %s)",
                    s, get_cpu_spike_val_each_file(j, i, "iowait", "lowest"),
                        get_cpu_spike_date_each_file(j, i, "iowait", "lowest"),
                            get_cpu_spike_time_each_file(j, i, "iowait", "lowest"));
                append_list(&report_cpu_spike_obj[i], str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  value of '%%idle'         for CPU %s is %8.2f (%s %s)",
                    s, get_cpu_spike_val_each_file(j, i, "idle", "lowest"),
                        get_cpu_spike_date_each_file(j, i, "idle", "lowest"),
                            get_cpu_spike_time_each_file(j, i, "idle", "lowest"));
                append_list(&report_cpu_spike_obj[i], str_tmp);

                /* for time-span option */
                if (time_span != NULL) {
                    append_list(&report_cpu_time_span_spike_obj[i], "");
                    append_list(&report_cpu_time_span_spike_obj[i], str_num);
                    snprintf(str_tmp, MAX_LINE_LENGTH, "  %s Spike   value of '%%usr(%%user)'   for CPU %s is %8.2f (%s %s)", time_span,
                        s, get_cpu_time_span_spike_val_each_file(j, i, "usr", "spike"),
                            get_cpu_time_span_spike_date_each_file(j, i, "usr", "spike"),
                                get_cpu_time_span_spike_time_each_file ( j, i, "usr", "spike"));
                    append_list(&report_cpu_time_span_spike_obj[i], str_tmp);
                    snprintf(str_tmp, MAX_LINE_LENGTH, "  %s Spike   value of '%%sys(%%system)' for CPU %s is %8.2f (%s %s)", time_span,
                        s, get_cpu_time_span_spike_val_each_file(j, i, "sys", "spike"),
                            get_cpu_time_span_spike_date_each_file(j, i, "sys", "spike"),
                                get_cpu_time_span_spike_time_each_file(j, i, "sys", "spike"));
                    append_list(&report_cpu_time_span_spike_obj[i], str_tmp);
                    snprintf(str_tmp, MAX_LINE_LENGTH, "  %s Spike   value of '%%iowait'       for CPU %s is %8.2f (%s %s)", time_span,
                        s, get_cpu_time_span_spike_val_each_file(j, i, "iowait", "spike"),
                            get_cpu_time_span_spike_date_each_file(j, i, "iowait", "spike"),
                                get_cpu_time_span_spike_time_each_file(j, i, "iowait", "spike"));
                    append_list(&report_cpu_time_span_spike_obj[i], str_tmp);
                    snprintf(str_tmp, MAX_LINE_LENGTH, "  %s Spike   value of '%%idle'         for CPU %s is %8.2f (%s %s)", time_span,
                        s, get_cpu_time_span_spike_val_each_file(j, i, "idle", "spike"),
                            get_cpu_time_span_spike_date_each_file(j, i, "idle", "spike" ),
                                get_cpu_time_span_spike_time_each_file(j, i, "idle", "spike"));
                    append_list(&report_cpu_time_span_spike_obj[i], str_tmp);
                    append_list(&report_cpu_time_span_spike_obj[i], "");

                    snprintf(str_tmp, MAX_LINE_LENGTH, "  %s Highest value of '%%usr(%%user)'   for CPU %s is %8.2f (%s %s)", time_span,
                        s, get_cpu_time_span_spike_val_each_file(j, i, "usr", "highest"),
                            get_cpu_time_span_spike_date_each_file(j, i, "usr", "highest"),
                                get_cpu_time_span_spike_time_each_file(j, i, "usr", "highest"));
                    append_list(&report_cpu_time_span_spike_obj[i], str_tmp);
                    snprintf(str_tmp, MAX_LINE_LENGTH, "  %s Highest value of '%%sys(%%system)' for CPU %s is %8.2f (%s %s)", time_span,
                        s, get_cpu_time_span_spike_val_each_file(j, i, "sys", "highest"),
                            get_cpu_time_span_spike_date_each_file(j, i, "sys", "highest"),
                                get_cpu_time_span_spike_time_each_file(j, i, "sys", "highest"));
                    append_list(&report_cpu_time_span_spike_obj[i], str_tmp);
                    snprintf(str_tmp, MAX_LINE_LENGTH, "  %s Highest value of '%%iowait'       for CPU %s is %8.2f (%s %s)", time_span,
                        s, get_cpu_time_span_spike_val_each_file(j, i, "iowait", "highest"),
                            get_cpu_time_span_spike_date_each_file(j, i, "iowait", "highest"),
                                get_cpu_time_span_spike_time_each_file(j, i, "iowait", "highest"));
                    append_list(&report_cpu_time_span_spike_obj[i], str_tmp);
                    snprintf(str_tmp, MAX_LINE_LENGTH, "  %s Highest value of '%%idle'         for CPU %s is %8.2f (%s %s)", time_span,
                        s, get_cpu_time_span_spike_val_each_file(j, i, "idle", "highest"),
                            get_cpu_time_span_spike_date_each_file(j, i, "idle", "highest"),
                                get_cpu_time_span_spike_time_each_file(j, i, "idle", "highest"));
                    append_list(&report_cpu_time_span_spike_obj[i], str_tmp);

                    append_list(&report_cpu_time_span_spike_obj[i], "");

                    snprintf(str_tmp, MAX_LINE_LENGTH, "  %s Lowest  value of '%%usr(%%user)'   for CPU %s is %8.2f (%s %s)", time_span,
                        s, get_cpu_time_span_spike_val_each_file(j, i, "usr", "lowest"),
                            get_cpu_time_span_spike_date_each_file(j, i, "usr", "lowest"),
                                get_cpu_time_span_spike_time_each_file(j, i, "usr", "lowest"));
                    append_list(&report_cpu_time_span_spike_obj[i], str_tmp);
                    snprintf(str_tmp, MAX_LINE_LENGTH, "  %s Lowest  value of '%%sys(%%system)' for CPU %s is %8.2f (%s %s)", time_span,
                        s, get_cpu_time_span_spike_val_each_file(j, i, "sys", "lowest"),
                            get_cpu_time_span_spike_date_each_file(j, i, "sys", "lowest"),
                                get_cpu_time_span_spike_time_each_file(j, i, "sys", "lowest"));
                    append_list(&report_cpu_time_span_spike_obj[i], str_tmp);
                    snprintf(str_tmp, MAX_LINE_LENGTH, "  %s Lowest  value of '%%iowait'       for CPU %s is %8.2f (%s %s)", time_span,
                        s, get_cpu_time_span_spike_val_each_file(j, i, "iowait", "lowest"),
                            get_cpu_time_span_spike_date_each_file(j, i, "iowait", "lowest" ),
                                get_cpu_time_span_spike_time_each_file(j, i, "iowait", "lowest"));
                    append_list(&report_cpu_time_span_spike_obj[i], str_tmp);
                    snprintf(str_tmp, MAX_LINE_LENGTH, "  %s Lowest  value of '%%idle'         for CPU %s is %8.2f (%s %s)", time_span,
                        s, get_cpu_time_span_spike_val_each_file(j, i, "idle", "lowest"),
                            get_cpu_time_span_spike_date_each_file(j, i, "idle", "lowest"),
                                get_cpu_time_span_spike_time_each_file(j, i, "idle", "lowest"));
                    append_list(&report_cpu_time_span_spike_obj[i], str_tmp);
                }
            }
        }

        append_list(&report_cpu_explanation_obj, "--------");
        append_list(&report_cpu_explanation_obj, "  Each CPU can be in one of four states: user, sys, idle, iowait." );
        append_list(&report_cpu_explanation_obj, "  If '%usr' is over 60%, applications are in a busy state. Check with ps command which application is busy.");
        append_list(&report_cpu_explanation_obj, "  If '%sys' is over '%usr', kernel is in a busy state. Check cswch is high or not." );
        append_list(&report_cpu_explanation_obj, "  If '%iowait' is high, cpu is working for other task more. Note that iowait sometimes meaningless, at all.");
        append_list(&report_cpu_explanation_obj, "  Check swap statistics or high disk I/O would be the cause. Also check process or memory statistics.");
        append_list(&report_cpu_explanation_obj, "  Check paging activity of 'pgpgin/s' in that very time. If both '%iowait' and 'pgpgin/s' is high,");
        append_list(&report_cpu_explanation_obj, "  thrashing is occurring at that time. Check carefully...");
        append_list(&report_cpu_explanation_obj, "  If %idle is lower than 30%, you would need new CPU or cores.");
        append_list(&report_cpu_explanation_obj, "  Check not only 'CPU all', but each CPU values. And if some of their values are high, check the sar file of that date.");
        append_list(&report_cpu_explanation_obj, "  In such a case, certain program may woking with only one core.");

        /* tasks */

        append_list(&report_tasks_obj, " \n-- Report task creation and system switching activity --\n");
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest value of 'proc/s'  is %13.2f (%s %s)",
            get_tasks_highest_val("proc"), get_tasks_highest_date("proc"), get_tasks_highest_time("proc"));
        append_list(&report_tasks_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  value of 'proc/s'  is %13.2f (%s %s)",
            get_tasks_lowest_val("proc"), get_tasks_lowest_date("proc"), get_tasks_lowest_time("proc"));
        append_list(&report_tasks_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Spike   value of 'proc/s'  is %13.2f (%s %s)",
            get_tasks_spike_val("proc"), get_tasks_spike_date("proc"), get_tasks_spike_time("proc"));
        append_list(&report_tasks_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest value of 'cswch/s' is %13.2f (%s %s)",
            get_tasks_highest_val("cswch"), get_tasks_highest_date("cswch"), get_tasks_highest_time("cswch"));
        append_list(&report_tasks_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  value of 'cswch/s' is %13.2f (%s %s)",
            get_tasks_lowest_val("cswch"), get_tasks_lowest_date("cswch"), get_tasks_lowest_time("cswch"));
        append_list(&report_tasks_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Spike   value of 'cswch/s' is %13.2f (%s %s)",
            get_tasks_spike_val("cswch"), get_tasks_spike_date("cswch"), get_tasks_spike_time("cswch"));
        append_list(&report_tasks_obj, str_tmp);
        /* averages */
        append_list(&report_tasks_obj, "");
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest Average value of 'proc/s'  is %13.2f (%s)",
            get_tasks_avg_highest_val("proc"), get_tasks_avg_highest_date("proc"));
        append_list(&report_tasks_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  Average value of 'proc/s'  is %13.2f (%s)",
            get_tasks_avg_lowest_val("proc"), get_tasks_avg_lowest_date("proc"));
        append_list(&report_tasks_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest Average value of 'cswch/s' is %13.2f (%s)",
            get_tasks_avg_highest_val("cswch"), get_tasks_avg_highest_date("proc"));
        append_list(&report_tasks_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  Average value of 'cswch/s' is %13.2f (%s)",
            get_tasks_avg_lowest_val("cswch"), get_tasks_avg_lowest_date("proc"));
        append_list(&report_tasks_obj, str_tmp);
        /* end averages */

        append_list (&report_tasks_obj, "\n-- Report spikes for each file of task creation and system switching activity --\n");
        for (j = 0; j < files_n; j++) {
            /* set for declaring file no in case -O option is set */
            char str_tasks_tmp[13] = "----file no.";
            char str_num[50] = {'\0'};
            snprintf(str_num, MAX_INPUT, "%s%d", str_tasks_tmp, j + 1);
            append_list(&report_tasks_spike_obj, str_num);
            /* end -- set for declaring file no in case -O option is set */

            snprintf(str_tmp, MAX_LINE_LENGTH, "  Spike   value of 'proc/s'  is %13.2f (%s %s)",
                get_tasks_spike_val_each_file(j, "proc", "spike"),
                    get_tasks_spike_date_each_file(j, "proc", "spike"),
                        get_tasks_spike_time_each_file(j, "proc", "spike"));
            append_list(&report_tasks_spike_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Spike   value of 'cswch/s' is %13.2f (%s %s)",
                get_tasks_spike_val_each_file(j, "cswch", "spike"),
                    get_tasks_spike_date_each_file(j, "cswch", "spike"),
                        get_tasks_spike_time_each_file(j, "cswch", "spike"));
            append_list(&report_tasks_spike_obj, str_tmp);
            append_list(&report_tasks_spike_obj, "");

            snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest value of 'proc/s'  is %13.2f (%s %s)",
                get_tasks_spike_val_each_file(j, "proc", "highest"),
                    get_tasks_spike_date_each_file(j, "proc", "highest"),
                        get_tasks_spike_time_each_file(j, "proc", "highest"));
            append_list(&report_tasks_spike_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest value of 'cswch/s' is %13.2f (%s %s)",
                get_tasks_spike_val_each_file(j, "cswch", "highest"),
                    get_tasks_spike_date_each_file(j, "cswch", "highest"),
                        get_tasks_spike_time_each_file(j, "cswch", "highest"));
            append_list(&report_tasks_spike_obj, str_tmp);

            append_list(&report_tasks_spike_obj, "");

            snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  value of 'proc/s'  is %13.2f (%s %s)",
                get_tasks_spike_val_each_file(j, "proc", "lowest"),
                    get_tasks_spike_date_each_file(j, "proc", "lowest"),
                        get_tasks_spike_time_each_file(j, "proc", "lowest"));
            append_list(&report_tasks_spike_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  value of 'cswch/s' is %13.2f (%s %s)",
                get_tasks_spike_val_each_file(j, "cswch", "lowest"),
                    get_tasks_spike_date_each_file(j, "cswch", "lowest"),
                        get_tasks_spike_time_each_file(j, "cswch", "lowest"));
            append_list(&report_tasks_spike_obj, str_tmp);
            /* for time-span option */
            if (time_span != NULL) {
                append_list(&report_tasks_time_span_spike_obj, "");
                append_list(&report_tasks_time_span_spike_obj, str_num);
                snprintf(str_tmp, MAX_LINE_LENGTH, "  %s Spike   value of 'proc/s'  is %13.2f (%s %s)", time_span,
                    get_tasks_time_span_spike_val_each_file(j, "proc", "spike"),
                        get_tasks_time_span_spike_date_each_file(j, "proc", "spike"),
                            get_tasks_time_span_spike_time_each_file(j, "proc", "spike"));
                append_list(&report_tasks_time_span_spike_obj, str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, "  %s Spike   value of 'cswch/s' is %13.2f (%s %s)", time_span,
                    get_tasks_time_span_spike_val_each_file(j, "cswch", "spike"),
                        get_tasks_time_span_spike_date_each_file(j, "cswch", "spike"),
                            get_tasks_time_span_spike_time_each_file ( j, "cswch", "spike"));
                append_list(&report_tasks_time_span_spike_obj, str_tmp);
                append_list(&report_tasks_time_span_spike_obj, "" );

                snprintf(str_tmp, MAX_LINE_LENGTH, "  %s Highest value of 'proc/s'  is %13.2f (%s %s)", time_span,
                    get_tasks_time_span_spike_val_each_file(j, "proc", "highest"),
                        get_tasks_time_span_spike_date_each_file(j, "proc", "highest"),
                            get_tasks_time_span_spike_time_each_file ( j, "proc", "highest"));
                append_list(&report_tasks_time_span_spike_obj, str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, "  %s Highest value of 'cswch/s' is %13.2f (%s %s)", time_span,
                    get_tasks_time_span_spike_val_each_file(j, "cswch", "highest"),
                        get_tasks_time_span_spike_date_each_file(j, "cswch", "highest"),
                            get_tasks_time_span_spike_time_each_file ( j, "cswch", "highest"));
                append_list(&report_tasks_time_span_spike_obj, str_tmp);

                append_list(&report_tasks_time_span_spike_obj, "");

                snprintf(str_tmp, MAX_LINE_LENGTH, "  %s Lowest  value of 'proc/s'  is %13.2f (%s %s)", time_span,
                    get_tasks_time_span_spike_val_each_file(j, "proc", "lowest"),
                        get_tasks_time_span_spike_date_each_file(j, "proc", "lowest"),
                            get_tasks_time_span_spike_time_each_file(j, "proc", "lowest"));
                append_list(&report_tasks_time_span_spike_obj, str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, "  %s Lowest  value of 'cswch/s' is %13.2f (%s %s)", time_span,
                    get_tasks_time_span_spike_val_each_file(j, "cswch", "lowest"),
                        get_tasks_time_span_spike_date_each_file(j, "cswch", "lowest"),
                            get_tasks_time_span_spike_time_each_file(j, "cswch", "lowest"));
                append_list(&report_tasks_time_span_spike_obj, str_tmp);
            }
        }

        append_list(&report_tasks_explanation_obj, "--------");
        append_list(&report_tasks_explanation_obj, " proc/s shows number of tasks which was created per second.");
        append_list(&report_tasks_explanation_obj, " Check the order. Depends on cores, but under 100 would be fine.");
        append_list(&report_tasks_explanation_obj, " cswch/s shows number of context switching activity of CPU per second.");
        append_list(&report_tasks_explanation_obj, " Check the order. Depends on cores, but maybe over 10000 would be some trouble.");

        /* pswap */

        append_list(&report_pswap_obj, " \n-- Report swapping statistics--\n");
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest value of 'pswpin/s'   is %13.2f (%s %s)",
            get_pswap_highest_val("pswpin"), get_pswap_highest_date("pswpin"), get_pswap_highest_time("pswpin"));
        append_list(&report_pswap_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  value of 'pswpin/s'   is %13.2f (%s %s)",
            get_pswap_lowest_val("pswpin"), get_pswap_lowest_date("pswpin"), get_pswap_lowest_time("pswpin"));
        append_list(&report_pswap_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Spike   value of 'pswpin/s'   is %13.2f (%s %s)",
            get_pswap_spike_val("pswpin"), get_pswap_spike_date("pswpin"), get_pswap_spike_time("pswpin"));
        append_list(&report_pswap_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest value of 'pswpout/s'  is %13.2f (%s %s)",
            get_pswap_highest_val("pswpout"), get_pswap_highest_date("pswpout"), get_pswap_highest_time("pswpout"));
        append_list(&report_pswap_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  value of 'pswpout/s'  is %13.2f (%s %s)",
            get_pswap_lowest_val("pswpout"), get_pswap_lowest_date("pswpout"), get_pswap_lowest_time("pswpout"));
        append_list(&report_pswap_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Spike   value of 'pswpout/s'  is %13.2f (%s %s)",
            get_pswap_spike_val("pswpout"), get_pswap_spike_date("pswpout"), get_pswap_spike_time("pswpout"));
        append_list(&report_pswap_obj, str_tmp);
        /* averages */
        append_list(&report_pswap_obj, "");
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest Average value of 'pswpin/s'   is %13.2f (%s)",
            get_pswap_avg_highest_val("pswpin"), get_pswap_avg_highest_date("pswpin"));
        append_list(&report_pswap_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  Average value of 'pswpin/s'   is %13.2f (%s)",
            get_pswap_avg_lowest_val("pswpin"), get_pswap_avg_lowest_date("pswpin"));
        append_list(&report_pswap_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest Average value of 'pswpout/s'  is %13.2f (%s)",
            get_pswap_avg_highest_val("pswpout"), get_pswap_avg_highest_date("pswpout"));
        append_list(&report_pswap_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  Average value of 'pswpout/s'  is %13.2f (%s)",
            get_pswap_avg_lowest_val("pswpout"), get_pswap_avg_lowest_date("pswpout"));
        append_list(&report_pswap_obj, str_tmp);
        /* end averages */

        append_list(&report_pswap_obj, "\n-- Report spikes for each file of swapping statistics --\n");
        for (j = 0; j < files_n; j++) {
            /* set for declaring file no in case -O option is set */
            char str_pswap_tmp[13] = "----file no.";
            char str_num[50] = {'\0'};
            snprintf(str_num, MAX_INPUT, "%s%d", str_pswap_tmp, j + 1);
            append_list(&report_pswap_spike_obj, str_num);
            /* end -- set for declaring file no in case -O option is set */

            snprintf(str_tmp, MAX_LINE_LENGTH, "  Spike   value of 'pswpin/s'   is %13.2f (%s %s)",
                get_pswap_spike_val_each_file(j, "pswpin", "spike"),
                    get_pswap_spike_date_each_file(j, "pswpin", "spike"),
                        get_pswap_spike_time_each_file(j, "pswpin", "spike"));
            append_list(&report_pswap_spike_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Spike   value of 'pswpout/s'  is %13.2f (%s %s)",
                get_pswap_spike_val_each_file(j, "pswpout", "spike"),
                    get_pswap_spike_date_each_file(j, "pswpout", "spike"),
                        get_pswap_spike_time_each_file(j, "pswpout", "spike"));
            append_list(&report_pswap_spike_obj, str_tmp);
            append_list(&report_pswap_spike_obj, "");

            snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest value of 'pswpin/s'   is %13.2f (%s %s)",
                get_pswap_spike_val_each_file(j, "pswpin", "highest"),
                    get_pswap_spike_date_each_file(j, "pswpin", "highest"),
                        get_pswap_spike_time_each_file(j, "pswpin", "highest"));
            append_list(&report_pswap_spike_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest value of 'pswpout/s'  is %13.2f (%s %s)",
                get_pswap_spike_val_each_file(j, "pswpout", "highest"),
                    get_pswap_spike_date_each_file(j, "pswpout", "highest"),
                        get_pswap_spike_time_each_file(j, "pswpout", "highest"));
            append_list(&report_pswap_spike_obj, str_tmp);

            append_list(&report_pswap_spike_obj, "");

            snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  value of 'pswpin/s'   is %13.2f (%s %s)",
                get_pswap_spike_val_each_file(j, "pswpin", "lowest"),
                    get_pswap_spike_date_each_file(j, "pswpin", "lowest"),
                        get_pswap_spike_time_each_file(j, "pswpin", "lowest"));
            append_list(&report_pswap_spike_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  value of 'pswpout/s'  is %13.2f (%s %s)",
                get_pswap_spike_val_each_file(j, "pswpout", "lowest"),
                    get_pswap_spike_date_each_file(j, "pswpout", "lowest"),
                        get_pswap_spike_time_each_file(j, "pswpout", "lowest"));
            append_list(&report_pswap_spike_obj, str_tmp);
            /* for time-span option */
            if (time_span != NULL) {
                append_list(&report_pswap_time_span_spike_obj, str_num);
                snprintf(str_tmp, MAX_LINE_LENGTH, " %s Spike   value of 'pswpin/s'   is %13.2f (%s %s)", time_span,
                    get_pswap_time_span_spike_val_each_file(j, "pswpin", "spike"),
                        get_pswap_time_span_spike_date_each_file(j, "pswpin", "spike"),
                            get_pswap_time_span_spike_time_each_file(j, "pswpin", "spike"));
                append_list(&report_pswap_time_span_spike_obj, str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, " %s Spike   value of 'pswpout/s'  is %13.2f (%s %s)", time_span,
                    get_pswap_time_span_spike_val_each_file(j, "pswpout", "spike"),
                        get_pswap_time_span_spike_date_each_file(j, "pswpout", "spike"),
                            get_pswap_time_span_spike_time_each_file(j, "pswpout", "spike"));
                append_list(&report_pswap_time_span_spike_obj, str_tmp);
                append_list(&report_pswap_time_span_spike_obj, "");

                snprintf(str_tmp, MAX_LINE_LENGTH, " %s Highest value of 'pswpin/s'   is %13.2f (%s %s)", time_span,
                    get_pswap_time_span_spike_val_each_file(j, "pswpin", "highest"),
                        get_pswap_time_span_spike_date_each_file(j, "pswpin", "highest"),
                            get_pswap_time_span_spike_time_each_file(j, "pswpin", "highest"));
                append_list(&report_pswap_time_span_spike_obj, str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, " %s Highest value of 'pswpout/s'  is %13.2f (%s %s)", time_span,
                    get_pswap_time_span_spike_val_each_file(j, "pswpout", "highest"),
                        get_pswap_time_span_spike_date_each_file(j, "pswpout", "highest"),
                            get_pswap_time_span_spike_time_each_file(j, "pswpout", "highest"));
                append_list(&report_pswap_time_span_spike_obj, str_tmp);

                append_list(&report_pswap_time_span_spike_obj, "");

                snprintf(str_tmp, MAX_LINE_LENGTH, " %s Lowest  value of 'pswpin/s'   is %13.2f (%s %s)", time_span,
                    get_pswap_time_span_spike_val_each_file(j, "pswpin", "lowest"),
                        get_pswap_time_span_spike_date_each_file(j, "pswpin", "lowest"),
                            get_pswap_time_span_spike_time_each_file(j, "pswpin", "lowest"));
                append_list(&report_pswap_time_span_spike_obj, str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, " %s Lowest  value of 'pswpout/s'  is %13.2f (%s %s)", time_span,
                    get_pswap_time_span_spike_val_each_file(j, "pswpout", "lowest"),
                        get_pswap_time_span_spike_date_each_file(j, "pswpout", "lowest"),
                            get_pswap_time_span_spike_time_each_file(j, "pswpout", "lowest"));
                append_list(&report_pswap_time_span_spike_obj, str_tmp);
            }
        }

        append_list(&report_pswap_explanation_obj, "--------");
        append_list(&report_pswap_explanation_obj, " pswpin/s is total number of swap pages the system brought in per second.");
        append_list(&report_pswap_explanation_obj, " pswpout/s is total number of swap pages the system brought out per second.");
        append_list(&report_pswap_explanation_obj, " If these values are not 0, the box is lacking on memory.");

        /*  paging */

        append_list(&report_paging_obj, " \n-- Report paging statistics --\n" );
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest value of 'pgpgin/s'  is %13.2f (%s %s)",
            get_paging_highest_val("pgpgin"), get_paging_highest_date("pgpgin"), get_paging_highest_time("pgpgin"));
        append_list(&report_paging_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  value of 'pgpgin/s'  is %13.2f (%s %s)",
            get_paging_lowest_val("pgpgin"), get_paging_lowest_date("pgpgin"), get_paging_lowest_time("pgpgin"));
        append_list(&report_paging_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Spike   value of 'pgpgin/s'  is %13.2f (%s %s)",
            get_paging_spike_val("pgpgin"), get_paging_spike_date("pgpgin"), get_paging_spike_time("pgpgin"));
        append_list(&report_paging_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest value of 'pgpgout/s' is %13.2f (%s %s)",
            get_paging_highest_val("pgpgout"), get_paging_highest_date("pgpgout"), get_paging_highest_time("pgpgout"));
        append_list(&report_paging_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  value of 'pgpgout/s' is %13.2f (%s %s)",
            get_paging_lowest_val("pgpgout"), get_paging_lowest_date("pgpgout"), get_paging_lowest_time("pgpgout"));
        append_list(&report_paging_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Spike   value of 'pgpgout/s' is %13.2f (%s %s)",
            get_paging_spike_val("pgpgout"), get_paging_spike_date("pgpgout"), get_paging_spike_time("pgpgout"));
        append_list(&report_paging_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest value of 'fault/s'   is %13.2f (%s %s)",
            get_paging_highest_val("fault"), get_paging_highest_date("fault"), get_paging_highest_time("fault"));
        append_list(&report_paging_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  value of 'fault/s'   is %13.2f (%s %s)",
            get_paging_lowest_val("fault"), get_paging_lowest_date("fault"), get_paging_lowest_time("fault"));
        append_list(&report_paging_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Spike   value of 'fault/s'   is %13.2f (%s %s)",
            get_paging_spike_val("fault"), get_paging_spike_date("fault"), get_paging_spike_time("fault"));
        append_list(&report_paging_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest value of 'majflt/s'  is %13.2f (%s %s)",
            get_paging_highest_val("majflt"), get_paging_highest_date("majflt"), get_paging_highest_time("majflt"));
        append_list(&report_paging_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  value of 'majflt/s'  is %13.2f (%s %s)",
            get_paging_lowest_val("majflt"), get_paging_lowest_date("majflt"), get_paging_lowest_time("majflt"));
        append_list(&report_paging_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Spike   value of 'majflt/s'  is %13.2f (%s %s)",
            get_paging_spike_val("majflt"), get_paging_spike_date("majflt"), get_paging_spike_time("majflt"));
        append_list(&report_paging_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest value of '%%vmeff/s'  is %13.2f (%s %s)",
            get_paging_highest_val("vmeff"), get_paging_highest_date("vmeff"), get_paging_highest_time("vmeff"));
        append_list(&report_paging_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  value of '%%vmeff/s'  is %13.2f (%s %s)",
            get_paging_lowest_val("vmeff"), get_paging_lowest_date("vmeff"), get_paging_lowest_time("vmeff"));
        append_list(&report_paging_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Spike   value of '%%vmeff/s'  is %13.2f (%s %s)",
            get_paging_spike_val("vmeff"), get_paging_spike_date("vmeff"), get_paging_spike_time("vmeff"));
        append_list(&report_paging_obj, str_tmp);
        /* averages */
        append_list(&report_paging_obj, "");
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest Average value of 'pgpgin/s'  is %13.2f (%s)",
            get_paging_avg_highest_val("pgpgin"), get_paging_avg_highest_date("pgpgin"));
        append_list(&report_paging_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  Average value of 'pgpgin/s'  is %13.2f (%s)",
            get_paging_avg_lowest_val("pgpgin"), get_paging_avg_lowest_date("pgpgin"));
        append_list(&report_paging_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest Average value of 'pgpgout/s' is %13.2f (%s)",
            get_paging_avg_highest_val("pgpgout"), get_paging_avg_highest_date("pgpgout"));
        append_list(&report_paging_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  Average value of 'pgpgout/s' is %13.2f (%s)",
            get_paging_avg_lowest_val("pgpgout"), get_paging_avg_lowest_date("pgpgout"));
        append_list(&report_paging_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest Average value of 'fault/s'   is %13.2f (%s)",
            get_paging_avg_highest_val("fault"), get_paging_avg_highest_date("fault"));
        append_list(&report_paging_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  Average value of 'fault/s'   is %13.2f (%s)",
            get_paging_avg_lowest_val("fault"), get_paging_avg_lowest_date("fault"));
        append_list(&report_paging_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest Average value of 'majflt/s'  is %13.2f (%s)",
            get_paging_avg_highest_val("majflt"), get_paging_avg_highest_date("majflt"));
        append_list(&report_paging_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  Average value of 'majflt/s'  is %13.2f (%s)",
            get_paging_avg_lowest_val("majflt"), get_paging_avg_lowest_date("majflt"));
        append_list(&report_paging_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest Average value of '%%vmeff/s'  is %13.2f (%s)",
            get_paging_avg_highest_val("vmeff"), get_paging_avg_highest_date("vmeff"));
        append_list(&report_paging_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  Average value of '%%vmeff/s'  is %13.2f (%s)",
            get_paging_avg_lowest_val("vmeff"), get_paging_avg_lowest_date("vmeff"));
        append_list(&report_paging_obj, str_tmp);
        /* end averages */

        append_list(&report_paging_obj, "\n-- Report spikes for each file of paging statistics --\n");
        for (j = 0; j < files_n; j++) {
            /* set for declaring file no in case -O option is set */
            char str_paging_tmp[13] = "----file no.";
            char str_num[50] = {'\0'};
            snprintf(str_num, MAX_INPUT, "%s%d", str_paging_tmp, j + 1);
            append_list(&report_paging_spike_obj, str_num);
            /* end -- set for declaring file no in case -O option is set */

            snprintf(str_tmp, MAX_LINE_LENGTH, "  Spike   value of 'pgpgin/s'  is %13.2f (%s %s)",
                get_paging_spike_val_each_file(j, "pgpgin", "spike"), get_paging_spike_date_each_file(j, "pgpgin", "spike"),
                    get_paging_spike_time_each_file(j, "pgpgin", "spike"));
            append_list(&report_paging_spike_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Spike   value of 'pgpgout/s' is %13.2f (%s %s)",
                get_paging_spike_val_each_file(j, "pgpgout", "spike"), get_paging_spike_date_each_file(j, "pgpgout", "spike"),
                    get_paging_spike_time_each_file(j, "pgpgout", "spike"));
            append_list(&report_paging_spike_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Spike   value of 'fault/s'   is %13.2f (%s %s)",
                get_paging_spike_val_each_file(j, "fault", "spike"), get_paging_spike_date_each_file(j, "fault", "spike"),
                    get_paging_spike_time_each_file(j, "fault", "spike"));
            append_list(&report_paging_spike_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Spike   value of 'majflt/s'  is %13.2f (%s %s)",
                get_paging_spike_val_each_file(j, "majflt", "spike"), get_paging_spike_date_each_file(j, "majflt", "spike"),
                    get_paging_spike_time_each_file(j, "majflt", "spike"));
            append_list(&report_paging_spike_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Spike   value of '%%vmeff/s'  is %13.2f (%s %s)",
                get_paging_spike_val_each_file(j, "vmeff", "spike"), get_paging_spike_date_each_file(j, "vmeff", "spike"),
                    get_paging_spike_time_each_file(j, "vmeff", "spike"));
            append_list(&report_paging_spike_obj, str_tmp);
            append_list(&report_paging_spike_obj, "");

            snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest value of 'pgpgin/s'  is %13.2f (%s %s)",
                get_paging_spike_val_each_file(j, "pgpgin", "highest"), get_paging_spike_date_each_file(j, "pgpgin", "highest"),
                    get_paging_spike_time_each_file(j, "pgpgin", "highest"));
            append_list(&report_paging_spike_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest value of 'pgpgout/s' is %13.2f (%s %s)",
                get_paging_spike_val_each_file(j, "pgpgout", "highest"), get_paging_spike_date_each_file(j, "pgpgout", "highest"),
                    get_paging_spike_time_each_file(j, "pgpgout", "highest"));
            append_list(&report_paging_spike_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest value of 'fault/s'   is %13.2f (%s %s)",
                get_paging_spike_val_each_file(j, "fault", "highest"), get_paging_spike_date_each_file(j, "fault", "highest"),
                    get_paging_spike_time_each_file(j, "fault", "highest"));
            append_list(&report_paging_spike_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest value of 'majflt/s'  is %13.2f (%s %s)",
                get_paging_spike_val_each_file(j, "majflt", "highest"), get_paging_spike_date_each_file(j, "majflt", "highest"),
                    get_paging_spike_time_each_file(j, "majflt", "highest"));
            append_list(&report_paging_spike_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest value of '%%vmeff/s'  is %13.2f (%s %s)",
                get_paging_spike_val_each_file(j, "vmeff", "highest"), get_paging_spike_date_each_file(j, "vmeff", "highest"),
                    get_paging_spike_time_each_file(j, "vmeff", "highest"));
            append_list(&report_paging_spike_obj, str_tmp);

            append_list(&report_paging_spike_obj, "");

            snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  value of 'pgpgin/s'  is %13.2f (%s %s)",
                get_paging_spike_val_each_file(j, "pgpgin", "lowest"), get_paging_spike_date_each_file(j, "pgpgin", "lowest"),
                    get_paging_spike_time_each_file(j, "pgpgin", "lowest"));
            append_list(&report_paging_spike_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  value of 'pgpgout/s' is %13.2f (%s %s)",
                get_paging_spike_val_each_file(j, "pgpgout", "lowest"), get_paging_spike_date_each_file(j, "pgpgout", "lowest"),
                    get_paging_spike_time_each_file(j, "pgpgout", "lowest"));
            append_list(&report_paging_spike_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  value of 'fault/s'   is %13.2f (%s %s)",
                get_paging_spike_val_each_file(j, "fault", "lowest"), get_paging_spike_date_each_file(j, "fault", "lowest"),
                    get_paging_spike_time_each_file(j, "fault", "lowest"));
            append_list(&report_paging_spike_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  value of 'majflt/s'  is %13.2f (%s %s)",
                get_paging_spike_val_each_file(j, "majflt", "lowest"), get_paging_spike_date_each_file(j, "majflt", "lowest"),
                    get_paging_spike_time_each_file(j, "majflt", "lowest"));
            append_list(&report_paging_spike_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  value of '%%vmeff/s'  is %13.2f (%s %s)",
                get_paging_spike_val_each_file(j, "vmeff", "lowest"), get_paging_spike_date_each_file(j, "vmeff", "lowest"),
                    get_paging_spike_time_each_file(j, "vmeff", "lowest"));
            append_list(&report_paging_spike_obj, str_tmp);
            /* for time-span option */
            if (time_span != NULL) {
                append_list(&report_paging_time_span_spike_obj, str_num);
                snprintf(str_tmp, MAX_LINE_LENGTH, " %s Spike   value of 'pgpgin/s'  is %13.2f (%s %s)", time_span,
                    get_paging_time_span_spike_val_each_file(j, "pgpgin", "spike"),
                        get_paging_time_span_spike_date_each_file(j, "pgpgin", "spike"),
                            get_paging_time_span_spike_time_each_file(j, "pgpgin", "spike"));
                append_list(&report_paging_time_span_spike_obj, str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, " %s Spike   value of 'pgpgout/s' is %13.2f (%s %s)", time_span,
                    get_paging_time_span_spike_val_each_file(j, "pgpgout", "spike"),
                        get_paging_time_span_spike_date_each_file(j, "pgpgout", "spike"),
                            get_paging_time_span_spike_time_each_file(j, "pgpgout", "spike"));
                append_list(&report_paging_time_span_spike_obj, str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, " %s Spike   value of 'fault/s'   is %13.2f (%s %s)", time_span,
                    get_paging_time_span_spike_val_each_file(j, "fault", "spike"),
                        get_paging_time_span_spike_date_each_file(j, "fault", "spike"),
                            get_paging_time_span_spike_time_each_file(j, "fault", "spike"));
                append_list(&report_paging_time_span_spike_obj, str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, " %s Spike   value of 'majflt/s'  is %13.2f (%s %s)", time_span,
                    get_paging_time_span_spike_val_each_file(j, "majflt", "spike"),
                        get_paging_time_span_spike_date_each_file(j, "majflt", "spike"),
                            get_paging_time_span_spike_time_each_file(j, "majflt", "spike"));
                append_list(&report_paging_time_span_spike_obj, str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, " %s Spike   value of '%%vmeff/s'  is %13.2f (%s %s)",time_span,
                    get_paging_time_span_spike_val_each_file(j, "vmeff", "spike"),
                        get_paging_time_span_spike_date_each_file(j, "vmeff", "spike"),
                            get_paging_time_span_spike_time_each_file(j, "vmeff", "spike"));
                append_list(&report_paging_time_span_spike_obj, str_tmp);
                append_list(&report_paging_time_span_spike_obj, "");

                snprintf(str_tmp, MAX_LINE_LENGTH, " %s Highest value of 'pgpgin/s'  is %13.2f (%s %s)", time_span,
                    get_paging_time_span_spike_val_each_file(j, "pgpgin", "highest"),
                        get_paging_time_span_spike_date_each_file(j, "pgpgin", "highest"),
                            get_paging_time_span_spike_time_each_file(j, "pgpgin", "highest"));
                append_list(&report_paging_time_span_spike_obj, str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, " %s Highest value of 'pgpgout/s' is %13.2f (%s %s)",time_span,
                    get_paging_time_span_spike_val_each_file(j, "pgpgout", "highest"),
                        get_paging_time_span_spike_date_each_file(j, "pgpgout", "highest"),
                            get_paging_time_span_spike_time_each_file(j, "pgpgout", "highest"));
                append_list(&report_paging_time_span_spike_obj, str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, " %s Highest value of 'fault/s'   is %13.2f (%s %s)", time_span,
                    get_paging_time_span_spike_val_each_file(j, "fault", "highest"),
                        get_paging_time_span_spike_date_each_file(j, "fault", "highest"),
                            get_paging_time_span_spike_time_each_file(j, "fault", "highest"));
                append_list(&report_paging_time_span_spike_obj, str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, " %s Highest value of 'majflt/s'  is %13.2f (%s %s)", time_span,
                    get_paging_time_span_spike_val_each_file(j, "majflt", "highest"),
                        get_paging_time_span_spike_date_each_file(j, "majflt", "highest"),
                            get_paging_time_span_spike_time_each_file(j, "majflt", "highest"));
                append_list(&report_paging_time_span_spike_obj, str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, " %s Highest value of '%%vmeff/s'  is %13.2f (%s %s)", time_span,
                get_paging_time_span_spike_val_each_file(j, "vmeff", "highest"),
                    get_paging_time_span_spike_date_each_file(j, "vmeff", "highest"),
                        get_paging_time_span_spike_time_each_file(j, "vmeff", "highest"));
                append_list(&report_paging_time_span_spike_obj, str_tmp);

                append_list(&report_paging_time_span_spike_obj, "");

                snprintf(str_tmp, MAX_LINE_LENGTH, " %s Lowest  value of 'pgpgin/s'  is %13.2f (%s %s)", time_span,
                    get_paging_time_span_spike_val_each_file(j, "pgpgin", "lowest"),
                        get_paging_time_span_spike_date_each_file(j, "pgpgin", "lowest"),
                            get_paging_time_span_spike_time_each_file(j, "pgpgin", "lowest"));
                append_list(&report_paging_time_span_spike_obj, str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, " %s Lowest  value of 'pgpgout/s' is %13.2f (%s %s)",time_span,
                    get_paging_time_span_spike_val_each_file(j, "pgpgout", "lowest"),
                        get_paging_time_span_spike_date_each_file(j, "pgpgout", "lowest"),
                            get_paging_time_span_spike_time_each_file(j, "pgpgout", "lowest"));
                append_list(&report_paging_time_span_spike_obj, str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, " %s Lowest  value of 'fault/s'   is %13.2f (%s %s)", time_span,
                    get_paging_time_span_spike_val_each_file(j, "fault", "lowest"),
                        get_paging_time_span_spike_date_each_file(j, "fault", "lowest"),
                            get_paging_time_span_spike_time_each_file(j, "fault", "lowest"));
                append_list(&report_paging_time_span_spike_obj, str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, " %s Lowest  value of 'majflt/s'  is %13.2f (%s %s)", time_span,
                    get_paging_time_span_spike_val_each_file(j, "majflt", "lowest"),
                        get_paging_time_span_spike_date_each_file(j, "majflt", "lowest"),
                            get_paging_time_span_spike_time_each_file(j, "majflt", "lowest"));
                append_list(&report_paging_time_span_spike_obj, str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, " %s Lowest  value of '%%vmeff/s'  is %13.2f (%s %s)", time_span,
                get_paging_time_span_spike_val_each_file(j, "vmeff", "lowest"),
                    get_paging_time_span_spike_date_each_file(j, "vmeff", "lowest"),
                        get_paging_time_span_spike_time_each_file(j, "vmeff", "lowest"));
                append_list(&report_paging_time_span_spike_obj, str_tmp);
            }
        }
        append_list(&report_paging_explanation_obj, "--------");
        append_list(&report_paging_explanation_obj, " If pgpgin/s is high, It is most doubtful that thrashing is occurring. Check cpu's '%iowait' in that very time.");
        append_list(&report_paging_explanation_obj, " If fault/s is high, programs may requiring memory. Check with, say '# ps -o min_flt,maj_flt <PID>'.");
        append_list(&report_paging_explanation_obj, " If majflt/s is starting to become high at some time, some big program had been started somehow on that day.");
        append_list(&report_paging_explanation_obj, " If majflt/s is high some program is waiting to complete disk I/O.");
        append_list(&report_paging_explanation_obj, " If vmeff/s is 0, no worry on memory, if vmeff/s is not 0 and over 90.00, it is good.");
        append_list(&report_paging_explanation_obj, " If vmeff/s is under 30.00, somethig is wrong.");

        /* io_transfer_rate */

        append_list(&report_io_transfer_rate_obj, " \n-- Report I/O and transfer rate statistics --\n");
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest value of 'tps'     is %13.2f (%s %s)",
            get_io_transfer_rate_highest_val("tps"), get_io_transfer_rate_highest_date("tps"),
                get_io_transfer_rate_highest_time("tps"));
        append_list(&report_io_transfer_rate_obj, str_tmp );
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  value of 'tps'     is %13.2f (%s %s)",
            get_io_transfer_rate_lowest_val("tps"), get_io_transfer_rate_lowest_date("tps"),
                get_io_transfer_rate_lowest_time("tps"));
        append_list(&report_io_transfer_rate_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Spike   value of 'tps'     is %13.2f (%s %s)",
            get_io_transfer_rate_spike_val("tps"), get_io_transfer_rate_spike_date("tps"),
                get_io_transfer_rate_spike_time("tps"));
        append_list(&report_io_transfer_rate_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest value of 'bread/s' is %13.2f (%s %s)",
            get_io_transfer_rate_highest_val("bread"), get_io_transfer_rate_highest_date("bread"),
                get_io_transfer_rate_highest_time("bread"));
        append_list(&report_io_transfer_rate_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  value of 'bread/s' is %13.2f (%s %s)",
            get_io_transfer_rate_lowest_val("bread"), get_io_transfer_rate_lowest_date ( "bread"),
                get_io_transfer_rate_lowest_time("bread"));
        append_list(&report_io_transfer_rate_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Spike   value of 'bread/s' is %13.2f (%s %s)",
            get_io_transfer_rate_spike_val("bread"), get_io_transfer_rate_spike_date ( "bread"),
                get_io_transfer_rate_spike_time("bread"));
        append_list(&report_io_transfer_rate_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest value of 'bwrtn/s' is %13.2f (%s %s)",
            get_io_transfer_rate_highest_val("bwrtn"), get_io_transfer_rate_highest_date ( "bwrtn"),
                get_io_transfer_rate_highest_time("bwrtn"));
        append_list(&report_io_transfer_rate_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  value of 'bwrtn/s' is %13.2f (%s %s)",
            get_io_transfer_rate_lowest_val("bwrtn"), get_io_transfer_rate_lowest_date ( "bwrtn"),
                get_io_transfer_rate_lowest_time("bwrtn"));
        append_list(&report_io_transfer_rate_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Spike   value of 'bwrtn/s' is %13.2f (%s %s)",
            get_io_transfer_rate_spike_val("bwrtn"), get_io_transfer_rate_spike_date ( "bwrtn" ),
                get_io_transfer_rate_spike_time("bwrtn"));
        append_list(&report_io_transfer_rate_obj, str_tmp);
        /* averages */
        append_list(&report_io_transfer_rate_obj, "");
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest Average value of 'tps'     is %13.2f (%s)",
            get_io_transfer_rate_avg_highest_val("tps"),
                get_io_transfer_rate_avg_highest_date("tps"));
        append_list(&report_io_transfer_rate_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  Average value of 'tps'     is %13.2f (%s)",
            get_io_transfer_rate_avg_lowest_val("tps"),
                get_io_transfer_rate_avg_lowest_date("tps"));
        append_list(&report_io_transfer_rate_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest Average value of 'bread/s' is %13.2f (%s)",
            get_io_transfer_rate_avg_highest_val("bread"),
                get_io_transfer_rate_avg_highest_date("bread"));
        append_list(&report_io_transfer_rate_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  Average value of 'bread/s' is %13.2f (%s)",
            get_io_transfer_rate_avg_lowest_val("bread"),
                get_io_transfer_rate_avg_lowest_date("bread"));
        append_list(&report_io_transfer_rate_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest Average value of 'bwrtn/s' is %13.2f (%s)",
            get_io_transfer_rate_avg_highest_val("bwrtn"),
                get_io_transfer_rate_avg_highest_date("bwrtn"));
        append_list(&report_io_transfer_rate_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  Average value of 'bwrtn/s' is %13.2f (%s)",
            get_io_transfer_rate_avg_lowest_val("bwrtn"),
                get_io_transfer_rate_avg_lowest_date("bwrtn"));
        append_list(&report_io_transfer_rate_obj, str_tmp);
        /* end averages */

        append_list(&report_io_transfer_rate_obj, "\n-- Report spikes for each file of I/O and transfer rate statistics --\n" );
        for (j = 0; j < files_n; j++) {
            /* set for declaring file no in case -O option is set */
            char str_io_transfer_rate_tmp[13] = "----file no.";
            char str_num[50] = {'\0'};
            snprintf(str_num, MAX_INPUT, "%s%d", str_io_transfer_rate_tmp, j + 1);
            append_list(&report_io_transfer_rate_spike_obj, str_num );
            /* end -- set for declaring file no in case -O option is set */

            snprintf(str_tmp, MAX_LINE_LENGTH, "  Spike   value of 'tps'     is %13.2f (%s %s)",
                get_io_transfer_rate_spike_val_each_file(j, "tps", "spike"),
                    get_io_transfer_rate_spike_date_each_file(j, "tps", "spike"),
                        get_io_transfer_rate_spike_time_each_file(j, "tps", "spike"));
            append_list(&report_io_transfer_rate_spike_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Spike   value of 'bread/s' is %13.2f (%s %s)",
                get_io_transfer_rate_spike_val_each_file(j, "bread", "spike"),
                    get_io_transfer_rate_spike_date_each_file(j, "bread", "spike"),
                        get_io_transfer_rate_spike_time_each_file(j, "bread", "spike"));
            append_list(&report_io_transfer_rate_spike_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Spike   value of 'bwrtn/s' is %13.2f (%s %s)",
                get_io_transfer_rate_spike_val_each_file(j, "bwrtn", "spike"),
                    get_io_transfer_rate_spike_date_each_file(j, "bwrtn", "spike"),
                        get_io_transfer_rate_spike_time_each_file(j, "bwrtn", "spike"));
            append_list(&report_io_transfer_rate_spike_obj, str_tmp);
            append_list(&report_io_transfer_rate_spike_obj, "");

            snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest value of 'tps'     is %13.2f (%s %s)",
                get_io_transfer_rate_spike_val_each_file(j, "tps", "highest"),
                    get_io_transfer_rate_spike_date_each_file(j, "tps", "highest"),
                        get_io_transfer_rate_spike_time_each_file(j, "tps", "highest"));
            append_list(&report_io_transfer_rate_spike_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest value of 'bread/s' is %13.2f (%s %s)",
                get_io_transfer_rate_spike_val_each_file(j, "bread", "highest"),
                    get_io_transfer_rate_spike_date_each_file(j, "bread", "highest"),
                        get_io_transfer_rate_spike_time_each_file(j, "bread", "highest"));
            append_list(&report_io_transfer_rate_spike_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest value of 'bwrtn/s' is %13.2f (%s %s)",
                get_io_transfer_rate_spike_val_each_file(j, "bwrtn", "highest"),
                    get_io_transfer_rate_spike_date_each_file(j, "bwrtn", "highest"),
                        get_io_transfer_rate_spike_time_each_file(j, "bwrtn", "highest"));
            append_list(&report_io_transfer_rate_spike_obj, str_tmp);

            append_list(&report_io_transfer_rate_spike_obj, "");

            snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  value of 'tps'     is %13.2f (%s %s)",
                get_io_transfer_rate_spike_val_each_file(j, "tps", "lowest"),
                    get_io_transfer_rate_spike_date_each_file(j, "tps", "lowest"),
                        get_io_transfer_rate_spike_time_each_file(j, "tps", "lowest"));
            append_list(&report_io_transfer_rate_spike_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  value of 'bread/s' is %13.2f (%s %s)",
                get_io_transfer_rate_spike_val_each_file(j, "bread", "lowest"),
                    get_io_transfer_rate_spike_date_each_file(j, "bread", "lowest"),
                        get_io_transfer_rate_spike_time_each_file(j, "bread", "lowest"));
            append_list(&report_io_transfer_rate_spike_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  value of 'bwrtn/s' is %13.2f (%s %s)",
                get_io_transfer_rate_spike_val_each_file(j, "bwrtn", "lowest"),
                    get_io_transfer_rate_spike_date_each_file(j, "bwrtn", "lowest"),
                        get_io_transfer_rate_spike_time_each_file(j, "bwrtn", "lowest"));
            append_list(&report_io_transfer_rate_spike_obj, str_tmp);
            /* for time-span option */
            if (time_span != NULL) {
                append_list(&report_io_transfer_rate_time_span_spike_obj, str_num );
                snprintf(str_tmp, MAX_LINE_LENGTH, " %s Spike   value of 'tps'     is %13.2f (%s %s)", time_span,
                    get_io_transfer_rate_time_span_spike_val_each_file(j, "tps", "spike"),
                        get_io_transfer_rate_time_span_spike_date_each_file(j, "tps", "spike"),
                            get_io_transfer_rate_time_span_spike_time_each_file(j, "tps", "spike"));
                append_list(&report_io_transfer_rate_time_span_spike_obj, str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, " %s Spike   value of 'bread/s' is %13.2f (%s %s)", time_span,
                    get_io_transfer_rate_time_span_spike_val_each_file(j, "bread", "spike"),
                        get_io_transfer_rate_time_span_spike_date_each_file(j, "bread", "spike"),
                            get_io_transfer_rate_time_span_spike_time_each_file(j, "bread", "spike"));
                append_list(&report_io_transfer_rate_time_span_spike_obj, str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, " %s Spike   value of 'bwrtn/s' is %13.2f (%s %s)", time_span,
                    get_io_transfer_rate_time_span_spike_val_each_file(j, "bwrtn", "spike"),
                        get_io_transfer_rate_time_span_spike_date_each_file(j, "bwrtn", "spike"),
                            get_io_transfer_rate_time_span_spike_time_each_file(j, "bwrtn", "spike"));
                append_list(&report_io_transfer_rate_time_span_spike_obj, str_tmp);
                append_list(&report_io_transfer_rate_time_span_spike_obj, "");

                snprintf(str_tmp, MAX_LINE_LENGTH, " %s Highest value of 'tps'     is %13.2f (%s %s)", time_span,
                    get_io_transfer_rate_time_span_spike_val_each_file(j, "tps", "highest"),
                        get_io_transfer_rate_time_span_spike_date_each_file(j, "tps", "highest"),
                            get_io_transfer_rate_time_span_spike_time_each_file(j, "tps", "highest"));
                append_list(&report_io_transfer_rate_time_span_spike_obj, str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, " %s Highest value of 'bread/s' is %13.2f (%s %s)", time_span,
                    get_io_transfer_rate_time_span_spike_val_each_file(j, "bread", "highest"),
                        get_io_transfer_rate_time_span_spike_date_each_file(j, "bread", "highest"),
                            get_io_transfer_rate_time_span_spike_time_each_file(j, "bread", "highest"));
                append_list(&report_io_transfer_rate_time_span_spike_obj, str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, " %s Highest value of 'bwrtn/s' is %13.2f (%s %s)", time_span,
                    get_io_transfer_rate_time_span_spike_val_each_file(j, "bwrtn", "highest"),
                        get_io_transfer_rate_time_span_spike_date_each_file(j, "bwrtn", "highest"),
                            get_io_transfer_rate_time_span_spike_time_each_file(j, "bwrtn", "highest"));
                append_list(&report_io_transfer_rate_time_span_spike_obj, str_tmp);

                append_list(&report_io_transfer_rate_time_span_spike_obj, "");

                snprintf(str_tmp, MAX_LINE_LENGTH, " %s Lowest  value of 'tps'     is %13.2f (%s %s)", time_span,
                    get_io_transfer_rate_time_span_spike_val_each_file(j, "tps", "lowest"),
                        get_io_transfer_rate_time_span_spike_date_each_file(j, "tps", "lowest"),
                            get_io_transfer_rate_time_span_spike_time_each_file(j, "tps", "lowest"));
                append_list(&report_io_transfer_rate_time_span_spike_obj, str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, " %s Lowest  value of 'bread/s' is %13.2f (%s %s)", time_span,
                    get_io_transfer_rate_time_span_spike_val_each_file(j, "bread", "lowest"),
                        get_io_transfer_rate_time_span_spike_date_each_file(j, "bread", "lowest"),
                            get_io_transfer_rate_time_span_spike_time_each_file(j, "bread", "lowest"));
                append_list(&report_io_transfer_rate_time_span_spike_obj, str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, " %s Lowest  value of 'bwrtn/s' is %13.2f (%s %s)", time_span,
                    get_io_transfer_rate_time_span_spike_val_each_file(j, "bwrtn", "lowest"),
                        get_io_transfer_rate_time_span_spike_date_each_file(j, "bwrtn", "lowest"),
                            get_io_transfer_rate_time_span_spike_time_each_file(j, "bwrtn", "lowest"));
                append_list(&report_io_transfer_rate_time_span_spike_obj, str_tmp);
            }
        }

        append_list(&report_io_transfer_rate_explanation_obj, "--------");
        append_list(&report_io_transfer_rate_explanation_obj, " tps is total number of transfers per second that were issued to physical devices."); 
        append_list(&report_io_transfer_rate_explanation_obj, " A transfer is an I/O request to a physical device."); 
        append_list(&report_io_transfer_rate_explanation_obj, " Multiple logical requests can be combined into a single I/O request to the device.");
        append_list(&report_io_transfer_rate_explanation_obj, " A transfer is of indeterminate size.");
        append_list(&report_io_transfer_rate_explanation_obj, " bread/s is Total amount of data read from the devices in blocks per second.");
        append_list(&report_io_transfer_rate_explanation_obj, " Blocks are equivalent to sectors and therefore have a size of 512 bytes.");
        append_list(&report_io_transfer_rate_explanation_obj, " bwrtn/s is Total amount of data written to devices in blocks per second.");

        /* memory */

        append_list(&report_memory_obj, " \n-- Report memory utilization statistics --\n" );
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest value of '%%memused' is %13.2f (%s %s)",
            get_memory_highest_val("memused"), get_memory_highest_date("memused"), get_memory_highest_time("memused"));
        append_list(&report_memory_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  value of '%%memused' is %13.2f (%s %s)",
            get_memory_lowest_val("memused"), get_memory_lowest_date("memused"), get_memory_lowest_time("memused"));
        append_list(&report_memory_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Spike   value of '%%memused' is %13.2f (%s %s)",
            get_memory_spike_val("memused"), get_memory_spike_date("memused"), get_memory_spike_time("memused"));
        append_list(&report_memory_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest value of 'kbcommit' is %13d (%s %s)",
            (int)get_memory_highest_val("kbcommit"), get_memory_highest_date("kbcommit"), get_memory_highest_time("kbcommit"));
        append_list(&report_memory_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  value of 'kbcommit' is %13d (%s %s)",
            (int)get_memory_lowest_val("kbcommit"), get_memory_lowest_date("kbcommit"), get_memory_lowest_time("kbcommit"));
        append_list(&report_memory_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Spike   value of 'kbcommit' is %13d (%s %s)",
            (int)get_memory_spike_val("kbcommit"), get_memory_spike_date("kbcommit"), get_memory_spike_time("kbcommit"));
        append_list(&report_memory_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest value of '%%commit'  is %13.2f (%s %s)",
            get_memory_highest_val("commit"), get_memory_highest_date("commit"), get_memory_highest_time("commit"));
        append_list(&report_memory_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  value of '%%commit'  is %13.2f (%s %s)",
            get_memory_lowest_val("commit"), get_memory_lowest_date("commit"), get_memory_lowest_time("commit"));
        append_list(&report_memory_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Spike   value of '%%commit'  is %13.2f (%s %s)",
            get_memory_spike_val("commit"), get_memory_spike_date("commit"), get_memory_spike_time("commit"));
        append_list(&report_memory_obj, str_tmp);
        /* averages */
        append_list(&report_memory_obj, "");
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest Average value of '%%memused' is %13.2f (%s)",
            get_memory_avg_highest_val("memused"), get_memory_avg_highest_date("memused"));
        append_list(&report_memory_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  Average value of '%%memused' is %13.2f (%s)",
            get_memory_avg_lowest_val("memused"), get_memory_avg_lowest_date("memused"));
        append_list(&report_memory_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest Average value of 'kbcommit' is %13d (%s)",
            (int)get_memory_avg_highest_val("kbcommit"), get_memory_avg_highest_date("kbcommit"));
        append_list(&report_memory_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  Average value of 'kbcommit' is %13d (%s)",
            (int)get_memory_avg_lowest_val("kbcommit"), get_memory_avg_lowest_date("kbcommit"));
        append_list(&report_memory_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest Average value of '%%commit'  is %13.2f (%s)",
            get_memory_avg_highest_val("commit"), get_memory_avg_highest_date("commit"));
        append_list(&report_memory_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  Average value of '%%commit'  is %13.2f (%s)",
            get_memory_avg_lowest_val("commit"), get_memory_avg_lowest_date("commit"));
        append_list(&report_memory_obj, str_tmp);
        /* end averages */

        append_list (&report_memory_obj, "\n-- Report spikes for each file of memory utilization statistics --\n");
        for (j = 0; j < files_n; j++) {
            /* set for declaring file no in case -O option is set */
            char str_memory_tmp[13] = "----file no.";
            char str_num[50] = {'\0'};
            snprintf(str_num, MAX_INPUT, "%s%d", str_memory_tmp, j + 1);
            append_list(&report_memory_spike_obj, str_num);
            /* end -- set for declaring file no in case -O option is set */

            snprintf(str_tmp, MAX_LINE_LENGTH, "  Spike   value of '%%memused' is %13.2f (%s %s)",
                get_memory_spike_val_each_file(j, "memused", "spike"),
                    get_memory_spike_date_each_file(j, "memused", "spike"),
                        get_memory_spike_time_each_file(j, "memused", "spike"));
            append_list(&report_memory_spike_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Spike   value of 'kbcommit' is %13d (%s %s)",
                (int)get_memory_spike_val_each_file(j, "kbcommit", "spike"),
                    get_memory_spike_date_each_file(j, "kbcommit", "spike"),
                        get_memory_spike_time_each_file(j, "kbcommit", "spike"));
            append_list(&report_memory_spike_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Spike   value of '%%commit'  is %13.2f (%s %s)",
                get_memory_spike_val_each_file(j, "commit", "spike"),
                    get_memory_spike_date_each_file(j, "commit", "spike"),
                        get_memory_spike_time_each_file(j, "commit", "spike"));
            append_list(&report_memory_spike_obj, str_tmp);
            append_list(&report_memory_spike_obj, "");

            snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest value of '%%memused' is %13.2f (%s %s)",
                get_memory_spike_val_each_file(j, "memused", "highest"),
                    get_memory_spike_date_each_file(j, "memused", "highest"),
                        get_memory_spike_time_each_file(j, "memused", "highest"));
            append_list(&report_memory_spike_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest value of 'kbcommit' is %13d (%s %s)",
                (int)get_memory_spike_val_each_file(j, "kbcommit", "highest"),
                    get_memory_spike_date_each_file(j, "kbcommit", "highest"),
                        get_memory_spike_time_each_file(j, "kbcommit", "highest"));
            append_list(&report_memory_spike_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest value of '%%commit'  is %13.2f (%s %s)",
                get_memory_spike_val_each_file(j, "commit", "highest"),
                    get_memory_spike_date_each_file(j, "commit", "highest"),
                        get_memory_spike_time_each_file(j, "commit", "highest"));
            append_list(&report_memory_spike_obj, str_tmp);

            append_list(&report_memory_spike_obj, "");

            snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  value of '%%memused' is %13.2f (%s %s)",
                get_memory_spike_val_each_file(j, "memused", "lowest"),
                    get_memory_spike_date_each_file(j, "memused", "lowest"),
                        get_memory_spike_time_each_file(j, "memused", "lowest"));
            append_list(&report_memory_spike_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  value of 'kbcommit' is %13d (%s %s)",
                (int)get_memory_spike_val_each_file(j, "kbcommit", "lowest"),
                    get_memory_spike_date_each_file(j, "kbcommit", "lowest"),
                        get_memory_spike_time_each_file(j, "kbcommit", "lowest"));
            append_list(&report_memory_spike_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  value of '%%commit'  is %13.2f (%s %s)",
                get_memory_spike_val_each_file(j, "commit", "lowest"),
                    get_memory_spike_date_each_file(j, "commit", "lowest"),
                        get_memory_spike_time_each_file(j, "commit", "lowest"));
            append_list(&report_memory_spike_obj, str_tmp);
            /* for time-span option */
            if (time_span != NULL) {
                append_list(&report_memory_time_span_spike_obj, str_num);
                snprintf(str_tmp, MAX_LINE_LENGTH, " %s Spike   value of '%%memused' is %13.2f (%s %s)", time_span,
                    get_memory_time_span_spike_val_each_file(j, "memused", "spike"),
                        get_memory_time_span_spike_date_each_file(j, "memused", "spike"),
                            get_memory_time_span_spike_time_each_file(j, "memused", "spike"));
                append_list(&report_memory_time_span_spike_obj, str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, " %s Spike   value of 'kbcommit' is %13d (%s %s)", time_span,
                    (int)get_memory_time_span_spike_val_each_file(j, "kbcommit", "spike"),
                        get_memory_time_span_spike_date_each_file(j, "kbcommit", "spike"),
                            get_memory_time_span_spike_time_each_file(j, "kbcommit", "spike"));
                append_list(&report_memory_time_span_spike_obj, str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, " %s Spike   value of '%%commit'  is %13.2f (%s %s)", time_span,
                    get_memory_time_span_spike_val_each_file(j, "commit", "spike"),
                        get_memory_time_span_spike_date_each_file(j, "commit", "spike"),
                            get_memory_time_span_spike_time_each_file(j, "commit", "spike"));
                append_list(&report_memory_time_span_spike_obj, str_tmp);
                append_list(&report_memory_time_span_spike_obj, "");

                snprintf(str_tmp, MAX_LINE_LENGTH, " %s Highest value of '%%memused' is %13.2f (%s %s)", time_span,
                    get_memory_time_span_spike_val_each_file(j, "memused", "highest"),
                        get_memory_time_span_spike_date_each_file(j, "memused", "highest"),
                            get_memory_time_span_spike_time_each_file(j, "memused", "highest"));
                append_list(&report_memory_time_span_spike_obj, str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, " %s Highest value of 'kbcommit' is %13d (%s %s)", time_span,
                    (int)get_memory_time_span_spike_val_each_file(j, "kbcommit", "highest"),
                        get_memory_time_span_spike_date_each_file(j, "kbcommit", "highest"),
                            get_memory_time_span_spike_time_each_file ( j, "kbcommit", "highest"));
                append_list(&report_memory_time_span_spike_obj, str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, " %s Highest value of '%%commit'  is %13.2f (%s %s)", time_span,
                    get_memory_time_span_spike_val_each_file(j, "commit", "highest"),
                        get_memory_time_span_spike_date_each_file(j, "commit", "highest"),
                            get_memory_time_span_spike_time_each_file(j, "commit", "highest"));
                append_list(&report_memory_time_span_spike_obj, str_tmp);

                append_list(&report_memory_time_span_spike_obj, "");

                snprintf(str_tmp, MAX_LINE_LENGTH, " %s Lowest  value of '%%memused' is %13.2f (%s %s)", time_span,
                    get_memory_time_span_spike_val_each_file(j, "memused", "lowest"),
                        get_memory_time_span_spike_date_each_file(j, "memused", "lowest"),
                            get_memory_time_span_spike_time_each_file(j, "memused", "lowest"));
                append_list(&report_memory_time_span_spike_obj, str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, " %s Lowest  value of 'kbcommit' is %13d (%s %s)", time_span,
                    (int)get_memory_time_span_spike_val_each_file(j, "kbcommit", "lowest"),
                        get_memory_time_span_spike_date_each_file(j, "kbcommit", "lowest"),
                            get_memory_time_span_spike_time_each_file(j, "kbcommit", "lowest"));
                append_list(&report_memory_time_span_spike_obj, str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, " %s Lowest  value of '%%commit'  is %13.2f (%s %s)", time_span,
                    get_memory_time_span_spike_val_each_file(j, "commit", "lowest"),
                        get_memory_time_span_spike_date_each_file(j, "commit", "lowest"),
                            get_memory_time_span_spike_time_each_file(j, "commit", "lowest"));
                append_list(&report_memory_time_span_spike_obj, str_tmp);
            }
        }

        append_list(&report_memory_explanation_obj, "--------");
        append_list(&report_memory_explanation_obj, " Even if %memused is around 99.0%, it's OK with Linux.");
        append_list(&report_memory_explanation_obj, " Check the highest value of kbcommit. This is the amount of memory needed for the system. If lacking, consider adding more memory.");
        append_list(&report_memory_explanation_obj, " If %commit is over 100%, memory shortage is occurring. Gain swap or add more memory.");

        /* swpused */

        append_list(&report_swpused_obj, " \n-- Report swap space utilization statistics --\n");
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest value of '%%swpused'  is %13.2f (%s %s)",
            get_swpused_highest_val(), get_swpused_highest_date(), get_swpused_highest_time());
        append_list(&report_swpused_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  value of '%%swpused'  is %13.2f (%s %s)",
            get_swpused_lowest_val(), get_swpused_lowest_date(), get_swpused_lowest_time());
        append_list(&report_swpused_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Spike   value of '%%swpused'  is %13.2f (%s %s)",
            get_swpused_spike_val(), get_swpused_spike_date(), get_swpused_spike_time());
        append_list(&report_swpused_obj, str_tmp);
        /* averages */
        append_list(&report_swpused_obj, "");
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest Average value of '%%swpused'  is %13.2f (%s)",
            get_swpused_avg_highest_val(), get_swpused_avg_highest_date());
        append_list(&report_swpused_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  Average value of '%%swpused'  is %13.2f (%s)",
            get_swpused_avg_lowest_val(), get_swpused_avg_lowest_date());
        append_list(&report_swpused_obj, str_tmp);
        /* end averages */

        append_list(&report_swpused_obj, "\n-- Report spikes for each file of swap space utilization statistics --\n" );
        for (j = 0; j < files_n; j++) {
            /* set for declaring file no in case -O option is set */
            char str_swpused_tmp[13] = "----file no.";
            char str_num[50] = {'\0'};
            snprintf(str_num, MAX_INPUT, "%s%d", str_swpused_tmp, j + 1);
            append_list(&report_swpused_spike_obj, str_num);
            /* end -- set for declaring file no in case -O option is set */

            snprintf(str_tmp, MAX_LINE_LENGTH, "  Spike   value of '%%swpused'  is %13.2f (%s %s)",
                get_swpused_spike_val_each_file(j, "spike"), get_swpused_spike_date_each_file(j, "spike"),
                    get_swpused_spike_time_each_file(j, "spike"));
            append_list(&report_swpused_spike_obj, str_tmp);
            append_list(&report_swpused_spike_obj, "");

            snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest value of '%%swpused'  is %13.2f (%s %s)",
                get_swpused_spike_val_each_file(j, "highest"), get_swpused_spike_date_each_file(j, "highest"),
                    get_swpused_spike_time_each_file(j, "highest"));
            append_list(&report_swpused_spike_obj, str_tmp);

            append_list(&report_swpused_spike_obj, "");

            snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  value of '%%swpused'  is %13.2f (%s %s)",
                get_swpused_spike_val_each_file(j, "lowest"), get_swpused_spike_date_each_file(j, "lowest"),
                    get_swpused_spike_time_each_file(j, "lowest"));
            append_list(&report_swpused_spike_obj, str_tmp);
            /* for time-span option */
            if (time_span != NULL) {
                append_list(&report_swpused_time_span_spike_obj, str_num );
                snprintf(str_tmp, MAX_LINE_LENGTH, " %s Spike   value of '%%swpused'  is %13.2f (%s %s)", time_span,
                    get_swpused_time_span_spike_val_each_file(j, "spike"), 
                        get_swpused_time_span_spike_date_each_file(j, "spike"),
                            get_swpused_time_span_spike_time_each_file(j, "spike"));
                append_list(&report_swpused_time_span_spike_obj, str_tmp);
                append_list(&report_swpused_time_span_spike_obj, "");

                snprintf(str_tmp, MAX_LINE_LENGTH, " %s Highest value of '%%swpused'  is %13.2f (%s %s)", time_span,
                    get_swpused_time_span_spike_val_each_file(j, "highest"),
                        get_swpused_time_span_spike_date_each_file(j, "highest"),
                            get_swpused_time_span_spike_time_each_file(j, "highest"));
                append_list(&report_swpused_time_span_spike_obj, str_tmp);

                append_list(&report_swpused_time_span_spike_obj, "");

                snprintf(str_tmp, MAX_LINE_LENGTH, " %s Lowest  value of '%%swpused'  is %13.2f (%s %s)", time_span,
                    get_swpused_time_span_spike_val_each_file(j, "lowest"),
                        get_swpused_time_span_spike_date_each_file(j, "lowest"),
                            get_swpused_time_span_spike_time_each_file(j, "lowest"));
                append_list(&report_swpused_time_span_spike_obj, str_tmp);
            }
        }

        append_list(&report_swpused_explanation_obj, "--------");
        append_list(&report_swpused_explanation_obj, " %swpused percentage of used swap space.");
        append_list(&report_swpused_explanation_obj, " If it's high, the box is lacking on memory.");

        /* kernel_table */

        append_list(&report_kernel_table_obj, " \n-- Report status of inode, file and other kernel tables --\n" );
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest value of 'dentunusd'  is %13d (%s %s)",
            get_kernel_table_highest_val("dentunusd"), get_kernel_table_highest_date("dentunusd"),
                get_kernel_table_highest_time("dentunusd"));
        append_list(&report_kernel_table_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  value of 'dentunusd'  is %13d (%s %s)",
            get_kernel_table_lowest_val("dentunusd"), get_kernel_table_lowest_date("dentunusd"),
                get_kernel_table_lowest_time("dentunusd"));
        append_list(&report_kernel_table_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Spike   value of 'dentunusd'  is %13d (%s %s)",
            get_kernel_table_spike_val("dentunusd"), get_kernel_table_spike_date("dentunusd"),
                get_kernel_table_spike_time("dentunusd"));
        append_list(&report_kernel_table_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest value of 'file-nr'    is %13d (%s %s)",
            get_kernel_table_highest_val("file"), get_kernel_table_highest_date("file"),
                get_kernel_table_highest_time("file"));
        append_list(&report_kernel_table_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  value of 'file-nr'    is %13d (%s %s)",
            get_kernel_table_lowest_val("file"), get_kernel_table_lowest_date("file"),
                get_kernel_table_lowest_time("file"));
        append_list(&report_kernel_table_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Spike   value of 'file-nr'    is %13d (%s %s)",
            get_kernel_table_spike_val("file"), get_kernel_table_spike_date("file"),
                get_kernel_table_spike_time("file"));
        append_list(&report_kernel_table_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest value of 'inode-nr'   is %13d (%s %s)",
            get_kernel_table_highest_val("inode"), get_kernel_table_highest_date("inode"),
                get_kernel_table_highest_time("inode"));
        append_list(&report_kernel_table_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  value of 'inode-nr'   is %13d (%s %s)",
            get_kernel_table_lowest_val("inode"), get_kernel_table_lowest_date("inode"),
                get_kernel_table_lowest_time("inode"));
        append_list(&report_kernel_table_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Spike   value of 'inode-nr'   is %13d (%s %s)",
            get_kernel_table_spike_val("inode"), get_kernel_table_spike_date("inode"),
                get_kernel_table_spike_time("inode"));
        append_list(&report_kernel_table_obj, str_tmp);
        /* averages */
        append_list(&report_kernel_table_obj, "");
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest Average value of 'dentunusd'  is %13d (%s)",
            get_kernel_table_avg_highest_val("dentunusd"), get_kernel_table_avg_highest_date("dentunusd"));
        append_list(&report_kernel_table_obj, str_tmp );
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  Average value of 'dentunusd'  is %13d (%s)",
            get_kernel_table_avg_lowest_val("dentunusd"), get_kernel_table_avg_lowest_date("dentunusd"));
        append_list(&report_kernel_table_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest Average value of 'file-nr'    is %13d (%s)",
            get_kernel_table_avg_highest_val("file"), get_kernel_table_avg_highest_date("file"));
        append_list(&report_kernel_table_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  Average value of 'file-nr'    is %13d (%s)",
            get_kernel_table_avg_lowest_val("file"), get_kernel_table_avg_lowest_date("file"));
        append_list(&report_kernel_table_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest Average value of 'inode-nr'   is %13d (%s)",
            get_kernel_table_avg_highest_val("inode"), get_kernel_table_avg_highest_date("inode"));
        append_list(&report_kernel_table_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  Average value of 'inode-nr'   is %13d (%s)",
            get_kernel_table_avg_lowest_val("inode"), get_kernel_table_avg_lowest_date("inode"));
        append_list(&report_kernel_table_obj, str_tmp);
        /* end averages */

        append_list(&report_kernel_table_obj, "\n-- Report spikes for each file of inode, file and other kernel tables --\n" );
        for (j = 0; j < files_n; j++) {
            /* set for declaring file no in case -O option is set */
            char str_kernel_table_tmp[13] = "----file no.";
            char str_num[50] = {'\0'};
            snprintf(str_num, MAX_INPUT, "%s%d", str_kernel_table_tmp, j + 1 );
            append_list(&report_kernel_table_spike_obj, str_num );
            /* end -- set for declaring file no in case -O option is set */
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Spike   value of 'dentunusd'  is %13d (%s %s)",
                get_kernel_table_spike_val_each_file(j, "dentunusd", "spike"),
                    get_kernel_table_spike_date_each_file(j, "dentunusd", "spike"),
                        get_kernel_table_spike_time_each_file(j, "dentunusd", "spike"));
            append_list(&report_kernel_table_spike_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Spike   value of 'file-nr'    is %13d (%s %s)",
                get_kernel_table_spike_val_each_file(j, "file", "spike"),
                    get_kernel_table_spike_date_each_file(j, "file", "spike"),
                        get_kernel_table_spike_time_each_file(j, "file", "spike"));
            append_list(&report_kernel_table_spike_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Spike   value of 'inode-nr'   is %13d (%s %s)",
                get_kernel_table_spike_val_each_file(j, "inode", "spike"),
                    get_kernel_table_spike_date_each_file(j, "inode", "spike"),
                        get_kernel_table_spike_time_each_file(j, "inode", "spike"));
            append_list(&report_kernel_table_spike_obj, str_tmp);
            append_list(&report_kernel_table_spike_obj, "");

            snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest value of 'dentunusd'  is %13d (%s %s)",
                get_kernel_table_spike_val_each_file(j, "dentunusd", "highest"),
                    get_kernel_table_spike_date_each_file(j, "dentunusd", "highest"),
                        get_kernel_table_spike_time_each_file(j, "dentunusd", "highest"));
            append_list(&report_kernel_table_spike_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest value of 'file-nr'    is %13d (%s %s)",
                get_kernel_table_spike_val_each_file(j, "file", "highest"),
                    get_kernel_table_spike_date_each_file(j, "file", "highest"),
                        get_kernel_table_spike_time_each_file(j, "file", "highest"));
            append_list(&report_kernel_table_spike_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest value of 'inode-nr'   is %13d (%s %s)",
                get_kernel_table_spike_val_each_file(j, "inode", "highest"),
                    get_kernel_table_spike_date_each_file(j, "inode", "highest"),
                        get_kernel_table_spike_time_each_file(j, "inode", "highest"));
            append_list(&report_kernel_table_spike_obj, str_tmp);

            append_list(&report_kernel_table_spike_obj, "");

            snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  value of 'dentunusd'  is %13d (%s %s)",
                get_kernel_table_spike_val_each_file(j, "dentunusd", "lowest"),
                    get_kernel_table_spike_date_each_file(j, "dentunusd", "lowest"),
                        get_kernel_table_spike_time_each_file(j, "dentunusd", "lowest"));
            append_list(&report_kernel_table_spike_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  value of 'file-nr'    is %13d (%s %s)",
                get_kernel_table_spike_val_each_file(j, "file", "lowest"),
                    get_kernel_table_spike_date_each_file(j, "file", "lowest"),
                        get_kernel_table_spike_time_each_file(j, "file", "lowest"));
            append_list(&report_kernel_table_spike_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  value of 'inode-nr'   is %13d (%s %s)",
                get_kernel_table_spike_val_each_file(j, "inode", "lowest"),
                    get_kernel_table_spike_date_each_file(j, "inode", "lowest"),
                        get_kernel_table_spike_time_each_file(j, "inode", "lowest"));
            append_list(&report_kernel_table_spike_obj, str_tmp);
            /* for time-span option */
            if (time_span != NULL) {
                append_list(&report_kernel_table_time_span_spike_obj, str_num);
                snprintf(str_tmp, MAX_LINE_LENGTH, " %s Spike   value of 'dentunusd'  is %13d (%s %s)", time_span,
                    get_kernel_table_time_span_spike_val_each_file(j, "dentunusd", "spike" ),
                        get_kernel_table_time_span_spike_date_each_file(j, "dentunusd", "spike"),
                            get_kernel_table_time_span_spike_time_each_file(j, "dentunusd", "spike"));
                append_list(&report_kernel_table_time_span_spike_obj, str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, " %s Spike   value of 'file-nr'    is %13d (%s %s)", time_span,
                    get_kernel_table_time_span_spike_val_each_file(j, "file", "spike"),
                        get_kernel_table_time_span_spike_date_each_file(j, "file", "spike"),
                            get_kernel_table_time_span_spike_time_each_file(j, "file", "spike"));
                append_list(&report_kernel_table_time_span_spike_obj, str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, " %s Spike   value of 'inode-nr'   is %13d (%s %s)", time_span,
                    get_kernel_table_time_span_spike_val_each_file(j, "inode", "spike"),
                        get_kernel_table_time_span_spike_date_each_file(j, "inode", "spike"),
                            get_kernel_table_time_span_spike_time_each_file(j, "inode", "spike"));
                append_list(&report_kernel_table_time_span_spike_obj, str_tmp);
                append_list(&report_kernel_table_time_span_spike_obj, "");

                snprintf(str_tmp, MAX_LINE_LENGTH, " %s Highest value of 'dentunusd'  is %13d (%s %s)", time_span,
                    get_kernel_table_time_span_spike_val_each_file(j, "dentunusd", "highest"),
                        get_kernel_table_time_span_spike_date_each_file(j, "dentunusd", "highest"),
                            get_kernel_table_time_span_spike_time_each_file(j, "dentunusd", "highest"));
                append_list(&report_kernel_table_time_span_spike_obj, str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, " %s Highest value of 'file-nr'    is %13d (%s %s)", time_span,
                    get_kernel_table_time_span_spike_val_each_file(j, "file", "highest"),
                        get_kernel_table_time_span_spike_date_each_file(j, "file", "highest"),
                            get_kernel_table_time_span_spike_time_each_file(j, "file", "highest"));
                append_list(&report_kernel_table_time_span_spike_obj, str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, " %s Highest value of 'inode-nr'   is %13d (%s %s)", time_span,
                    get_kernel_table_time_span_spike_val_each_file(j, "inode", "highest"),
                        get_kernel_table_time_span_spike_date_each_file(j, "inode", "highest"),
                            get_kernel_table_time_span_spike_time_each_file(j, "inode", "highest"));
                append_list(&report_kernel_table_time_span_spike_obj, str_tmp);

                append_list(&report_kernel_table_time_span_spike_obj, "");

                snprintf(str_tmp, MAX_LINE_LENGTH, " %s Lowest  value of 'dentunusd'  is %13d (%s %s)", time_span,
                    get_kernel_table_time_span_spike_val_each_file(j, "dentunusd", "lowest"),
                        get_kernel_table_time_span_spike_date_each_file(j, "dentunusd", "lowest"),
                            get_kernel_table_time_span_spike_time_each_file(j, "dentunusd", "lowest"));
                append_list(&report_kernel_table_time_span_spike_obj, str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, " %s Lowest  value of 'file-nr'    is %13d (%s %s)", time_span,
                    get_kernel_table_time_span_spike_val_each_file(j, "file", "lowest"),
                        get_kernel_table_time_span_spike_date_each_file(j, "file", "lowest"),
                            get_kernel_table_time_span_spike_time_each_file(j, "file", "lowest"));
                append_list(&report_kernel_table_time_span_spike_obj, str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, " %s Lowest  value of 'inode-nr'   is %13d (%s %s)", time_span,
                    get_kernel_table_time_span_spike_val_each_file(j, "inode", "lowest"),
                        get_kernel_table_time_span_spike_date_each_file(j, "inode", "lowest"),
                            get_kernel_table_time_span_spike_time_each_file(j, "inode", "lowest"));
                append_list(&report_kernel_table_time_span_spike_obj, str_tmp);
            }
        }
        append_list(&report_kernel_table_explanation_obj, "--------");
        append_list(&report_kernel_table_explanation_obj, " dentunusd is number of unused cache entries in the directory cache.");
        append_list(&report_kernel_table_explanation_obj, " file-nr is number of file handles used by the system.");
        append_list(&report_kernel_table_explanation_obj, " inode-nr is number of inode handlers used by the system.");
        append_list(&report_kernel_table_explanation_obj, " Check the order of these values. If it's high, something is wrong.");

        /* ldavg */

        append_list(&report_ldavg_obj, " \n-- Report of queue length and load averages --\n" );
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest value of 'runq-sz'  is %13d (%s %s)",
            (int)get_ldavg_highest_val("runq_sz"), get_ldavg_highest_date("runq_sz"), get_ldavg_highest_time("runq_sz"));
        append_list(&report_ldavg_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  value of 'runq-sz'  is %13d (%s %s)",
            (int)get_ldavg_lowest_val("runq_sz"), get_ldavg_lowest_date("runq_sz"), get_ldavg_lowest_time("runq_sz"));
        append_list(&report_ldavg_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Spike   value of 'runq-sz'  is %13d (%s %s)",
            (int)get_ldavg_spike_val("runq_sz"), get_ldavg_spike_date("runq_sz"), get_ldavg_spike_time("runq_sz"));
        append_list(&report_ldavg_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest value of 'plist-sz' is %13d (%s %s)",
            (int)get_ldavg_highest_val("plist_sz"), get_ldavg_highest_date("plist_sz"), get_ldavg_highest_time("plist_sz"));
        append_list(&report_ldavg_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  value of 'plist-sz' is %13d (%s %s)",
            (int)get_ldavg_lowest_val("plist_sz"), get_ldavg_lowest_date("plist_sz"), get_ldavg_lowest_time("plist_sz"));
        append_list(&report_ldavg_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Spike   value of 'plist-sz' is %13d (%s %s)",
            (int)get_ldavg_spike_val("plist_sz"), get_ldavg_spike_date("plist_sz"), get_ldavg_spike_time("plist_sz"));
        append_list(&report_ldavg_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest value of 'ldavg-1'  is %13.2f (%s %s)",
            get_ldavg_highest_val("ldavg_one"), get_ldavg_highest_date("ldavg_one"), get_ldavg_highest_time("ldavg_one"));
        append_list(&report_ldavg_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  value of 'ldavg-1'  is %13.2f (%s %s)",
            get_ldavg_lowest_val("ldavg_one"), get_ldavg_lowest_date("ldavg_one"), get_ldavg_lowest_time("ldavg_one"));
        append_list(&report_ldavg_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Spike   value of 'ldavg-1'  is %13.2f (%s %s)",
            get_ldavg_spike_val("ldavg_one"), get_ldavg_spike_date("ldavg_one"), get_ldavg_spike_time("ldavg_one"));
        append_list(&report_ldavg_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest value of 'ldavg-5'  is %13.2f (%s %s)",
            get_ldavg_highest_val("ldavg_five"), get_ldavg_highest_date("ldavg_five"), get_ldavg_highest_time("ldavg_five"));
        append_list(&report_ldavg_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  value of 'ldavg-5'  is %13.2f (%s %s)",
            get_ldavg_lowest_val("ldavg_five"), get_ldavg_lowest_date("ldavg_five"), get_ldavg_lowest_time("ldavg_five"));
        append_list(&report_ldavg_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Spike   value of 'ldavg-5'  is %13.2f (%s %s)",
            get_ldavg_spike_val("ldavg_five"), get_ldavg_spike_date("ldavg_five"), get_ldavg_spike_time("ldavg_five"));
        append_list(&report_ldavg_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest value of 'ldavg-15' is %13.2f (%s %s)",
            get_ldavg_highest_val("ldavg_15"), get_ldavg_highest_date("ldavg_15"), get_ldavg_highest_time("ldavg_15"));
        append_list(&report_ldavg_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  value of 'ldavg-15' is %13.2f (%s %s)",
            get_ldavg_lowest_val("ldavg_15"), get_ldavg_lowest_date("ldavg_15"), get_ldavg_lowest_time("ldavg_15"));
        append_list(&report_ldavg_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  SPike   value of 'ldavg-15' is %13.2f (%s %s)",
            get_ldavg_spike_val("ldavg_15"), get_ldavg_spike_date("ldavg_15"), get_ldavg_spike_time("ldavg_15"));
        append_list(&report_ldavg_obj, str_tmp);
        /* averages */
        append_list(&report_ldavg_obj, "" );
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest Average value of 'runq-sz'  is %13d (%s)",
            (int)get_ldavg_avg_highest_val("runq_sz"), get_ldavg_avg_highest_date("runq_sz"));
        append_list(&report_ldavg_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  Average value of 'runq-sz'  is %13d (%s)",
            (int)get_ldavg_avg_lowest_val("runq_sz"), get_ldavg_avg_lowest_date("runq_sz"));
        append_list(&report_ldavg_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest Average value of 'plist-sz' is %13d (%s)",
            (int)get_ldavg_avg_highest_val("plist_sz"), get_ldavg_avg_highest_date("plist_sz"));
        append_list(&report_ldavg_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  Average value of 'plist-sz' is %13d (%s)",
            (int)get_ldavg_avg_lowest_val("plist_sz"), get_ldavg_avg_lowest_date("plist_sz"));
        append_list(&report_ldavg_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest Average value of 'ldavg-1'  is %13.2f (%s)",
            get_ldavg_avg_highest_val("ldavg_one"), get_ldavg_avg_highest_date("ldavg_one"));
        append_list(&report_ldavg_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  Average value of 'ldavg-1'  is %13.2f (%s)",
            get_ldavg_avg_lowest_val("ldavg_one"), get_ldavg_avg_lowest_date("ldavg_one"));
        append_list(&report_ldavg_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest Average value of 'ldavg-5'  is %13.2f (%s)",
            get_ldavg_avg_highest_val("ldavg_five"), get_ldavg_avg_highest_date("ldavg_five"));
        append_list(&report_ldavg_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  Average value of 'ldavg-5'  is %13.2f (%s)",
            get_ldavg_avg_lowest_val("ldavg_five"), get_ldavg_avg_lowest_date("ldavg_five"));
        append_list(&report_ldavg_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest Average value of 'ldavg-15' is %13.2f (%s)",
            get_ldavg_avg_highest_val("ldavg_15"), get_ldavg_avg_highest_date("ldavg_15"));
        append_list(&report_ldavg_obj, str_tmp);
        snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  Average value of 'ldavg-15' is %13.2f (%s)",
            get_ldavg_avg_lowest_val("ldavg_15"), get_ldavg_avg_lowest_date("ldavg_15"));
        append_list(&report_ldavg_obj, str_tmp);
        /* end averages */

        append_list (&report_ldavg_obj, "\n-- Report spikes for each file of queue length and load averages --\n");
        for (j = 0; j < files_n; j++) {
            /* set for declaring file no in case -O option is set */
            char str_ldavg_tmp[13] = "----file no.";
            char str_num[50] = {'\0'};
            snprintf(str_num, MAX_INPUT, "%s%d", str_ldavg_tmp, j + 1);
            append_list(&report_ldavg_spike_obj, str_num );
            /* end -- set for declaring file no in case -O option is set */

            snprintf(str_tmp, MAX_LINE_LENGTH, "  Spike   value of 'runq-sz'  is %13d (%s %s)",
                (int)get_ldavg_spike_val_each_file(j, "runq_sz", "spike"),
                    get_ldavg_spike_date_each_file(j, "runq_sz", "spike"), get_ldavg_spike_time_each_file(j, "runq_sz", "spike"));
            append_list(&report_ldavg_spike_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Spike   value of 'plist-sz' is %13d (%s %s)",
                (int)get_ldavg_spike_val_each_file(j, "plist_sz", "spike"),
                    get_ldavg_spike_date_each_file(j, "plist_sz", "spike"), get_ldavg_spike_time_each_file(j, "plist_sz", "spike"));
            append_list(&report_ldavg_spike_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Spike   value of 'ldavg-1'  is %13.2f (%s %s)",
                get_ldavg_spike_val_each_file(j, "ldavg_one", "spike"),
                    get_ldavg_spike_date_each_file(j, "ldavg_one", "spike"), get_ldavg_spike_time_each_file(j, "ldavg_one", "spike"));
            append_list(&report_ldavg_spike_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Spike   value of 'ldavg-5'  is %13.2f (%s %s)",
                get_ldavg_spike_val_each_file(j, "ldavg_five", "spike"),
                    get_ldavg_spike_date_each_file(j, "ldavg_five", "spike"), get_ldavg_spike_time_each_file(j, "ldavg_five", "spike"));
            append_list(&report_ldavg_spike_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  SPike   value of 'ldavg-15' is %13.2f (%s %s)",
                get_ldavg_spike_val_each_file(j, "ldavg_15", "spike"),
                    get_ldavg_spike_date_each_file(j, "ldavg_15", "spike"), get_ldavg_spike_time_each_file(j, "ldavg_15", "spike"));
            append_list(&report_ldavg_spike_obj, str_tmp);
            append_list(&report_ldavg_spike_obj, "");

            snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest value of 'runq-sz'  is %13d (%s %s)",
                (int)get_ldavg_spike_val_each_file(j, "runq_sz", "highest"),
                    get_ldavg_spike_date_each_file(j, "runq_sz", "highest"), get_ldavg_spike_time_each_file(j, "runq_sz", "highest"));
            append_list(&report_ldavg_spike_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest value of 'plist-sz' is %13d (%s %s)",
                (int)get_ldavg_spike_val_each_file(j, "plist_sz", "highest"),
                    get_ldavg_spike_date_each_file(j, "plist_sz", "highest"), get_ldavg_spike_time_each_file(j, "plist_sz", "highest"));
            append_list(&report_ldavg_spike_obj, str_tmp );
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest value of 'ldavg-1'  is %13.2f (%s %s)",
                get_ldavg_spike_val_each_file(j, "ldavg_one", "highest"),
                    get_ldavg_spike_date_each_file(j, "ldavg_one", "highest"), get_ldavg_spike_time_each_file(j, "ldavg_one", "highest"));
            append_list(&report_ldavg_spike_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest value of 'ldavg-5'  is %13.2f (%s %s)",
                get_ldavg_spike_val_each_file(j, "ldavg_five", "highest"),
                    get_ldavg_spike_date_each_file(j, "ldavg_five", "highest"), get_ldavg_spike_time_each_file(j, "ldavg_five", "highest"));
            append_list(&report_ldavg_spike_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest value of 'ldavg-15' is %13.2f (%s %s)",
                get_ldavg_spike_val_each_file(j, "ldavg_15", "highest"),
                    get_ldavg_spike_date_each_file(j, "ldavg_15", "highest"), get_ldavg_spike_time_each_file(j, "ldavg_15", "highest"));
            append_list(&report_ldavg_spike_obj, str_tmp);

            append_list(&report_ldavg_spike_obj, "");

            snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  value of 'runq-sz'  is %13d (%s %s)",
                (int)get_ldavg_spike_val_each_file(j, "runq_sz", "lowest"),
                    get_ldavg_spike_date_each_file(j, "runq_sz", "lowest"), get_ldavg_spike_time_each_file(j, "runq_sz", "lowest"));
            append_list(&report_ldavg_spike_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  value of 'plist-sz' is %13d (%s %s)",
                (int)get_ldavg_spike_val_each_file(j, "plist_sz", "lowest"),
                    get_ldavg_spike_date_each_file(j, "plist_sz", "lowest"), get_ldavg_spike_time_each_file(j, "plist_sz", "lowest"));
            append_list(&report_ldavg_spike_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  value of 'ldavg-1'  is %13.2f (%s %s)",
                get_ldavg_spike_val_each_file(j, "ldavg_one", "lowest"),
                    get_ldavg_spike_date_each_file(j, "ldavg_one", "lowest"), get_ldavg_spike_time_each_file(j, "ldavg_one", "lowest"));
            append_list(&report_ldavg_spike_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  value of 'ldavg-5'  is %13.2f (%s %s)",
                get_ldavg_spike_val_each_file(j, "ldavg_five", "lowest"),
                    get_ldavg_spike_date_each_file(j, "ldavg_five", "lowest"), get_ldavg_spike_time_each_file(j, "ldavg_five", "lowest"));
            append_list(&report_ldavg_spike_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  value of 'ldavg-15' is %13.2f (%s %s)",
                get_ldavg_spike_val_each_file(j, "ldavg_15", "lowest"),
                    get_ldavg_spike_date_each_file(j, "ldavg_15", "lowest"), get_ldavg_spike_time_each_file(j, "ldavg_15", "lowest"));
            append_list(&report_ldavg_spike_obj, str_tmp);
            /* for time-span option */
            if (time_span != NULL) {
                append_list(&report_ldavg_time_span_spike_obj, str_num);
                snprintf(str_tmp, MAX_LINE_LENGTH, " %s Spike   value of 'runq-sz'  is %13d (%s %s)", time_span,
                    (int)get_ldavg_time_span_spike_val_each_file(j, "runq_sz", "spike"),
                        get_ldavg_time_span_spike_date_each_file(j, "runq_sz", "spike"),
                            get_ldavg_time_span_spike_time_each_file(j, "runq_sz", "spike"));
                append_list(&report_ldavg_time_span_spike_obj, str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, " %s Spike   value of 'plist-sz' is %13d (%s %s)", time_span,
                    (int)get_ldavg_time_span_spike_val_each_file(j, "plist_sz", "spike"),
                        get_ldavg_time_span_spike_date_each_file(j, "plist_sz", "spike"),
                            get_ldavg_time_span_spike_time_each_file(j, "plist_sz", "spike"));
                append_list(&report_ldavg_time_span_spike_obj, str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, " %s Spike   value of 'ldavg-1'  is %13.2f (%s %s)", time_span,
                    get_ldavg_time_span_spike_val_each_file(j, "ldavg_one", "spike"),
                        get_ldavg_time_span_spike_date_each_file(j, "ldavg_one", "spike"),
                            get_ldavg_time_span_spike_time_each_file(j, "ldavg_one", "spike"));
                append_list(&report_ldavg_time_span_spike_obj, str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, " %s Spike   value of 'ldavg-5'  is %13.2f (%s %s)", time_span,
                    get_ldavg_time_span_spike_val_each_file(j, "ldavg_five", "spike"),
                        get_ldavg_time_span_spike_date_each_file(j, "ldavg_five", "spike"),
                            get_ldavg_time_span_spike_time_each_file(j, "ldavg_five", "spike"));
                append_list(&report_ldavg_time_span_spike_obj, str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, " %s SPike   value of 'ldavg-15' is %13.2f (%s %s)", time_span,
                    get_ldavg_time_span_spike_val_each_file(j, "ldavg_15", "spike"),
                        get_ldavg_time_span_spike_date_each_file(j, "ldavg_15", "spike"),
                            get_ldavg_time_span_spike_time_each_file(j, "ldavg_15", "spike"));
                append_list(&report_ldavg_time_span_spike_obj, str_tmp);
                append_list(&report_ldavg_time_span_spike_obj, "");

                snprintf(str_tmp, MAX_LINE_LENGTH, " %s Highest value of 'runq-sz'  is %13d (%s %s)", time_span,
                    (int)get_ldavg_time_span_spike_val_each_file(j, "runq_sz", "highest"),
                        get_ldavg_time_span_spike_date_each_file(j, "runq_sz", "highest"),
                            get_ldavg_time_span_spike_time_each_file(j, "runq_sz", "highest"));
                append_list(&report_ldavg_time_span_spike_obj, str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, " %s Highest value of 'plist-sz' is %13d (%s %s)", time_span,
                    (int)get_ldavg_time_span_spike_val_each_file(j, "plist_sz", "highest"),
                        get_ldavg_time_span_spike_date_each_file(j, "plist_sz", "highest"),
                            get_ldavg_time_span_spike_time_each_file(j, "plist_sz", "highest"));
                append_list(&report_ldavg_time_span_spike_obj, str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, " %s Highest value of 'ldavg-1'  is %13.2f (%s %s)", time_span,
                    get_ldavg_time_span_spike_val_each_file(j, "ldavg_one", "highest"),
                        get_ldavg_time_span_spike_date_each_file(j, "ldavg_one", "highest"),
                            get_ldavg_time_span_spike_time_each_file(j, "ldavg_one", "highest"));
                append_list(&report_ldavg_time_span_spike_obj, str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, " %s Highest value of 'ldavg-5'  is %13.2f (%s %s)", time_span,
                    get_ldavg_time_span_spike_val_each_file(j, "ldavg_five", "highest"),
                        get_ldavg_time_span_spike_date_each_file(j, "ldavg_five", "highest"),
                            get_ldavg_time_span_spike_time_each_file(j, "ldavg_five", "highest"));
                append_list(&report_ldavg_time_span_spike_obj, str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, " %s Highest value of 'ldavg-15' is %13.2f (%s %s)", time_span,
                    get_ldavg_time_span_spike_val_each_file(j, "ldavg_15", "highest"),
                        get_ldavg_time_span_spike_date_each_file(j, "ldavg_15", "highest"),
                            get_ldavg_time_span_spike_time_each_file(j, "ldavg_15", "highest"));
                append_list(&report_ldavg_time_span_spike_obj, str_tmp);

                append_list(&report_ldavg_time_span_spike_obj, "");

                snprintf(str_tmp, MAX_LINE_LENGTH, " %s Lowest  value of 'runq-sz'  is %13d (%s %s)", time_span,
                    (int)get_ldavg_time_span_spike_val_each_file(j, "runq_sz", "lowest"),
                        get_ldavg_time_span_spike_date_each_file(j, "runq_sz", "lowest"),
                            get_ldavg_time_span_spike_time_each_file(j, "runq_sz", "lowest"));
                append_list ( &report_ldavg_time_span_spike_obj, str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, " %s Lowest  value of 'plist-sz' is %13d (%s %s)", time_span,
                    (int)get_ldavg_time_span_spike_val_each_file(j, "plist_sz", "lowest"),
                        get_ldavg_time_span_spike_date_each_file(j, "plist_sz", "lowest"),
                            get_ldavg_time_span_spike_time_each_file(j, "plist_sz", "lowest"));
                append_list(&report_ldavg_time_span_spike_obj, str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, " %s Lowest  value of 'ldavg-1'  is %13.2f (%s %s)", time_span,
                    get_ldavg_time_span_spike_val_each_file(j, "ldavg_one", "lowest"),
                        get_ldavg_time_span_spike_date_each_file(j, "ldavg_one", "lowest"),
                            get_ldavg_time_span_spike_time_each_file(j, "ldavg_one", "lowest"));
                append_list(&report_ldavg_time_span_spike_obj, str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, " %s Lowest  value of 'ldavg-5'  is %13.2f (%s %s)", time_span,
                    get_ldavg_time_span_spike_val_each_file(j, "ldavg_five", "lowest"),
                        get_ldavg_time_span_spike_date_each_file(j, "ldavg_five", "lowest"),
                            get_ldavg_time_span_spike_time_each_file(j, "ldavg_five", "lowest"));
                append_list(&report_ldavg_time_span_spike_obj, str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, " %s Lowest  value of 'ldavg-15' is %13.2f (%s %s)", time_span,
                    get_ldavg_time_span_spike_val_each_file(j, "ldavg_15", "lowest"),
                        get_ldavg_time_span_spike_date_each_file(j, "ldavg_15", "lowest"),
                            get_ldavg_time_span_spike_time_each_file(j, "ldavg_15", "lowest"));
                append_list(&report_ldavg_time_span_spike_obj, str_tmp);
            }
        }

        append_list(&report_ldavg_explanation_obj, "--------");
        append_list(&report_ldavg_explanation_obj, "  If devided by /proc/cpuinfo|grep 'cores' value of 'runq-sz' is over 2, the box is cpu bound.");
        append_list(&report_ldavg_explanation_obj, "  If that is the case, you might need more cpu power to do the task.");
        append_list(&report_ldavg_explanation_obj, "  If 'plist-sz' is higher than 10,000 for example, there are waits.");
        append_list(&report_ldavg_explanation_obj, "  If 'ldavg-<minites>' exceeds number of cores, cpu load is high.");
        append_list(&report_ldavg_explanation_obj, "  Check number of cores with, $cat /proc/cpuinfo | grep 'cpu cores'.");
        append_list(&report_ldavg_explanation_obj, "  Check number of physical cpu with, $cat /proc/cpuinfo | grep 'physical id'.");
        append_list(&report_ldavg_explanation_obj, "  Check if hyperthreading is enabled with, $cat /proc/cpuinfo | grep 'siblings'.");
        append_list(&report_ldavg_explanation_obj, "  Divide the result of above command and if it is not same as core, hyperthreading is enabled.");
        append_list(&report_ldavg_explanation_obj, "  So, if you have 8 cores, highest value is 800.00 and above 60% of this value would be a trouble.");
 
        /* block_device */ 

        append_list(&report_block_device_obj, " \n-- Report activity for each block device --\n");
        for (i = 1; i <= MAX_BLOCK_DEVICE_NUMBERS; i++) {
            if (i >= get_block_device_numbers())
                break;
            char ss[20];
            memset(ss, 0, sizeof(ss));
            int dev_nam_l = 0;
            dev_nam_l = (int)strlen(get_block_device_names(i));
            if (dev_nam_l == 2)
                strncpy(ss, "          ", 11);
            if (dev_nam_l == 3)
                strncpy(ss, "         ", 10);
            if (dev_nam_l == 4)
                strncpy(ss, "        ", 9);
            if (dev_nam_l == 5)
                strncpy(ss, "       ", 8);
            if (dev_nam_l == 6)
                strncpy(ss, "      ", 7);
            if (dev_nam_l == 7)
                strncpy(ss, "     ", 6);
            if (dev_nam_l == 8)
                strncpy(ss, "    ", 5);
            if (dev_nam_l == 8)
                strncpy(ss, "   ", 4);
            if (dev_nam_l == 9)
                strncpy(ss, "  ", 3);
            if (dev_nam_l == 10)
                strncpy(ss, " ", 2);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest value of 'areq-sz' of %s is%s%13.2f (%s %s)",
                get_block_device_names(i), ss, get_block_device_highest_val(i, "areqsz"),
                    get_block_device_highest_date(i, "areqsz"), get_block_device_highest_time(i, "areqsz"));
            append_list(&report_block_device_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  value of 'areq-sz' of %s is%s%13.2f (%s %s)",
                get_block_device_names(i), ss, get_block_device_lowest_val(i, "areqsz"),
                    get_block_device_lowest_date(i, "areqsz"), get_block_device_lowest_time(i, "areqsz"));
            append_list(&report_block_device_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Spike   value of 'areq-sz' of %s is%s%13.2f (%s %s)",
                get_block_device_names(i), ss, get_block_device_spike_val(i, "areqsz"),
                    get_block_device_spike_date(i, "areqsz"), get_block_device_spike_time(i, "areqsz"));
            append_list(&report_block_device_obj, str_tmp );
            append_list(&report_block_device_obj, "" );
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest value of '%%util'   of %s is%s%13.2f (%s %s)",
                get_block_device_names(i), ss, get_block_device_highest_val(i, "util"),
                    get_block_device_highest_date(i, "util"), get_block_device_highest_time(i, "util"));
            append_list(&report_block_device_obj, str_tmp );
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  value of '%%util'   of %s is%s%13.2f (%s %s)",
                get_block_device_names(i), ss, get_block_device_lowest_val(i, "util"),
                    get_block_device_lowest_date(i, "util"), get_block_device_lowest_time(i, "util"));
            append_list(&report_block_device_obj, str_tmp );
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Spike   value of '%%util'   of %s is%s%13.2f (%s %s)",
                get_block_device_names(i), ss, get_block_device_spike_val(i, "util"),
                    get_block_device_spike_date(i, "util"), get_block_device_spike_time(i, "util"));
            append_list(&report_block_device_obj, str_tmp);
            append_list(&report_block_device_obj, "----");
            /* averages */
            append_list(&report_ldavg_obj, "");
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest Average value of 'areq-sz' of %s is%s%13.2f (%s)",
                get_block_device_names(i), ss, get_block_device_avg_highest_val(i, "areqsz"),
                    get_block_device_avg_highest_date(i, "areqsz"));
            append_list(&report_block_device_obj, str_tmp );
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  Average value of 'areq-sz' of %s is%s%13.2f (%s)",
                get_block_device_names(i), ss, get_block_device_avg_lowest_val(i, "areqsz"),
                    get_block_device_avg_lowest_date(i, "areqsz"));
            append_list(&report_block_device_obj, str_tmp);
            append_list(&report_block_device_obj, "" );
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest Average value of '%%util'   of %s is%s%13.2f (%s)",
                get_block_device_names(i), ss, get_block_device_avg_highest_val(i, "util"),
                    get_block_device_avg_highest_date(i, "util"));
            append_list(&report_block_device_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  Average value of '%%util'   of %s is%s%13.2f (%s)",
                get_block_device_names(i), ss, get_block_device_avg_lowest_val(i, "util"),
                    get_block_device_avg_lowest_date(i, "util"));
            append_list(&report_block_device_obj, str_tmp);
            append_list(&report_block_device_obj, "----");
            /* end averages */
        }

        append_list(&report_block_device_obj, "\n-- Report spikes for each file of activity for each block device--\n");
        for (i = 1; i <= MAX_BLOCK_DEVICE_NUMBERS; i++) {
            if (i >= get_block_device_numbers())
                break;
            char ss[20];
            memset(ss, 0, sizeof(ss));
            int dev_nam_l = 0;
            dev_nam_l = (int)strlen(get_block_device_names(i));
            if (dev_nam_l == 2)
                strncpy (ss, "          ", 11);
            if (dev_nam_l == 3)
                strncpy (ss, "         ", 10);
            if (dev_nam_l == 4)
                strncpy (ss, "        ", 9);
            if (dev_nam_l == 5)
                strncpy (ss, "       ", 8);
            if (dev_nam_l == 6)
                strncpy (ss, "      ", 7);
            if (dev_nam_l == 7)
                strncpy (ss, "     ", 6);
            if (dev_nam_l == 8)
                strncpy (ss, "    ", 5);
            if (dev_nam_l == 8)
                strncpy (ss, "   ", 4);
            if (dev_nam_l == 9)
                strncpy (ss, "  ", 3);
            if (dev_nam_l == 10)
                strncpy (ss, " ", 2);

            for (j = 0; j < files_n; j++)
            {

                /* set for declaring file no in case -O option is set */
                char str_block_device[10] = "--DEVICE ";
                char str_block_device_tmp[13] = " -- file no.";
                char str_num[150] = {'\0'};
                snprintf(str_num, MAX_INPUT, "%s%s%s%d", str_block_device, get_block_device_names(i), str_block_device_tmp, j + 1);
                append_list(&report_block_device_spike_obj[i], str_num);
                /* end -- set for declaring file no in case -O option is set */

                snprintf(str_tmp, MAX_LINE_LENGTH, "  Spike   value of 'areq-sz' of %s is%s%13.2f (%s %s)",
                    get_block_device_names(i), ss, get_block_device_spike_val_each_file(j, i, "areqsz", "spike"),
                        get_block_device_spike_date_each_file(j, i, "areqsz", "spike"),
                            get_block_device_spike_time_each_file(j, i, "areqsz", "spike"));
                append_list(&report_block_device_spike_obj[i], str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, "  Spike   value of '%%util'   of %s is%s%13.2f (%s %s)",
                    get_block_device_names(i), ss, get_block_device_spike_val_each_file(j, i, "util", "spike"),
                        get_block_device_spike_date_each_file(j, i, "util", "spike"),
                            get_block_device_spike_time_each_file(j, i, "util", "spike"));
                append_list(&report_block_device_spike_obj[i], str_tmp);
                append_list(&report_block_device_spike_obj[i], "");

                snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest value of 'areq-sz' of %s is%s%13.2f (%s %s)",
                    get_block_device_names(i), ss, get_block_device_spike_val_each_file(j, i, "areqsz", "highest"),
                        get_block_device_spike_date_each_file(j, i, "areqsz", "highest"),
                            get_block_device_spike_time_each_file(j, i, "areqsz", "highest"));
                append_list(&report_block_device_spike_obj[i], str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest value of '%%util'   of %s is%s%13.2f (%s %s)",
                    get_block_device_names(i), ss, get_block_device_spike_val_each_file(j, i, "util", "highest"),
                        get_block_device_spike_date_each_file(j, i, "util", "highest"),
                            get_block_device_spike_time_each_file(j, i, "util", "highest"));
                append_list(&report_block_device_spike_obj[i], str_tmp);

                append_list(&report_block_device_spike_obj[i], "");

                snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  value of 'areq-sz' of %s is%s%13.2f (%s %s)",
                    get_block_device_names(i), ss, get_block_device_spike_val_each_file(j, i, "areqsz", "lowest"),
                        get_block_device_spike_date_each_file(j, i, "areqsz", "lowest"),
                            get_block_device_spike_time_each_file(j, i, "areqsz", "lowest"));
                append_list(&report_block_device_spike_obj[i], str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  value of '%%util'   of %s is%s%13.2f (%s %s)",
                    get_block_device_names(i), ss, get_block_device_spike_val_each_file(j, i, "util", "lowest"),
                        get_block_device_spike_date_each_file(j, i, "util", "lowest"),
                            get_block_device_spike_time_each_file(j, i, "util", "lowest"));
                append_list(&report_block_device_spike_obj[i], str_tmp);
            }
        }

        append_list(&report_block_device_explanation_obj, "--------");
        append_list(&report_block_device_explanation_obj, " 'areq-sz' is the average size (in kilobytes) of the I/O requests that were issued to the device.");
        append_list(&report_block_device_explanation_obj, " Note: In previous versions, this field was known as avgrq-sz and was expressed in sectors.");
        append_list(&report_block_device_explanation_obj, " '%util'is percentage of elapsed time during which I/O requests were issued to the device ");
        append_list(&report_block_device_explanation_obj, " (bandwidth utilization for the device). Device saturation occurs when this value " );
        append_list(&report_block_device_explanation_obj, " is close to 100% for devices serving requests serially. But for devices serving requests in");
        append_list(&report_block_device_explanation_obj, " parallel, such as RAID arrays and modern SSDs, this number does not reflect their performance limits.");

        /* network */

        append_list(&report_network_obj, " \n-- Report network statistics --\n");

        for (i = 1; i <= MAX_NETWORK_DEVICE_NUMBERS; i++) {
            if (i >= get_network_device_numbers())
                break;
            char ss[20];
            memset(ss, 0, sizeof(ss));
            int dev_nam_l = 0;
            dev_nam_l = (int)strlen(get_network_device_names(i));
            if (dev_nam_l == 2)
                strncpy (ss, "          ", 11);
            if (dev_nam_l == 3)
                strncpy (ss, "         ", 10);
            if (dev_nam_l == 4)
                strncpy (ss, "        ", 9);
            if (dev_nam_l == 5)
                strncpy (ss, "       ", 8);
            if (dev_nam_l == 6)
                strncpy (ss, "      ", 7);
            if (dev_nam_l == 7)
                strncpy (ss, "     ", 6);
            if (dev_nam_l == 8)
                strncpy (ss, "    ", 5);
            if (dev_nam_l == 8)
                strncpy (ss, "   ", 4);
            if (dev_nam_l == 9)
                strncpy (ss, "  ", 3);
            if (dev_nam_l == 10)
                strncpy (ss, " ", 2);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest value of 'rxpck/s' of %s is%s%13.2f (%s %s)",
                get_network_device_names(i), ss, get_network_highest_val(i, "rxpck"),
                    get_network_highest_date(i, "rxpck"), get_network_highest_time(i, "rxpck"));
            append_list(&report_network_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  value of 'rxpck/s' of %s is%s%13.2f (%s %s)",
                get_network_device_names(i), ss, get_network_lowest_val(i, "rxpck"),
                    get_network_lowest_date(i, "rxpck"), get_network_lowest_time(i, "rxpck"));
            append_list ( &report_network_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Spike   value of 'rxpck/s' of %s is%s%13.2f (%s %s)",
                get_network_device_names(i), ss, get_network_spike_val(i, "rxpck"),
                    get_network_spike_date(i, "rxpck"), get_network_spike_time(i, "rxpck"));
            append_list(&report_network_obj, "" );
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest value of 'txpck/s' of %s is%s%13.2f (%s %s)",
                get_network_device_names(i), ss, get_network_highest_val(i, "txpck"),
                    get_network_highest_date(i, "txpck"), get_network_highest_time(i, "txpck"));
            append_list(&report_network_obj, str_tmp );
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  value of 'txpck/s' of %s is%s%13.2f (%s %s)",
                get_network_device_names(i), ss, get_network_lowest_val(i, "txpck"),
                    get_network_lowest_date(i, "txpck"), get_network_lowest_time(i, "txpck"));
            append_list(&report_network_obj, str_tmp );
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Spike   value of 'txpck/s' of %s is%s%13.2f (%s %s)",
                get_network_device_names(i), ss, get_network_spike_val(i, "txpck"),
                    get_network_spike_date(i, "txpck"), get_network_spike_time(i, "txpck"));
            append_list(&report_network_obj, str_tmp);
            append_list(&report_network_obj, "" );
            snprintf ( str_tmp, MAX_LINE_LENGTH, "  Highest value of 'rxkB/s'  of %s is%s%13.2f (%s %s)",
                get_network_device_names(i), ss, get_network_highest_val(i, "rxkb"),
                    get_network_highest_date(i, "rxkb"), get_network_highest_time(i, "rxkb"));
            append_list(&report_network_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  value of 'rxkB/s'  of %s is%s%13.2f (%s %s)",
                get_network_device_names(i), ss, get_network_lowest_val(i, "rxkb"),
                    get_network_lowest_date(i, "rxkb"), get_network_lowest_time(i, "rxkb"));
            append_list(&report_network_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Spike   value of 'rxkB/s'  of %s is%s%13.2f (%s %s)",
                get_network_device_names(i), ss, get_network_spike_val(i, "rxkb"),
                    get_network_spike_date(i, "rxkb"), get_network_spike_time(i, "rxkb"));
            append_list(&report_network_obj, str_tmp);
            append_list(&report_network_obj, "" );
            snprintf ( str_tmp, MAX_LINE_LENGTH, "  Highest value of 'txkB/s'  of %s is%s%13.2f (%s %s)",
                get_network_device_names(i), ss, get_network_highest_val(i, "txkb"),
                    get_network_highest_date(i, "txkb"), get_network_highest_time(i, "txkb"));
            append_list(&report_network_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  value of 'txkB/s'  of %s is%s%13.2f (%s %s)",
                get_network_device_names(i), ss, get_network_lowest_val(i, "txkb"),
                    get_network_lowest_date(i, "txkb"), get_network_lowest_time(i, "txkb"));
            append_list(&report_network_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Spike   value of 'txkB/s'  of %s is%s%13.2f (%s %s)",
                get_network_device_names(i), ss, get_network_spike_val(i, "txkb"),
                    get_network_spike_date(i, "txkb"), get_network_spike_time(i, "txkb"));
            append_list(&report_network_obj, str_tmp);
            append_list(&report_network_obj, "----");
            /* averages */
            append_list(&report_network_obj, "");
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest Average value of 'rxpck/s' of %s is%s%13.2f (%s)",
                get_network_device_names(i), ss, get_network_avg_highest_val(i, "rxpck"),
                    get_network_avg_highest_date(i, "rxpck"));
            append_list(&report_network_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  Average value of 'rxpck/s' of %s is%s%13.2f (%s)",
                get_network_device_names(i), ss, get_network_avg_lowest_val(i, "rxpck"),
                    get_network_avg_lowest_date(i, "rxpck"));
            append_list(&report_network_obj, str_tmp);
            append_list(&report_network_obj, "");
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest Average value of 'txpck/s' of %s is%s%13.2f (%s)",
                get_network_device_names(i), ss, get_network_avg_highest_val(i, "txpck"),
                    get_network_avg_highest_date(i, "txpck"));
            append_list(&report_network_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  Average value of 'txpck/s' of %s is%s%13.2f (%s)",
                get_network_device_names(i), ss, get_network_avg_lowest_val(i, "txpck"),
                    get_network_avg_lowest_date(i, "txpck"));
            append_list(&report_network_obj, str_tmp);
            append_list(&report_network_obj, "");
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest Average value of 'rxkB/s'  of %s is%s%13.2f (%s)",
                get_network_device_names(i), ss, get_network_avg_highest_val(i, "rxkb"),
                    get_network_avg_highest_date(i, "rxkb"));
            append_list(&report_network_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  Average value of 'rxkB/s'  of %s is%s%13.2f (%s)",
                get_network_device_names(i), ss, get_network_avg_lowest_val(i, "rxkb"),
                    get_network_avg_lowest_date(i, "rxkb"));
            append_list(&report_network_obj, str_tmp);
            append_list(&report_network_obj, "");
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest Average value of 'txkB/s'  of %s is%s%13.2f (%s)",
                get_network_device_names(i), ss, get_network_avg_highest_val(i, "txkb"),
                    get_network_avg_highest_date(i, "txkb"));
            append_list(&report_network_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  Average value of 'txkB/s'  of %s is%s%13.2f (%s)",
                get_network_device_names(i), ss, get_network_avg_lowest_val(i, "txkb"),
                    get_network_avg_lowest_date(i, "txkb"));
            append_list(&report_network_obj, str_tmp);
            append_list(&report_network_obj, "----");
            /* end averages */
        }

        /* network spike */

        append_list(&report_network_obj, "\n-- Report spikes for each file of network statistics --\n");
        for (i = 1; i <= MAX_NETWORK_DEVICE_NUMBERS; i++) {
            if (i >= get_network_device_numbers())
                break;
            char ss[20];
            memset(ss, 0, sizeof(ss));
            int dev_nam_l = 0;
            dev_nam_l = (int)strlen(get_network_device_names(i));
            if (dev_nam_l == 2)
                strncpy(ss, "          ", 11);
            if (dev_nam_l == 3)
                strncpy(ss, "         ", 10);
            if (dev_nam_l == 4)
                strncpy(ss, "        ", 9);
            if (dev_nam_l == 5)
                strncpy(ss, "       ", 8);
            if (dev_nam_l == 6)
                strncpy(ss, "      ", 7);
            if (dev_nam_l == 7)
                strncpy(ss, "     ", 6);
            if (dev_nam_l == 8)
                strncpy(ss, "    ", 5);
            if (dev_nam_l == 8)
                strncpy(ss, "   ", 4);
            if (dev_nam_l == 9)
                strncpy(ss, "  ", 3);
            if (dev_nam_l == 10)
                strncpy(ss, " ", 2);

            for (j = 0; j < files_n; j++) {
                /* set for declaring file no in case -O option is set */
                char str_network_device[10] = "--DEVICE ";
                char str_network_device_tmp[13] = " -- file no.";
                char str_num[150] = {'\0'};
                snprintf(str_num, MAX_INPUT, "%s%s%s%d", str_network_device, get_network_device_names(i), str_network_device_tmp, j + 1);
                append_list(&report_network_spike_obj[i], str_num);
                /* end -- set for declaring file no in case -O option is set */

                snprintf(str_tmp, MAX_LINE_LENGTH, "  Spike   value of 'rxpck/s' of %s is%s%13.2f (%s %s)",
                    get_network_device_names(i), ss, get_network_spike_val_each_file(j, i, "rxpck", "spike"),
                        get_network_spike_date_each_file(j, i, "rxpck", "spike"),
                            get_network_spike_time_each_file(j, i, "rxpck", "spike"));
                append_list(&report_network_spike_obj[i], str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, "  Spike   value of 'txpck/s' of %s is%s%13.2f (%s %s)",
                    get_network_device_names(i), ss, get_network_spike_val_each_file(j, i, "txpck", "spike"),
                        get_network_spike_date_each_file(j, i, "txpck", "spike"),
                            get_network_spike_time_each_file(j, i, "txpck", "spike"));
                append_list(&report_network_spike_obj[i], str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, "  Spike   value of 'rxkB/s'  of %s is%s%13.2f (%s %s)",
                    get_network_device_names(i), ss, get_network_spike_val_each_file(j, i, "rxkb", "spike"),
                        get_network_spike_date_each_file(j, i, "rxkb", "spike"),
                            get_network_spike_time_each_file(j, i, "rxkb", "spike"));
                append_list(&report_network_spike_obj[i], str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, "  Spike   value of 'txkB/s'  of %s is%s%13.2f (%s %s)",
                    get_network_device_names(i), ss, get_network_spike_val_each_file(j, i, "txkb", "spike"),
                        get_network_spike_date_each_file(j, i, "txkb", "spike"),
                            get_network_spike_time_each_file(j, i, "txkb", "spike"));
                append_list(&report_network_spike_obj[i], str_tmp);
                append_list(&report_network_spike_obj[i], "");

                snprintf ( str_tmp, MAX_LINE_LENGTH, "  Highest value of 'rxpck/s' of %s is%s%13.2f (%s %s)",
                    get_network_device_names(i), ss, get_network_spike_val_each_file(j, i, "rxpck", "highest"),
                        get_network_spike_date_each_file(j, i, "rxpck", "highest"),
                            get_network_spike_time_each_file(j, i, "rxpck", "highest"));
                append_list(&report_network_spike_obj[i], str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest value of 'txpck/s' of %s is%s%13.2f (%s %s)",
                    get_network_device_names(i), ss, get_network_spike_val_each_file(j, i, "txpck", "highest"),
                        get_network_spike_date_each_file(j, i, "txpck", "highest"),
                            get_network_spike_time_each_file(j, i, "txpck", "highest"));
                append_list(&report_network_spike_obj[i], str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest value of 'rxkB/s'  of %s is%s%13.2f (%s %s)",
                    get_network_device_names(i), ss, get_network_spike_val_each_file(j, i, "rxkb", "highest"),
                        get_network_spike_date_each_file(j, i, "rxkb", "highest"),
                            get_network_spike_time_each_file(j, i, "rxkb", "highest"));
                append_list(&report_network_spike_obj[i], str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest value of 'txkB/s'  of %s is%s%13.2f (%s %s)",
                    get_network_device_names(i), ss, get_network_spike_val_each_file(j, i, "txkb", "highest"),
                        get_network_spike_date_each_file(j, i, "txkb", "highest"),
                            get_network_spike_time_each_file(j, i, "txkb", "highest"));
                append_list(&report_network_spike_obj[i], str_tmp);

                append_list(&report_network_spike_obj[i], "");

                snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  value of 'rxpck/s' of %s is%s%13.2f (%s %s)",
                    get_network_device_names(i), ss, get_network_spike_val_each_file(j, i, "rxpck", "lowest"),
                        get_network_spike_date_each_file(j, i, "rxpck", "lowest"),
                            get_network_spike_time_each_file(j, i, "rxpck", "lowest"));
                append_list(&report_network_spike_obj[i], str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  value of 'txpck/s' of %s is%s%13.2f (%s %s)",
                    get_network_device_names(i), ss, get_network_spike_val_each_file(j, i, "txpck", "lowest"),
                        get_network_spike_date_each_file(j, i, "txpck", "lowest"),
                            get_network_spike_time_each_file(j, i, "txpck", "lowest"));
                append_list(&report_network_spike_obj[i], str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  value of 'rxkB/s'  of %s is%s%13.2f (%s %s)",
                    get_network_device_names(i), ss, get_network_spike_val_each_file(j, i, "rxkb", "lowest"),
                        get_network_spike_date_each_file(j, i, "rxkb", "lowest"),
                            get_network_spike_time_each_file(j, i, "rxkb", "lowest"));
                append_list(&report_network_spike_obj[i], str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  value of 'txkB/s'  of %s is%s%13.2f (%s %s)",
                    get_network_device_names(i), ss, get_network_spike_val_each_file(j, i, "txkb", "lowest"),
                        get_network_spike_date_each_file(j, i, "txkb", "lowest"),
                            get_network_spike_time_each_file(j, i, "txkb", "lowest"));
                append_list(&report_network_spike_obj[i], str_tmp);
            }
        }
        append_list(&report_network_explanation_obj, "--------");
        append_list(&report_network_explanation_obj, " Check these values for the each network device.");

        /* network_error */

        append_list(&report_network_error_obj, " \n-- Report statistics on failures (errors) from the network devices --\n");
        for (i = 1; i <= MAX_NETWORK_DEVICE_NUMBERS; i++) {
            if (i >= get_network_device_numbers())
                break;
            char ss[20];
            memset(ss, 0, sizeof(ss));
            int dev_nam_l = 0;
            dev_nam_l = (int)strlen(get_network_device_names(i));
            if (dev_nam_l == 2)
                strncpy (ss, "          ", 11);
            if (dev_nam_l == 3)
                strncpy (ss, "         ", 10);
            if (dev_nam_l == 4)
                strncpy (ss, "        ", 9);
            if (dev_nam_l == 5)
                strncpy (ss, "       ", 8);
            if (dev_nam_l == 6)
                strncpy (ss, "      ", 7);
            if (dev_nam_l == 7)
                strncpy (ss, "     ", 6);
            if (dev_nam_l == 8)
                strncpy (ss, "    ", 5);
            if (dev_nam_l == 8)
                strncpy (ss, "   ", 4);
            if (dev_nam_l == 9)
                strncpy (ss, "  ", 3);
            if (dev_nam_l == 10)
               strncpy (ss, " ", 2);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest value of 'rxerr/s'  of %s is%s%13.2f (%s %s)",
                get_network_device_names(i), ss, get_network_highest_val(i, "rxerr"),
                    get_network_highest_date(i, "rxerr"), get_network_highest_time(i, "rxerr"));
            append_list(&report_network_error_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  value of 'rxerr/s'  of %s is%s%13.2f (%s %s)",
                get_network_device_names(i), ss, get_network_lowest_val(i, "rxerr"),
                    get_network_lowest_date(i, "rxerr"), get_network_lowest_time(i, "rxerr"));
            append_list(&report_network_error_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Spike   value of 'rxerr/s'  of %s is%s%13.2f (%s %s)",
                get_network_device_names(i), ss, get_network_spike_val(i, "rxerr"),
                    get_network_spike_date(i, "rxerr"), get_network_spike_time(i, "rxerr"));
            append_list(&report_network_error_obj, str_tmp);
            append_list(&report_network_error_obj, "");
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest value of 'txerr/s'  of %s is%s%13.2f (%s %s)",
                get_network_device_names(i), ss, get_network_highest_val(i, "txerr"),
                get_network_highest_date(i, "txerr"), get_network_highest_time(i, "txerr"));
            append_list(&report_network_error_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  value of 'txerr/s'  of %s is%s%13.2f (%s %s)",
                get_network_device_names(i), ss, get_network_lowest_val(i, "txerr"),
                    get_network_lowest_date(i, "txerr"), get_network_lowest_time(i, "txerr"));
            append_list(&report_network_error_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Spike   value of 'txerr/s'  of %s is%s%13.2f (%s %s)",
                get_network_device_names(i), ss, get_network_spike_val(i, "txerr"),
                    get_network_spike_date(i, "txerr"), get_network_spike_time(i, "txerr"));
            append_list(&report_network_error_obj, str_tmp);
            append_list(&report_network_error_obj, "");
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest value of 'rxdrop/s' of %s is%s%13.2f (%s %s)",
                get_network_device_names(i), ss, get_network_highest_val(i, "rxdrop"),
                    get_network_highest_date(i, "rxdrop"), get_network_highest_time(i, "rxdrop"));
            append_list(&report_network_error_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  value of 'rxdrop/s' of %s is%s%13.2f (%s %s)",
                get_network_device_names(i), ss, get_network_lowest_val ( i, "rxdrop"),
                    get_network_lowest_date(i, "rxdrop"), get_network_lowest_time(i, "rxdrop"));
            append_list(&report_network_error_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Spike   value of 'rxdrop/s' of %s is%s%13.2f (%s %s)",
                get_network_device_names(i), ss, get_network_spike_val(i, "rxdrop"),
                    get_network_spike_date(i, "rxdrop"), get_network_spike_time(i, "rxdrop"));
            append_list(&report_network_error_obj, str_tmp);
            append_list(&report_network_error_obj, "" );
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest value of 'txdrop/s' of %s is%s%13.2f (%s %s)",
                get_network_device_names(i), ss, get_network_highest_val(i, "txdrop"),
                    get_network_highest_date(i, "txdrop"), get_network_highest_time(i, "txdrop"));
            append_list(&report_network_error_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  value of 'txdrop/s' of %s is%s%13.2f (%s %s)",
                get_network_device_names(i), ss, get_network_lowest_val ( i, "txdrop"),
                    get_network_lowest_date(i, "txdrop"), get_network_lowest_time(i, "txdrop"));
            append_list(&report_network_error_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Spike   value of 'txdrop/s' of %s is%s%13.2f (%s %s)",
                get_network_device_names(i), ss, get_network_spike_val(i, "txdrop"),
                    get_network_spike_date(i, "txdrop"), get_network_spike_time(i, "txdrop"));
            append_list ( &report_network_error_obj, str_tmp);
            /* averages */
            append_list(&report_network_error_obj, "");
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest Average value of 'rxerr/s'  of %s is%s%13.2f (%s)",
                get_network_device_names(i), ss, get_network_avg_highest_val(i, "rxerr"),
                    get_network_avg_highest_date(i, "rxerr"));
            append_list(&report_network_error_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  Average value of 'rxerr/s'  of %s is%s%13.2f (%s)",
                get_network_device_names(i), ss, get_network_avg_lowest_val(i, "rxerr"),
                    get_network_avg_lowest_date(i, "rxerr"));
            append_list(&report_network_error_obj, str_tmp);
            append_list(&report_network_error_obj, "" );
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest Average value of 'txerr/s'  of %s is%s%13.2f (%s)",
                get_network_device_names(i), ss, get_network_avg_highest_val(i, "txerr"),
                    get_network_avg_highest_date(i, "txerr"));
            append_list(&report_network_error_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  Average value of 'txerr/s'  of %s is%s%13.2f (%s)",
                get_network_device_names(i), ss, get_network_avg_lowest_val(i, "txerr"),
                    get_network_avg_lowest_date(i, "txerr"));
            append_list(&report_network_error_obj, str_tmp);
            append_list(&report_network_error_obj, "" );
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest Average value of 'rxdrop/s' of %s is%s%13.2f (%s)",
                get_network_device_names(i), ss, get_network_avg_highest_val(i, "rxdrop"),
                    get_network_avg_highest_date(i, "rxdrop"));
            append_list(&report_network_error_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  Average value of 'rxdrop/s' of %s is%s%13.2f (%s)",
                get_network_device_names(i), ss, get_network_avg_lowest_val(i, "rxdrop"),
                    get_network_avg_lowest_date(i, "rxdrop"));
            append_list(&report_network_error_obj, str_tmp);
            append_list(&report_network_error_obj, "");
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest Average value of 'txdrop/s' of %s is%s%13.2f (%s)",
                get_network_device_names(i), ss, get_network_avg_highest_val(i, "txdrop"),
                    get_network_avg_highest_date(i, "txdrop"));
            append_list(&report_network_error_obj, str_tmp);
            snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  Average value of 'txdrop/s' of %s is%s%13.2f (%s)",
                get_network_device_names(i), ss, get_network_avg_lowest_val(i, "txdrop"),
                    get_network_avg_lowest_date(i, "txdrop"));
            append_list(&report_network_error_obj, str_tmp);
            append_list(&report_network_error_obj, "----");
            /* end averages */
        }

        append_list(&report_network_error_obj, "\n-- Report spikes for each file of statistics on failures (errors) from the network devices --\n" );
        for (i = 1; i <= MAX_NETWORK_DEVICE_NUMBERS; i++) {
            if (i >= get_network_device_numbers())
                break;
            char ss[20];
            memset(ss, 0, sizeof(ss));
            int dev_nam_l = 0;
            dev_nam_l = (int)strlen(get_network_device_names(i));
            if (dev_nam_l == 2)
                strncpy(ss, "          ", 11);
            if (dev_nam_l == 3)
                strncpy(ss, "         ", 10);
            if (dev_nam_l == 4)
                strncpy(ss, "        ", 9);
            if (dev_nam_l == 5)
                strncpy(ss, "       ", 8);
            if (dev_nam_l == 6)
                strncpy(ss, "      ", 7);
            if (dev_nam_l == 7)
                strncpy(ss, "     ", 6);
            if (dev_nam_l == 8)
                strncpy(ss, "    ", 5);
            if (dev_nam_l == 8)
                strncpy(ss, "   ", 4);
            if (dev_nam_l == 9)
                strncpy(ss, "  ", 3);
            if (dev_nam_l == 10)
               strncpy(ss, " ", 2);

            for (j = 0; j < files_n; j++) {
                /* set for declaring file no in case -O option is set */
                char str_network_device[10] = "--DEVICE ";
                char str_network_device_tmp[13] = " -- file no.";
                char str_num[150] = {'\0'};
                snprintf(str_num, MAX_INPUT, "%s%s%s%d", str_network_device, get_network_device_names(i), str_network_device_tmp, j + 1);
                append_list(&report_network_error_spike_obj[i], str_num);
                /* end -- set for declaring file no in case -O option is set */

                snprintf(str_tmp, MAX_LINE_LENGTH, "  Spike   value of 'rxerr/s'  of %s is%s%13.2f (%s %s)",
                    get_network_device_names(i), ss, get_network_spike_val_each_file(j, i, "rxerr", "spike"),
                        get_network_spike_date_each_file(j, i, "rxerr", "spike"),
                            get_network_spike_time_each_file(j, i, "rxerr", "spike"));
                append_list ( &report_network_error_spike_obj[i], str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, "  Spike   value of 'txerr/s'  of %s is%s%13.2f (%s %s)",
                    get_network_device_names(i), ss, get_network_spike_val_each_file(j, i, "txerr", "spike"),
                        get_network_spike_date_each_file(j, i, "txerr", "spike"),
                            get_network_spike_time_each_file(j, i, "txerr", "spike"));
                append_list ( &report_network_error_spike_obj[i], str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, "  Spike   value of 'rxdrop/s' of %s is%s%13.2f (%s %s)",
                    get_network_device_names(i), ss, get_network_spike_val_each_file(j, i, "rxdrop", "spike"),
                        get_network_spike_date_each_file(j, i, "rxdrop", "spike"),
                            get_network_spike_time_each_file(j, i, "rxdrop", "spike"));
                append_list(&report_network_error_spike_obj[i], str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, "  Spike   value of 'txdrop/s' of %s is%s%13.2f (%s %s)",
                    get_network_device_names(i), ss, get_network_spike_val_each_file(j, i, "txdrop", "spike"),
                        get_network_spike_date_each_file(j, i, "txdrop", "spike"),
                            get_network_spike_time_each_file(j, i, "txdrop", "spike"));
                append_list(&report_network_error_spike_obj[i], str_tmp);
                append_list(&report_network_error_spike_obj[i], "");

                snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest value of 'rxerr/s'  of %s is%s%13.2f (%s %s)",
                    get_network_device_names(i), ss, get_network_spike_val_each_file(j, i, "rxerr", "highest"),
                        get_network_spike_date_each_file(j, i, "rxerr", "highest"),
                            get_network_spike_time_each_file(j, i, "rxerr", "highest"));
                append_list(&report_network_error_spike_obj[i], str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest value of 'txerr/s'  of %s is%s%13.2f (%s %s)",
                    get_network_device_names(i), ss, get_network_spike_val_each_file(j, i, "txerr", "highest"),
                        get_network_spike_date_each_file(j, i, "txerr", "highest"),
                            get_network_spike_time_each_file(j, i, "txerr", "highest"));
                append_list(&report_network_error_spike_obj[i], str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest value of 'rxdrop/s' of %s is%s%13.2f (%s %s)",
                    get_network_device_names(i), ss, get_network_spike_val_each_file(j, i, "rxdrop", "highest"),
                        get_network_spike_date_each_file(j, i, "rxdrop", "highest"),
                            get_network_spike_time_each_file(j, i, "rxdrop", "highest"));
                append_list(&report_network_error_spike_obj[i], str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest value of 'txdrop/s' of %s is%s%13.2f (%s %s)",
                    get_network_device_names(i), ss, get_network_spike_val_each_file(j, i, "txdrop", "highest"),
                        get_network_spike_date_each_file(j, i, "txdrop", "highest"),
                            get_network_spike_time_each_file(j, i, "txdrop", "highest"));
                append_list(&report_network_error_spike_obj[i], str_tmp);

                append_list(&report_network_error_spike_obj[i], "");

                snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  value of 'rxerr/s'  of %s is%s%13.2f (%s %s)",
                    get_network_device_names(i), ss, get_network_spike_val_each_file(j, i, "rxerr", "lowest"),
                         get_network_spike_date_each_file(j, i, "rxerr", "lowest"),
                             get_network_spike_time_each_file(j, i, "rxerr", "lowest"));
                append_list(&report_network_error_spike_obj[i], str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  value of 'txerr/s'  of %s is%s%13.2f (%s %s)",
                    get_network_device_names(i), ss, get_network_spike_val_each_file(j, i, "txerr", "lowest"),
                        get_network_spike_date_each_file(j, i, "txerr", "lowest"),
                            get_network_spike_time_each_file(j, i, "txerr", "lowest"));
                append_list(&report_network_error_spike_obj[i], str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  value of 'rxdrop/s' of %s is%s%13.2f (%s %s)",
                    get_network_device_names(i), ss, get_network_spike_val_each_file(j, i, "rxdrop", "lowest"),
                        get_network_spike_date_each_file(j, i, "rxdrop", "lowest"),
                            get_network_spike_time_each_file(j, i, "rxdrop", "lowest"));
                append_list(&report_network_error_spike_obj[i], str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  value of 'txdrop/s' of %s is%s%13.2f (%s %s)",
                    get_network_device_names(i), ss, get_network_spike_val_each_file(j, i, "txdrop", "lowest"),
                        get_network_spike_date_each_file(j, i, "txdrop", "lowest"),
                            get_network_spike_time_each_file(j, i, "txdrop", "lowest"));
                append_list(&report_network_error_spike_obj[i], str_tmp);
            }
        }

        append_list(&report_network_error_explanation_obj, "--------");
        append_list(&report_network_error_explanation_obj, " Check these error values for the each network device.");
        append_list(&report_network_error_explanation_obj, " If these are not 0, something is wrong on the network device.");
        append_list(&report_network_error_explanation_obj, " Wrong driver, wrong firmware, or device itself is broken.");
        append_list(&report_obj, "\n#### End Report by sar-analyzer ####" );

    } else {
        if ((SAR_OPTION == 'u') || (SAR_OPTION == 'q') || (SAR_OPTION == 'w') || (SAR_OPTION == 'B') || (SAR_OPTION == 'r') ||
        (SAR_OPTION == 'b') || (SAR_OPTION == 'd') || (SAR_OPTION == 'S') || (SAR_OPTION == 'W') || (SAR_OPTION == 'v') ||
        (SAR_OPTION == 'n') || (SAR_OPTION == 'm') || (SAR_OPTION == 'A')) {
            append_list(&report_obj, "\n#### Report by sar-analyzer ####");
            char str_tmp[MAX_LINE_LENGTH - 1000];
            char s[MAX_LINE_LENGTH - 1000];
            /* filling up with '\0' */
            memset(str_tmp, '\0', MAX_LINE_LENGTH - 1001);
            memset(s, '\0', MAX_LINE_LENGTH - 1001);
            int i = 0, ii = -1;
            if ((SAR_OPTION == 'u') || (SAR_OPTION == 'A')) {
                append_list(&report_obj, "\n-- Report of CPU utilization --");
                for (i = 0, ii = -1; i <= MAX_CORE_NUMBERS; i++, ii++) {
                    if (i > get_core_numbers())
                        break;
                    if (ii == -1)
                        snprintf(s, 12, "%s", "all"); 
                    else
                        snprintf(s, 12, "%d", ii); 
                    append_list(&report_obj, "" );
                    snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest Average value of '%%usr(%%user)'   for CPU %s is %8.2f (%s)",
                        s, get_cpu_avg_highest_val(i, "usr"), get_cpu_avg_highest_date(i, "usr"));
                    append_list(&report_obj, str_tmp);
                    snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  Average value of '%%usr(%%user)'   for CPU %s is %8.2f (%s)",
                        s, get_cpu_avg_lowest_val(i, "usr"), get_cpu_avg_lowest_date(i, "usr"));
                    append_list(&report_obj, str_tmp);
                    snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest Average value of '%%sys(%%system)' for CPU %s is %8.2f (%s)",
                        s, get_cpu_avg_highest_val(i, "sys"), get_cpu_avg_highest_date(i, "sys"));
                    append_list(&report_obj, str_tmp);
                    snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  Average value of '%%sys(%%system)' for CPU %s is %8.2f (%s)",
                        s, get_cpu_avg_lowest_val(i, "sys"), get_cpu_avg_lowest_date(i, "sys"));
                    append_list(&report_obj, str_tmp);
                    snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest Average value of '%%iowait'       for CPU %s is %8.2f (%s)",
                        s, get_cpu_avg_highest_val(i, "iowait"), get_cpu_avg_highest_date(i, "iowait"));
                    append_list(&report_obj, str_tmp);
                    snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  Average value of '%%iowait'       for CPU %s is %8.2f (%s)",
                        s, get_cpu_avg_lowest_val(i,"iowait"), get_cpu_avg_lowest_date(i, "iowait"));
                    append_list(&report_obj, str_tmp);
                    snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest Average value of '%%idle'         for CPU %s is %8.2f (%s)",
                        s, get_cpu_avg_highest_val(i, "idle"), get_cpu_avg_highest_date(i, "idle"));
                    append_list(&report_obj, str_tmp);
                    snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  Average value of '%%idle'         for CPU %s is %8.2f (%s)",
                        s, get_cpu_avg_lowest_val(i, "idle"), get_cpu_avg_lowest_date(i, "idle"));
                    append_list(&report_obj, str_tmp);
                }

                append_list(&report_obj, "--------");
                append_list(&report_obj, "  Each CPU can be in one of four states: user, sys, idle, iowait.");
                append_list(&report_obj, "  If '%usr' is over 60%, applications are in a busy state. Check with ps command which application is busy.");
                append_list(&report_obj, "  If '%sys' is over '%usr', kernel is in a busy state. Check cswch is high or not.");
                append_list(&report_obj, "  If '%iowait' is high, cpu is working for other task more. Note that iowait sometimes meaningless, at all.");
                append_list(&report_obj, "  Check swap statistics or high disk I/O would be the cause. Also check process or memory statistics.");
                append_list(&report_obj, "  If %idle is lower than 30%, you would need new CPU or cores.");
                append_list(&report_obj, "  Check not only 'CPU all', but each CPU values. And if some of their values are high, check the sar file of that date.");
                append_list(&report_obj, "  In such a case, certain program may woking with only one core.");
            }
            if ((SAR_OPTION == 'w') || (SAR_OPTION == 'A')) {
                append_list(&report_obj, " \n-- Report task creation and system switching activity --\n");
                snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest Average value of 'proc/s'  is %13.2f (%s)",
                    get_tasks_avg_highest_val("proc"), get_tasks_avg_highest_date("proc"));
                append_list(&report_obj, str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  Average value of 'proc/s'  is %13.2f (%s)",
                    get_tasks_avg_lowest_val("proc"), get_tasks_avg_lowest_date("proc"));
                append_list(&report_obj, str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest Average value of 'cswch/s' is %13.2f (%s)",
                    get_tasks_avg_highest_val("cswch"), get_tasks_avg_highest_date("proc"));
                append_list(&report_obj, str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  Average value of 'cswch/s' is %13.2f (%s)",
                    get_tasks_avg_lowest_val("cswch"), get_tasks_avg_lowest_date("proc"));
                append_list(&report_obj, str_tmp);
                append_list(&report_obj, "--------");
                append_list(&report_obj, " proc/s shows number of tasks which was created per second.");
                append_list(&report_obj, " Check the order. Depends on cores, but under 100 would be fine.");
                append_list(&report_obj, " cswch/s shows number of context switching activity of CPU per second.");
                append_list(&report_obj, " Check the order. Depends on cores, but maybe over 10000 would be some trouble.");
            }
            if ((SAR_OPTION == 'W') || (SAR_OPTION == 'A')) {
                append_list(&report_obj, " \n-- Report swapping statistics--\n");
                snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest Average value of 'pswpin/s'   is %13.2f (%s)",
                    get_pswap_avg_highest_val("pswpin"), get_pswap_avg_highest_date("pswpin"));
                append_list(&report_obj, str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  Average value of 'pswpin/s'   is %13.2f (%s)",
                    get_pswap_avg_lowest_val("pswpin"), get_pswap_avg_lowest_date("pswpin"));
                append_list(&report_obj, str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest Average value of 'pswpout/s'  is %13.2f (%s)",
                    get_pswap_avg_highest_val("pswpout"), get_pswap_avg_highest_date("pswpout"));
                append_list(&report_obj, str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  Average value of 'pswpout/s'  is %13.2f (%s)",
                    get_pswap_avg_lowest_val("pswpout"), get_pswap_avg_lowest_date("pswpout"));
                append_list(&report_obj, str_tmp);
                append_list(&report_obj, "--------");
                append_list(&report_obj, " pswpin/s is total number of swap pages the system brought in per second.");
                append_list(&report_obj, " pswpout/s is total number of swap pages the system brought out per second.");
                append_list(&report_obj, " If these values are not 0, the box is lacking on memory.");
            }
            if ((SAR_OPTION == 'B') || (SAR_OPTION == 'A')) {
                append_list(&report_obj, " \n-- Report paging statistics --\n" );

                snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest Average value of 'pgpgin/s'  is %13.2f (%s)",
                    get_paging_avg_highest_val("pgpgin"), get_paging_avg_highest_date("pgpgin"));
                append_list(&report_obj, str_tmp );
                snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  Average value of 'pgpgin/s'  is %13.2f (%s)",
                    get_paging_avg_lowest_val("pgpgin"), get_paging_avg_lowest_date("pgpgin"));
                append_list(&report_obj, str_tmp );
                snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest Average value of 'pgpgout/s' is %13.2f (%s)",
                    get_paging_avg_highest_val("pgpgout"), get_paging_avg_highest_date("pgpgout"));
                append_list(&report_obj, str_tmp );
                snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  Average value of 'pgpgout/s' is %13.2f (%s)",
                    get_paging_avg_lowest_val("pgpgout"), get_paging_avg_lowest_date("pgpgout"));
                append_list(&report_obj, str_tmp );
                snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest Average value of 'fault/s'   is %13.2f (%s)",
                    get_paging_avg_highest_val("fault"), get_paging_avg_highest_date("fault"));
                append_list(&report_obj, str_tmp );
                snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  Average value of 'fault/s'   is %13.2f (%s)",
                    get_paging_avg_lowest_val("fault"), get_paging_avg_lowest_date("fault"));
                append_list(&report_obj, str_tmp );
                snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest Average value of 'majflt/s'  is %13.2f (%s)",
                    get_paging_avg_highest_val("majflt"), get_paging_avg_highest_date("majflt"));
                append_list(&report_obj, str_tmp );
                snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  Average value of 'majflt/s'  is %13.2f (%s)",
                    get_paging_avg_lowest_val("majflt"), get_paging_avg_lowest_date("majflt"));
                append_list(&report_obj, str_tmp );
                snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest Average value of '%%vmeff/s'  is %13.2f (%s)",
                    get_paging_avg_highest_val("vmeff"), get_paging_avg_highest_date("vmeff"));
                append_list(&report_obj, str_tmp );
                snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  Average value of '%%vmeff/s'  is %13.2f (%s)",
                    get_paging_avg_lowest_val("vmeff"), get_paging_avg_lowest_date("vmeff"));
                append_list(&report_obj, str_tmp);
                append_list(&report_obj, "--------");
                append_list(&report_obj, " If fault/s is high, programs may requiring memory. Check with, say '# ps -o min_flt,maj_flt <PID>'.");
                append_list(&report_obj, " If majflt/s is high, some big program had been started somehow on that day.");
                append_list(&report_obj, " If vmeff/s is 0, no worry on memory, if vmeff/s is not 0 and over 90.00, it is good.");
                append_list(&report_obj, " If vmeff/s is under 30.00, somethig is wrong.");
            }
            if ((SAR_OPTION == 'b') || (SAR_OPTION == 'A')) {
                append_list(&report_obj, " \n-- Report I/O and transfer rate statistics --\n");
                snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest Average value of 'tps'     is %13.2f (%s)",
                    get_io_transfer_rate_avg_highest_val("tps"), get_io_transfer_rate_avg_highest_date("tps"));
                append_list(&report_obj, str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  Average value of 'tps'     is %13.2f (%s)",
                    get_io_transfer_rate_avg_lowest_val("tps"), get_io_transfer_rate_avg_lowest_date("tps"));
                append_list(&report_obj, str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest Average value of 'bread/s' is %13.2f (%s)",
                    get_io_transfer_rate_avg_highest_val("bread"), get_io_transfer_rate_avg_highest_date("bread"));
                append_list(&report_obj, str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  Average value of 'bread/s' is %13.2f (%s)",
                    get_io_transfer_rate_avg_lowest_val("bread"), get_io_transfer_rate_avg_lowest_date("bread"));
                append_list(&report_obj, str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest Average value of 'bwrtn/s' is %13.2f (%s)",
                    get_io_transfer_rate_avg_highest_val("bwrtn"), get_io_transfer_rate_avg_highest_date("bwrtn"));
                append_list(&report_obj, str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  Average value of 'bwrtn/s' is %13.2f (%s)",
                    get_io_transfer_rate_avg_lowest_val("bwrtn"), get_io_transfer_rate_avg_lowest_date("bwrtn"));
                append_list(&report_obj, str_tmp);
                append_list(&report_obj, "--------");
                append_list(&report_obj, " tps is total number of transfers per second that were issued to physical devices."); 
                append_list(&report_obj, " A transfer is an I/O request to a physical device." ); 
                append_list(&report_obj, " Multiple logical requests can be combined into a single I/O request to the device.");
                append_list(&report_obj, " A transfer is of indeterminate size." );
                append_list(&report_obj, " bread/s is Total amount of data read from the devices in blocks per second.");
                append_list(&report_obj, " Blocks are equivalent to sectors and therefore have a size of 512 bytes.");
                append_list(&report_obj, " bwrtn/s is Total amount of data written to devices in blocks per second.");
                append_list(&report_obj, " If these values are, say over 10000 or some, I/O was heavy on that day. Check the sar file related.");
                append_list(&report_obj, " Check iowait on CPU, also.");
            }
            if ((SAR_OPTION == 'r') || (SAR_OPTION == 'A')) {
                append_list(&report_obj, " \n-- Report memory utilization statistics --\n");
                snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest Average value of '%%memused' is %13.2f (%s)",
                    get_memory_avg_highest_val("memused"), get_memory_avg_highest_date("memused"));
                append_list(&report_obj, str_tmp );
                snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  Average value of '%%memused' is %13.2f (%s)",
                    get_memory_avg_lowest_val("memused"), get_memory_avg_lowest_date("memused"));
                append_list(&report_obj, str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest Average value of 'kbcommit' is %13d (%s)",
                    (int)get_memory_avg_highest_val("kbcommit"), get_memory_avg_highest_date("kbcommit"));
                append_list(&report_obj, str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  Average value of 'kbcommit' is %13d (%s)",
                    (int)get_memory_avg_lowest_val("kbcommit"), get_memory_avg_lowest_date("kbcommit"));
                append_list(&report_obj, str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest Average value of '%%commit'  is %13.2f (%s)",
                    get_memory_avg_highest_val("commit"), get_memory_avg_highest_date("commit"));
                append_list(&report_obj, str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  Average value of '%%commit'  is %13.2f (%s)",
                    get_memory_avg_lowest_val("commit"), get_memory_avg_lowest_date("commit"));
                append_list(&report_obj, str_tmp);
                append_list(&report_obj, "--------");
                append_list(&report_obj, " Even if %memused is around 99.0%, it's OK with Linux." );
                append_list(&report_obj, " Check the highest value of kbcommit. This is the amount of memory needed for the system. If lacking, consider adding more memory.");
                append_list (&report_obj, " If %commit is over 100%, memory shortage is occurring. Gain swap or add more memory.");
            }
            if ((SAR_OPTION == 'S') || (SAR_OPTION == 'A')) {
                append_list(&report_obj, " \n-- Report swap space utilization statistics --\n");
                snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest Average value of '%%swpused'  is %13.2f (%s)",
                    get_swpused_avg_highest_val(), get_swpused_avg_highest_date());
                append_list(&report_obj, str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  Average value of '%%swpused'  is %13.2f (%s)",
                    get_swpused_avg_lowest_val(), get_swpused_avg_lowest_date());
                append_list(&report_obj, str_tmp);
                append_list(&report_obj, "--------");
                append_list(&report_obj, " %swpused percentage of used swap space.");
                append_list(&report_obj, " If it's high, the box is lacking on memory.");
            }
            if ((SAR_OPTION == 'v') || (SAR_OPTION == 'A')) {
                append_list(&report_obj, " \n-- Report status of inode, file and other kernel tables --\n");
                snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest Average value of 'dentunusd'  is %13d (%s)",
                    get_kernel_table_avg_highest_val("dentunusd"), get_kernel_table_avg_highest_date("dentunusd"));
                append_list(&report_obj, str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  Average value of 'dentunusd'  is %13d (%s)",
                    get_kernel_table_avg_lowest_val("dentunusd"), get_kernel_table_avg_lowest_date("dentunusd"));
                append_list(&report_obj, str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest Average value of 'file-nr'    is %13d (%s)",
                    get_kernel_table_avg_highest_val("file"), get_kernel_table_avg_highest_date("file"));
                append_list(&report_obj, str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  Average value of 'file-nr'    is %13d (%s)",
                    get_kernel_table_avg_lowest_val("file"), get_kernel_table_avg_lowest_date("file"));
                append_list(&report_obj, str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest Average value of 'inode-nr'   is %13d (%s)",
                    get_kernel_table_avg_highest_val("inode"), get_kernel_table_avg_highest_date("inode"));
                append_list(&report_obj, str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  Average value of 'inode-nr'   is %13d (%s)",
                    get_kernel_table_avg_lowest_val("inode"), get_kernel_table_avg_lowest_date("inode"));
                append_list(&report_obj, str_tmp);
                append_list(&report_obj, "--------");
                append_list(&report_obj, " dentunusd is number of unused cache entries in the directory cache.");
                append_list(&report_obj, " file-nr is number of file handles used by the system.");
                append_list(&report_obj, " inode-nr is number of inode handlers used by the system.");
                append_list(&report_obj, " Check the order of these values. If it's high, something is wrong.");
            }
            if ((SAR_OPTION == 'q') || (SAR_OPTION == 'A')) {
                append_list (&report_obj, " \n-- Report of queue length and load averages --\n" );
                snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest Average value of 'runq-sz'  is %13d (%s)",
                    (int)get_ldavg_avg_highest_val("runq_sz"), get_ldavg_avg_highest_date("runq_sz"));
                append_list(&report_obj, str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  Average value of 'runq-sz'  is %13d (%s)",
                    (int)get_ldavg_avg_lowest_val("runq_sz"), get_ldavg_avg_lowest_date("runq_sz"));
                append_list(&report_obj, str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest Average value of 'plist-sz' is %13d (%s)",
                    (int)get_ldavg_avg_highest_val("plist_sz"), get_ldavg_avg_highest_date("plist_sz"));
                append_list(&report_obj, str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  Average value of 'plist-sz' is %13d (%s)",
                    (int)get_ldavg_avg_lowest_val("plist_sz"), get_ldavg_avg_lowest_date("plist_sz"));
                append_list(&report_obj, str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest Average value of 'ldavg-1'  is %13.2f (%s)",
                    get_ldavg_avg_highest_val("ldavg_one"), get_ldavg_avg_highest_date("ldavg_one"));
                append_list(&report_obj, str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  Average value of 'ldavg-1'  is %13.2f (%s)",
                    get_ldavg_avg_lowest_val("ldavg_one"), get_ldavg_avg_lowest_date("ldavg_one"));
                append_list(&report_obj, str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest Average value of 'ldavg-5'  is %13.2f (%s)",
                    get_ldavg_avg_highest_val("ldavg_five"), get_ldavg_avg_highest_date("ldavg_five"));
                append_list(&report_obj, str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  Average value of 'ldavg-5'  is %13.2f (%s)",
                    get_ldavg_avg_lowest_val("ldavg_five"), get_ldavg_avg_lowest_date("ldavg_five"));
                append_list(&report_obj, str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest Average value of 'ldavg-15' is %13.2f (%s)",
                    get_ldavg_avg_highest_val("ldavg_15"), get_ldavg_avg_highest_date("ldavg_15"));
                append_list(&report_obj, str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  Average value of 'ldavg-15' is %13.2f (%s)",
                    get_ldavg_avg_lowest_val("ldavg_15"), get_ldavg_avg_lowest_date("ldavg_15"));
                append_list(&report_obj, str_tmp);
                append_list(&report_obj, "--------");
                append_list(&report_obj, "  If devided by /proc/cpuinfo|grep 'cores' value of 'runq-sz' is over 2, the box is cpu bound.");
                append_list(&report_obj, "  If that is the case, you might need more cpu power to do the task.");
                append_list(&report_obj, "  If 'plist-sz' is higher than 10,000 for example, there are waits.");
                append_list(&report_obj, "  If 'ldavg-<minites>' exceeds number of cores, cpu load is high.");
                append_list(&report_obj, "  Check number of cores with, $cat /proc/cpuinfo | grep 'cpu cores'.");
                append_list(&report_obj, "  Check number of physical cpu with, $cat /proc/cpuinfo | grep 'physical id'.");
                append_list(&report_obj, "  Check if hyperthreading is enabled with, $cat /proc/cpuinfo | grep 'siblings'.");
                append_list(&report_obj, "  Divide the result of above command and if it is not same as core, hyperthreading is enabled.");
                append_list(&report_obj, "  So, if you have 8 cores, highest value is 800.00 and above 60% of this value would be a trouble.");
            }
            if ((SAR_OPTION == 'd') || (SAR_OPTION == 'A')) {
                append_list(&report_obj, " \n-- Report activity for each block device --\n");
                for (i = 1; i <= MAX_BLOCK_DEVICE_NUMBERS; i++) {
                    if (i >= get_block_device_numbers())
                        break;
                    char ss[20];
                    memset(ss, 0, sizeof(ss));
                    int dev_nam_l = 0;
                    dev_nam_l = (int)strlen(get_block_device_names(i));
                    if (dev_nam_l == 2)
                        strncpy(ss, "          ", 11);
                    if (dev_nam_l == 3)
                        strncpy(ss, "         ", 10);
                    if (dev_nam_l == 4)
                        strncpy(ss, "        ", 9);
                    if (dev_nam_l == 5)
                        strncpy(ss, "       ", 8);
                    if (dev_nam_l == 6)
                        strncpy(ss, "      ", 7);
                    if (dev_nam_l == 7)
                        strncpy(ss, "     ", 6);
                    if (dev_nam_l == 8)
                        strncpy(ss, "    ", 5);
                    if (dev_nam_l == 8)
                        strncpy(ss, "   ", 4);
                    if (dev_nam_l == 9)
                        strncpy(ss, "  ", 3);
                    if (dev_nam_l == 10)
                        strncpy(ss, " ", 2);
                    snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest Average value of 'areq-sz' of %s is%s%13.2f (%s)",
                        get_block_device_names(i), ss,
                            get_block_device_avg_highest_val(i, "areqsz"),
                                get_block_device_avg_highest_date(i, "areqsz"));
                    append_list(&report_obj, str_tmp);
                    snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  Average value of 'areq-sz' of %s is%s%13.2f (%s)",
                        get_block_device_names(i), ss,
                            get_block_device_avg_lowest_val(i, "areqsz"),
                                get_block_device_avg_lowest_date(i, "areqsz"));
                    append_list(&report_obj, str_tmp);
                    append_list(&report_obj, "");
                    snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest Average value of '%%util'   of %s is%s%13.2f (%s)",
                        get_block_device_names(i), ss,
                            get_block_device_avg_highest_val(i, "util"),
                                get_block_device_avg_highest_date(i, "util"));
                    append_list(&report_obj, str_tmp);
                    snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  Average value of '%%util'   of %s is%s%13.2f (%s)",
                        get_block_device_names(i), ss,
                            get_block_device_avg_lowest_val(i, "util"),
                                get_block_device_avg_lowest_date(i, "util"));
                    append_list(&report_obj, str_tmp);
                    append_list(&report_obj, "----");
                }
                append_list(&report_obj, "--------" );
                append_list(&report_obj, " 'areq-sz' is the average size (in kilobytes) of the I/O requests that were issued to the device.");
                append_list(&report_obj, " Note: In previous versions, this field was known as avgrq-sz and was expressed in sectors.");
                append_list(&report_obj, " '%util'is percentage of elapsed time during which I/O requests were issued to the device ");
                append_list(&report_obj, " (bandwidth utilization for the device). Device saturation occurs when this value ");
                append_list(&report_obj, " is close to 100% for devices serving requests serially. But for devices serving requests in");
                append_list(&report_obj, " parallel, such as RAID arrays and modern SSDs, this number does not reflect their performance limits.");
            }
            if ((SAR_OPTION == 'n') || (SAR_OPTION == 'A')) {
                append_list(&report_obj, " \n-- Report network statistics --\n");
                for (i = 1; i <= MAX_NETWORK_DEVICE_NUMBERS; i++) {
                    if (i >= get_network_device_numbers())
                        break;
                    char ss[20];
                    memset(ss, 0, sizeof(ss));
                    int dev_nam_l = 0;
                    dev_nam_l = (int)strlen(get_network_device_names(i));
                    if (dev_nam_l == 2)
                        strncpy(ss, "          ", 11);
                    if (dev_nam_l == 3)
                        strncpy(ss, "         ", 10);
                    if (dev_nam_l == 4)
                        strncpy(ss, "        ", 9);
                    if (dev_nam_l == 5)
                        strncpy(ss, "       ", 8);
                    if (dev_nam_l == 6)
                        strncpy(ss, "      ", 7);
                    if (dev_nam_l == 7)
                        strncpy(ss, "     ", 6);
                    if (dev_nam_l == 8)
                        strncpy(ss, "    ", 5);
                    if (dev_nam_l == 8)
                        strncpy(ss, "   ", 4);
                    if (dev_nam_l == 9)
                        strncpy(ss, "  ", 3);
                    if (dev_nam_l == 10)
                        strncpy(ss, " ", 2);
                    snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest Average value of 'rxpck/s' of %s is%s%13.2f (%s)",
                        get_network_device_names(i), ss,
                            get_network_avg_highest_val(i, "rxpck"),
                                get_network_avg_highest_date(i, "rxpck"));
                    append_list(&report_obj, str_tmp );
                    snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  Average value of 'rxpck/s' of %s is%s%13.2f (%s)",
                        get_network_device_names(i), ss,
                            get_network_avg_lowest_val(i, "rxpck"),
                                get_network_avg_lowest_date(i, "rxpck"));
                    append_list(&report_obj, str_tmp);
                    append_list(&report_obj, "");
                    snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest Average value of 'txpck/s' of %s is%s%13.2f (%s)",
                        get_network_device_names(i), ss,
                            get_network_avg_highest_val(i, "txpck"),
                                get_network_avg_highest_date(i, "txpck"));
                    append_list(&report_obj, str_tmp);
                    snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  Average value of 'txpck/s' of %s is%s%13.2f (%s)",
                        get_network_device_names(i), ss,
                            get_network_avg_lowest_val(i, "txpck"),
                                get_network_avg_lowest_date(i, "txpck"));
                    append_list(&report_obj, str_tmp);
                    append_list(&report_obj, "");
                    snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest Average value of 'rxkB/s'  of %s is%s%13.2f (%s)",
                        get_network_device_names(i), ss,
                            get_network_avg_highest_val(i, "rxkb"),
                                get_network_avg_highest_date(i, "rxkb"));
                    append_list(&report_obj, str_tmp);
                    snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  Average value of 'rxkB/s'  of %s is%s%13.2f (%s)",
                        get_network_device_names(i), ss,
                            get_network_avg_lowest_val(i, "rxkb"),
                                get_network_avg_lowest_date(i, "rxkb"));
                    append_list(&report_obj, str_tmp);
                    append_list(&report_obj, "");
                    snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest Average value of 'txkB/s'  of %s is%s%13.2f (%s)",
                        get_network_device_names(i), ss,
                            get_network_avg_highest_val(i, "txkb"),
                                get_network_avg_highest_date(i, "txkb"));
                    append_list(&report_obj, str_tmp);
                    snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  Average value of 'txkB/s'  of %s is%s%13.2f (%s)",
                        get_network_device_names(i), ss,
                            get_network_avg_lowest_val(i, "txkb"),
                                get_network_avg_lowest_date(i, "txkb"));
                    append_list(&report_obj, str_tmp);
                    append_list(&report_obj, "----");
                }
                append_list(&report_obj, "--------");
                append_list(&report_obj, " Check these values for the each network device.");
            }
            if ((SAR_OPTION == 'm') ||(SAR_OPTION == 'A')) {
                append_list(&report_obj, " \n-- Report statistics on failures (errors) from the network devices --\n");
                for (i = 1; i <= MAX_NETWORK_DEVICE_NUMBERS; i++) {
                    if (i >= get_network_device_numbers())
                        break;
                    char ss[20];
                    memset (ss, 0, sizeof(ss));
                    int dev_nam_l = 0;
                    dev_nam_l = (int)strlen(get_network_device_names(i));
                    if (dev_nam_l == 2)
                        strncpy(ss, "          ", 11);
                    if (dev_nam_l == 3)
                        strncpy(ss, "         ", 10);
                    if (dev_nam_l == 4)
                        strncpy(ss, "        ", 9);
                    if (dev_nam_l == 5)
                        strncpy(ss, "       ", 8);
                    if (dev_nam_l == 6)
                        strncpy(ss, "      ", 7);
                    if (dev_nam_l == 7)
                        strncpy(ss, "     ", 6);
                    if (dev_nam_l == 8)
                        strncpy(ss, "    ", 5);
                    if (dev_nam_l == 8)
                        strncpy(ss, "   ", 4);
                    if (dev_nam_l == 9)
                        strncpy(ss, "  ", 3);
                    if (dev_nam_l == 10)
                        strncpy(ss, " ", 2);
                    snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest Average value of 'rxerr/s'  of %s is%s%13.2f (%s)",
                        get_network_device_names(i), ss,
                            get_network_avg_highest_val(i, "rxerr"),
                                get_network_avg_highest_date(i, "rxerr"));
                    append_list(&report_obj, str_tmp);
                    snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  Average value of 'rxerr/s'  of %s is%s%13.2f (%s)",
                        get_network_device_names(i), ss,
                            get_network_avg_lowest_val(i, "rxerr"),
                                get_network_avg_lowest_date(i, "rxerr"));
                    append_list(&report_obj, str_tmp);
                    append_list(&report_obj, "");
                    snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest Average value of 'txerr/s'  of %s is%s%13.2f (%s)",
                        get_network_device_names(i), ss,
                            get_network_avg_highest_val(i, "txerr"),
                                get_network_avg_highest_date(i, "txerr"));
                    append_list(&report_obj, str_tmp );
                    snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  Average value of 'txerr/s'  of %s is%s%13.2f (%s)",
                        get_network_device_names(i), ss,
                            get_network_avg_lowest_val(i, "txerr"),
                                get_network_avg_lowest_date(i, "txerr"));
                    append_list(&report_obj, str_tmp);
                    append_list(&report_obj, "");
                    snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest Average value of 'rxdrop/s' of %s is%s%13.2f (%s)",
                        get_network_device_names(i), ss,
                            get_network_avg_highest_val(i, "rxdrop"),
                                get_network_avg_highest_date(i, "rxdrop"));
                    append_list(&report_obj, str_tmp);
                    snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  Average value of 'rxdrop/s' of %s is%s%13.2f (%s)",
                        get_network_device_names(i), ss,
                            get_network_avg_lowest_val(i, "rxdrop"),
                                get_network_avg_lowest_date(i, "rxdrop"));
                    append_list(&report_obj, str_tmp);
                    append_list(&report_obj, "");
                    snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest Average value of 'txdrop/s' of %s is%s%13.2f (%s)",
                        get_network_device_names(i), ss,
                            get_network_avg_highest_val(i, "txdrop"),
                                get_network_avg_highest_date(i, "txdrop"));
                    append_list(&report_obj, str_tmp);
                    snprintf(str_tmp, MAX_LINE_LENGTH, "  Lowest  Average value of 'txdrop/s' of %s is%s%13.2f (%s)",
                        get_network_device_names(i), ss,
                            get_network_avg_lowest_val(i, "txdrop"),
                                get_network_avg_lowest_date(i, "txdrop"));
                    append_list(&report_obj, str_tmp);
                    append_list(&report_obj, "----");
                }
                append_list(&report_obj, "--------");
                append_list(&report_obj, " Check these error values for the each network device.");
                append_list(&report_obj, " If these are not 0, something is wrong on the network device.");
                append_list(&report_obj, " Wrong driver, wrong firmware, or device itself is broken.");
            }
        }
        append_list(&report_obj, "\n#### End Report by sar-analyzer ####");
    }

    /*** detecting thrashing and others ****/
    char str_tmp[MAX_LINE_LENGTH - 1000];
    char str_tmp_thrashing_cpu_pre[51];
    char str_tmp_thrashing_pgpgin_pre[51];
    char s[MAX_LINE_LENGTH - 1000];

    /* filling up with '\0' */
    memset(str_tmp, '\0', MAX_LINE_LENGTH - 1001);
    memset(str_tmp_thrashing_cpu_pre, '\0', 50);
    memset(str_tmp_thrashing_pgpgin_pre, '\0', 50);
    memset(s, '\0', MAX_LINE_LENGTH - 1001);

    append_list(&report_thrashing_obj, "\n#### Detecting thrashing ####");

    int i = 0, ii = -1, j = 1, l = 0;

    /* in each file */
    for (i = 0, ii = -1; i <= 0; i++, ii++) {
        if (i > get_core_numbers())
            break;
        if (ii == -1)
            snprintf(s, 12, "%s", "all"); 
        else
            break;

        for (j = 0; j < files_n; j++) {
            append_list(&report_thrashing_obj, "");
            /* set for declaring file no in case -O option is set */
            char str_cpu[7] = "--CPU ";
            char str_cpu_tmp[13] = " ## file no.";
            char str_num[50] = {'\0'};
            char s[5];
            if (ii == -1)
                snprintf(s, 4, "%s", "all"); 
            else
                break;
            snprintf(str_num, MAX_INPUT, "%s%s%s%d", str_cpu, s, str_cpu_tmp, j + 1);
            append_list(&report_thrashing_obj, str_num);
            /* end -- set for declaring file no in case -O option is set */

            snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest value of '%%iowait' for CPU %s is %8.2f (%s %s)",
                s, get_cpu_spike_val_each_file(j, i, "iowait", "highest"),
                    get_cpu_spike_date_each_file(j, i, "iowait", "highest"),
                        get_cpu_spike_time_each_file(j, i, "iowait", "highest"));
            append_list(&report_thrashing_obj, str_tmp);

            snprintf(str_tmp, MAX_LINE_LENGTH, "  Highest value of 'pgpgin/s'            is %8.2f (%s %s)",
                get_paging_spike_val_each_file(j, "pgpgin", "highest"),
                    get_paging_spike_date_each_file(j, "pgpgin", "highest"),
                        get_paging_spike_time_each_file(j, "pgpgin", "highest"));
            append_list(&report_thrashing_obj, str_tmp);
            strncpy(str_tmp_thrashing_cpu_pre, get_cpu_spike_time_each_file(j, i,  "iowait", "highest"), 50);
            strncpy(str_tmp_thrashing_pgpgin_pre, get_paging_spike_time_each_file(j, "pgpgin", "highest"), 50);
            if (strcmp(str_tmp_thrashing_cpu_pre, str_tmp_thrashing_pgpgin_pre) == 0) {
                /* if using color, this is an example */
                /* snprintf(str_tmp, MAX_LINE_LENGTH, "%s%s%s", ANSI_COLOR_RED, "---- !! Possibly, thrashing is occurring !!", ANSI_COLOR_RESET); */
                snprintf(str_tmp, MAX_INPUT, "%s", "");
                append_list(&report_thrashing_obj, str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, "%s", "    !!!! Possibly, thrashing is occurring !!!!" );
                append_list(&report_thrashing_obj, str_tmp);
                l++;
            }
            if ((j == files_n - 1) && (l == 0)) {
                append_list(&report_thrashing_obj, "");
                append_list(&report_thrashing_obj, "No thrashing detected");
            }
        }
    }

    append_list(&report_thrashing_obj, "");

    /*** detecting network down ****/
    l = 0;
    for (i = 1; i <= MAX_NETWORK_DEVICE_NUMBERS; i++)
    {
        if (i >= get_network_device_numbers())
            break;
        if (i == 1)
        {
            append_list(&report_network_down_obj[i], "#### Detecting network down ####");
            append_list(&report_network_down_obj[i], "");
        }

        char ss[20];
        memset(ss, 0, sizeof(ss));
        int dev_nam_l = 0;
        dev_nam_l = (int)strlen(get_network_device_names(i));
        if (dev_nam_l == 2)
            strncpy(ss, "          ", 11);
        if (dev_nam_l == 3)
            strncpy(ss, "         ", 10);
        if (dev_nam_l == 4)
            strncpy(ss, "        ", 9);
        if (dev_nam_l == 5)
            strncpy(ss, "       ", 8);
        if (dev_nam_l == 6)
            strncpy(ss, "      ", 7);
        if (dev_nam_l == 7)
            strncpy(ss, "     ", 6);
        if (dev_nam_l == 8)
            strncpy(ss, "    ", 5);
        if (dev_nam_l == 8)
            strncpy(ss, "   ", 4);
        if (dev_nam_l == 9)
            strncpy(ss, "  ", 3);
        if (dev_nam_l == 10)
           strncpy(ss, " ", 2);
        for (j = 0; j < files_n; j++)
        {
            if (strcmp(get_network_spike_date_each_file(j, i, "rxpck", "down"), "") != 0)
            {
                /* set for declaring file no in case -O option is set */
                char str_network_device[10] = "--DEVICE ";
                char str_network_device_tmp[13] = " -- file no.";
                char str_num[150] = {'\0'};
                snprintf(str_num, MAX_INPUT, "%s%s%s%d", str_network_device, get_network_device_names(i), str_network_device_tmp, j + 1);
                append_list(&report_network_down_obj[i], str_num);
                /* end -- set for declaring file no in case -O option is set */
                snprintf(str_tmp, MAX_LINE_LENGTH, "  Down   time of 'rxpck/s' of %s is%s%13.2f (%s %s)",
                    get_network_device_names(i), ss,
                        get_network_spike_val_each_file(j, i, "rxpck", "down"),
                            get_network_spike_date_each_file(j, i, "rxpck", "down"),
                                get_network_spike_time_each_file(j, i, "rxpck", "down"));
                append_list(&report_network_down_obj[i], str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, "  Down   time of 'txpck/s' of %s is%s%13.2f (%s %s)",
                    get_network_device_names(i), ss,
                        get_network_spike_val_each_file(j, i, "txpck", "down"),
                            get_network_spike_date_each_file(j, i, "txpck", "down"),
                                get_network_spike_time_each_file(j, i, "txpck", "down"));
                append_list(&report_network_down_obj[i], str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, "  Down   time of 'rxkB/s'  of %s is%s%13.2f (%s %s)",
                    get_network_device_names(i), ss,
                        get_network_spike_val_each_file(j, i, "rxkb", "down"),
                            get_network_spike_date_each_file(j, i, "rxkb", "down"),
                                get_network_spike_time_each_file(j, i, "rxkb", "down"));
                append_list(&report_network_down_obj[i], str_tmp);
                snprintf(str_tmp, MAX_LINE_LENGTH, "  Down   time of 'txkB/s'  of %s is%s%13.2f (%s %s)",
                    get_network_device_names(i), ss,
                        get_network_spike_val_each_file(j, i, "txkb", "down"),
                            get_network_spike_date_each_file(j, i, "txkb", "down"),
                                get_network_spike_time_each_file(j, i, "txkb", "down"));
                append_list(&report_network_down_obj[i], str_tmp);
                l++;
            }
        }
        if ((i == get_network_device_numbers() -1 ) && (l == 0))
            append_list(&report_network_down_obj[i], "No network down detected");
    }

    /*** Overall judgement ***/
    append_list(&report_overall_judgement_obj, "");
    append_list(&report_overall_judgement_obj, "#### Overall Judgement ####");
    double judge_cpu_avg_lowest_val = get_cpu_avg_lowest_val(0, "idle");
    append_list(&report_overall_judgement_obj, "   -- CPU --");
    if (judge_cpu_avg_lowest_val < 30.00) {
        append_list(&report_overall_judgement_obj, "   Add more CPU!");
        snprintf(str_tmp, MAX_LINE_LENGTH, "   Lowest average value of '%%idle' for CPU all is below 30(%5.2f)%%!", judge_cpu_avg_lowest_val);
        append_list(&report_overall_judgement_obj, str_tmp);
    } else {
        append_list(&report_overall_judgement_obj, "   No need to add more CPU.");
        snprintf(str_tmp, MAX_LINE_LENGTH, "   Lowest average value of '%%idle' for CPU all is above 30(%5.2f)%%.", judge_cpu_avg_lowest_val);
        append_list(&report_overall_judgement_obj, str_tmp);
    }
    append_list(&report_overall_judgement_obj, "   -- MEMORY --");
    if (judge_memory_avg_highest_val >= 80.00) {
        append_list(&report_overall_judgement_obj, "   Add more MEMORY!");
        snprintf(str_tmp, MAX_LINE_LENGTH, "   Highest average value of '%%memused' is above 80(%5.2f)%%!", judge_memory_avg_highest_val);
        append_list(&report_overall_judgement_obj, str_tmp);
    } else {
        append_list(&report_overall_judgement_obj, "   No need to add more MEMORY.");
        snprintf(str_tmp, MAX_LINE_LENGTH, "   Highest average value of '%%memused' is below 80(%5.2f)%%.", judge_memory_avg_highest_val);
        append_list(&report_overall_judgement_obj, str_tmp);
    }

    return 0;
}

int append_header_to_ps_objs(node **obj, FILE *fp_w)
{
    append_list(obj, "%!PS-Adobe-3.0 EPSF-3.0");
    append_list(obj, " initgraphics erasepage a4  0.39 0.39 scale 66 63 translate");
    append_list(obj, " 2 setlinewidth 0 setlinecap 2 setlinejoin /#copies 1 def /f { fill} def");
    append_list(obj, " /ff {findfont} def /gr { grestore} def /gs { gsave} def /l { lineto} def");
    append_list(obj, " /lw { setlinewidth} def /mf { makefont} def /m { moveto} def");
    append_list(obj, " /n { newpath} def /sf { setfont} def /rgb { setrgbcolor} def");
    append_list(obj, " /g { setgray} def /sh { show} def /p { showpage} def /s { stroke} def");
    append_list(obj, " /scf { scalefont} def");
    return 0;
}

int append_rectangular_to_ps_objs(node **obj, FILE *fp_w, const char *element)
{
    /* rectangular 1 */
    if (strcmp("up", element) == 0) {
        append_list(obj, "%rectangular 1");
        append_list(obj, " 100 1900 m");
        append_list(obj, " 1400 1900 l");
        append_list(obj, " 1400 1200 l");
        append_list(obj, " 100 1200 l");
        append_list(obj, " 100 1900 l");
        append_list(obj, "stroke");
    }
    /* rectangular 2 */
    if (strcmp("down", element) == 0) {
        append_list(obj, "%rectangular 2");
        append_list(obj, " 100 830 m");
        append_list(obj, " 1400 830 l");
        append_list(obj, " 1400 130 l");
        append_list(obj, " 100 130 l");
        append_list(obj, " 100 830 l");
        append_list(obj, "stroke");
    }
    return 0;
}

int append_labels_to_ps_obj(node **obj, FILE *fp_w, const char *item)
{
    char str_tmp[50];
    /* creating postscript file data */

    /* for file cpu */
    if (strcmp("cpu", item) == 0) {
        /* title */
        append_list(obj, "% Label for title");
        append_list(obj, " /Times-Roman ff 24 scf sf");
        append_list(obj, " 0.000 0.000 0.000 rgb 1 lw");
        snprintf(str_tmp, 50, " 45 2000 m (Created by sar-analyzer %d.%d.%d) sh",
            PROGRAM_VERSION, PROGRAM_RELEASE, PROGRAM_SUB_RELEASE);
        append_list(obj, str_tmp);
        append_list(obj, "stroke");
        append_list(obj, "%");

        /* title of CPU all */
        append_list(obj, "% Label for CPU all");
        append_list(obj, " /Times-Roman ff 36 scf sf");
        append_list(obj, " 0.000 0.000 0.000 rgb 1 lw");
        append_list(obj, " 100 1930 m (CPU all) sh");
        append_list(obj, "%" );
        /* full for cpu all rectangular left position */
        append_list(obj, "% Label for CPU all - full");
        append_list(obj, " /Times-Roman ff 24 scf sf");
        append_list(obj, " 0.000 0.000 0.000 rgb 1 lw");
        append_list(obj, " 35 1890 m (100%) sh");
        append_list(obj, "%");
        /* half for cpu all rectangular left position */
        append_list(obj, "% Label for CPU all - half");
        append_list(obj, " /Times-Roman ff 24 scf sf");
        append_list(obj, " 0.000 0.000 0.000 rgb 1 lw");
        append_list(obj, " 40 1550 m (50%) sh");
        append_list(obj, "%");
        /* zero for cpu all rectangular left position */
        append_list(obj, "% Label for CPU all - zero");
        append_list(obj, " /Times-Roman ff 24 scf sf");
        append_list(obj, " 0.000 0.000 0.000 rgb 1 lw");
        append_list(obj, " 45 1200 m (0%) sh");
        append_list(obj, "%");
        /* graph legend strings for CPU */
        append_list(obj, "% Graph legend for CPU all (strings)");
        append_list(obj, " /Times-Roman ff 20 scf sf");
        append_list(obj, " 0.000 0.000 0.000 rgb 1 lw");
        append_list(obj, " 1300 1965 m (%usr (grn)) sh");
        append_list(obj, " 0.000 0.000 0.000 rgb 1 lw");
        append_list(obj, " 1300 1950 m (%sys (blu)) sh");
        append_list(obj, " 0.000 0.000 0.000 rgb 1 lw");
        append_list(obj, " 1300 1935 m (%iowait (red)) sh");
        append_list(obj, " 0.000 0.000 0.000 rgb 1 lw");
        append_list(obj, " 1300 1910 m (%idle (blk)) sh");
        append_list(obj, "%");

        /* title of paigng */
        append_list(obj, "% Label for paging");
        append_list(obj, " /Times-Roman ff 36 scf sf");
        append_list(obj, " 0.000 0.000 0.000 rgb 1 lw");
        append_list(obj, " 100 860 m (paging) sh");
        append_list(obj, "%");
        /* full for paging rectangular left position */
        append_list(obj, "% Label for paging - full");
        append_list(obj, " /Times-Roman ff 20 scf sf");
        append_list(obj, " 0.000 0.000 0.000 rgb 1 lw");
        append_list(obj, " 20 820 m (10,000) sh");
        append_list(obj, " 0.000 0.000 1.000 rgb 1 lw");
        append_list(obj, " 15 805 m (200,000) sh");
        /* full for paging rectangular right position */
        append_list(obj, " /Times-Roman ff 20 scf sf");
        append_list(obj, " 0.000 0.000 0.000 rgb 1 lw");
        append_list(obj, " 1405 810 m (100%) sh");
        append_list(obj, "%");
        /* half for paging rectangular left position */
        append_list(obj, "% Label for paging - half");
        append_list(obj, " /Times-Roman ff 20 scf sf");
        append_list(obj, " 0.000 0.000 0.000 rgb 1 lw");
        append_list(obj, " 30 480 m (5,000) sh");
        append_list(obj, " 0.000 0.000 1.000 rgb 1 lw");
        append_list(obj, " 15 465 m (100,000) sh");
        /* half for paging rectangular right position */
        append_list(obj, " /Times-Roman ff 20 scf sf");
        append_list(obj, " 0.000 0.000 0.000 rgb 1 lw");
        append_list(obj, " 1405 470 m (50%) sh");
        append_list(obj, "%");
        /* zero for paging rectangular left position */
        append_list(obj, "% Label for paging - zero");
        append_list(obj, " /Times-Roman ff 20 scf sf");
        append_list(obj, " 0.000 0.000 0.000 rgb 1 lw");
        append_list(obj, " 60 130 m (0) sh");
        /* zero for paging rectangular right position */
        append_list(obj, " /Times-Roman ff 20 scf sf");
        append_list(obj, " 1410 130 m (0%) sh");
        append_list(obj, "%");
        /* graph legend strings for paging */
        append_list(obj, "% Graph legend for paging (strings)");
        append_list(obj, " /Times-Roman ff 20 scf sf");
        append_list(obj, " 0.000 0.000 0.000 rgb 1 lw");
        append_list(obj, " 1300 930 m (pgpgin/s (red)) sh");
        append_list(obj, " 0.000 0.000 0.000 rgb 1 lw");
        append_list(obj, " 1300 910 m (pgpgout/s (grn)) sh");
        append_list(obj, " 0.000 0.000 0.000 rgb 1 lw");
        append_list(obj, " 1300 890 m (fault/s (blu)) sh");
        append_list(obj, " 0.000 0.000 0.000 rgb 1 lw");
        append_list(obj, " 1300 870 m (majflt/s (blk)) sh");
        append_list(obj, " 0.000 0.000 0.000 rgb 1 lw");
        append_list(obj, " 1300 845 m (%vmeff (yel)) sh");
        append_list(obj, "%");
    }
    /* for file mem */
    else if (strcmp("memory", item) == 0) {
        /* title */
        append_list(obj, "% Label for title");
        append_list(obj, " /Times-Roman ff 24 scf sf");
        append_list(obj, " 0.000 0.000 0.000 rgb 1 lw");
        snprintf(str_tmp, 50, " 45 2000 m (Created by sar-analyzer %d.%d.%d) sh",
            PROGRAM_VERSION, PROGRAM_RELEASE, PROGRAM_SUB_RELEASE);
        append_list(obj, str_tmp);
        append_list(obj, "stroke");
        append_list(obj, "%");

        /* title of memory */
        append_list(obj, "% Label for memory");
        append_list(obj, " /Times-Roman ff 36 scf sf");
        append_list(obj, " 0.000 0.000 0.000 rgb 1 lw");
        append_list(obj, " 100 1930 m (memory) sh");
        append_list(obj, "%");
        /* full for memory rectangular left position */
        append_list(obj, "% Label for memory - full");
        append_list(obj, " /Times-Roman ff 20 scf sf");
        append_list(obj, " 0.000 0.000 0.000 rgb 1 lw");
        append_list(obj, " 45 1890 m (100%) sh");
        append_list(obj, " 1.000 0.000 0.000 rgb 1 lw");
        append_list(obj, " 0 1875 m (40,000,000) sh");
        append_list(obj, "%");
        /* half for memory rectangular left position */
        append_list(obj, "% Label for memory - half");
        append_list(obj, " /Times-Roman ff 20 scf sf");
        append_list(obj, " 0.000 0.000 0.000 rgb 1 lw");
        append_list(obj, " 55 1550 m (50%) sh");
        append_list(obj, " 1.000 0.000 0.000 rgb 1 lw");
        append_list(obj, " 0 1535 m (20,000,000) sh");
        append_list(obj, "%");
        /* zero for memory rectangular left position */
        append_list(obj, "% Label for memory - zero");
        append_list(obj, " /Times-Roman ff 20 scf sf");
        append_list(obj, " 0.000 0.000 0.000 rgb 1 lw");
        append_list(obj, " 65 1200 m (0%) sh");
        append_list(obj, " 1.000 0.000 0.000 rgb 1 lw");
        append_list(obj, " 60 1185 m (0) sh");
        append_list(obj, "%");
        /* graph legend strings for memory */
        append_list(obj, "% Graph legend for memory (strings)");
        append_list(obj, " /Times-Roman ff 20 scf sf");
        append_list(obj, " 0.000 0.000 0.000 rgb 1 lw");
        append_list(obj, " 1300 1945 m (%memused (blu)) sh");
        append_list(obj, " 0.000 0.000 0.000 rgb 1 lw");
        append_list(obj, " 1300 1925 m (kbcommit (red)) sh");
        append_list(obj, " 0.000 0.000 0.000 rgb 1 lw");
        append_list(obj, " 1300 1910 m (%commit (blk)) sh");
        append_list(obj, "%");

        /* title of swapping */
        append_list(obj, "% Label for swapping");
        append_list(obj, " /Times-Roman ff 36 scf sf");
        append_list(obj, " 0.000 0.000 0.000 rgb 1 lw");
        append_list(obj, " 100 860 m (swapping) sh");
        append_list(obj, "%");
        /* full for swapping rectangular left position */
        append_list(obj, "% Label for swapping - full");
        append_list(obj, " /Times-Roman ff 20 scf sf");
        append_list(obj, " 0.000 0.000 0.000 rgb 1 lw");
        append_list(obj, " 60 820 m (2.0) sh");
        append_list(obj, "%");
        /* half for swapping rectangular left position */
        append_list(obj, "% Label for swapping - half");
        append_list(obj, " /Times-Roman ff 20 scf sf");
        append_list(obj, " 0.000 0.000 0.000 rgb 1 lw");
        append_list(obj, " 60 480 m (1.0) sh");
        append_list(obj, "%");
        /* zero for swapping rectangular left position */
        append_list(obj, "% Label for swapping - zero");
        append_list(obj, " /Times-Roman ff 20 scf sf");
        append_list(obj, " 0.000 0.000 0.000 rgb 1 lw");
        append_list(obj, " 70 130 m (0) sh");
        append_list(obj, "%");
        /* graph legend strings for swapping */
        append_list(obj, "% Graph legend for paging (strings)");
        append_list(obj, " /Times-Roman ff 20 scf sf");
        append_list(obj, " 0.000 0.000 0.000 rgb 1 lw");
        append_list(obj, " 1300 870 m (pswpin/s (blu)) sh");
        append_list(obj, " 0.000 0.000 0.000 rgb 1 lw");
        append_list(obj, " 1300 850 m (pswpout/s (grn)) sh");
        append_list(obj, "%");
    }
    /* for file ldv */
    else if (strcmp("ldavg", item ) == 0) {
        /* title */
        append_list(obj, "% Label for title");
        append_list(obj, " /Times-Roman ff 24 scf sf");
        append_list(obj, " 0.000 0.000 0.000 rgb 1 lw");
        snprintf(str_tmp, 50, " 45 2000 m (Created by sar-analyzer %d.%d.%d) sh",
            PROGRAM_VERSION, PROGRAM_RELEASE, PROGRAM_SUB_RELEASE);
        append_list(obj, str_tmp);
        append_list(obj, "stroke");
        append_list(obj, "%");

        /* title of ldavg */
        append_list(obj, "% Label for ldavg");
        append_list(obj, " /Times-Roman ff 36 scf sf");
        append_list(obj, " 0.000 0.000 0.000 rgb 1 lw");
        append_list(obj, " 100 1930 m (ldavg) sh");
        append_list(obj, "%");
        /* full for ldavg rectangular left position */
        append_list(obj, "% Label for ldavg - full");
        append_list(obj, " /Times-Roman ff 20 scf sf");
        append_list(obj, " 0.000 0.000 0.000 rgb 1 lw");
        append_list(obj, " 60 1890 m (50) sh");
        append_list(obj, " 1.000 0.000 0.000 rgb 1 lw");
        append_list(obj, " 35 1875 m (3,000) sh");
        append_list(obj, "%");
        /* half for ldavg rectangular left position */
        append_list(obj, "% Label for ldavg - half");
        append_list(obj, " /Times-Roman ff 20 scf sf");
        append_list(obj, " 0.000 0.000 0.000 rgb 1 lw");
        append_list(obj, " 60 1550 m (25) sh");
        append_list(obj, " 1.000 0.000 0.000 rgb 1 lw");
        append_list(obj, " 35 1535 m (1,500) sh");
        append_list(obj, "%");
        /* zero for ldavg rectangular left position */
        append_list(obj, "% Label for ldavg - zero");
        append_list(obj, " /Times-Roman ff 20 scf sf");
        append_list(obj, " 0.000 0.000 0.000 rgb 1 lw");
        append_list(obj, " 60 1190 m (0) sh");
        append_list(obj, "%");
        /* graph legend strings for ldavg */
        append_list(obj, "% Graph legend for ldavg (strings)");
        append_list(obj, " /Times-Roman ff 20 scf sf");
        append_list(obj, " 0.000 0.000 0.000 rgb 1 lw");
        append_list(obj, " 1300 1990 m (runq-sz (blu)) sh");
        append_list(obj, " 0.000 0.000 0.000 rgb 1 lw");
        append_list(obj, " 1300 1970 m (plist-sz (red)) sh");
        append_list(obj, " 0.000 0.000 0.000 rgb 1 lw");
        append_list(obj, " 1300 1950 m (ldavg-1 (grn)) sh");
        append_list(obj, " 0.000 0.000 0.000 rgb 1 lw");
        append_list(obj, " 1300 1930 m (ldavg-5 (sbl)) sh");
        append_list(obj, " 0.000 0.000 0.000 rgb 1 lw");
        append_list(obj, " 1300 1910 m (ldavg-15 (blk)) sh");
        append_list(obj, "%");

        /* title of tasks */
        append_list(obj, "% Label for tasks");
        append_list(obj, " /Times-Roman ff 36 scf sf");
        append_list(obj, " 0.000 0.000 0.000 rgb 1 lw");
        append_list(obj, " 100 860 m (tasks) sh");
        append_list(obj, "%" );
        /* full for tasks rectangular left position */
        append_list(obj, "% Label for tasks - full");
        append_list(obj, " /Times-Roman ff 20 scf sf");
        append_list(obj, " 0.000 0.000 1.000 rgb 1 lw");
        append_list(obj, " 50 820 m (500) sh");
        append_list(obj, " 0.000 1.000 0.000 rgb 1 lw");
        append_list(obj, " 15 800 m (100,000) sh");
        append_list(obj, "%" );
        /* half for tasks rectangular left position */
        append_list(obj, "% Label for tasks - half");
        append_list(obj, " /Times-Roman ff 20 scf sf");
        append_list(obj, " 0.000 0.000 1.000 rgb 1 lw");
        append_list(obj, " 50 480 m (250) sh");
        append_list(obj, " 0.000 1.000 0.000 rgb 1 lw");
        append_list(obj, " 25 460 m (50,000) sh");
        append_list(obj, "%");
        /* zero for tasks rectangular left position */
        append_list(obj, "% Label for tasks - zero");
        append_list(obj, " /Times-Roman ff 20 scf sf");
        append_list(obj, " 0.000 0.000 0.000 rgb 1 lw");
        append_list(obj, " 65 130 m (0) sh");
        append_list(obj, "%" );
        /* graph legend strings for tasks */
        append_list(obj, "% Graph legend for tasks (strings)");
        append_list(obj, " /Times-Roman ff 20 scf sf");
        append_list(obj, " 0.000 0.000 0.000 rgb 1 lw");
        append_list(obj, " 1300 870 m (proc/s (blu)) sh");
        append_list(obj, " 0.000 0.000 0.000 rgb 1 lw");
        append_list(obj, " 1300 850 m (cswch/s (grn)) sh");
        append_list(obj, "%");
    }
    /* for file ior */
    else if (strcmp("io_transfer_rate", item ) == 0) {
        /* title */
        append_list(obj, "% Label for title");
        append_list(obj, " /Times-Roman ff 24 scf sf");
        append_list(obj, " 0.000 0.000 0.000 rgb 1 lw");
        snprintf(str_tmp, 50, " 45 2000 m (Created by sar-analyzer %d.%d.%d) sh",
            PROGRAM_VERSION, PROGRAM_RELEASE, PROGRAM_SUB_RELEASE);
        append_list(obj, str_tmp);
        append_list(obj, "stroke");
        append_list(obj, "%");

        /* title of io transfer rate */
        append_list(obj, "% Label for io transfer rate");
        append_list(obj, " /Times-Roman ff 24 scf sf");
        append_list(obj, " 0.000 0.000 0.000 rgb 1 lw");
        append_list(obj, " 100 1930 m (io transfer rate) sh");
        append_list(obj, "%");
        /* full for io transfer rate rectangular left position */
        append_list(obj, "% Label for io transfer rate - full");
        append_list(obj, " /Times-Roman ff 20 scf sf");
        append_list(obj, " 0.000 0.000 1.000 rgb 1 lw");
        append_list(obj, " 35 1900 m (1,000) sh");
        append_list(obj, " 0.000 1.000 0.000 rgb 1 lw");
        append_list(obj, " 25 1885 m (10,000) sh");
        append_list(obj, " 1.000 0.000 0.000 rgb 1 lw");
        append_list(obj, " 25 1870 m (30,000) sh");
        append_list(obj, "%");
        /* half for io transfer rate rectangular left position */
        append_list(obj, "% Label for io transfer rate - half");
        append_list(obj, " /Times-Roman ff 20 scf sf");
        append_list(obj, " 0.000 0.000 1.000 rgb 1 lw");
        append_list(obj, " 50 1560 m (500) sh");
        append_list(obj, " 0.000 1.000 0.000 rgb 1 lw");
        append_list(obj, " 35 1545 m (5,000) sh");
        append_list(obj, " 1.000 0.000 0.000 rgb 1 lw");
        append_list(obj, " 25 1530 m (15,000) sh");
        append_list(obj, "%");
        /* zero for io transfer rate rectangular left position */
        append_list(obj, "% Label for io transfer rate - zero");
        append_list(obj, " /Times-Roman ff 24 scf sf");
        append_list(obj, " 0.000 0.000 0.000 rgb 1 lw");
        append_list(obj, " 25 1185 m (0) sh");
        append_list(obj, "%" );
        /* graph legend strings for io transfer rate */
        append_list(obj, "% Graph legend for io transfer rate (strings)");
        append_list(obj, " /Times-Roman ff 20 scf sf");
        append_list(obj, " 0.000 0.000 0.000 rgb 1 lw");
        append_list(obj, " 1300 1950 m (tps (blu)) sh");
        append_list(obj, " 0.000 0.000 0.000 rgb 1 lw");
        append_list(obj, " 1300 1930 m (bread/s (grn)) sh");
        append_list(obj, " 0.000 0.000 0.000 rgb 1 lw");
        append_list(obj, " 1300 1910 m (bwrtn/s (red)) sh");
        append_list(obj, "%");

        /* title of kernel table */
        append_list(obj, "% Label for kernel table");
        append_list(obj, " /Times-Roman ff 24 scf sf");
        append_list(obj, " 0.000 0.000 0.000 rgb 1 lw");
        append_list(obj, " 100 860 m (kernel table) sh");
        append_list(obj, "%");
        /* full for kernel table rectangular left position */
        append_list(obj, "% Label for kernel table - full");
        append_list(obj, " /Times-Roman ff 20 scf sf");
        append_list(obj, " 0.000 0.000 0.000 rgb 1 lw");
        append_list(obj, " 5 820 m (2,000,000) sh");
        append_list(obj, " 1.000 0.000 0.000 rgb 1 lw");
        append_list(obj, " 20 800 m (100,000) sh");
        append_list(obj, "%");
        /* half for kernel table rectangular left position */
        append_list(obj, "% Label for kernel table - half");
        append_list(obj, " /Times-Roman ff 20 scf sf");
        append_list(obj, " 0.000 0.000 0.000 rgb 1 lw");
        append_list(obj, " 5 480 m (1,000,000) sh");
        append_list(obj, " 1.000 0.000 0.000 rgb 1 lw");
        append_list(obj, " 30 460 m (50,000) sh");
        append_list(obj, "%" );
        /* zero for kernel table rectangular left position */
        append_list(obj, "% Label for kernel table - zero");
        append_list(obj, " /Times-Roman ff 20 scf sf");
        append_list(obj, " 0.000 0.000 0.000 rgb 1 lw");
        append_list(obj, " 65 130 m (0) sh");
        append_list(obj, "%");
        /* graph legend strings for kernel table */
        append_list(obj, "% Graph legend for kernel table (strings)");
        append_list(obj, " /Times-Roman ff 20 scf sf");
        append_list(obj, " 0.000 0.000 0.000 rgb 1 lw");
        append_list(obj, " 1300 890 m (dentunusd (blu)) sh");
        append_list(obj, " 0.000 0.000 0.000 rgb 1 lw");
        append_list(obj, " 1300 870 m (file-nr (red)) sh");
        append_list(obj, " 0.000 0.000 0.000 rgb 1 lw");
        append_list(obj, " 1300 850 m (inode-nr (grn)) sh");
        append_list(obj, "%");
    }
    return 0;
}
