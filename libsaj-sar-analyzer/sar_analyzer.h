/*
 *  sar_analyzer.h - analyzing definitions
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

#include "common.h"
#include "../libsaj-sosreport-analyzer/line_data.h"

#ifndef SAR__ANALYZER_H
#define SAR__ANALYZER_H

#define _CPU 0x00000001 /* ( 1 << 0 )*/
#define _TASKS 0x00000002 /* ( 1 << 1 ) */
#define _PSWAP 0x00000004 /* ( 1 << 2 ) */
#define _PAGING 0x00000008 /* ( 1 << 3 ) */
#define _IO_TRANSFER_RATE 0x00000010 /* ( 1 << 4 ) */
#define _MEMORY 0x00000020 /* ( 1 << 5 ) */ 
#define _SWPUSED 0x00000040 /* ( 1 << 6 ) */
#define _KERNEL_TABLE 0x00000080 /* ( 1 << 7 ) */ 
#define _LDAVG 0x00000100 /* ( 1 << 8 ) */
#define _BLOCK_DEVICE 0x00000200 /* ( 1 << 9 ) */
#define _NETWORK 0x00000400 /* ( 1 << 10 ) */
#define _NETWORK_ERROR 0x00000800 /* ( 1 << 11 ) */

/* These are the numbers of items*/
int CHK_CORES_N = 0;
int SHOW_AVG = 1;
int CHECK_CPU_EACH = 0;
u_int32_t CHK_A = 0x00000000;
u_int32_t CHK_Z = 0x00000000;

int set_column_cpu ( int var, const char *element );
int set_column_tasks ( int var, const char *element );
int set_column_pswap ( int var, const char *element );
int set_column_paging ( int var, const char *element );
int set_column_io_transfer_rate ( int var, const char *element );
int set_column_memory ( int var, const char *element );
int set_column_swpused ( int var );
int set_column_kernel_table ( int var, const char *element );
int set_column_ldavg ( int var, const char *element );
int set_column_block_device ( int var, const char *element );
int set_column_network ( int var, const char *element );

/* 
 * 
 *  Initialize the stuct and make it living.
 * 
 */

/* 
 * 
 *  sar_analyzer_obj
 *  When making object, these should be initialized with functions 
 *
 */
struct sar_analyzer_data sar_analyzer_obj_raw =
    {
        5, /* threads */
        "./tmp", /* dir_name_analyze */
        "localhost", /* hostname */
        0, /* number of sar files */
        0, /* number of cores read from sar files */
        0, /* number of devices read from sar files */
        0, /* number of network devices read from sar files */
        {{"test"}}, /* device names read from sar files */
        {{"ignore"}}, /* network device names read from sar files */
        "test.txt", /* file_name_to_be_written */
        {{0}}, /* title_strings */
        {{0}}, /* title_strings_first_file */
        0, /* columns */
        "1970-01-01", /* this_date */

        {0, 0, 0, 0, 0}, /* cpu_column_data */
        {0, 0, 0, 0, 0}, /* ldavg_column_data */
        {0, 0}, /* task_column_data */
        {0, 0, 0, 0, 0}, /* paging_column_data */
        {0, 0, 0}, /* memory_column_data */
        {0,0,0}, /* io_transfer_rate_column_data */
        {0,0}, /* block_device_column_data */
        {0}, /* swap_column_data */
        {0, 0}, /* pswap_column_data */
        {0 ,0, 0}, /* kerlel_table_column_data */
        {0 ,0, 0, 0, 0, 0, 0, 0}, /* network_column_data */

        {{0.00, 0.00, 0.00, 0.00}}, /* cpu_data_avg_highest */
        {{100.00, 100.00, 100.00, 100.00}}, /* cpu_data_avg_lowest */
        {0,0,0.00,0.00,0.00}, /* ldavg_data_avg_highest */
        {999999, 9999999, 100.00, 100.00, 100.00}, /* ldavg_data_avg_lowest */
        {0.00, 0.00}, /* task_data_avg_highest */
        {999999.00, 9999999.00}, /* task_data_avg_lowest */
        {0.00, 0.00, 0.00, 0.00, 0.00}, /* paging_data_avg_highest */
        {999999.00, 999999.00, 999999.00, 9999999.00, 100.00}, /* paging_data_avg_lowest */
        {0.00, 0.00, 0.00}, /* memory_data_avg_highest */
        {100.01, 100.1, 100.1}, /* memory_data_avg_lowest */
        {0.00, 0.00, 0.00}, /* io_transfer_rate_data_avg_highest */
        {100.01, 100.01, 100.01}, /* io_transfer_rate_data_avg_lowest */
        {{0.00, 0.00}}, /* block_device_data_avg_highest */
        {{100.01, 100.01}}, /* block_device_data_avg_lowest */
        {100.01}, /* swap_data_avg_highest */
        {100.01}, /* swap_data_avg_lowest */
        {999999, 999999}, /* pswap_data_avg_highest */
        {999999, 999999}, /* pswap_data_avg_lowest */
        {999999, 999999, 999999}, /* kernel_table_data_avg_highest */
        {999999, 999999, 999999}, /* kernel_table_data_avg_lowest */
        {{100.01, 100.1, 100.1, 100.1, 100.1, 100.1, 100.1, 100.1}}, /* network_data_avg_highest */
        {{0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00}}, /* network_data_avg_lowest */

        {{"", "", "", ""}}, /* cpu_date_avg_highest */
        {{"", "", "", ""}}, /* cpu_date_avg_lowest */
        {"", "", "", "", ""}, /* ldavg_date_avg_highest */
        {"", "", "", "", ""}, /* ldavg_date_avg_lowest */
        {"", ""}, /* task_date_avg_highest */
        {"", ""}, /* task_date_avg_lowest */
        {"", "", "", "", ""}, /* paging_date_avg_highest */
        {"", "", "", "", ""}, /* paging_date_avg_lowest */
        {"", "", ""}, /* memory_date_avg_highest */
        {"", "", ""}, /* memory_date_avg_lowest */
        {"", "", ""}, /* io_transfer_rate_date_avg_highest */
        {"", "", ""}, /* io_transfer_rate_date_avg_lowest */
        {{"", ""}}, /* block_device_date_avg_highest */
        {{"", ""}}, /* block_device_date_avg_lowest */
        {""}, /* swap_date_avg_highest */
        {""}, /* swap_date_avg_lowest */
        {"", ""}, /* pswap_date_avg_highest */
        {"", ""}, /* pswap_date_avg_lowest */
        {"", "", ""}, /* kernel_table_date_avg_highest */
        {"", "", ""}, /* kernel_table_date_avg_lowest */
        {{"", "", "", "", "", "", "", ""}}, /* network_date_avg_highest */
        {{"", "", "", "", "", "", "", ""}}, /* network_date_avg_lowest */
    };

/* 
 * 
 *  sar_analyzer_all_obj ( this object is for data all -Z option )
 *  When making object, these should be initialized with functions 
 *
 */
