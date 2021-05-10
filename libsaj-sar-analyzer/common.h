/*
 *  common.h - common definitions
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
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../common/global.h" 

#ifndef SAJ_COMMON_H
#define SAJ_COMMON_H

/* ---------- macros ( tweak if needed ) ---------- */
#define TITLE_TOKEN_LIMIT 10 

/* the maximum line length of file name */
#define MAX_FULL_PATH_LENGTH  512 

/* maximum core numbers to be analyzed */
#define MAX_CORE_NUMBERS  70 

/* maximum date string */
#define MAX_DATE_STRINGS  40 

/* maximum block device numbers to be analyzed ( minus 1 )*/
#define MAX_BLOCK_DEVICE_NUMBERS  65  /* we save it to 64 */

/* maximum network device numbers to be analyzed */
#define MAX_NETWORK_DEVICE_NUMBERS  64 /* hopefully 1025, because NI_MAXHOST is 1025, but we save it */

/* the maximum line length of directory name */
#define MAX_DIR_NAME_LENGTH  255 

/* maximum device string */
#define MAX_DEVICE_STRINGS  50 

/* maximum network device string */
#define MAX_NETWORK_DEVICE_STRINGS  50 

/* data directory which stores analyzed result data */
#define SAR_ANALYZER_RESULT_DIR  "sar-analyzer-results"

/*
 * Types for Columns, Dates, Data is needed.
 */

/*  -------------------- Column Structures Types -------------------- */

/*
 *  This is the type for CPU utilization column data 
 *  when analyzing with -u
 *  data type shoud be int
 */
typedef struct
{
    /* number of column of CPU */
    int CPU;
    /* number of column of %usr */
    int cpu_usr;
    /* number of column of %sys */
    int cpu_sys;
    /* number of column of %iowait */
    int cpu_iowait;
    /* number of column of %idle */
    int cpu_idle;

} cpu_column_data;

/*
 *  This is the type for task creation and system switching activity column data
 *  when analyzing with -w 
 *  data type shoud be int
 */
typedef struct
{
    /* number of column of proc */
    int proc;
    /* number of column of cswch */
    int cswch;

} task_column_data;

/*
 *  This is the type for swapping statistics 
 *  when analyzing with -W 
 *  data type shoud be int
 */
typedef struct
{
    /* number of column of pswpin/s */
    int pswpin;
    /* number of column of pswpout/s */
    int pswpout;

} pswap_column_data;

/*
 *  This is the type for paging sttistics column data
 *  when analyzing with -B 
 *  data type shoud be int
 */
typedef struct
{
    /* number of column of pgpgin */
    int pgpgin;
    /* number of column of pgpgout */
    int pgpgout;
    /* number of column of fault */
    int fault;
    /* number of column of majflt */
    int majflt;
    /* number of column of vmeff */
    int vmeff;

} paging_column_data;

/*
 *  This is the type for I/O and transfer rate sttistics column data
 *  when analyzing with -b 
 *  data type shoud be int
 */
typedef struct
{
    /* number of column of tps */
    int tps;
    /* number of column of bread/s */
    int bread;
    /* number of column of bwrtn/s */
    int bwrtn;

} io_transfer_rate_column_data;

/*
 *  This is the type for memory utilization sttistics column data
 *  when analyzing with -r 
 *  data type shoud be int
 */
typedef struct
{
    /* number of column of memused */
    int memused;
    /* number of column of kbcommit */
    int kbcommit;
    /* number of column of commit */
    int commit;

} memory_column_data;

/*
 *  This is the type for swap space utilization statistics 
 *  when analyzing with -S 
 *  data type shoud be int
 */
typedef struct
{
    /* number of column of swpused */
    int swpused;

} swap_column_data;

/*
 *  This is the type for status of inode, file and other kernel tables 
 *  when analyzing with -v 
 *  data type shoud be int
 */
typedef struct
{
    /* number of column of dentunusd */
    int dentunusd;
    /* number of column of file-nr */
    int file;
    /* number of column of inode-nr */
    int inode;

} kernel_table_column_data;

/*
 *  This is the type for queue length and load averages column data 
 *  when analyzing with -q 
 *  data type shoud be int
 */
typedef struct
{
    /* number of column of runq-sz */
    int runq_sz;
    /* number of column of plist-sz */
    int plist_sz;
    /* number of column of ldavg-1 */
    int ldavg_one;
    /* number of column of ldavg-5 */
    int ldavg_five;
    /* number of column of ldavg-15 */
    int ldavg_15;

} ldavg_column_data;

/*
 *  This is the type for activity for each block device column data
 *  when analyzing with -d 
 *  data type shoud be int
 */
typedef struct
{
    /* number of column of areqsz */
    int areqsz;
    /* number of column of util */
    int util;

} block_device_column_data;

/*
 *  This is the type for network statistics 
 *  when analyzing with -n 
 *  data type shoud be int
 */
typedef struct
{
    /* number of column of rxpck/s */
    int rxpck;
    /* number of column of txpck/s */
    int txpck;
    /* number of column of rxkB/s */
    int rxkb;
    /* number of column of txkB/s */
    int txkb;
    /* number of column of rxerr/s */
    int rxerr;
    /* number of column of txerr/s */
    int txerr;
    /* number of column of rxdrop/s */
    int rxdrop;
    /* number of column of txdrop/s */
    int txdrop;

} network_column_data;

/*  -------------------- end Column Structures Types -------------------- */

/*  -------------------- Date Structures Types -------------------- */

/*
 *  This is the date type for CPU utilization 
 *  when analyzing with -u
 */
typedef struct
{
    /* date string related to cpu_usr */
    char cpu_usr_date[MAX_CORE_NUMBERS +1][MAX_DATE_STRINGS];
    /* date string related to cpu_sys */
    char cpu_sys_date[MAX_CORE_NUMBERS +1][MAX_DATE_STRINGS];
    /* date string related to cpu_iowait */
    char cpu_iowait_date[MAX_CORE_NUMBERS +1][MAX_DATE_STRINGS];
    /* date string related to cpu_idle */
    char cpu_idle_date[MAX_CORE_NUMBERS +1][MAX_DATE_STRINGS];
    /* time string related to cpu_usr */
    char cpu_usr_time[MAX_CORE_NUMBERS +1][MAX_DATE_STRINGS];
    /* time string related to cpu_sys */
    char cpu_sys_time[MAX_CORE_NUMBERS +1][MAX_DATE_STRINGS];
    /* time string related to cpu_iowait */
    char cpu_iowait_time[MAX_CORE_NUMBERS +1][MAX_DATE_STRINGS];
    /* time string related to cpu_idle */
    char cpu_idle_time[MAX_CORE_NUMBERS +1][MAX_DATE_STRINGS];

} cpu_date;

typedef struct
{
    char cpu_usr_spike_date_each_file[MAX_ANALYZE_FILES +1][MAX_CORE_NUMBERS +1][MAX_DATE_STRINGS];
    char cpu_sys_spike_date_each_file[MAX_ANALYZE_FILES +1][MAX_CORE_NUMBERS +1][MAX_DATE_STRINGS];
    char cpu_iowait_spike_date_each_file[MAX_ANALYZE_FILES +1][MAX_CORE_NUMBERS +1][MAX_DATE_STRINGS];
    char cpu_idle_spike_date_each_file[MAX_ANALYZE_FILES +1][MAX_CORE_NUMBERS +1][MAX_DATE_STRINGS];
    char cpu_usr_spike_time_each_file[MAX_ANALYZE_FILES +1][MAX_CORE_NUMBERS +1][MAX_DATE_STRINGS];
    char cpu_sys_spike_time_each_file[MAX_ANALYZE_FILES +1][MAX_CORE_NUMBERS +1][MAX_DATE_STRINGS];
    char cpu_iowait_spike_time_each_file[MAX_ANALYZE_FILES +1][MAX_CORE_NUMBERS +1][MAX_DATE_STRINGS];
    char cpu_idle_spike_time_each_file[MAX_ANALYZE_FILES +1][MAX_CORE_NUMBERS +1][MAX_DATE_STRINGS];

    char cpu_usr_highest_date_each_file[MAX_ANALYZE_FILES +1][MAX_CORE_NUMBERS +1][MAX_DATE_STRINGS];
    char cpu_sys_highest_date_each_file[MAX_ANALYZE_FILES +1][MAX_CORE_NUMBERS +1][MAX_DATE_STRINGS];
    char cpu_iowait_highest_date_each_file[MAX_ANALYZE_FILES +1][MAX_CORE_NUMBERS +1][MAX_DATE_STRINGS];
    char cpu_idle_highest_date_each_file[MAX_ANALYZE_FILES +1][MAX_CORE_NUMBERS +1][MAX_DATE_STRINGS];
    char cpu_usr_highest_time_each_file[MAX_ANALYZE_FILES +1][MAX_CORE_NUMBERS +1][MAX_DATE_STRINGS];
    char cpu_sys_highest_time_each_file[MAX_ANALYZE_FILES +1][MAX_CORE_NUMBERS +1][MAX_DATE_STRINGS];
    char cpu_iowait_highest_time_each_file[MAX_ANALYZE_FILES +1][MAX_CORE_NUMBERS +1][MAX_DATE_STRINGS];
    char cpu_idle_highest_time_each_file[MAX_ANALYZE_FILES +1][MAX_CORE_NUMBERS +1][MAX_DATE_STRINGS];

    char cpu_usr_lowest_date_each_file[MAX_ANALYZE_FILES +1][MAX_CORE_NUMBERS +1][MAX_DATE_STRINGS];
    char cpu_sys_lowest_date_each_file[MAX_ANALYZE_FILES +1][MAX_CORE_NUMBERS +1][MAX_DATE_STRINGS];
    char cpu_iowait_lowest_date_each_file[MAX_ANALYZE_FILES +1][MAX_CORE_NUMBERS +1][MAX_DATE_STRINGS];
    char cpu_idle_lowest_date_each_file[MAX_ANALYZE_FILES +1][MAX_CORE_NUMBERS +1][MAX_DATE_STRINGS];
    char cpu_usr_lowest_time_each_file[MAX_ANALYZE_FILES +1][MAX_CORE_NUMBERS +1][MAX_DATE_STRINGS];
    char cpu_sys_lowest_time_each_file[MAX_ANALYZE_FILES +1][MAX_CORE_NUMBERS +1][MAX_DATE_STRINGS];
    char cpu_iowait_lowest_time_each_file[MAX_ANALYZE_FILES +1][MAX_CORE_NUMBERS +1][MAX_DATE_STRINGS];
    char cpu_idle_lowest_time_each_file[MAX_ANALYZE_FILES +1][MAX_CORE_NUMBERS +1][MAX_DATE_STRINGS];

} cpu_date_spike_each_file;

typedef struct
{
    char cpu_usr_time_span_spike_date_each_file[MAX_ANALYZE_FILES +1][MAX_CORE_NUMBERS +1][MAX_DATE_STRINGS];
    char cpu_sys_time_span_spike_date_each_file[MAX_ANALYZE_FILES +1][MAX_CORE_NUMBERS +1][MAX_DATE_STRINGS];
    char cpu_iowait_time_span_spike_date_each_file[MAX_ANALYZE_FILES +1][MAX_CORE_NUMBERS +1][MAX_DATE_STRINGS];
    char cpu_idle_time_span_spike_date_each_file[MAX_ANALYZE_FILES +1][MAX_CORE_NUMBERS +1][MAX_DATE_STRINGS];
    char cpu_usr_time_span_spike_time_each_file[MAX_ANALYZE_FILES +1][MAX_CORE_NUMBERS +1][MAX_DATE_STRINGS];
    char cpu_sys_time_span_spike_time_each_file[MAX_ANALYZE_FILES +1][MAX_CORE_NUMBERS +1][MAX_DATE_STRINGS];
    char cpu_iowait_time_span_spike_time_each_file[MAX_ANALYZE_FILES +1][MAX_CORE_NUMBERS +1][MAX_DATE_STRINGS];
    char cpu_idle_time_span_spike_time_each_file[MAX_ANALYZE_FILES +1][MAX_CORE_NUMBERS +1][MAX_DATE_STRINGS];

    char cpu_usr_time_span_highest_date_each_file[MAX_ANALYZE_FILES +1][MAX_CORE_NUMBERS +1][MAX_DATE_STRINGS];
    char cpu_sys_time_span_highest_date_each_file[MAX_ANALYZE_FILES +1][MAX_CORE_NUMBERS +1][MAX_DATE_STRINGS];
    char cpu_iowait_time_span_highest_date_each_file[MAX_ANALYZE_FILES +1][MAX_CORE_NUMBERS +1][MAX_DATE_STRINGS];
    char cpu_idle_time_span_highest_date_each_file[MAX_ANALYZE_FILES +1][MAX_CORE_NUMBERS +1][MAX_DATE_STRINGS];
    char cpu_usr_time_span_highest_time_each_file[MAX_ANALYZE_FILES +1][MAX_CORE_NUMBERS +1][MAX_DATE_STRINGS];
    char cpu_sys_time_span_highest_time_each_file[MAX_ANALYZE_FILES +1][MAX_CORE_NUMBERS +1][MAX_DATE_STRINGS];
    char cpu_iowait_time_span_highest_time_each_file[MAX_ANALYZE_FILES +1][MAX_CORE_NUMBERS +1][MAX_DATE_STRINGS];
    char cpu_idle_time_span_highest_time_each_file[MAX_ANALYZE_FILES +1][MAX_CORE_NUMBERS +1][MAX_DATE_STRINGS];

    char cpu_usr_time_span_lowest_date_each_file[MAX_ANALYZE_FILES +1][MAX_CORE_NUMBERS +1][MAX_DATE_STRINGS];
    char cpu_sys_time_span_lowest_date_each_file[MAX_ANALYZE_FILES +1][MAX_CORE_NUMBERS +1][MAX_DATE_STRINGS];
    char cpu_iowait_time_span_lowest_date_each_file[MAX_ANALYZE_FILES +1][MAX_CORE_NUMBERS +1][MAX_DATE_STRINGS];
    char cpu_idle_time_span_lowest_date_each_file[MAX_ANALYZE_FILES +1][MAX_CORE_NUMBERS +1][MAX_DATE_STRINGS];
    char cpu_usr_time_span_lowest_time_each_file[MAX_ANALYZE_FILES +1][MAX_CORE_NUMBERS +1][MAX_DATE_STRINGS];
    char cpu_sys_time_span_lowest_time_each_file[MAX_ANALYZE_FILES +1][MAX_CORE_NUMBERS +1][MAX_DATE_STRINGS];
    char cpu_iowait_time_span_lowest_time_each_file[MAX_ANALYZE_FILES +1][MAX_CORE_NUMBERS +1][MAX_DATE_STRINGS];
    char cpu_idle_time_span_lowest_time_each_file[MAX_ANALYZE_FILES +1][MAX_CORE_NUMBERS +1][MAX_DATE_STRINGS];

} cpu_date_time_span_spike_each_file;

