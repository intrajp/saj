/*
 *  setter_getter.h - setter_getter definitions
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

#ifndef SAR_ANALYZER_SETTER_GETTER_H
#define SAR_ANALYZER_SETTER_GETTER_H

/* average highest val */
int set_cpu_avg_highest_val(double var, int x, const char *element);
int set_tasks_avg_highest_val(double var, const char *element);
int set_pswap_avg_highest_val(double var, const char *element);
int set_paging_avg_highest_val(double var, const char *element);
int set_io_transfer_rate_avg_highest_val(double var, const char *element);
int set_memory_double_avg_highest_val(double var, const char *element);
int set_memory_int_avg_highest_val(int var, const char *element);
int set_swpused_avg_highest_val(double var);
int set_kernel_table_avg_highest_val(int var, const char *element);
int set_ldavg_int_avg_highest_val(int var, const char *element);
int set_ldavg_double_avg_highest_val(double var, const char *element);
int set_block_device_avg_highest_val(double var, int x, const char *element);
int set_network_avg_highest_val(double var, int x, const char *element);

/* highest val */
int set_cpu_highest_val(double var, int x, const char *element);
int set_tasks_highest_val(double var, const char *element);
int set_pswap_highest_val(double var, const char *element);
int set_paging_highest_val(double var, const char *element);
int set_io_transfer_rate_highest_val(double var, const char *element);
int set_memory_double_highest_val(double var, const char *element);
int set_memory_int_highest_val(int var, const char *element);
int set_swpused_highest_val(double var);
int set_kernel_table_highest_val(int var, const char *element);
int set_ldavg_int_highest_val(int var, const char *element);
int set_ldavg_double_highest_val(double var, const char *element);
int set_block_device_highest_val(double var, int x, const char *element);
int set_network_highest_val(double var, int x, const char *element);

/* average lowest val */
int set_cpu_avg_lowest_val(double var, int x, const char *element);
int set_tasks_avg_lowest_val(double var, const char *element);
int set_pswap_avg_lowest_val(double var, const char *element);
int set_paging_avg_lowest_val(double var, const char *element);
int set_io_transfer_rate_avg_lowest_val(double var, const char *element);
int set_memory_double_avg_lowest_val(double var, const char *element);
int set_memory_int_avg_lowest_val(int var, const char *element);
int set_swpused_avg_lowest_val(double var);
int set_kernel_table_avg_lowest_val(int var, const char *element);
int set_ldavg_int_avg_lowest_val(int var, const char *element);
int set_ldavg_double_avg_lowest_val(double var, const char *element);
int set_block_device_avg_lowest_val(double var, int x, const char *element);
int set_network_avg_lowest_val(double var, int x, const char *element);

/* spike val */
int set_cpu_spike_val(double var, int x, const char *element);
int set_tasks_spike_val(double var, const char *element);
int set_pswap_spike_val(double var, const char *element);
int set_paging_spike_val(double var, const char *element);
int set_io_transfer_rate_spike_val(double var, const char *element);
int set_memory_double_spike_val(double var, const char *element);
int set_memory_int_spike_val(int var, const char *element);
int set_swpused_spike_val(double var);
int set_kernel_table_spike_val(int var, const char *element);
int set_ldavg_int_spike_val(int var, const char *element);
int set_ldavg_double_spike_val(double var, const char *element);
int set_block_device_spike_val(double var, int x, const char *element);
int set_network_spike_val(double var, int x, const char *element);

/* former val */
int set_cpu_former_val(double var, int x, const char *element);
int set_tasks_former_val(double var, const char *element);
int set_pswap_former_val(double var, const char *element);
int set_paging_former_val(double var, const char *element);
int set_io_transfer_rate_former_val(double var, const char *element);
int set_memory_double_former_val(double var, const char *element);
int set_memory_int_former_val(int var, const char *element);
int set_swpused_former_val(double var);
int set_kernel_table_former_val(int var, const char *element);
int set_ldavg_int_former_val(int var, const char *element);
int set_ldavg_double_former_val(double var, const char *element);
int set_block_device_former_val(double var, int x, const char *element);
int set_network_former_val(double var, int x, const char *element);