struct sar_analyzer_data_all sar_analyzer_all_obj_raw =
    {
        5, /* threads */
        "./tmp", /* dir_name_analyze */
        "localhost", /* hostname */
        0, /* number of sar files */
        0, /* number of cores read from sar files */
        0, /* number of devices read from sar files */
        0, /* number of network devices read from sar files */
        {{"test"}}, /* device names read from sar files */
        {{"ignore"}}, /* network device names read from sar files */
        "test.txt", /* file_name_to_be_written */
        {{0}}, /* title_strings */
        {{0}}, /* title_strings_first_file */
        0, /* columns */
        "1970-01-01", /* this_date */

        {0, 0, 0, 0, 0}, /* cpu_column_data */
        {0, 0, 0, 0, 0}, /* ldavg_column_data */
        {0, 0}, /* task_column_data */
        {0, 0, 0}, /* paging_column_data */
        {0, 0, 0}, /* memory_column_data */
        {0,0,0}, /* io_transfer_rate_column_data */
        {0,0}, /* block_device_column_data */
        {0}, /* swap_column_data */
        {0, 0}, /* pswap_column_data */
        {0 ,0, 0}, /* kerlel_table_column_data */
        {0 ,0, 0, 0, 0, 0, 0, 0}, /* network_column_data */

        {{0.00, 0.00, 0.00, 0.00}}, /* cpu_data_spike */
        {{0.00, 0.00, 0.00, 0.00}}, /* cpu_data_former */
        {{0.00, 0.00, 0.00, 0.00}}, /* cpu_data_highest */
        {{100.00, 100.00, 100.00, 100.00}}, /* cpu_data_lowest */

        {0, 0, 0.00, 0.00, 0.00}, /* ldavg_data_spike */
        {0, 0, 0.00, 0.00, 0.00}, /* ldavg_data_former */
        {0, 0, 0.00, 0.00, 0.00}, /* ldavg_data_highest */
        {999999, 9999999, 100.00, 100.00, 100.00}, /* ldavg_data_lowest */

        {0.00, 0.00}, /* task_data_spike */
        {0.00, 0.00}, /* task_data_former */
        {0.00, 0.00}, /* task_data_highest */
        {999999.00, 9999999.00}, /* task_data_lowest */

        {0.00, 0.00, 0.00, 0.00, 0.00}, /* paging_data_spike */
        {0.00, 0.00, 0.00, 0.00, 0.00}, /* paging_data_former */
        {0.00, 0.00, 0.00, 0.00, 0.00}, /* paging_data_highest */
        {999999.00, 999999.00, 999999.00, 9999999.00, 100.00}, /* paging_data_lowest */

        {0.00, 0.00, 0.00}, /* memory_data_spike */
        {0.00, 0.00, 0.00}, /* memory_data_former */
        {0.00, 0.00, 0.00}, /* memory_data_highest */
        {100.01, 100.1, 100.1}, /* memory_data_lowest */

        {0.00, 0.00, 0.00}, /* io_transfer_rate_data_spike */
        {0.00, 0.00, 0.00}, /* io_transfer_rate_data_former */
        {0.00, 0.00, 0.00}, /* io_transfer_rate_data_highest */
        {100.01, 100.01, 100.01}, /* io_transfer_rate_data_lowest */

        {{0.00, 0.00}}, /* block_device_data_spike */
        {{0.00, 0.00}}, /* block_device_data_former */
        {{0.00, 0.00}}, /* block_device_data_highest */
        {{100.01, 100.01}}, /* block_device_data_lowest */

        {100.01}, /* swap_data_spike */
        {100.01}, /* swap_data_former */
        {100.01}, /* swap_data_highest */
        {100.01}, /* swap_data_lowest */

        {0, 0}, /* pswap_data_spike */
        {0, 0}, /* pswap_data_former */
        {0, 0}, /* pswap_data_highest */
        {999999, 999999}, /* pswap_data_lowest */

        {0, 0, 0}, /* kernel_table_data_spike */
        {0, 0, 0}, /* kernel_table_data_former */
        {0, 0, 0}, /* kernel_table_data_highest */
        {999999, 999999, 999999}, /* kernel_table_data_lowest */

        {{100.01, 100.1, 100.1, 100.1, 100.1, 100.1, 100.1, 100.1}}, /* network_data_spike */
        {{100.01, 100.1, 100.1, 100.1, 100.1, 100.1, 100.1, 100.1}}, /* network_data_former */
        {{100.01, 100.1, 100.1, 100.1, 100.1, 100.1, 100.1, 100.1}}, /* network_data_highest */
        {{0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00}}, /* network_data_lowest */

        {{"", "", "", "",
        "", "", "", ""}}, /* cpu_date_spike */
        {{"", "", "", "",
        "", "", "", ""}}, /* cpu_date_highest */
        {{"", "", "", "",
        "", "", "", ""}}, /* cpu_date_lowest  */

        {"", "", "", "", "",
         "", "", "", "", ""
        }, /* ldavg_date_spike */
        {"", "", "", "", "",
         "", "", "", "", ""
        }, /* ldavg_date_highest */
        {"", "", "", "", "",
         "", "", "", "", ""
        }, /* ldavg_date_lowest */

        {"", "", "", ""}, /* task_date_spike */
        {"", "", "", ""}, /* task_date_highest */
        {"", "", "", ""}, /* task_date_lowest */

        {"", "", "", "", "", "", "", ""}, /* paging_date_spike */
        {"", "", "", "", "", "", "", ""}, /* paging_date_highest */
        {"", "", "", "", "", "", "", ""}, /* paging_date_lowest */

        {"", "", "", "", "", ""}, /* memory_date_spike */
        {"", "", "", "", "", ""}, /* memory_date_highest */
        {"", "", "", "", "", ""}, /* memory_date_lowest */

        {"", "", "", "", "", ""}, /* io_transfer_rate_date_spike */
        {"", "", "", "", "", ""}, /* io_transfer_rate_date_highest */
        {"", "", "", "", "", ""}, /* io_transfer_rate_date_lowest */

        {{"", "", "", ""}}, /* block_device_date_spike */
        {{"", "", "", ""}}, /* block_device_date_highest */
        {{"", "", "", ""}}, /* block_device_date_lowest */

        {"", ""}, /* swap_date_spike */
        {"", ""}, /* swap_date_highest */
        {"", ""}, /* swap_date_lowest */

        {"", "", "", ""}, /* pswap_date_spike */
        {"", "", "", ""}, /* pswap_date_highest */
        {"", "", "", ""}, /* pswap_date_lowest */

        {"", "", "", "", "", ""}, /* kernel_table_date_spike */
        {"", "", "", "", "", ""}, /* kernel_table_date_highest */
        {"", "", "", "", "", ""}, /* kernel_table_date_lowest */

        {{"", "", "", "", "", "", "", "",
          "", "", "", "", "", "", "", ""}}, /* network_date_spike */
        {{"", "", "", "", "", "", "", "",
          "", "", "", "", "", "", "", ""}}, /* network_date_highest */
        {{"", "", "", "", "", "", "", "",
          "", "", "", "", "", "", "", ""}}, /* network_date_lowest */
        0, /* cpu_as_paragraph */
        0.0, /* tmp_val */
        0.0, /* tmp2_val */
        0.0, /* tmp3_val */
        0.0, /* tmp4_val */
    };

/* 
 *  sar_analyzer_spike_obj ( this object is for data all -Z option )
 *  When making object, these should be initialized with functions 
 *
 */