/*
 *  This is the date type for task creation and system switching activity
 *  when analyzing with -w 
 */
typedef struct
{
    /* date string related to proc */
    char proc_date[MAX_DATE_STRINGS];
    /* date string related to cswch */
    char cswch_date[MAX_DATE_STRINGS];
    /* time string related to proc */
    char proc_time[MAX_DATE_STRINGS];
    /* time string related to cswch */
    char cswch_time[MAX_DATE_STRINGS];

} task_date;

typedef struct
{
    char proc_spike_date_each_file[MAX_ANALYZE_FILES +1] [MAX_DATE_STRINGS];
    char cswch_spike_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char proc_spike_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char cswch_spike_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];

    char proc_highest_date_each_file[MAX_ANALYZE_FILES +1] [MAX_DATE_STRINGS];
    char cswch_highest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char proc_highest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char cswch_highest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];

    char proc_lowest_date_each_file[MAX_ANALYZE_FILES +1] [MAX_DATE_STRINGS];
    char cswch_lowest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char proc_lowest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char cswch_lowest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];

} task_date_spike_each_file;

typedef struct
{
    char proc_time_span_spike_date_each_file[MAX_ANALYZE_FILES +1] [MAX_DATE_STRINGS];
    char cswch_time_span_spike_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char proc_time_span_spike_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char cswch_time_span_spike_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];

    char proc_time_span_highest_date_each_file[MAX_ANALYZE_FILES +1] [MAX_DATE_STRINGS];
    char cswch_time_span_highest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char proc_time_span_highest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char cswch_time_span_highest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];

    char proc_time_span_lowest_date_each_file[MAX_ANALYZE_FILES +1] [MAX_DATE_STRINGS];
    char cswch_time_span_lowest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char proc_time_span_lowest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char cswch_time_span_lowest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];

} task_date_time_span_spike_each_file;

/*
 *  This is the date type for swapping statistics 
 *  when analyzing with -W 
 */
typedef struct
{
    /* date string related to pswpin/s */
    char pswpin_date[MAX_DATE_STRINGS];
    /* date string related to pswpout/s */
    char pswpout_date[MAX_DATE_STRINGS];
    /* time string related to pswpin/s */
    char pswpin_time[MAX_DATE_STRINGS];
    /* time string related to pswpout/s */
    char pswpout_time[MAX_DATE_STRINGS];

} pswap_date;

typedef struct
{
    char pswpin_spike_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char pswpout_spike_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char pswpin_spike_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char pswpout_spike_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];

    char pswpin_highest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char pswpout_highest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char pswpin_highest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char pswpout_highest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];

    char pswpin_lowest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char pswpout_lowest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char pswpin_lowest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char pswpout_lowest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];

} pswap_date_spike_each_file;

typedef struct
{
    char pswpin_time_span_spike_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char pswpout_time_span_spike_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char pswpin_time_span_spike_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char pswpout_time_span_spike_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];

    char pswpin_time_span_highest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char pswpout_time_span_highest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char pswpin_time_span_highest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char pswpout_time_span_highest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];

    char pswpin_time_span_lowest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char pswpout_time_span_lowest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char pswpin_time_span_lowest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char pswpout_time_span_lowest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];

} pswap_date_time_span_spike_each_file;

/*
 *  This is the date type for paging staistics
 *  when analyzing with -B 
 */
typedef struct
{
    /* date string related to pgpgin */
    char pgpgin_date[MAX_DATE_STRINGS];
    /* date string related to pgpgout */
    char pgpgout_date[MAX_DATE_STRINGS];
    /* date string related to fault */
    char fault_date[MAX_DATE_STRINGS];
    /* date string related to majflt */
    char majflt_date[MAX_DATE_STRINGS];
    /* date string related to vmeff */
    char vmeff_date[MAX_DATE_STRINGS];
    /* time string related to pgpgin */
    char pgpgin_time[MAX_DATE_STRINGS];
    /* time string related to pgpgout */
    char pgpgout_time[MAX_DATE_STRINGS];
    /* time string related to fault */
    char fault_time[MAX_DATE_STRINGS];
    /* time string related to majflt */
    char majflt_time[MAX_DATE_STRINGS];
    /* time string related to vmeff */
    char vmeff_time[MAX_DATE_STRINGS];

} paging_date;

typedef struct
{
    char pgpgin_spike_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char pgpgout_spike_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char fault_spike_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char majflt_spike_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char vmeff_spike_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char pgpgin_spike_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char pgpgout_spike_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char fault_spike_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char majflt_spike_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char vmeff_spike_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];

    char pgpgin_highest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char pgpgout_highest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char fault_highest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char majflt_highest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char vmeff_highest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char pgpgin_highest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char pgpgout_highest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char fault_highest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char majflt_highest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char vmeff_highest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];

    char pgpgin_lowest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char pgpgout_lowest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char fault_lowest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char majflt_lowest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char vmeff_lowest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char pgpgin_lowest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char pgpgout_lowest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char fault_lowest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char majflt_lowest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char vmeff_lowest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];

} paging_date_spike_each_file;

typedef struct
{
    char pgpgin_time_span_spike_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char pgpgout_time_span_spike_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char fault_time_span_spike_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char majflt_time_span_spike_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char vmeff_time_span_spike_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char pgpgin_time_span_spike_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char pgpgout_time_span_spike_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char fault_time_span_spike_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char majflt_time_span_spike_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char vmeff_time_span_spike_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];

    char pgpgin_time_span_highest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char pgpgout_time_span_highest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char fault_time_span_highest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char majflt_time_span_highest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char vmeff_time_span_highest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char pgpgin_time_span_highest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char pgpgout_time_span_highest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char fault_time_span_highest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char majflt_time_span_highest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char vmeff_time_span_highest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];

    char pgpgin_time_span_lowest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char pgpgout_time_span_lowest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char fault_time_span_lowest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char majflt_time_span_lowest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char vmeff_time_span_lowest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char pgpgin_time_span_lowest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char pgpgout_time_span_lowest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char fault_time_span_lowest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char majflt_time_span_lowest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char vmeff_time_span_lowest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];

} paging_date_time_span_spike_each_file;

/*
 *  This is the date type for I/O and transfer rate staistics
 *  when analyzing with -b 
 */
typedef struct
{
    /* date string related to tps */
    char tps_date[MAX_DATE_STRINGS];
    /* date string related to bread */
    char bread_date[MAX_DATE_STRINGS];
    /* date string related to bwrtn */
    char bwrtn_date[MAX_DATE_STRINGS];
    /* time string related to tps */
    char tps_time[MAX_DATE_STRINGS];
    /* time string related to bread */
    char bread_time[MAX_DATE_STRINGS];
    /* time string related to bwrtn */
    char bwrtn_time[MAX_DATE_STRINGS];

} io_transfer_rate_date;

typedef struct
{
    char tps_spike_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char bread_spike_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char bwrtn_spike_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char tps_spike_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char bread_spike_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char bwrtn_spike_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];

    char tps_highest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char bread_highest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char bwrtn_highest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char tps_highest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char bread_highest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char bwrtn_highest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];

    char tps_lowest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char bread_lowest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char bwrtn_lowest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char tps_lowest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char bread_lowest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char bwrtn_lowest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];

} io_transfer_rate_date_spike_each_file;

typedef struct
{
    char tps_time_span_spike_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char bread_time_span_spike_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char bwrtn_time_span_spike_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char tps_time_span_spike_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char bread_time_span_spike_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char bwrtn_time_span_spike_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];

    char tps_time_span_highest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char bread_time_span_highest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char bwrtn_time_span_highest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char tps_time_span_highest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char bread_time_span_highest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char bwrtn_time_span_highest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];

    char tps_time_span_lowest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char bread_time_span_lowest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char bwrtn_time_span_lowest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char tps_time_span_lowest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char bread_time_span_lowest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char bwrtn_time_span_lowest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];

} io_transfer_rate_date_time_span_spike_each_file;

/*
 *  This is the date type for memory utilization staistics
 *  when analyzing with -r 
 */
typedef struct
{
    /* date string related to memused */
    char memused_date[MAX_DATE_STRINGS];
    /* date string related to kbcommit */
    char kbcommit_date[MAX_DATE_STRINGS];
    /* date string related to commit */
    char commit_date[MAX_DATE_STRINGS];
    /* time string related to memused */
    char memused_time[MAX_DATE_STRINGS];
    /* time string related to kbcommit */
    char kbcommit_time[MAX_DATE_STRINGS];
    /* time string related to commit */
    char commit_time[MAX_DATE_STRINGS];

} memory_date;

typedef struct
{
    char memused_spike_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char kbcommit_spike_date_each_file[MAX_ANALYZE_FILES +1] [MAX_DATE_STRINGS];
    char commit_spike_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char memused_spike_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char kbcommit_spike_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char commit_spike_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];

    char memused_highest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char kbcommit_highest_date_each_file[MAX_ANALYZE_FILES +1] [MAX_DATE_STRINGS];
    char commit_highest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char memused_highest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char kbcommit_highest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char commit_highest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];

    char memused_lowest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char kbcommit_lowest_date_each_file[MAX_ANALYZE_FILES +1] [MAX_DATE_STRINGS];
    char commit_lowest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char memused_lowest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char kbcommit_lowest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char commit_lowest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];

} memory_date_spike_each_file;

typedef struct
{
    char memused_time_span_spike_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char kbcommit_time_span_spike_date_each_file[MAX_ANALYZE_FILES +1] [MAX_DATE_STRINGS];
    char commit_time_span_spike_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char memused_time_span_spike_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char kbcommit_time_span_spike_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char commit_time_span_spike_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];

    char memused_time_span_highest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char kbcommit_time_span_highest_date_each_file[MAX_ANALYZE_FILES +1] [MAX_DATE_STRINGS];
    char commit_time_span_highest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char memused_time_span_highest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char kbcommit_time_span_highest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char commit_time_span_highest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];

    char memused_time_span_lowest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char kbcommit_time_span_lowest_date_each_file[MAX_ANALYZE_FILES +1] [MAX_DATE_STRINGS];
    char commit_time_span_lowest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char memused_time_span_lowest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char kbcommit_time_span_lowest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char commit_time_span_lowest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];

} memory_date_time_span_spike_each_file;

/*
 *  This is the date type for activity for swap space utilization statistics
 *  when analyzing with -S 
 */
typedef struct
{
    /* date string related to swpused */
    char swpused_date[MAX_DATE_STRINGS];
    char swpused_time[MAX_DATE_STRINGS];

} swap_date;

typedef struct
{
    char swpused_spike_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char swpused_spike_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];

    char swpused_highest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char swpused_highest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];

    char swpused_lowest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char swpused_lowest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];

} swap_date_spike_each_file;

typedef struct
{
    char swpused_time_span_spike_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char swpused_time_span_spike_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];

    char swpused_time_span_highest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char swpused_time_span_highest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];

    char swpused_time_span_lowest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char swpused_time_span_lowest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];

} swap_date_time_span_spike_each_file;

/*
 *  This is the date type for status of inode, file and other kernel tables 
 *  when analyzing with -v 
 */
typedef struct
{
    /* date string related to dentunusd */
    char dentunusd_date[MAX_DATE_STRINGS];
    /* date string related to file-nr */
    char file_date[MAX_DATE_STRINGS];
    /* date string related to inode-nr */
    char inode_date[MAX_DATE_STRINGS];
    /* time string related to dentunusd */
    char dentunusd_time[MAX_DATE_STRINGS];
    /* time string related to file-nr */
    char file_time[MAX_DATE_STRINGS];
    /* time string related to inode-nr */
    char inode_time[MAX_DATE_STRINGS];

} kernel_table_date;

typedef struct
{
    char dentunusd_spike_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char file_spike_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char inode_spike_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char dentunusd_spike_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char file_spike_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char inode_spike_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];

    char dentunusd_highest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char file_highest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char inode_highest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char dentunusd_highest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char file_highest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char inode_highest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];

    char dentunusd_lowest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char file_lowest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char inode_lowest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char dentunusd_lowest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char file_lowest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char inode_lowest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];

} kernel_table_date_spike_each_file;

typedef struct
{
    char dentunusd_time_span_spike_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char file_time_span_spike_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char inode_time_span_spike_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char dentunusd_time_span_spike_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char file_time_span_spike_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char inode_time_span_spike_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];

    char dentunusd_time_span_highest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char file_time_span_highest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char inode_time_span_highest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char dentunusd_time_span_highest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char file_time_span_highest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char inode_time_span_highest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];

    char dentunusd_time_span_lowest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char file_time_span_lowest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char inode_time_span_lowest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char dentunusd_time_span_lowest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char file_time_span_lowest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char inode_time_span_lowest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];

} kernel_table_date_time_span_spike_each_file;

/*
 *  This is the date type for queue length and load averages 
 *  when analyzing with -q 
 */