/* lowest val */
int set_cpu_lowest_val(double var, int x, const char *element);
int set_tasks_lowest_val(double var, const char *element);
int set_pswap_lowest_val(double var, const char *element);
int set_paging_lowest_val(double var, const char *element);
int set_io_transfer_rate_lowest_val(double var, const char *element);
int set_memory_double_lowest_val(double var, const char *element);
int set_memory_int_lowest_val(int var, const char *element);
int set_swpused_lowest_val(double var);
int set_kernel_table_lowest_val(int var, const char *element);
int set_ldavg_int_lowest_val(int var, const char *element);
int set_ldavg_double_lowest_val(double var, const char *element);
int set_block_device_lowest_val(double var, int x, const char *element);
int set_network_lowest_val(double var, int x, const char *element);

/* spike val each file */
int set_cpu_spike_val_each_file(int x, double var, int y, const char *element, const char *analyze_item);
int set_tasks_spike_val_each_file(int x, double var, const char *element, const char *analyze_item);
int set_pswap_spike_val_each_file(int x, double var, const char *element, const char *analyze_item);
int set_paging_spike_val_each_file(int x, double var, const char *element, const char *analyze_item);
int set_io_transfer_rate_spike_val_each_file(int x, double var, const char *element, const char *analyze_item);
int set_memory_double_spike_val_each_file(int x, double var, const char *element, const char *analyze_item);
int set_memory_int_spike_val_each_file(int x, int var, const char *element, const char *analyze_item);
int set_swpused_spike_val_each_file(int x, double var, const char *analyze_item);
int set_kernel_table_spike_val_each_file(int x,  double var, const char *element, const char *analyze_item);
int set_ldavg_int_spike_val_each_file(int x,  int var, const char *element, const char *analyze_item);
int set_ldavg_double_spike_val_each_file(int x,  double var, const char *element, const char *analyze_item);
int set_block_device_spike_val_each_file(int x,  double var, int y, const char *element, const char *analyze_item);
int set_network_spike_val_each_file(int x,  double var, int y, const char *element, const char *analyze_item);

/* spike val time-span each file */
int set_cpu_time_span_spike_val_each_file(int x, double var, int y, const char *element, const char *analyze_item);
int set_tasks_time_span_spike_val_each_file(int x, double var, const char *element, const char *analyze_item);
int set_pswap_time_span_spike_val_each_file(int x, double var, const char *element, const char *analyze_item);
int set_paging_time_span_spike_val_each_file(int x, double var, const char *element, const char *analyze_item);
int set_io_transfer_rate_time_span_spike_val_each_file(int x, double var, const char *element, const char *analyze_item);
int set_memory_double_time_span_spike_val_each_file(int x, double var, const char *element, const char *analyze_item);
int set_memory_int_time_span_spike_val_each_file(int x, int var, const char *element, const char *analyze_item);
int set_swpused_time_span_spike_val_each_file(int x, double var, const char *analyze_item);
int set_kernel_table_time_span_spike_val_each_file(int x,  double var, const char *element, const char *analyze_item);
int set_ldavg_int_time_span_spike_val_each_file(int x,  int var, const char *element, const char *analyze_item);
int set_ldavg_double_time_span_spike_val_each_file(int x,  double var, const char *element, const char *analyze_item);
int set_block_device_time_span_spike_val_each_file(int x,  double var, int y, const char *element, const char *analyze_item);
int set_network_time_span_spike_val_each_file(int x,  double var, int y, const char *element, const char *analyze_item);

/* former val each file */
int set_cpu_former_val_each_file(int x, double var, int y, const char *element);
int set_tasks_former_val_each_file(int x, double var, const char *element);
int set_pswap_former_val_each_file(int x, double var, const char *element);
int set_paging_former_val_each_file(int x, double var, const char *element);
int set_io_transfer_rate_former_val_each_file(int x, double var, const char *element);
int set_memory_double_former_val_each_file(int x, double var, const char *element);
int set_memory_int_former_val_each_file(int x, int var, const char *element);
int set_swpused_former_val_each_file(int x, double var);
int set_kernel_table_former_val_each_file(int x,  double var, const char *element);
int set_ldavg_int_former_val_each_file(int x,  int var, const char *element);
int set_ldavg_double_former_val_each_file(int x,  double var, const char *element);
int set_block_device_former_val_each_file(int x,  double var, int y, const char *element);
int set_network_former_val_each_file(int x,  double var, int y, const char *element);