struct sar_analyzer_data_spike_each_file sar_analyzer_spike_obj_raw =
    {
        /* cpu_data_spike_each_file */
        {{
        {0.00}, {0.00}, {0.00}, {0.00}, /* spike */
        {0.00}, {0.00}, {0.00}, {0.00}, /* former */
        {0.00}, {0.00}, {0.00}, {0.00}, /* highest */
        {100.00}, {100.00}, {100.00}, {100.00}, /* lowest */
        }},
        /* task_data_spike_each_file */
        {
        {0.00}, {0.00}, /* spike */
        {0.00}, {0.00}, /* former */
        {0.00}, {0.00}, /* highest */
        {999999.00}, {9999999.00}, /* lowest */
        },
        /* pswap_data_spike_each_file */
        {
        {0}, {0}, /* spike */
        {0}, {0}, /* former */
        {0}, {0}, /* highest */
        {999999}, {999999}, /* lowest */
        },
        /* paging_data_spike_each_file */
        {
        {0.00}, {0.00}, {0.00}, {0.00}, {0.00}, /* spike */
        {0.00}, {0.00}, {0.00}, {0.00}, {0.00}, /* former */
        {0.00}, {0.00}, {0.00}, {0.00}, {0.00}, /* highest */
        {999999.00}, {999999.00}, {999999.00}, {999999.00}, {999999.00}, /* lowest */
        },
        /* io_transfer_rate_data_spike_each_file */
        {
        {0.00}, {0.00}, {0.00}, /* spike */
        {0.00}, {0.00}, {0.00}, /* former */
        {0.00}, {0.00}, {0.00}, /* highest */
        {999999.00}, {999999.00}, {999999.00}, /* lowest */
        },
        /* memory_data_spike_each_file */
        {
        {0.00}, {0.00}, {0.00}, /* spike */
        {0.00}, {0.00}, {0.00}, /* former */
        {0.00}, {0.00}, {0.00}, /* highest */
        {999999.00}, {999999.00}, {999999.00}, /* lowest */
        },
        /* swap_data_spike_each_file */
        {
        {0.00}, /* spike */
        {0.00}, /* former */
        {0.00}, /* highest */
        {999999.00}, /* lowest */
        },
        /* kernel_table_data_spike_each_file */
        {
        {0}, {0}, {0}, /* spike */
        {0}, {0}, {0}, /* former */
        {0}, {0}, {0}, /* highest */
        {999999}, {999999}, {999999}, /* lowest */
        },
        /* ldavg_data_spike_each_file */
        {
        {0},{0},{0.00},{0.00},{0.00}, /* spike */
        {0},{0},{0.00},{0.00},{0.00}, /* former */
        {0},{0},{0.00},{0.00},{0.00}, /* highest */
        {999999},{999999},{999999.00},{999999.00},{999999.00}, /* lowest */
        },
        /* block_device_data_spike_each_file */
        {{
        {0.00}, {0.00}, /* spike */
        {0.00}, {0.00}, /* former */
        {0.00}, {0.00}, /* highest */
        {999999.00}, {999999.00}, /* lowest */
        }},
        /* network_data_spike_each_file */
        {{
        {0.00}, {0.00}, {0.00}, {0.00}, {0.00}, {0.00}, {0.00}, {0.00}, /* spike */
        {0.00}, {0.00}, {0.00}, {0.00}, {0.00}, {0.00}, {0.00}, {0.00}, /* former */
        {0.00}, {0.00}, {0.00}, {0.00}, {0.00}, {0.00}, {0.00}, {0.00}, /* highest */
        {999999.00}, {999999.00}, {999999.00}, {999999.00}, {999999.00}, {999999.00}, {999999.00}, {999999.00}, /* lowest */
        //{0.00}, {0.00}, {0.00}, {0.00}, {0.00}, {0.00}, {0.00}, {0.00}, /* down */
        }},

        /* cpu_date_spike_each_file */
        {{
        {""}, {""}, {""}, {""}, /* spike date */
        {""}, {""}, {""}, {""}, /* spike time */
        {""}, {""}, {""}, {""}, /* highest date */
        {""}, {""}, {""}, {""}, /* highest time */
        {""}, {""}, {""}, {""}, /* lowest date */
        {""}, {""}, {""}, {""}, /* lowest time */
        }},
        /* task_date_spike_each_file */
        {
        {""}, {""}, {""}, {""}, /* spike date and time */
        {""}, {""}, {""}, {""}, /* highest date and time */
        {""}, {""}, {""}, {""}, /* lowest date and time */
        },
        /* pswap_date_spike_each_file */
        {
        {""}, {""}, {""}, {""}, /* pswap date and time */
        {""}, {""}, {""}, {""}, /* highest date and time */
        {""}, {""}, {""}, {""}, /* lowest date and time */
        },
        /* paging_date_spike_each_file */
        {
        {""}, {""}, {""}, {""}, /* spike date */
        {""}, {""}, {""}, {""}, /* spike time */
        {""}, {""}, {""}, {""}, /* highest date */
        {""}, {""}, {""}, {""}, /* highest time */
        {""}, {""}, {""}, {""}, /* lowest date */
        {""}, {""}, {""}, {""}, /* lowest time */
        },
        /* io_transfer_rate_date_spike_each_file  */
        {
        {""}, {""}, {""}, {""}, {""}, {""}, /* spike date and time */
        {""}, {""}, {""}, {""}, {""}, {""}, /* highest date and time */
        {""}, {""}, {""}, {""}, {""}, {""}, /* lowest date and time */
        },
        /* memory_date_spike_each_file */
        {
        {""}, {""}, {""}, {""}, {""}, {""}, /* spike date and time */
        {""}, {""}, {""}, {""}, {""}, {""}, /* highest date and time */
        {""}, {""}, {""}, {""}, {""}, {""}, /* lowest date and time */
        },
        /* swap_date_spike_each_file */
        {
        {""}, {""}, /* spike date and time */
        {""}, {""}, /* highest date and time */
        {""}, {""}, /* lowest date and time */
        },
        /* kernel_table_date_spike_each_file */
        {
        {""}, {""}, {""}, {""}, {""}, {""}, /* spike date and time */
        {""}, {""}, {""}, {""}, {""}, {""}, /* highest date and time */
        {""}, {""}, {""}, {""}, {""}, {""}, /* lowest date and time */
        },
        /* ldavg_date_spike_each_file */
        {
        {""}, {""}, {""}, {""}, {""}, /* spike date */
        {""}, {""}, {""}, {""}, {""}, /* spike time */
        {""}, {""}, {""}, {""}, {""}, /* highest date */
        {""}, {""}, {""}, {""}, {""}, /* highest time */
        {""}, {""}, {""}, {""}, {""}, /* lowest date */
        {""}, {""}, {""}, {""}, {""}, /* lowest time */
        },
        /* block_device_date_spike_each_file */
        {{
        {""}, {""}, {""}, {""}, /* spike date and time */
        {""}, {""}, {""}, {""}, /* highest date and time */
        {""}, {""}, {""}, {""}, /* lowest date and time */
        }},
        /* network_date_spike_each_file */
        {{
        {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, /* spike date */
        {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, /* spike time */
        {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, /* highest date */
        {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, /* highest time */
        //{""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, /* lowest date */
        //{""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, /* lowest time */
        /*{"1970-01-01"}, {"1970-01-01"}, {"1970-01-01"}, {"1970-01-01"}, {"1970-01-01"}, {"1970-01-01"}, {"1970-01-01"}, {"1970-01-01"},*/ /* down date */
        /*{"00:00:00"}, {"00:00:00"}, {"00:00:00"}, {"00:00:00"}, {"00:00:00"}, {"00:00:00"}, {"00:00:00"}, {"00:00:00"},*/ /* down time */
        }},
    };

/* 
 *  sar_analyzer_time_span_spike_obj ( this object is for data all -Z option )
 *  When making object, these should be initialized with functions 
 *
 */
struct sar_analyzer_data_time_span_spike_each_file sar_analyzer_time_span_spike_obj_raw =
    {
        /* cpu_data_time_span_spike_each_file */
        {{
        {0.00}, {0.00}, {0.00}, {0.00}, /* spike */
        {0.00}, {0.00}, {0.00}, {0.00}, /* former */
        {0.00}, {0.00}, {0.00}, {0.00}, /* highest */
        {100.00}, {100.00}, {100.00}, {100.00}, /* lowest */
        }},
        /* task_data_time_span_spike_each_file */
        {
        {0.00}, {0.00}, /* spike */
        {0.00}, {0.00}, /* former */
        {0.00}, {0.00}, /* highest */
        {999999.00}, {999999.00}, /* lowest */
        },
        /* pswap_data_time_span_spike_each_file */
        {
        {0}, {0}, /* spike */
        {0}, {0}, /* former */
        {0}, {0}, /* highest */
        {999999}, {999999}, /* lowest */
        },
        /* paging_data_time_span_spike_each_file */
        {
        {0.00}, {0.00}, {0.00}, {0.00}, {0.00}, /* spike */
        {0.00}, {0.00}, {0.00}, {0.00}, {0.00}, /* former */
        {0.00}, {0.00}, {0.00}, {0.00}, {0.00}, /* highest */
        {999999.00}, {999999.00}, {999999.00}, {999999.00}, {999999.00}, /* lowest */
        },
        /* io_transfer_rate_data_time_span_spike_each_file */
        {
        {0.00}, {0.00}, {0.00}, /* spike */
        {0.00}, {0.00}, {0.00}, /* former */
        {0.00}, {0.00}, {0.00}, /* highest */
        {999999.00}, {999999.00}, {999999.00}, /* lowest */
        },
        /* memory_data_time_span_spike_each_file */
        {
        {0.00}, {0.00}, {0.00}, /* spike */
        {0.00}, {0.00}, {0.00}, /* former */
        {0.00}, {0.00}, {0.00}, /* highest */
        {999999.00}, {999999.00}, {999999.00}, /* lowest */
        },
        /* swap_data_time_span_spike_each_file */
        {
        {0.00}, /* spike */
        {0.00}, /* former */
        {0.00}, /* highest */
        {999999.00}, /* lowest */
        },
        /* kernel_table_data_time_span_spike_each_file */
        {
        {0}, {0}, {0}, /* spike */
        {0}, {0}, {0}, /* former */
        {0}, {0}, {0}, /* highest */
        {999999}, {999999}, {999999}, /* lowest */
        },
        /* ldavg_data_time_span_spike_each_file */
        {
        {0},{0},{0.00},{0.00},{0.00}, /* spike */
        {0},{0},{0.00},{0.00},{0.00}, /* former */
        {0},{0},{0.00},{0.00},{0.00}, /* highest */
        {999999},{999999},{999999.00},{999999.00},{999999.00}, /* lowest */
        },
        /* block_device_data_time_span_spike_each_file */
        {{
        {0.00}, {0.00}, /* spike */
        {0.00}, {0.00}, /* former */
        {0.00}, {0.00}, /* highest */
        {999999.00}, {999999.00}, /* lowest */
        }},
        /* network_data_time_span_spike_each_file */
        {{
        {0.00}, {0.00}, {0.00}, {0.00}, {0.00}, {0.00}, {0.00}, {0.00}, /* spike */
        {0.00}, {0.00}, {0.00}, {0.00}, {0.00}, {0.00}, {0.00}, {0.00}, /* former */
        {0.00}, {0.00}, {0.00}, {0.00}, {0.00}, {0.00}, {0.00}, {0.00}, /* highest */
        {999999.00}, {999999.00}, {999999.00}, {999999.00}, {999999.00}, {999999.00}, {999999.00}, {999999.00}, /* lowest */
        }},

        /* cpu_date_time_span_spike_each_file */
        {{
        {""}, {""}, {""}, {""}, /* spike date */
        {""}, {""}, {""}, {""}, /* spike time */
        {""}, {""}, {""}, {""}, /* highest date */
        {""}, {""}, {""}, {""}, /* highest time */
        {""}, {""}, {""}, {""}, /* lowest date */
        {""}, {""}, {""}, {""}, /* lowest time */
        }},
        /* task_date_time_span_spike_each_file */
        {
        {""}, {""}, {""}, {""}, /* spike date and time */
        {""}, {""}, {""}, {""}, /* highest date and time */
        {""}, {""}, {""}, {""}, /* lowest date and time */
        },
        /* pswap_date_time_span_spike_each_file */
        {
        {""}, {""}, {""}, {""}, /* pswap date and time */
        {""}, {""}, {""}, {""}, /* highest date and time */
        {""}, {""}, {""}, {""}, /* lowest date and time */
        },
        /* paging_date_time_span_spike_each_file */
        {
        {""}, {""}, {""}, {""}, /* spike date */
        {""}, {""}, {""}, {""}, /* spike time */
        {""}, {""}, {""}, {""}, /* highest date */
        {""}, {""}, {""}, {""}, /* highest time */
        {""}, {""}, {""}, {""}, /* lowest date */
        {""}, {""}, {""}, {""}, /* lowest time */
        },
        /* io_transfer_rate_date_time_span_spike_each_file  */
        {
        {""}, {""}, {""}, {""}, {""}, {""}, /* spike date and time */
        {""}, {""}, {""}, {""}, {""}, {""}, /* highest date and time */
        {""}, {""}, {""}, {""}, {""}, {""}, /* lowest date and time */
        },
        /* memory_date_time_span_spike_each_file */
        {
        {""}, {""}, {""}, {""}, {""}, {""}, /* spike date and time */
        {""}, {""}, {""}, {""}, {""}, {""}, /* highest date and time */
        {""}, {""}, {""}, {""}, {""}, {""}, /* lowest date and time */
        },
        /* swap_date_time_span_spike_each_file */
        {
        {""}, {""}, /* spike date and time */
        {""}, {""}, /* highest date and time */
        {""}, {""}, /* lowest date and time */
        },
        /* kernel_table_date_time_span_spike_each_file */
        {
        {""}, {""}, {""}, {""}, {""}, {""}, /* spike date and time */
        {""}, {""}, {""}, {""}, {""}, {""}, /* highest date and time */
        {""}, {""}, {""}, {""}, {""}, {""}, /* lowest date and time */
        },
        /* ldavg_date_time_span_spike_each_file */
        {
        {""}, {""}, {""}, {""}, {""}, /* spike date */
        {""}, {""}, {""}, {""}, {""}, /* spike time */
        {""}, {""}, {""}, {""}, {""}, /* highest date */
        {""}, {""}, {""}, {""}, {""}, /* highest time */
        {""}, {""}, {""}, {""}, {""}, /* lowest date */
        {""}, {""}, {""}, {""}, {""}, /* lowest time */
        },
        /* block_device_date_time_span_spike_each_file */
        {{
        {""}, {""}, {""}, {""}, /* spike date and time */
        {""}, {""}, {""}, {""}, /* highest date and time */
        {""}, {""}, {""}, {""}, /* lowest date and time */
        }},
        /* network_date_time_span_spike_each_file */
        {{
        {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, /* spike date */
        {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, /* spike time */
        {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, /* highest date */
        {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, /* highest time */
        //{""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, /* lowest date */
        //{""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, /* lowest time */
        }},
    };


/* line_obj */
struct line_data line_obj_raw =
    {
        "", /* each line */
        NULL /* next pointer */
    };
/* line_obj_all */
struct line_data line_all_obj_raw =
    {
        "", /* each line */
        NULL /* next pointer */
    };

/* header_obj */
struct line_data header_obj_raw =
    {
        "", /* each line */
        NULL /* next pointer */
    };

/* report_obj */
struct line_data report_obj_raw =
    {
        "", /* each line */
        NULL /* next pointer */
    };

/* report_cpu_obj */
struct line_data report_cpu_obj_raw =
    {
        "", /* each line */
        NULL /* next pointer */
    };

/* report_cpu_spike_obj */
struct line_data report_cpu_spike_obj_raw =
    {
        "", /* each line */
        NULL /* next pointer */
    };

/* report_cpu_time_span_spike_obj */
struct line_data report_cpu_time_span_spike_obj_raw =
    {
        "", /* each line */
        NULL /* next pointer */
    };

/* report_cpu_explanation_obj */
struct line_data report_cpu_explanation_obj_raw =
    {
        "", /* each line */
        NULL /* next pointer */
    };

/* report_tasks_obj */
struct line_data report_tasks_obj_raw =
    {
        "", /* each line */
        NULL /* next pointer */
    };

/* report_tasks_spike_obj */
struct line_data report_tasks_spike_obj_raw =
    {
        "", /* each line */
        NULL /* next pointer */
    };

/* report_tasks_time_span_spike_obj */
struct line_data report_tasks_time_span_spike_obj_raw =
    {
        "", /* each line */
        NULL /* next pointer */
    };

/* report_tasks_explanation_obj */
struct line_data report_tasks_explanation_obj_raw =
    {
        "", /* each line */
        NULL /* next pointer */
    };

/* report_pswap_obj */
struct line_data report_pswap_obj_raw =
    {
        "", /* each line */
        NULL /* next pointer */
    };

/* report_pswap_spike_obj */
struct line_data report_pswap_spike_obj_raw =
    {
        "", /* each line */
        NULL /* next pointer */
    };

/* report_pswap_time_span_spike_obj */
struct line_data report_pswap_time_span_spike_obj_raw =
    {
        "", /* each line */
        NULL /* next pointer */
    };

/* report_pswap_explanation_obj */
struct line_data report_pswap_explanation_obj_raw =
    {
        "", /* each line */
        NULL /* next pointer */
    };

/* report_paging_obj */
struct line_data report_paging_obj_raw =
    {
        "", /* each line */
        NULL /* next pointer */
    };

/* report_paging_spike_obj */
struct line_data report_paging_spike_obj_raw =
    {
        "", /* each line */
        NULL /* next pointer */
    };

/* report_paging_time_span_spike_obj */
struct line_data report_paging_time_span_spike_obj_raw =
    {
        "", /* each line */
        NULL /* next pointer */
    };

/* report_paging_explanation_obj */
struct line_data report_paging_explanation_obj_raw =
    {
        "", /* each line */
        NULL /* next pointer */
    };

/* report_io_transfer_rate_obj */
struct line_data report_io_transfer_rate_obj_raw =
    {
        "", /* each line */
        NULL /* next pointer */
    };

/* report_io_transfer_rate_spike_obj */
struct line_data report_io_transfer_rate_spike_obj_raw =
    {
        "", /* each line */
        NULL /* next pointer */
    };

/* report_io_transfer_rate_time_span_spike_obj */
struct line_data report_io_transfer_rate_time_span_spike_obj_raw =
    {
        "", /* each line */
        NULL /* next pointer */
    };

/* report_io_transfer_rate_explanation_obj */
struct line_data report_io_transfer_rate_explanation_obj_raw =
    {
        "", /* each line */
        NULL /* next pointer */
    };

/* report_memory_obj */
struct line_data report_memory_obj_raw =
    {
        "", /* each line */
        NULL /* next pointer */
    };

/* report_memory_spike_obj */
struct line_data report_memory_spike_obj_raw =
    {
        "", /* each line */
        NULL /* next pointer */
    };

/* report_memory_time_span_spike_obj */
struct line_data report_memory_time_span_spike_obj_raw =
    {
        "", /* each line */
        NULL /* next pointer */
    };

/* report_memory_explanation_obj */
struct line_data report_memory_explanation_obj_raw =
    {
        "", /* each line */
        NULL /* next pointer */
    };

/* report_swpused_obj */
struct line_data report_swpused_obj_raw =
    {
        "", /* each line */
        NULL /* next pointer */
    };

/* report_swpused_spike_obj */
struct line_data report_swpused_spike_obj_raw =
    {
        "", /* each line */
        NULL /* next pointer */
    };

/* report_swpused_time_span_spike_obj */
struct line_data report_swpused_time_span_spike_obj_raw =
    {
        "", /* each line */
        NULL /* next pointer */
    };

/* report_swpused_explanation_obj */
struct line_data report_swpused_explanation_obj_raw =
    {
        "", /* each line */
        NULL /* next pointer */
    };

/* report_kernel_table_obj */
struct line_data report_kernel_table_obj_raw =
    {
        "", /* each line */
        NULL /* next pointer */
    };

/* report_kernel_table_spike_obj */
struct line_data report_kernel_table_spike_obj_raw =
    {
        "", /* each line */
        NULL /* next pointer */
    };

/* report_kernel_table_time_span_spike_obj */
struct line_data report_kernel_table_time_span_spike_obj_raw =
    {
        "", /* each line */
        NULL /* next pointer */
    };

/* report_kernel_table_explanation_obj */
struct line_data report_kernel_table_explanation_obj_raw =
    {
        "", /* each line */
        NULL /* next pointer */
    };

/* report_ldavg_obj */
struct line_data report_ldavg_obj_raw =
    {
        "", /* each line */
        NULL /* next pointer */
    };

/* report_ldavg_spike_obj */
struct line_data report_ldavg_spike_obj_raw =
    {
        "", /* each line */
        NULL /* next pointer */
    };

/* report_ldavg_time_span_spike_obj */
struct line_data report_ldavg_time_span_spike_obj_raw =
    {
        "", /* each line */
        NULL /* next pointer */
    };

/* report_ldavg_explanation_obj */
struct line_data report_ldavg_explanation_obj_raw =
    {
        "", /* each line */
        NULL /* next pointer */
    };

/* report_block_device_obj */
struct line_data report_block_device_obj_raw =
    {
        "", /* each line */
        NULL /* next pointer */
    };

/* report_block_device_spike_obj */
struct line_data report_block_device_spike_obj_raw =
    {
        "", /* each line */
        NULL /* next pointer */
    };

/* report_block_device_time_span_spike_obj */
struct line_data report_block_device_time_span_spike_obj_raw =
    {
        "", /* each line */
        NULL /* next pointer */
    };

/* report_block_device_explanation_obj */
struct line_data report_block_device_explanation_obj_raw =
    {
        "", /* each line */
        NULL /* next pointer */
    };

/* report_network_obj */
struct line_data report_network_obj_raw =
    {
        "", /* each line */
        NULL /* next pointer */
    };

/* report_network_spike_obj */
struct line_data report_network_spike_obj_raw =
    {
        "", /* each line */
        NULL /* next pointer */
    };

/* report_network_time_span_spike_obj */
struct line_data report_network_time_span_spike_obj_raw =
    {
        "", /* each line */
        NULL /* next pointer */
    };

/* report_network_explanation_obj */
struct line_data report_network_explanation_obj_raw =
    {
        "", /* each line */
        NULL /* next pointer */
    };

/* report_network_error_obj */
struct line_data report_network_error_obj_raw =
    {
        "", /* each line */
        NULL /* next pointer */
    };

/* report_network_error_spike_obj */
struct line_data report_network_error_spike_obj_raw =
    {
        "", /* each line */
        NULL /* next pointer */
    };

/* report_network_error_time_span_spike_obj */
struct line_data report_network_error_time_span_spike_obj_raw =
    {
        "", /* each line */
        NULL /* next pointer */
    };

/* report_network_error_explanation_obj */
struct line_data report_network_error_explanation_obj_raw =
    {
        "", /* each line */
        NULL /* next pointer */
    };

/* report_thrashing_obj */
struct line_data report_thrashing_obj_raw =
    {
        "", /* each line */
        NULL /* next pointer */
    };

/* report_network_down_obj */
struct line_data report_network_down_obj_raw =
    {
        "", /* each line */
        NULL /* next pointer */
    };

/* report_overall_judgement_obj */
struct line_data report_overall_judgement_obj_raw =
    {
        "", /* each line */
        NULL /* next pointer */
    };

/* svg_common_cpu_obj */
struct line_data svg_common_cpu_obj_raw =
    {
        "", /* each line */
        NULL /* next pointer */
    };

/* svg_cpu_usr_obj */
struct line_data2 svg_cpu_usr_obj_raw =
    {
        "", /* each line */
        "", /* each line */
        NULL /* next pointer */
    };

/* svg_cpu_sys_obj */
struct line_data2 svg_cpu_sys_obj_raw =
    {
        "", /* each line */
        "", /* each line */
        NULL /* next pointer */
    };

/* declaring pointers */
struct sar_analyzer_data *sar_analyzer_obj = &sar_analyzer_obj_raw;
struct sar_analyzer_data_all *sar_analyzer_all_obj = &sar_analyzer_all_obj_raw;
struct sar_analyzer_data_spike_each_file *sar_analyzer_spike_obj = &sar_analyzer_spike_obj_raw;
struct sar_analyzer_data_time_span_spike_each_file *sar_analyzer_time_span_spike_obj = &sar_analyzer_time_span_spike_obj_raw;

/* declaring pointers */
struct line_data *line_obj = &line_obj_raw;
struct line_data *line_all_obj = &line_all_obj_raw;
struct line_data *header_obj = &header_obj_raw;
struct line_data *report_obj = &report_obj_raw;
struct line_data *report_cpu_obj = &report_cpu_obj_raw;
struct line_data *report_cpu_spike_obj [ MAX_CORE_NUMBERS ] =  { &report_cpu_spike_obj_raw };
struct line_data *report_cpu_time_span_spike_obj [ MAX_CORE_NUMBERS ] =  { &report_cpu_time_span_spike_obj_raw };
struct line_data *report_cpu_explanation_obj = &report_cpu_explanation_obj_raw;
struct line_data *report_tasks_obj = &report_tasks_obj_raw;
struct line_data *report_tasks_spike_obj = &report_tasks_spike_obj_raw;
struct line_data *report_tasks_time_span_spike_obj = &report_tasks_time_span_spike_obj_raw;
struct line_data *report_tasks_explanation_obj = &report_tasks_explanation_obj_raw;
struct line_data *report_pswap_obj = &report_pswap_obj_raw;
struct line_data *report_pswap_spike_obj = &report_pswap_spike_obj_raw;
struct line_data *report_pswap_time_span_spike_obj = &report_pswap_time_span_spike_obj_raw;
struct line_data *report_pswap_explanation_obj = &report_pswap_explanation_obj_raw;
struct line_data *report_paging_obj = &report_paging_obj_raw;
struct line_data *report_paging_spike_obj = &report_paging_spike_obj_raw;
struct line_data *report_paging_time_span_spike_obj = &report_paging_time_span_spike_obj_raw;
struct line_data *report_paging_explanation_obj = &report_paging_explanation_obj_raw;
struct line_data *report_io_transfer_rate_obj = &report_io_transfer_rate_obj_raw;
struct line_data *report_io_transfer_rate_spike_obj = &report_io_transfer_rate_spike_obj_raw;
struct line_data *report_io_transfer_rate_time_span_spike_obj = &report_io_transfer_rate_time_span_spike_obj_raw;
struct line_data *report_io_transfer_rate_explanation_obj = &report_io_transfer_rate_explanation_obj_raw;
struct line_data *report_memory_obj = &report_memory_obj_raw;
struct line_data *report_memory_spike_obj = &report_memory_spike_obj_raw;
struct line_data *report_memory_time_span_spike_obj = &report_memory_time_span_spike_obj_raw;
struct line_data *report_memory_explanation_obj = &report_memory_explanation_obj_raw;
struct line_data *report_swpused_obj = &report_swpused_obj_raw;
struct line_data *report_swpused_spike_obj = &report_swpused_spike_obj_raw;
struct line_data *report_swpused_time_span_spike_obj = &report_swpused_time_span_spike_obj_raw;
struct line_data *report_swpused_explanation_obj = &report_swpused_explanation_obj_raw;
struct line_data *report_kernel_table_obj = &report_kernel_table_obj_raw;
struct line_data *report_kernel_table_spike_obj = &report_kernel_table_spike_obj_raw;
struct line_data *report_kernel_table_time_span_spike_obj = &report_kernel_table_time_span_spike_obj_raw;
struct line_data *report_kernel_table_explanation_obj = &report_kernel_table_explanation_obj_raw;
struct line_data *report_ldavg_obj = &report_ldavg_obj_raw;
struct line_data *report_ldavg_spike_obj = &report_ldavg_spike_obj_raw;
struct line_data *report_ldavg_time_span_spike_obj = &report_ldavg_time_span_spike_obj_raw;
struct line_data *report_ldavg_explanation_obj = &report_ldavg_explanation_obj_raw;
struct line_data *report_block_device_obj = &report_block_device_obj_raw;
struct line_data *report_block_device_spike_obj [ MAX_BLOCK_DEVICE_NUMBERS ] =  { &report_block_device_spike_obj_raw };
struct line_data *report_block_device_time_span_spike_obj [ MAX_BLOCK_DEVICE_NUMBERS ] =  { &report_block_device_time_span_spike_obj_raw };
struct line_data *report_block_device_explanation_obj = &report_block_device_explanation_obj_raw;
struct line_data *report_network_obj = &report_network_obj_raw;
struct line_data *report_network_spike_obj [ MAX_NETWORK_DEVICE_NUMBERS ] =  { &report_network_spike_obj_raw };
struct line_data *report_network_time_span_spike_obj [ MAX_NETWORK_DEVICE_NUMBERS ] =  { &report_network_time_span_spike_obj_raw };
struct line_data *report_network_explanation_obj = &report_network_explanation_obj_raw;
struct line_data *report_network_error_obj = &report_network_error_obj_raw;
struct line_data *report_network_error_spike_obj [ MAX_NETWORK_DEVICE_NUMBERS ] =  { &report_network_error_spike_obj_raw };
struct line_data *report_network_error_time_span_spike_obj [ MAX_NETWORK_DEVICE_NUMBERS ] =  { &report_network_error_time_span_spike_obj_raw };
struct line_data *report_network_error_explanation_obj = &report_network_error_explanation_obj_raw;
struct line_data *report_thrashing_obj = &report_thrashing_obj_raw;
struct line_data *report_network_down_obj [ MAX_NETWORK_DEVICE_NUMBERS ] = { &report_network_down_obj_raw };
struct line_data *report_overall_judgement_obj = &report_overall_judgement_obj_raw;
/* for each file */
struct line_data *svg_common_cpu_obj = &svg_common_cpu_obj_raw;
/* for file cpu */
struct line_data2* svg_cpu_usr_obj = &svg_cpu_usr_obj_raw;
struct line_data2* svg_cpu_sys_obj = &svg_cpu_sys_obj_raw;

/*
 *  This function initialzes check int
 *  check int applies to each analyzing item
 *
 *  Caller : get_word_line()
 *
 */
void initialize_check_int ( void );

/* 
 *  This function converts am-pm style to abs style.
 *
 */
static void set_pm_to_abs_time ( char *time_value );

/* 
 *  This function checks column number and sets needed member to the struct. 
 *  Members are used to read item data by 'set_token_items()'. 
 *
 *  Caller : get_word_line()
 *
 * Calls : setters 
 */
/* restart should be 1 when RESTART string appears */
int set_token_column ( int file_number, char *line, const char *item_name_for_column, int restart, int SAR_OPTION );

/* 
 *  This function sets needed item values to the struct.
 *  Most of them are double but some of them are int type. 
 *  'utility' is used for numbers for cpu or device analyzing. 
 *
 *  Caller : read_sar() 
 *
 *  Calls : setters and getters
 *
 */
int set_token_items ( int file_number, char **line, const char *item_name, int utility, int SAR_OPTION, const char *time_span, int PM );

/* 
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
int get_word_line ( int file_number, char **line, int SAR_OPTION, int MESSAGE_ONLY, const char *time_span );

/**** setter ****/
void set_hostname ( char *hostname );
void set_dir_name_analyze ( const char *dname );
void set_core_numbers ( int x );
void set_title_strings ( int x, const char *title_strings );
void set_network_device_names ( const char *network_device_name );
void set_block_device_names ( const char *block_device_name );
void set_title_strings_first_file ( int x, const char *title_strings );
void set_this_date ( const char *date_string );
void set_this_date_all ( const char *date_string );
int search_block_device_name ( const char *block_device_name );

/* columns */
int set_column_cpu ( int var, const char *element );
int set_column_tasks ( int var, const char *element );
int set_column_pswap ( int var, const char *element );
int set_column_paging ( int var, const char *element );
int set_column_io_transfer_rate ( int var, const char *element );
int set_column_memory ( int var, const char *element );
int set_column_swpused ( int var );
int set_column_kernel_table ( int var, const char *element );
int set_column_ldavg ( int var, const char *element );
int set_column_block_device ( int var, const char *element );
int set_column_network ( int var, const char *element );

/* spike val each file */
int set_cpu_spike_val_each_file ( int x, double var, int y, const char *element, const char *analyze_item );
int set_tasks_spike_val_each_file ( int x, double var, const char *element, const char *analyze_item );
int set_pswap_spike_val_each_file ( int x, double var, const char *element, const char *analyze_item );
int set_paging_spike_val_each_file ( int x, double var, const char *element, const char *analyze_item );
int set_io_transfer_rate_spike_val_each_file ( int x, double var, const char *element, const char *analyze_item );
int set_memory_double_spike_val_each_file ( int x, double var, const char *element, const char *analyze_item );
int set_memory_int_spike_val_each_file ( int x, int var, const char *element, const char *analyze_item );
int set_swpused_spike_val_each_file ( int x,  double var, const char *analyze_item );
int set_kernel_table_spike_val_each_file ( int x,  double var, const char *element, const char *analyze_item );
int set_ldavg_int_spike_val_each_file ( int x,  int var, const char *element, const char *analyze_item );
int set_ldavg_double_spike_val_each_file ( int x,  double var, const char *element, const char *analyze_item );
int set_block_device_spike_val_each_file ( int x,  double var, int y, const char *element, const char *analyze_item );
int set_network_spike_val_each_file ( int x,  double var, int y, const char *element, const char *analyze_item );

/* time-span spike val each file */
int set_cpu_time_span_spike_val_each_file ( int x, double var, int y, const char *element, const char *analyze_item );
int set_tasks_time_span_spike_val_each_file ( int x, double var, const char *element, const char *analyze_item );
int set_pswap_time_span_spike_val_each_file ( int x, double var, const char *element, const char *analyze_item );
int set_paging_time_span_spike_val_each_file ( int x, double var, const char *element, const char *analyze_item );
int set_io_transfer_rate_time_span_spike_val_each_file ( int x, double var, const char *element, const char *analyze_item );
int set_memory_double_time_span_spike_val_each_file ( int x, double var, const char *element, const char *analyze_item );
int set_memory_int_time_span_spike_val_each_file ( int x, int var, const char *element, const char *analyze_item );
int set_swpused_time_span_spike_val_each_file ( int x,  double var, const char *analyze_item );
int set_kernel_table_time_span_spike_val_each_file ( int x,  double var, const char *element, const char *analyze_item );
int set_ldavg_int_time_span_spike_val_each_file ( int x,  int var, const char *element, const char *analyze_item );
int set_ldavg_double_time_span_spike_val_each_file ( int x,  double var, const char *element, const char *analyze_item );
int set_block_device_time_span_spike_val_each_file ( int x,  double var, int y, const char *element, const char *analyze_item );
int set_network_time_span_spike_val_each_file ( int x,  double var, int y, const char *element, const char *analyze_item );

/* spike date */
int set_cpu_spike_date ( const char *date_string, int x, const char *element );
int set_tasks_spike_date ( const char *date_string, const char *element );
int set_pswap_spike_date ( const char *date_string, const char *element );
int set_paging_spike_date ( const char *date_string, const char *element );
int set_io_transfer_rate_spike_date ( const char *date_string, const char *element );
int set_memory_spike_date ( const char *date_string, const char *element );
int set_swpused_spike_date ( const char *date_string );
int set_kernel_table_spike_date ( const char *date_string, const char *element );
int set_ldavg_spike_date ( const char *date_string, const char *element );
int set_block_device_spike_date ( const char *date_string, int x, const char *element );
int set_network_spike_date ( const char *date_string, int x, const char *element );

/* spike time */
int set_cpu_spike_time ( const char *date_string, int x, const char *element );
int set_tasks_spike_time ( const char *date_string, const char *element );
int set_pswap_spike_time ( const char *date_string, const char *element );
int set_paging_spike_time ( const char *date_string, const char *element );
int set_io_transfer_rate_spike_time ( const char *date_string, const char *element );
int set_memory_spike_time ( const char *date_string, const char *element );
int set_swpused_spike_time ( const char *date_string );
int set_kernel_table_spike_time ( const char *date_string, const char *element );
int set_ldavg_spike_time ( const char *date_string, const char *element );
int set_block_device_spike_time ( const char *date_string, int x, const char *element );
int set_network_spike_time ( const char *date_string, int x, const char *element );

/* spike date each file */
int set_cpu_spike_date_each_file ( int x, const char *date_string, int y, const char *element, const char *analyze_item );
int set_tasks_spike_date_each_file ( int x, const char *date_string, const char *element, const char *analyze_item );
int set_pswap_spike_date_each_file ( int x, const char *date_string, const char *element, const char *analyze_item );
int set_paging_spike_date_each_file ( int x, const char *date_string, const char *element, const char *analyze_item );
int set_io_transfer_rate_spike_date_each_file ( int x, const char *date_string, const char *element, const char *analyze_item );
int set_memory_spike_date_each_file ( int x, const char *date_string, const char *element, const char *analyze_item );
int set_swpused_spike_date_each_file ( int x, const char *date_string, const char *analyze_item );
int set_kernel_table_spike_date_each_file ( int x, const char *date_string, const char *element, const char *analyze_item );
int set_ldavg_spike_date_each_file ( int x, const char *date_string, const char *element, const char *analyze_item );
int set_block_device_spike_date_each_file ( int x, const char *date_string, int y, const char *element, const char *analyze_item );
int set_network_spike_date_each_file ( int x, const char *date_string, int y, const char *element, const char *analyze_item );

/* spike time each file */
int set_cpu_spike_time_each_file ( int x, const char *date_string, int y, const char *element, const char *analyze_item );
int set_tasks_spike_time_each_file ( int x, const char *date_string, const char *element, const char *analyze_item );
int set_pswap_spike_time_each_file ( int x, const char *date_string, const char *element, const char *analyze_item );
int set_paging_spike_time_each_file ( int x, const char *date_string, const char *element, const char *analyze_item );
int set_io_transfer_rate_spike_time_each_file ( int x, const char *date_string, const char *element, const char *analyze_item );
int set_memory_spike_time_each_file ( int x, const char *date_string, const char *element, const char *analyze_item );
int set_swpused_spike_time_each_file ( int x, const char *date_string, const char *analyze_item );
int set_kernel_table_spike_time_each_file ( int x, const char *date_string, const char *element, const char *analyze_item );
int set_ldavg_spike_time_each_file ( int x, const char *date_string, const char *element, const char *analyze_item );
int set_block_device_spike_time_each_file ( int x, const char *date_string, int y, const char *element, const char *analyze_item );
int set_network_spike_time_each_file ( int x, const char *date_string, int y, const char *element, const char *analyze_item );

/* time-span spike date each file */
int set_cpu_time_span_spike_date_each_file ( int x, const char *date_string, int y, const char *element, const char *analyze_item );
int set_tasks_time_span_spike_date_each_file ( int x, const char *date_string, const char *element, const char *analyze_item );
int set_pswap_time_span_spike_date_each_file ( int x, const char *date_string, const char *element, const char *analyze_item );
int set_paging_time_span_spike_date_each_file ( int x, const char *date_string, const char *element, const char *analyze_item );
int set_io_transfer_rate_time_span_spike_date_each_file ( int x, const char *date_string, const char *element, const char *analyze_item );
int set_memory_time_span_spike_date_each_file ( int x, const char *date_string, const char *element, const char *analyze_item );
int set_swpused_time_span_spike_date_each_file ( int x, const char *date_string, const char *analyze_item );
int set_kernel_table_time_span_spike_date_each_file ( int x, const char *date_string, const char *element, const char *analyze_item );
int set_ldavg_time_span_spike_date_each_file ( int x, const char *date_string, const char *element, const char *analyze_item );
int set_block_device_time_span_spike_date_each_file ( int x, const char *date_string, int y, const char *element, const char *analyze_item );
int set_network_time_span_spike_date_each_file ( int x, const char *date_string, int y, const char *element, const char *analyze_item );

/* time-span spike time each file */
int set_cpu_time_span_spike_time_each_file ( int x, const char *date_string, int y, const char *element, const char *analyze_item );
int set_tasks_time_span_spike_time_each_file ( int x, const char *date_string, const char *element, const char *analyze_item );
int set_pswap_time_span_spike_time_each_file ( int x, const char *date_string, const char *element, const char *analyze_item );
int set_paging_time_span_spike_time_each_file ( int x, const char *date_string, const char *element, const char *analyze_item );
int set_io_transfer_rate_time_span_spike_time_each_file ( int x, const char *date_string, const char *element, const char *analyze_item );
int set_memory_time_span_spike_time_each_file ( int x, const char *date_string, const char *element, const char *analyze_item );
int set_swpused_time_span_spike_time_each_file ( int x, const char *date_string, const char *analyze_item );
int set_kernel_table_time_span_spike_time_each_file ( int x, const char *date_string, const char *element, const char *analyze_item );
int set_ldavg_time_span_spike_time_each_file ( int x, const char *date_string, const char *element, const char *analyze_item );
int set_block_device_time_span_spike_time_each_file ( int x, const char *date_string, int y, const char *element, const char *analyze_item );
int set_network_time_span_spike_time_each_file ( int x, const char *date_string, int y, const char *element, const char *analyze_item );

/* former val each file */
int set_cpu_former_val_each_file ( int x, double var, int y, const char *element );
int set_tasks_former_val_each_file ( int x, double var, const char *element );
int set_pswap_former_val_each_file ( int x, double var, const char *element );
int set_paging_former_val_each_file ( int x, double var, const char *element );
int set_io_transfer_rate_former_val_each_file ( int x, double var, const char *element );
int set_memory_double_former_val_each_file ( int x, double var, const char *element );
int set_memory_int_former_val_each_file ( int x, int var, const char *element );
int set_swpused_former_val_each_file ( int x,  double var );
int set_kernel_table_former_val_each_file ( int x,  double var, const char *element );
int set_ldavg_int_former_val_each_file ( int x,  int var, const char *element );
int set_ldavg_double_former_val_each_file ( int x,  double var, const char *element );
int set_block_device_former_val_each_file ( int x,  double var, int y, const char *element );
int set_network_former_val_each_file ( int x,  double var, int y, const char *element );

/* time-span former val each file */
int set_cpu_time_span_former_val_each_file ( int x, double var, int y, const char *element );
int set_tasks_time_span_former_val_each_file ( int x, double var, const char *element );
int set_pswap_time_span_former_val_each_file ( int x, double var, const char *element );
int set_paging_time_span_former_val_each_file ( int x, double var, const char *element );
int set_io_transfer_rate_time_span_former_val_each_file ( int x, double var, const char *element );
int set_memory_double_time_span_former_val_each_file ( int x, double var, const char *element );
int set_memory_int_time_span_former_val_each_file ( int x, int var, const char *element );
int set_swpused_time_span_former_val_each_file ( int x,  double var );
int set_kernel_table_time_span_former_val_each_file ( int x,  double var, const char *element );
int set_ldavg_int_time_span_former_val_each_file ( int x,  int var, const char *element );
int set_ldavg_double_time_span_former_val_each_file ( int x,  double var, const char *element );
int set_block_device_time_span_former_val_each_file ( int x,  double var, int y, const char *element );
int set_network_time_span_former_val_each_file ( int x,  double var, int y, const char *element );

/* average highest date */
int set_cpu_avg_highest_date ( const char *date_string, int x, const char *element );
int set_tasks_avg_highest_date ( const char *date_string, const char *element );
int set_pswap_avg_highest_date ( const char *date_string, const char *element );
int set_paging_avg_highest_date ( const char *date_string, const char *element );
int set_io_transfer_rate_avg_highest_date ( const char *date_string, const char *element );
int set_memory_avg_highest_date ( const char *date_string, const char *element );
int set_swpused_avg_highest_date ( const char *date_string );
int set_kernel_table_avg_highest_date ( const char *date_string, const char *element );
int set_ldavg_avg_highest_date ( const char *date_string, const char *element );
int set_block_device_avg_highest_date ( const char *date_string, int x, const char *element );
int set_network_avg_highest_date ( const char *date_string, int x, const char *element );

/* highest date */
int set_cpu_highest_date ( const char *date_string, int x, const char *element );
int set_tasks_highest_date ( const char *date_string, const char *element );
int set_pswap_highest_date ( const char *date_string, const char *element );
int set_paging_highest_date ( const char *date_string, const char *element );
int set_io_transfer_rate_highest_date ( const char *date_string, const char *element );
int set_memory_highest_date ( const char *date_string, const char *element );
int set_swpused_highest_date ( const char *date_string );
int set_kernel_table_highest_date ( const char *date_string, const char *element );
int set_ldavg_highest_date ( const char *date_string, const char *element );
int set_block_device_highest_date ( const char *date_string, int x, const char *element );
int set_network_highest_date ( const char *date_string, int x, const char *element );

/* highest time */
int set_cpu_highest_time ( const char *date_string, int x, const char *element );
int set_tasks_highest_time ( const char *date_string, const char *element );
int set_pswap_highest_time ( const char *date_string, const char *element );
int set_paging_highest_time ( const char *date_string, const char *element );
int set_io_transfer_rate_highest_time ( const char *date_string, const char *element );
int set_memory_highest_time ( const char *date_string, const char *element );
int set_swpused_highest_time ( const char *date_string );
int set_kernel_table_highest_time ( const char *date_string, const char *element );
int set_ldavg_highest_time ( const char *date_string, const char *element );
int set_block_device_highest_time ( const char *date_string, int x, const char *element );
int set_network_highest_time ( const char *date_string, int x, const char *element );

/* average lowest date */
int set_cpu_avg_lowest_date ( const char *date_string, int x, const char *element );
int set_tasks_avg_lowest_date ( const char *date_string, const char *element );
int set_pswap_avg_lowest_date ( const char *date_string, const char *element );
int set_paging_avg_lowest_date ( const char *date_string, const char *element );
int set_io_transfer_rate_avg_lowest_date ( const char *date_string, const char *element );
int set_memory_avg_lowest_date ( const char *date_string, const char *element );
int set_swpused_avg_lowest_date ( const char *date_string );
int set_kernel_table_avg_lowest_date ( const char *date_string, const char *element );
int set_ldavg_avg_lowest_date ( const char *date_string, const char *element );
int set_block_device_avg_lowest_date ( const char *date_string, int x, const char *element );
int set_network_avg_lowest_date ( const char *date_string, int x, const char *element );

/* lowest date */
int set_cpu_lowest_date ( const char *date_string, int x, const char *element );
int set_tasks_lowest_date ( const char *date_string, const char *element );
int set_pswap_lowest_date ( const char *date_string, const char *element );
int set_paging_lowest_date ( const char *date_string, const char *element );
int set_io_transfer_rate_lowest_date ( const char *date_string, const char *element );
int set_memory_lowest_date ( const char *date_string, const char *element );
int set_swpused_lowest_date ( const char *date_string );
int set_kernel_table_lowest_date ( const char *date_string, const char *element );
int set_ldavg_lowest_date ( const char *date_string, const char *element );
int set_block_device_lowest_date ( const char *date_string, int x, const char *element );
int set_network_lowest_date ( const char *date_string, int x, const char *element );

/* lowest time */
int set_cpu_lowest_time ( const char *date_string, int x, const char *element );
int set_tasks_lowest_time ( const char *date_string, const char *element );
int set_pswap_lowest_time ( const char *date_string, const char *element );
int set_paging_lowest_time ( const char *date_string, const char *element );
int set_io_transfer_rate_lowest_time ( const char *date_string, const char *element );
int set_memory_lowest_time ( const char *date_string, const char *element );
int set_swpused_lowest_time ( const char *date_string );
int set_kernel_table_lowest_time ( const char *date_string, const char *element );
int set_ldavg_lowest_time ( const char *date_string, const char *element );
int set_block_device_lowest_time ( const char *date_string, int x, const char *element );
int set_network_lowest_time ( const char *date_string, int x, const char *element );

/**** getters ****/
const char *get_this_date ( void );
const char *get_this_date_all ( void );

/* columns */
int get_column_cpu ( const char *element);
int get_column_tasks ( const char *element );
int get_column_pswap ( const char *element );
int get_column_paging ( const char *element );
int get_column_io_transfer_rate ( const char *element );
int get_column_memory ( const char *element );
int get_column_swpused ( void );
int get_column_kernel_table ( const char *element );
int get_column_ldavg ( const char *element );
int get_column_block_device ( const char *element );
int get_column_network ( const char *element );

/* former val each file */
double get_cpu_former_val_each_file ( int x, int y, const char *element );
double get_tasks_former_val_each_file ( int x, const char *element );
double get_pswap_former_val_each_file ( int x, const char *element );
double get_paging_former_val_each_file ( int x, const char *element );
double get_io_transfer_rate_former_val_each_file ( int x, const char *element );
double get_memory_former_val_each_file ( int x, const char *element );
double get_swpused_former_val_each_file ( int x );
int get_kernel_table_former_val_each_file ( int x, const char *element );
double get_ldavg_former_val_each_file ( int x, const char *element );
double get_block_device_former_val_each_file ( int x, int y, const char *element );
double get_network_former_val_each_file ( int x, int y, const char *element );

/* time-span former val each file */
double get_cpu_time_span_former_val_each_file ( int x, int y, const char *element );
double get_tasks_time_span_former_val_each_file ( int x, const char *element );
double get_pswap_time_span_former_val_each_file ( int x, const char *element );
double get_paging_time_span_former_val_each_file ( int x, const char *element );
double get_io_transfer_rate_time_span_former_val_each_file ( int x, const char *element );
double get_memory_time_span_former_val_each_file ( int x, const char *element );
double get_swpused_time_span_former_val_each_file ( int x );
int get_kernel_table_time_span_former_val_each_file ( int x, const char *element );
double get_ldavg_time_span_former_val_each_file ( int x, const char *element );
double get_block_device_time_span_former_val_each_file ( int x, int y, const char *element );
double get_network_time_span_former_val_each_file ( int x, int y, const char *element );

/* cpu as paragraph */
int get_cpu_as_paragraph ( void );

/* tmp_val */
double get_tmp_val ( void );
double get_tmp2_val ( void );
double get_tmp3_val ( void );
double get_tmp4_val ( void );

#endif /* SAR__ANALYZER_H */