typedef struct
{
    /* date string related to runq_sz */
    char runq_sz_date[MAX_DATE_STRINGS];
    /* date string related to plist_sz */
    char plist_sz_date[MAX_DATE_STRINGS];
    /* date string related to ldavg_1_sz */
    char ldavg_one_date[MAX_DATE_STRINGS];
    /* date string related to ldavg_5_sz */
    char ldavg_five_date[MAX_DATE_STRINGS];
    /* date string related to ldavg_15_sz */
    char ldavg_15_date[MAX_DATE_STRINGS];
    /* time string related to runq_sz */
    char runq_sz_time[MAX_DATE_STRINGS];
    /* time string related to plist_sz */
    char plist_sz_time[MAX_DATE_STRINGS];
    /* time string related to ldavg_1_sz */
    char ldavg_one_time[MAX_DATE_STRINGS];
    /* time string related to ldavg_5_sz */
    char ldavg_five_time[MAX_DATE_STRINGS];
    /* time string related to ldavg_15_sz */
    char ldavg_15_time[MAX_DATE_STRINGS];

} ldavg_date;

typedef struct
{
    char runq_sz_spike_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char plist_sz_spike_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char ldavg_one_spike_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char ldavg_five_spike_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char ldavg_15_spike_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char runq_sz_spike_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char plist_sz_spike_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char ldavg_one_spike_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char ldavg_five_spike_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char ldavg_15_spike_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];

    char runq_sz_highest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char plist_sz_highest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char ldavg_one_highest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char ldavg_five_highest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char ldavg_15_highest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char runq_sz_highest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char plist_sz_highest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char ldavg_one_highest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char ldavg_five_highest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char ldavg_15_highest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];

    char runq_sz_lowest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char plist_sz_lowest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char ldavg_one_lowest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char ldavg_five_lowest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char ldavg_15_lowest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char runq_sz_lowest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char plist_sz_lowest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char ldavg_one_lowest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char ldavg_five_lowest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char ldavg_15_lowest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];

} ldavg_date_spike_each_file;

typedef struct
{
    char runq_sz_time_span_spike_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char plist_sz_time_span_spike_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char ldavg_one_time_span_spike_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char ldavg_five_time_span_spike_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char ldavg_15_time_span_spike_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char runq_sz_time_span_spike_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char plist_sz_time_span_spike_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char ldavg_one_time_span_spike_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char ldavg_five_time_span_spike_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char ldavg_15_time_span_spike_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];

    char runq_sz_time_span_highest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char plist_sz_time_span_highest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char ldavg_one_time_span_highest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char ldavg_five_time_span_highest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char ldavg_15_time_span_highest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char runq_sz_time_span_highest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char plist_sz_time_span_highest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char ldavg_one_time_span_highest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char ldavg_five_time_span_highest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char ldavg_15_time_span_highest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];

    char runq_sz_time_span_lowest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char plist_sz_time_span_lowest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char ldavg_one_time_span_lowest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char ldavg_five_time_span_lowest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char ldavg_15_time_span_lowest_date_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char runq_sz_time_span_lowest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char plist_sz_time_span_lowest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char ldavg_one_time_span_lowest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char ldavg_five_time_span_lowest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];
    char ldavg_15_time_span_lowest_time_each_file[MAX_ANALYZE_FILES +1][MAX_DATE_STRINGS];

} ldavg_date_time_span_spike_each_file;

/*
 *  This is the date type for activity for each block device staistics
 *  when analyzing with -d 
 */