/* -- time-span former val each file -- */
int set_cpu_time_span_former_val_each_file(int x, double var, int y, const char *element);
int set_tasks_time_span_former_val_each_file(int x, double var, const char *element);
int set_pswap_time_span_former_val_each_file(int x, double var, const char *element);
int set_paging_time_span_former_val_each_file(int x, double var, const char *element);
int set_io_transfer_rate_time_span_former_val_each_file(int x, double var, const char *element);
int set_memory_double_time_span_former_val_each_file(int x, double var, const char *element);
int set_memory_int_time_span_former_val_each_file(int x, int var, const char *element);
int set_swpused_time_span_former_val_each_file(int x, double var);
int set_kernel_table_time_span_former_val_each_file(int x,  double var, const char *element);
int set_ldavg_int_time_span_former_val_each_file(int x,  int var, const char *element);
int set_ldavg_double_time_span_former_val_each_file(int x,  double var, const char *element);
int set_block_device_time_span_former_val_each_file(int x,  double var, int y, const char *element);
int set_network_time_span_former_val_each_file(int x,  double var, int y, const char *element);

/* spike date each file */
int set_cpu_spike_date_each_file(int x, const char *date_string, int y, const char *element, const char *analyze_item);
int set_tasks_spike_date_each_file(int x, const char *date_string, const char *element, const char *analyze_item);
int set_pswap_spike_date_each_file(int x, const char *date_string, const char *element, const char *analyze_item);
int set_paging_spike_date_each_file(int x, const char *date_string, const char *element, const char *analyze_item);
int set_io_transfer_rate_spike_date_each_file(int x, const char *date_string, const char *element, const char *analyze_item);
int set_memory_spike_date_each_file(int x, const char *date_string, const char *element, const char *analyze_item);
int set_swpused_spike_date_each_file(int x, const char *date_string, const char *analyze_item);
int set_kernel_table_spike_date_each_file(int x, const char *date_string, const char *element, const char *analyze_item);
int set_ldavg_spike_date_each_file(int x, const char *date_string, const char *element, const char *analyze_item);
int set_block_device_spike_date_each_file(int x, const char *date_string, int y, const char *element, const char *analyze_item);
int set_network_spike_date_each_file(int x, const char *date_string, int y, const char *element, const char *analyze_item);

/* spike time each file */
int set_cpu_spike_time_each_file(int x, const char *date_string, int y, const char *element, const char *analyze_item);
int set_tasks_spike_time_each_file(int x, const char *date_string, const char *element, const char *analyze_item);
int set_pswap_spike_time_each_file(int x, const char *date_string, const char *element, const char *analyze_item);
int set_paging_spike_time_each_file(int x, const char *date_string, const char *element, const char *analyze_item);
int set_io_transfer_rate_spike_time_each_file(int x, const char *date_string, const char *element, const char *analyze_item);
int set_memory_spike_time_each_file(int x, const char *date_string, const char *element, const char *analyze_item);
int set_swpused_spike_time_each_file(int x, const char *date_string, const char *analyze_item);
int set_kernel_table_spike_time_each_file(int x, const char *date_string, const char *element, const char *analyze_item);
int set_ldavg_spike_time_each_file(int x, const char *date_string, const char *element, const char *analyze_item);
int set_block_device_spike_time_each_file(int x, const char *date_string, int y, const char *element, const char *analyze_item);
int set_network_spike_time_each_file(int x, const char *date_string, int y, const char *element, const char *analyze_item);

/* time-span spike date each file */
int set_cpu_time_span_spike_date_each_file(int x, const char *date_string, int y, const char *element, const char *analyze_item);
int set_tasks_time_span_spike_date_each_file(int x, const char *date_string, const char *element, const char *analyze_item);
int set_pswap_time_span_spike_date_each_file(int x, const char *date_string, const char *element, const char *analyze_item);
int set_paging_time_span_spike_date_each_file(int x, const char *date_string, const char *element, const char *analyze_item);
int set_io_transfer_rate_time_span_spike_date_each_file(int x, const char *date_string, const char *element, const char *analyze_item);
int set_memory_time_span_spike_date_each_file(int x, const char *date_string, const char *element, const char *analyze_item);
int set_swpused_time_span_spike_date_each_file(int x, const char *date_string, const char *analyze_item);
int set_kernel_table_time_span_spike_date_each_file(int x, const char *date_string, const char *element, const char *analyze_item);
int set_ldavg_time_span_spike_date_each_file(int x, const char *date_string, const char *element, const char *analyze_item);
int set_block_device_time_span_spike_date_each_file(int x, const char *date_string, int y, const char *element, const char *analyze_item);
int set_network_time_span_spike_date_each_file(int x, const char *date_string, int y, const char *element, const char *analyze_item);

/* time-span spike time each file */
int set_cpu_time_span_spike_time_each_file(int x, const char *date_string, int y, const char *element, const char *analyze_item);
int set_tasks_time_span_spike_time_each_file(int x, const char *date_string, const char *element, const char *analyze_item);
int set_pswap_time_span_spike_time_each_file(int x, const char *date_string, const char *element, const char *analyze_item);
int set_paging_time_span_spike_time_each_file(int x, const char *date_string, const char *element, const char *analyze_item);
int set_io_transfer_rate_time_span_spike_time_each_file(int x, const char *date_string, const char *element, const char *analyze_item);
int set_memory_time_span_spike_time_each_file(int x, const char *date_string, const char *element, const char *analyze_item);
int set_swpused_time_span_spike_time_each_file(int x, const char *date_string, const char *analyze_item);
int set_kernel_table_time_span_spike_time_each_file(int x, const char *date_string, const char *element, const char *analyze_item);
int set_ldavg_time_span_spike_time_each_file(int x, const char *date_string, const char *element, const char *analyze_item);
int set_block_device_time_span_spike_time_each_file(int x, const char *date_string, int y, const char *element, const char *analyze_item);
int set_network_time_span_spike_time_each_file(int x, const char *date_string, int y, const char *element, const char *analyze_item);

/* cpu as paragraph */
void set_cpu_as_paragraph(int x);

/* tmp_val */
void set_tmp_val(double var);
void set_tmp2_val(double var);
void set_tmp3_val(double var);
void set_tmp4_val(double var);

/* getters */

/* former val */
double get_cpu_former_val(int x, const char *element);
double get_tasks_former_val(const char *element);
double get_pswap_former_val(const char *element);
double get_paging_former_val(const char *element);
double get_io_transfer_rate_former_val(const char *element);
double get_memory_former_val(const char *element);
double get_swpused_former_val(void);
int get_kernel_table_former_val(const char *element);
double get_ldavg_former_val(const char *element);
double get_block_device_former_val(int x, const char *element);
double get_network_former_val(int x, const char *element);

/* average highest val */
double get_cpu_avg_highest_val(int x, const char *element);
double get_tasks_avg_highest_val(const char *element);
double get_pswap_avg_highest_val(const char *element);
double get_paging_avg_highest_val(const char *element);
double get_io_transfer_rate_avg_highest_val(const char *element);
double get_memory_avg_highest_val(const char *element);
double get_swpused_avg_highest_val(void);
int get_kernel_table_avg_highest_val(const char *element);
double get_ldavg_avg_highest_val(const char *element);
double get_block_device_avg_highest_val(int x, const char *element);
double get_network_avg_highest_val(int x, const char *element);

/* highest val */
double get_cpu_highest_val(int x, const char *element);
double get_tasks_highest_val(const char *element);
double get_pswap_highest_val(const char *element);
double get_paging_highest_val(const char *element);
double get_io_transfer_rate_highest_val(const char *element);
double get_memory_highest_val(const char *element);
double get_swpused_highest_val(void);
int get_kernel_table_highest_val(const char *element);
double get_ldavg_highest_val(const char *element);
double get_block_device_highest_val(int x, const char *element);
double get_network_highest_val(int x, const char *element);

/* average highest date */
const char *get_cpu_avg_highest_date(int x, const char *element);
const char *get_tasks_avg_highest_date(const char *element);
const char *get_pswap_avg_highest_date(const char *element);
const char *get_paging_avg_highest_date(const char *element);
const char *get_io_transfer_rate_avg_highest_date(const char *element);
const char *get_memory_avg_highest_date(const char *element);
const char *get_swpused_avg_highest_date(void);
const char *get_kernel_table_avg_highest_date(const char *element);
const char *get_ldavg_avg_highest_date(const char *element);
const char *get_block_device_avg_highest_date(int x, const char *element);
const char *get_network_avg_highest_date(int x, const char *element);