typedef struct
{
    /* date string related to areqsz */
    char areqsz_date[MAX_BLOCK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    /* date string related to areqsz */
    char util_date[MAX_BLOCK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    /* time string related to areqsz */
    char areqsz_time[MAX_BLOCK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    /* time string related to areqsz */
    char util_time[MAX_BLOCK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];

} block_device_date;

typedef struct
{
    char areqsz_spike_date_each_file[MAX_ANALYZE_FILES +1][MAX_BLOCK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char util_spike_date_each_file[MAX_ANALYZE_FILES +1][MAX_BLOCK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char areqsz_spike_time_each_file[MAX_ANALYZE_FILES +1][MAX_BLOCK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char util_spike_time_each_file[MAX_ANALYZE_FILES +1][MAX_BLOCK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];

    char areqsz_highest_date_each_file[MAX_ANALYZE_FILES +1][MAX_BLOCK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char util_highest_date_each_file[MAX_ANALYZE_FILES +1][MAX_BLOCK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char areqsz_highest_time_each_file[MAX_ANALYZE_FILES +1][MAX_BLOCK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char util_highest_time_each_file[MAX_ANALYZE_FILES +1][MAX_BLOCK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];

    char areqsz_lowest_date_each_file[MAX_ANALYZE_FILES +1][MAX_BLOCK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char util_lowest_date_each_file[MAX_ANALYZE_FILES +1][MAX_BLOCK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char areqsz_lowest_time_each_file[MAX_ANALYZE_FILES +1][MAX_BLOCK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char util_lowest_time_each_file[MAX_ANALYZE_FILES +1][MAX_BLOCK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];

} block_device_date_spike_each_file;

typedef struct
{
    char areqsz_time_span_spike_date_each_file[MAX_ANALYZE_FILES +1][MAX_BLOCK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char util_time_span_spike_date_each_file[MAX_ANALYZE_FILES +1][MAX_BLOCK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char areqsz_time_span_spike_time_each_file[MAX_ANALYZE_FILES +1][MAX_BLOCK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char util_time_span_spike_time_each_file[MAX_ANALYZE_FILES +1][MAX_BLOCK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];

    char areqsz_time_span_highest_date_each_file[MAX_ANALYZE_FILES +1][MAX_BLOCK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char util_time_span_highest_date_each_file[MAX_ANALYZE_FILES +1][MAX_BLOCK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char areqsz_time_span_highest_time_each_file[MAX_ANALYZE_FILES +1][MAX_BLOCK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char util_time_span_highest_time_each_file[MAX_ANALYZE_FILES +1][MAX_BLOCK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];

    char areqsz_time_span_lowest_date_each_file[MAX_ANALYZE_FILES +1][MAX_BLOCK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char util_time_span_lowest_date_each_file[MAX_ANALYZE_FILES +1][MAX_BLOCK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char areqsz_time_span_lowest_time_each_file[MAX_ANALYZE_FILES +1][MAX_BLOCK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char util_time_span_lowest_time_each_file[MAX_ANALYZE_FILES +1][MAX_BLOCK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];

} block_device_date_time_span_spike_each_file;

/*
 *  This is the date type for network statistics 
 *  when analyzing with -n 
 */
typedef struct
{
    /* date string related to rxpck/s */
    char rxpck_date[MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    /* date string related to txpck/s */
    char txpck_date[MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    /* date string related to rxkB/s */
    char rxkb_date[MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    /* date string related to txkB/s */
    char txkb_date[MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    /* date string related to rxerr/s */
    char rxerr_date[MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    /* date string related to txerr/s */
    char txerr_date[MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    /* date string related to rxdrop/s */
    char rxdrop_date[MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    /* date string related to txfrop/s */
    char txdrop_date[MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    /* time string related to rxpck/s */
    char rxpck_time[MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    /* time string related to txpck/s */
    char txpck_time[MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    /* time string related to rxkB/s */
    char rxkb_time[MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    /* time string related to txkB/s */
    char txkb_time[MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    /* time string related to rxerr/s */
    char rxerr_time[MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    /* time string related to txerr/s */
    char txerr_time[MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    /* time string related to rxdrop/s */
    char rxdrop_time[MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    /* time string related to txfrop/s */
    char txdrop_time[MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];

} network_date;

typedef struct
{
    char rxpck_spike_date_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char txpck_spike_date_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char rxkb_spike_date_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char txkb_spike_date_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char rxerr_spike_date_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char txerr_spike_date_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char rxdrop_spike_date_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char txdrop_spike_date_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char rxpck_spike_time_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char txpck_spike_time_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char rxkb_spike_time_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char txkb_spike_time_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char rxerr_spike_time_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char txerr_spike_time_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char rxdrop_spike_time_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char txdrop_spike_time_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];

    char rxpck_highest_date_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char txpck_highest_date_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char rxkb_highest_date_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char txkb_highest_date_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char rxerr_highest_date_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char txerr_highest_date_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char rxdrop_highest_date_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char txdrop_highest_date_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char rxpck_highest_time_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char txpck_highest_time_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char rxkb_highest_time_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char txkb_highest_time_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char rxerr_highest_time_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char txerr_highest_time_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char rxdrop_highest_time_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char txdrop_highest_time_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];

    char rxpck_lowest_date_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char txpck_lowest_date_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char rxkb_lowest_date_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char txkb_lowest_date_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char rxerr_lowest_date_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char txerr_lowest_date_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char rxdrop_lowest_date_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char txdrop_lowest_date_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char rxpck_lowest_time_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char txpck_lowest_time_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char rxkb_lowest_time_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char txkb_lowest_time_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char rxerr_lowest_time_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char txerr_lowest_time_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char rxdrop_lowest_time_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char txdrop_lowest_time_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];

    char rxpck_down_date_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char txpck_down_date_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char rxkb_down_date_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char txkb_down_date_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char rxerr_down_date_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char txerr_down_date_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char rxdrop_down_date_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char txdrop_down_date_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char rxpck_down_time_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char txpck_down_time_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char rxkb_down_time_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char txkb_down_time_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char rxerr_down_time_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char txerr_down_time_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char rxdrop_down_time_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char txdrop_down_time_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];

} network_date_spike_each_file;

typedef struct
{
    char rxpck_time_span_spike_date_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char txpck_time_span_spike_date_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char rxkb_time_span_spike_date_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char txkb_time_span_spike_date_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char rxerr_time_span_spike_date_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char txerr_time_span_spike_date_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char rxdrop_time_span_spike_date_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char txdrop_time_span_spike_date_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char rxpck_time_span_spike_time_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char txpck_time_span_spike_time_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char rxkb_time_span_spike_time_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char txkb_time_span_spike_time_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char rxerr_time_span_spike_time_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char txerr_time_span_spike_time_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char rxdrop_time_span_spike_time_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char txdrop_time_span_spike_time_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];

    char rxpck_time_span_highest_date_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char txpck_time_span_highest_date_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char rxkb_time_span_highest_date_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char txkb_time_span_highest_date_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char rxerr_time_span_highest_date_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char txerr_time_span_highest_date_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char rxdrop_time_span_highest_date_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char txdrop_time_span_highest_date_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char rxpck_time_span_highest_time_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char txpck_time_span_highest_time_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char rxkb_time_span_highest_time_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char txkb_time_span_highest_time_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char rxerr_time_span_highest_time_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char txerr_time_span_highest_time_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char rxdrop_time_span_highest_time_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char txdrop_time_span_highest_time_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];

    char rxpck_time_span_lowest_date_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char txpck_time_span_lowest_date_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char rxkb_time_span_lowest_date_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char txkb_time_span_lowest_date_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char rxerr_time_span_lowest_date_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char txerr_time_span_lowest_date_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char rxdrop_time_span_lowest_date_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char txdrop_time_span_lowest_date_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char rxpck_time_span_lowest_time_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char txpck_time_span_lowest_time_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char rxkb_time_span_lowest_time_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char txkb_time_span_lowest_time_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char rxerr_time_span_lowest_time_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char txerr_time_span_lowest_time_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char rxdrop_time_span_lowest_time_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];
    char txdrop_time_span_lowest_time_each_file[MAX_ANALYZE_FILES +1][MAX_NETWORK_DEVICE_NUMBERS +1][MAX_DATE_STRINGS];

} network_date_time_span_spike_each_file;

/*  -------------------- end Date Structures Types-------------------- */

/*  -------------------- Data Structures Types-------------------- */

/*
 *  This is the data type for CPU utilization 
 *  when analyzing with -u
 */
typedef struct
{
    /* value %usr */
    double cpu_usr_val[MAX_CORE_NUMBERS +1];
    /* value of %sys */
    double cpu_sys_val[MAX_CORE_NUMBERS +1];
    /* value of %iowait */
    double cpu_iowait_val[MAX_CORE_NUMBERS +1];
    /* value of %idle */
    double cpu_idle_val[MAX_CORE_NUMBERS +1];

} cpu_data;

typedef struct
{
    double cpu_usr_spike_val_each_file[MAX_ANALYZE_FILES +1][MAX_CORE_NUMBERS +1];
    double cpu_sys_spike_val_each_file[MAX_ANALYZE_FILES +1][MAX_CORE_NUMBERS +1];
    double cpu_iowait_spike_val_each_file[MAX_ANALYZE_FILES +1][MAX_CORE_NUMBERS +1];
    double cpu_idle_spike_val_each_file[MAX_ANALYZE_FILES +1][MAX_CORE_NUMBERS +1];

    double cpu_usr_former_val_each_file[MAX_ANALYZE_FILES +1][MAX_CORE_NUMBERS +1];
    double cpu_sys_former_val_each_file[MAX_ANALYZE_FILES +1][MAX_CORE_NUMBERS +1];
    double cpu_iowait_former_val_each_file[MAX_ANALYZE_FILES +1][MAX_CORE_NUMBERS +1];
    double cpu_idle_former_val_each_file[MAX_ANALYZE_FILES +1][MAX_CORE_NUMBERS +1];

    double cpu_usr_highest_val_each_file[MAX_ANALYZE_FILES +1][MAX_CORE_NUMBERS +1];
    double cpu_sys_highest_val_each_file[MAX_ANALYZE_FILES +1][MAX_CORE_NUMBERS +1];
    double cpu_iowait_highest_val_each_file[MAX_ANALYZE_FILES +1][MAX_CORE_NUMBERS +1];
    double cpu_idle_highest_val_each_file[MAX_ANALYZE_FILES +1][MAX_CORE_NUMBERS +1];

    double cpu_usr_lowest_val_each_file[MAX_ANALYZE_FILES +1][MAX_CORE_NUMBERS +1];
    double cpu_sys_lowest_val_each_file[MAX_ANALYZE_FILES +1][MAX_CORE_NUMBERS +1];
    double cpu_iowait_lowest_val_each_file[MAX_ANALYZE_FILES +1][MAX_CORE_NUMBERS +1];
    double cpu_idle_lowest_val_each_file[MAX_ANALYZE_FILES +1][MAX_CORE_NUMBERS +1];

} cpu_data_spike_each_file;

typedef struct
{
    double cpu_usr_time_span_spike_val_each_file[MAX_ANALYZE_FILES +1][MAX_CORE_NUMBERS +1];
    double cpu_sys_time_span_spike_val_each_file[MAX_ANALYZE_FILES +1][MAX_CORE_NUMBERS +1];
    double cpu_iowait_time_span_spike_val_each_file[MAX_ANALYZE_FILES +1][MAX_CORE_NUMBERS +1];
    double cpu_idle_time_span_spike_val_each_file[MAX_ANALYZE_FILES +1][MAX_CORE_NUMBERS +1];

    double cpu_usr_time_span_former_val_each_file[MAX_ANALYZE_FILES +1][MAX_CORE_NUMBERS +1];
    double cpu_sys_time_span_former_val_each_file[MAX_ANALYZE_FILES +1][MAX_CORE_NUMBERS +1];
    double cpu_iowait_time_span_former_val_each_file[MAX_ANALYZE_FILES +1][MAX_CORE_NUMBERS +1];
    double cpu_idle_time_span_former_val_each_file[MAX_ANALYZE_FILES +1][MAX_CORE_NUMBERS +1];

    double cpu_usr_time_span_highest_val_each_file[MAX_ANALYZE_FILES +1][MAX_CORE_NUMBERS +1];
    double cpu_sys_time_span_highest_val_each_file[MAX_ANALYZE_FILES +1][MAX_CORE_NUMBERS +1];
    double cpu_iowait_time_span_highest_val_each_file[MAX_ANALYZE_FILES +1][MAX_CORE_NUMBERS +1];
    double cpu_idle_time_span_highest_val_each_file[MAX_ANALYZE_FILES +1][MAX_CORE_NUMBERS +1];

    double cpu_usr_time_span_lowest_val_each_file[MAX_ANALYZE_FILES +1][MAX_CORE_NUMBERS +1];
    double cpu_sys_time_span_lowest_val_each_file[MAX_ANALYZE_FILES +1][MAX_CORE_NUMBERS +1];
    double cpu_iowait_time_span_lowest_val_each_file[MAX_ANALYZE_FILES +1][MAX_CORE_NUMBERS +1];
    double cpu_idle_time_span_lowest_val_each_file[MAX_ANALYZE_FILES +1][MAX_CORE_NUMBERS +1];

} cpu_data_time_span_spike_each_file;

/*
 *  This is the data type for task creation and system switching activity
 *  when analyzing with -w 
 */
typedef struct
{
    /* value of proc */
    double proc_val;
    /* value of cswch */
    double cswch_val;

} task_data;

typedef struct
{
    double proc_spike_val_each_file[MAX_ANALYZE_FILES +1];
    double cswch_spike_val_each_file[MAX_ANALYZE_FILES +1];

    double proc_former_val_each_file[MAX_ANALYZE_FILES +1];
    double cswch_former_val_each_file[MAX_ANALYZE_FILES +1];

    double proc_highest_val_each_file[MAX_ANALYZE_FILES +1];
    double cswch_highest_val_each_file[MAX_ANALYZE_FILES +1];

    double proc_lowest_val_each_file[MAX_ANALYZE_FILES +1];
    double cswch_lowest_val_each_file[MAX_ANALYZE_FILES +1];

} task_data_spike_each_file;

typedef struct
{
    double proc_time_span_spike_val_each_file[MAX_ANALYZE_FILES +1];
    double cswch_time_span_spike_val_each_file[MAX_ANALYZE_FILES +1];

    double proc_time_span_former_val_each_file[MAX_ANALYZE_FILES +1];
    double cswch_time_span_former_val_each_file[MAX_ANALYZE_FILES +1];

    double proc_time_span_highest_val_each_file[MAX_ANALYZE_FILES +1];
    double cswch_time_span_highest_val_each_file[MAX_ANALYZE_FILES +1];

    double proc_time_span_lowest_val_each_file[MAX_ANALYZE_FILES +1];
    double cswch_time_span_lowest_val_each_file[MAX_ANALYZE_FILES +1];

} task_data_time_span_spike_each_file;

/*
 *  This is the data type for activity for swapping statistics 
 *  when analyzing with -W 
 */
typedef struct
{
    /* value of pswpin/s */
    double pswpin_val;
    /* value of pswpout/s */
    double pswpout_val;

} pswap_data;

typedef struct
{
    double pswpin_spike_val_each_file[MAX_ANALYZE_FILES +1];
    double pswpout_spike_val_each_file[MAX_ANALYZE_FILES +1];

    double pswpin_former_val_each_file[MAX_ANALYZE_FILES +1];
    double pswpout_former_val_each_file[MAX_ANALYZE_FILES +1];

    double pswpin_highest_val_each_file[MAX_ANALYZE_FILES +1];
    double pswpout_highest_val_each_file[MAX_ANALYZE_FILES +1];

    double pswpin_lowest_val_each_file[MAX_ANALYZE_FILES +1];
    double pswpout_lowest_val_each_file[MAX_ANALYZE_FILES +1];

} pswap_data_spike_each_file;

typedef struct
{
    double pswpin_time_span_spike_val_each_file[MAX_ANALYZE_FILES +1];
    double pswpout_time_span_spike_val_each_file[MAX_ANALYZE_FILES +1];

    double pswpin_time_span_former_val_each_file[MAX_ANALYZE_FILES +1];
    double pswpout_time_span_former_val_each_file[MAX_ANALYZE_FILES +1];

    double pswpin_time_span_highest_val_each_file[MAX_ANALYZE_FILES +1];
    double pswpout_time_span_highest_val_each_file[MAX_ANALYZE_FILES +1];

    double pswpin_time_span_lowest_val_each_file[MAX_ANALYZE_FILES +1];
    double pswpout_time_span_lowest_val_each_file[MAX_ANALYZE_FILES +1];

} pswap_data_time_span_spike_each_file;

/*
 *  This is the data type for paging staistics
 *  when analyzing with -B 
 */
typedef struct
{
    /* value of pgpgin */
    double pgpgin_val;
    /* value of pgpgout */
    double pgpgout_val;
    /* value of fault */
    double fault_val;
    /* value of majflt */
    double majflt_val;
    /* value of vmeff */
    double vmeff_val;

} paging_data;

typedef struct
{
    double pgpgin_spike_val_each_file[MAX_ANALYZE_FILES +1];
    double pgpgout_spike_val_each_file[MAX_ANALYZE_FILES +1];
    double fault_spike_val_each_file[MAX_ANALYZE_FILES +1];
    double majflt_spike_val_each_file[MAX_ANALYZE_FILES +1];
    double vmeff_spike_val_each_file[MAX_ANALYZE_FILES +1];

    double pgpgin_former_val_each_file[MAX_ANALYZE_FILES +1];
    double pgpgout_former_val_each_file[MAX_ANALYZE_FILES +1];
    double fault_former_val_each_file[MAX_ANALYZE_FILES +1];
    double majflt_former_val_each_file[MAX_ANALYZE_FILES +1];
    double vmeff_former_val_each_file[MAX_ANALYZE_FILES +1];

    double pgpgin_highest_val_each_file[MAX_ANALYZE_FILES +1];
    double pgpgout_highest_val_each_file[MAX_ANALYZE_FILES +1];
    double fault_highest_val_each_file[MAX_ANALYZE_FILES +1];
    double majflt_highest_val_each_file[MAX_ANALYZE_FILES +1];
    double vmeff_highest_val_each_file[MAX_ANALYZE_FILES +1];

    double pgpgin_lowest_val_each_file[MAX_ANALYZE_FILES +1];
    double pgpgout_lowest_val_each_file[MAX_ANALYZE_FILES +1];
    double fault_lowest_val_each_file[MAX_ANALYZE_FILES +1];
    double majflt_lowest_val_each_file[MAX_ANALYZE_FILES +1];
    double vmeff_lowest_val_each_file[MAX_ANALYZE_FILES +1];

} paging_data_spike_each_file;

typedef struct
{
    double pgpgin_time_span_spike_val_each_file[MAX_ANALYZE_FILES +1];
    double pgpgout_time_span_spike_val_each_file[MAX_ANALYZE_FILES +1];
    double fault_time_span_spike_val_each_file[MAX_ANALYZE_FILES +1];
    double majflt_time_span_spike_val_each_file[MAX_ANALYZE_FILES +1];
    double vmeff_time_span_spike_val_each_file[MAX_ANALYZE_FILES +1];

    double pgpgin_time_span_former_val_each_file[MAX_ANALYZE_FILES +1];
    double pgpgout_time_span_former_val_each_file[MAX_ANALYZE_FILES +1];
    double fault_time_span_former_val_each_file[MAX_ANALYZE_FILES +1];
    double majflt_time_span_former_val_each_file[MAX_ANALYZE_FILES +1];
    double vmeff_time_span_former_val_each_file[MAX_ANALYZE_FILES +1];

    double pgpgin_time_span_highest_val_each_file[MAX_ANALYZE_FILES +1];
    double pgpgout_time_span_highest_val_each_file[MAX_ANALYZE_FILES +1];
    double fault_time_span_highest_val_each_file[MAX_ANALYZE_FILES +1];
    double majflt_time_span_highest_val_each_file[MAX_ANALYZE_FILES +1];
    double vmeff_time_span_highest_val_each_file[MAX_ANALYZE_FILES +1];

    double pgpgin_time_span_lowest_val_each_file[MAX_ANALYZE_FILES +1];
    double pgpgout_time_span_lowest_val_each_file[MAX_ANALYZE_FILES +1];
    double fault_time_span_lowest_val_each_file[MAX_ANALYZE_FILES +1];
    double majflt_time_span_lowest_val_each_file[MAX_ANALYZE_FILES +1];
    double vmeff_time_span_lowest_val_each_file[MAX_ANALYZE_FILES +1];

} paging_data_time_span_spike_each_file;

/*
 *  This is the data type for I/O and transfer rate staistics
 *  when analyzing with -b 
 */
typedef struct
{
    /* value of tps */
    double tps_val;
    /* value of bread */
    double bread_val;
    /* value of bwrtn */
    double bwrtn_val;

} io_transfer_rate_data;

typedef struct
{
    double tps_spike_val_each_file[MAX_ANALYZE_FILES +1];
    double bread_spike_val_each_file[MAX_ANALYZE_FILES +1];
    double bwrtn_spike_val_each_file[MAX_ANALYZE_FILES +1];

    double tps_former_val_each_file[MAX_ANALYZE_FILES +1];
    double bread_former_val_each_file[MAX_ANALYZE_FILES +1];
    double bwrtn_former_val_each_file[MAX_ANALYZE_FILES +1];

    double tps_highest_val_each_file[MAX_ANALYZE_FILES +1];
    double bread_highest_val_each_file[MAX_ANALYZE_FILES +1];
    double bwrtn_highest_val_each_file[MAX_ANALYZE_FILES +1];

    double tps_lowest_val_each_file[MAX_ANALYZE_FILES +1];
    double bread_lowest_val_each_file[MAX_ANALYZE_FILES +1];
    double bwrtn_lowest_val_each_file[MAX_ANALYZE_FILES +1];

} io_transfer_rate_data_spike_each_file;

typedef struct
{
    double tps_time_span_spike_val_each_file[MAX_ANALYZE_FILES +1];
    double bread_time_span_spike_val_each_file[MAX_ANALYZE_FILES +1];
    double bwrtn_time_span_spike_val_each_file[MAX_ANALYZE_FILES +1];

    double tps_time_span_former_val_each_file[MAX_ANALYZE_FILES +1];
    double bread_time_span_former_val_each_file[MAX_ANALYZE_FILES +1];
    double bwrtn_time_span_former_val_each_file[MAX_ANALYZE_FILES +1];

    double tps_time_span_highest_val_each_file[MAX_ANALYZE_FILES +1];
    double bread_time_span_highest_val_each_file[MAX_ANALYZE_FILES +1];
    double bwrtn_time_span_highest_val_each_file[MAX_ANALYZE_FILES +1];

    double tps_time_span_lowest_val_each_file[MAX_ANALYZE_FILES +1];
    double bread_time_span_lowest_val_each_file[MAX_ANALYZE_FILES +1];
    double bwrtn_time_span_lowest_val_each_file[MAX_ANALYZE_FILES +1];

} io_transfer_rate_data_time_span_spike_each_file;

/*
 *  This is the data type for memory staistics
 *  when analyzing with -r 
 */
typedef struct
{
    /* value of memused */
    double memused_val;
    /* value of kbcommit */
    int kbcommit_val;
    /* value of commit */
    double commit_val;

} memory_data;

typedef struct
{
    double memused_spike_val_each_file[MAX_ANALYZE_FILES +1];
    int kbcommit_spike_val_each_file[MAX_ANALYZE_FILES +1];
    double commit_spike_val_each_file[MAX_ANALYZE_FILES +1];

    double memused_former_val_each_file[MAX_ANALYZE_FILES +1];
    int kbcommit_former_val_each_file[MAX_ANALYZE_FILES +1];
    double commit_former_val_each_file[MAX_ANALYZE_FILES +1];

    double memused_highest_val_each_file[MAX_ANALYZE_FILES +1];
    int kbcommit_highest_val_each_file[MAX_ANALYZE_FILES +1];
    double commit_highest_val_each_file[MAX_ANALYZE_FILES +1];

    double memused_lowest_val_each_file[MAX_ANALYZE_FILES +1];
    int kbcommit_lowest_val_each_file[MAX_ANALYZE_FILES +1];
    double commit_lowest_val_each_file[MAX_ANALYZE_FILES +1];

} memory_data_spike_each_file;

typedef struct
{
    double memused_time_span_spike_val_each_file[MAX_ANALYZE_FILES +1];
    int kbcommit_time_span_spike_val_each_file[MAX_ANALYZE_FILES +1];
    double commit_time_span_spike_val_each_file[MAX_ANALYZE_FILES +1];

    double memused_time_span_former_val_each_file[MAX_ANALYZE_FILES +1];
    int kbcommit_time_span_former_val_each_file[MAX_ANALYZE_FILES +1];
    double commit_time_span_former_val_each_file[MAX_ANALYZE_FILES +1];

    double memused_time_span_highest_val_each_file[MAX_ANALYZE_FILES +1];
    int kbcommit_time_span_highest_val_each_file[MAX_ANALYZE_FILES +1];
    double commit_time_span_highest_val_each_file[MAX_ANALYZE_FILES +1];

    double memused_time_span_lowest_val_each_file[MAX_ANALYZE_FILES +1];
    int kbcommit_time_span_lowest_val_each_file[MAX_ANALYZE_FILES +1];
    double commit_time_span_lowest_val_each_file[MAX_ANALYZE_FILES +1];

} memory_data_time_span_spike_each_file;

/*
 *  This is the data type for activity for swap space utilization statistics
 *  when analyzing with -S 
 */
typedef struct
{
    /* value of swpused */
    double swpused_val;

} swap_data;

typedef struct
{
    double swpused_spike_val_each_file[MAX_ANALYZE_FILES +1];

    double swpused_former_val_each_file[MAX_ANALYZE_FILES +1];

    double swpused_highest_val_each_file[MAX_ANALYZE_FILES +1];

    double swpused_lowest_val_each_file[MAX_ANALYZE_FILES +1];

} swap_data_spike_each_file;

typedef struct
{
    double swpused_time_span_spike_val_each_file[MAX_ANALYZE_FILES +1];

    double swpused_time_span_former_val_each_file[MAX_ANALYZE_FILES +1];

    double swpused_time_span_highest_val_each_file[MAX_ANALYZE_FILES +1];

    double swpused_time_span_lowest_val_each_file[MAX_ANALYZE_FILES +1];

} swap_data_time_span_spike_each_file;

/*
 *  This is the data type for status of inode, file and other kernel tables 
 *  when analyzing with -v 
 */
typedef struct
{
    /* value of dentunusd */
    int dentunusd_val;
    /* value of file-nr */
    int file_val;
    /* value of inode-nr */
    int inode_val;

} kernel_table_data;

typedef struct
{
    int dentunusd_spike_val_each_file[MAX_ANALYZE_FILES +1];
    int file_spike_val_each_file[MAX_ANALYZE_FILES +1];
    int inode_spike_val_each_file[MAX_ANALYZE_FILES +1];

    int dentunusd_former_val_each_file[MAX_ANALYZE_FILES +1];
    int file_former_val_each_file[MAX_ANALYZE_FILES +1];
    int inode_former_val_each_file[MAX_ANALYZE_FILES +1];

    int dentunusd_highest_val_each_file[MAX_ANALYZE_FILES +1];
    int file_highest_val_each_file[MAX_ANALYZE_FILES +1];
    int inode_highest_val_each_file[MAX_ANALYZE_FILES +1];

    int dentunusd_lowest_val_each_file[MAX_ANALYZE_FILES +1];
    int file_lowest_val_each_file[MAX_ANALYZE_FILES +1];
    int inode_lowest_val_each_file[MAX_ANALYZE_FILES +1];

} kernel_table_data_spike_each_file;

typedef struct
{
    int dentunusd_time_span_spike_val_each_file[MAX_ANALYZE_FILES +1];
    int file_time_span_spike_val_each_file[MAX_ANALYZE_FILES +1];
    int inode_time_span_spike_val_each_file[MAX_ANALYZE_FILES +1];

    int dentunusd_time_span_former_val_each_file[MAX_ANALYZE_FILES +1];
    int file_time_span_former_val_each_file[MAX_ANALYZE_FILES +1];
    int inode_time_span_former_val_each_file[MAX_ANALYZE_FILES +1];

    int dentunusd_time_span_highest_val_each_file[MAX_ANALYZE_FILES +1];
    int file_time_span_highest_val_each_file[MAX_ANALYZE_FILES +1];
    int inode_time_span_highest_val_each_file[MAX_ANALYZE_FILES +1];

    int dentunusd_time_span_lowest_val_each_file[MAX_ANALYZE_FILES +1];
    int file_time_span_lowest_val_each_file[MAX_ANALYZE_FILES +1];
    int inode_time_span_lowest_val_each_file[MAX_ANALYZE_FILES +1];

} kernel_table_data_time_span_spike_each_file;

/*
 *  This is the data type for queue length and load averages 
 *  when analyzing with -q 
 */
typedef struct
{
    /* value of runq_sz */
    double runq_sz_val;
    /* value of plist_sz */
    double plist_sz_val;
    /* value of ldavg_1 */
    double ldavg_one_val;
    /* value of ldavg_5 */
    double ldavg_five_val;
    /* value of ldavg_15 */
    double ldavg_15_val;

} ldavg_data;

typedef struct
{
    double runq_sz_spike_val_each_file[MAX_ANALYZE_FILES +1];
    double plist_sz_spike_val_each_file[MAX_ANALYZE_FILES +1];
    double ldavg_one_spike_val_each_file[MAX_ANALYZE_FILES +1];
    double ldavg_five_spike_val_each_file[MAX_ANALYZE_FILES +1];
    double ldavg_15_spike_val_each_file[MAX_ANALYZE_FILES +1];

    double runq_sz_former_val_each_file[MAX_ANALYZE_FILES +1];
    double plist_sz_former_val_each_file[MAX_ANALYZE_FILES +1];
    double ldavg_one_former_val_each_file[MAX_ANALYZE_FILES +1];
    double ldavg_five_former_val_each_file[MAX_ANALYZE_FILES +1];
    double ldavg_15_former_val_each_file[MAX_ANALYZE_FILES +1];

    double runq_sz_highest_val_each_file[MAX_ANALYZE_FILES +1];
    double plist_sz_highest_val_each_file[MAX_ANALYZE_FILES +1];
    double ldavg_one_highest_val_each_file[MAX_ANALYZE_FILES +1];
    double ldavg_five_highest_val_each_file[MAX_ANALYZE_FILES +1];
    double ldavg_15_highest_val_each_file[MAX_ANALYZE_FILES +1];

    double runq_sz_lowest_val_each_file[MAX_ANALYZE_FILES +1];
    double plist_sz_lowest_val_each_file[MAX_ANALYZE_FILES +1];
    double ldavg_one_lowest_val_each_file[MAX_ANALYZE_FILES +1];
    double ldavg_five_lowest_val_each_file[MAX_ANALYZE_FILES +1];
    double ldavg_15_lowest_val_each_file[MAX_ANALYZE_FILES +1];

} ldavg_data_spike_each_file;

typedef struct
{
    double runq_sz_time_span_spike_val_each_file[MAX_ANALYZE_FILES +1];
    double plist_sz_time_span_spike_val_each_file[MAX_ANALYZE_FILES +1];
    double ldavg_one_time_span_spike_val_each_file[MAX_ANALYZE_FILES +1];
    double ldavg_five_time_span_spike_val_each_file[MAX_ANALYZE_FILES +1];
    double ldavg_15_time_span_spike_val_each_file[MAX_ANALYZE_FILES +1];

    double runq_sz_time_span_former_val_each_file[MAX_ANALYZE_FILES +1];
    double plist_sz_time_span_former_val_each_file[MAX_ANALYZE_FILES +1];
    double ldavg_one_time_span_former_val_each_file[MAX_ANALYZE_FILES +1];
    double ldavg_five_time_span_former_val_each_file[MAX_ANALYZE_FILES +1];
    double ldavg_15_time_span_former_val_each_file[MAX_ANALYZE_FILES +1];

    double runq_sz_time_span_highest_val_each_file[MAX_ANALYZE_FILES +1];
    double plist_sz_time_span_highest_val_each_file[MAX_ANALYZE_FILES +1];
    double ldavg_one_time_span_highest_val_each_file[MAX_ANALYZE_FILES +1];
    double ldavg_five_time_span_highest_val_each_file[MAX_ANALYZE_FILES +1];
    double ldavg_15_time_span_highest_val_each_file[MAX_ANALYZE_FILES +1];

    double runq_sz_time_span_lowest_val_each_file[MAX_ANALYZE_FILES +1];
    double plist_sz_time_span_lowest_val_each_file[MAX_ANALYZE_FILES +1];
    double ldavg_one_time_span_lowest_val_each_file[MAX_ANALYZE_FILES +1];
    double ldavg_five_time_span_lowest_val_each_file[MAX_ANALYZE_FILES +1];
    double ldavg_15_time_span_lowest_val_each_file[MAX_ANALYZE_FILES +1];

} ldavg_data_time_span_spike_each_file;

/*
 *  This is the data type for activity for each block device staistics
 *  when analyzing with -d 
 */
typedef struct
{
    /* value of areqsz */
    double areqsz_val[MAX_BLOCK_DEVICE_NUMBERS +1];
    /* value of util */
    double util_val[MAX_BLOCK_DEVICE_NUMBERS +1];

} block_device_data;

typedef struct
{
    double areqsz_spike_val_each_file[MAX_ANALYZE_FILES +1][MAX_BLOCK_DEVICE_NUMBERS +1];
    double util_spike_val_each_file[MAX_ANALYZE_FILES +1][MAX_BLOCK_DEVICE_NUMBERS +1];

    double areqsz_former_val_each_file[MAX_ANALYZE_FILES +1][MAX_BLOCK_DEVICE_NUMBERS +1];
    double util_former_val_each_file[MAX_ANALYZE_FILES +1][MAX_BLOCK_DEVICE_NUMBERS +1];

    double areqsz_highest_val_each_file[MAX_ANALYZE_FILES +1][MAX_BLOCK_DEVICE_NUMBERS +1];
    double util_highest_val_each_file[MAX_ANALYZE_FILES +1][MAX_BLOCK_DEVICE_NUMBERS +1];

    double areqsz_lowest_val_each_file[MAX_ANALYZE_FILES +1][MAX_BLOCK_DEVICE_NUMBERS +1];
    double util_lowest_val_each_file[MAX_ANALYZE_FILES +1][MAX_BLOCK_DEVICE_NUMBERS +1];

} block_device_data_spike_each_file;

typedef struct
{
    double areqsz_time_span_spike_val_each_file[MAX_ANALYZE_FILES +1][MAX_BLOCK_DEVICE_NUMBERS +1];
    double util_time_span_spike_val_each_file[MAX_ANALYZE_FILES +1][MAX_BLOCK_DEVICE_NUMBERS +1];

    double areqsz_time_span_former_val_each_file[MAX_ANALYZE_FILES +1][MAX_BLOCK_DEVICE_NUMBERS +1];
    double util_time_span_former_val_each_file[MAX_ANALYZE_FILES +1][MAX_BLOCK_DEVICE_NUMBERS +1];

    double areqsz_time_span_highest_val_each_file[MAX_ANALYZE_FILES +1][MAX_BLOCK_DEVICE_NUMBERS +1];
    double util_time_span_highest_val_each_file[MAX_ANALYZE_FILES +1][MAX_BLOCK_DEVICE_NUMBERS +1];

    double areqsz_time_span_lowest_val_each_file[MAX_ANALYZE_FILES +1][MAX_BLOCK_DEVICE_NUMBERS +1];
    double util_time_span_lowest_val_each_file[MAX_ANALYZE_FILES +1][MAX_BLOCK_DEVICE_NUMBERS +1];

} block_device_data_time_span_spike_each_file;

/*
 *  This is the date type for network statistics 
 *  when analyzing with -n 
 */
typedef struct
{
    /* value of rxpck/s */
    double rxpck_val[MAX_NETWORK_DEVICE_NUMBERS +1];
    /* value of txpck/s */
    double txpck_val[MAX_NETWORK_DEVICE_NUMBERS +1];
    /* value of rxkB/s */
    double rxkb_val[MAX_NETWORK_DEVICE_NUMBERS +1];
    /* value of txkB/s */
    double txkb_val[MAX_NETWORK_DEVICE_NUMBERS +1];
    /* value of rxerr/s */
    double rxerr_val[MAX_NETWORK_DEVICE_NUMBERS +1];
    /* value of txerr/s */
    double txerr_val[MAX_NETWORK_DEVICE_NUMBERS +1];
    /* value of rxdrop/s */
    double rxdrop_val[MAX_NETWORK_DEVICE_NUMBERS +1];
    /* value of txdrop/s */
    double txdrop_val[MAX_NETWORK_DEVICE_NUMBERS +1];

} network_data;

typedef struct
{
    double rxpck_spike_val_each_file[MAX_ANALYZE_FILES + 1][MAX_NETWORK_DEVICE_NUMBERS + 1];
    double txpck_spike_val_each_file[MAX_ANALYZE_FILES + 1][MAX_NETWORK_DEVICE_NUMBERS + 1];
    double rxkb_spike_val_each_file[MAX_ANALYZE_FILES + 1][MAX_NETWORK_DEVICE_NUMBERS + 1];
    double txkb_spike_val_each_file[MAX_ANALYZE_FILES + 1][MAX_NETWORK_DEVICE_NUMBERS + 1];
    double rxerr_spike_val_each_file[MAX_ANALYZE_FILES + 1][MAX_NETWORK_DEVICE_NUMBERS + 1];
    double txerr_spike_val_each_file[MAX_ANALYZE_FILES + 1][MAX_NETWORK_DEVICE_NUMBERS + 1];
    double rxdrop_spike_val_each_file[MAX_ANALYZE_FILES + 1][MAX_NETWORK_DEVICE_NUMBERS + 1];
    double txdrop_spike_val_each_file[MAX_ANALYZE_FILES + 1][MAX_NETWORK_DEVICE_NUMBERS + 1];

    double rxpck_former_val_each_file[MAX_ANALYZE_FILES + 1][MAX_NETWORK_DEVICE_NUMBERS + 1];
    double txpck_former_val_each_file[MAX_ANALYZE_FILES + 1][MAX_NETWORK_DEVICE_NUMBERS + 1];
    double rxkb_former_val_each_file[MAX_ANALYZE_FILES + 1][MAX_NETWORK_DEVICE_NUMBERS + 1];
    double txkb_former_val_each_file[MAX_ANALYZE_FILES + 1][MAX_NETWORK_DEVICE_NUMBERS + 1];
    double rxerr_former_val_each_file[MAX_ANALYZE_FILES + 1][MAX_NETWORK_DEVICE_NUMBERS + 1];
    double txerr_former_val_each_file[MAX_ANALYZE_FILES + 1][MAX_NETWORK_DEVICE_NUMBERS + 1];
    double rxdrop_former_val_each_file[MAX_ANALYZE_FILES + 1][MAX_NETWORK_DEVICE_NUMBERS + 1];
    double txdrop_former_val_each_file[MAX_ANALYZE_FILES + 1][MAX_NETWORK_DEVICE_NUMBERS + 1];

    double rxpck_highest_val_each_file[MAX_ANALYZE_FILES + 1][MAX_NETWORK_DEVICE_NUMBERS + 1];
    double txpck_highest_val_each_file[MAX_ANALYZE_FILES + 1][MAX_NETWORK_DEVICE_NUMBERS + 1];
    double rxkb_highest_val_each_file[MAX_ANALYZE_FILES + 1][MAX_NETWORK_DEVICE_NUMBERS + 1];
    double txkb_highest_val_each_file[MAX_ANALYZE_FILES + 1][MAX_NETWORK_DEVICE_NUMBERS + 1];
    double rxerr_highest_val_each_file[MAX_ANALYZE_FILES + 1][MAX_NETWORK_DEVICE_NUMBERS + 1];
    double txerr_highest_val_each_file[MAX_ANALYZE_FILES + 1][MAX_NETWORK_DEVICE_NUMBERS + 1];
    double rxdrop_highest_val_each_file[MAX_ANALYZE_FILES + 1][MAX_NETWORK_DEVICE_NUMBERS + 1];
    double txdrop_highest_val_each_file[MAX_ANALYZE_FILES + 1][MAX_NETWORK_DEVICE_NUMBERS + 1];

    double rxpck_lowest_val_each_file[MAX_ANALYZE_FILES + 1][MAX_NETWORK_DEVICE_NUMBERS + 1];
    double txpck_lowest_val_each_file[MAX_ANALYZE_FILES + 1][MAX_NETWORK_DEVICE_NUMBERS + 1];
    double rxkb_lowest_val_each_file[MAX_ANALYZE_FILES + 1][MAX_NETWORK_DEVICE_NUMBERS + 1];
    double txkb_lowest_val_each_file[MAX_ANALYZE_FILES + 1][MAX_NETWORK_DEVICE_NUMBERS + 1];
    double rxerr_lowest_val_each_file[MAX_ANALYZE_FILES + 1][MAX_NETWORK_DEVICE_NUMBERS + 1];
    double txerr_lowest_val_each_file[MAX_ANALYZE_FILES + 1][MAX_NETWORK_DEVICE_NUMBERS + 1];
    double rxdrop_lowest_val_each_file[MAX_ANALYZE_FILES + 1][MAX_NETWORK_DEVICE_NUMBERS + 1];
    double txdrop_lowest_val_each_file[MAX_ANALYZE_FILES + 1][MAX_NETWORK_DEVICE_NUMBERS + 1];

    double rxpck_down_val_each_file[MAX_ANALYZE_FILES + 1][MAX_NETWORK_DEVICE_NUMBERS + 1];
    double txpck_down_val_each_file[MAX_ANALYZE_FILES + 1][MAX_NETWORK_DEVICE_NUMBERS + 1];
    double rxkb_down_val_each_file[MAX_ANALYZE_FILES + 1][MAX_NETWORK_DEVICE_NUMBERS + 1];
    double txkb_down_val_each_file[MAX_ANALYZE_FILES + 1][MAX_NETWORK_DEVICE_NUMBERS + 1];
    double rxerr_down_val_each_file[MAX_ANALYZE_FILES + 1][MAX_NETWORK_DEVICE_NUMBERS + 1];
    double txerr_down_val_each_file[MAX_ANALYZE_FILES + 1][MAX_NETWORK_DEVICE_NUMBERS + 1];
    double rxdrop_down_val_each_file[MAX_ANALYZE_FILES + 1][MAX_NETWORK_DEVICE_NUMBERS + 1];
    double txdrop_down_val_each_file[MAX_ANALYZE_FILES + 1][MAX_NETWORK_DEVICE_NUMBERS + 1];

} network_data_spike_each_file;

typedef struct
{
    double rxpck_time_span_spike_val_each_file[MAX_ANALYZE_FILES + 1][MAX_NETWORK_DEVICE_NUMBERS + 1];
    double txpck_time_span_spike_val_each_file[MAX_ANALYZE_FILES + 1][MAX_NETWORK_DEVICE_NUMBERS + 1];
    double rxkb_time_span_spike_val_each_file[MAX_ANALYZE_FILES + 1][MAX_NETWORK_DEVICE_NUMBERS + 1];
    double txkb_time_span_spike_val_each_file[MAX_ANALYZE_FILES + 1][MAX_NETWORK_DEVICE_NUMBERS + 1];
    double rxerr_time_span_spike_val_each_file[MAX_ANALYZE_FILES + 1][MAX_NETWORK_DEVICE_NUMBERS + 1];
    double txerr_time_span_spike_val_each_file[MAX_ANALYZE_FILES + 1][MAX_NETWORK_DEVICE_NUMBERS + 1];
    double rxdrop_time_span_spike_val_each_file[MAX_ANALYZE_FILES + 1][MAX_NETWORK_DEVICE_NUMBERS + 1];
    double txdrop_time_span_spike_val_each_file[MAX_ANALYZE_FILES + 1][MAX_NETWORK_DEVICE_NUMBERS + 1];

    double rxpck_time_span_former_val_each_file[MAX_ANALYZE_FILES + 1][MAX_NETWORK_DEVICE_NUMBERS + 1];
    double txpck_time_span_former_val_each_file[MAX_ANALYZE_FILES + 1][MAX_NETWORK_DEVICE_NUMBERS + 1];
    double rxkb_time_span_former_val_each_file[MAX_ANALYZE_FILES + 1][MAX_NETWORK_DEVICE_NUMBERS + 1];
    double txkb_time_span_former_val_each_file[MAX_ANALYZE_FILES + 1][MAX_NETWORK_DEVICE_NUMBERS + 1];
    double rxerr_time_span_former_val_each_file[MAX_ANALYZE_FILES + 1][MAX_NETWORK_DEVICE_NUMBERS + 1];
    double txerr_time_span_former_val_each_file[MAX_ANALYZE_FILES + 1][MAX_NETWORK_DEVICE_NUMBERS + 1];
    double rxdrop_time_span_former_val_each_file[MAX_ANALYZE_FILES + 1][MAX_NETWORK_DEVICE_NUMBERS + 1];
    double txdrop_time_span_former_val_each_file[MAX_ANALYZE_FILES + 1][MAX_NETWORK_DEVICE_NUMBERS + 1];

    double rxpck_time_span_highest_val_each_file[MAX_ANALYZE_FILES + 1][MAX_NETWORK_DEVICE_NUMBERS + 1];
    double txpck_time_span_highest_val_each_file[MAX_ANALYZE_FILES + 1][MAX_NETWORK_DEVICE_NUMBERS + 1];
    double rxkb_time_span_highest_val_each_file[MAX_ANALYZE_FILES + 1][MAX_NETWORK_DEVICE_NUMBERS + 1];
    double txkb_time_span_highest_val_each_file[MAX_ANALYZE_FILES + 1][MAX_NETWORK_DEVICE_NUMBERS + 1];
    double rxerr_time_span_highest_val_each_file[MAX_ANALYZE_FILES + 1][MAX_NETWORK_DEVICE_NUMBERS + 1];
    double txerr_time_span_highest_val_each_file[MAX_ANALYZE_FILES + 1][MAX_NETWORK_DEVICE_NUMBERS + 1];
    double rxdrop_time_span_highest_val_each_file[MAX_ANALYZE_FILES + 1][MAX_NETWORK_DEVICE_NUMBERS + 1];
    double txdrop_time_span_highest_val_each_file[MAX_ANALYZE_FILES + 1][MAX_NETWORK_DEVICE_NUMBERS + 1];

    double rxpck_time_span_lowest_val_each_file[MAX_ANALYZE_FILES + 1][MAX_NETWORK_DEVICE_NUMBERS + 1];
    double txpck_time_span_lowest_val_each_file[MAX_ANALYZE_FILES + 1][MAX_NETWORK_DEVICE_NUMBERS + 1];
    double rxkb_time_span_lowest_val_each_file[MAX_ANALYZE_FILES + 1][MAX_NETWORK_DEVICE_NUMBERS + 1];
    double txkb_time_span_lowest_val_each_file[MAX_ANALYZE_FILES + 1][MAX_NETWORK_DEVICE_NUMBERS + 1];
    double rxerr_time_span_lowest_val_each_file[MAX_ANALYZE_FILES + 1][MAX_NETWORK_DEVICE_NUMBERS + 1];
    double txerr_time_span_lowest_val_each_file[MAX_ANALYZE_FILES + 1][MAX_NETWORK_DEVICE_NUMBERS + 1];
    double rxdrop_time_span_lowest_val_each_file[MAX_ANALYZE_FILES + 1][MAX_NETWORK_DEVICE_NUMBERS + 1];
    double txdrop_time_span_lowest_val_each_file[MAX_ANALYZE_FILES + 1][MAX_NETWORK_DEVICE_NUMBERS + 1];

} network_data_time_span_spike_each_file;

/*  -------------------- end Data Structures Types-------------------- */

/*  -------------------- Live Structures -------------------- */

/* This is the sar_analyzer object*/
struct sar_analyzer_data
{
    /* the number of threads to start */
    int threads;
    /* directory_name */
    const char *dir_name_analyze;
    /* hostname */
    char hostname[MAX_DATE_STRINGS];
    /* number of sar files */
    int files_n;
    /* number of cores read from sar files*/
    int cores_n;
    /* number of devices read from sar files*/
    int devices_n;
    /* number of network devices read from sar files*/
    int network_devices_n;
    /* device names read from sar files*/
    char device_names[MAX_BLOCK_DEVICE_NUMBERS][MAX_DEVICE_STRINGS];
    /* network device names read from sar files*/
    char network_device_names[MAX_NETWORK_DEVICE_NUMBERS][MAX_NETWORK_DEVICE_STRINGS];
    /* file name to be written */
    char file_name_to_be_written[MAX_FILE_NAME_LENGTH];
    /* title string which had been divided by space[pairs][chars] */
    char title_strings[TITLE_TOKEN_LIMIT][MAX_DATE_STRINGS];
    /* title string of first file which had been divided by space [pairs][chars] */
    char title_strings_first_file[TITLE_TOKEN_LIMIT][MAX_DATE_STRINGS];
    /* this numbers should be consistent with item columns sometimes, AM or PM should appear, in that case, decrement it*/
    int columns;
    /* date string related to below values */
    char this_date[MAX_DATE_STRINGS];
    char this_date_former[MAX_DATE_STRINGS];

    /* struct of cpu_column_data */
    cpu_column_data column_cpus;
    /* struct of ldavg_column_data */
    ldavg_column_data column_ldavgs;
    /* struct of task_column_data */
    task_column_data column_tasks;
    /* struct of paging_column_data */
    paging_column_data column_pagings;
    /* struct of memory_column_data */
    memory_column_data column_memories;
    /* struct of io_transfer_rate_column_data */
    io_transfer_rate_column_data column_io_transfer_rates;
    /* struct of block_device_column_data */
    block_device_column_data column_block_devices;
    /* struct of swap_column_data */
    swap_column_data column_swaps;
    /* struct of pswap_column_data */
    pswap_column_data column_pswaps;
    /* struct of kernel_table_column_data */
    kernel_table_column_data column_kernel_tables;
    /* struct of network_column_data */
    network_column_data column_networks;

    /* struct of cpu_data */
    cpu_data cpus_avg_highest;
    cpu_data cpus_avg_lowest;
    /* struct of ldavg_data */
    ldavg_data ldavgs_avg_highest;
    ldavg_data ldavgs_avg_lowest;
    /* struct of task_data */
    task_data tasks_avg_highest;
    task_data tasks_avg_lowest;
    /* struct of paging_data */
    paging_data pagings_avg_highest;
    paging_data pagings_avg_lowest;
    /* struct of memory_data */
    memory_data memories_avg_highest;
    memory_data memories_avg_lowest;
    /* struct of io_transfer_rate_data */
    io_transfer_rate_data io_transfer_rates_avg_highest;
    io_transfer_rate_data io_transfer_rates_avg_lowest;
    /* struct of block_device_data */
    block_device_data block_devices_avg_highest;
    block_device_data block_devices_avg_lowest;
    /* struct of swap_data */
    swap_data swaps_avg_highest;
    swap_data swaps_avg_lowest;
    /* struct of pswap_data */
    pswap_data pswaps_avg_highest;
    pswap_data pswaps_avg_lowest;
    /* struct of kernel_table_data */
    kernel_table_data kernel_tables_avg_highest;
    kernel_table_data kernel_tables_avg_lowest;
    /* struct of network_data */
    network_data networks_avg_highest;
    network_data networks_avg_lowest;

    /* struct of cpu_date */
    cpu_date date_cpus_avg_highest;
    cpu_date date_cpus_avg_lowest;
    /* struct of ldavg_date */
    ldavg_date date_ldavgs_avg_highest;
    ldavg_date date_ldavgs_avg_lowest;
    /* struct of task_date */
    task_date date_tasks_avg_highest;
    task_date date_tasks_avg_lowest;
    /* struct of paging_date */
    paging_date date_pagings_avg_highest;
    paging_date date_pagings_avg_lowest;
    /* struct of memory_date */
    memory_date date_memories_avg_highest;
    memory_date date_memories_avg_lowest;
    /* struct of io_transfer_rate_date */
    io_transfer_rate_date date_io_transfer_rates_avg_highest;
    io_transfer_rate_date date_io_transfer_rates_avg_lowest;
    /* struct of block_device_date */
    block_device_date date_block_devices_avg_highest;
    block_device_date date_block_devices_avg_lowest;
    /* struct of swap_date */
    swap_date date_swaps_avg_highest;
    swap_date date_swaps_avg_lowest;
    /* struct of pswap_date */
    pswap_date date_pswaps_avg_highest;
    pswap_date date_pswaps_avg_lowest;
    /* struct of kernel_table_date */
    kernel_table_date date_kernel_tables_avg_highest;
    kernel_table_date date_kernel_tables_avg_lowest;
    /* struct of network_date */
    network_date date_networks_avg_highest;
    network_date date_networks_avg_lowest;
};

/* This is the sar_analyzer_all object*/
struct sar_analyzer_data_all
{
    /* the number of threads to start */
    int threads;
    /* directory_name */
    const char *dir_name_analyze;
    /* hostname */
    char hostname[MAX_DATE_STRINGS];
    /* number of sar files */
    int files_n;
    /* number of cores read from sar files*/
    int cores_n;
    /* number of devices read from sar files*/
    int devices_n;
    /* number of network devices read from sar files*/
    int network_devices_n;
    /* device names read from sar files*/
    char device_names[MAX_BLOCK_DEVICE_NUMBERS][MAX_DEVICE_STRINGS];
    /* network device names read from sar files*/
    char network_device_names[MAX_NETWORK_DEVICE_NUMBERS][MAX_NETWORK_DEVICE_STRINGS];
    /* file name to be written */
    char file_name_to_be_written[MAX_FILE_NAME_LENGTH];
    /* title string which had been divided by space [pairs][chars] */
    char title_strings[TITLE_TOKEN_LIMIT][MAX_DATE_STRINGS];
    /* title string of first file which had been divided by space[pairs][chars] */
    char title_strings_first_file[TITLE_TOKEN_LIMIT][MAX_DATE_STRINGS];
    /* ( this is not the case in this object ) this numbers should be consistent with item columns sometimes,
     * AM or PM should appear, in that case, decrement it
     */
    int columns;
    /* date string related to below values */
    char this_date[MAX_DATE_STRINGS];
    char this_date_former[MAX_DATE_STRINGS];

    /* struct of cpu_column_data */
    cpu_column_data column_cpus;
    /* struct of ldavg_column_data */
    ldavg_column_data column_ldavgs;
    /* struct of task_column_data */
    task_column_data column_tasks;
    /* struct of paging_column_data */
    paging_column_data column_pagings;
    /* struct of memory_column_data */
    memory_column_data column_memories;
    /* struct of io_transfer_rate_column_data */
    io_transfer_rate_column_data column_io_transfer_rates;
    /* struct of block_device_column_data */
    block_device_column_data column_block_devices;
    /* struct of swap_column_data */
    swap_column_data column_swaps;
    /* struct of pswap_column_data */
    pswap_column_data column_pswaps;
    /* struct of kernel_table_column_data */
    kernel_table_column_data column_kernel_tables;
    /* struct of network_column_data */
    network_column_data column_networks;

    /* struct of cpu_data */
    cpu_data cpus_spike;
    cpu_data cpus_former;
    cpu_data cpus_highest;
    cpu_data cpus_lowest;
    /* struct of ldavg_data */
    ldavg_data ldavgs_spike;
    ldavg_data ldavgs_former;
    ldavg_data ldavgs_highest;
    ldavg_data ldavgs_lowest;
    /* struct of task_data */
    task_data tasks_spike;
    task_data tasks_former;
    task_data tasks_highest;
    task_data tasks_lowest;
    /* struct of paging_data */
    paging_data pagings_spike;
    paging_data pagings_former;
    paging_data pagings_highest;
    paging_data pagings_lowest;
    /* struct of memory_data */
    memory_data memories_spike;
    memory_data memories_former;
    memory_data memories_highest;
    memory_data memories_lowest;
    /* struct of io_transfer_rate_data */
    io_transfer_rate_data io_transfer_rates_spike;
    io_transfer_rate_data io_transfer_rates_former;
    io_transfer_rate_data io_transfer_rates_highest;
    io_transfer_rate_data io_transfer_rates_lowest;
    /* struct of block_device_data */
    block_device_data block_devices_spike;
    block_device_data block_devices_former;
    block_device_data block_devices_highest;
    block_device_data block_devices_lowest;
    /* struct of swap_data */
    swap_data swaps_spike;
    swap_data swaps_former;
    swap_data swaps_highest;
    swap_data swaps_lowest;
    /* struct of pswap_data */
    pswap_data pswaps_spike;
    pswap_data pswaps_former;
    pswap_data pswaps_highest;
    pswap_data pswaps_lowest;
    /* struct of kernel_table_data */
    kernel_table_data kernel_tables_spike;
    kernel_table_data kernel_tables_former;
    kernel_table_data kernel_tables_highest;
    kernel_table_data kernel_tables_lowest;
    /* struct of network_data */
    network_data networks_spike;
    network_data networks_former;
    network_data networks_highest;
    network_data networks_lowest;

    /* struct of cpu_date */
    cpu_date date_cpus_spike;
    cpu_date date_cpus_highest;
    cpu_date date_cpus_lowest;
    /* struct of ldavg_date */
    ldavg_date date_ldavgs_spike;
    ldavg_date date_ldavgs_highest;
    ldavg_date date_ldavgs_lowest;
    /* struct of task_date */
    task_date date_tasks_spike;
    task_date date_tasks_highest;
    task_date date_tasks_lowest;
    /* struct of paging_date */
    paging_date date_pagings_spike;
    paging_date date_pagings_highest;
    paging_date date_pagings_lowest;
    /* struct of memory_date */
    memory_date date_memories_spike;
    memory_date date_memories_highest;
    memory_date date_memories_lowest;
    /* struct of io_transfer_rate_date */
    io_transfer_rate_date date_io_transfer_rates_spike;
    io_transfer_rate_date date_io_transfer_rates_highest;
    io_transfer_rate_date date_io_transfer_rates_lowest;
    /* struct of block_device_date */
    block_device_date date_block_devices_spike;
    block_device_date date_block_devices_highest;
    block_device_date date_block_devices_lowest;
    /* struct of swap_date */
    swap_date date_swaps_spike;
    swap_date date_swaps_highest;
    swap_date date_swaps_lowest;
    /* struct of pswap_date */
    pswap_date date_pswaps_spike;
    pswap_date date_pswaps_highest;
    pswap_date date_pswaps_lowest;
    /* struct of kernel_table_date */
    kernel_table_date date_kernel_tables_spike;
    kernel_table_date date_kernel_tables_highest;
    kernel_table_date date_kernel_tables_lowest;
    /* struct of network_date */
    network_date date_networks_spike;
    network_date date_networks_highest;
    network_date date_networks_lowest;

    /*cpu as paragraph*/
    int cpu_as_paragraph;

    /* tmp_val */
    double tmp_val;
    double tmp2_val;
    double tmp3_val;
    double tmp4_val;
};

/* This is the sar_analyzer_spike_each_file object*/
struct sar_analyzer_data_spike_each_file
{
    /* struct of cpu_data */
    cpu_data_spike_each_file cpus_spike_each_file;
    /* struct of task_data */
    task_data_spike_each_file tasks_spike_each_file;
    /* struct of pswap_data */
    pswap_data_spike_each_file pswaps_spike_each_file;
    /* struct of paging_data */
    paging_data_spike_each_file pagings_spike_each_file;
    /* struct of io_transfer_rate_data */
    io_transfer_rate_data_spike_each_file io_transfer_rates_spike_each_file;
    /* struct of memory_data */
    memory_data_spike_each_file memories_spike_each_file;
    /* struct of swap_data */
    swap_data_spike_each_file swaps_spike_each_file;
    /* struct of kernel_table_data */
    kernel_table_data_spike_each_file kernel_tables_spike_each_file;
    /* struct of ldavg_data */
    ldavg_data_spike_each_file ldavgs_spike_each_file;
    /* struct of block_device_data */
    block_device_data_spike_each_file block_devices_spike_each_file;
    /* struct of network_data */
    network_data_spike_each_file networks_spike_each_file;

    /* struct of cpu_date */
    cpu_date_spike_each_file date_cpus_spike_each_file;
    /* struct of task_date */
    task_date_spike_each_file date_tasks_spike_each_file;
    /* struct of pswap_date */
    pswap_date_spike_each_file date_pswaps_spike_each_file;
    /* struct of paging_date */
    paging_date_spike_each_file date_pagings_spike_each_file;
    /* struct of io_transfer_rate_date */
    io_transfer_rate_date_spike_each_file date_io_transfer_rates_spike_each_file;
    /* struct of memory_date */
    memory_date_spike_each_file date_memories_spike_each_file;
    /* struct of swap_date */
    swap_date_spike_each_file date_swaps_spike_each_file;
    /* struct of kernel_table_date */
    kernel_table_date_spike_each_file date_kernel_tables_spike_each_file;
    /* struct of ldavg_date */
    ldavg_date_spike_each_file date_ldavgs_spike_each_file;
    /* struct of block_device_date */
    block_device_date_spike_each_file date_block_devices_spike_each_file;
    /* struct of network_date */
    network_date_spike_each_file date_networks_spike_each_file;
};

/* This is the sar_analyzer_time_span_spike_each_file object*/
struct sar_analyzer_data_time_span_spike_each_file
{
    /* struct of cpu_data */
    cpu_data_time_span_spike_each_file cpus_time_span_spike_each_file;
    /* struct of task_data */
    task_data_time_span_spike_each_file tasks_time_span_spike_each_file;
    /* struct of pswap_data */
    pswap_data_time_span_spike_each_file pswaps_time_span_spike_each_file;
    /* struct of paging_data */
    paging_data_time_span_spike_each_file pagings_time_span_spike_each_file;
    /* struct of io_transfer_rate_data */
    io_transfer_rate_data_time_span_spike_each_file io_transfer_rates_time_span_spike_each_file;
    /* struct of memory_data */
    memory_data_time_span_spike_each_file memories_time_span_spike_each_file;
    /* struct of swap_data */
    swap_data_time_span_spike_each_file swaps_time_span_spike_each_file;
    /* struct of kernel_table_data */
    kernel_table_data_time_span_spike_each_file kernel_tables_time_span_spike_each_file;
    /* struct of ldavg_data */
    ldavg_data_time_span_spike_each_file ldavgs_time_span_spike_each_file;
    /* struct of block_device_data */
    block_device_data_time_span_spike_each_file block_devices_time_span_spike_each_file;
    /* struct of network_data */
    network_data_time_span_spike_each_file networks_time_span_spike_each_file;

    /* struct of cpu_date */
    cpu_date_time_span_spike_each_file date_cpus_time_span_spike_each_file;
    /* struct of task_date */
    task_date_time_span_spike_each_file date_tasks_time_span_spike_each_file;
    /* struct of pswap_date */
    pswap_date_time_span_spike_each_file date_pswaps_time_span_spike_each_file;
    /* struct of paging_date */
    paging_date_time_span_spike_each_file date_pagings_time_span_spike_each_file;
    /* struct of io_transfer_rate_date */
    io_transfer_rate_date_time_span_spike_each_file date_io_transfer_rates_time_span_spike_each_file;
    /* struct of memory_date */
    memory_date_time_span_spike_each_file date_memories_time_span_spike_each_file;
    /* struct of swap_date */
    swap_date_time_span_spike_each_file date_swaps_time_span_spike_each_file;
    /* struct of kernel_table_date */
    kernel_table_date_time_span_spike_each_file date_kernel_tables_time_span_spike_each_file;
    /* struct of ldavg_date */
    ldavg_date_time_span_spike_each_file date_ldavgs_time_span_spike_each_file;
    /* struct of block_device_date */
    block_device_date_time_span_spike_each_file date_block_devices_time_span_spike_each_file;
    /* struct of network_date */
    network_date_time_span_spike_each_file date_networks_time_span_spike_each_file;
};

/*  -------------------- end Live Structures -------------------- */

/* 
 *  These are pointers to the global data, it should be available
 *  once sar_analyzer_init() was called.
 */
extern struct sar_analyzer_data *sar_analyzer_obj;
extern struct sar_analyzer_data_all *sar_analyzer_all_obj;
extern struct sar_analyzer_data_spike_each_file *sar_analyzer_spike_obj;
extern struct sar_analyzer_data_time_span_spike_each_file *sar_analyzer_time_span_spike_obj;
extern struct line_data *header_obj;
extern struct line_data *line_obj;
extern struct line_data *line_all_obj;
extern struct line_data *report_obj;
extern struct line_data *report_cpu_obj;
extern struct line_data *report_cpu_spike_obj[MAX_CORE_NUMBERS];
extern struct line_data *report_cpu_time_span_spike_obj[MAX_CORE_NUMBERS];
extern struct line_data *report_cpu_explanation_obj;
extern struct line_data *report_tasks_obj;
extern struct line_data *report_tasks_spike_obj;
extern struct line_data *report_tasks_time_span_spike_obj;
extern struct line_data *report_tasks_explanation_obj;
extern struct line_data *report_pswap_obj;
extern struct line_data *report_pswap_spike_obj;
extern struct line_data *report_pswap_time_span_spike_obj;
extern struct line_data *report_pswap_explanation_obj;
extern struct line_data *report_paging_obj;
extern struct line_data *report_paging_spike_obj;
extern struct line_data *report_paging_time_span_spike_obj;
extern struct line_data *report_paging_explanation_obj;
extern struct line_data *report_io_transfer_rate_obj;
extern struct line_data *report_io_transfer_rate_spike_obj;
extern struct line_data *report_io_transfer_rate_time_span_spike_obj;
extern struct line_data *report_io_transfer_rate_explanation_obj;
extern struct line_data *report_memory_obj;
extern struct line_data *report_memory_spike_obj;
extern struct line_data *report_memory_time_span_spike_obj;
extern struct line_data *report_memory_explanation_obj;
extern struct line_data *report_swpused_obj;
extern struct line_data *report_swpused_spike_obj;
extern struct line_data *report_swpused_time_span_spike_obj;
extern struct line_data *report_swpused_explanation_obj;
extern struct line_data *report_kernel_table_obj;
extern struct line_data *report_kernel_table_spike_obj;
extern struct line_data *report_kernel_table_time_span_spike_obj;
extern struct line_data *report_kernel_table_explanation_obj;
extern struct line_data *report_ldavg_obj;
extern struct line_data *report_ldavg_spike_obj;
extern struct line_data *report_ldavg_time_span_spike_obj;
extern struct line_data *report_ldavg_explanation_obj;
extern struct line_data *report_block_device_obj;
extern struct line_data *report_block_device_spike_obj[MAX_BLOCK_DEVICE_NUMBERS];
extern struct line_data *report_block_device_time_span_spike_obj[MAX_BLOCK_DEVICE_NUMBERS];
extern struct line_data *report_block_device_explanation_obj;
extern struct line_data *report_network_obj;
extern struct line_data *report_network_spike_obj[MAX_NETWORK_DEVICE_NUMBERS];
extern struct line_data *report_network_time_span_spike_obj[MAX_NETWORK_DEVICE_NUMBERS];
extern struct line_data *report_network_explanation_obj;
extern struct line_data *report_network_error_obj;
extern struct line_data *report_network_error_spike_obj[MAX_NETWORK_DEVICE_NUMBERS];
extern struct line_data *report_network_error_time_span_spike_obj[MAX_NETWORK_DEVICE_NUMBERS];
extern struct line_data *report_network_error_explanation_obj;
extern struct line_data *report_thrashing_obj;
extern struct line_data *report_network_down_obj[MAX_NETWORK_DEVICE_NUMBERS];
extern struct line_data *report_overall_judgement_obj;
/* svg obj should go here */
extern struct line_data *svg_common_cpu_obj;
extern struct line_data2 *svg_cpu_usr_obj;
extern struct line_data2 *svg_cpu_sys_obj;
extern struct line_data2 *svg_cpu_iowait_obj;
extern struct line_data2 *svg_cpu_idle_obj;
extern struct line_data2 *svg_memory_memused_obj;
extern struct line_data2 *svg_memory_swpused_obj;
extern struct line_data2 *svg_block_device_util_obj[MAX_BLOCK_DEVICE_NUMBERS];
extern struct line_data2 *svg_ldavg_one_obj;
extern struct line_data2 *svg_ldavg_five_obj;
extern struct line_data2 *svg_ldavg_15_obj;

/*
 * Function Name: initialize_avg_checked_int()
 *
 * This function initializes avg_checked_int 
 *
 * Caller : read_write_file()
 *
 * Calls : none
 *
 */
void initialize_avg_checked_int(void);

/*
 * Function Name: get_dir_name_analyze()
 *
 * This function returns dir_name_analyze
 *
 * Caller : read_write_file()
 *
 * Calls : none
 *
 */
const char *get_dir_name_analyze(void);

/*
 * Function Name: get_hostname()
 *
 * This function returns hostname 
 *
 * Caller :
 *
 * Calls : none
 *
 */
char *get_hostname(void);

/*
 * Function Name: get_files_n()
 *
 * This function returns number of sar files
 *
 * Caller : main()
 *
 * Calls : none
 *
 */
int get_files_n(void);

/*
 * Function Name: get_core_numbers()
 *
 * This function returns number of cores read from sar files
 *
 * Caller : main()
 * Caller : make_report()
 *
 * Calls : none
 *
 */
int get_core_numbers(void);

/* 
 * Function Name: get_network_device_numbers()
 * This function returns number of network devices read from sar files
 *
 * Caller : main()
 * Caller : make_report()
 *
 * Calls : none
 *
 */
int get_network_device_numbers(void);


/*
 * Function Names: get_block_device_numbers()
 *
 * This function returns number of block devices read from sar files
 *
 * Caller : main()
 * Caller : make_report()
 *
 * Calls : none
 *
 */
int get_block_device_numbers(void);

/*
 * Function Name: get_block_device_names()
 *
 * This function returns names of block devices read from sar files
 *
 * Caller : main()
 * Caller : make_report()
 *
 * Calls : none
 *
 */
const char *get_block_device_names(int x);

/*
 * Function Name: initialize_block_device_name()
 *
 * This function sets very first name of block device and others to string 'ignore'
 * string 'ignore' could be used for getting how many block devices exist.
 *
 * Caller : create_sar_analyzer_obj()
 *
 * Calls : none
 *
 */
void initialize_block_device_name(void);

/*
 * Function Name: initialize_network_device_name()
 *
 * This function sets very first name of network device and others to string 'ignore'
 * string 'ignore' could be used for getting how many network devices exist.
 *
 * Caller : create_sar_analyzer_obj()
 *
 * Calls : none
 */
void initialize_network_device_name(void);

/*
 * Function Name: get_network_device_names()
 *
 * This function returns names of network devices read from sar files
 *
 * Caller : make_report()
 *
 * Calls : none
 *
 */
const char *get_network_device_names(int x);

/*
 * Function Name: search_block_device_name()
 *
 * This function searches block device name from the object
 * and if it exists, returns the array element number, if not, returns 0 
 *
 * Caller : set_token_items()
 *
 * Calls : none
 *
 */
int search_block_device_name(const char *block_device_name);

/*
 * Function Name: search_network_device_name()
 *
 * This function searches network devices from the object
 * and if it exists, returns the array element number, if not, returns 0 
 *
 * Caller : set_token_items()
 *
 * Calls : none
 *
 */
int search_network_device_name(const char *network_device_name);

/* 
 *  Function Name: check_result_dir()
 *
 *  This function checks result directory.
 *  If result directory does not exist, creates it.
 *
 *  Caller : main()
 *
 *  Calls : none
 *
 */
int check_result_dir(const char *dname, int sar_only, int tmp);

/* 
 *  Function Name: sar_analyzer_init()
 *
 *  This function initializes object .
 *  And also be the entry point of the program.
 *  dname and fname could be given as NULL.
 *  Call 'read_sa_dir()' and pass the directory given. 
 *
 *  Caller : main()
 *
 *  Calls : read_sa_dir (when -D is set)
 *  Calls : prepareing... (when -i is set)
 *
 */
void sar_analyzer_init(const char *dname, const char *fname, int SAR_OPTION,
                       int REPORT, int MESSAGE_ONLY, const char *time_span);

/* 
 * Function Name: create_sar_analyzer_obj()
 *
 * This function initializes object.
 *
 *  Caller : main()
 *
 */
int create_sar_analyzer_obj(void);

/*
 * Function Name: free_sar_analyzer_obj()
 *
 * This function frees sar_analyzer_obj
 *
 *  Caller : main()
 *
 */
int free_sar_analyzer_obj(void);

/*
 *  Function Name: file_to_write()
 *
 *  This function sets file name to be written to the sar_analyzer_obj from the SAR_OPTION.
 *
 *  Caller : main()
 *
 */
int file_to_write(int SAR_OPTION);

/*
 * Function Name: set_dir_name_analyze()
 *
 * This function sets dir_name_analyze
 *
 * Caller : main()
 *
 * Calls : none
 *
 */
void set_dir_name_analyze(const char *dname);

/* 
 * Function Name: set_files_n() 
 *
 * This function sets number of sar files
 * 
 * Caller : read_sa_dir()
 *
 * Calls : none
 * 
 */
void set_files_n(int var);

/* 
 *  Function Name: read_sa_dir()
 *
 *  This function reads sa directory.
 *  Sorts file names and puts them into an array.
 *  Pass an array and file numbers with the SAR_OPTION and REPORT
 *  to the function 'read_write_file()'.
 *
 *  Caller : sar_analyzer_init()
 *
 *  Calls : read_write_file()
 *
 */
void read_sa_dir(const char *dname, int SAR_OPTION, int REPORT,
                 int MESSAGE_ONLY, const char *time_span);

/* 
 *  Function Name: read_sar()
 *
 *  This function reads sar file and during the procedure, 'get_word_line()' writes 
 *  item values to the struct as an option orders.
 *
 *  Caller : read_write_file()
 *
 *  Calls : get_word_line()
 *
 */
void read_sar(int file_number, const char *fname, int SAR_OPTION,
              int REPORT, int MESSAGE_ONLY, const char *time_span);

/*
 *  Function Name: read_write_file ()
 *
 *  This function loops through an array given by 'read_sa_dir()'.
 *  During the procedure, files are read by 'read_sar()' and data are stored in the struct. 
 *  After 'read_sar()' job is done, calls 'make_report()' to store data in the struct. 
 *
 *  Caller read_sa_dir()
 *
 *  Calls: read_sar()
 *  Calls: make_report()
 *
 */
void read_write_file(DIR *dir, const char *dname, char *sar_files[], int n,
                     int SAR_OPOTION, int REPORT, int MESSAGE_ONLY, 
                     const char *time_span);

/*
 *  Function Name: make_report()
 *
 *  This function makes a report and set them to the struct. 
 *  If argument 'REPORT' is not 0 returns and do nothing. 
 *
 *  Caller : read_write_file()
 *
 *  Calls : many
 *
 */
int make_report(int SAR_OPTION, int REPORT, int files_n, const char *time_span);

/* 
 *  Function Name : get_word_line()
 *
 *  This function checks if item string is inclued in a single line.
 *  If so, set them to the struct. 
 *  During the procedure, after initializing column number with 'initialize_check_int()',
 *  'set_token_column()' is called to set item's column number. 
 *
 *  Caller : read_sar()
 *
 *  Calls : innitialize_check_int()
 *  Calls : set_token_column()
 *  Calls : get_word_line()
 *  Calls : set_token_items()
 *
 */
int get_word_line(int file_number, char **line, int SAR_OPTION,
                  int MESSAGE_ONLY, const char *time_span);

/* 
 * Function Name: read_sar_check()
 *
 *  This function reads sar file and checks healthness. 
 *
 *  Caller : read_write_file()
 *
 *  Calls : sanity_check_file() 
 *
 */
void read_sar_check(int file_number, const char *fname, int SAR_OPTION);

/* 
 * Function Name: read_sar_cpu_as_paragraph()
 *
 *  This function reads sar file and counts cpu as paragraph and set number to cpu_as_paragraph. 
 *
 *  Caller : read_write_file()
 *
 */
void read_sar_cpu_as_paragraph(const char *filename);

/* 
 * Function Name: sanity_check_file()
 *
 * This function checks healthness of sar file 
 * Checks the order of items by 'Average' line.
 *
 *  Caller : read_sar()
 *
 *  Calls : none 
 */
void sanity_check_file(char * line, const char * filename);

/* 
 * Function Name: set_title_strings()
 *
 * This function sets title_strings to sar_analyzer_obj
 *
 *  Caller : set_token_column()
 *
 *  Calls : none 
 */
void set_title_strings(int x, const char *title_strings);

/* 
 * Function Name: set_title_strings_first_file()
 *
 * This function sets title_strings of a first file to sar_analyzer_obj
 *
 *  Caller : set_token_column()
 *
 *  Calls : none 
 */
void set_title_strings_first_file(int x, const char *title_strings);

/* 
 * Function Name: set_core_numbers()
 *
 * This function sets number of cores to sar_analyzer_obj
 *
 *  Caller : get_word_line()
 *
 *  Calls : none 
 */
void set_core_numbers(int var);

/* 
 * Function Name: set_block_device_names()
 *
 * This function sets names of block devices to sar_analyzer_obj
 *
 *  Caller : set_token_items()
 *
 *  Calls : none 
 */
void set_block_device_names(const char *block_device_name);

/* 
 * Function Name: set_this_date()
 *
 * This function sets this_date to sar_analyzer_obj
 *
 *  Caller : set_token_column()
 *
 *  Calls : none 
 */
void set_this_date(const char *date_string);

/* 
 * Function Name: set_this_date_all()
 *
 * This function sets this_date_all to sar_analyzer_all_obj
 *
 *  Caller : set_token_column()
 *
 *  Calls : none 
 */
void set_this_date_all(const char *date_string);

/* 
 * Function Name: set_this_date_former()
 *
 * This function sets this_date_former to sar_analyzer_obj
 *
 *  Caller : set_token_column()
 *
 *  Calls : none 
 */
void set_this_date_former(const char *date_string);

/* 
 * Function Name: set_this_date_all_former()
 *
 * This function sets this_date_all_former to sar_analyzer_all_obj
 *
 *  Caller : set_token_column()
 *
 *  Calls : none 
 */
void set_this_date_all_former(const char *date_string);

/*
 * Function Name: remove_unneeded_files()
 *
 * This function removes unneeded files  
 *
 *  Caller : main()
 *
 *  Calls : system() system call
 *
 */
void remove_unneeded_files(const char *filename, const char *extension);

/*
 * Function Name: check_time_value()
 *
 * This function returns counts which should by multiplied by norizontal_notch 
 *
 *  Caller : set_token_items()
 *
 *  Calls : none 
 *
 */
double check_time_value(double initial_val, double horizontal_notch, int count, char *time_value); 

/*
 * Function Name: check_time_value_is_in_time_span()
 *
 * This function returns 1 if time_value is in between the time_span given and if not return 0.  
 *
 *  Caller : set_token_items()
 *
 *  Calls : none 
 */
int check_time_value_is_in_time_span(const char *time_span_str, const char *time_value);

#endif /* SAJ_COMMON_H */