/* highest date */
const char *get_cpu_highest_date(int x, const char *element);
const char *get_tasks_highest_date(const char *element);
const char *get_pswap_highest_date(const char *element);
const char *get_paging_highest_date(const char *element);
const char *get_io_transfer_rate_highest_date(const char *element);
const char *get_memory_highest_date(const char *element);
const char *get_swpused_highest_date(void);
const char *get_kernel_table_highest_date(const char *element);
const char *get_ldavg_highest_date(const char *element);
const char *get_block_device_highest_date(int x, const char *element);
const char *get_network_highest_date(int x, const char *element);

/* highest time */
const char *get_cpu_highest_time(int x, const char *element);
const char *get_tasks_highest_time(const char *element);
const char *get_pswap_highest_time(const char *element);
const char *get_paging_highest_time(const char *element);
const char *get_io_transfer_rate_highest_time(const char *element);
const char *get_memory_highest_time(const char *element);
const char *get_swpused_highest_time(void);
const char *get_kernel_table_highest_time(const char *element);
const char *get_ldavg_highest_time(const char *element);
const char *get_block_device_highest_time(int x, const char *element);
const char *get_network_highest_time(int x, const char *element);

/* average lowest val */
double get_cpu_avg_lowest_val(int x, const char *element);
double get_tasks_avg_lowest_val(const char *element);
double get_pswap_avg_lowest_val(const char *element);
double get_paging_avg_lowest_val(const char *element);
double get_io_transfer_rate_avg_lowest_val(const char *element);
double get_memory_avg_lowest_val(const char *element);
double get_swpused_avg_lowest_val(void);
int get_kernel_table_avg_lowest_val(const char *element);
double get_ldavg_avg_lowest_val(const char *element);
double get_block_device_avg_lowest_val(int x, const char *element);
double get_network_avg_lowest_val(int x, const char *element);

/* lowest val */
double get_cpu_lowest_val(int x, const char *element);
double get_tasks_lowest_val(const char *element);
double get_pswap_lowest_val(const char *element);
double get_paging_lowest_val(const char *element);
double get_io_transfer_rate_lowest_val(const char *element);
double get_memory_lowest_val(const char *element);
double get_swpused_lowest_val(void);
int get_kernel_table_lowest_val(const char *element);
double get_ldavg_lowest_val(const char *element);
double get_block_device_lowest_val(int x, const char *element);
double get_network_lowest_val(int x, const char *element);

/* average lowest date */
const char *get_cpu_avg_lowest_date(int x, const char *element);
const char *get_tasks_avg_lowest_date(const char *element);
const char *get_pswap_avg_lowest_date(const char *element);
const char *get_paging_avg_lowest_date(const char *element);
const char *get_io_transfer_rate_avg_lowest_date(const char *element);
const char *get_memory_avg_lowest_date(const char *element);
const char *get_swpused_avg_lowest_date(void);
const char *get_kernel_table_avg_lowest_date(const char *element);
const char *get_ldavg_avg_lowest_date(const char *element);
const char *get_block_device_avg_lowest_date(int x, const char *element);
const char *get_network_avg_lowest_date(int x, const char *element);

/* lowest date */
const char *get_cpu_lowest_date(int x, const char *element);
const char *get_tasks_lowest_date(const char *element);
const char *get_pswap_lowest_date(const char *element);
const char *get_paging_lowest_date(const char *element);
const char *get_io_transfer_rate_lowest_date(const char *element);
const char *get_memory_lowest_date(const char *element);
const char *get_swpused_lowest_date(void);
const char *get_kernel_table_lowest_date(const char *element);
const char *get_ldavg_lowest_date(const char *element);
const char *get_block_device_lowest_date(int x, const char *element);
const char *get_network_lowest_date(int x, const char *element);

/* lowest time */
const char *get_cpu_lowest_time(int x, const char *element);
const char *get_tasks_lowest_time(const char *element);
const char *get_pswap_lowest_time(const char *element);
const char *get_paging_lowest_time(const char *element);
const char *get_io_transfer_rate_lowest_time(const char *element);
const char *get_memory_lowest_time(const char *element);
const char *get_swpused_lowest_time(void);
const char *get_kernel_table_lowest_time(const char *element);
const char *get_ldavg_lowest_time(const char *element);
const char *get_block_device_lowest_time(int x, const char *element);
const char *get_network_lowest_time(int x, const char *element);

/* spike val */
double get_cpu_spike_val(int x, const char *element);
double get_tasks_spike_val(const char *element);
double get_pswap_spike_val(const char *element);
double get_paging_spike_val(const char *element);
double get_io_transfer_rate_spike_val(const char *element);
double get_memory_spike_val(const char *element);
double get_swpused_spike_val(void);
int get_kernel_table_spike_val(const char *element);
double get_ldavg_spike_val(const char *element);
double get_block_device_spike_val(int x, const char *element);
double get_network_spike_val(int x, const char *element);

/* spike date */
const char *get_cpu_spike_date(int x, const char *element);
const char *get_tasks_spike_date(const char *element);
const char *get_pswap_spike_date(const char *element);
const char *get_paging_spike_date(const char *element);
const char *get_io_transfer_rate_spike_date(const char *element);
const char *get_memory_spike_date(const char *element);
const char *get_swpused_spike_date(void);
const char *get_kernel_table_spike_date(const char *element);
const char *get_ldavg_spike_date(const char *element);
const char *get_block_device_spike_date(int x, const char *element);
const char *get_network_spike_date(int x, const char *element);

/* spike time */
const char *get_cpu_spike_time(int x, const char *element);
const char *get_tasks_spike_time(const char *element);
const char *get_pswap_spike_time(const char *element);
const char *get_paging_spike_time(const char *element);
const char *get_io_transfer_rate_spike_time(const char *element);
const char *get_memory_spike_time(const char *element);
const char *get_swpused_spike_time(void);
const char *get_kernel_table_spike_time(const char *element);
const char *get_ldavg_spike_time(const char *element);
const char *get_block_device_spike_time(int x, const char *element);
const char *get_network_spike_time(int x, const char *element);

/* spike val each file */
double get_cpu_spike_val_each_file(int x, int y, const char *element, const char *analyze_item);
double get_tasks_spike_val_each_file(int x, const char *element, const char *analyze_item);
double get_pswap_spike_val_each_file(int x, const char *element, const char *analyze_item);
double get_paging_spike_val_each_file(int x, const char *element, const char *analyze_item);
double get_io_transfer_rate_spike_val_each_file(int x, const char *element, const char *analyze_item);
double get_memory_spike_val_each_file(int x, const char *element, const char *analyze_item);
double get_swpused_spike_val_each_file(int x, const char *analyze_item);
int get_kernel_table_spike_val_each_file(int x, const char *element, const char *analyze_item);
double get_ldavg_spike_val_each_file(int x, const char *element, const char *analyze_item);
double get_block_device_spike_val_each_file(int x, int y, const char *element, const char *analyze_item);
double get_network_spike_val_each_file(int x, int y, const char *element, const char *analyze_item);

/* spike date each file */
const char *get_cpu_spike_date_each_file(int x, int y, const char *element, const char *analyze_item);
const char *get_tasks_spike_date_each_file(int x, const char *element, const char *analyze_item);
const char *get_pswap_spike_date_each_file(int x, const char *element, const char *analyze_item);
const char *get_paging_spike_date_each_file(int x, const char *element, const char *analyze_item);
const char *get_io_transfer_rate_spike_date_each_file(int x, const char *element, const char *analyze_item);
const char *get_memory_spike_date_each_file(int x, const char *element, const char *analyze_item);
const char *get_swpused_spike_date_each_file(int x, const char *analyze_item);
const char *get_kernel_table_spike_date_each_file(int x, const char *element, const char *analyze_item);
const char *get_ldavg_spike_date_each_file(int x, const char *element, const char *analyze_item);
const char *get_block_device_spike_date_each_file(int x, int y, const char *element, const char *analyze_item);
const char *get_network_spike_date_each_file(int x, int y, const char *element, const char *analyze_item);

/* spike time each file */
const char *get_cpu_spike_time_each_file(int x, int y, const char *element, const char *analyze_item);
const char *get_tasks_spike_time_each_file(int x, const char *element, const char *analyze_item);
const char *get_pswap_spike_time_each_file(int x, const char *element, const char *analyze_item);
const char *get_paging_spike_time_each_file(int x, const char *element, const char *analyze_item);
const char *get_io_transfer_rate_spike_time_each_file(int x, const char *element, const char *analyze_item);
const char *get_memory_spike_time_each_file(int x, const char *element, const char *analyze_item);
const char *get_swpused_spike_time_each_file(int x, const char *analyze_item);
const char *get_kernel_table_spike_time_each_file(int x, const char *element, const char *analyze_item);
const char *get_ldavg_spike_time_each_file(int x, const char *element, const char *analyze_item);
const char *get_block_device_spike_time_each_file(int x, int y, const char *element, const char *analyze_item);
const char *get_network_spike_time_each_file(int x, int y, const char *element, const char *analyze_item);

/* time-span spike val each file */
double get_cpu_time_span_spike_val_each_file(int x, int y, const char *element, const char *analyze_item);
double get_tasks_time_span_spike_val_each_file(int x, const char *element, const char *analyze_item);
double get_pswap_time_span_spike_val_each_file(int x, const char *element, const char *analyze_item);
double get_paging_time_span_spike_val_each_file(int x, const char *element, const char *analyze_item);
double get_io_transfer_rate_time_span_spike_val_each_file(int x, const char *element, const char *analyze_item);
double get_memory_time_span_spike_val_each_file(int x, const char *element, const char *analyze_item);
double get_swpused_time_span_spike_val_each_file(int x, const char *analyze_item);
int get_kernel_table_time_span_spike_val_each_file(int x, const char *element, const char *analyze_item);
double get_ldavg_time_span_spike_val_each_file(int x, const char *element, const char *analyze_item);
double get_block_device_time_span_spike_val_each_file(int x, int y, const char *element, const char *analyze_item);
double get_network_time_span_spike_val_each_file(int x, int y, const char *element, const char *analyze_item);

/* time-span spike date each file */
const char *get_cpu_time_span_spike_date_each_file(int x, int y, const char *element, const char *analyze_item);
const char *get_tasks_time_span_spike_date_each_file(int x, const char *element, const char *analyze_item);
const char *get_pswap_time_span_spike_date_each_file(int x, const char *element, const char *analyze_item);
const char *get_paging_time_span_spike_date_each_file(int x, const char *element, const char *analyze_item);
const char *get_io_transfer_rate_time_span_spike_date_each_file(int x, const char *element, const char *analyze_item);
const char *get_memory_time_span_spike_date_each_file(int x, const char *element, const char *analyze_item);
const char *get_swpused_time_span_spike_date_each_file(int x, const char *analyze_item);
const char *get_kernel_table_time_span_spike_date_each_file(int x, const char *element, const char *analyze_item);
const char *get_ldavg_time_span_spike_date_each_file(int x, const char *element, const char *analyze_item);
const char *get_block_device_time_span_spike_date_each_file(int x, int y, const char *element, const char *analyze_item);
const char *get_network_time_span_spike_date_each_file(int x, int y, const char *element, const char *analyze_item);

/* time-span spike time each file */
const char *get_cpu_time_span_spike_time_each_file(int x, int y, const char *element, const char *analyze_item);
const char *get_tasks_time_span_spike_time_each_file(int x, const char *element, const char *analyze_item);
const char *get_pswap_time_span_spike_time_each_file(int x, const char *element, const char *analyze_item);
const char *get_paging_time_span_spike_time_each_file(int x, const char *element, const char *analyze_item);
const char *get_io_transfer_rate_time_span_spike_time_each_file(int x, const char *element, const char *analyze_item);
const char *get_memory_time_span_spike_time_each_file(int x, const char *element, const char *analyze_item);
const char *get_swpused_time_span_spike_time_each_file(int x, const char *analyze_item);
const char *get_kernel_table_time_span_spike_time_each_file(int x, const char *element, const char *analyze_item);
const char *get_ldavg_time_span_spike_time_each_file(int x, const char *element, const char *analyze_item);
const char *get_block_device_time_span_spike_time_each_file(int x, int y, const char *element, const char *analyze_item);
const char *get_network_time_span_spike_time_each_file(int x, int y, const char *element, const char *analyze_item);

#endif /* SAR_ANALYZER_SETTER_GETTER_H */
