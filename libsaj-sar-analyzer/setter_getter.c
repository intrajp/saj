/*
 *  setter_getter.c - setter and getter functions 
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
#include <string.h>
#include "common.h" 
#include "setter_getter.h" 

/* -------- setters -------- */

void set_title_strings(int x, const char *title_strings)
{
    x++;
    strncpy(sar_analyzer_obj->title_strings[x], title_strings, MAX_DATE_STRINGS);
}

void set_core_numbers(int var)
{
    sar_analyzer_obj->cores_n = var;
}

int search_block_device_name(const char *block_device_name)
{
    int x = 0;
    for (x = 1; x <= get_block_device_numbers (); x++) {
        if (strcmp((char *) get_block_device_names(x), block_device_name) == 0)
            return x;
    }
    return 0;
}

void set_block_device_names(const char *block_device_name)
{
    if (search_block_device_name(block_device_name) == 0)
        strcpy(sar_analyzer_obj->device_names[get_block_device_numbers()], block_device_name);
}

void set_title_strings_first_file(int x, const char *title_strings)
{
    strncpy(sar_analyzer_obj->title_strings_first_file[x], title_strings, MAX_DATE_STRINGS);
}

void set_this_date(const char *date_string)
{
    strncpy(sar_analyzer_obj->this_date, date_string, MAX_DATE_STRINGS - 1);
}

void set_this_date_all(const char *date_string)
{
    strncpy(sar_analyzer_all_obj->this_date, date_string, MAX_DATE_STRINGS - 1);
}

void set_this_date_former(const char *date_string)
{
    strncpy(sar_analyzer_obj->this_date_former, date_string, MAX_DATE_STRINGS - 1);
}

void set_this_date_all_former(const char *date_string)
{
    strncpy(sar_analyzer_all_obj->this_date_former, date_string, MAX_DATE_STRINGS - 1);
}

void set_this_time(const char *date_string)
{
    strncpy(sar_analyzer_obj->this_time, date_string, MAX_DATE_STRINGS - 1);
}

void set_this_time_former(const char *date_string)
{
    strncpy(sar_analyzer_obj->this_time_former, date_string, MAX_DATE_STRINGS - 1);
}

void set_this_time_all(const char *date_string)
{
    strncpy(sar_analyzer_all_obj->this_time, date_string, MAX_DATE_STRINGS - 1);
}

void set_this_time_all_former(const char *date_string)
{
    strncpy(sar_analyzer_all_obj->this_time_former, date_string, MAX_DATE_STRINGS - 1);
}

/* -------- Columns -------- */
int set_column_cpu(int var, const char *element)
{
    if (strcmp("CPU", element) == 0) {
        sar_analyzer_obj->column_cpus.CPU = var;
        return EXIT_SUCCESS;
    } else if (strcmp("usr", element) == 0) {
        sar_analyzer_obj->column_cpus.cpu_usr = var;
        return EXIT_SUCCESS;
    } else if (strcmp("sys", element) == 0) {
        sar_analyzer_obj->column_cpus.cpu_sys = var;
        return EXIT_SUCCESS;
    } else if (strcmp("iowait", element) == 0) {
        sar_analyzer_obj->column_cpus.cpu_iowait = var;
        return EXIT_SUCCESS;
    } else if (strcmp("idle", element) == 0) {
        sar_analyzer_obj->column_cpus.cpu_idle = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_column_tasks(int var, const char *element)
{
    if (strcmp("proc", element) == 0) {
        sar_analyzer_obj->column_tasks.proc = var;
        return EXIT_SUCCESS;
    } else if (strcmp("cswch", element) == 0) {
        sar_analyzer_obj->column_tasks.cswch = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_column_pswap(int var, const char *element)
{
    if (strcmp("pswpin", element) == 0) {
        sar_analyzer_obj->column_pswaps.pswpin = var;
        return EXIT_SUCCESS;
    } else if (strcmp("pswpout", element) == 0) {
        sar_analyzer_obj->column_pswaps.pswpout = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_column_paging(int var, const char *element)
{
    if (strcmp("pgpgin", element) == 0) {
        sar_analyzer_obj->column_pagings.pgpgin = var;
        return EXIT_SUCCESS;
    } else if (strcmp("pgpgout", element) == 0) {
        sar_analyzer_obj->column_pagings.pgpgout = var;
        return EXIT_SUCCESS;
    } else if (strcmp("fault", element) == 0) {
        sar_analyzer_obj->column_pagings.fault = var;
        return EXIT_SUCCESS;
    } else if (strcmp("majflt", element) == 0) {
        sar_analyzer_obj->column_pagings.majflt = var;
        return EXIT_SUCCESS;
    } else if (strcmp("vmeff", element) == 0) {
        sar_analyzer_obj->column_pagings.vmeff = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_column_io_transfer_rate(int var, const char *element)
{
    if (strcmp("tps", element) == 0) {
        sar_analyzer_obj->column_io_transfer_rates.tps = var;
        return EXIT_SUCCESS;
    } else if (strcmp("bread", element) == 0) {
        sar_analyzer_obj->column_io_transfer_rates.bread = var;
        return EXIT_SUCCESS;
    } else if (strcmp("bwrtn", element) == 0) {
        sar_analyzer_obj->column_io_transfer_rates.bwrtn = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_column_memory(int var, const char *element)
{
    if (strcmp("memused", element) == 0) {
        sar_analyzer_obj->column_memories.memused = var;
        return EXIT_SUCCESS;
    } else if (strcmp("kbcommit", element) == 0) {
        sar_analyzer_obj->column_memories.kbcommit = var;
        return EXIT_SUCCESS;
    } else if (strcmp("commit", element) == 0) {
        sar_analyzer_obj->column_memories.commit = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_column_swpused(int var)
{
    sar_analyzer_obj->column_swaps.swpused = var;
    return EXIT_SUCCESS;
}


int set_column_kernel_table(int var, const char *element)
{
    if (strcmp("dentunusd", element) == 0) {
        sar_analyzer_obj->column_kernel_tables.dentunusd = var;
        return EXIT_SUCCESS;
    } else if (strcmp("file", element) == 0) {
        sar_analyzer_obj->column_kernel_tables.file = var;
        return EXIT_SUCCESS;
    } else if (strcmp("inode", element) == 0) {
        sar_analyzer_obj->column_kernel_tables.inode = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_column_ldavg(int var, const char *element)
{
    if (strcmp("runq_sz", element) == 0) {
        sar_analyzer_obj->column_ldavgs.runq_sz = var;
        return EXIT_SUCCESS;
    } else if (strcmp("plist_sz", element) == 0) {
        sar_analyzer_obj->column_ldavgs.plist_sz = var;
        return EXIT_SUCCESS;
    } else if (strcmp("ldavg_one", element) == 0) {
        sar_analyzer_obj->column_ldavgs.ldavg_one = var;
        return EXIT_SUCCESS;
    } else if (strcmp("ldavg_five", element) == 0) {
        sar_analyzer_obj->column_ldavgs.ldavg_five = var;
        return EXIT_SUCCESS;
    } else if (strcmp("ldavg_15", element) == 0) {
        sar_analyzer_obj->column_ldavgs.ldavg_15 = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_column_block_device(int var, const char *element)
{
    if (strcmp("areqsz", element) == 0) {
        sar_analyzer_obj->column_block_devices.areqsz = var;
        return EXIT_SUCCESS;
    } else if (strcmp("util", element) == 0) {
        sar_analyzer_obj->column_block_devices.util = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_column_network(int var, const char *element)
{
    if (strcmp("rxpck", element) == 0) {
        sar_analyzer_obj->column_networks.rxpck = var;
        return EXIT_SUCCESS;
    } else if (strcmp("txpck", element) == 0) {
        sar_analyzer_obj->column_networks.txpck = var;
        return EXIT_SUCCESS;
    } else if (strcmp("rxkb", element) == 0) {
        sar_analyzer_obj->column_networks.rxkb = var;
        return EXIT_SUCCESS;
    } else if (strcmp("txkb", element) == 0) {
        sar_analyzer_obj->column_networks.txkb = var;
        return EXIT_SUCCESS;
    } else if (strcmp("rxerr", element) == 0) {
        sar_analyzer_obj->column_networks.rxerr = var;
        return EXIT_SUCCESS;
    } else if (strcmp("txerr", element) == 0) {
        sar_analyzer_obj->column_networks.txerr = var;
        return EXIT_SUCCESS;
    } else if (strcmp("rxdrop", element) == 0) {
        sar_analyzer_obj->column_networks.rxdrop = var;
        return EXIT_SUCCESS;
    } else if (strcmp("txdrop", element) == 0) {
        sar_analyzer_obj->column_networks.txdrop = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

/* -------- end Columns -------- */

/* -------- Data -------- */

/* -- spike val each file -- */

int set_cpu_spike_val_each_file(int x, double var, int y, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("usr", element) == 0) {
            sar_analyzer_spike_obj->cpus_spike_each_file.cpu_usr_spike_val_each_file[x][y] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("sys", element) == 0) {
            sar_analyzer_spike_obj->cpus_spike_each_file.cpu_sys_spike_val_each_file[x][y] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("iowait", element) == 0) {
            sar_analyzer_spike_obj->cpus_spike_each_file.cpu_iowait_spike_val_each_file[x][y] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("idle", element) == 0) {
            sar_analyzer_spike_obj->cpus_spike_each_file.cpu_idle_spike_val_each_file[x][y] = var;
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("usr", element) == 0) {
            sar_analyzer_spike_obj->cpus_spike_each_file.cpu_usr_highest_val_each_file[x][y] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("sys", element) == 0) {
            sar_analyzer_spike_obj->cpus_spike_each_file.cpu_sys_highest_val_each_file[x][y] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("iowait", element) == 0) {
            sar_analyzer_spike_obj->cpus_spike_each_file.cpu_iowait_highest_val_each_file[x][y] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("idle", element) == 0) {
            sar_analyzer_spike_obj->cpus_spike_each_file.cpu_idle_highest_val_each_file[x][y] = var;
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("usr", element) == 0) {
            sar_analyzer_spike_obj->cpus_spike_each_file.cpu_usr_lowest_val_each_file[x][y] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("sys", element) == 0) {
            sar_analyzer_spike_obj->cpus_spike_each_file.cpu_sys_lowest_val_each_file[x][y] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("iowait", element) == 0) {
            sar_analyzer_spike_obj->cpus_spike_each_file.cpu_iowait_lowest_val_each_file[x][y] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("idle", element) == 0) {
            sar_analyzer_spike_obj->cpus_spike_each_file.cpu_idle_lowest_val_each_file[x][y] = var;
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else
        return EXIT_FAILURE;
}

int set_tasks_spike_val_each_file(int x, double var, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("proc", element) == 0) {
            sar_analyzer_spike_obj->tasks_spike_each_file.proc_spike_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("cswch", element) == 0) {
            sar_analyzer_spike_obj->tasks_spike_each_file.cswch_spike_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("proc", element) == 0) {
            sar_analyzer_spike_obj->tasks_spike_each_file.proc_highest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("cswch", element) == 0) {
            sar_analyzer_spike_obj->tasks_spike_each_file.cswch_highest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("proc", element) == 0) {
            sar_analyzer_spike_obj->tasks_spike_each_file.proc_lowest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("cswch", element) == 0) {
            sar_analyzer_spike_obj->tasks_spike_each_file.cswch_lowest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else
        return EXIT_FAILURE;
}

int set_pswap_spike_val_each_file(int x, double var, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("pswpin", element) == 0) {
            sar_analyzer_spike_obj->pswaps_spike_each_file.pswpin_spike_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("pswpout", element) == 0) {
            sar_analyzer_spike_obj->pswaps_spike_each_file.pswpout_spike_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("pswpin", element) == 0) {
            sar_analyzer_spike_obj->pswaps_spike_each_file.pswpin_highest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("pswpout", element) == 0) {
            sar_analyzer_spike_obj->pswaps_spike_each_file.pswpout_highest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("pswpin", element) == 0) {
            sar_analyzer_spike_obj->pswaps_spike_each_file.pswpin_lowest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("pswpout", element) == 0) {
            sar_analyzer_spike_obj->pswaps_spike_each_file.pswpout_lowest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else
        return EXIT_FAILURE;
}

int set_paging_spike_val_each_file(int x, double var, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("pgpgin", element) == 0) {
            sar_analyzer_spike_obj->pagings_spike_each_file.pgpgin_spike_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("pgpgout", element) == 0) {
            sar_analyzer_spike_obj->pagings_spike_each_file.pgpgout_spike_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("fault", element) == 0) {
            sar_analyzer_spike_obj->pagings_spike_each_file.fault_spike_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("majflt", element) == 0) {
            sar_analyzer_spike_obj->pagings_spike_each_file.majflt_spike_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("vmeff", element) == 0) {
            sar_analyzer_spike_obj->pagings_spike_each_file.vmeff_spike_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("pgpgin", element) == 0) {
            sar_analyzer_spike_obj->pagings_spike_each_file.pgpgin_highest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("pgpgout", element) == 0) {
            sar_analyzer_spike_obj->pagings_spike_each_file.pgpgout_highest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("fault", element) == 0) {
            sar_analyzer_spike_obj->pagings_spike_each_file.fault_highest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("majflt", element) == 0) {
            sar_analyzer_spike_obj->pagings_spike_each_file.majflt_highest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("vmeff", element) == 0) {
            sar_analyzer_spike_obj->pagings_spike_each_file.vmeff_highest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("pgpgin", element) == 0) {
            sar_analyzer_spike_obj->pagings_spike_each_file.pgpgin_lowest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("pgpgout", element) == 0) {
            sar_analyzer_spike_obj->pagings_spike_each_file.pgpgout_lowest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("fault", element) == 0) {
            sar_analyzer_spike_obj->pagings_spike_each_file.fault_lowest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("majflt", element) == 0) {
            sar_analyzer_spike_obj->pagings_spike_each_file.majflt_lowest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("vmeff", element) == 0) {
            sar_analyzer_spike_obj->pagings_spike_each_file.vmeff_lowest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else
        return EXIT_FAILURE;
}

int set_io_transfer_rate_spike_val_each_file(int x, double var, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("tps", element) == 0) {
            sar_analyzer_spike_obj->io_transfer_rates_spike_each_file.tps_spike_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("bread", element) == 0) {
            sar_analyzer_spike_obj->io_transfer_rates_spike_each_file.bread_spike_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("bwrtn", element) == 0) {
            sar_analyzer_spike_obj->io_transfer_rates_spike_each_file.bwrtn_spike_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("tps", element) == 0) {
            sar_analyzer_spike_obj->io_transfer_rates_spike_each_file.tps_highest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("bread", element) == 0) {
            sar_analyzer_spike_obj->io_transfer_rates_spike_each_file.bread_highest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("bwrtn", element) == 0) {
            sar_analyzer_spike_obj->io_transfer_rates_spike_each_file.bwrtn_highest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("tps", element) == 0) {
            sar_analyzer_spike_obj->io_transfer_rates_spike_each_file.tps_lowest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("bread", element) == 0) {
            sar_analyzer_spike_obj->io_transfer_rates_spike_each_file.bread_lowest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("bwrtn", element) == 0) {
            sar_analyzer_spike_obj->io_transfer_rates_spike_each_file.bwrtn_lowest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else
        return EXIT_FAILURE;
}

int set_memory_double_spike_val_each_file(int x, double var, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("memused", element) == 0) {
            sar_analyzer_spike_obj->memories_spike_each_file.memused_spike_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("commit", element) == 0) {
            sar_analyzer_spike_obj->memories_spike_each_file.commit_spike_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("memused", element) == 0) {
            sar_analyzer_spike_obj->memories_spike_each_file.memused_highest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("commit", element) == 0) {
            sar_analyzer_spike_obj->memories_spike_each_file.commit_highest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("memused", element) == 0) {
            sar_analyzer_spike_obj->memories_spike_each_file.memused_lowest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("commit", element) == 0) {
            sar_analyzer_spike_obj->memories_spike_each_file.commit_lowest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else
        return EXIT_FAILURE;
}

int set_memory_int_spike_val_each_file(int x, int var, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("kbcommit", element) == 0) {
            sar_analyzer_spike_obj->memories_spike_each_file.kbcommit_spike_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("kbcommit", element) == 0) {
            sar_analyzer_spike_obj->memories_spike_each_file.kbcommit_highest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("kbcommit", element) == 0) {
            sar_analyzer_spike_obj->memories_spike_each_file.kbcommit_lowest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else
        return EXIT_FAILURE;
}

int set_swpused_spike_val_each_file(int x, double var, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        sar_analyzer_spike_obj->swaps_spike_each_file.swpused_spike_val_each_file[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("highest", analyze_item) == 0) {
        sar_analyzer_spike_obj->swaps_spike_each_file.swpused_highest_val_each_file[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("lowest", analyze_item) == 0) {
        sar_analyzer_spike_obj->swaps_spike_each_file.swpused_lowest_val_each_file[x] = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_kernel_table_spike_val_each_file(int x,  double var, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("dentunusd", element) == 0) {
            sar_analyzer_spike_obj->kernel_tables_spike_each_file.dentunusd_spike_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("file", element) == 0) {
            sar_analyzer_spike_obj->kernel_tables_spike_each_file.file_spike_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("inode", element) == 0) {
            sar_analyzer_spike_obj->kernel_tables_spike_each_file.inode_spike_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("dentunusd", element) == 0) {
            sar_analyzer_spike_obj->kernel_tables_spike_each_file.dentunusd_highest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("file", element) == 0) {
            sar_analyzer_spike_obj->kernel_tables_spike_each_file.file_highest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("inode", element) == 0) {
            sar_analyzer_spike_obj->kernel_tables_spike_each_file.inode_highest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("dentunusd", element) == 0) {
            sar_analyzer_spike_obj->kernel_tables_spike_each_file.dentunusd_lowest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("file", element) == 0) {
            sar_analyzer_spike_obj->kernel_tables_spike_each_file.file_lowest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("inode", element) == 0) {
            sar_analyzer_spike_obj->kernel_tables_spike_each_file.inode_lowest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else
        return EXIT_FAILURE;
}

int set_ldavg_int_spike_val_each_file(int x,  int var, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("runq_sz", element) == 0) {
            sar_analyzer_spike_obj->ldavgs_spike_each_file.runq_sz_spike_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("plist_sz", element) == 0) {
            sar_analyzer_spike_obj->ldavgs_spike_each_file.plist_sz_spike_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("runq_sz", element) == 0) {
            sar_analyzer_spike_obj->ldavgs_spike_each_file.runq_sz_highest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("plist_sz", element) == 0) {
            sar_analyzer_spike_obj->ldavgs_spike_each_file.plist_sz_highest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("runq_sz", element) == 0) {
            sar_analyzer_spike_obj->ldavgs_spike_each_file.runq_sz_lowest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("plist_sz", element) == 0) {
            sar_analyzer_spike_obj->ldavgs_spike_each_file.plist_sz_lowest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else
        return EXIT_FAILURE;
}

int set_ldavg_double_spike_val_each_file(int x,  double var, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("ldavg_one", element) == 0) {
            sar_analyzer_spike_obj->ldavgs_spike_each_file.ldavg_one_spike_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("ldavg_five", element) == 0) {
            sar_analyzer_spike_obj->ldavgs_spike_each_file.ldavg_five_spike_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("ldavg_15", element) == 0) {
            sar_analyzer_spike_obj->ldavgs_spike_each_file.ldavg_15_spike_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("ldavg_one", element) == 0) {
            sar_analyzer_spike_obj->ldavgs_spike_each_file.ldavg_one_highest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("ldavg_five", element) == 0) {
            sar_analyzer_spike_obj->ldavgs_spike_each_file.ldavg_five_highest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("ldavg_15", element) == 0) {
            sar_analyzer_spike_obj->ldavgs_spike_each_file.ldavg_15_highest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("ldavg_one", element) == 0) {
            sar_analyzer_spike_obj->ldavgs_spike_each_file.ldavg_one_lowest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("ldavg_five", element) == 0) {
            sar_analyzer_spike_obj->ldavgs_spike_each_file.ldavg_five_lowest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("ldavg_15", element) == 0) {
            sar_analyzer_spike_obj->ldavgs_spike_each_file.ldavg_15_lowest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else
        return EXIT_FAILURE;
}

int set_block_device_spike_val_each_file(int x,  double var, int y, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("areqsz", element) == 0) {
            sar_analyzer_spike_obj->block_devices_spike_each_file.areqsz_spike_val_each_file[x][y] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("util", element) == 0) {
            sar_analyzer_spike_obj->block_devices_spike_each_file.util_spike_val_each_file[x][y] = var;
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("areqsz", element) == 0) {
            sar_analyzer_spike_obj->block_devices_spike_each_file.areqsz_highest_val_each_file[x][y] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("util", element) == 0) {
            sar_analyzer_spike_obj->block_devices_spike_each_file.util_highest_val_each_file[x][y] = var;
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("areqsz", element) == 0) {
            sar_analyzer_spike_obj->block_devices_spike_each_file.areqsz_lowest_val_each_file[x][y] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("util", element) == 0) {
            sar_analyzer_spike_obj->block_devices_spike_each_file.util_lowest_val_each_file[x][y] = var;
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else
        return EXIT_FAILURE;
}

int set_network_spike_val_each_file(int x,  double var, int y, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("rxpck", element) == 0) {
            sar_analyzer_spike_obj->networks_spike_each_file.rxpck_spike_val_each_file[x][y] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("txpck", element) == 0) {
            sar_analyzer_spike_obj->networks_spike_each_file.txpck_spike_val_each_file[x][y] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("rxkb", element) == 0) {
            sar_analyzer_spike_obj->networks_spike_each_file.rxkb_spike_val_each_file[x][y] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("txkb", element) == 0) {
            sar_analyzer_spike_obj->networks_spike_each_file.txkb_spike_val_each_file[x][y] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("rxerr", element) == 0) {
            sar_analyzer_spike_obj->networks_spike_each_file.rxerr_spike_val_each_file[x][y] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("txerr", element) == 0) {
            sar_analyzer_spike_obj->networks_spike_each_file.txerr_spike_val_each_file[x][y] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("rxdrop", element) == 0) {
            sar_analyzer_spike_obj->networks_spike_each_file.rxdrop_spike_val_each_file[x][y] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("txdrop", element) == 0) {
            sar_analyzer_spike_obj->networks_spike_each_file.txdrop_spike_val_each_file[x][y] = var;
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("rxpck", element) == 0) {
            sar_analyzer_spike_obj->networks_spike_each_file.rxpck_highest_val_each_file[x][y] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("txpck", element) == 0) {
            sar_analyzer_spike_obj->networks_spike_each_file.txpck_highest_val_each_file[x][y] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("rxkb", element) == 0) {
            sar_analyzer_spike_obj->networks_spike_each_file.rxkb_highest_val_each_file[x][y] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("txkb", element) == 0) {
            sar_analyzer_spike_obj->networks_spike_each_file.txkb_highest_val_each_file[x][y] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("rxerr", element) == 0) {
            sar_analyzer_spike_obj->networks_spike_each_file.rxerr_highest_val_each_file[x][y] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("txerr", element) == 0) {
            sar_analyzer_spike_obj->networks_spike_each_file.txerr_highest_val_each_file[x][y] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("rxdrop", element) == 0) {
            sar_analyzer_spike_obj->networks_spike_each_file.rxdrop_highest_val_each_file[x][y] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("txdrop", element) == 0) {
            sar_analyzer_spike_obj->networks_spike_each_file.txdrop_highest_val_each_file[x][y] = var;
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("rxpck", element) == 0) {
            sar_analyzer_spike_obj->networks_spike_each_file.rxpck_lowest_val_each_file[x][y] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("txpck", element) == 0) {
            sar_analyzer_spike_obj->networks_spike_each_file.txpck_lowest_val_each_file[x][y] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("rxkb", element) == 0) {
            sar_analyzer_spike_obj->networks_spike_each_file.rxkb_lowest_val_each_file[x][y] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("txkb", element) == 0) {
            sar_analyzer_spike_obj->networks_spike_each_file.txkb_lowest_val_each_file[x][y] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("rxerr", element) == 0) {
            sar_analyzer_spike_obj->networks_spike_each_file.rxerr_lowest_val_each_file[x][y] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("txerr", element) == 0) {
            sar_analyzer_spike_obj->networks_spike_each_file.txerr_lowest_val_each_file[x][y] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("rxdrop", element) == 0) {
            sar_analyzer_spike_obj->networks_spike_each_file.rxdrop_lowest_val_each_file[x][y] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("txdrop", element) == 0) {
            sar_analyzer_spike_obj->networks_spike_each_file.txdrop_lowest_val_each_file[x][y] = var;
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("down", analyze_item) == 0) {
        if (strcmp("rxpck", element) == 0) {
            sar_analyzer_spike_obj->networks_spike_each_file.rxpck_down_val_each_file[x][y] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("txpck", element) == 0) {
            sar_analyzer_spike_obj->networks_spike_each_file.txpck_down_val_each_file[x][y] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("rxkb", element) == 0) {
            sar_analyzer_spike_obj->networks_spike_each_file.rxkb_down_val_each_file[x][y] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("txkb", element) == 0) {
            sar_analyzer_spike_obj->networks_spike_each_file.txkb_down_val_each_file[x][y] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("rxerr", element) == 0) {
            sar_analyzer_spike_obj->networks_spike_each_file.rxerr_down_val_each_file[x][y] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("txerr", element) == 0) {
            sar_analyzer_spike_obj->networks_spike_each_file.txerr_down_val_each_file[x][y] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("rxdrop", element) == 0) {
            sar_analyzer_spike_obj->networks_spike_each_file.rxdrop_down_val_each_file[x][y] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("txdrop", element) == 0) {
            sar_analyzer_spike_obj->networks_spike_each_file.txdrop_down_val_each_file[x][y] = var;
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else
        return EXIT_FAILURE;
}


/* -- time-span spike val each file -- */

int set_cpu_time_span_spike_val_each_file(int x, double var, int y, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("usr", element) == 0) {
            sar_analyzer_time_span_spike_obj->cpus_time_span_spike_each_file.cpu_usr_time_span_spike_val_each_file[x][y] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("sys", element) == 0) {
            sar_analyzer_time_span_spike_obj->cpus_time_span_spike_each_file.cpu_sys_time_span_spike_val_each_file[x][y] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("iowait", element) == 0) {
            sar_analyzer_time_span_spike_obj->cpus_time_span_spike_each_file.cpu_iowait_time_span_spike_val_each_file[x][y] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("idle", element) == 0) {
            sar_analyzer_time_span_spike_obj->cpus_time_span_spike_each_file.cpu_idle_time_span_spike_val_each_file[x][y] = var;
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("usr", element) == 0) {
            sar_analyzer_time_span_spike_obj->cpus_time_span_spike_each_file.cpu_usr_time_span_highest_val_each_file[x][y] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("sys", element) == 0) {
            sar_analyzer_time_span_spike_obj->cpus_time_span_spike_each_file.cpu_sys_time_span_highest_val_each_file[x][y] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("iowait", element) == 0) {
            sar_analyzer_time_span_spike_obj->cpus_time_span_spike_each_file.cpu_iowait_time_span_highest_val_each_file[x][y] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("idle", element) == 0) {
            sar_analyzer_time_span_spike_obj->cpus_time_span_spike_each_file.cpu_idle_time_span_highest_val_each_file[x][y] = var;
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("usr", element) == 0) {
            sar_analyzer_time_span_spike_obj->cpus_time_span_spike_each_file.cpu_usr_time_span_lowest_val_each_file[x][y] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("sys", element) == 0) {
            sar_analyzer_time_span_spike_obj->cpus_time_span_spike_each_file.cpu_sys_time_span_lowest_val_each_file[x][y] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("iowait", element) == 0) {
            sar_analyzer_time_span_spike_obj->cpus_time_span_spike_each_file.cpu_iowait_time_span_lowest_val_each_file[x][y] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("idle", element) == 0) {
            sar_analyzer_time_span_spike_obj->cpus_time_span_spike_each_file.cpu_idle_time_span_lowest_val_each_file[x][y] = var;
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else
        return EXIT_FAILURE;
}

int set_tasks_time_span_spike_val_each_file(int x, double var, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("proc", element) == 0) {
            sar_analyzer_time_span_spike_obj->tasks_time_span_spike_each_file.proc_time_span_spike_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("cswch", element) == 0) {
            sar_analyzer_time_span_spike_obj->tasks_time_span_spike_each_file.cswch_time_span_spike_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("proc", element) == 0) {
            sar_analyzer_time_span_spike_obj->tasks_time_span_spike_each_file.proc_time_span_highest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("cswch", element) == 0) {
            sar_analyzer_time_span_spike_obj->tasks_time_span_spike_each_file.cswch_time_span_highest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("proc", element) == 0) {
            sar_analyzer_time_span_spike_obj->tasks_time_span_spike_each_file.proc_time_span_lowest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("cswch", element) == 0) {
            sar_analyzer_time_span_spike_obj->tasks_time_span_spike_each_file.cswch_time_span_lowest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else
        return EXIT_FAILURE;
}

int set_pswap_time_span_spike_val_each_file(int x, double var, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("pswpin", element) == 0) {
            sar_analyzer_time_span_spike_obj->pswaps_time_span_spike_each_file.pswpin_time_span_spike_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("pswpout", element) == 0) {
            sar_analyzer_time_span_spike_obj->pswaps_time_span_spike_each_file.pswpout_time_span_spike_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("pswpin", element) == 0) {
            sar_analyzer_time_span_spike_obj->pswaps_time_span_spike_each_file.pswpin_time_span_highest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("pswpout", element) == 0) {
            sar_analyzer_time_span_spike_obj->pswaps_time_span_spike_each_file.pswpout_time_span_highest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("pswpin", element) == 0) {
            sar_analyzer_time_span_spike_obj->pswaps_time_span_spike_each_file.pswpin_time_span_lowest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("pswpout", element) == 0) {
            sar_analyzer_time_span_spike_obj->pswaps_time_span_spike_each_file.pswpout_time_span_lowest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else
        return EXIT_FAILURE;
}

int set_paging_time_span_spike_val_each_file(int x, double var, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("pgpgin", element) == 0) {
            sar_analyzer_time_span_spike_obj->pagings_time_span_spike_each_file.pgpgin_time_span_spike_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("pgpgout", element) == 0) {
            sar_analyzer_time_span_spike_obj->pagings_time_span_spike_each_file.pgpgout_time_span_spike_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("fault", element) == 0) {
            sar_analyzer_time_span_spike_obj->pagings_time_span_spike_each_file.fault_time_span_spike_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("majflt", element) == 0) {
            sar_analyzer_time_span_spike_obj->pagings_time_span_spike_each_file.majflt_time_span_spike_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("vmeff", element) == 0) {
            sar_analyzer_time_span_spike_obj->pagings_time_span_spike_each_file.vmeff_time_span_spike_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("pgpgin", element) == 0) {
            sar_analyzer_time_span_spike_obj->pagings_time_span_spike_each_file.pgpgin_time_span_highest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("pgpgout", element) == 0) {
            sar_analyzer_time_span_spike_obj->pagings_time_span_spike_each_file.pgpgout_time_span_highest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("fault", element) == 0) {
            sar_analyzer_time_span_spike_obj->pagings_time_span_spike_each_file.fault_time_span_highest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("majflt", element) == 0) {
            sar_analyzer_time_span_spike_obj->pagings_time_span_spike_each_file.majflt_time_span_highest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("vmeff", element) == 0) {
            sar_analyzer_time_span_spike_obj->pagings_time_span_spike_each_file.vmeff_time_span_highest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("pgpgin", element) == 0) {
            sar_analyzer_time_span_spike_obj->pagings_time_span_spike_each_file.pgpgin_time_span_lowest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("pgpgout", element) == 0) {
            sar_analyzer_time_span_spike_obj->pagings_time_span_spike_each_file.pgpgout_time_span_lowest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("fault", element) == 0) {
            sar_analyzer_time_span_spike_obj->pagings_time_span_spike_each_file.fault_time_span_lowest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("majflt", element) == 0) {
            sar_analyzer_time_span_spike_obj->pagings_time_span_spike_each_file.majflt_time_span_lowest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("vmeff", element) == 0) {
            sar_analyzer_time_span_spike_obj->pagings_time_span_spike_each_file.vmeff_time_span_lowest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else
        return EXIT_FAILURE;
}

int set_io_transfer_rate_time_span_spike_val_each_file(int x, double var, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("tps", element) == 0) {
            sar_analyzer_time_span_spike_obj->io_transfer_rates_time_span_spike_each_file.tps_time_span_spike_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("bread", element) == 0) {
            sar_analyzer_time_span_spike_obj->io_transfer_rates_time_span_spike_each_file.bread_time_span_spike_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("bwrtn", element) == 0) {
            sar_analyzer_time_span_spike_obj->io_transfer_rates_time_span_spike_each_file.bwrtn_time_span_spike_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("tps", element) == 0) {
            sar_analyzer_time_span_spike_obj->io_transfer_rates_time_span_spike_each_file.tps_time_span_highest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("bread", element) == 0) {
            sar_analyzer_time_span_spike_obj->io_transfer_rates_time_span_spike_each_file.bread_time_span_highest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("bwrtn", element) == 0) {
            sar_analyzer_time_span_spike_obj->io_transfer_rates_time_span_spike_each_file.bwrtn_time_span_highest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("tps", element) == 0) {
            sar_analyzer_time_span_spike_obj->io_transfer_rates_time_span_spike_each_file.tps_time_span_lowest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("bread", element) == 0) {
            sar_analyzer_time_span_spike_obj->io_transfer_rates_time_span_spike_each_file.bread_time_span_lowest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("bwrtn", element) == 0) {
            sar_analyzer_time_span_spike_obj->io_transfer_rates_time_span_spike_each_file.bwrtn_time_span_lowest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else
        return EXIT_FAILURE;
}

int set_memory_double_time_span_spike_val_each_file(int x, double var, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("memused", element) == 0) {
            sar_analyzer_time_span_spike_obj->memories_time_span_spike_each_file.memused_time_span_spike_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("commit", element) == 0) {
            sar_analyzer_time_span_spike_obj->memories_time_span_spike_each_file.commit_time_span_spike_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("memused", element) == 0) {
            sar_analyzer_time_span_spike_obj->memories_time_span_spike_each_file.memused_time_span_highest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("commit", element) == 0) {
            sar_analyzer_time_span_spike_obj->memories_time_span_spike_each_file.commit_time_span_highest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("memused", element) == 0) {
            sar_analyzer_time_span_spike_obj->memories_time_span_spike_each_file.memused_time_span_lowest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("commit", element) == 0) {
            sar_analyzer_time_span_spike_obj->memories_time_span_spike_each_file.commit_time_span_lowest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else
        return EXIT_FAILURE;
}

int set_memory_int_time_span_spike_val_each_file(int x, int var, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("kbcommit", element) == 0) {
            sar_analyzer_time_span_spike_obj->memories_time_span_spike_each_file.kbcommit_time_span_spike_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("kbcommit", element) == 0) {
            sar_analyzer_time_span_spike_obj->memories_time_span_spike_each_file.kbcommit_time_span_highest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("kbcommit", element) == 0) {
            sar_analyzer_time_span_spike_obj->memories_time_span_spike_each_file.kbcommit_time_span_lowest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else
        return EXIT_FAILURE;
}

int set_swpused_time_span_spike_val_each_file(int x, double var, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        sar_analyzer_time_span_spike_obj->swaps_time_span_spike_each_file.swpused_time_span_spike_val_each_file[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("highest", analyze_item) == 0) {
        sar_analyzer_time_span_spike_obj->swaps_time_span_spike_each_file.swpused_time_span_highest_val_each_file[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("lowest", analyze_item) == 0) {
        sar_analyzer_time_span_spike_obj->swaps_time_span_spike_each_file.swpused_time_span_lowest_val_each_file[x] = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_kernel_table_time_span_spike_val_each_file(int x,  double var, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("dentunusd", element) == 0) {
            sar_analyzer_time_span_spike_obj->kernel_tables_time_span_spike_each_file.dentunusd_time_span_spike_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("file", element) == 0) {
            sar_analyzer_time_span_spike_obj->kernel_tables_time_span_spike_each_file.file_time_span_spike_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("inode", element) == 0) {
            sar_analyzer_time_span_spike_obj->kernel_tables_time_span_spike_each_file.inode_time_span_spike_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("dentunusd", element) == 0) {
            sar_analyzer_time_span_spike_obj->kernel_tables_time_span_spike_each_file.dentunusd_time_span_highest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("file", element) == 0) {
            sar_analyzer_time_span_spike_obj->kernel_tables_time_span_spike_each_file.file_time_span_highest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("inode", element) == 0) {
            sar_analyzer_time_span_spike_obj->kernel_tables_time_span_spike_each_file.inode_time_span_highest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("dentunusd", element) == 0) {
            sar_analyzer_time_span_spike_obj->kernel_tables_time_span_spike_each_file.dentunusd_time_span_lowest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("file", element) == 0) {
            sar_analyzer_time_span_spike_obj->kernel_tables_time_span_spike_each_file.file_time_span_lowest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("inode", element) == 0) {
            sar_analyzer_time_span_spike_obj->kernel_tables_time_span_spike_each_file.inode_time_span_lowest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else
        return EXIT_FAILURE;
}

int set_ldavg_int_time_span_spike_val_each_file(int x,  int var, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("runq_sz", element) == 0) {
            sar_analyzer_time_span_spike_obj->ldavgs_time_span_spike_each_file.runq_sz_time_span_spike_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("plist_sz", element) == 0) {
            sar_analyzer_time_span_spike_obj->ldavgs_time_span_spike_each_file.plist_sz_time_span_spike_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("runq_sz", element) == 0) {
            sar_analyzer_time_span_spike_obj->ldavgs_time_span_spike_each_file.runq_sz_time_span_highest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("plist_sz", element) == 0) {
            sar_analyzer_time_span_spike_obj->ldavgs_time_span_spike_each_file.plist_sz_time_span_highest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("runq_sz", element) == 0) {
            sar_analyzer_time_span_spike_obj->ldavgs_time_span_spike_each_file.runq_sz_time_span_lowest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("plist_sz", element) == 0) {
            sar_analyzer_time_span_spike_obj->ldavgs_time_span_spike_each_file.plist_sz_time_span_lowest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else
        return EXIT_FAILURE;
}

int set_ldavg_double_time_span_spike_val_each_file(int x,  double var, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("ldavg_one", element) == 0) {
            sar_analyzer_time_span_spike_obj->ldavgs_time_span_spike_each_file.ldavg_one_time_span_spike_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("ldavg_five", element) == 0) {
            sar_analyzer_time_span_spike_obj->ldavgs_time_span_spike_each_file.ldavg_five_time_span_spike_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("ldavg_15", element) == 0) {
            sar_analyzer_time_span_spike_obj->ldavgs_time_span_spike_each_file.ldavg_15_time_span_spike_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("ldavg_one", element) == 0) {
            sar_analyzer_time_span_spike_obj->ldavgs_time_span_spike_each_file.ldavg_one_time_span_highest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("ldavg_five", element) == 0) {
            sar_analyzer_time_span_spike_obj->ldavgs_time_span_spike_each_file.ldavg_five_time_span_highest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("ldavg_15", element) == 0) {
            sar_analyzer_time_span_spike_obj->ldavgs_time_span_spike_each_file.ldavg_15_time_span_highest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("ldavg_one", element) == 0) {
            sar_analyzer_time_span_spike_obj->ldavgs_time_span_spike_each_file.ldavg_one_time_span_lowest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("ldavg_five", element) == 0) {
            sar_analyzer_time_span_spike_obj->ldavgs_time_span_spike_each_file.ldavg_five_time_span_lowest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("ldavg_15", element) == 0) {
            sar_analyzer_time_span_spike_obj->ldavgs_time_span_spike_each_file.ldavg_15_time_span_lowest_val_each_file[x] = var;
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else
        return EXIT_FAILURE;
}

int set_block_device_time_span_spike_val_each_file(int x,  double var, int y, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("areqsz", element) == 0) {
            sar_analyzer_time_span_spike_obj->block_devices_time_span_spike_each_file.areqsz_time_span_spike_val_each_file[x][y] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("util", element) == 0) {
            sar_analyzer_time_span_spike_obj->block_devices_time_span_spike_each_file.util_time_span_spike_val_each_file[x][y] = var;
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("areqsz", element) == 0) {
            sar_analyzer_time_span_spike_obj->block_devices_time_span_spike_each_file.areqsz_time_span_highest_val_each_file[x][y] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("util", element) == 0) {
            sar_analyzer_time_span_spike_obj->block_devices_time_span_spike_each_file.util_time_span_highest_val_each_file[x][y] = var;
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("areqsz", element) == 0) {
            sar_analyzer_time_span_spike_obj->block_devices_time_span_spike_each_file.areqsz_time_span_lowest_val_each_file[x][y] = var;
            return EXIT_SUCCESS;
        } else if (strcmp("util", element) == 0) {
            sar_analyzer_time_span_spike_obj->block_devices_time_span_spike_each_file.util_time_span_lowest_val_each_file[x][y] = var;
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else
        return EXIT_FAILURE;
}

/* -- former val each file -- */

int set_cpu_former_val_each_file(int x, double var, int y, const char *element)
{
    if (strcmp("usr", element) == 0) {
        sar_analyzer_spike_obj->cpus_spike_each_file.cpu_usr_former_val_each_file[x][y] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("sys", element) == 0) {
        sar_analyzer_spike_obj->cpus_spike_each_file.cpu_sys_former_val_each_file[x][y] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("iowait", element) == 0) {
        sar_analyzer_spike_obj->cpus_spike_each_file.cpu_iowait_former_val_each_file[x][y] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("idle", element) == 0) {
        sar_analyzer_spike_obj->cpus_spike_each_file.cpu_idle_former_val_each_file[x][y] = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_tasks_former_val_each_file(int x, double var, const char *element)
{
    if (strcmp("proc", element) == 0) {
        sar_analyzer_spike_obj->tasks_spike_each_file.proc_former_val_each_file[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("cswch", element) == 0) {
        sar_analyzer_spike_obj->tasks_spike_each_file.cswch_former_val_each_file[x] = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_pswap_former_val_each_file(int x, double var, const char *element)
{
    if (strcmp("pswpin", element) == 0) {
        sar_analyzer_spike_obj->pswaps_spike_each_file.pswpin_former_val_each_file[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("pswpout", element) == 0) {
        sar_analyzer_spike_obj->pswaps_spike_each_file.pswpout_former_val_each_file[x] = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_paging_former_val_each_file(int x, double var, const char *element)
{
    if (strcmp("pgpgin", element) == 0) {
        sar_analyzer_spike_obj->pagings_spike_each_file.pgpgin_former_val_each_file[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("pgpgout", element) == 0) {
        sar_analyzer_spike_obj->pagings_spike_each_file.pgpgout_former_val_each_file[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("fault", element) == 0) {
        sar_analyzer_spike_obj->pagings_spike_each_file.fault_former_val_each_file[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("majflt", element) == 0) {
        sar_analyzer_spike_obj->pagings_spike_each_file.majflt_former_val_each_file[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("vmeff", element) == 0) {
        sar_analyzer_spike_obj->pagings_spike_each_file.vmeff_former_val_each_file[x] = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_io_transfer_rate_former_val_each_file(int x, double var, const char *element)
{
    if (strcmp("tps", element) == 0) {
        sar_analyzer_spike_obj->io_transfer_rates_spike_each_file.tps_former_val_each_file[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("bread", element) == 0) {
        sar_analyzer_spike_obj->io_transfer_rates_spike_each_file.bread_former_val_each_file[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("bwrtn", element) == 0) {
        sar_analyzer_spike_obj->io_transfer_rates_spike_each_file.bwrtn_former_val_each_file[x] = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_memory_double_former_val_each_file(int x, double var, const char *element)
{
    if (strcmp("memused", element) == 0) {
        sar_analyzer_spike_obj->memories_spike_each_file.memused_former_val_each_file[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("commit", element) == 0) {
        sar_analyzer_spike_obj->memories_spike_each_file.commit_former_val_each_file[x] = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_memory_int_former_val_each_file(int x, int var, const char *element)
{
    if (strcmp("kbcommit", element) == 0) {
        sar_analyzer_spike_obj->memories_spike_each_file.kbcommit_former_val_each_file[x] = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_swpused_former_val_each_file(int x, double var)
{
    sar_analyzer_spike_obj->swaps_spike_each_file.swpused_former_val_each_file[x] = var;
    return EXIT_SUCCESS;
}

int set_kernel_table_former_val_each_file(int x,  double var, const char *element)
{
    if (strcmp("dentunusd", element) == 0) {
        sar_analyzer_spike_obj->kernel_tables_spike_each_file.dentunusd_former_val_each_file[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("file", element) == 0) {
        sar_analyzer_spike_obj->kernel_tables_spike_each_file.file_former_val_each_file[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("inode", element) == 0) {
        sar_analyzer_spike_obj->kernel_tables_spike_each_file.inode_former_val_each_file[x] = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_ldavg_int_former_val_each_file(int x,  int var, const char *element)
{
    if (strcmp("runq_sz", element) == 0) {
        sar_analyzer_spike_obj->ldavgs_spike_each_file.runq_sz_former_val_each_file[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("plist_sz", element) == 0) {
        sar_analyzer_spike_obj->ldavgs_spike_each_file.plist_sz_former_val_each_file[x] = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_ldavg_double_former_val_each_file(int x,  double var, const char *element)
{
    if (strcmp("ldavg_one", element) == 0) {
        sar_analyzer_spike_obj->ldavgs_spike_each_file.ldavg_one_former_val_each_file[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("ldavg_five", element) == 0) {
        sar_analyzer_spike_obj->ldavgs_spike_each_file.ldavg_five_former_val_each_file[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("ldavg_15", element) == 0) {
        sar_analyzer_spike_obj->ldavgs_spike_each_file.ldavg_15_former_val_each_file[x] = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_block_device_former_val_each_file(int x,  double var, int y, const char *element)
{
    if (strcmp("areqsz", element) == 0) {
        sar_analyzer_spike_obj->block_devices_spike_each_file.areqsz_former_val_each_file[x][y] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("util", element) == 0) {
        sar_analyzer_spike_obj->block_devices_spike_each_file.util_former_val_each_file[x][y] = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_network_former_val_each_file(int x,  double var, int y, const char *element)
{
    if (strcmp("rxpck", element) == 0) {
        sar_analyzer_spike_obj->networks_spike_each_file.rxpck_former_val_each_file[x][y] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("txpck", element) == 0) {
        sar_analyzer_spike_obj->networks_spike_each_file.txpck_former_val_each_file[x][y] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("rxkb", element) == 0) {
        sar_analyzer_spike_obj->networks_spike_each_file.rxkb_former_val_each_file[x][y] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("txkb", element) == 0) {
        sar_analyzer_spike_obj->networks_spike_each_file.txkb_former_val_each_file[x][y] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("rxerr", element) == 0) {
        sar_analyzer_spike_obj->networks_spike_each_file.rxerr_former_val_each_file[x][y] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("txerr", element) == 0) {
        sar_analyzer_spike_obj->networks_spike_each_file.txerr_former_val_each_file[x][y] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("rxdrop", element) == 0) {
        sar_analyzer_spike_obj->networks_spike_each_file.rxdrop_former_val_each_file[x][y] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("txdrop", element) == 0) {
        sar_analyzer_spike_obj->networks_spike_each_file.txdrop_former_val_each_file[x][y] = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

/* -- time-span former val each file -- */

int set_cpu_time_span_former_val_each_file(int x, double var, int y, const char *element)
{
    if (strcmp("usr", element) == 0) {
        sar_analyzer_time_span_spike_obj->cpus_time_span_spike_each_file.cpu_usr_time_span_former_val_each_file[x][y] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("sys", element) == 0) {
        sar_analyzer_time_span_spike_obj->cpus_time_span_spike_each_file.cpu_sys_time_span_former_val_each_file[x][y] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("iowait", element) == 0) {
        sar_analyzer_time_span_spike_obj->cpus_time_span_spike_each_file.cpu_iowait_time_span_former_val_each_file[x][y] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("idle", element) == 0) {
        sar_analyzer_time_span_spike_obj->cpus_time_span_spike_each_file.cpu_idle_time_span_former_val_each_file[x][y] = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_tasks_time_span_former_val_each_file(int x, double var, const char *element)
{
    if (strcmp("proc", element) == 0) {
        sar_analyzer_time_span_spike_obj->tasks_time_span_spike_each_file.proc_time_span_former_val_each_file[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("cswch", element) == 0) {
        sar_analyzer_time_span_spike_obj->tasks_time_span_spike_each_file.cswch_time_span_former_val_each_file[x] = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_pswap_time_span_former_val_each_file(int x, double var, const char *element)
{
    if (strcmp("pswpin", element) == 0) {
        sar_analyzer_time_span_spike_obj->pswaps_time_span_spike_each_file.pswpin_time_span_former_val_each_file[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("pswpout", element) == 0) {
        sar_analyzer_time_span_spike_obj->pswaps_time_span_spike_each_file.pswpout_time_span_former_val_each_file[x] = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_paging_time_span_former_val_each_file(int x, double var, const char *element)
{
    if (strcmp("pgpgin", element) == 0) {
        sar_analyzer_time_span_spike_obj->pagings_time_span_spike_each_file.pgpgin_time_span_former_val_each_file[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("pgpgout", element) == 0) {
        sar_analyzer_time_span_spike_obj->pagings_time_span_spike_each_file.pgpgout_time_span_former_val_each_file[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("fault", element) == 0) {
        sar_analyzer_time_span_spike_obj->pagings_time_span_spike_each_file.fault_time_span_former_val_each_file[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("majflt", element) == 0) {
        sar_analyzer_time_span_spike_obj->pagings_time_span_spike_each_file.majflt_time_span_former_val_each_file[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("vmeff", element) == 0) {
        sar_analyzer_time_span_spike_obj->pagings_time_span_spike_each_file.vmeff_time_span_former_val_each_file[x] = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_io_transfer_rate_time_span_former_val_each_file(int x, double var, const char *element)
{
    if (strcmp("tps", element) == 0) {
        sar_analyzer_time_span_spike_obj->io_transfer_rates_time_span_spike_each_file.tps_time_span_former_val_each_file[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("bread", element) == 0) {
        sar_analyzer_time_span_spike_obj->io_transfer_rates_time_span_spike_each_file.bread_time_span_former_val_each_file[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("bwrtn", element) == 0) {
        sar_analyzer_time_span_spike_obj->io_transfer_rates_time_span_spike_each_file.bwrtn_time_span_former_val_each_file[x] = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_memory_double_time_span_former_val_each_file(int x, double var, const char *element)
{
    if (strcmp("memused", element) == 0) {
        sar_analyzer_time_span_spike_obj->memories_time_span_spike_each_file.memused_time_span_former_val_each_file[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("commit", element) == 0) {
        sar_analyzer_time_span_spike_obj->memories_time_span_spike_each_file.commit_time_span_former_val_each_file[x] = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_memory_int_time_span_former_val_each_file(int x, int var, const char *element)
{
    if (strcmp("kbcommit", element) == 0) {
        sar_analyzer_time_span_spike_obj->memories_time_span_spike_each_file.kbcommit_time_span_former_val_each_file[x] = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_swpused_time_span_former_val_each_file(int x, double var)
{
    sar_analyzer_time_span_spike_obj->swaps_time_span_spike_each_file.swpused_time_span_former_val_each_file[x] = var;
    return EXIT_SUCCESS;
}

int set_kernel_table_time_span_former_val_each_file(int x,  double var, const char *element)
{
    if (strcmp("dentunusd", element) == 0) {
        sar_analyzer_time_span_spike_obj->kernel_tables_time_span_spike_each_file.dentunusd_time_span_former_val_each_file[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("file", element) == 0) {
        sar_analyzer_time_span_spike_obj->kernel_tables_time_span_spike_each_file.file_time_span_former_val_each_file[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("inode", element) == 0) {
        sar_analyzer_time_span_spike_obj->kernel_tables_time_span_spike_each_file.inode_time_span_former_val_each_file[x] = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_ldavg_int_time_span_former_val_each_file(int x,  int var, const char *element)
{
    if (strcmp("runq_sz", element) == 0) {
        sar_analyzer_time_span_spike_obj->ldavgs_time_span_spike_each_file.runq_sz_time_span_former_val_each_file[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("plist_sz", element) == 0) {
        sar_analyzer_time_span_spike_obj->ldavgs_time_span_spike_each_file.plist_sz_time_span_former_val_each_file[x] = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_ldavg_double_time_span_former_val_each_file(int x,  double var, const char *element)
{
    if (strcmp("ldavg_one", element) == 0) {
        sar_analyzer_time_span_spike_obj->ldavgs_time_span_spike_each_file.ldavg_one_time_span_former_val_each_file[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("ldavg_five", element) == 0) {
        sar_analyzer_time_span_spike_obj->ldavgs_time_span_spike_each_file.ldavg_five_time_span_former_val_each_file[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("ldavg_15", element) == 0) {
        sar_analyzer_time_span_spike_obj->ldavgs_time_span_spike_each_file.ldavg_15_time_span_former_val_each_file[x] = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_block_device_time_span_former_val_each_file(int x,  double var, int y, const char *element)
{
    if (strcmp("areqsz", element) == 0) {
        sar_analyzer_time_span_spike_obj->block_devices_time_span_spike_each_file.areqsz_time_span_former_val_each_file[x][y] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("util", element) == 0) {
        sar_analyzer_time_span_spike_obj->block_devices_time_span_spike_each_file.util_time_span_former_val_each_file[x][y] = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

/* -- time-span former val each file -- */
/* -------- end Data -------- */

/* -------- Dates -------- */

/* -- spike date(for sar_analyzer_all_obj) -- */
int set_cpu_spike_date(const char *date_string, int x, const char *element)
{
    if (strcmp("usr", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_cpus_spike.cpu_usr_date[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("sys", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_cpus_spike.cpu_sys_date[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("iowait", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_cpus_spike.cpu_iowait_date[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("idle", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_cpus_spike.cpu_idle_date[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_tasks_spike_date(const char *date_string, const char *element)
{
    if (strcmp("proc", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_tasks_spike.proc_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("cswch", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_tasks_spike.cswch_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_pswap_spike_date(const char *date_string, const char *element)
{
    if (strcmp("pswpin", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_pswaps_spike.pswpin_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("pswpout", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_pswaps_spike.pswpout_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_paging_spike_date(const char *date_string, const char *element)
{
    if (strcmp("pgpgin", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_pagings_spike.pgpgin_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("pgpgout", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_pagings_spike.pgpgout_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("fault", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_pagings_spike.fault_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("majflt", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_pagings_spike.majflt_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("vmeff", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_pagings_spike.vmeff_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_io_transfer_rate_spike_date(const char *date_string, const char *element)
{
    if (strcmp("tps", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_io_transfer_rates_spike.tps_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("bread", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_io_transfer_rates_spike.bread_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("bwrtn", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_io_transfer_rates_spike.bwrtn_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_memory_spike_date(const char *date_string, const char *element)
{
    if (strcmp("memused", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_memories_spike.memused_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("kbcommit", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_memories_spike.kbcommit_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("commit", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_memories_spike.commit_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_swpused_spike_date(const char *date_string)
{
    strncpy(sar_analyzer_all_obj->date_swaps_spike.swpused_date, date_string, MAX_DATE_STRINGS - 1);
    return EXIT_SUCCESS;
}

int set_kernel_table_spike_date(const char *date_string, const char *element)
{
    if (strcmp("dentunusd", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_kernel_tables_spike.dentunusd_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("file", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_kernel_tables_spike.file_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("inode", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_kernel_tables_spike.inode_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_ldavg_spike_date(const char *date_string, const char *element)
{
    if (strcmp("runq_sz", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_ldavgs_spike.runq_sz_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("plist_sz", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_ldavgs_spike.plist_sz_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("ldavg_one", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_ldavgs_spike.ldavg_one_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("ldavg_five", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_ldavgs_spike.ldavg_five_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("ldavg_15", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_ldavgs_spike.ldavg_15_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_block_device_spike_date(const char *date_string, int x, const char *element)
{
    if (strcmp("areqsz", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_block_devices_spike.areqsz_date[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("util", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_block_devices_spike.util_date[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_network_spike_date(const char *date_string, int x, const char *element)
{
    if (strcmp("rxpck", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_networks_spike.rxpck_date[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("txpck", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_networks_spike.txpck_date[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("rxkb", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_networks_spike.rxkb_date[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("txkb", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_networks_spike.txkb_date[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("rxerr", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_networks_spike.rxerr_date[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("txerr", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_networks_spike.txerr_date[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("rxdrop", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_networks_spike.rxdrop_date[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("txdrop", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_networks_spike.txdrop_date[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

/* -- spike time(for sar_analyzer_all_obj) -- */

int set_cpu_spike_time(const char *date_string, int x, const char *element)
{
    if (strcmp("usr", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_cpus_spike.cpu_usr_time[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("sys", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_cpus_spike.cpu_sys_time[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("iowait", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_cpus_spike.cpu_iowait_time[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("idle", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_cpus_spike.cpu_idle_time[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_tasks_spike_time(const char *date_string, const char *element)
{
    if (strcmp("proc", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_tasks_spike.proc_time, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("cswch", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_tasks_spike.cswch_time, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_pswap_spike_time(const char *date_string, const char *element)
{
    if (strcmp("pswpin", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_pswaps_spike.pswpin_time, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("pswpout", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_pswaps_spike.pswpout_time, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_paging_spike_time(const char *date_string, const char *element)
{
    if (strcmp("pgpgin", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_pagings_spike.pgpgin_time, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("pgpgout", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_pagings_spike.pgpgout_time, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("fault", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_pagings_spike.fault_time, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("majflt", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_pagings_spike.majflt_time, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("vmeff", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_pagings_spike.vmeff_time, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_io_transfer_rate_spike_time(const char *date_string, const char *element)
{
    if (strcmp("tps", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_io_transfer_rates_spike.tps_time, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("bread", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_io_transfer_rates_spike.bread_time, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("bwrtn", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_io_transfer_rates_spike.bwrtn_time, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_memory_spike_time(const char *date_string, const char *element)
{
    if (strcmp("memused", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_memories_spike.memused_time, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("kbcommit", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_memories_spike.kbcommit_time, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("commit", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_memories_spike.commit_time, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_swpused_spike_time(const char *date_string)
{
    strncpy(sar_analyzer_all_obj->date_swaps_spike.swpused_time, date_string, MAX_DATE_STRINGS - 1);
    return EXIT_SUCCESS;
}

int set_kernel_table_spike_time(const char *date_string, const char *element)
{
    if (strcmp("dentunusd", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_kernel_tables_spike.dentunusd_time, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("file", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_kernel_tables_spike.file_time, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("inode", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_kernel_tables_spike.inode_time, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_ldavg_spike_time(const char *date_string, const char *element)
{
    if (strcmp("runq_sz", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_ldavgs_spike.runq_sz_time, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("plist_sz", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_ldavgs_spike.plist_sz_time, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("ldavg_one", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_ldavgs_spike.ldavg_one_time, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("ldavg_five", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_ldavgs_spike.ldavg_five_time, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("ldavg_15", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_ldavgs_spike.ldavg_15_time, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_block_device_spike_time(const char *date_string, int x, const char *element)
{
    if (strcmp("areqsz", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_block_devices_spike.areqsz_time[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("util", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_block_devices_spike.util_time[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_network_spike_time(const char *date_string, int x, const char *element)
{
    if (strcmp("rxpck", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_networks_spike.rxpck_time[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("txpck", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_networks_spike.txpck_time[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("rxkb", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_networks_spike.rxkb_time[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("txkb", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_networks_spike.txkb_time[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("rxerr", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_networks_spike.rxerr_time[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("txerr", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_networks_spike.txerr_time[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("rxdrop", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_networks_spike.rxdrop_time[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("txdrop", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_networks_spike.txdrop_time[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

/* -- spike date each file -- */

int set_cpu_spike_date_each_file(int x, const char *date_string, int y, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("usr", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_cpus_spike_each_file.cpu_usr_spike_date_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("sys", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_cpus_spike_each_file.cpu_sys_spike_date_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("iowait", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_cpus_spike_each_file.cpu_iowait_spike_date_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("idle", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_cpus_spike_each_file.cpu_idle_spike_date_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("usr", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_cpus_spike_each_file.cpu_usr_highest_date_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("sys", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_cpus_spike_each_file.cpu_sys_highest_date_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("iowait", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_cpus_spike_each_file.cpu_iowait_highest_date_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("idle", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_cpus_spike_each_file.cpu_idle_highest_date_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("usr", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_cpus_spike_each_file.cpu_usr_lowest_date_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("sys", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_cpus_spike_each_file.cpu_sys_lowest_date_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("iowait", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_cpus_spike_each_file.cpu_iowait_lowest_date_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("idle", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_cpus_spike_each_file.cpu_idle_lowest_date_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else
        return EXIT_FAILURE;
}

int set_tasks_spike_date_each_file(int x, const char *date_string, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("proc", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_tasks_spike_each_file.proc_spike_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("cswch", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_tasks_spike_each_file.cswch_spike_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("proc", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_tasks_spike_each_file.proc_highest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("cswch", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_tasks_spike_each_file.cswch_highest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("proc", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_tasks_spike_each_file.proc_lowest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("cswch", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_tasks_spike_each_file.cswch_lowest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else
        return EXIT_FAILURE;
}

int set_pswap_spike_date_each_file(int x, const char *date_string, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("pswpin", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_pswaps_spike_each_file.pswpin_spike_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("pswpout", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_pswaps_spike_each_file.pswpout_spike_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("pswpin", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_pswaps_spike_each_file.pswpin_highest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("pswpout", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_pswaps_spike_each_file.pswpout_highest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("pswpin", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_pswaps_spike_each_file.pswpin_lowest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("pswpout", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_pswaps_spike_each_file.pswpout_lowest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else
        return EXIT_FAILURE;
}

int set_paging_spike_date_each_file(int x, const char *date_string, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("pgpgin", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_pagings_spike_each_file.pgpgin_spike_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("pgpgout", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_pagings_spike_each_file.pgpgout_spike_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("fault", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_pagings_spike_each_file.fault_spike_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("majflt", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_pagings_spike_each_file.majflt_spike_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("vmeff", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_pagings_spike_each_file.vmeff_spike_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("pgpgin", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_pagings_spike_each_file.pgpgin_highest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("pgpgout", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_pagings_spike_each_file.pgpgout_highest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("fault", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_pagings_spike_each_file.fault_highest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("majflt", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_pagings_spike_each_file.majflt_highest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("vmeff", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_pagings_spike_each_file.vmeff_highest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("pgpgin", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_pagings_spike_each_file.pgpgin_lowest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("pgpgout", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_pagings_spike_each_file.pgpgout_lowest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("fault", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_pagings_spike_each_file.fault_lowest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("majflt", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_pagings_spike_each_file.majflt_lowest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("vmeff", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_pagings_spike_each_file.vmeff_lowest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else
        return EXIT_FAILURE;
}

int set_io_transfer_rate_spike_date_each_file(int x, const char *date_string, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("tps", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_io_transfer_rates_spike_each_file.tps_spike_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("bread", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_io_transfer_rates_spike_each_file.bread_spike_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("bwrtn", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_io_transfer_rates_spike_each_file.bwrtn_spike_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("tps", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_io_transfer_rates_spike_each_file.tps_highest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("bread", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_io_transfer_rates_spike_each_file.bread_highest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("bwrtn", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_io_transfer_rates_spike_each_file.bwrtn_highest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("tps", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_io_transfer_rates_spike_each_file.tps_lowest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("bread", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_io_transfer_rates_spike_each_file.bread_lowest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("bwrtn", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_io_transfer_rates_spike_each_file.bwrtn_lowest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else
        return EXIT_FAILURE;
}

int set_memory_spike_date_each_file(int x, const char *date_string, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("memused", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_memories_spike_each_file.memused_spike_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("kbcommit", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_memories_spike_each_file.kbcommit_spike_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("commit", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_memories_spike_each_file.commit_spike_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("memused", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_memories_spike_each_file.memused_highest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("kbcommit", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_memories_spike_each_file.kbcommit_highest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("commit", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_memories_spike_each_file.commit_highest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("memused", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_memories_spike_each_file.memused_lowest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("kbcommit", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_memories_spike_each_file.kbcommit_lowest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("commit", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_memories_spike_each_file.commit_lowest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else
        return EXIT_FAILURE;
}

int set_swpused_spike_date_each_file(int x, const char *date_string, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        strncpy(sar_analyzer_spike_obj->date_swaps_spike_each_file.swpused_spike_date_each_file[x] , date_string, MAX_DATE_STRINGS);
        return EXIT_SUCCESS;
    } else if (strcmp("highest", analyze_item) == 0) {
        strncpy(sar_analyzer_spike_obj->date_swaps_spike_each_file.swpused_highest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
        return EXIT_SUCCESS;
    } else if (strcmp("lowest", analyze_item) == 0) {
        strncpy(sar_analyzer_spike_obj->date_swaps_spike_each_file.swpused_lowest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_kernel_table_spike_date_each_file(int x, const char *date_string, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("dentunusd", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_kernel_tables_spike_each_file.dentunusd_spike_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("file", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_kernel_tables_spike_each_file.file_spike_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("inode", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_kernel_tables_spike_each_file.inode_spike_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("dentunusd", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_kernel_tables_spike_each_file.dentunusd_highest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("file", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_kernel_tables_spike_each_file.file_highest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("inode", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_kernel_tables_spike_each_file.inode_highest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("dentunusd", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_kernel_tables_spike_each_file.dentunusd_lowest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("file", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_kernel_tables_spike_each_file.file_lowest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("inode", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_kernel_tables_spike_each_file.inode_lowest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else
        return EXIT_FAILURE;
}

int set_ldavg_spike_date_each_file(int x, const char *date_string, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("runq_sz", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_ldavgs_spike_each_file.runq_sz_spike_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("plist_sz", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_ldavgs_spike_each_file.plist_sz_spike_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("ldavg_one", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_ldavgs_spike_each_file.ldavg_one_spike_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("ldavg_five", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_ldavgs_spike_each_file.ldavg_five_spike_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("ldavg_15", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_ldavgs_spike_each_file.ldavg_15_spike_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("runq_sz", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_ldavgs_spike_each_file.runq_sz_highest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("plist_sz", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_ldavgs_spike_each_file.plist_sz_highest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("ldavg_one", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_ldavgs_spike_each_file.ldavg_one_highest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("ldavg_five", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_ldavgs_spike_each_file.ldavg_five_highest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("ldavg_15", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_ldavgs_spike_each_file.ldavg_15_highest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("runq_sz", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_ldavgs_spike_each_file.runq_sz_lowest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("plist_sz", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_ldavgs_spike_each_file.plist_sz_lowest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("ldavg_one", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_ldavgs_spike_each_file.ldavg_one_lowest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("ldavg_five", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_ldavgs_spike_each_file.ldavg_five_lowest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("ldavg_15", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_ldavgs_spike_each_file.ldavg_15_lowest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else
        return EXIT_FAILURE;
}

int set_block_device_spike_date_each_file(int x, const char *date_string, int y, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("areqsz", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_block_devices_spike_each_file.areqsz_spike_date_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("util", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_block_devices_spike_each_file.util_spike_date_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("areqsz", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_block_devices_spike_each_file.areqsz_highest_date_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("util", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_block_devices_spike_each_file.util_highest_date_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("areqsz", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_block_devices_spike_each_file.areqsz_lowest_date_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("util", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_block_devices_spike_each_file.util_lowest_date_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else
        return EXIT_FAILURE;
}

int set_network_spike_date_each_file(int x, const char *date_string, int y, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("rxpck", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_networks_spike_each_file.rxpck_spike_date_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("txpck", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_networks_spike_each_file.txpck_spike_date_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("rxkb", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_networks_spike_each_file.rxkb_spike_date_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("txkb", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_networks_spike_each_file.txkb_spike_date_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("rxerr", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_networks_spike_each_file.rxerr_spike_date_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("txerr", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_networks_spike_each_file.txerr_spike_date_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("rxdrop", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_networks_spike_each_file.rxdrop_spike_date_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("txdrop", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_networks_spike_each_file.txdrop_spike_date_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("rxpck", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_networks_spike_each_file.rxpck_highest_date_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("txpck", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_networks_spike_each_file.txpck_highest_date_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("rxkb", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_networks_spike_each_file.rxkb_highest_date_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("txkb", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_networks_spike_each_file.txkb_highest_date_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("rxerr", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_networks_spike_each_file.rxerr_highest_date_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("txerr", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_networks_spike_each_file.txerr_highest_date_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("rxdrop", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_networks_spike_each_file.rxdrop_highest_date_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("txdrop", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_networks_spike_each_file.txdrop_highest_date_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("rxpck", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_networks_spike_each_file.rxpck_lowest_date_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("txpck", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_networks_spike_each_file.txpck_lowest_date_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("rxkb", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_networks_spike_each_file.rxkb_lowest_date_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("txkb", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_networks_spike_each_file.txkb_lowest_date_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("rxerr", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_networks_spike_each_file.rxerr_lowest_date_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("txerr", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_networks_spike_each_file.txerr_lowest_date_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("rxdrop", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_networks_spike_each_file.rxdrop_lowest_date_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("txdrop", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_networks_spike_each_file.txdrop_lowest_date_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("down", analyze_item) == 0) {
        if (strcmp("rxpck", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_networks_spike_each_file.rxpck_down_date_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("txpck", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_networks_spike_each_file.txpck_down_date_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("rxkb", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_networks_spike_each_file.rxkb_down_date_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("txkb", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_networks_spike_each_file.txkb_down_date_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("rxerr", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_networks_spike_each_file.rxerr_down_date_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("txerr", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_networks_spike_each_file.txerr_down_date_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("rxdrop", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_networks_spike_each_file.rxdrop_down_date_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("txdrop", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_networks_spike_each_file.txdrop_down_date_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else
        return EXIT_FAILURE;
}


/* -- time-span spike date each file -- */

int set_cpu_time_span_spike_date_each_file(int x, const char *date_string, int y, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("usr", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_cpus_time_span_spike_each_file.cpu_usr_time_span_spike_date_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("sys", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_cpus_time_span_spike_each_file.cpu_sys_time_span_spike_date_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("iowait", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_cpus_time_span_spike_each_file.cpu_iowait_time_span_spike_date_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("idle", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_cpus_time_span_spike_each_file.cpu_idle_time_span_spike_date_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("usr", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_cpus_time_span_spike_each_file.cpu_usr_time_span_highest_date_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("sys", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_cpus_time_span_spike_each_file.cpu_sys_time_span_highest_date_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("iowait", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_cpus_time_span_spike_each_file.cpu_iowait_time_span_highest_date_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("idle", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_cpus_time_span_spike_each_file.cpu_idle_time_span_highest_date_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("usr", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_cpus_time_span_spike_each_file.cpu_usr_time_span_lowest_date_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("sys", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_cpus_time_span_spike_each_file.cpu_sys_time_span_lowest_date_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("iowait", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_cpus_time_span_spike_each_file.cpu_iowait_time_span_lowest_date_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("idle", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_cpus_time_span_spike_each_file.cpu_idle_time_span_lowest_date_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else
        return EXIT_FAILURE;
}

int set_tasks_time_span_spike_date_each_file(int x, const char *date_string, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("proc", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_tasks_time_span_spike_each_file.proc_time_span_spike_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("cswch", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_tasks_time_span_spike_each_file.cswch_time_span_spike_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("proc", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_tasks_time_span_spike_each_file.proc_time_span_highest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("cswch", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_tasks_time_span_spike_each_file.cswch_time_span_highest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("proc", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_tasks_time_span_spike_each_file.proc_time_span_lowest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("cswch", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_tasks_time_span_spike_each_file.cswch_time_span_lowest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else
        return EXIT_FAILURE;
}

int set_pswap_time_span_spike_date_each_file(int x, const char *date_string, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("pswpin", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_pswaps_time_span_spike_each_file.pswpin_time_span_spike_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("pswpout", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_pswaps_time_span_spike_each_file.pswpout_time_span_spike_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("pswpin", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_pswaps_time_span_spike_each_file.pswpin_time_span_highest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("pswpout", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_pswaps_time_span_spike_each_file.pswpout_time_span_highest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("pswpin", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_pswaps_time_span_spike_each_file.pswpin_time_span_lowest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("pswpout", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_pswaps_time_span_spike_each_file.pswpout_time_span_lowest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else
        return EXIT_FAILURE;
}

int set_paging_time_span_spike_date_each_file(int x, const char *date_string, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("pgpgin", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_pagings_time_span_spike_each_file.pgpgin_time_span_spike_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("pgpgout", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_pagings_time_span_spike_each_file.pgpgout_time_span_spike_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("fault", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_pagings_time_span_spike_each_file.fault_time_span_spike_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("majflt", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_pagings_time_span_spike_each_file.majflt_time_span_spike_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("vmeff", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_pagings_time_span_spike_each_file.vmeff_time_span_spike_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("pgpgin", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_pagings_time_span_spike_each_file.pgpgin_time_span_highest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("pgpgout", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_pagings_time_span_spike_each_file.pgpgout_time_span_highest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("fault", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_pagings_time_span_spike_each_file.fault_time_span_highest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("majflt", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_pagings_time_span_spike_each_file.majflt_time_span_highest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("vmeff", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_pagings_time_span_spike_each_file.vmeff_time_span_highest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("pgpgin", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_pagings_time_span_spike_each_file.pgpgin_time_span_lowest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("pgpgout", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_pagings_time_span_spike_each_file.pgpgout_time_span_lowest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("fault", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_pagings_time_span_spike_each_file.fault_time_span_lowest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("majflt", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_pagings_time_span_spike_each_file.majflt_time_span_lowest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("vmeff", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_pagings_time_span_spike_each_file.vmeff_time_span_lowest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else
        return EXIT_FAILURE;
}

int set_io_transfer_rate_time_span_spike_date_each_file(int x, const char *date_string, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("tps", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_io_transfer_rates_time_span_spike_each_file.tps_time_span_spike_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("bread", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_io_transfer_rates_time_span_spike_each_file.bread_time_span_spike_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("bwrtn", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_io_transfer_rates_time_span_spike_each_file.bwrtn_time_span_spike_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("tps", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_io_transfer_rates_time_span_spike_each_file.tps_time_span_highest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("bread", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_io_transfer_rates_time_span_spike_each_file.bread_time_span_highest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("bwrtn", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_io_transfer_rates_time_span_spike_each_file.bwrtn_time_span_highest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("tps", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_io_transfer_rates_time_span_spike_each_file.tps_time_span_lowest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("bread", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_io_transfer_rates_time_span_spike_each_file.bread_time_span_lowest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("bwrtn", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_io_transfer_rates_time_span_spike_each_file.bwrtn_time_span_lowest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else
        return EXIT_FAILURE;
}

int set_memory_time_span_spike_date_each_file(int x, const char *date_string, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("memused", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_memories_time_span_spike_each_file.memused_time_span_spike_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("kbcommit", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_memories_time_span_spike_each_file.kbcommit_time_span_spike_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("commit", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_memories_time_span_spike_each_file.commit_time_span_spike_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("memused", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_memories_time_span_spike_each_file.memused_time_span_highest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("kbcommit", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_memories_time_span_spike_each_file.kbcommit_time_span_highest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("commit", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_memories_time_span_spike_each_file.commit_time_span_highest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("memused", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_memories_time_span_spike_each_file.memused_time_span_lowest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("kbcommit", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_memories_time_span_spike_each_file.kbcommit_time_span_lowest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("commit", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_memories_time_span_spike_each_file.commit_time_span_lowest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else
        return EXIT_FAILURE;
}

int set_swpused_time_span_spike_date_each_file(int x, const char *date_string, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        strncpy(sar_analyzer_time_span_spike_obj->date_swaps_time_span_spike_each_file.swpused_time_span_spike_date_each_file[x] , date_string, MAX_DATE_STRINGS);
        return EXIT_SUCCESS;
    } else if (strcmp("highest", analyze_item) == 0) {
        strncpy(sar_analyzer_time_span_spike_obj->date_swaps_time_span_spike_each_file.swpused_time_span_highest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
        return EXIT_SUCCESS;
    } else if (strcmp("lowest", analyze_item) == 0) {
        strncpy(sar_analyzer_time_span_spike_obj->date_swaps_time_span_spike_each_file.swpused_time_span_lowest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_kernel_table_time_span_spike_date_each_file(int x, const char *date_string, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("dentunusd", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_kernel_tables_time_span_spike_each_file.dentunusd_time_span_spike_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("file", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_kernel_tables_time_span_spike_each_file.file_time_span_spike_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("inode", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_kernel_tables_time_span_spike_each_file.inode_time_span_spike_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("dentunusd", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_kernel_tables_time_span_spike_each_file.dentunusd_time_span_highest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("file", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_kernel_tables_time_span_spike_each_file.file_time_span_highest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("inode", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_kernel_tables_time_span_spike_each_file.inode_time_span_highest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("dentunusd", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_kernel_tables_time_span_spike_each_file.dentunusd_time_span_lowest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("file", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_kernel_tables_time_span_spike_each_file.file_time_span_lowest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("inode", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_kernel_tables_time_span_spike_each_file.inode_time_span_lowest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else
        return EXIT_FAILURE;
}

int set_ldavg_time_span_spike_date_each_file(int x, const char *date_string, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("runq_sz", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_ldavgs_time_span_spike_each_file.runq_sz_time_span_spike_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("plist_sz", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_ldavgs_time_span_spike_each_file.plist_sz_time_span_spike_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("ldavg_one", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_ldavgs_time_span_spike_each_file.ldavg_one_time_span_spike_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("ldavg_five", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_ldavgs_time_span_spike_each_file.ldavg_five_time_span_spike_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("ldavg_15", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_ldavgs_time_span_spike_each_file.ldavg_15_time_span_spike_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("runq_sz", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_ldavgs_time_span_spike_each_file.runq_sz_time_span_highest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("plist_sz", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_ldavgs_time_span_spike_each_file.plist_sz_time_span_highest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("ldavg_one", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_ldavgs_time_span_spike_each_file.ldavg_one_time_span_highest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("ldavg_five", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_ldavgs_time_span_spike_each_file.ldavg_five_time_span_highest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("ldavg_15", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_ldavgs_time_span_spike_each_file.ldavg_15_time_span_highest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("runq_sz", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_ldavgs_time_span_spike_each_file.runq_sz_time_span_lowest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("plist_sz", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_ldavgs_time_span_spike_each_file.plist_sz_time_span_lowest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("ldavg_one", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_ldavgs_time_span_spike_each_file.ldavg_one_time_span_lowest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("ldavg_five", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_ldavgs_time_span_spike_each_file.ldavg_five_time_span_lowest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("ldavg_15", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_ldavgs_time_span_spike_each_file.ldavg_15_time_span_lowest_date_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else
        return EXIT_FAILURE;
}

int set_block_device_time_span_spike_date_each_file(int x, const char *date_string, int y, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("areqsz", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_block_devices_time_span_spike_each_file.areqsz_time_span_spike_date_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("util", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_block_devices_time_span_spike_each_file.util_time_span_spike_date_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("areqsz", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_block_devices_time_span_spike_each_file.areqsz_time_span_highest_date_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("util", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_block_devices_time_span_spike_each_file.util_time_span_highest_date_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("areqsz", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_block_devices_time_span_spike_each_file.areqsz_time_span_lowest_date_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("util", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_block_devices_time_span_spike_each_file.util_time_span_lowest_date_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else
        return EXIT_FAILURE;
}

/* -- spike time each file -- */

int set_cpu_spike_time_each_file(int x, const char *date_string, int y, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("usr", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_cpus_spike_each_file.cpu_usr_spike_time_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("sys", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_cpus_spike_each_file.cpu_sys_spike_time_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("iowait", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_cpus_spike_each_file.cpu_iowait_spike_time_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("idle", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_cpus_spike_each_file.cpu_idle_spike_time_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("usr", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_cpus_spike_each_file.cpu_usr_highest_time_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("sys", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_cpus_spike_each_file.cpu_sys_highest_time_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("iowait", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_cpus_spike_each_file.cpu_iowait_highest_time_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("idle", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_cpus_spike_each_file.cpu_idle_highest_time_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("usr", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_cpus_spike_each_file.cpu_usr_lowest_time_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("sys", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_cpus_spike_each_file.cpu_sys_lowest_time_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("iowait", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_cpus_spike_each_file.cpu_iowait_lowest_time_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("idle", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_cpus_spike_each_file.cpu_idle_lowest_time_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else
        return EXIT_FAILURE;
}

int set_tasks_spike_time_each_file(int x, const char *date_string, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("proc", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_tasks_spike_each_file.proc_spike_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("cswch", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_tasks_spike_each_file.cswch_spike_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("proc", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_tasks_spike_each_file.proc_highest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("cswch", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_tasks_spike_each_file.cswch_highest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("proc", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_tasks_spike_each_file.proc_lowest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("cswch", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_tasks_spike_each_file.cswch_lowest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else
        return EXIT_FAILURE;
}

int set_pswap_spike_time_each_file(int x, const char *date_string, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("pswpin", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_pswaps_spike_each_file.pswpin_spike_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("pswpout", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_pswaps_spike_each_file.pswpout_spike_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("pswpin", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_pswaps_spike_each_file.pswpin_highest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("pswpout", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_pswaps_spike_each_file.pswpout_highest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("pswpin", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_pswaps_spike_each_file.pswpin_lowest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("pswpout", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_pswaps_spike_each_file.pswpout_lowest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else
        return EXIT_FAILURE;
}

int set_paging_spike_time_each_file(int x, const char *date_string, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("pgpgin", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_pagings_spike_each_file.pgpgin_spike_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("pgpgout", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_pagings_spike_each_file.pgpgout_spike_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("fault", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_pagings_spike_each_file.fault_spike_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("majflt", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_pagings_spike_each_file.majflt_spike_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("vmeff", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_pagings_spike_each_file.vmeff_spike_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("pgpgin", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_pagings_spike_each_file.pgpgin_highest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("pgpgout", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_pagings_spike_each_file.pgpgout_highest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("fault", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_pagings_spike_each_file.fault_highest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("majflt", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_pagings_spike_each_file.majflt_highest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("vmeff", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_pagings_spike_each_file.vmeff_highest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("pgpgin", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_pagings_spike_each_file.pgpgin_lowest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("pgpgout", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_pagings_spike_each_file.pgpgout_lowest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("fault", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_pagings_spike_each_file.fault_lowest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("majflt", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_pagings_spike_each_file.majflt_lowest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("vmeff", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_pagings_spike_each_file.vmeff_lowest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else
        return EXIT_FAILURE;
}

int set_io_transfer_rate_spike_time_each_file(int x, const char *date_string, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("tps", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_io_transfer_rates_spike_each_file.tps_spike_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("bread", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_io_transfer_rates_spike_each_file.bread_spike_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("bwrtn", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_io_transfer_rates_spike_each_file.bwrtn_spike_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("tps", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_io_transfer_rates_spike_each_file.tps_highest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("bread", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_io_transfer_rates_spike_each_file.bread_highest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("bwrtn", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_io_transfer_rates_spike_each_file.bwrtn_highest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("tps", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_io_transfer_rates_spike_each_file.tps_lowest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("bread", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_io_transfer_rates_spike_each_file.bread_lowest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("bwrtn", element) == 0) { 
            strncpy(sar_analyzer_spike_obj->date_io_transfer_rates_spike_each_file.bwrtn_lowest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else
        return EXIT_FAILURE;
}

int set_memory_spike_time_each_file(int x, const char *date_string, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("memused", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_memories_spike_each_file.memused_spike_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("kbcommit", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_memories_spike_each_file.kbcommit_spike_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("commit", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_memories_spike_each_file.commit_spike_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("memused", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_memories_spike_each_file.memused_highest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("kbcommit", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_memories_spike_each_file.kbcommit_highest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("commit", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_memories_spike_each_file.commit_highest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("memused", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_memories_spike_each_file.memused_lowest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("kbcommit", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_memories_spike_each_file.kbcommit_lowest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("commit", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_memories_spike_each_file.commit_lowest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else
        return EXIT_FAILURE;
}

int set_swpused_spike_time_each_file(int x, const char *date_string, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        strncpy(sar_analyzer_spike_obj->date_swaps_spike_each_file.swpused_spike_time_each_file[x] , date_string, MAX_DATE_STRINGS);
        return EXIT_SUCCESS;
    } else if (strcmp("highest", analyze_item) == 0) {
        strncpy(sar_analyzer_spike_obj->date_swaps_spike_each_file.swpused_highest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
        return EXIT_SUCCESS;
    } else if (strcmp("lowest", analyze_item) == 0) {
        strncpy(sar_analyzer_spike_obj->date_swaps_spike_each_file.swpused_lowest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_kernel_table_spike_time_each_file(int x, const char *date_string, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("dentunusd", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_kernel_tables_spike_each_file.dentunusd_spike_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("file", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_kernel_tables_spike_each_file.file_spike_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("inode", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_kernel_tables_spike_each_file.inode_spike_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("dentunusd", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_kernel_tables_spike_each_file.dentunusd_highest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("file", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_kernel_tables_spike_each_file.file_highest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("inode", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_kernel_tables_spike_each_file.inode_highest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("dentunusd", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_kernel_tables_spike_each_file.dentunusd_lowest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("file", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_kernel_tables_spike_each_file.file_lowest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("inode", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_kernel_tables_spike_each_file.inode_lowest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else
        return EXIT_FAILURE;
}

int set_ldavg_spike_time_each_file(int x, const char *date_string, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("runq_sz", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_ldavgs_spike_each_file.runq_sz_spike_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("plist_sz", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_ldavgs_spike_each_file.plist_sz_spike_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("ldavg_one", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_ldavgs_spike_each_file.ldavg_one_spike_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("ldavg_five", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_ldavgs_spike_each_file.ldavg_five_spike_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("ldavg_15", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_ldavgs_spike_each_file.ldavg_15_spike_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("runq_sz", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_ldavgs_spike_each_file.runq_sz_highest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("plist_sz", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_ldavgs_spike_each_file.plist_sz_highest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("ldavg_one", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_ldavgs_spike_each_file.ldavg_one_highest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("ldavg_five", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_ldavgs_spike_each_file.ldavg_five_highest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("ldavg_15", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_ldavgs_spike_each_file.ldavg_15_highest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("runq_sz", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_ldavgs_spike_each_file.runq_sz_lowest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("plist_sz", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_ldavgs_spike_each_file.plist_sz_lowest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("ldavg_one", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_ldavgs_spike_each_file.ldavg_one_lowest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("ldavg_five", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_ldavgs_spike_each_file.ldavg_five_lowest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("ldavg_15", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_ldavgs_spike_each_file.ldavg_15_lowest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else
        return EXIT_FAILURE;
}

int set_block_device_spike_time_each_file(int x, const char *date_string, int y, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("areqsz", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_block_devices_spike_each_file.areqsz_spike_time_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("util", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_block_devices_spike_each_file.util_spike_time_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("areqsz", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_block_devices_spike_each_file.areqsz_highest_time_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("util", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_block_devices_spike_each_file.util_highest_time_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("areqsz", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_block_devices_spike_each_file.areqsz_lowest_time_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("util", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_block_devices_spike_each_file.util_lowest_time_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else
        return EXIT_FAILURE;
}

int set_network_spike_time_each_file(int x, const char *date_string, int y, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("rxpck", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_networks_spike_each_file.rxpck_spike_time_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("txpck", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_networks_spike_each_file.txpck_spike_time_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("rxkb", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_networks_spike_each_file.rxkb_spike_time_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("txkb", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_networks_spike_each_file.txkb_spike_time_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("rxerr", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_networks_spike_each_file.rxerr_spike_time_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("txerr", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_networks_spike_each_file.txerr_spike_time_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("rxdrop", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_networks_spike_each_file.rxdrop_spike_time_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("txdrop", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_networks_spike_each_file.txdrop_spike_time_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("rxpck", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_networks_spike_each_file.rxpck_highest_time_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("txpck", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_networks_spike_each_file.txpck_highest_time_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("rxkb", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_networks_spike_each_file.rxkb_highest_time_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("txkb", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_networks_spike_each_file.txkb_highest_time_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("rxerr", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_networks_spike_each_file.rxerr_highest_time_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("txerr", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_networks_spike_each_file.txerr_highest_time_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("rxdrop", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_networks_spike_each_file.rxdrop_highest_time_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("txdrop", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_networks_spike_each_file.txdrop_highest_time_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("rxpck", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_networks_spike_each_file.rxpck_lowest_time_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("txpck", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_networks_spike_each_file.txpck_lowest_time_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("rxkb", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_networks_spike_each_file.rxkb_lowest_time_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("txkb", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_networks_spike_each_file.txkb_lowest_time_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("rxerr", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_networks_spike_each_file.rxerr_lowest_time_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("txerr", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_networks_spike_each_file.txerr_lowest_time_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("rxdrop", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_networks_spike_each_file.rxdrop_lowest_time_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("txdrop", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_networks_spike_each_file.txdrop_lowest_time_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("down", analyze_item) == 0) {
        if (strcmp("rxpck", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_networks_spike_each_file.rxpck_down_time_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("txpck", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_networks_spike_each_file.txpck_down_time_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("rxkb", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_networks_spike_each_file.rxkb_down_time_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("txkb", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_networks_spike_each_file.txkb_down_time_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("rxerr", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_networks_spike_each_file.rxerr_down_time_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("txerr", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_networks_spike_each_file.txerr_down_time_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("rxdrop", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_networks_spike_each_file.rxdrop_down_time_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("txdrop", element) == 0) {
            strncpy(sar_analyzer_spike_obj->date_networks_spike_each_file.txdrop_down_time_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else
        return EXIT_FAILURE;
}

/* -- time-span spike time each file -- */

int set_cpu_time_span_spike_time_each_file(int x, const char *date_string, int y, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("usr", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_cpus_time_span_spike_each_file.cpu_usr_time_span_spike_time_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("sys", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_cpus_time_span_spike_each_file.cpu_sys_time_span_spike_time_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("iowait", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_cpus_time_span_spike_each_file.cpu_iowait_time_span_spike_time_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("idle", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_cpus_time_span_spike_each_file.cpu_idle_time_span_spike_time_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("usr", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_cpus_time_span_spike_each_file.cpu_usr_time_span_highest_time_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("sys", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_cpus_time_span_spike_each_file.cpu_sys_time_span_highest_time_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("iowait", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_cpus_time_span_spike_each_file.cpu_iowait_time_span_highest_time_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("idle", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_cpus_time_span_spike_each_file.cpu_idle_time_span_highest_time_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("usr", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_cpus_time_span_spike_each_file.cpu_usr_time_span_lowest_time_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("sys", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_cpus_time_span_spike_each_file.cpu_sys_time_span_lowest_time_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("iowait", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_cpus_time_span_spike_each_file.cpu_iowait_time_span_lowest_time_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("idle", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_cpus_time_span_spike_each_file.cpu_idle_time_span_lowest_time_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else
        return EXIT_FAILURE;
}

int set_tasks_time_span_spike_time_each_file(int x, const char *date_string, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("proc", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_tasks_time_span_spike_each_file.proc_time_span_spike_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("cswch", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_tasks_time_span_spike_each_file.cswch_time_span_spike_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("proc", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_tasks_time_span_spike_each_file.proc_time_span_highest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("cswch", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_tasks_time_span_spike_each_file.cswch_time_span_highest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("proc", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_tasks_time_span_spike_each_file.proc_time_span_lowest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("cswch", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_tasks_time_span_spike_each_file.cswch_time_span_lowest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else
        return EXIT_FAILURE;
}

int set_pswap_time_span_spike_time_each_file(int x, const char *date_string, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("pswpin", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_pswaps_time_span_spike_each_file.pswpin_time_span_spike_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("pswpout", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_pswaps_time_span_spike_each_file.pswpout_time_span_spike_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("pswpin", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_pswaps_time_span_spike_each_file.pswpin_time_span_highest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("pswpout", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_pswaps_time_span_spike_each_file.pswpout_time_span_highest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("pswpin", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_pswaps_time_span_spike_each_file.pswpin_time_span_lowest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("pswpout", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_pswaps_time_span_spike_each_file.pswpout_time_span_lowest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else
        return EXIT_FAILURE;
}

int set_paging_time_span_spike_time_each_file(int x, const char *date_string, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("pgpgin", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_pagings_time_span_spike_each_file.pgpgin_time_span_spike_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("pgpgout", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_pagings_time_span_spike_each_file.pgpgout_time_span_spike_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("fault", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_pagings_time_span_spike_each_file.fault_time_span_spike_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("majflt", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_pagings_time_span_spike_each_file.majflt_time_span_spike_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("vmeff", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_pagings_time_span_spike_each_file.vmeff_time_span_spike_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("pgpgin", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_pagings_time_span_spike_each_file.pgpgin_time_span_highest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("pgpgout", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_pagings_time_span_spike_each_file.pgpgout_time_span_highest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("fault", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_pagings_time_span_spike_each_file.fault_time_span_highest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("majflt", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_pagings_time_span_spike_each_file.majflt_time_span_highest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("vmeff", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_pagings_time_span_spike_each_file.vmeff_time_span_highest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("pgpgin", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_pagings_time_span_spike_each_file.pgpgin_time_span_lowest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("pgpgout", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_pagings_time_span_spike_each_file.pgpgout_time_span_lowest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("fault", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_pagings_time_span_spike_each_file.fault_time_span_lowest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("majflt", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_pagings_time_span_spike_each_file.majflt_time_span_lowest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("vmeff", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_pagings_time_span_spike_each_file.vmeff_time_span_lowest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else
        return EXIT_FAILURE;
}

int set_io_transfer_rate_time_span_spike_time_each_file(int x, const char *date_string, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("tps", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_io_transfer_rates_time_span_spike_each_file.tps_time_span_spike_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("bread", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_io_transfer_rates_time_span_spike_each_file.bread_time_span_spike_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("bwrtn", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_io_transfer_rates_time_span_spike_each_file.bwrtn_time_span_spike_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("tps", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_io_transfer_rates_time_span_spike_each_file.tps_time_span_highest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("bread", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_io_transfer_rates_time_span_spike_each_file.bread_time_span_highest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("bwrtn", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_io_transfer_rates_time_span_spike_each_file.bwrtn_time_span_highest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("tps", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_io_transfer_rates_time_span_spike_each_file.tps_time_span_lowest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("bread", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_io_transfer_rates_time_span_spike_each_file.bread_time_span_lowest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("bwrtn", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_io_transfer_rates_time_span_spike_each_file.bwrtn_time_span_lowest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else
        return EXIT_FAILURE;
}

int set_memory_time_span_spike_time_each_file(int x, const char *date_string, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("memused", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_memories_time_span_spike_each_file.memused_time_span_spike_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("kbcommit", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_memories_time_span_spike_each_file.kbcommit_time_span_spike_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("commit", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_memories_time_span_spike_each_file.commit_time_span_spike_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("memused", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_memories_time_span_spike_each_file.memused_time_span_highest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("kbcommit", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_memories_time_span_spike_each_file.kbcommit_time_span_highest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("commit", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_memories_time_span_spike_each_file.commit_time_span_highest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("memused", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_memories_time_span_spike_each_file.memused_time_span_lowest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("kbcommit", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_memories_time_span_spike_each_file.kbcommit_time_span_lowest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("commit", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_memories_time_span_spike_each_file.commit_time_span_lowest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else
        return EXIT_FAILURE;
}

int set_swpused_time_span_spike_time_each_file(int x, const char *date_string, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        strncpy(sar_analyzer_time_span_spike_obj->date_swaps_time_span_spike_each_file.swpused_time_span_spike_time_each_file[x] , date_string, MAX_DATE_STRINGS);
        return EXIT_SUCCESS;
    } else if (strcmp("highest", analyze_item) == 0) {
        strncpy(sar_analyzer_time_span_spike_obj->date_swaps_time_span_spike_each_file.swpused_time_span_highest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
        return EXIT_SUCCESS;
    } else if (strcmp("lowest", analyze_item) == 0) {
        strncpy(sar_analyzer_time_span_spike_obj->date_swaps_time_span_spike_each_file.swpused_time_span_lowest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_kernel_table_time_span_spike_time_each_file(int x, const char *date_string, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("dentunusd", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_kernel_tables_time_span_spike_each_file.dentunusd_time_span_spike_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("file", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_kernel_tables_time_span_spike_each_file.file_time_span_spike_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("inode", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_kernel_tables_time_span_spike_each_file.inode_time_span_spike_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("dentunusd", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_kernel_tables_time_span_spike_each_file.dentunusd_time_span_highest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("file", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_kernel_tables_time_span_spike_each_file.file_time_span_highest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("inode", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_kernel_tables_time_span_spike_each_file.inode_time_span_highest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("dentunusd", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_kernel_tables_time_span_spike_each_file.dentunusd_time_span_lowest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("file", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_kernel_tables_time_span_spike_each_file.file_time_span_lowest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("inode", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_kernel_tables_time_span_spike_each_file.inode_time_span_lowest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else
        return EXIT_FAILURE;
}

int set_ldavg_time_span_spike_time_each_file(int x, const char *date_string, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("runq_sz", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_ldavgs_time_span_spike_each_file.runq_sz_time_span_spike_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("plist_sz", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_ldavgs_time_span_spike_each_file.plist_sz_time_span_spike_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("ldavg_one", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_ldavgs_time_span_spike_each_file.ldavg_one_time_span_spike_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("ldavg_five", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_ldavgs_time_span_spike_each_file.ldavg_five_time_span_spike_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("ldavg_15", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_ldavgs_time_span_spike_each_file.ldavg_15_time_span_spike_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("runq_sz", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_ldavgs_time_span_spike_each_file.runq_sz_time_span_highest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("plist_sz", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_ldavgs_time_span_spike_each_file.plist_sz_time_span_highest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("ldavg_one", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_ldavgs_time_span_spike_each_file.ldavg_one_time_span_highest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("ldavg_five", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_ldavgs_time_span_spike_each_file.ldavg_five_time_span_highest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("ldavg_15", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_ldavgs_time_span_spike_each_file.ldavg_15_time_span_highest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("runq_sz", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_ldavgs_time_span_spike_each_file.runq_sz_time_span_lowest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("plist_sz", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_ldavgs_time_span_spike_each_file.plist_sz_time_span_lowest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("ldavg_one", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_ldavgs_time_span_spike_each_file.ldavg_one_time_span_lowest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("ldavg_five", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_ldavgs_time_span_spike_each_file.ldavg_five_time_span_lowest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("ldavg_15", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_ldavgs_time_span_spike_each_file.ldavg_15_time_span_lowest_time_each_file[x] , date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else
        return EXIT_FAILURE;
}

int set_block_device_time_span_spike_time_each_file(int x, const char *date_string, int y, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("areqsz", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_block_devices_time_span_spike_each_file.areqsz_time_span_spike_time_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("util", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_block_devices_time_span_spike_each_file.util_time_span_spike_time_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("areqsz", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_block_devices_time_span_spike_each_file.areqsz_time_span_highest_time_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("util", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_block_devices_time_span_spike_each_file.util_time_span_highest_time_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("areqsz", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_block_devices_time_span_spike_each_file.areqsz_time_span_lowest_time_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else if (strcmp("util", element) == 0) {
            strncpy(sar_analyzer_time_span_spike_obj->date_block_devices_time_span_spike_each_file.util_time_span_lowest_time_each_file[x][y], date_string, MAX_DATE_STRINGS);
            return EXIT_SUCCESS;
        } else
            return EXIT_FAILURE;
    } else
        return EXIT_FAILURE;
}

/* -- average highest date -- */
int set_cpu_avg_highest_date(const char *date_string, int x, const char *element)
{
    if (strcmp("usr", element) == 0) {
        strncpy(sar_analyzer_obj->date_cpus_avg_highest.cpu_usr_date[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("sys", element) == 0) {
        strncpy(sar_analyzer_obj->date_cpus_avg_highest.cpu_sys_date[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("iowait", element) == 0) {
        strncpy(sar_analyzer_obj->date_cpus_avg_highest.cpu_iowait_date[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("idle", element) == 0) {
        strncpy(sar_analyzer_obj->date_cpus_avg_highest.cpu_idle_date[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_tasks_avg_highest_date(const char *date_string, const char *element)
{
    if (strcmp("proc", element) == 0) {
        strncpy(sar_analyzer_obj->date_tasks_avg_highest.proc_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("cswch", element) == 0) {
        strncpy(sar_analyzer_obj->date_tasks_avg_highest.cswch_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_pswap_avg_highest_date(const char *date_string, const char *element)
{
    if (strcmp("pswpin", element) == 0) {
        strncpy(sar_analyzer_obj->date_pswaps_avg_highest.pswpin_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("pswpout", element) == 0) {
        strncpy(sar_analyzer_obj->date_pswaps_avg_highest.pswpout_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_paging_avg_highest_date(const char *date_string, const char *element)
{
    if (strcmp("pgpgin", element) == 0) {
        strncpy(sar_analyzer_obj->date_pagings_avg_highest.pgpgin_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("pgpgout", element) == 0) {
        strncpy(sar_analyzer_obj->date_pagings_avg_highest.pgpgout_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("fault", element) == 0) {
        strncpy(sar_analyzer_obj->date_pagings_avg_highest.fault_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("majflt", element) == 0) {
        strncpy(sar_analyzer_obj->date_pagings_avg_highest.majflt_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("vmeff", element) == 0) {
        strncpy(sar_analyzer_obj->date_pagings_avg_highest.vmeff_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_io_transfer_rate_avg_highest_date(const char *date_string, const char *element)
{
    if (strcmp("tps", element) == 0) {
        strncpy(sar_analyzer_obj->date_io_transfer_rates_avg_highest.tps_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("bread", element) == 0) {
        strncpy(sar_analyzer_obj->date_io_transfer_rates_avg_highest.bread_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("bwrtn", element) == 0) {
        strncpy(sar_analyzer_obj->date_io_transfer_rates_avg_highest.bwrtn_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_memory_avg_highest_date(const char *date_string, const char *element)
{
    if (strcmp("memused", element) == 0) {
        strncpy(sar_analyzer_obj->date_memories_avg_highest.memused_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("kbcommit", element) == 0) {
        strncpy(sar_analyzer_obj->date_memories_avg_highest.kbcommit_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("commit", element) == 0) {
        strncpy(sar_analyzer_obj->date_memories_avg_highest.commit_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_swpused_avg_highest_date(const char *date_string)
{
    strncpy(sar_analyzer_obj->date_swaps_avg_highest.swpused_date, date_string, MAX_DATE_STRINGS - 1);
    return EXIT_SUCCESS;
}

int set_kernel_table_avg_highest_date(const char *date_string, const char *element)
{
    if (strcmp("dentunusd", element) == 0) {
        strncpy(sar_analyzer_obj->date_kernel_tables_avg_highest.dentunusd_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("file", element) == 0) {
        strncpy(sar_analyzer_obj->date_kernel_tables_avg_highest.file_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("inode", element) == 0) {
        strncpy(sar_analyzer_obj->date_kernel_tables_avg_highest.inode_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_ldavg_avg_highest_date(const char *date_string, const char *element)
{
    if (strcmp("runq_sz", element) == 0) {
        strncpy(sar_analyzer_obj->date_ldavgs_avg_highest.runq_sz_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("plist_sz", element) == 0) {
        strncpy(sar_analyzer_obj->date_ldavgs_avg_highest.plist_sz_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("ldavg_one", element) == 0) {
        strncpy(sar_analyzer_obj->date_ldavgs_avg_highest.ldavg_one_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("ldavg_five", element) == 0) {
        strncpy(sar_analyzer_obj->date_ldavgs_avg_highest.ldavg_five_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("ldavg_15", element) == 0) {
        strncpy(sar_analyzer_obj->date_ldavgs_avg_highest.ldavg_15_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_block_device_avg_highest_date(const char *date_string, int x, const char *element)
{
    if (strcmp("areqsz", element) == 0) {
        strncpy(sar_analyzer_obj->date_block_devices_avg_highest.areqsz_date[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("util", element) == 0) {
        strncpy(sar_analyzer_obj->date_block_devices_avg_highest.util_date[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_network_avg_highest_date(const char *date_string, int x, const char *element)
{
    if (strcmp("rxpck", element) == 0) {
        strncpy(sar_analyzer_obj->date_networks_avg_highest.rxpck_date[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("txpck", element) == 0) {
        strncpy(sar_analyzer_obj->date_networks_avg_highest.txpck_date[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("rxkb", element) == 0) {
        strncpy(sar_analyzer_obj->date_networks_avg_highest.rxkb_date[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("txkb", element) == 0) {
        strncpy(sar_analyzer_obj->date_networks_avg_highest.txkb_date[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("rxerr", element) == 0) {
        strncpy(sar_analyzer_obj->date_networks_avg_highest.rxerr_date[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("txerr", element) == 0) {
        strncpy(sar_analyzer_obj->date_networks_avg_highest.txerr_date[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("rxdrop", element) == 0) {
        strncpy(sar_analyzer_obj->date_networks_avg_highest.rxdrop_date[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("txdrop", element) == 0) {
        strncpy(sar_analyzer_obj->date_networks_avg_highest.txdrop_date[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

/* -- highest date(for sar_analyzer_all_obj) -- */
int set_cpu_highest_date(const char *date_string, int x, const char *element)
{
    if (strcmp("usr", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_cpus_highest.cpu_usr_date[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("sys", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_cpus_highest.cpu_sys_date[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("iowait", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_cpus_highest.cpu_iowait_date[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("idle", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_cpus_highest.cpu_idle_date[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_tasks_highest_date(const char *date_string, const char *element)
{
    if (strcmp("proc", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_tasks_highest.proc_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("cswch", element) == 0) { 
        strncpy(sar_analyzer_all_obj->date_tasks_highest.cswch_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_pswap_highest_date(const char *date_string, const char *element)
{
    if (strcmp("pswpin", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_pswaps_highest.pswpin_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("pswpout", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_pswaps_highest.pswpout_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_paging_highest_date(const char *date_string, const char *element)
{
    if (strcmp("pgpgin", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_pagings_highest.pgpgin_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("pgpgout", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_pagings_highest.pgpgout_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("fault", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_pagings_highest.fault_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("majflt", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_pagings_highest.majflt_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("vmeff", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_pagings_highest.vmeff_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_io_transfer_rate_highest_date(const char *date_string, const char *element)
{
    if (strcmp("tps", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_io_transfer_rates_highest.tps_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("bread", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_io_transfer_rates_highest.bread_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("bwrtn", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_io_transfer_rates_highest.bwrtn_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_memory_highest_date(const char *date_string, const char *element)
{
    if (strcmp("memused", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_memories_highest.memused_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("kbcommit", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_memories_highest.kbcommit_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("commit", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_memories_highest.commit_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_swpused_highest_date(const char *date_string)
{
    strncpy(sar_analyzer_all_obj->date_swaps_highest.swpused_date, date_string, MAX_DATE_STRINGS - 1);
    return EXIT_SUCCESS;
}

int set_kernel_table_highest_date(const char *date_string, const char *element)
{
    if (strcmp("dentunusd", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_kernel_tables_highest.dentunusd_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("file", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_kernel_tables_highest.file_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("inode", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_kernel_tables_highest.inode_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_ldavg_highest_date(const char *date_string, const char *element)
{
    if (strcmp("runq_sz", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_ldavgs_highest.runq_sz_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("plist_sz", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_ldavgs_highest.plist_sz_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("ldavg_one", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_ldavgs_highest.ldavg_one_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("ldavg_five", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_ldavgs_highest.ldavg_five_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("ldavg_15", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_ldavgs_highest.ldavg_15_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_block_device_highest_date(const char *date_string, int x, const char *element)
{
    if (strcmp("areqsz", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_block_devices_highest.areqsz_date[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("util", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_block_devices_highest.util_date[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_network_highest_date(const char *date_string, int x, const char *element)
{
    if (strcmp("rxpck", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_networks_highest.rxpck_date[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("txpck", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_networks_highest.txpck_date[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("rxkb", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_networks_highest.rxkb_date[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("txkb", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_networks_highest.txkb_date[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("rxerr", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_networks_highest.rxerr_date[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("txerr", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_networks_highest.txerr_date[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("rxdrop", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_networks_highest.rxdrop_date[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("txdrop", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_networks_highest.txdrop_date[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

/* -- highest time(for sar_analyzer_all_obj) -- */
int set_cpu_highest_time(const char *date_string, int x, const char *element)
{
    if (strcmp("usr", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_cpus_highest.cpu_usr_time[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("sys", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_cpus_highest.cpu_sys_time[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("iowait", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_cpus_highest.cpu_iowait_time[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("idle", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_cpus_highest.cpu_idle_time[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_tasks_highest_time(const char *date_string, const char *element)
{
    if (strcmp("proc", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_tasks_highest.proc_time, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("cswch", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_tasks_highest.cswch_time, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_pswap_highest_time(const char *date_string, const char *element)
{
    if (strcmp("pswpin", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_pswaps_highest.pswpin_time, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("pswpout", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_pswaps_highest.pswpout_time, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_paging_highest_time(const char *date_string, const char *element)
{
    if (strcmp("pgpgin", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_pagings_highest.pgpgin_time, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("pgpgout", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_pagings_highest.pgpgout_time, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("fault", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_pagings_highest.fault_time, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("majflt", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_pagings_highest.majflt_time, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("vmeff", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_pagings_highest.vmeff_time, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_io_transfer_rate_highest_time(const char *date_string, const char *element)
{
    if (strcmp("tps", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_io_transfer_rates_highest.tps_time, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("bread", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_io_transfer_rates_highest.bread_time, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("bwrtn", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_io_transfer_rates_highest.bwrtn_time, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_memory_highest_time(const char *date_string, const char *element)
{
    if (strcmp("memused", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_memories_highest.memused_time, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("kbcommit", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_memories_highest.kbcommit_time, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("commit", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_memories_highest.commit_time, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_swpused_highest_time(const char *date_string)
{
    strncpy(sar_analyzer_all_obj->date_swaps_highest.swpused_time, date_string, MAX_DATE_STRINGS - 1);
    return EXIT_SUCCESS;
}

int set_kernel_table_highest_time(const char *date_string, const char *element)
{
    if (strcmp("dentunusd", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_kernel_tables_highest.dentunusd_time, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("file", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_kernel_tables_highest.file_time, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("inode", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_kernel_tables_highest.inode_time, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_ldavg_highest_time(const char *date_string, const char *element)
{
    if (strcmp("runq_sz", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_ldavgs_highest.runq_sz_time, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("plist_sz", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_ldavgs_highest.plist_sz_time, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("ldavg_one", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_ldavgs_highest.ldavg_one_time, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("ldavg_five", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_ldavgs_highest.ldavg_five_time, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("ldavg_15", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_ldavgs_highest.ldavg_15_time, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_block_device_highest_time(const char *date_string, int x, const char *element)
{
    if (strcmp("areqsz", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_block_devices_highest.areqsz_time[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("util", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_block_devices_highest.util_time[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_network_highest_time(const char *date_string, int x, const char *element)
{
    if (strcmp("rxpck", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_networks_highest.rxpck_time[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("txpck", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_networks_highest.txpck_time[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("rxkb", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_networks_highest.rxkb_time[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("txkb", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_networks_highest.txkb_time[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("rxerr", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_networks_highest.rxerr_time[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("txerr", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_networks_highest.txerr_time[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("rxdrop", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_networks_highest.rxdrop_time[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("txdrop", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_networks_highest.txdrop_time[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

/* -- average lowest date -- */
int set_cpu_avg_lowest_date(const char *date_string, int x, const char *element)
{
    if (strcmp("usr", element) == 0) {
        strncpy(sar_analyzer_obj->date_cpus_avg_lowest.cpu_usr_date[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("sys", element) == 0) {
        strncpy(sar_analyzer_obj->date_cpus_avg_lowest.cpu_sys_date[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("iowait", element) == 0) {
        strncpy(sar_analyzer_obj->date_cpus_avg_lowest.cpu_iowait_date[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("idle", element) == 0) {
        strncpy(sar_analyzer_obj->date_cpus_avg_lowest.cpu_idle_date[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_tasks_avg_lowest_date(const char *date_string, const char *element)
{
    if (strcmp("proc", element) == 0) {
        strncpy(sar_analyzer_obj->date_tasks_avg_lowest.proc_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("cswch", element) == 0) {
        strncpy(sar_analyzer_obj->date_tasks_avg_lowest.cswch_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_pswap_avg_lowest_date(const char *date_string, const char *element)
{
    if (strcmp("pswpin", element) == 0) {
        strncpy(sar_analyzer_obj->date_pswaps_avg_lowest.pswpin_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("pswpout", element) == 0) {
        strncpy(sar_analyzer_obj->date_pswaps_avg_lowest.pswpout_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_paging_avg_lowest_date(const char *date_string, const char *element)
{
    if (strcmp("pgpgin", element) == 0) {
        strncpy(sar_analyzer_obj->date_pagings_avg_lowest.pgpgin_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("pgpgout", element) == 0) {
        strncpy(sar_analyzer_obj->date_pagings_avg_lowest.pgpgout_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("fault", element) == 0) {
        strncpy(sar_analyzer_obj->date_pagings_avg_lowest.fault_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("majflt", element) == 0) {
        strncpy(sar_analyzer_obj->date_pagings_avg_lowest.majflt_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("vmeff", element) == 0) {
        strncpy(sar_analyzer_obj->date_pagings_avg_lowest.vmeff_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_io_transfer_rate_avg_lowest_date(const char *date_string, const char *element)
{
    if (strcmp("tps", element) == 0) {
        strncpy(sar_analyzer_obj->date_io_transfer_rates_avg_lowest.tps_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("bread", element) == 0) {
        strncpy(sar_analyzer_obj->date_io_transfer_rates_avg_lowest.bread_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("bwrtn", element) == 0) {
        strncpy(sar_analyzer_obj->date_io_transfer_rates_avg_lowest.bwrtn_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_memory_avg_lowest_date(const char *date_string, const char *element)
{
    if (strcmp("memused", element) == 0) {
        strncpy(sar_analyzer_obj->date_memories_avg_lowest.memused_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("kbcommit", element) == 0) {
        strncpy(sar_analyzer_obj->date_memories_avg_lowest.kbcommit_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("commit", element) == 0) {
        strncpy(sar_analyzer_obj->date_memories_avg_lowest.commit_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_swpused_avg_lowest_date(const char *date_string)
{
    strncpy(sar_analyzer_obj->date_swaps_avg_lowest.swpused_date, date_string, MAX_DATE_STRINGS - 1);
    return EXIT_SUCCESS;
}

int set_kernel_table_avg_lowest_date(const char *date_string, const char *element)
{
    if (strcmp("dentunusd", element) == 0) {
        strncpy(sar_analyzer_obj->date_kernel_tables_avg_lowest.dentunusd_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("file", element) == 0) {
        strncpy(sar_analyzer_obj->date_kernel_tables_avg_lowest.file_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("inode", element) == 0) {
        strncpy(sar_analyzer_obj->date_kernel_tables_avg_lowest.inode_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_ldavg_avg_lowest_date(const char *date_string, const char *element)
{
    if (strcmp("runq_sz", element) == 0) {
        strncpy(sar_analyzer_obj->date_ldavgs_avg_lowest.runq_sz_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("plist_sz", element) == 0) {
        strncpy(sar_analyzer_obj->date_ldavgs_avg_lowest.plist_sz_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("ldavg_one", element) == 0) {
        strncpy(sar_analyzer_obj->date_ldavgs_avg_lowest.ldavg_one_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("ldavg_five", element) == 0) {
        strncpy(sar_analyzer_obj->date_ldavgs_avg_lowest.ldavg_five_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("ldavg_15", element) == 0) {
        strncpy(sar_analyzer_obj->date_ldavgs_avg_lowest.ldavg_15_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_block_device_avg_lowest_date(const char *date_string, int x, const char *element)
{
    if (strcmp("areqsz", element) == 0) {
        strncpy(sar_analyzer_obj->date_block_devices_avg_lowest.areqsz_date[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("util", element) == 0) {
        strncpy(sar_analyzer_obj->date_block_devices_avg_lowest.util_date[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_network_avg_lowest_date(const char *date_string, int x, const char *element)
{
    if (strcmp("rxpck", element) == 0)
    {
        strncpy(sar_analyzer_obj->date_networks_avg_lowest.rxpck_date[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("txpck", element) == 0)
    {
        strncpy(sar_analyzer_obj->date_networks_avg_lowest.txpck_date[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("rxkb", element) == 0)
    {
        strncpy(sar_analyzer_obj->date_networks_avg_lowest.rxkb_date[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("txkb", element) == 0)
    {
        strncpy(sar_analyzer_obj->date_networks_avg_lowest.txkb_date[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("rxerr", element) == 0)
    {
        strncpy(sar_analyzer_obj->date_networks_avg_lowest.rxerr_date[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("txerr", element) == 0)
    {
        strncpy(sar_analyzer_obj->date_networks_avg_lowest.txerr_date[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("rxdrop", element) == 0)
    {
        strncpy(sar_analyzer_obj->date_networks_avg_lowest.rxdrop_date[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("txdrop", element) == 0)
    {
        strncpy(sar_analyzer_obj->date_networks_avg_lowest.txdrop_date[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

/* -- lowest date(for sar_analyzer_all_obj) -- */
int set_cpu_lowest_date(const char *date_string, int x, const char *element)
{
    if (strcmp("usr", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_cpus_lowest.cpu_usr_date[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("sys", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_cpus_lowest.cpu_sys_date[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("iowait", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_cpus_lowest.cpu_iowait_date[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("idle", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_cpus_lowest.cpu_idle_date[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_tasks_lowest_date(const char *date_string, const char *element)
{
    if (strcmp("proc", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_tasks_lowest.proc_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("cswch", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_tasks_lowest.cswch_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_pswap_lowest_date(const char *date_string, const char *element)
{
    if (strcmp("pswpin", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_pswaps_lowest.pswpin_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("pswpout", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_pswaps_lowest.pswpout_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_paging_lowest_date(const char *date_string, const char *element)
{
    if (strcmp("pgpgin", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_pagings_lowest.pgpgin_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("pgpgout", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_pagings_lowest.pgpgout_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("fault", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_pagings_lowest.fault_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("majflt", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_pagings_lowest.majflt_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("vmeff", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_pagings_lowest.vmeff_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_io_transfer_rate_lowest_date(const char *date_string, const char *element)
{
    if (strcmp("tps", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_io_transfer_rates_lowest.tps_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("bread", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_io_transfer_rates_lowest.bread_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("bwrtn", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_io_transfer_rates_lowest.bwrtn_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_memory_lowest_date(const char *date_string, const char *element)
{
    if (strcmp("memused", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_memories_lowest.memused_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("kbcommit", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_memories_lowest.kbcommit_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("commit", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_memories_lowest.commit_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_swpused_lowest_date(const char *date_string)
{
    strncpy(sar_analyzer_all_obj->date_swaps_lowest.swpused_date, date_string, MAX_DATE_STRINGS - 1);
    return EXIT_SUCCESS;
}

int set_kernel_table_lowest_date(const char *date_string, const char *element)
{
    if (strcmp("dentunusd", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_kernel_tables_lowest.dentunusd_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("file", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_kernel_tables_lowest.file_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("inode", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_kernel_tables_lowest.inode_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_ldavg_lowest_date(const char *date_string, const char *element)
{
    if (strcmp("runq_sz", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_ldavgs_lowest.runq_sz_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("plist_sz", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_ldavgs_lowest.plist_sz_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("ldavg_one", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_ldavgs_lowest.ldavg_one_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("ldavg_five", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_ldavgs_lowest.ldavg_five_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("ldavg_15", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_ldavgs_lowest.ldavg_15_date, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_block_device_lowest_date(const char *date_string, int x, const char *element)
{
    if (strcmp("areqsz", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_block_devices_lowest.areqsz_date[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("util", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_block_devices_lowest.util_date[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_network_lowest_date(const char *date_string, int x, const char *element)
{
    if (strcmp("rxpck", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_networks_lowest.rxpck_date[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("txpck", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_networks_lowest.txpck_date[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("rxkb", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_networks_lowest.rxkb_date[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("txkb", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_networks_lowest.txkb_date[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("rxerr", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_networks_lowest.rxerr_date[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("txerr", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_networks_lowest.txerr_date[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("rxdrop", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_networks_lowest.rxdrop_date[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("txdrop", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_networks_lowest.txdrop_date[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

/* -- lowest time(for sar_analyzer_all_obj) -- */
int set_cpu_lowest_time(const char *date_string, int x, const char *element)
{
    if (strcmp("usr", element) == 0)
    {
        strncpy(sar_analyzer_all_obj->date_cpus_lowest.cpu_usr_time[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("sys", element) == 0)
    {
        strncpy(sar_analyzer_all_obj->date_cpus_lowest.cpu_sys_time[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("iowait", element) == 0)
    {
        strncpy(sar_analyzer_all_obj->date_cpus_lowest.cpu_iowait_time[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("idle", element) == 0)
    {
        strncpy(sar_analyzer_all_obj->date_cpus_lowest.cpu_idle_time[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_tasks_lowest_time(const char *date_string, const char *element)
{
    if (strcmp("proc", element) == 0)
    {
        strncpy(sar_analyzer_all_obj->date_tasks_lowest.proc_time, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("cswch", element) == 0)
    {
        strncpy(sar_analyzer_all_obj->date_tasks_lowest.cswch_time, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_pswap_lowest_time(const char *date_string, const char *element)
{
    if (strcmp("pswpin", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_pswaps_lowest.pswpin_time, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("pswpout", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_pswaps_lowest.pswpout_time, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_paging_lowest_time(const char *date_string, const char *element)
{
    if (strcmp("pgpgin", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_pagings_lowest.pgpgin_time, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("pgpgout", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_pagings_lowest.pgpgout_time, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("fault", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_pagings_lowest.fault_time, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("majflt", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_pagings_lowest.majflt_time, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("vmeff", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_pagings_lowest.vmeff_time, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_io_transfer_rate_lowest_time(const char *date_string, const char *element)
{
    if (strcmp("tps", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_io_transfer_rates_lowest.tps_time, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("bread", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_io_transfer_rates_lowest.bread_time, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("bwrtn", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_io_transfer_rates_lowest.bwrtn_time, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_memory_lowest_time(const char *date_string, const char *element)
{
    if (strcmp("memused", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_memories_lowest.memused_time, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("kbcommit", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_memories_lowest.kbcommit_time, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("commit", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_memories_lowest.commit_time, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_swpused_lowest_time(const char *date_string)
{
    strncpy(sar_analyzer_all_obj->date_swaps_lowest.swpused_time, date_string, MAX_DATE_STRINGS - 1);
    return EXIT_SUCCESS;
}

int set_kernel_table_lowest_time(const char *date_string, const char *element)
{
    if (strcmp("dentunusd", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_kernel_tables_lowest.dentunusd_time, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("file", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_kernel_tables_lowest.file_time, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("inode", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_kernel_tables_lowest.inode_time, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_ldavg_lowest_time(const char *date_string, const char *element)
{
    if (strcmp("runq_sz", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_ldavgs_lowest.runq_sz_time, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("plist_sz", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_ldavgs_lowest.plist_sz_time, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("ldavg_one", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_ldavgs_lowest.ldavg_one_time, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("ldavg_five", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_ldavgs_lowest.ldavg_five_time, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("ldavg_15", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_ldavgs_lowest.ldavg_15_time, date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_block_device_lowest_time(const char *date_string, int x, const char *element)
{
    if (strcmp("areqsz", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_block_devices_lowest.areqsz_time[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("util", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_block_devices_lowest.util_time[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_network_lowest_time(const char *date_string, int x, const char *element)
{
    if (strcmp("rxpck", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_networks_lowest.rxpck_time[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("txpck", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_networks_lowest.txpck_time[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("rxkb", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_networks_lowest.rxkb_time[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("txkb", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_networks_lowest.txkb_time[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("rxerr", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_networks_lowest.rxerr_time[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("txerr", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_networks_lowest.txerr_time[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("rxdrop", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_networks_lowest.rxdrop_time[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else if (strcmp("txdrop", element) == 0) {
        strncpy(sar_analyzer_all_obj->date_networks_lowest.txdrop_time[x], date_string, MAX_DATE_STRINGS - 1);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

/* -------- end Dates -------- */

/* -------- getters -------- */

const char *get_this_date(void)
{
    return sar_analyzer_obj->this_date;
}

const char *get_this_date_all(void)
{
    return sar_analyzer_all_obj->this_date;
}

const char *get_this_date_former(void)
{
    return sar_analyzer_obj->this_date_former;
}

const char *get_this_date_all_former(void)
{
    return sar_analyzer_all_obj->this_date_former;
}

const char *get_this_time(void)
{
    return sar_analyzer_obj->this_time;
}

const char *get_this_time_all(void)
{
    return sar_analyzer_all_obj->this_time;
}

const char *get_this_time_former(void)
{
    return sar_analyzer_obj->this_time_former;
}

const char *get_this_time_all_former(void)
{
    return sar_analyzer_all_obj->this_time_former;
}

/* -------- Columns -------- */
int get_column_cpu(const char *element)
{
    if (strcmp("CPU", element) == 0)
        return sar_analyzer_obj->column_cpus.CPU;
    else if (strcmp("usr", element) == 0)
        return sar_analyzer_obj->column_cpus.cpu_usr;
    else if (strcmp("sys", element) == 0)
        return sar_analyzer_obj->column_cpus.cpu_sys;
    else if (strcmp("iowait", element) == 0)
        return sar_analyzer_obj->column_cpus.cpu_iowait;
    else if (strcmp("idle", element) == 0)
        return sar_analyzer_obj->column_cpus.cpu_idle;
    else
        return EXIT_FAILURE;
}

int get_column_tasks(const char *element)
{
    if (strcmp("proc", element) == 0)
        return sar_analyzer_obj->column_tasks.proc;
    else if (strcmp("cswch", element) == 0)
        return sar_analyzer_obj->column_tasks.cswch;
    else
        return EXIT_FAILURE;
}

int get_column_pswap(const char *element)
{
    if (strcmp("pswpin", element) == 0)
        return sar_analyzer_obj->column_pswaps.pswpin;
    else if (strcmp("pswpout", element) == 0)
        return sar_analyzer_obj->column_pswaps.pswpout;
    else
        return EXIT_FAILURE;
}

int get_column_paging(const char *element)
{
    if (strcmp("pgpgin", element) == 0)
        return sar_analyzer_obj->column_pagings.pgpgin;
    else if (strcmp("pgpgout", element) == 0)
        return sar_analyzer_obj->column_pagings.pgpgout;
    else if (strcmp("fault", element) == 0)
        return sar_analyzer_obj->column_pagings.fault;
    else if (strcmp("majflt", element) == 0)
        return sar_analyzer_obj->column_pagings.majflt;
    else if (strcmp("vmeff", element) == 0)
        return sar_analyzer_obj->column_pagings.vmeff;
    else
        return EXIT_FAILURE;
}

int get_column_io_transfer_rate(const char *element)
{
    if (strcmp("tps", element) == 0)
        return sar_analyzer_obj->column_io_transfer_rates.tps;
    else if (strcmp("bread", element) == 0)
        return sar_analyzer_obj->column_io_transfer_rates.bread;
    else if (strcmp("bwrtn", element) == 0)
        return sar_analyzer_obj->column_io_transfer_rates.bwrtn;
    else
        return EXIT_FAILURE;
}

int get_column_memory(const char *element)
{
    if (strcmp("memused", element) == 0)
        return sar_analyzer_obj->column_memories.memused;
    else if (strcmp("kbcommit", element) == 0)
        return sar_analyzer_obj->column_memories.kbcommit;
    else if (strcmp("commit", element) == 0)
        return sar_analyzer_obj->column_memories.commit;
    else
        return EXIT_FAILURE;
}

int get_column_swpused(void)
{
    return sar_analyzer_obj->column_swaps.swpused;
}

int get_column_kernel_table(const char *element)
{
    if (strcmp("dentunusd", element) == 0)
        return sar_analyzer_obj->column_kernel_tables.dentunusd;
    else if (strcmp("file", element) == 0)
        return sar_analyzer_obj->column_kernel_tables.file;
    else if (strcmp("inode", element) == 0)
        return sar_analyzer_obj->column_kernel_tables.inode;
    else
        return EXIT_FAILURE;
}

int get_column_ldavg(const char *element)
{
    if (strcmp("runq_sz", element) == 0)
        return sar_analyzer_obj->column_ldavgs.runq_sz;
    else if (strcmp("plist_sz", element) == 0)
        return sar_analyzer_obj->column_ldavgs.plist_sz;
    else if (strcmp("ldavg_one", element) == 0)
        return sar_analyzer_obj->column_ldavgs.ldavg_one;
    else if (strcmp("ldavg_five", element) == 0)
        return sar_analyzer_obj->column_ldavgs.ldavg_five;
    else if (strcmp("ldavg_15", element) == 0)
        return sar_analyzer_obj->column_ldavgs.ldavg_15;
    else
        return EXIT_FAILURE;
}

int get_column_block_device(const char *element)
{
    if (strcmp("areqsz", element) == 0)
        return sar_analyzer_obj->column_block_devices.areqsz;
    else if (strcmp("util", element) == 0)
        return sar_analyzer_obj->column_block_devices.util;
    else
        return EXIT_FAILURE;
}

int get_column_network(const char *element)
{
    if (strcmp("rxpck", element) == 0)
        return sar_analyzer_obj->column_networks.rxpck;
    else if (strcmp("txpck", element) == 0)
        return sar_analyzer_obj->column_networks.txpck;
    else if (strcmp("rxkb", element) == 0)
        return sar_analyzer_obj->column_networks.rxkb;
    else if (strcmp("txkb", element) == 0)
        return sar_analyzer_obj->column_networks.txkb;
    else if (strcmp("rxerr", element) == 0)
        return sar_analyzer_obj->column_networks.rxerr;
    else if (strcmp("txerr", element) == 0)
        return sar_analyzer_obj->column_networks.txerr;
    else if (strcmp("rxdrop", element) == 0)
        return sar_analyzer_obj->column_networks.rxdrop;
    else if (strcmp("txdrop", element) == 0)
        return sar_analyzer_obj->column_networks.txdrop;
    else
        return EXIT_FAILURE;
}
/* -------- end Columns -------- */

/* -------- Data -------- */

/* -- spike val each file -- */

double get_cpu_spike_val_each_file(int x, int y, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("usr", element) == 0)
            return sar_analyzer_spike_obj->cpus_spike_each_file.cpu_usr_spike_val_each_file[x][y];
        else if (strcmp("sys", element) == 0)
            return sar_analyzer_spike_obj->cpus_spike_each_file.cpu_sys_spike_val_each_file[x][y];
        else if (strcmp("iowait", element) == 0)
            return sar_analyzer_spike_obj->cpus_spike_each_file.cpu_iowait_spike_val_each_file[x][y];
        else if (strcmp("idle", element) == 0)
            return sar_analyzer_spike_obj->cpus_spike_each_file.cpu_idle_spike_val_each_file[x][y];
        else
            return EXIT_FAILURE;
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("usr", element) == 0)
            return sar_analyzer_spike_obj->cpus_spike_each_file.cpu_usr_highest_val_each_file[x][y];
        else if (strcmp("sys", element) == 0)
            return sar_analyzer_spike_obj->cpus_spike_each_file.cpu_sys_highest_val_each_file[x][y];
        else if (strcmp("iowait", element) == 0)
            return sar_analyzer_spike_obj->cpus_spike_each_file.cpu_iowait_highest_val_each_file[x][y];
        else if (strcmp("idle", element) == 0)
            return sar_analyzer_spike_obj->cpus_spike_each_file.cpu_idle_highest_val_each_file[x][y];
        else
            return EXIT_FAILURE;
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("usr", element) == 0)
            return sar_analyzer_spike_obj->cpus_spike_each_file.cpu_usr_lowest_val_each_file[x][y];
        else if (strcmp("sys", element) == 0)
            return sar_analyzer_spike_obj->cpus_spike_each_file.cpu_sys_lowest_val_each_file[x][y];
        else if (strcmp("iowait", element) == 0)
            return sar_analyzer_spike_obj->cpus_spike_each_file.cpu_iowait_lowest_val_each_file[x][y];
        else if (strcmp("idle", element) == 0)
            return sar_analyzer_spike_obj->cpus_spike_each_file.cpu_idle_lowest_val_each_file[x][y];
        else
            return EXIT_FAILURE;
    } else
        return EXIT_FAILURE;
}

double get_tasks_spike_val_each_file(int x, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("proc", element) == 0)
            return sar_analyzer_spike_obj->tasks_spike_each_file.proc_spike_val_each_file[x];
        else if (strcmp("cswch", element) == 0)
            return sar_analyzer_spike_obj->tasks_spike_each_file.cswch_spike_val_each_file[x];
        else
            return EXIT_FAILURE;
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("proc", element) == 0)
            return sar_analyzer_spike_obj->tasks_spike_each_file.proc_highest_val_each_file[x];
        else if (strcmp("cswch", element) == 0)
            return sar_analyzer_spike_obj->tasks_spike_each_file.cswch_highest_val_each_file[x];
        else
            return EXIT_FAILURE;
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("proc", element) == 0)
            return sar_analyzer_spike_obj->tasks_spike_each_file.proc_lowest_val_each_file[x];
        else if (strcmp("cswch", element) == 0)
            return sar_analyzer_spike_obj->tasks_spike_each_file.cswch_lowest_val_each_file[x];
        else
            return EXIT_FAILURE;
    } else
        return EXIT_FAILURE;
}

double get_pswap_spike_val_each_file(int x, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("pswpin", element) == 0)
            return sar_analyzer_spike_obj->pswaps_spike_each_file.pswpin_spike_val_each_file[x];
        else if (strcmp("pswpout", element) == 0)
            return sar_analyzer_spike_obj->pswaps_spike_each_file.pswpout_spike_val_each_file[x];
        else
            return EXIT_FAILURE;
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("pswpin", element) == 0)
            return sar_analyzer_spike_obj->pswaps_spike_each_file.pswpin_highest_val_each_file[x];
        else if (strcmp("pswpout", element) == 0)
            return sar_analyzer_spike_obj->pswaps_spike_each_file.pswpout_highest_val_each_file[x];
        else
            return EXIT_FAILURE;
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("pswpin", element) == 0)
            return sar_analyzer_spike_obj->pswaps_spike_each_file.pswpin_lowest_val_each_file[x];
        else if (strcmp("pswpout", element) == 0)
            return sar_analyzer_spike_obj->pswaps_spike_each_file.pswpout_lowest_val_each_file[x];
        else
            return EXIT_FAILURE;
    } else
        return EXIT_FAILURE;
}

double get_paging_spike_val_each_file(int x, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("pgpgin", element) == 0)
            return sar_analyzer_spike_obj->pagings_spike_each_file.pgpgin_spike_val_each_file[x];
        else if (strcmp("pgpgout", element) == 0)
            return sar_analyzer_spike_obj->pagings_spike_each_file.pgpgout_spike_val_each_file[x];
        else if (strcmp("fault", element) == 0)
            return sar_analyzer_spike_obj->pagings_spike_each_file.fault_spike_val_each_file[x];
        else if (strcmp("majflt", element) == 0)
            return sar_analyzer_spike_obj->pagings_spike_each_file.majflt_spike_val_each_file[x];
        else if (strcmp("vmeff", element) == 0)
            return sar_analyzer_spike_obj->pagings_spike_each_file.vmeff_spike_val_each_file[x];
        else
            return EXIT_FAILURE;
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("pgpgin", element) == 0)
            return sar_analyzer_spike_obj->pagings_spike_each_file.pgpgin_highest_val_each_file[x];
        else if (strcmp("pgpgout", element) == 0)
            return sar_analyzer_spike_obj->pagings_spike_each_file.pgpgout_highest_val_each_file[x];
        else if (strcmp("fault", element) == 0)
            return sar_analyzer_spike_obj->pagings_spike_each_file.fault_highest_val_each_file[x];
        else if (strcmp("majflt", element) == 0)
            return sar_analyzer_spike_obj->pagings_spike_each_file.majflt_highest_val_each_file[x];
        else if (strcmp("vmeff", element) == 0)
            return sar_analyzer_spike_obj->pagings_spike_each_file.vmeff_highest_val_each_file[x];
        else
            return EXIT_FAILURE;
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("pgpgin", element) == 0)
            return sar_analyzer_spike_obj->pagings_spike_each_file.pgpgin_lowest_val_each_file[x];
        else if (strcmp("pgpgout", element) == 0)
            return sar_analyzer_spike_obj->pagings_spike_each_file.pgpgout_lowest_val_each_file[x];
        else if (strcmp("fault", element) == 0)
            return sar_analyzer_spike_obj->pagings_spike_each_file.fault_lowest_val_each_file[x];
        else if (strcmp("majflt", element) == 0)
            return sar_analyzer_spike_obj->pagings_spike_each_file.majflt_lowest_val_each_file[x];
        else if (strcmp("vmeff", element) == 0)
            return sar_analyzer_spike_obj->pagings_spike_each_file.vmeff_lowest_val_each_file[x];
        else
            return EXIT_FAILURE;
    } else
        return EXIT_FAILURE;
}

double get_io_transfer_rate_spike_val_each_file(int x, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("tps", element) == 0)
            return sar_analyzer_spike_obj->io_transfer_rates_spike_each_file.tps_spike_val_each_file[x];
        else if (strcmp("bread", element) == 0)
            return sar_analyzer_spike_obj->io_transfer_rates_spike_each_file.bread_spike_val_each_file[x];
        else if (strcmp("bwrtn", element) == 0)
            return sar_analyzer_spike_obj->io_transfer_rates_spike_each_file.bwrtn_spike_val_each_file[x];
        else
            return EXIT_FAILURE;
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("tps", element) == 0)
            return sar_analyzer_spike_obj->io_transfer_rates_spike_each_file.tps_highest_val_each_file[x];
        else if (strcmp("bread", element) == 0)
            return sar_analyzer_spike_obj->io_transfer_rates_spike_each_file.bread_highest_val_each_file[x];
        else if (strcmp("bwrtn", element) == 0)
            return sar_analyzer_spike_obj->io_transfer_rates_spike_each_file.bwrtn_highest_val_each_file[x];
        else
            return EXIT_FAILURE;
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("tps", element) == 0)
            return sar_analyzer_spike_obj->io_transfer_rates_spike_each_file.tps_lowest_val_each_file[x];
        else if (strcmp("bread", element) == 0)
            return sar_analyzer_spike_obj->io_transfer_rates_spike_each_file.bread_lowest_val_each_file[x];
        else if (strcmp("bwrtn", element) == 0)
            return sar_analyzer_spike_obj->io_transfer_rates_spike_each_file.bwrtn_lowest_val_each_file[x];
        else
            return EXIT_FAILURE;
    } else
        return EXIT_FAILURE;
}

double get_memory_spike_val_each_file(int x, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("memused", element) == 0)
            return sar_analyzer_spike_obj->memories_spike_each_file.memused_spike_val_each_file[x];
        else if (strcmp("kbcommit", element) == 0)
            return sar_analyzer_spike_obj->memories_spike_each_file.kbcommit_spike_val_each_file[x];
        else if (strcmp("commit", element) == 0)
            return sar_analyzer_spike_obj->memories_spike_each_file.commit_spike_val_each_file[x];
        else
            return EXIT_FAILURE;
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("memused", element) == 0)
            return sar_analyzer_spike_obj->memories_spike_each_file.memused_highest_val_each_file[x];
        else if (strcmp("kbcommit", element) == 0)
            return sar_analyzer_spike_obj->memories_spike_each_file.kbcommit_highest_val_each_file[x];
        else if (strcmp("commit", element) == 0)
            return sar_analyzer_spike_obj->memories_spike_each_file.commit_highest_val_each_file[x];
        else
            return EXIT_FAILURE;
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("memused", element) == 0)
            return sar_analyzer_spike_obj->memories_spike_each_file.memused_lowest_val_each_file[x];
        else if (strcmp("kbcommit", element) == 0)
            return sar_analyzer_spike_obj->memories_spike_each_file.kbcommit_lowest_val_each_file[x];
        else if (strcmp("commit", element) == 0)
            return sar_analyzer_spike_obj->memories_spike_each_file.commit_lowest_val_each_file[x];
        else
            return EXIT_FAILURE;
    } else
        return EXIT_FAILURE;
}

double get_swpused_spike_val_each_file(int x, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0)
        return sar_analyzer_spike_obj->swaps_spike_each_file.swpused_spike_val_each_file[x];
    else if (strcmp("highest", analyze_item) == 0)
        return sar_analyzer_spike_obj->swaps_spike_each_file.swpused_highest_val_each_file[x];
    else if (strcmp("lowest", analyze_item) == 0)
        return sar_analyzer_spike_obj->swaps_spike_each_file.swpused_lowest_val_each_file[x];
    else
        return EXIT_FAILURE;
}

int get_kernel_table_spike_val_each_file(int x, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("dentunusd", element) == 0)
            return sar_analyzer_spike_obj->kernel_tables_spike_each_file.dentunusd_spike_val_each_file[x];
        else if (strcmp("file", element) == 0)
            return sar_analyzer_spike_obj->kernel_tables_spike_each_file.file_spike_val_each_file[x];
        else if (strcmp("inode", element) == 0)
            return sar_analyzer_spike_obj->kernel_tables_spike_each_file.inode_spike_val_each_file[x];
        else
            return EXIT_FAILURE;
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("dentunusd", element) == 0)
            return sar_analyzer_spike_obj->kernel_tables_spike_each_file.dentunusd_highest_val_each_file[x];
        else if (strcmp("file", element) == 0)
            return sar_analyzer_spike_obj->kernel_tables_spike_each_file.file_highest_val_each_file[x];
        else if (strcmp("inode", element) == 0)
            return sar_analyzer_spike_obj->kernel_tables_spike_each_file.inode_highest_val_each_file[x];
        else
            return EXIT_FAILURE;
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("dentunusd", element) == 0)
            return sar_analyzer_spike_obj->kernel_tables_spike_each_file.dentunusd_lowest_val_each_file[x];
        else if (strcmp("file", element) == 0)
            return sar_analyzer_spike_obj->kernel_tables_spike_each_file.file_lowest_val_each_file[x];
        else if (strcmp("inode", element) == 0)
            return sar_analyzer_spike_obj->kernel_tables_spike_each_file.inode_lowest_val_each_file[x];
        else
            return EXIT_FAILURE;
    } else
        return EXIT_FAILURE;
}

double get_ldavg_spike_val_each_file(int x, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("runq_sz", element) == 0)
            return sar_analyzer_spike_obj->ldavgs_spike_each_file.runq_sz_spike_val_each_file[x];
        else if (strcmp("plist_sz", element) == 0)
            return sar_analyzer_spike_obj->ldavgs_spike_each_file.plist_sz_spike_val_each_file[x];
        else if (strcmp("ldavg_one", element) == 0)
            return sar_analyzer_spike_obj->ldavgs_spike_each_file.ldavg_one_spike_val_each_file[x];
        else if (strcmp("ldavg_five", element) == 0)
            return sar_analyzer_spike_obj->ldavgs_spike_each_file.ldavg_five_spike_val_each_file[x];
        else if (strcmp("ldavg_15", element) == 0)
            return sar_analyzer_spike_obj->ldavgs_spike_each_file.ldavg_15_spike_val_each_file[x];
        else
            return EXIT_FAILURE;
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("runq_sz", element) == 0)
            return sar_analyzer_spike_obj->ldavgs_spike_each_file.runq_sz_highest_val_each_file[x];
        else if (strcmp("plist_sz", element) == 0)
            return sar_analyzer_spike_obj->ldavgs_spike_each_file.plist_sz_highest_val_each_file[x];
        else if (strcmp("ldavg_one", element) == 0)
            return sar_analyzer_spike_obj->ldavgs_spike_each_file.ldavg_one_highest_val_each_file[x];
        else if (strcmp("ldavg_five", element) == 0)
            return sar_analyzer_spike_obj->ldavgs_spike_each_file.ldavg_five_highest_val_each_file[x];
        else if (strcmp("ldavg_15", element) == 0)
            return sar_analyzer_spike_obj->ldavgs_spike_each_file.ldavg_15_highest_val_each_file[x];
        else
            return EXIT_FAILURE;
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("runq_sz", element) == 0)
            return sar_analyzer_spike_obj->ldavgs_spike_each_file.runq_sz_lowest_val_each_file[x];
        else if (strcmp("plist_sz", element) == 0)
            return sar_analyzer_spike_obj->ldavgs_spike_each_file.plist_sz_lowest_val_each_file[x];
        else if (strcmp("ldavg_one", element) == 0)
            return sar_analyzer_spike_obj->ldavgs_spike_each_file.ldavg_one_lowest_val_each_file[x];
        else if (strcmp("ldavg_five", element) == 0)
            return sar_analyzer_spike_obj->ldavgs_spike_each_file.ldavg_five_lowest_val_each_file[x];
        else if (strcmp("ldavg_15", element) == 0)
            return sar_analyzer_spike_obj->ldavgs_spike_each_file.ldavg_15_lowest_val_each_file[x];
        else
            return EXIT_FAILURE;
    } else
        return EXIT_FAILURE;
}

double get_block_device_spike_val_each_file(int x, int y, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("areqsz", element) == 0)
            return sar_analyzer_spike_obj->block_devices_spike_each_file.areqsz_spike_val_each_file[x][y];
        else if (strcmp("util", element) == 0)
            return sar_analyzer_spike_obj->block_devices_spike_each_file.util_spike_val_each_file[x][y];
        else
            return EXIT_FAILURE;
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("areqsz", element) == 0)
            return sar_analyzer_spike_obj->block_devices_spike_each_file.areqsz_highest_val_each_file[x][y];
        else if (strcmp("util", element) == 0)
            return sar_analyzer_spike_obj->block_devices_spike_each_file.util_highest_val_each_file[x][y];
        else
            return EXIT_FAILURE;
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("areqsz", element) == 0)
            return sar_analyzer_spike_obj->block_devices_spike_each_file.areqsz_lowest_val_each_file[x][y];
        else if (strcmp("util", element) == 0)
            return sar_analyzer_spike_obj->block_devices_spike_each_file.util_lowest_val_each_file[x][y];
        else
            return EXIT_FAILURE;
    } else
        return EXIT_FAILURE;
}

double get_network_spike_val_each_file(int x, int y, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("rxpck", element) == 0)
            return sar_analyzer_spike_obj->networks_spike_each_file.rxpck_spike_val_each_file[x][y];
        else if (strcmp("txpck", element) == 0)
            return sar_analyzer_spike_obj->networks_spike_each_file.txpck_spike_val_each_file[x][y];
        else if (strcmp("rxkb", element) == 0)
            return sar_analyzer_spike_obj->networks_spike_each_file.rxkb_spike_val_each_file[x][y];
        else if (strcmp("txkb", element) == 0)
            return sar_analyzer_spike_obj->networks_spike_each_file.txkb_spike_val_each_file[x][y];
        else if (strcmp("rxerr", element) == 0)
            return sar_analyzer_spike_obj->networks_spike_each_file.rxerr_spike_val_each_file[x][y];
        else if (strcmp("txerr", element) == 0)
            return sar_analyzer_spike_obj->networks_spike_each_file.txerr_spike_val_each_file[x][y];
        else if (strcmp("rxdrop", element) == 0)
            return sar_analyzer_spike_obj->networks_spike_each_file.rxdrop_spike_val_each_file[x][y];
        else if (strcmp("txdrop", element) == 0)
            return sar_analyzer_spike_obj->networks_spike_each_file.txdrop_spike_val_each_file[x][y];
        else
            return EXIT_FAILURE;
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("rxpck", element) == 0)
            return sar_analyzer_spike_obj->networks_spike_each_file.rxpck_highest_val_each_file[x][y];
        else if (strcmp("txpck", element) == 0)
            return sar_analyzer_spike_obj->networks_spike_each_file.txpck_highest_val_each_file[x][y];
        else if (strcmp("rxkb", element) == 0)
            return sar_analyzer_spike_obj->networks_spike_each_file.rxkb_highest_val_each_file[x][y];
        else if (strcmp("txkb", element) == 0)
            return sar_analyzer_spike_obj->networks_spike_each_file.txkb_highest_val_each_file[x][y];
        else if (strcmp("rxerr", element) == 0)
            return sar_analyzer_spike_obj->networks_spike_each_file.rxerr_highest_val_each_file[x][y];
        else if (strcmp("txerr", element) == 0)
            return sar_analyzer_spike_obj->networks_spike_each_file.txerr_highest_val_each_file[x][y];
        else if (strcmp("rxdrop", element) == 0)
            return sar_analyzer_spike_obj->networks_spike_each_file.rxdrop_highest_val_each_file[x][y];
        else if (strcmp("txdrop", element) == 0)
            return sar_analyzer_spike_obj->networks_spike_each_file.txdrop_highest_val_each_file[x][y];
        else
            return EXIT_FAILURE;
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("rxpck", element) == 0)
            return sar_analyzer_spike_obj->networks_spike_each_file.rxpck_lowest_val_each_file[x][y];
        else if (strcmp("txpck", element) == 0)
            return sar_analyzer_spike_obj->networks_spike_each_file.txpck_lowest_val_each_file[x][y];
        else if (strcmp("rxkb", element) == 0)
            return sar_analyzer_spike_obj->networks_spike_each_file.rxkb_lowest_val_each_file[x][y];
        else if (strcmp("txkb", element) == 0)
            return sar_analyzer_spike_obj->networks_spike_each_file.txkb_lowest_val_each_file[x][y];
        else if (strcmp("rxerr", element) == 0)
            return sar_analyzer_spike_obj->networks_spike_each_file.rxerr_lowest_val_each_file[x][y];
        else if (strcmp("txerr", element) == 0)
            return sar_analyzer_spike_obj->networks_spike_each_file.txerr_lowest_val_each_file[x][y];
        else if (strcmp("rxdrop", element) == 0)
            return sar_analyzer_spike_obj->networks_spike_each_file.rxdrop_lowest_val_each_file[x][y];
        else if (strcmp("txdrop", element) == 0)
            return sar_analyzer_spike_obj->networks_spike_each_file.txdrop_lowest_val_each_file[x][y];
        else
            return EXIT_FAILURE;
    } else if (strcmp("down", analyze_item) == 0) {
        if (strcmp("rxpck", element) == 0)
            return sar_analyzer_spike_obj->networks_spike_each_file.rxpck_down_val_each_file[x][y];
        else if (strcmp("txpck", element) == 0)
            return sar_analyzer_spike_obj->networks_spike_each_file.txpck_down_val_each_file[x][y];
        else if (strcmp("rxkb", element) == 0)
            return sar_analyzer_spike_obj->networks_spike_each_file.rxkb_down_val_each_file[x][y];
        else if (strcmp("txkb", element) == 0)
            return sar_analyzer_spike_obj->networks_spike_each_file.txkb_down_val_each_file[x][y];
        else if (strcmp("rxerr", element) == 0)
            return sar_analyzer_spike_obj->networks_spike_each_file.rxerr_down_val_each_file[x][y];
        else if (strcmp("txerr", element) == 0)
            return sar_analyzer_spike_obj->networks_spike_each_file.txerr_down_val_each_file[x][y];
        else if (strcmp("rxdrop", element) == 0)
            return sar_analyzer_spike_obj->networks_spike_each_file.rxdrop_down_val_each_file[x][y];
        else if (strcmp("txdrop", element) == 0)
            return sar_analyzer_spike_obj->networks_spike_each_file.txdrop_down_val_each_file[x][y];
        else
            return EXIT_FAILURE;
    } else
        return EXIT_FAILURE;
}

/* -- time-span spike val each file -- */

double get_cpu_time_span_spike_val_each_file(int x, int y, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("usr", element) == 0)
            return sar_analyzer_time_span_spike_obj->cpus_time_span_spike_each_file.cpu_usr_time_span_spike_val_each_file[x][y];
        else if (strcmp("sys", element) == 0)
            return sar_analyzer_time_span_spike_obj->cpus_time_span_spike_each_file.cpu_sys_time_span_spike_val_each_file[x][y];
        else if (strcmp("iowait", element) == 0)
            return sar_analyzer_time_span_spike_obj->cpus_time_span_spike_each_file.cpu_iowait_time_span_spike_val_each_file[x][y];
        else if (strcmp("idle", element) == 0)
            return sar_analyzer_time_span_spike_obj->cpus_time_span_spike_each_file.cpu_idle_time_span_spike_val_each_file[x][y];
        else
            return EXIT_FAILURE;
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("usr", element) == 0)
            return sar_analyzer_time_span_spike_obj->cpus_time_span_spike_each_file.cpu_usr_time_span_highest_val_each_file[x][y];
        else if (strcmp("sys", element) == 0)
            return sar_analyzer_time_span_spike_obj->cpus_time_span_spike_each_file.cpu_sys_time_span_highest_val_each_file[x][y];
        else if (strcmp("iowait", element) == 0)
            return sar_analyzer_time_span_spike_obj->cpus_time_span_spike_each_file.cpu_iowait_time_span_highest_val_each_file[x][y];
        else if (strcmp("idle", element) == 0)
            return sar_analyzer_time_span_spike_obj->cpus_time_span_spike_each_file.cpu_idle_time_span_highest_val_each_file[x][y];
        else
            return EXIT_FAILURE;
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("usr", element) == 0)
            return sar_analyzer_time_span_spike_obj->cpus_time_span_spike_each_file.cpu_usr_time_span_lowest_val_each_file[x][y];
        else if (strcmp("sys", element) == 0)
            return sar_analyzer_time_span_spike_obj->cpus_time_span_spike_each_file.cpu_sys_time_span_lowest_val_each_file[x][y];
        else if (strcmp("iowait", element) == 0)
            return sar_analyzer_time_span_spike_obj->cpus_time_span_spike_each_file.cpu_iowait_time_span_lowest_val_each_file[x][y];
        else if (strcmp("idle", element) == 0)
            return sar_analyzer_time_span_spike_obj->cpus_time_span_spike_each_file.cpu_idle_time_span_lowest_val_each_file[x][y];
        else
            return EXIT_FAILURE;
    } else
        return EXIT_FAILURE;
}

double get_tasks_time_span_spike_val_each_file(int x, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("proc", element) == 0)
            return sar_analyzer_time_span_spike_obj->tasks_time_span_spike_each_file.proc_time_span_spike_val_each_file[x];
        else if (strcmp("cswch", element) == 0)
            return sar_analyzer_time_span_spike_obj->tasks_time_span_spike_each_file.cswch_time_span_spike_val_each_file[x];
        else
            return EXIT_FAILURE;
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("proc", element) == 0)
            return sar_analyzer_time_span_spike_obj->tasks_time_span_spike_each_file.proc_time_span_highest_val_each_file[x];
        else if (strcmp("cswch", element) == 0)
            return sar_analyzer_time_span_spike_obj->tasks_time_span_spike_each_file.cswch_time_span_highest_val_each_file[x];
        else
            return EXIT_FAILURE;
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("proc", element) == 0)
            return sar_analyzer_time_span_spike_obj->tasks_time_span_spike_each_file.proc_time_span_lowest_val_each_file[x];
        else if (strcmp("cswch", element) == 0)
            return sar_analyzer_time_span_spike_obj->tasks_time_span_spike_each_file.cswch_time_span_lowest_val_each_file[x];
        else
            return EXIT_FAILURE;
    } else
        return EXIT_FAILURE;
}

double get_pswap_time_span_spike_val_each_file(int x, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("pswpin", element) == 0)
            return sar_analyzer_time_span_spike_obj->pswaps_time_span_spike_each_file.pswpin_time_span_spike_val_each_file[x];
        else if (strcmp("pswpout", element) == 0)
            return sar_analyzer_time_span_spike_obj->pswaps_time_span_spike_each_file.pswpout_time_span_spike_val_each_file[x];
        else
            return EXIT_FAILURE;
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("pswpin", element) == 0)
            return sar_analyzer_time_span_spike_obj->pswaps_time_span_spike_each_file.pswpin_time_span_highest_val_each_file[x];
        else if (strcmp("pswpout", element) == 0)
            return sar_analyzer_time_span_spike_obj->pswaps_time_span_spike_each_file.pswpout_time_span_highest_val_each_file[x];
        else
            return EXIT_FAILURE;
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("pswpin", element) == 0)
            return sar_analyzer_time_span_spike_obj->pswaps_time_span_spike_each_file.pswpin_time_span_lowest_val_each_file[x];
        else if (strcmp("pswpout", element) == 0)
            return sar_analyzer_time_span_spike_obj->pswaps_time_span_spike_each_file.pswpout_time_span_lowest_val_each_file[x];
        else
            return EXIT_FAILURE;
    } else
        return EXIT_FAILURE;
}

double get_paging_time_span_spike_val_each_file(int x, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("pgpgin", element) == 0)
            return sar_analyzer_time_span_spike_obj->pagings_time_span_spike_each_file.pgpgin_time_span_spike_val_each_file[x];
        else if (strcmp("pgpgout", element) == 0)
            return sar_analyzer_time_span_spike_obj->pagings_time_span_spike_each_file.pgpgout_time_span_spike_val_each_file[x];
        else if (strcmp("fault", element) == 0)
            return sar_analyzer_time_span_spike_obj->pagings_time_span_spike_each_file.fault_time_span_spike_val_each_file[x];
        else if (strcmp("majflt", element) == 0)
            return sar_analyzer_time_span_spike_obj->pagings_time_span_spike_each_file.majflt_time_span_spike_val_each_file[x];
        else if (strcmp("vmeff", element) == 0)
            return sar_analyzer_time_span_spike_obj->pagings_time_span_spike_each_file.vmeff_time_span_spike_val_each_file[x];
        else
            return EXIT_FAILURE;
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("pgpgin", element) == 0)
            return sar_analyzer_time_span_spike_obj->pagings_time_span_spike_each_file.pgpgin_time_span_highest_val_each_file[x];
        else if (strcmp("pgpgout", element) == 0)
            return sar_analyzer_time_span_spike_obj->pagings_time_span_spike_each_file.pgpgout_time_span_highest_val_each_file[x];
        else if (strcmp("fault", element) == 0)
            return sar_analyzer_time_span_spike_obj->pagings_time_span_spike_each_file.fault_time_span_highest_val_each_file[x];
        else if (strcmp("majflt", element) == 0)
            return sar_analyzer_time_span_spike_obj->pagings_time_span_spike_each_file.majflt_time_span_highest_val_each_file[x];
        else if (strcmp("vmeff", element) == 0)
            return sar_analyzer_time_span_spike_obj->pagings_time_span_spike_each_file.vmeff_time_span_highest_val_each_file[x];
        else
            return EXIT_FAILURE;
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("pgpgin", element) == 0)
            return sar_analyzer_time_span_spike_obj->pagings_time_span_spike_each_file.pgpgin_time_span_lowest_val_each_file[x];
        else if (strcmp("pgpgout", element) == 0)
            return sar_analyzer_time_span_spike_obj->pagings_time_span_spike_each_file.pgpgout_time_span_lowest_val_each_file[x];
        else if (strcmp("fault", element) == 0)
            return sar_analyzer_time_span_spike_obj->pagings_time_span_spike_each_file.fault_time_span_lowest_val_each_file[x];
        else if (strcmp("majflt", element) == 0)
            return sar_analyzer_time_span_spike_obj->pagings_time_span_spike_each_file.majflt_time_span_lowest_val_each_file[x];
        else if (strcmp("vmeff", element) == 0)
            return sar_analyzer_time_span_spike_obj->pagings_time_span_spike_each_file.vmeff_time_span_lowest_val_each_file[x];
        else
            return EXIT_FAILURE;
    } else
        return EXIT_FAILURE;
}

double get_io_transfer_rate_time_span_spike_val_each_file(int x, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("tps", element) == 0)
            return sar_analyzer_time_span_spike_obj->io_transfer_rates_time_span_spike_each_file.tps_time_span_spike_val_each_file[x];
        else if (strcmp("bread", element) == 0)
            return sar_analyzer_time_span_spike_obj->io_transfer_rates_time_span_spike_each_file.bread_time_span_spike_val_each_file[x];
        else if (strcmp("bwrtn", element) == 0)
            return sar_analyzer_time_span_spike_obj->io_transfer_rates_time_span_spike_each_file.bwrtn_time_span_spike_val_each_file[x];
        else
            return EXIT_FAILURE;
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("tps", element) == 0)
            return sar_analyzer_time_span_spike_obj->io_transfer_rates_time_span_spike_each_file.tps_time_span_highest_val_each_file[x];
        else if (strcmp("bread", element) == 0)
            return sar_analyzer_time_span_spike_obj->io_transfer_rates_time_span_spike_each_file.bread_time_span_highest_val_each_file[x];
        else if (strcmp("bwrtn", element) == 0)
            return sar_analyzer_time_span_spike_obj->io_transfer_rates_time_span_spike_each_file.bwrtn_time_span_highest_val_each_file[x];
        else
            return EXIT_FAILURE;
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("tps", element) == 0)
            return sar_analyzer_time_span_spike_obj->io_transfer_rates_time_span_spike_each_file.tps_time_span_lowest_val_each_file[x];
        else if (strcmp("bread", element) == 0)
            return sar_analyzer_time_span_spike_obj->io_transfer_rates_time_span_spike_each_file.bread_time_span_lowest_val_each_file[x];
        else if (strcmp("bwrtn", element) == 0)
            return sar_analyzer_time_span_spike_obj->io_transfer_rates_time_span_spike_each_file.bwrtn_time_span_lowest_val_each_file[x];
        else
            return EXIT_FAILURE;
    } else
        return EXIT_FAILURE;
}

double get_memory_time_span_spike_val_each_file(int x, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("memused", element) == 0)
            return sar_analyzer_time_span_spike_obj->memories_time_span_spike_each_file.memused_time_span_spike_val_each_file[x];
        else if (strcmp("kbcommit", element) == 0)
            return sar_analyzer_time_span_spike_obj->memories_time_span_spike_each_file.kbcommit_time_span_spike_val_each_file[x];
        else if (strcmp("commit", element) == 0)
            return sar_analyzer_time_span_spike_obj->memories_time_span_spike_each_file.commit_time_span_spike_val_each_file[x];
        else
            return EXIT_FAILURE;
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("memused", element) == 0)
            return sar_analyzer_time_span_spike_obj->memories_time_span_spike_each_file.memused_time_span_highest_val_each_file[x];
        else if (strcmp("kbcommit", element) == 0)
            return sar_analyzer_time_span_spike_obj->memories_time_span_spike_each_file.kbcommit_time_span_highest_val_each_file[x];
        else if (strcmp("commit", element) == 0)
            return sar_analyzer_time_span_spike_obj->memories_time_span_spike_each_file.commit_time_span_highest_val_each_file[x];
        else
            return EXIT_FAILURE;
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("memused", element) == 0)
            return sar_analyzer_time_span_spike_obj->memories_time_span_spike_each_file.memused_time_span_lowest_val_each_file[x];
        else if (strcmp("kbcommit", element) == 0)
            return sar_analyzer_time_span_spike_obj->memories_time_span_spike_each_file.kbcommit_time_span_lowest_val_each_file[x];
        else if (strcmp("commit", element) == 0)
            return sar_analyzer_time_span_spike_obj->memories_time_span_spike_each_file.commit_time_span_lowest_val_each_file[x];
        else
            return EXIT_FAILURE;
    } else
        return EXIT_FAILURE;
}

double get_swpused_time_span_spike_val_each_file(int x, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0)
        return sar_analyzer_time_span_spike_obj->swaps_time_span_spike_each_file.swpused_time_span_spike_val_each_file[x];
    else if (strcmp("highest", analyze_item) == 0)
        return sar_analyzer_time_span_spike_obj->swaps_time_span_spike_each_file.swpused_time_span_highest_val_each_file[x];
    else if (strcmp("lowest", analyze_item) == 0)
        return sar_analyzer_time_span_spike_obj->swaps_time_span_spike_each_file.swpused_time_span_lowest_val_each_file[x];
    else
        return EXIT_FAILURE;
}

int get_kernel_table_time_span_spike_val_each_file(int x, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("dentunusd", element) == 0)
            return sar_analyzer_time_span_spike_obj->kernel_tables_time_span_spike_each_file.dentunusd_time_span_spike_val_each_file[x];
        else if (strcmp("file", element) == 0)
            return sar_analyzer_time_span_spike_obj->kernel_tables_time_span_spike_each_file.file_time_span_spike_val_each_file[x];
        else if (strcmp("inode", element) == 0)
            return sar_analyzer_time_span_spike_obj->kernel_tables_time_span_spike_each_file.inode_time_span_spike_val_each_file[x];
        else
            return EXIT_FAILURE;
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("dentunusd", element) == 0)
            return sar_analyzer_time_span_spike_obj->kernel_tables_time_span_spike_each_file.dentunusd_time_span_highest_val_each_file[x];
        else if (strcmp("file", element) == 0)
            return sar_analyzer_time_span_spike_obj->kernel_tables_time_span_spike_each_file.file_time_span_highest_val_each_file[x];
        else if (strcmp("inode", element) == 0)
            return sar_analyzer_time_span_spike_obj->kernel_tables_time_span_spike_each_file.inode_time_span_highest_val_each_file[x];
        else
            return EXIT_FAILURE;
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("dentunusd", element) == 0)
            return sar_analyzer_time_span_spike_obj->kernel_tables_time_span_spike_each_file.dentunusd_time_span_lowest_val_each_file[x];
        else if (strcmp("file", element) == 0)
            return sar_analyzer_time_span_spike_obj->kernel_tables_time_span_spike_each_file.file_time_span_lowest_val_each_file[x];
        else if (strcmp("inode", element) == 0)
            return sar_analyzer_time_span_spike_obj->kernel_tables_time_span_spike_each_file.inode_time_span_lowest_val_each_file[x];
        else
            return EXIT_FAILURE;
    } else
        return EXIT_FAILURE;
}

double get_ldavg_time_span_spike_val_each_file(int x, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("runq_sz", element) == 0)
            return sar_analyzer_time_span_spike_obj->ldavgs_time_span_spike_each_file.runq_sz_time_span_spike_val_each_file[x];
        else if (strcmp("plist_sz", element) == 0)
            return sar_analyzer_time_span_spike_obj->ldavgs_time_span_spike_each_file.plist_sz_time_span_spike_val_each_file[x];
        else if (strcmp("ldavg_one", element) == 0)
            return sar_analyzer_time_span_spike_obj->ldavgs_time_span_spike_each_file.ldavg_one_time_span_spike_val_each_file[x];
        else if (strcmp("ldavg_five", element) == 0)
            return sar_analyzer_time_span_spike_obj->ldavgs_time_span_spike_each_file.ldavg_five_time_span_spike_val_each_file[x];
        else if (strcmp("ldavg_15", element) == 0)
            return sar_analyzer_time_span_spike_obj->ldavgs_time_span_spike_each_file.ldavg_15_time_span_spike_val_each_file[x];
        else
            return EXIT_FAILURE;
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("runq_sz", element) == 0)
            return sar_analyzer_time_span_spike_obj->ldavgs_time_span_spike_each_file.runq_sz_time_span_highest_val_each_file[x];
        else if (strcmp("plist_sz", element) == 0)
            return sar_analyzer_time_span_spike_obj->ldavgs_time_span_spike_each_file.plist_sz_time_span_highest_val_each_file[x];
        else if (strcmp("ldavg_one", element) == 0)
            return sar_analyzer_time_span_spike_obj->ldavgs_time_span_spike_each_file.ldavg_one_time_span_highest_val_each_file[x];
        else if (strcmp("ldavg_five", element) == 0)
            return sar_analyzer_time_span_spike_obj->ldavgs_time_span_spike_each_file.ldavg_five_time_span_highest_val_each_file[x];
        else if (strcmp("ldavg_15", element) == 0)
            return sar_analyzer_time_span_spike_obj->ldavgs_time_span_spike_each_file.ldavg_15_time_span_highest_val_each_file[x];
        else
            return EXIT_FAILURE;
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("runq_sz", element) == 0)
            return sar_analyzer_time_span_spike_obj->ldavgs_time_span_spike_each_file.runq_sz_time_span_lowest_val_each_file[x];
        else if (strcmp("plist_sz", element) == 0)
            return sar_analyzer_time_span_spike_obj->ldavgs_time_span_spike_each_file.plist_sz_time_span_lowest_val_each_file[x];
        else if (strcmp("ldavg_one", element) == 0)
            return sar_analyzer_time_span_spike_obj->ldavgs_time_span_spike_each_file.ldavg_one_time_span_lowest_val_each_file[x];
        else if (strcmp("ldavg_five", element) == 0)
            return sar_analyzer_time_span_spike_obj->ldavgs_time_span_spike_each_file.ldavg_five_time_span_lowest_val_each_file[x];
        else if (strcmp("ldavg_15", element) == 0)
            return sar_analyzer_time_span_spike_obj->ldavgs_time_span_spike_each_file.ldavg_15_time_span_lowest_val_each_file[x];
        else
            return EXIT_FAILURE;
    } else
        return EXIT_FAILURE;
}

double get_block_device_time_span_spike_val_each_file(int x, int y, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("areqsz", element) == 0)
            return sar_analyzer_time_span_spike_obj->block_devices_time_span_spike_each_file.areqsz_time_span_spike_val_each_file[x][y];
        else if (strcmp("util", element) == 0)
            return sar_analyzer_time_span_spike_obj->block_devices_time_span_spike_each_file.util_time_span_spike_val_each_file[x][y];
        else
            return EXIT_FAILURE;
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("areqsz", element) == 0)
            return sar_analyzer_time_span_spike_obj->block_devices_time_span_spike_each_file.areqsz_time_span_highest_val_each_file[x][y];
        else if (strcmp("util", element) == 0)
            return sar_analyzer_time_span_spike_obj->block_devices_time_span_spike_each_file.util_time_span_highest_val_each_file[x][y];
        else
            return EXIT_FAILURE;
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("areqsz", element) == 0)
            return sar_analyzer_time_span_spike_obj->block_devices_time_span_spike_each_file.areqsz_time_span_lowest_val_each_file[x][y];
        else if (strcmp("util", element) == 0)
            return sar_analyzer_time_span_spike_obj->block_devices_time_span_spike_each_file.util_time_span_lowest_val_each_file[x][y];
        else
            return EXIT_FAILURE;
    } else
        return EXIT_FAILURE;
}

/* -- former val -- */

double get_cpu_former_val(int x, const char *element)
{
    if (strcmp("usr", element) == 0)
        return sar_analyzer_all_obj->cpus_former.cpu_usr_val[x];
    else if (strcmp("sys", element) == 0)
        return sar_analyzer_all_obj->cpus_former.cpu_sys_val[x];
    else if (strcmp("iowait", element) == 0)
        return sar_analyzer_all_obj->cpus_former.cpu_iowait_val[x];
    else if (strcmp("idle", element) == 0)
        return sar_analyzer_all_obj->cpus_former.cpu_idle_val[x];
    else
        return EXIT_FAILURE;
}

double get_tasks_former_val(const char *element)
{
    if (strcmp("proc", element) == 0)
        return sar_analyzer_all_obj->tasks_former.proc_val;
    else if (strcmp("cswch", element) == 0)
        return sar_analyzer_all_obj->tasks_former.cswch_val;
    else
        return EXIT_FAILURE;
}

double get_pswap_former_val(const char *element)
{
    if (strcmp("pswpin", element) == 0)
        return sar_analyzer_all_obj->pswaps_former.pswpin_val;
    else if (strcmp("pswpout", element) == 0)
        return sar_analyzer_all_obj->pswaps_former.pswpout_val;
    else
        return EXIT_FAILURE;
}

double get_paging_former_val(const char *element)
{
    if (strcmp("pgpgin", element) == 0)
        return sar_analyzer_all_obj->pagings_former.pgpgin_val;
    else if (strcmp("pgpgout", element) == 0)
        return sar_analyzer_all_obj->pagings_former.pgpgout_val;
    else if (strcmp("fault", element) == 0)
        return sar_analyzer_all_obj->pagings_former.fault_val;
    else if (strcmp("majflt", element) == 0)
        return sar_analyzer_all_obj->pagings_former.majflt_val;
    else if (strcmp("vmeff", element) == 0)
        return sar_analyzer_all_obj->pagings_former.vmeff_val;
    else
        return EXIT_FAILURE;
}

double get_io_transfer_rate_former_val(const char *element)
{
    if (strcmp("tps", element) == 0)
        return sar_analyzer_all_obj->io_transfer_rates_former.tps_val;
    else if (strcmp("bread", element) == 0)
        return sar_analyzer_all_obj->io_transfer_rates_former.bread_val;
    else if (strcmp("bwrtn", element) == 0)
        return sar_analyzer_all_obj->io_transfer_rates_former.bwrtn_val;
    else
        return EXIT_FAILURE;
}

double get_memory_former_val(const char *element)
{
    if (strcmp("memused", element) == 0)
        return sar_analyzer_all_obj->memories_former.memused_val;
    else if (strcmp("kbcommit", element) == 0)
        return sar_analyzer_all_obj->memories_former.kbcommit_val;
    else if (strcmp("commit", element) == 0)
        return sar_analyzer_all_obj->memories_former.commit_val;
    else
        return EXIT_FAILURE;
}

double get_swpused_former_val(void)
{
    return sar_analyzer_all_obj->swaps_former.swpused_val;
}

int get_kernel_table_former_val(const char *element)
{
    if (strcmp("dentunusd", element) == 0)
        return sar_analyzer_all_obj->kernel_tables_former.dentunusd_val;
    else if (strcmp("file", element) == 0)
        return sar_analyzer_all_obj->kernel_tables_former.file_val;
    else if (strcmp("inode", element) == 0)
        return sar_analyzer_all_obj->kernel_tables_former.inode_val;
    else
        return EXIT_FAILURE;
}

double get_ldavg_former_val(const char *element)
{
    if (strcmp("runq_sz", element) == 0)
        return sar_analyzer_all_obj->ldavgs_former.runq_sz_val;
    else if (strcmp("plist_sz", element) == 0)
        return sar_analyzer_all_obj->ldavgs_former.plist_sz_val;
    else if (strcmp("ldavg_one", element) == 0)
        return sar_analyzer_all_obj->ldavgs_former.ldavg_one_val;
    else if (strcmp("ldavg_five", element) == 0)
        return sar_analyzer_all_obj->ldavgs_former.ldavg_five_val;
    else if (strcmp("ldavg_15", element) == 0)
        return sar_analyzer_all_obj->ldavgs_former.ldavg_15_val;
    else
        return EXIT_FAILURE;
}

double get_block_device_former_val(int x, const char *element)
{
    if (strcmp("areqsz", element) == 0)
        return sar_analyzer_all_obj->block_devices_former.areqsz_val[x];
    else if (strcmp("util", element) == 0)
        return sar_analyzer_all_obj->block_devices_former.util_val[x];
    else
        return EXIT_FAILURE;
}

double get_network_former_val(int x, const char *element)
{
    if (strcmp("rxpck", element) == 0)
        return sar_analyzer_all_obj->networks_former.rxpck_val[x];
    else if (strcmp("txpck", element) == 0)
        return sar_analyzer_all_obj->networks_former.txpck_val[x];
    else if (strcmp("rxkb", element) == 0)
        return sar_analyzer_all_obj->networks_former.rxkb_val[x];
    else if (strcmp("txkb", element) == 0)
        return sar_analyzer_all_obj->networks_former.txkb_val[x];
    else if (strcmp("rxerr", element) == 0)
        return sar_analyzer_all_obj->networks_former.rxerr_val[x];
    else if (strcmp("txerr", element) == 0)
        return sar_analyzer_all_obj->networks_former.txerr_val[x];
    else if (strcmp("rxdrop", element) == 0)
        return sar_analyzer_all_obj->networks_former.rxdrop_val[x];
    else if (strcmp("txdrop", element) == 0)
        return sar_analyzer_all_obj->networks_former.txdrop_val[x];
    else
        return EXIT_FAILURE;
}

/* -- former val each file -- */

double get_cpu_former_val_each_file(int x, int y, const char *element)
{
    if (strcmp("usr", element) == 0)
        return sar_analyzer_spike_obj->cpus_spike_each_file.cpu_usr_former_val_each_file[x][y];
    else if (strcmp("sys", element) == 0)
        return sar_analyzer_spike_obj->cpus_spike_each_file.cpu_sys_former_val_each_file[x][y];
    else if (strcmp("iowait", element) == 0)
        return sar_analyzer_spike_obj->cpus_spike_each_file.cpu_iowait_former_val_each_file[x][y];
    else if (strcmp("idle", element) == 0)
        return sar_analyzer_spike_obj->cpus_spike_each_file.cpu_idle_former_val_each_file[x][y];
    else
        return EXIT_FAILURE;
}

double get_tasks_former_val_each_file(int x, const char *element)
{
    if (strcmp("proc", element) == 0)
        return sar_analyzer_spike_obj->tasks_spike_each_file.proc_former_val_each_file[x];
    else if (strcmp("cswch", element) == 0)
        return sar_analyzer_spike_obj->tasks_spike_each_file.cswch_former_val_each_file[x];
    else
        return EXIT_FAILURE;
}

double get_pswap_former_val_each_file(int x, const char *element)
{
    if (strcmp("pswpin", element) == 0)
        return sar_analyzer_spike_obj->pswaps_spike_each_file.pswpin_former_val_each_file[x];
    else if (strcmp("pswpout", element) == 0)
        return sar_analyzer_spike_obj->pswaps_spike_each_file.pswpout_former_val_each_file[x];
    else
        return EXIT_FAILURE;
}

double get_paging_former_val_each_file(int x, const char *element)
{
    if (strcmp("pgpgin", element) == 0)
        return sar_analyzer_spike_obj->pagings_spike_each_file.pgpgin_former_val_each_file[x];
    else if (strcmp("pgpgout", element) == 0)
        return sar_analyzer_spike_obj->pagings_spike_each_file.pgpgout_former_val_each_file[x];
    else if (strcmp("fault", element) == 0)
        return sar_analyzer_spike_obj->pagings_spike_each_file.fault_former_val_each_file[x];
    else if (strcmp("majflt", element) == 0)
        return sar_analyzer_spike_obj->pagings_spike_each_file.majflt_former_val_each_file[x];
    else if (strcmp("vmeff", element) == 0)
        return sar_analyzer_spike_obj->pagings_spike_each_file.vmeff_former_val_each_file[x];
    else
        return EXIT_FAILURE;
}

double get_io_transfer_rate_former_val_each_file(int x, const char *element)
{
    if (strcmp("tps", element) == 0)
        return sar_analyzer_spike_obj->io_transfer_rates_spike_each_file.tps_former_val_each_file[x];
    else if (strcmp("bread", element) == 0)
        return sar_analyzer_spike_obj->io_transfer_rates_spike_each_file.bread_former_val_each_file[x];
    else if (strcmp("bwrtn", element) == 0)
        return sar_analyzer_spike_obj->io_transfer_rates_spike_each_file.bwrtn_former_val_each_file[x];
    else
        return EXIT_FAILURE;
}

double get_memory_former_val_each_file(int x, const char *element)
{
    if (strcmp("memused", element) == 0)
        return sar_analyzer_spike_obj->memories_spike_each_file.memused_former_val_each_file[x];
    else if (strcmp("kbcommit", element) == 0)
        return sar_analyzer_spike_obj->memories_spike_each_file.kbcommit_former_val_each_file[x];
    else if (strcmp("commit", element) == 0)
        return sar_analyzer_spike_obj->memories_spike_each_file.commit_former_val_each_file[x];
    else
        return EXIT_FAILURE;
}

double get_swpused_former_val_each_file(int x)
{
    return sar_analyzer_spike_obj->swaps_spike_each_file.swpused_former_val_each_file[x];
}

int get_kernel_table_former_val_each_file(int x, const char *element)
{
    if (strcmp("dentunusd", element) == 0)
        return sar_analyzer_spike_obj->kernel_tables_spike_each_file.dentunusd_former_val_each_file[x];
    else if (strcmp("file", element) == 0)
        return sar_analyzer_spike_obj->kernel_tables_spike_each_file.file_former_val_each_file[x];
    else if (strcmp("inode", element) == 0)
        return sar_analyzer_spike_obj->kernel_tables_spike_each_file.inode_former_val_each_file[x];
    else
        return EXIT_FAILURE;
}

double get_ldavg_former_val_each_file(int x, const char *element)
{
    if (strcmp("runq_sz", element) == 0)
        return sar_analyzer_spike_obj->ldavgs_spike_each_file.runq_sz_former_val_each_file[x];
    else if (strcmp("plist_sz", element) == 0)
        return sar_analyzer_spike_obj->ldavgs_spike_each_file.plist_sz_former_val_each_file[x];
    else if (strcmp("ldavg_one", element) == 0)
        return sar_analyzer_spike_obj->ldavgs_spike_each_file.ldavg_one_former_val_each_file[x];
    else if (strcmp("ldavg_five", element) == 0)
        return sar_analyzer_spike_obj->ldavgs_spike_each_file.ldavg_five_former_val_each_file[x];
    else if (strcmp("ldavg_15", element) == 0)
        return sar_analyzer_spike_obj->ldavgs_spike_each_file.ldavg_15_former_val_each_file[x];
    else
        return EXIT_FAILURE;
}

double get_block_device_former_val_each_file(int x, int y, const char *element)
{
    if (strcmp("areqsz", element) == 0)
        return sar_analyzer_spike_obj->block_devices_spike_each_file.areqsz_former_val_each_file[x][y];
    else if (strcmp("util", element) == 0)
        return sar_analyzer_spike_obj->block_devices_spike_each_file.util_former_val_each_file[x][y];
    else
        return EXIT_FAILURE;
}

double get_network_former_val_each_file(int x, int y, const char *element)
{
    if (strcmp("rxpck", element) == 0)
        return sar_analyzer_spike_obj->networks_spike_each_file.rxpck_former_val_each_file[x][y];
    else if (strcmp("txpck", element) == 0)
        return sar_analyzer_spike_obj->networks_spike_each_file.txpck_former_val_each_file[x][y];
    else if (strcmp("rxkb", element) == 0)
        return sar_analyzer_spike_obj->networks_spike_each_file.rxkb_former_val_each_file[x][y];
    else if (strcmp("txkb", element) == 0)
        return sar_analyzer_spike_obj->networks_spike_each_file.txkb_former_val_each_file[x][y];
    else if (strcmp("rxerr", element) == 0)
        return sar_analyzer_spike_obj->networks_spike_each_file.rxerr_former_val_each_file[x][y];
    else if (strcmp("txerr", element) == 0)
        return sar_analyzer_spike_obj->networks_spike_each_file.txerr_former_val_each_file[x][y];
    else if (strcmp("rxdrop", element) == 0)
        return sar_analyzer_spike_obj->networks_spike_each_file.rxdrop_former_val_each_file[x][y];
    else if (strcmp("txdrop", element) == 0)
        return sar_analyzer_spike_obj->networks_spike_each_file.txdrop_former_val_each_file[x][y];
    else
        return EXIT_FAILURE;
}

/* -- time-span former val each file -- */

double get_cpu_time_span_former_val_each_file(int x, int y, const char *element)
{
    if (strcmp("usr", element) == 0)
        return sar_analyzer_time_span_spike_obj->cpus_time_span_spike_each_file.cpu_usr_time_span_former_val_each_file[x][y];
    else if (strcmp("sys", element) == 0)
        return sar_analyzer_time_span_spike_obj->cpus_time_span_spike_each_file.cpu_sys_time_span_former_val_each_file[x][y];
    else if (strcmp("iowait", element) == 0)
        return sar_analyzer_time_span_spike_obj->cpus_time_span_spike_each_file.cpu_iowait_time_span_former_val_each_file[x][y];
    else if (strcmp("idle", element) == 0)
        return sar_analyzer_time_span_spike_obj->cpus_time_span_spike_each_file.cpu_idle_time_span_former_val_each_file[x][y];
    else
        return EXIT_FAILURE;
}

double get_tasks_time_span_former_val_each_file(int x, const char *element)
{
    if (strcmp("proc", element) == 0)
        return sar_analyzer_time_span_spike_obj->tasks_time_span_spike_each_file.proc_time_span_former_val_each_file[x];
    else if (strcmp("cswch", element) == 0)
        return sar_analyzer_time_span_spike_obj->tasks_time_span_spike_each_file.cswch_time_span_former_val_each_file[x];
    else
        return EXIT_FAILURE;
}

double get_pswap_time_span_former_val_each_file(int x, const char *element)
{
    if (strcmp("pswpin", element) == 0)
        return sar_analyzer_time_span_spike_obj->pswaps_time_span_spike_each_file.pswpin_time_span_former_val_each_file[x];
    else if (strcmp("pswpout", element) == 0)
        return sar_analyzer_time_span_spike_obj->pswaps_time_span_spike_each_file.pswpout_time_span_former_val_each_file[x];
    else
        return EXIT_FAILURE;
}

double get_paging_time_span_former_val_each_file(int x, const char *element)
{
    if (strcmp("pgpgin", element) == 0)
        return sar_analyzer_time_span_spike_obj->pagings_time_span_spike_each_file.pgpgin_time_span_former_val_each_file[x];
    else if (strcmp("pgpgout", element) == 0)
        return sar_analyzer_time_span_spike_obj->pagings_time_span_spike_each_file.pgpgout_time_span_former_val_each_file[x];
    else if (strcmp("fault", element) == 0)
        return sar_analyzer_time_span_spike_obj->pagings_time_span_spike_each_file.fault_time_span_former_val_each_file[x];
    else if (strcmp("majflt", element) == 0)
        return sar_analyzer_time_span_spike_obj->pagings_time_span_spike_each_file.majflt_time_span_former_val_each_file[x];
    else if (strcmp("vmeff", element) == 0)
        return sar_analyzer_time_span_spike_obj->pagings_time_span_spike_each_file.vmeff_time_span_former_val_each_file[x];
    else
        return EXIT_FAILURE;
}

double get_io_transfer_rate_time_span_former_val_each_file(int x, const char *element)
{
    if (strcmp("tps", element) == 0)
        return sar_analyzer_time_span_spike_obj->io_transfer_rates_time_span_spike_each_file.tps_time_span_former_val_each_file[x];
    else if (strcmp("bread", element) == 0)
        return sar_analyzer_time_span_spike_obj->io_transfer_rates_time_span_spike_each_file.bread_time_span_former_val_each_file[x];
    else if (strcmp("bwrtn", element) == 0)
        return sar_analyzer_time_span_spike_obj->io_transfer_rates_time_span_spike_each_file.bwrtn_time_span_former_val_each_file[x];
    else
        return EXIT_FAILURE;
}

double get_memory_time_span_former_val_each_file(int x, const char *element)
{
    if (strcmp("memused", element) == 0)
        return sar_analyzer_time_span_spike_obj->memories_time_span_spike_each_file.memused_time_span_former_val_each_file[x];
    else if (strcmp("kbcommit", element) == 0)
        return sar_analyzer_time_span_spike_obj->memories_time_span_spike_each_file.kbcommit_time_span_former_val_each_file[x];
    else if (strcmp("commit", element) == 0)
        return sar_analyzer_time_span_spike_obj->memories_time_span_spike_each_file.commit_time_span_former_val_each_file[x];
    else
        return EXIT_FAILURE;
}

double get_swpused_time_span_former_val_each_file(int x)
{
    return sar_analyzer_time_span_spike_obj->swaps_time_span_spike_each_file.swpused_time_span_former_val_each_file[x];
}

int get_kernel_table_time_span_former_val_each_file(int x, const char *element)
{
    if (strcmp("dentunusd", element) == 0)
        return sar_analyzer_time_span_spike_obj->kernel_tables_time_span_spike_each_file.dentunusd_time_span_former_val_each_file[x];
    else if (strcmp("file", element) == 0)
        return sar_analyzer_time_span_spike_obj->kernel_tables_time_span_spike_each_file.file_time_span_former_val_each_file[x];
    else if (strcmp("inode", element) == 0)
        return sar_analyzer_time_span_spike_obj->kernel_tables_time_span_spike_each_file.inode_time_span_former_val_each_file[x];
    else
        return EXIT_FAILURE;
}

double get_ldavg_time_span_former_val_each_file(int x, const char *element)
{
    if (strcmp("runq_sz", element) == 0)
        return sar_analyzer_time_span_spike_obj->ldavgs_time_span_spike_each_file.runq_sz_time_span_former_val_each_file[x];
    else if (strcmp("plist_sz", element) == 0)
        return sar_analyzer_time_span_spike_obj->ldavgs_time_span_spike_each_file.plist_sz_time_span_former_val_each_file[x];
    else if (strcmp("ldavg_one", element) == 0)
        return sar_analyzer_time_span_spike_obj->ldavgs_time_span_spike_each_file.ldavg_one_time_span_former_val_each_file[x];
    else if (strcmp("ldavg_five", element) == 0)
        return sar_analyzer_time_span_spike_obj->ldavgs_time_span_spike_each_file.ldavg_five_time_span_former_val_each_file[x];
    else if (strcmp("ldavg_15", element) == 0)
        return sar_analyzer_time_span_spike_obj->ldavgs_time_span_spike_each_file.ldavg_15_time_span_former_val_each_file[x];
    else
        return EXIT_FAILURE;
}

double get_block_device_time_span_former_val_each_file(int x, int y, const char *element)
{
    if (strcmp("areqsz", element) == 0)
        return sar_analyzer_time_span_spike_obj->block_devices_time_span_spike_each_file.areqsz_time_span_former_val_each_file[x][y];
    else if (strcmp("util", element) == 0)
        return sar_analyzer_time_span_spike_obj->block_devices_time_span_spike_each_file.util_time_span_former_val_each_file[x][y];
    else
        return EXIT_FAILURE;
}

int get_cpu_as_paragraph(void)
{
    return sar_analyzer_all_obj->cpu_as_paragraph;
}

double get_tmp_val(void)
{
    return sar_analyzer_all_obj->tmp_val;
}

double get_tmp2_val(void)
{
    return sar_analyzer_all_obj->tmp2_val;
}

double get_tmp3_val(void)
{
    return sar_analyzer_all_obj->tmp3_val;
}

double get_tmp4_val(void)
{
    return sar_analyzer_all_obj->tmp4_val;
}

/* -------------------------------------------------- */

/* -- average highest val -- */

int set_cpu_avg_highest_val(double var, int x, const char *element)
{
    if (strcmp("usr", element) == 0) {
        sar_analyzer_obj->cpus_avg_highest.cpu_usr_val[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("sys", element) == 0) {
        sar_analyzer_obj->cpus_avg_highest.cpu_sys_val[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("iowait", element) == 0) {
        sar_analyzer_obj->cpus_avg_highest.cpu_iowait_val[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("idle", element) == 0) {
        sar_analyzer_obj->cpus_avg_highest.cpu_idle_val[x] = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_tasks_avg_highest_val(double var, const char *element)
{
    if (strcmp("proc", element) == 0) {
        sar_analyzer_obj->tasks_avg_highest.proc_val = var;
        return EXIT_SUCCESS;
    } else if (strcmp("cswch", element) == 0) {
        sar_analyzer_obj->tasks_avg_highest.cswch_val = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_pswap_avg_highest_val(double var, const char *element)
{
    if (strcmp("pswpin", element) == 0) {
        sar_analyzer_obj->pswaps_avg_highest.pswpin_val = var;
        return EXIT_SUCCESS;
    } else if (strcmp("pswpout", element) == 0) {
        sar_analyzer_obj->pswaps_avg_highest.pswpout_val = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_paging_avg_highest_val(double var, const char *element)
{
    if (strcmp("pgpgin", element) == 0) {
        sar_analyzer_obj->pagings_avg_highest.pgpgin_val = var;
        return EXIT_SUCCESS;
    } else if (strcmp("pgpgout", element) == 0) {
        sar_analyzer_obj->pagings_avg_highest.pgpgout_val = var;
        return EXIT_SUCCESS;
    } else if (strcmp("fault", element) == 0) {
        sar_analyzer_obj->pagings_avg_highest.fault_val = var;
        return EXIT_SUCCESS;
    } else if (strcmp("majflt", element) == 0) {
        sar_analyzer_obj->pagings_avg_highest.majflt_val = var;
        return EXIT_SUCCESS;
    } else if (strcmp("vmeff", element) == 0) {
        sar_analyzer_obj->pagings_avg_highest.vmeff_val = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_io_transfer_rate_avg_highest_val(double var, const char *element)
{
    if (strcmp("tps", element) == 0) {
        sar_analyzer_obj->io_transfer_rates_avg_highest.tps_val = var;
        return EXIT_SUCCESS;
    } else if (strcmp("bread", element) == 0) {
        sar_analyzer_obj->io_transfer_rates_avg_highest.bread_val = var;
        return EXIT_SUCCESS;
    } else if (strcmp("bwrtn", element) == 0) {
        sar_analyzer_obj->io_transfer_rates_avg_highest.bwrtn_val = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_memory_double_avg_highest_val(double var, const char *element)
{
    if (strcmp("memused", element) == 0) {
        sar_analyzer_obj->memories_avg_highest.memused_val = var;
        return EXIT_SUCCESS;
    } else if (strcmp("commit", element) == 0) {
        sar_analyzer_obj->memories_avg_highest.commit_val = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_memory_int_avg_highest_val(int var, const char *element)
{
    if (strcmp("kbcommit", element) == 0) {
        sar_analyzer_obj->memories_avg_highest.kbcommit_val = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_swpused_avg_highest_val(double var)
{
    sar_analyzer_obj->swaps_avg_highest.swpused_val = var;
    return EXIT_SUCCESS;
}

int set_kernel_table_avg_highest_val(int var, const char *element)
{
    if (strcmp("dentunusd", element) == 0) {
        sar_analyzer_obj->kernel_tables_avg_highest.dentunusd_val = var;
        return EXIT_SUCCESS;
    } else if (strcmp("file", element) == 0) {
        sar_analyzer_obj->kernel_tables_avg_highest.file_val = var;
        return EXIT_SUCCESS;
    } else if (strcmp("inode", element) == 0) {
        sar_analyzer_obj->kernel_tables_avg_highest.inode_val = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_ldavg_int_avg_highest_val(int var, const char *element)
{
    if (strcmp("runq_sz", element) == 0) {
        sar_analyzer_obj->ldavgs_avg_highest.runq_sz_val = var;
        return EXIT_SUCCESS;
    } else if (strcmp("plist_sz", element) == 0) {
        sar_analyzer_obj->ldavgs_avg_highest.plist_sz_val = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_ldavg_double_avg_highest_val(double var, const char *element)
{
    if (strcmp("ldavg_one", element) == 0) {
        sar_analyzer_obj->ldavgs_avg_highest.ldavg_one_val = var;
        return EXIT_SUCCESS;
    } else if (strcmp("ldavg_five", element) == 0) {
        sar_analyzer_obj->ldavgs_avg_highest.ldavg_five_val = var;
        return EXIT_SUCCESS;
    } else if (strcmp("ldavg_15", element) == 0) {
        sar_analyzer_obj->ldavgs_avg_highest.ldavg_15_val = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_block_device_avg_highest_val(double var, int x, const char *element)
{
    if (strcmp("areqsz", element) == 0) {
        sar_analyzer_obj->block_devices_avg_highest.areqsz_val[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("util", element) == 0) {
        sar_analyzer_obj->block_devices_avg_highest.util_val[x] = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_network_avg_highest_val(double var, int x, const char *element)
{
    if (strcmp("rxpck", element) == 0) {
        sar_analyzer_obj->networks_avg_highest.rxpck_val[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("txpck", element) == 0) {
        sar_analyzer_obj->networks_avg_highest.txpck_val[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("rxkb", element) == 0) {
        sar_analyzer_obj->networks_avg_highest.rxkb_val[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("txkb", element) == 0) {
        sar_analyzer_obj->networks_avg_highest.txkb_val[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("rxerr", element) == 0) {
        sar_analyzer_obj->networks_avg_highest.rxerr_val[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("txerr", element) == 0) {
        sar_analyzer_obj->networks_avg_highest.txerr_val[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("rxdrop", element) == 0) {
        sar_analyzer_obj->networks_avg_highest.rxdrop_val[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("txdrop", element) == 0) {
        sar_analyzer_obj->networks_avg_highest.txdrop_val[x] = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

/* -- highest val -- */
/* -- object should be sar_analyzer_all_obj -- */

int set_cpu_highest_val(double var, int x, const char *element)
{
    if (strcmp("usr", element) == 0) {
        sar_analyzer_all_obj->cpus_highest.cpu_usr_val[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("sys", element) == 0) {
        sar_analyzer_all_obj->cpus_highest.cpu_sys_val[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("iowait", element) == 0) {
        sar_analyzer_all_obj->cpus_highest.cpu_iowait_val[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("idle", element) == 0) {
        sar_analyzer_all_obj->cpus_highest.cpu_idle_val[x] = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_tasks_highest_val(double var, const char *element)
{
    if (strcmp("proc", element) == 0) {
        sar_analyzer_all_obj->tasks_highest.proc_val = var;
        return EXIT_SUCCESS;
    } else if (strcmp("cswch", element) == 0) {
        sar_analyzer_all_obj->tasks_highest.cswch_val = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_pswap_highest_val(double var, const char *element)
{
    if (strcmp("pswpin", element) == 0) {
        sar_analyzer_all_obj->pswaps_highest.pswpin_val = var;
        return EXIT_SUCCESS;
    } else if (strcmp("pswpout", element) == 0) {
        sar_analyzer_all_obj->pswaps_highest.pswpout_val = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_paging_highest_val(double var, const char *element)
{
    if (strcmp("pgpgin", element) == 0) {
        sar_analyzer_all_obj->pagings_highest.pgpgin_val = var;
        return EXIT_SUCCESS;
    }
    if (strcmp("pgpgout", element) == 0) {
        sar_analyzer_all_obj->pagings_highest.pgpgout_val = var;
        return EXIT_SUCCESS;
    } else if (strcmp("fault", element) == 0) {
        sar_analyzer_all_obj->pagings_highest.fault_val = var;
        return EXIT_SUCCESS;
    } else if (strcmp("majflt", element) == 0) {
        sar_analyzer_all_obj->pagings_highest.majflt_val = var;
        return EXIT_SUCCESS;
    } else if (strcmp("vmeff", element) == 0) {
        sar_analyzer_all_obj->pagings_highest.vmeff_val = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_io_transfer_rate_highest_val(double var, const char *element)
{
    if (strcmp("tps", element) == 0) {
        sar_analyzer_all_obj->io_transfer_rates_highest.tps_val = var;
        return EXIT_SUCCESS;
    } else if (strcmp("bread", element) == 0) {
        sar_analyzer_all_obj->io_transfer_rates_highest.bread_val = var;
        return EXIT_SUCCESS;
    } else if (strcmp("bwrtn", element) == 0) {
        sar_analyzer_all_obj->io_transfer_rates_highest.bwrtn_val = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_memory_double_highest_val(double var, const char *element)
{
    if (strcmp("memused", element) == 0) {
        sar_analyzer_all_obj->memories_highest.memused_val = var;
        return EXIT_SUCCESS;
    } else if (strcmp("commit", element) == 0) {
        sar_analyzer_all_obj->memories_highest.commit_val = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_memory_int_highest_val(int var, const char *element)
{
    if (strcmp("kbcommit", element) == 0) {
        sar_analyzer_all_obj->memories_highest.kbcommit_val = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_swpused_highest_val(double var)
{
    sar_analyzer_all_obj->swaps_highest.swpused_val = var;
    return EXIT_SUCCESS;
}

int set_kernel_table_highest_val(int var, const char *element)
{
    if (strcmp("dentunusd", element) == 0) {
        sar_analyzer_all_obj->kernel_tables_highest.dentunusd_val = var;
        return EXIT_SUCCESS;
    } else if (strcmp("file", element) == 0) {
        sar_analyzer_all_obj->kernel_tables_highest.file_val = var;
        return EXIT_SUCCESS;
    } else if (strcmp("inode", element) == 0) {
        sar_analyzer_all_obj->kernel_tables_highest.inode_val = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_ldavg_int_highest_val(int var, const char *element)
{
    if (strcmp("runq_sz", element) == 0) {
        sar_analyzer_all_obj->ldavgs_highest.runq_sz_val = var;
        return EXIT_SUCCESS;
    } else if (strcmp("plist_sz", element) == 0) {
        sar_analyzer_all_obj->ldavgs_highest.plist_sz_val = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_ldavg_double_highest_val(double var, const char *element)
{
    if (strcmp("ldavg_one", element) == 0) {
        sar_analyzer_all_obj->ldavgs_highest.ldavg_one_val = var;
        return EXIT_SUCCESS;
    } else if (strcmp("ldavg_five", element) == 0) {
        sar_analyzer_all_obj->ldavgs_highest.ldavg_five_val = var;
        return EXIT_SUCCESS;
    } else if (strcmp("ldavg_15", element) == 0) {
        sar_analyzer_all_obj->ldavgs_highest.ldavg_15_val = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_block_device_highest_val(double var, int x, const char *element)
{
    if (strcmp("areqsz", element) == 0) {
        sar_analyzer_all_obj->block_devices_highest.areqsz_val[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("util", element) == 0) {
        sar_analyzer_all_obj->block_devices_highest.util_val[x] = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_network_highest_val(double var, int x, const char *element)
{
    if (strcmp("rxpck", element) == 0) {
        sar_analyzer_all_obj->networks_highest.rxpck_val[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("txpck", element) == 0) {
        sar_analyzer_all_obj->networks_highest.txpck_val[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("rxkb", element) == 0) {
        sar_analyzer_all_obj->networks_highest.rxkb_val[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("txkb", element) == 0) {
        sar_analyzer_all_obj->networks_highest.txkb_val[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("rxerr", element) == 0) {
        sar_analyzer_all_obj->networks_highest.rxerr_val[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("txerr", element) == 0) {
        sar_analyzer_all_obj->networks_highest.txerr_val[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("rxdrop", element) == 0) {
        sar_analyzer_all_obj->networks_highest.rxdrop_val[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("txdrop", element) == 0) {
        sar_analyzer_all_obj->networks_highest.txdrop_val[x] = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

/* -- average lowest val -- */

int set_cpu_avg_lowest_val(double var, int x, const char *element)
{
    if (strcmp("usr", element) == 0) {
        sar_analyzer_obj->cpus_avg_lowest.cpu_usr_val[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("sys", element) == 0) {
        sar_analyzer_obj->cpus_avg_lowest.cpu_sys_val[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("iowait", element) == 0) {
        sar_analyzer_obj->cpus_avg_lowest.cpu_iowait_val[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("idle", element) == 0) {
        sar_analyzer_obj->cpus_avg_lowest.cpu_idle_val[x] = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_tasks_avg_lowest_val(double var, const char *element)
{
    if (strcmp("proc", element) == 0) {
        sar_analyzer_obj->tasks_avg_lowest.proc_val = var;
        return EXIT_SUCCESS;
    } else if (strcmp("cswch", element) == 0) {
        sar_analyzer_obj->tasks_avg_lowest.cswch_val = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_pswap_avg_lowest_val(double var, const char *element)
{
    if (strcmp("pswpin", element) == 0) {
        sar_analyzer_obj->pswaps_avg_lowest.pswpin_val = var;
        return EXIT_SUCCESS;
    } else if (strcmp("pswpout", element) == 0) {
        sar_analyzer_obj->pswaps_avg_lowest.pswpout_val = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_paging_avg_lowest_val(double var, const char *element)
{
    if (strcmp("pgpgin", element) == 0) {
        sar_analyzer_obj->pagings_avg_lowest.pgpgin_val = var;
        return EXIT_SUCCESS;
    } else if (strcmp("pgpgout", element) == 0) {
        sar_analyzer_obj->pagings_avg_lowest.pgpgout_val = var;
        return EXIT_SUCCESS;
    } else if (strcmp("fault", element) == 0) {
        sar_analyzer_obj->pagings_avg_lowest.fault_val = var;
        return EXIT_SUCCESS;
    } else if (strcmp("majflt", element) == 0) {
        sar_analyzer_obj->pagings_avg_lowest.majflt_val = var;
        return EXIT_SUCCESS;
    } else if (strcmp("vmeff", element) == 0) {
        sar_analyzer_obj->pagings_avg_lowest.vmeff_val = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_io_transfer_rate_avg_lowest_val(double var, const char *element)
{
    if (strcmp("tps", element) == 0) {
        sar_analyzer_obj->io_transfer_rates_avg_lowest.tps_val = var;
        return EXIT_SUCCESS;
    } else if (strcmp("bread", element) == 0) {
        sar_analyzer_obj->io_transfer_rates_avg_lowest.bread_val = var;
        return EXIT_SUCCESS;
    } else if (strcmp("bwrtn", element) == 0) {
        sar_analyzer_obj->io_transfer_rates_avg_lowest.bwrtn_val = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_memory_double_avg_lowest_val(double var, const char *element)
{
    if (strcmp("memused", element) == 0) {
        sar_analyzer_obj->memories_avg_lowest.memused_val = var;
        return EXIT_SUCCESS;
    } else if (strcmp("commit", element) == 0) {
        sar_analyzer_obj->memories_avg_lowest.commit_val = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_memory_int_avg_lowest_val(int var, const char *element)
{
    if (strcmp("kbcommit", element) == 0) {
        sar_analyzer_obj->memories_avg_lowest.kbcommit_val = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_swpused_avg_lowest_val(double var)
{
    sar_analyzer_obj->swaps_avg_lowest.swpused_val = var;
    return EXIT_SUCCESS;
}

int set_kernel_table_avg_lowest_val(int var, const char *element)
{
    if (strcmp("dentunusd", element) == 0) {
        sar_analyzer_obj->kernel_tables_avg_lowest.dentunusd_val = var;
        return EXIT_SUCCESS;
    } else if (strcmp("file", element) == 0) {
        sar_analyzer_obj->kernel_tables_avg_lowest.file_val = var;
        return EXIT_SUCCESS;
    } else if (strcmp("inode", element) == 0) {
        sar_analyzer_obj->kernel_tables_avg_lowest.inode_val = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_ldavg_int_avg_lowest_val(int var, const char *element)
{
    if (strcmp("runq_sz", element) == 0) {
        sar_analyzer_obj->ldavgs_avg_lowest.runq_sz_val = var;
        return EXIT_SUCCESS;
    } else if (strcmp("plist_sz", element) == 0) {
        sar_analyzer_obj->ldavgs_avg_lowest.plist_sz_val = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_ldavg_double_avg_lowest_val(double var, const char *element)
{
    if (strcmp("ldavg_one", element) == 0) {
        sar_analyzer_obj->ldavgs_avg_lowest.ldavg_one_val = var;
        return EXIT_SUCCESS;
    } else if (strcmp("ldavg_five", element) == 0) {
        sar_analyzer_obj->ldavgs_avg_lowest.ldavg_five_val = var;
        return EXIT_SUCCESS;
    } else if (strcmp("ldavg_15", element) == 0) {
        sar_analyzer_obj->ldavgs_avg_lowest.ldavg_15_val = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_block_device_avg_lowest_val(double var, int x, const char *element)
{
    if (strcmp("areqsz", element) == 0) {
        sar_analyzer_obj->block_devices_avg_lowest.areqsz_val[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("util", element) == 0) {
        sar_analyzer_obj->block_devices_avg_lowest.util_val[x] = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_network_avg_lowest_val(double var, int x, const char *element)
{
    if (strcmp("rxpck", element) == 0) {
        sar_analyzer_obj->networks_avg_lowest.rxpck_val[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("txpck", element) == 0) {
        sar_analyzer_obj->networks_avg_lowest.txpck_val[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("rxkb", element) == 0) {
        sar_analyzer_obj->networks_avg_lowest.rxkb_val[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("txkb", element) == 0) {
        sar_analyzer_obj->networks_avg_lowest.txkb_val[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("rxerr", element) == 0) {
        sar_analyzer_obj->networks_avg_lowest.rxerr_val[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("txerr", element) == 0) {
        sar_analyzer_obj->networks_avg_lowest.txerr_val[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("rxdrop", element) == 0) {
        sar_analyzer_obj->networks_avg_lowest.rxdrop_val[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("txdrop", element) == 0) {
        sar_analyzer_obj->networks_avg_lowest.txdrop_val[x] = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

/* -- spike val -- */
/* -- object should be sar_analyzer_all_obj -- */

int set_cpu_spike_val(double var, int x, const char *element)
{
    if (strcmp("usr", element) == 0) {
        sar_analyzer_all_obj->cpus_spike.cpu_usr_val[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("sys", element) == 0) {
        sar_analyzer_all_obj->cpus_spike.cpu_sys_val[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("iowait", element) == 0) {
        sar_analyzer_all_obj->cpus_spike.cpu_iowait_val[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("idle", element) == 0) {
        sar_analyzer_all_obj->cpus_spike.cpu_idle_val[x] = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_tasks_spike_val(double var, const char *element)
{
    if (strcmp("proc", element) == 0) {
        sar_analyzer_all_obj->tasks_spike.proc_val = var;
        return EXIT_SUCCESS;
    } else if (strcmp("cswch", element) == 0) {
        sar_analyzer_all_obj->tasks_spike.cswch_val = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_pswap_spike_val(double var, const char *element)
{
    if (strcmp("pswpin", element) == 0) {
        sar_analyzer_all_obj->pswaps_spike.pswpin_val = var;
        return EXIT_SUCCESS;
    } else if (strcmp("pswpout", element) == 0) {
        sar_analyzer_all_obj->pswaps_spike.pswpout_val = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_paging_spike_val(double var, const char *element)
{
    if (strcmp("pgpgin", element) == 0) {
        sar_analyzer_all_obj->pagings_spike.pgpgin_val = var;
        return EXIT_SUCCESS;
    } else if (strcmp("pgpgout", element) == 0) {
        sar_analyzer_all_obj->pagings_spike.pgpgout_val = var;
        return EXIT_SUCCESS;
    } else if (strcmp("fault", element) == 0) {
        sar_analyzer_all_obj->pagings_spike.fault_val = var;
        return EXIT_SUCCESS;
    } else if (strcmp("majflt", element) == 0) {
        sar_analyzer_all_obj->pagings_spike.majflt_val = var;
        return EXIT_SUCCESS;
    } else if (strcmp("vmeff", element) == 0) {
        sar_analyzer_all_obj->pagings_spike.vmeff_val = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_io_transfer_rate_spike_val(double var, const char *element)
{
    if (strcmp("tps", element) == 0) {
        sar_analyzer_all_obj->io_transfer_rates_spike.tps_val = var;
        return EXIT_SUCCESS;
    } else if (strcmp("bread", element) == 0) {
        sar_analyzer_all_obj->io_transfer_rates_spike.bread_val = var;
        return EXIT_SUCCESS;
    } else if (strcmp("bwrtn", element) == 0) {
        sar_analyzer_all_obj->io_transfer_rates_spike.bwrtn_val = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_memory_double_spike_val(double var, const char *element)
{
    if (strcmp("memused", element) == 0) {
        sar_analyzer_all_obj->memories_spike.memused_val = var;
        return EXIT_SUCCESS;
    } else if (strcmp("commit", element) == 0) {
        sar_analyzer_all_obj->memories_spike.commit_val = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_memory_int_spike_val(int var, const char *element)
{
    if (strcmp("kbcommit", element) == 0) {
        sar_analyzer_all_obj->memories_spike.kbcommit_val = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_swpused_spike_val(double var)
{
    sar_analyzer_all_obj->swaps_spike.swpused_val = var;
    return EXIT_SUCCESS;
}

int set_kernel_table_spike_val(int var, const char *element)
{
    if (strcmp("dentunusd", element) == 0) {
        sar_analyzer_all_obj->kernel_tables_spike.dentunusd_val = var;
        return EXIT_SUCCESS;
    } else if (strcmp("file", element) == 0) {
        sar_analyzer_all_obj->kernel_tables_spike.file_val = var;
        return EXIT_SUCCESS;
    } else if (strcmp("inode", element) == 0) {
        sar_analyzer_all_obj->kernel_tables_spike.inode_val = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_ldavg_int_spike_val(int var, const char *element)
{
    if (strcmp("runq_sz", element) == 0) {
        sar_analyzer_all_obj->ldavgs_spike.runq_sz_val = var;
        return EXIT_SUCCESS;
    } else if (strcmp("plist_sz", element) == 0) {
        sar_analyzer_all_obj->ldavgs_spike.plist_sz_val = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_ldavg_double_spike_val(double var, const char *element)
{
    if (strcmp("ldavg_one", element) == 0) {
        sar_analyzer_all_obj->ldavgs_spike.ldavg_one_val = var;
        return EXIT_SUCCESS;
    } else if (strcmp("ldavg_five", element) == 0) {
        sar_analyzer_all_obj->ldavgs_spike.ldavg_five_val = var;
        return EXIT_SUCCESS;
    } else if (strcmp("ldavg_15", element) == 0) {
        sar_analyzer_all_obj->ldavgs_spike.ldavg_15_val = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_block_device_spike_val(double var, int x, const char *element)
{
    if (strcmp("areqsz", element) == 0) {
        sar_analyzer_all_obj->block_devices_spike.areqsz_val[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("util", element) == 0) {
        sar_analyzer_all_obj->block_devices_spike.util_val[x] = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_network_spike_val(double var, int x, const char *element)
{
    if (strcmp("rxpck", element) == 0) {
        sar_analyzer_all_obj->networks_spike.rxpck_val[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("txpck", element) == 0) {
        sar_analyzer_all_obj->networks_spike.txpck_val[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("rxkb", element) == 0) {
        sar_analyzer_all_obj->networks_spike.rxkb_val[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("txkb", element) == 0) {
        sar_analyzer_all_obj->networks_spike.txkb_val[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("rxerr", element) == 0) {
        sar_analyzer_all_obj->networks_spike.rxerr_val[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("txerr", element) == 0) {
        sar_analyzer_all_obj->networks_spike.txerr_val[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("rxdrop", element) == 0) {
        sar_analyzer_all_obj->networks_spike.rxdrop_val[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("txdrop", element) == 0) {
        sar_analyzer_all_obj->networks_spike.txdrop_val[x] = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

/* -- former val -- */
/* -- object should be sar_analyzer_all_obj -- */

int set_cpu_former_val(double var, int x, const char *element)
{
    if (strcmp("usr", element) == 0) {
        sar_analyzer_all_obj->cpus_former.cpu_usr_val[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("sys", element) == 0) {
        sar_analyzer_all_obj->cpus_former.cpu_sys_val[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("iowait", element) == 0) {
        sar_analyzer_all_obj->cpus_former.cpu_iowait_val[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("idle", element) == 0) {
        sar_analyzer_all_obj->cpus_former.cpu_idle_val[x] = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_tasks_former_val(double var, const char *element)
{
    if (strcmp("proc", element) == 0) {
        sar_analyzer_all_obj->tasks_former.proc_val = var;
        return EXIT_SUCCESS;
    } else if (strcmp("cswch", element) == 0) {
        sar_analyzer_all_obj->tasks_former.cswch_val = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_pswap_former_val(double var, const char *element)
{
    if (strcmp("pswpin", element) == 0) {
        sar_analyzer_all_obj->pswaps_former.pswpin_val = var;
        return EXIT_SUCCESS;
    } else if (strcmp("pswpout", element) == 0) {
        sar_analyzer_all_obj->pswaps_former.pswpout_val = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_paging_former_val(double var, const char *element)
{
    if (strcmp("pgpgin", element) == 0) {
        sar_analyzer_all_obj->pagings_former.pgpgin_val = var;
        return EXIT_SUCCESS;
    } else if (strcmp("pgpgout", element) == 0) {
        sar_analyzer_all_obj->pagings_former.pgpgout_val = var;
        return EXIT_SUCCESS;
    } else if (strcmp("fault", element) == 0) {
        sar_analyzer_all_obj->pagings_former.fault_val = var;
        return EXIT_SUCCESS;
    } else if (strcmp("majflt", element) == 0) {
        sar_analyzer_all_obj->pagings_former.majflt_val = var;
        return EXIT_SUCCESS;
    } else if (strcmp("vmeff", element) == 0) {
        sar_analyzer_all_obj->pagings_former.vmeff_val = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_io_transfer_rate_former_val(double var, const char *element)
{
    if (strcmp("tps", element) == 0) {
        sar_analyzer_all_obj->io_transfer_rates_former.tps_val = var;
        return EXIT_SUCCESS;
    } else if (strcmp("bread", element) == 0) {
        sar_analyzer_all_obj->io_transfer_rates_former.bread_val = var;
        return EXIT_SUCCESS;
    } else if (strcmp("bwrtn", element) == 0) {
        sar_analyzer_all_obj->io_transfer_rates_former.bwrtn_val = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_memory_double_former_val(double var, const char *element)
{
    if (strcmp("memused", element) == 0) {
        sar_analyzer_all_obj->memories_former.memused_val = var;
        return EXIT_SUCCESS;
    } else if (strcmp("commit", element) == 0) {
        sar_analyzer_all_obj->memories_former.commit_val = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_memory_int_former_val(int var, const char *element)
{
    if (strcmp("kbcommit", element) == 0) {
        sar_analyzer_all_obj->memories_former.kbcommit_val = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_swpused_former_val(double var)
{
    sar_analyzer_all_obj->swaps_former.swpused_val = var;
    return EXIT_SUCCESS;
}

int set_kernel_table_former_val(int var, const char *element)
{
    if (strcmp("dentunusd", element) == 0) {
        sar_analyzer_all_obj->kernel_tables_former.dentunusd_val = var;
        return EXIT_SUCCESS;
    } else if (strcmp("file", element) == 0) {
        sar_analyzer_all_obj->kernel_tables_former.file_val = var;
        return EXIT_SUCCESS;
    } else if (strcmp("inode", element) == 0) {
        sar_analyzer_all_obj->kernel_tables_former.inode_val = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_ldavg_int_former_val(int var, const char *element)
{
    if (strcmp("runq_sz", element) == 0) {
        sar_analyzer_all_obj->ldavgs_former.runq_sz_val = var;
        return EXIT_SUCCESS;
    } else if (strcmp("plist_sz", element) == 0) {
        sar_analyzer_all_obj->ldavgs_former.plist_sz_val = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_ldavg_double_former_val(double var, const char *element)
{
    if (strcmp("ldavg_one", element) == 0) {
        sar_analyzer_all_obj->ldavgs_former.ldavg_one_val = var;
        return EXIT_SUCCESS;
    } else if (strcmp("ldavg_five", element) == 0) {
        sar_analyzer_all_obj->ldavgs_former.ldavg_five_val = var;
        return EXIT_SUCCESS;
    } else if (strcmp("ldavg_15", element) == 0) {
        sar_analyzer_all_obj->ldavgs_former.ldavg_15_val = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_block_device_former_val(double var, int x, const char *element)
{
    if (strcmp("areqsz", element) == 0) {
        sar_analyzer_all_obj->block_devices_former.areqsz_val[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("util", element) == 0) {
        sar_analyzer_all_obj->block_devices_former.util_val[x] = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_network_former_val(double var, int x, const char *element)
{
    if (strcmp("rxpck", element) == 0) {
        sar_analyzer_all_obj->networks_former.rxpck_val[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("txpck", element) == 0) {
        sar_analyzer_all_obj->networks_former.txpck_val[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("rxkb", element) == 0) {
        sar_analyzer_all_obj->networks_former.rxkb_val[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("txkb", element) == 0) {
        sar_analyzer_all_obj->networks_former.txkb_val[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("rxerr", element) == 0) {
        sar_analyzer_all_obj->networks_former.rxerr_val[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("txerr", element) == 0) {
        sar_analyzer_all_obj->networks_former.txerr_val[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("rxdrop", element) == 0) {
        sar_analyzer_all_obj->networks_former.rxdrop_val[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("txdrop", element) == 0) {
        sar_analyzer_all_obj->networks_former.txdrop_val[x] = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

/* -- lowest val -- */
/* -- object should be sar_analyzer_all_obj -- */

int set_cpu_lowest_val(double var, int x, const char *element)
{
    if (strcmp("usr", element) == 0) {
        sar_analyzer_all_obj->cpus_lowest.cpu_usr_val[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("sys", element) == 0) {
        sar_analyzer_all_obj->cpus_lowest.cpu_sys_val[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("iowait", element) == 0) {
        sar_analyzer_all_obj->cpus_lowest.cpu_iowait_val[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("idle", element) == 0) {
        sar_analyzer_all_obj->cpus_lowest.cpu_idle_val[x] = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_tasks_lowest_val(double var, const char *element)
{
    if (strcmp("proc", element) == 0) {
        sar_analyzer_all_obj->tasks_lowest.proc_val = var;
        return EXIT_SUCCESS;
    } else if (strcmp("cswch", element) == 0) {
        sar_analyzer_all_obj->tasks_lowest.cswch_val = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_pswap_lowest_val(double var, const char *element)
{
    if (strcmp("pswpin", element) == 0) {
        sar_analyzer_all_obj->pswaps_lowest.pswpin_val = var;
        return EXIT_SUCCESS;
    } else if (strcmp("pswpout", element) == 0) {
        sar_analyzer_all_obj->pswaps_lowest.pswpout_val = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_paging_lowest_val(double var, const char *element)
{
    if (strcmp("pgpgin", element) == 0) {
        sar_analyzer_all_obj->pagings_lowest.pgpgin_val = var;
        return EXIT_SUCCESS;
    } else if (strcmp("pgpgout", element) == 0) {
        sar_analyzer_all_obj->pagings_lowest.pgpgout_val = var;
        return EXIT_SUCCESS;
    }
    if (strcmp("fault", element) == 0) {
        sar_analyzer_all_obj->pagings_lowest.fault_val = var;
        return EXIT_SUCCESS;
    } else if (strcmp("majflt", element) == 0) {
        sar_analyzer_all_obj->pagings_lowest.majflt_val = var;
        return EXIT_SUCCESS;
    } else if (strcmp("vmeff", element) == 0) {
        sar_analyzer_all_obj->pagings_lowest.vmeff_val = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_io_transfer_rate_lowest_val(double var, const char *element)
{
    if (strcmp("tps", element) == 0) {
        sar_analyzer_all_obj->io_transfer_rates_lowest.tps_val = var;
        return EXIT_SUCCESS;
    } else if (strcmp("bread", element) == 0) {
        sar_analyzer_all_obj->io_transfer_rates_lowest.bread_val = var;
        return EXIT_SUCCESS;
    } else if (strcmp("bwrtn", element) == 0) {
        sar_analyzer_all_obj->io_transfer_rates_lowest.bwrtn_val = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_memory_double_lowest_val(double var, const char *element)
{
    if (strcmp("memused", element) == 0) {
        sar_analyzer_all_obj->memories_lowest.memused_val = var;
        return EXIT_SUCCESS;
    } else if (strcmp("commit", element) == 0) {
        sar_analyzer_all_obj->memories_lowest.commit_val = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_memory_int_lowest_val(int var, const char *element)
{
    if (strcmp("kbcommit", element) == 0) {
        sar_analyzer_all_obj->memories_lowest.kbcommit_val = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_swpused_lowest_val(double var)
{
    sar_analyzer_all_obj->swaps_lowest.swpused_val = var;
    return EXIT_SUCCESS;
}

int set_kernel_table_lowest_val(int var, const char *element)
{
    if (strcmp("dentunusd", element) == 0) {
        sar_analyzer_all_obj->kernel_tables_lowest.dentunusd_val = var;
        return EXIT_SUCCESS;
    } else if (strcmp("file", element) == 0) {
        sar_analyzer_all_obj->kernel_tables_lowest.file_val = var;
        return EXIT_SUCCESS;
    } else if (strcmp("inode", element) == 0) {
        sar_analyzer_all_obj->kernel_tables_lowest.inode_val = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_ldavg_int_lowest_val(int var, const char *element)
{
    if (strcmp("runq_sz", element) == 0) {
        sar_analyzer_all_obj->ldavgs_lowest.runq_sz_val = var;
        return EXIT_SUCCESS;
    } else if (strcmp("plist_sz", element) == 0) {
        sar_analyzer_all_obj->ldavgs_lowest.plist_sz_val = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_ldavg_double_lowest_val(double var, const char *element)
{
    if (strcmp("ldavg_one", element) == 0) {
        sar_analyzer_all_obj->ldavgs_lowest.ldavg_one_val = var;
        return EXIT_SUCCESS;
    } else if (strcmp("ldavg_five", element) == 0) {
        sar_analyzer_all_obj->ldavgs_lowest.ldavg_five_val = var;
        return EXIT_SUCCESS;
    } else if (strcmp("ldavg_15", element) == 0) {
        sar_analyzer_all_obj->ldavgs_lowest.ldavg_15_val = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_block_device_lowest_val(double var, int x, const char *element)
{
    if (strcmp("areqsz", element) == 0) {
        sar_analyzer_all_obj->block_devices_lowest.areqsz_val[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("util", element) == 0) {
        sar_analyzer_all_obj->block_devices_lowest.util_val[x] = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

int set_network_lowest_val(double var, int x, const char *element)
{
    if (strcmp("rxpck", element) == 0) {
        sar_analyzer_all_obj->networks_lowest.rxpck_val[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("txpck", element) == 0) {
        sar_analyzer_all_obj->networks_lowest.txpck_val[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("rxkb", element) == 0) {
        sar_analyzer_all_obj->networks_lowest.rxkb_val[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("txkb", element) == 0) {
        sar_analyzer_all_obj->networks_lowest.txkb_val[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("rxerr", element) == 0) {
        sar_analyzer_all_obj->networks_lowest.rxerr_val[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("txerr", element) == 0) {
        sar_analyzer_all_obj->networks_lowest.txerr_val[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("rxdrop", element) == 0) {
        sar_analyzer_all_obj->networks_lowest.rxdrop_val[x] = var;
        return EXIT_SUCCESS;
    } else if (strcmp("txdrop", element) == 0) {
        sar_analyzer_all_obj->networks_lowest.txdrop_val[x] = var;
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
}

void set_cpu_as_paragraph(int x)
{
    sar_analyzer_all_obj->cpu_as_paragraph = x;
}

void set_tmp_val(double x)
{
    sar_analyzer_all_obj->tmp_val = x;
}

void set_tmp2_val(double x)
{
    sar_analyzer_all_obj->tmp2_val = x;
}

void set_tmp3_val(double x)
{
    sar_analyzer_all_obj->tmp3_val = x;
}

void set_tmp4_val(double x)
{
    sar_analyzer_all_obj->tmp4_val = x;
}

/* getters */

/* -- average highest val -- */

double get_cpu_avg_highest_val(int x, const char *element)
{
    if (strcmp("usr", element) == 0)
        return sar_analyzer_obj->cpus_avg_highest.cpu_usr_val[x];
    else if (strcmp("sys", element) == 0)
        return sar_analyzer_obj->cpus_avg_highest.cpu_sys_val[x];
    else if (strcmp("iowait", element) == 0)
        return sar_analyzer_obj->cpus_avg_highest.cpu_iowait_val[x];
    else if (strcmp("idle", element) == 0)
        return sar_analyzer_obj->cpus_avg_highest.cpu_idle_val[x];
    else
        return EXIT_FAILURE;
}

double get_tasks_avg_highest_val(const char *element)
{
    if (strcmp("proc", element) == 0)
        return sar_analyzer_obj->tasks_avg_highest.proc_val;
    else if (strcmp("cswch", element) == 0)
        return sar_analyzer_obj->tasks_avg_highest.cswch_val;
    else
        return EXIT_FAILURE;
}

double get_pswap_avg_highest_val(const char *element)
{
    if (strcmp("pswpin", element) == 0)
        return sar_analyzer_obj->pswaps_avg_highest.pswpin_val;
    else if (strcmp("pswpout", element) == 0)
        return sar_analyzer_obj->pswaps_avg_highest.pswpout_val;
    else
        return EXIT_FAILURE;
}

double get_paging_avg_highest_val(const char *element)
{
    if (strcmp("pgpgin", element) == 0)
        return sar_analyzer_obj->pagings_avg_highest.pgpgin_val;
    else if (strcmp("pgpgout", element) == 0)
        return sar_analyzer_obj->pagings_avg_highest.pgpgout_val;
    else if (strcmp("fault", element) == 0)
        return sar_analyzer_obj->pagings_avg_highest.fault_val;
    else if (strcmp("majflt", element) == 0)
        return sar_analyzer_obj->pagings_avg_highest.majflt_val;
    else if (strcmp("vmeff", element) == 0)
        return sar_analyzer_obj->pagings_avg_highest.vmeff_val;
    else
        return EXIT_FAILURE;
}

double get_io_transfer_rate_avg_highest_val(const char *element)
{
    if (strcmp("tps", element) == 0)
        return sar_analyzer_obj->io_transfer_rates_avg_highest.tps_val;
    else if (strcmp("bread", element) == 0)
        return sar_analyzer_obj->io_transfer_rates_avg_highest.bread_val;
    else if (strcmp("bwrtn", element) == 0)
        return sar_analyzer_obj->io_transfer_rates_avg_highest.bwrtn_val;
    else
        return EXIT_FAILURE;
}

double get_memory_avg_highest_val(const char *element)
{
    if (strcmp("memused", element) == 0)
        return sar_analyzer_obj->memories_avg_highest.memused_val;
    else if (strcmp("kbcommit", element) == 0)
        return sar_analyzer_obj->memories_avg_highest.kbcommit_val;
    else if (strcmp("commit", element) == 0)
        return sar_analyzer_obj->memories_avg_highest.commit_val;
    else
        return EXIT_FAILURE;
}

double get_swpused_avg_highest_val(void)
{
    return sar_analyzer_obj->swaps_avg_highest.swpused_val;
}

int get_kernel_table_avg_highest_val(const char *element)
{
    if (strcmp("dentunusd", element) == 0)
        return sar_analyzer_obj->kernel_tables_avg_highest.dentunusd_val;
    else if (strcmp("file", element) == 0)
        return sar_analyzer_obj->kernel_tables_avg_highest.file_val;
    else if (strcmp("inode", element) == 0)
        return sar_analyzer_obj->kernel_tables_avg_highest.inode_val;
    else
        return EXIT_FAILURE;
}

double get_ldavg_avg_highest_val(const char *element)
{
    if (strcmp("runq_sz", element) == 0)
        return sar_analyzer_obj->ldavgs_avg_highest.runq_sz_val;
    else if (strcmp("plist_sz", element) == 0)
        return sar_analyzer_obj->ldavgs_avg_highest.plist_sz_val;
    else if (strcmp("ldavg_one", element) == 0)
        return sar_analyzer_obj->ldavgs_avg_highest.ldavg_one_val;
    else if (strcmp("ldavg_five", element) == 0)
        return sar_analyzer_obj->ldavgs_avg_highest.ldavg_five_val;
    else if (strcmp("ldavg_15", element) == 0)
        return sar_analyzer_obj->ldavgs_avg_highest.ldavg_15_val;
    else
        return EXIT_FAILURE;
}

double get_block_device_avg_highest_val(int x, const char *element)
{
    if (strcmp("areqsz", element) == 0)
        return sar_analyzer_obj->block_devices_avg_highest.areqsz_val[x];
    else if (strcmp("util", element) == 0)
        return sar_analyzer_obj->block_devices_avg_highest.util_val[x];
    else
        return EXIT_FAILURE;
}

double get_network_avg_highest_val(int x, const char *element)
{
    if (strcmp("rxpck", element) == 0)
        return sar_analyzer_obj->networks_avg_highest.rxpck_val[x];
    else if (strcmp("txpck", element) == 0)
        return sar_analyzer_obj->networks_avg_highest.txpck_val[x];
    else if (strcmp("rxkb", element) == 0)
        return sar_analyzer_obj->networks_avg_highest.rxkb_val[x];
    else if (strcmp("txkb", element) == 0)
        return sar_analyzer_obj->networks_avg_highest.txkb_val[x];
    else if (strcmp("rxerr", element) == 0)
        return sar_analyzer_obj->networks_avg_highest.rxerr_val[x];
    else if (strcmp("txerr", element) == 0)
        return sar_analyzer_obj->networks_avg_highest.txerr_val[x];
    else if (strcmp("rxdrop", element) == 0)
        return sar_analyzer_obj->networks_avg_highest.rxdrop_val[x];
    else if (strcmp("txdrop", element) == 0)
        return sar_analyzer_obj->networks_avg_highest.txdrop_val[x];
    else
        return EXIT_FAILURE;
}

/* -- highest val(for sar_analyzer_all_obj) -- */
/* -- object should be sar_analyzer_all_obj -- */

double get_cpu_highest_val(int x, const char *element)
{
    if (strcmp("usr", element) == 0)
        return sar_analyzer_all_obj->cpus_highest.cpu_usr_val[x];
    else if (strcmp("sys", element) == 0)
        return sar_analyzer_all_obj->cpus_highest.cpu_sys_val[x];
    else if (strcmp("iowait", element) == 0)
        return sar_analyzer_all_obj->cpus_highest.cpu_iowait_val[x];
    else if (strcmp("idle", element) == 0)
        return sar_analyzer_all_obj->cpus_highest.cpu_idle_val[x];
    else
        return EXIT_FAILURE;
}

double get_tasks_highest_val(const char *element)
{
    if (strcmp("proc", element) == 0)
        return sar_analyzer_all_obj->tasks_highest.proc_val;
    else if (strcmp("cswch", element) == 0)
        return sar_analyzer_all_obj->tasks_highest.cswch_val;
    else
        return EXIT_FAILURE;
}

double get_pswap_highest_val(const char *element)
{
    if (strcmp("pswpin", element) == 0)
        return sar_analyzer_all_obj->pswaps_highest.pswpin_val;
    else if (strcmp("pswpout", element) == 0)
        return sar_analyzer_all_obj->pswaps_highest.pswpout_val;
    else
        return EXIT_FAILURE;
}

double get_paging_highest_val(const char *element)
{
    if (strcmp("pgpgin", element) == 0)
        return sar_analyzer_all_obj->pagings_highest.pgpgin_val;
    else if (strcmp("pgpgout", element) == 0)
        return sar_analyzer_all_obj->pagings_highest.pgpgout_val;
    else if (strcmp("fault", element) == 0)
        return sar_analyzer_all_obj->pagings_highest.fault_val;
    else if (strcmp("majflt", element) == 0)
        return sar_analyzer_all_obj->pagings_highest.majflt_val;
    else if (strcmp("vmeff", element) == 0)
        return sar_analyzer_all_obj->pagings_highest.vmeff_val;
    else
        return EXIT_FAILURE;
}

double get_io_transfer_rate_highest_val(const char *element)
{
    if (strcmp("tps", element) == 0)
        return sar_analyzer_all_obj->io_transfer_rates_highest.tps_val;
    else if (strcmp("bread", element) == 0)
        return sar_analyzer_all_obj->io_transfer_rates_highest.bread_val;
    else if (strcmp("bwrtn", element) == 0)
        return sar_analyzer_all_obj->io_transfer_rates_highest.bwrtn_val;
    else
        return EXIT_FAILURE;
}

double get_memory_highest_val(const char *element)
{
    if (strcmp("memused", element) == 0)
        return sar_analyzer_all_obj->memories_highest.memused_val;
    else if (strcmp("kbcommit", element) == 0)
        return sar_analyzer_all_obj->memories_highest.kbcommit_val;
    else if (strcmp("commit", element) == 0)
        return sar_analyzer_all_obj->memories_highest.commit_val;
    else
        return EXIT_FAILURE;
}

double get_swpused_highest_val(void)
{
    return sar_analyzer_all_obj->swaps_highest.swpused_val;
}

int get_kernel_table_highest_val(const char *element)
{
    if (strcmp("dentunusd", element) == 0)
        return sar_analyzer_all_obj->kernel_tables_highest.dentunusd_val;
    else if (strcmp("file", element) == 0)
        return sar_analyzer_all_obj->kernel_tables_highest.file_val;
    else if (strcmp("inode", element) == 0)
        return sar_analyzer_all_obj->kernel_tables_highest.inode_val;
    else
        return EXIT_FAILURE;
}

double get_ldavg_highest_val(const char *element)
{
    if (strcmp("runq_sz", element) == 0)
        return sar_analyzer_all_obj->ldavgs_highest.runq_sz_val;
    else if (strcmp("plist_sz", element) == 0)
        return sar_analyzer_all_obj->ldavgs_highest.plist_sz_val;
    else if (strcmp("ldavg_one", element) == 0)
        return sar_analyzer_all_obj->ldavgs_highest.ldavg_one_val;
    else if (strcmp("ldavg_five", element) == 0)
        return sar_analyzer_all_obj->ldavgs_highest.ldavg_five_val;
    else if (strcmp("ldavg_15", element) == 0)
        return sar_analyzer_all_obj->ldavgs_highest.ldavg_15_val;
    else
        return EXIT_FAILURE;
}

double get_block_device_highest_val(int x, const char *element)
{
    if (strcmp("areqsz", element) == 0)
        return sar_analyzer_all_obj->block_devices_highest.areqsz_val[x];
    else if (strcmp("util", element) == 0)
        return sar_analyzer_all_obj->block_devices_highest.util_val[x];
    else
        return EXIT_FAILURE;
}

double get_network_highest_val(int x, const char *element)
{
    if (strcmp("rxpck", element) == 0)
        return sar_analyzer_all_obj->networks_highest.rxpck_val[x];
    else if (strcmp("txpck", element) == 0)
        return sar_analyzer_all_obj->networks_highest.txpck_val[x];
    else if (strcmp("rxkb", element) == 0)
        return sar_analyzer_all_obj->networks_highest.rxkb_val[x];
    else if (strcmp("txkb", element) == 0)
        return sar_analyzer_all_obj->networks_highest.txkb_val[x];
    else if (strcmp("rxerr", element) == 0)
        return sar_analyzer_all_obj->networks_highest.rxerr_val[x];
    else if (strcmp("txerr", element) == 0)
        return sar_analyzer_all_obj->networks_highest.txerr_val[x];
    else if (strcmp("rxdrop", element) == 0)
        return sar_analyzer_all_obj->networks_highest.rxdrop_val[x];
    else if (strcmp("txdrop", element) == 0)
        return sar_analyzer_all_obj->networks_highest.txdrop_val[x];
    else
        return EXIT_FAILURE;
}

/* -- avg_highest date(for sar_analyzer_obj) -- */

const char *get_cpu_avg_highest_date(int x, const char *element)
{
    if (strcmp("usr", element) == 0)
        return sar_analyzer_obj->date_cpus_avg_highest.cpu_usr_date[x];
    else if (strcmp("sys", element) == 0)
        return sar_analyzer_obj->date_cpus_avg_highest.cpu_sys_date[x];
    else if (strcmp("iowait", element) == 0)
        return sar_analyzer_obj->date_cpus_avg_highest.cpu_iowait_date[x];
    else if (strcmp("idle", element) == 0)
        return sar_analyzer_obj->date_cpus_avg_highest.cpu_idle_date[x];
    else
        return "error";
}

const char *get_tasks_avg_highest_date(const char *element)
{
    if (strcmp("proc", element) == 0)
        return sar_analyzer_obj->date_tasks_avg_highest.proc_date;
    else if (strcmp("cswch", element) == 0)
        return sar_analyzer_obj->date_tasks_avg_highest.cswch_date;
    else
        return "error";
}

const char *get_pswap_avg_highest_date(const char *element)
{
    if (strcmp("pswpin", element) == 0)
        return sar_analyzer_obj->date_pswaps_avg_highest.pswpin_date;
    else if (strcmp("pswpout", element) == 0)
        return sar_analyzer_obj->date_pswaps_avg_highest.pswpout_date;
    else
        return "error";
}

const char *get_paging_avg_highest_date(const char *element)
{
    if (strcmp("pgpgin", element) == 0)
        return sar_analyzer_obj->date_pagings_avg_highest.pgpgin_date;
    else if (strcmp("pgpgout", element) == 0)
        return sar_analyzer_obj->date_pagings_avg_highest.pgpgout_date;
    else if (strcmp("fault", element) == 0)
        return sar_analyzer_obj->date_pagings_avg_highest.fault_date;
    else if (strcmp("majflt", element) == 0)
        return sar_analyzer_obj->date_pagings_avg_highest.majflt_date;
    else if (strcmp("vmeff", element) == 0)
        return sar_analyzer_obj->date_pagings_avg_highest.vmeff_date;
    else
        return "error";
}

const char *get_io_transfer_rate_avg_highest_date(const char *element)
{
    if (strcmp("tps", element) == 0)
        return sar_analyzer_obj->date_io_transfer_rates_avg_highest.tps_date;
    else if (strcmp("bread", element) == 0)
        return sar_analyzer_obj->date_io_transfer_rates_avg_highest.bread_date;
    else if (strcmp("bwrtn", element) == 0)
        return sar_analyzer_obj->date_io_transfer_rates_avg_highest.bwrtn_date;
    else
        return "error";
}

const char *get_memory_avg_highest_date(const char *element)
{
    if (strcmp("memused", element) == 0)
        return sar_analyzer_obj->date_memories_avg_highest.memused_date;
    else if (strcmp("kbcommit", element) == 0)
        return sar_analyzer_obj->date_memories_avg_highest.kbcommit_date;
    else if (strcmp("commit", element) == 0)
        return sar_analyzer_obj->date_memories_avg_highest.commit_date;
    else
        return "error";
}

const char *get_swpused_avg_highest_date(void)
{
    return sar_analyzer_obj->date_swaps_avg_highest.swpused_date;
}

const char *get_kernel_table_avg_highest_date(const char *element)
{
    if (strcmp("dentunusd", element) == 0)
        return sar_analyzer_obj->date_kernel_tables_avg_highest.dentunusd_date;
    else if (strcmp("file", element) == 0)
        return sar_analyzer_obj->date_kernel_tables_avg_highest.file_date;
    else if (strcmp("inode", element) == 0)
        return sar_analyzer_obj->date_kernel_tables_avg_highest.inode_date;
    else
        return "error";
}

const char *get_ldavg_avg_highest_date(const char *element)
{
    if (strcmp("runq_sz", element) == 0)
        return sar_analyzer_obj->date_ldavgs_avg_highest.runq_sz_date;
    else if (strcmp("plist_sz", element) == 0)
        return sar_analyzer_obj->date_ldavgs_avg_highest.plist_sz_date;
    else if (strcmp("ldavg_one", element) == 0)
        return sar_analyzer_obj->date_ldavgs_avg_highest.ldavg_one_date;
    else if (strcmp("ldavg_five", element) == 0)
        return sar_analyzer_obj->date_ldavgs_avg_highest.ldavg_five_date;
    else if (strcmp("ldavg_15", element) == 0)
        return sar_analyzer_obj->date_ldavgs_avg_highest.ldavg_15_date;
    else
        return "error";
}

const char *get_block_device_avg_highest_date(int x, const char *element)
{
    if (strcmp("areqsz", element) == 0)
        return sar_analyzer_obj->date_block_devices_avg_highest.areqsz_date[x];
    else if (strcmp("util", element) == 0)
        return sar_analyzer_obj->date_block_devices_avg_highest.util_date[x];
    else
        return "error";
}

const char *get_network_avg_highest_date(int x, const char *element)
{
    if (strcmp("rxpck", element) == 0)
        return sar_analyzer_obj->date_networks_avg_highest.rxpck_date[x];
    else if (strcmp("txpck", element) == 0)
        return sar_analyzer_obj->date_networks_avg_highest.txpck_date[x];
    else if (strcmp("rxkb", element) == 0)
        return sar_analyzer_obj->date_networks_avg_highest.rxkb_date[x];
    else if (strcmp("txkb", element) == 0)
        return sar_analyzer_obj->date_networks_avg_highest.txkb_date[x];
    else if (strcmp("rxerr", element) == 0)
        return sar_analyzer_obj->date_networks_avg_highest.rxerr_date[x];
    else if (strcmp("txerr", element) == 0)
        return sar_analyzer_obj->date_networks_avg_highest.txerr_date[x];
    else if (strcmp("rxdrop", element) == 0)
        return sar_analyzer_obj->date_networks_avg_highest.rxdrop_date[x];
    else if (strcmp("txdrop", element) == 0)
        return sar_analyzer_obj->date_networks_avg_highest.txdrop_date[x];
    else
        return "error";
}

/* -- average lowest val -- */

double get_cpu_avg_lowest_val(int x, const char *element)
{
    if (strcmp("usr", element) == 0)
        return sar_analyzer_obj->cpus_avg_lowest.cpu_usr_val[x];
    else if (strcmp("sys", element) == 0)
        return sar_analyzer_obj->cpus_avg_lowest.cpu_sys_val[x];
    else if (strcmp("iowait", element) == 0)
        return sar_analyzer_obj->cpus_avg_lowest.cpu_iowait_val[x];
    else if (strcmp("idle", element) == 0)
        return sar_analyzer_obj->cpus_avg_lowest.cpu_idle_val[x];
    else
        return EXIT_FAILURE;
}

double get_tasks_avg_lowest_val(const char *element)
{
    if (strcmp("proc", element) == 0)
        return sar_analyzer_obj->tasks_avg_lowest.proc_val;
    else if (strcmp("cswch", element) == 0)
        return sar_analyzer_obj->tasks_avg_lowest.cswch_val;
    else
        return EXIT_FAILURE;
}

double get_pswap_avg_lowest_val(const char *element)
{
    if (strcmp("pswpin", element) == 0)
        return sar_analyzer_obj->pswaps_avg_lowest.pswpin_val;
    else if (strcmp("pswpout", element) == 0)
        return sar_analyzer_obj->pswaps_avg_lowest.pswpout_val;
    else
        return EXIT_FAILURE;
}

double get_paging_avg_lowest_val(const char *element)
{
    if (strcmp("pgpgin", element) == 0)
        return sar_analyzer_obj->pagings_avg_lowest.pgpgin_val;
    else if (strcmp("pgpgout", element) == 0)
        return sar_analyzer_obj->pagings_avg_lowest.pgpgout_val;
    else if (strcmp("fault", element) == 0)
        return sar_analyzer_obj->pagings_avg_lowest.fault_val;
    else if (strcmp("majflt", element) == 0)
        return sar_analyzer_obj->pagings_avg_lowest.majflt_val;
    else if (strcmp("vmeff", element) == 0)
        return sar_analyzer_obj->pagings_avg_lowest.vmeff_val;
    else
        return EXIT_FAILURE;
}

double get_io_transfer_rate_avg_lowest_val(const char *element)
{
    if (strcmp("tps", element) == 0)
        return sar_analyzer_obj->io_transfer_rates_avg_lowest.tps_val;
    else if (strcmp("bread", element) == 0)
        return sar_analyzer_obj->io_transfer_rates_avg_lowest.bread_val;
    else if (strcmp("bwrtn", element) == 0)
        return sar_analyzer_obj->io_transfer_rates_avg_lowest.bwrtn_val;
    else
        return EXIT_FAILURE;
}

double get_memory_avg_lowest_val(const char *element)
{
    if (strcmp("memused", element) == 0)
        return sar_analyzer_obj->memories_avg_lowest.memused_val;
    else if (strcmp("kbcommit", element) == 0)
        return sar_analyzer_obj->memories_avg_lowest.kbcommit_val;
    else if (strcmp("commit", element) == 0)
        return sar_analyzer_obj->memories_avg_lowest.commit_val;
    else
        return EXIT_FAILURE;
}

double get_swpused_avg_lowest_val(void)
{
    return sar_analyzer_obj->swaps_avg_lowest.swpused_val;
}

int get_kernel_table_avg_lowest_val(const char *element)
{
    if (strcmp("dentunusd", element) == 0)
        return sar_analyzer_obj->kernel_tables_avg_lowest.dentunusd_val;
    else if (strcmp("file", element) == 0)
        return sar_analyzer_obj->kernel_tables_avg_lowest.file_val;
    else if (strcmp("inode", element) == 0)
        return sar_analyzer_obj->kernel_tables_avg_lowest.inode_val;
    else
        return EXIT_FAILURE;
}

double get_ldavg_avg_lowest_val(const char *element)
{
    if (strcmp("runq_sz", element) == 0)
        return sar_analyzer_obj->ldavgs_avg_lowest.runq_sz_val;
    else if (strcmp("plist_sz", element) == 0)
        return sar_analyzer_obj->ldavgs_avg_lowest.plist_sz_val;
    else if (strcmp("ldavg_one", element) == 0)
        return sar_analyzer_obj->ldavgs_avg_lowest.ldavg_one_val;
    else if (strcmp("ldavg_five", element) == 0)
        return sar_analyzer_obj->ldavgs_avg_lowest.ldavg_five_val;
    else if (strcmp("ldavg_15", element) == 0)
        return sar_analyzer_obj->ldavgs_avg_lowest.ldavg_15_val;
    else
        return EXIT_FAILURE;
}

double get_block_device_avg_lowest_val(int x, const char *element)
{
    if (strcmp("areqsz", element) == 0)
        return sar_analyzer_obj->block_devices_avg_lowest.areqsz_val[x];
    else if (strcmp("util", element) == 0)
        return sar_analyzer_obj->block_devices_avg_lowest.util_val[x];
    else
        return EXIT_FAILURE;
}

double get_network_avg_lowest_val(int x, const char *element)
{
    if (strcmp("rxpck", element) == 0)
        return sar_analyzer_obj->networks_avg_lowest.rxpck_val[x];
    else if (strcmp("txpck", element) == 0)
        return sar_analyzer_obj->networks_avg_lowest.txpck_val[x];
    else if (strcmp("rxkb", element) == 0)
        return sar_analyzer_obj->networks_avg_lowest.rxkb_val[x];
    else if (strcmp("txkb", element) == 0)
        return sar_analyzer_obj->networks_avg_lowest.txkb_val[x];
    else if (strcmp("rxerr", element) == 0)
        return sar_analyzer_obj->networks_avg_lowest.rxerr_val[x];
    else if (strcmp("txerr", element) == 0)
        return sar_analyzer_obj->networks_avg_lowest.txerr_val[x];
    else if (strcmp("rxdrop", element) == 0)
        return sar_analyzer_obj->networks_avg_lowest.rxdrop_val[x];
    else if (strcmp("txdrop", element) == 0)
        return sar_analyzer_obj->networks_avg_lowest.txdrop_val[x];
    else
        return EXIT_FAILURE;
}

/* -- highst date(for sar_analyzer_all_obj) -- */
/* -- object should be sar_analyzer_all_obj -- */

const char *get_cpu_highest_date(int x, const char *element)
{
    if (strcmp("usr", element) == 0)
        return sar_analyzer_all_obj->date_cpus_highest.cpu_usr_date[x];
    else if (strcmp("sys", element) == 0)
        return sar_analyzer_all_obj->date_cpus_highest.cpu_sys_date[x];
    else if (strcmp("iowait", element) == 0)
        return sar_analyzer_all_obj->date_cpus_highest.cpu_iowait_date[x];
    else if (strcmp("idle", element) == 0)
        return sar_analyzer_all_obj->date_cpus_highest.cpu_idle_date[x];
    else
        return "error";
}

const char *get_tasks_highest_date(const char *element)
{
    if (strcmp("proc", element) == 0)
        return sar_analyzer_all_obj->date_tasks_highest.proc_date;
    else if (strcmp("cswch", element) == 0)
        return sar_analyzer_all_obj->date_tasks_highest.cswch_date;
    else
        return "error";
}

const char *get_pswap_highest_date(const char *element)
{
    if (strcmp("pswpin", element) == 0)
        return sar_analyzer_all_obj->date_pswaps_highest.pswpin_date;
    else if (strcmp("pswpout", element) == 0)
        return sar_analyzer_all_obj->date_pswaps_highest.pswpout_date;
    else
        return "error";
}

const char *get_paging_highest_date(const char *element)
{
    if (strcmp("pgpgin", element) == 0)
        return sar_analyzer_all_obj->date_pagings_highest.pgpgin_date;
    else if (strcmp("pgpgout", element) == 0)
        return sar_analyzer_all_obj->date_pagings_highest.pgpgout_date;
    else if (strcmp("fault", element) == 0)
        return sar_analyzer_all_obj->date_pagings_highest.fault_date;
    else if (strcmp("majflt", element) == 0)
        return sar_analyzer_all_obj->date_pagings_highest.majflt_date;
    else if (strcmp("vmeff", element) == 0)
        return sar_analyzer_all_obj->date_pagings_highest.vmeff_date;
    else
        return "error";
}

const char *get_io_transfer_rate_highest_date(const char *element)
{
    if (strcmp("tps", element) == 0)
        return sar_analyzer_all_obj->date_io_transfer_rates_highest.tps_date;
    else if (strcmp("bread", element) == 0)
        return sar_analyzer_all_obj->date_io_transfer_rates_highest.bread_date;
    else if (strcmp("bwrtn", element) == 0)
        return sar_analyzer_all_obj->date_io_transfer_rates_highest.bwrtn_date;
    else
        return "error";
}

const char *get_memory_highest_date(const char *element)
{
    if (strcmp("memused", element) == 0)
        return sar_analyzer_all_obj->date_memories_highest.memused_date;
    else if (strcmp("kbcommit", element) == 0)
        return sar_analyzer_all_obj->date_memories_highest.kbcommit_date;
    else if (strcmp("commit", element) == 0)
        return sar_analyzer_all_obj->date_memories_highest.commit_date;
    else
        return "error";
}

const char *get_swpused_highest_date(void)
{
    return sar_analyzer_all_obj->date_swaps_highest.swpused_date;
}

const char *get_kernel_table_highest_date(const char *element)
{
    if (strcmp("dentunusd", element) == 0)
        return sar_analyzer_all_obj->date_kernel_tables_highest.dentunusd_date;
    else if (strcmp("file", element) == 0)
        return sar_analyzer_all_obj->date_kernel_tables_highest.file_date;
    else if (strcmp("inode", element) == 0)
        return sar_analyzer_all_obj->date_kernel_tables_highest.inode_date;
    else
        return "error";
}

const char *get_ldavg_highest_date(const char *element)
{
    if (strcmp("runq_sz", element) == 0)
        return sar_analyzer_all_obj->date_ldavgs_highest.runq_sz_date;
    else if (strcmp("plist_sz", element) == 0)
        return sar_analyzer_all_obj->date_ldavgs_highest.plist_sz_date;
    else if (strcmp("ldavg_one", element) == 0)
        return sar_analyzer_all_obj->date_ldavgs_highest.ldavg_one_date;
    else if (strcmp("ldavg_five", element) == 0)
        return sar_analyzer_all_obj->date_ldavgs_highest.ldavg_five_date;
    else if (strcmp("ldavg_15", element) == 0)
        return sar_analyzer_all_obj->date_ldavgs_highest.ldavg_15_date;
    else
        return "error";
}

const char *get_block_device_highest_date(int x, const char *element)
{
    if (strcmp("areqsz", element) == 0)
        return sar_analyzer_all_obj->date_block_devices_highest.areqsz_date[x];
    else if (strcmp("util", element) == 0)
        return sar_analyzer_all_obj->date_block_devices_highest.util_date[x];
    else
        return "error";
}

const char *get_network_highest_date(int x, const char *element)
{
    if (strcmp("rxpck", element) == 0)
        return sar_analyzer_all_obj->date_networks_highest.rxpck_date[x];
    else if (strcmp("txpck", element) == 0)
        return sar_analyzer_all_obj->date_networks_highest.txpck_date[x];
    else if (strcmp("rxkb", element) == 0)
        return sar_analyzer_all_obj->date_networks_highest.rxkb_date[x];
    else if (strcmp("txkb", element) == 0)
        return sar_analyzer_all_obj->date_networks_highest.txkb_date[x];
    else if (strcmp("rxerr", element) == 0)
        return sar_analyzer_all_obj->date_networks_highest.rxerr_date[x];
    else if (strcmp("txerr", element) == 0)
        return sar_analyzer_all_obj->date_networks_highest.txerr_date[x];
    else if (strcmp("rxdrop", element) == 0)
        return sar_analyzer_all_obj->date_networks_highest.rxdrop_date[x];
    else if (strcmp("txdrop", element) == 0)
        return sar_analyzer_all_obj->date_networks_highest.txdrop_date[x];
    else
        return "error";
}

/* -- highst time(for sar_analyzer_all_obj) -- */
/* -- object should be sar_analyzer_all_obj -- */

const char *get_cpu_highest_time(int x, const char *element)
{
    if (strcmp("usr", element) == 0)
        return sar_analyzer_all_obj->date_cpus_highest.cpu_usr_time[x];
    else if (strcmp("sys", element) == 0)
        return sar_analyzer_all_obj->date_cpus_highest.cpu_sys_time[x];
    else if (strcmp("iowait", element) == 0)
        return sar_analyzer_all_obj->date_cpus_highest.cpu_iowait_time[x];
    else if (strcmp("idle", element) == 0)
        return sar_analyzer_all_obj->date_cpus_highest.cpu_idle_time[x];
    else
        return "error";
}

const char *get_tasks_highest_time(const char *element)
{
    if (strcmp("proc", element) == 0)
        return sar_analyzer_all_obj->date_tasks_highest.proc_time;
    else if (strcmp("cswch", element) == 0)
        return sar_analyzer_all_obj->date_tasks_highest.cswch_time;
    else
        return "error";
}

const char *get_pswap_highest_time(const char *element)
{
    if (strcmp("pswpin", element) == 0)
        return sar_analyzer_all_obj->date_pswaps_highest.pswpin_time;
    else if (strcmp("pswpout", element) == 0)
        return sar_analyzer_all_obj->date_pswaps_highest.pswpout_time;
    else
        return "error";
}

const char *get_paging_highest_time(const char *element)
{
    if (strcmp("pgpgin", element) == 0)
        return sar_analyzer_all_obj->date_pagings_highest.pgpgin_time;
    else if (strcmp("pgpgout", element) == 0)
        return sar_analyzer_all_obj->date_pagings_highest.pgpgout_time;
    else if (strcmp("fault", element) == 0)
        return sar_analyzer_all_obj->date_pagings_highest.fault_time;
    else if (strcmp("majflt", element) == 0)
        return sar_analyzer_all_obj->date_pagings_highest.majflt_time;
    else if (strcmp("vmeff", element) == 0)
        return sar_analyzer_all_obj->date_pagings_highest.vmeff_time;
    else
        return "error";
}

const char *get_io_transfer_rate_highest_time(const char *element)
{
    if (strcmp("tps", element) == 0)
        return sar_analyzer_all_obj->date_io_transfer_rates_highest.tps_time;
    else if (strcmp("bread", element) == 0)
        return sar_analyzer_all_obj->date_io_transfer_rates_highest.bread_time;
    else if (strcmp("bwrtn", element) == 0)
        return sar_analyzer_all_obj->date_io_transfer_rates_highest.bwrtn_time;
    else
        return "error";
}

const char *get_memory_highest_time(const char *element)
{
    if (strcmp("memused", element) == 0)
        return sar_analyzer_all_obj->date_memories_highest.memused_time;
    else if (strcmp("kbcommit", element) == 0)
        return sar_analyzer_all_obj->date_memories_highest.kbcommit_time;
    else if (strcmp("commit", element) == 0)
        return sar_analyzer_all_obj->date_memories_highest.commit_time;
    else
        return "error";
}

const char *get_swpused_highest_time(void)
{
    return sar_analyzer_all_obj->date_swaps_highest.swpused_time;
}

const char *get_kernel_table_highest_time(const char *element)
{
    if (strcmp("dentunusd", element) == 0)
        return sar_analyzer_all_obj->date_kernel_tables_highest.dentunusd_time;
    else if (strcmp("file", element) == 0)
        return sar_analyzer_all_obj->date_kernel_tables_highest.file_time;
    else if (strcmp("inode", element) == 0)
        return sar_analyzer_all_obj->date_kernel_tables_highest.inode_time;
    else
        return "error";
}

const char *get_ldavg_highest_time(const char *element)
{
    if (strcmp("runq_sz", element) == 0)
        return sar_analyzer_all_obj->date_ldavgs_highest.runq_sz_time;
    else if (strcmp("plist_sz", element) == 0)
        return sar_analyzer_all_obj->date_ldavgs_highest.plist_sz_time;
    else if (strcmp("ldavg_one", element) == 0)
        return sar_analyzer_all_obj->date_ldavgs_highest.ldavg_one_time;
    else if (strcmp("ldavg_five", element) == 0)
        return sar_analyzer_all_obj->date_ldavgs_highest.ldavg_five_time;
    else if (strcmp("ldavg_15", element) == 0)
        return sar_analyzer_all_obj->date_ldavgs_highest.ldavg_15_time;
    else
        return "error";
}

const char *get_block_device_highest_time(int x, const char *element)
{
    if (strcmp("areqsz", element) == 0)
        return sar_analyzer_all_obj->date_block_devices_highest.areqsz_time[x];
    else if (strcmp("util", element) == 0)
        return sar_analyzer_all_obj->date_block_devices_highest.util_time[x];
    else
        return "error";
}

const char *get_network_highest_time(int x, const char *element)
{
    if (strcmp("rxpck", element) == 0)
        return sar_analyzer_all_obj->date_networks_highest.rxpck_time[x];
    else if (strcmp("txpck", element) == 0)
        return sar_analyzer_all_obj->date_networks_highest.txpck_time[x];
    else if (strcmp("rxkb", element) == 0)
        return sar_analyzer_all_obj->date_networks_highest.rxkb_time[x];
    else if (strcmp("txkb", element) == 0)
        return sar_analyzer_all_obj->date_networks_highest.txkb_time[x];
    else if (strcmp("rxerr", element) == 0)
        return sar_analyzer_all_obj->date_networks_highest.rxerr_time[x];
    else if (strcmp("txerr", element) == 0)
        return sar_analyzer_all_obj->date_networks_highest.txerr_time[x];
    else if (strcmp("rxdrop", element) == 0)
        return sar_analyzer_all_obj->date_networks_highest.rxdrop_time[x];
    else if (strcmp("txdrop", element) == 0)
        return sar_analyzer_all_obj->date_networks_highest.txdrop_time[x];
    else
        return "error";
}

/* -- lowest val(for sar_analyzer_all_obj) -- */
/* -- object should be sar_analyzer_all_obj -- */

double get_cpu_lowest_val(int x, const char *element)
{
    if (strcmp("usr", element) == 0)
        return sar_analyzer_all_obj->cpus_lowest.cpu_usr_val[x];
    else if (strcmp("sys", element) == 0)
        return sar_analyzer_all_obj->cpus_lowest.cpu_sys_val[x];
    else if (strcmp("iowait", element) == 0)
        return sar_analyzer_all_obj->cpus_lowest.cpu_iowait_val[x];
    else if (strcmp("idle", element) == 0)
        return sar_analyzer_all_obj->cpus_lowest.cpu_idle_val[x];
    else
        return EXIT_FAILURE;
}

double get_tasks_lowest_val(const char *element)
{
    if (strcmp("proc", element) == 0)
        return sar_analyzer_all_obj->tasks_lowest.proc_val;
    else if (strcmp("cswch", element) == 0)
        return sar_analyzer_all_obj->tasks_lowest.cswch_val;
    else
        return EXIT_FAILURE;
}

double get_pswap_lowest_val(const char *element)
{
    if (strcmp("pswpin", element) == 0)
        return sar_analyzer_all_obj->pswaps_lowest.pswpin_val;
    else if (strcmp("pswpout", element) == 0)
        return sar_analyzer_all_obj->pswaps_lowest.pswpout_val;
    else
        return EXIT_FAILURE;
}

double get_paging_lowest_val(const char *element)
{
    if (strcmp("pgpgin", element) == 0)
        return sar_analyzer_all_obj->pagings_lowest.pgpgin_val;
    else if (strcmp("pgpgout", element) == 0)
        return sar_analyzer_all_obj->pagings_lowest.pgpgout_val;
    else if (strcmp("fault", element) == 0)
        return sar_analyzer_all_obj->pagings_lowest.fault_val;
    else if (strcmp("majflt", element) == 0)
        return sar_analyzer_all_obj->pagings_lowest.majflt_val;
    else if (strcmp("vmeff", element) == 0)
        return sar_analyzer_all_obj->pagings_lowest.vmeff_val;
    else
        return EXIT_FAILURE;
}

double get_io_transfer_rate_lowest_val(const char *element)
{
    if (strcmp("tps", element) == 0)
        return sar_analyzer_all_obj->io_transfer_rates_lowest.tps_val;
    else if (strcmp("bread", element) == 0)
        return sar_analyzer_all_obj->io_transfer_rates_lowest.bread_val;
    else if (strcmp("bwrtn", element) == 0)
        return sar_analyzer_all_obj->io_transfer_rates_lowest.bwrtn_val;
    else
        return EXIT_FAILURE;
}

double get_memory_lowest_val(const char *element)
{
    if (strcmp("memused", element) == 0)
        return sar_analyzer_all_obj->memories_lowest.memused_val;
    else if (strcmp("kbcommit", element) == 0)
        return sar_analyzer_all_obj->memories_lowest.kbcommit_val;
    else if (strcmp("commit", element) == 0)
        return sar_analyzer_all_obj->memories_lowest.commit_val;
    else
        return EXIT_FAILURE;
}

double get_swpused_lowest_val(void)
{
    return sar_analyzer_all_obj->swaps_lowest.swpused_val;
}

int get_kernel_table_lowest_val(const char *element)
{
    if (strcmp("dentunusd", element) == 0)
        return sar_analyzer_all_obj->kernel_tables_lowest.dentunusd_val;
    else if (strcmp("file", element) == 0)
        return sar_analyzer_all_obj->kernel_tables_lowest.file_val;
    else if (strcmp("inode", element) == 0)
        return sar_analyzer_all_obj->kernel_tables_lowest.inode_val;
    else
        return EXIT_FAILURE;
}

double get_ldavg_lowest_val(const char *element)
{
    if (strcmp("runq_sz", element) == 0)
        return sar_analyzer_all_obj->ldavgs_lowest.runq_sz_val;
    else if (strcmp("plist_sz", element) == 0)
        return sar_analyzer_all_obj->ldavgs_lowest.plist_sz_val;
    else if (strcmp("ldavg_one", element) == 0)
        return sar_analyzer_all_obj->ldavgs_lowest.ldavg_one_val;
    else if (strcmp("ldavg_five", element) == 0)
        return sar_analyzer_all_obj->ldavgs_lowest.ldavg_five_val;
    else if (strcmp("ldavg_15", element) == 0)
        return sar_analyzer_all_obj->ldavgs_lowest.ldavg_15_val;
    else
        return EXIT_FAILURE;
}

double get_block_device_lowest_val(int x, const char *element)
{
    if (strcmp("areqsz", element) == 0)
        return sar_analyzer_all_obj->block_devices_lowest.areqsz_val[x];
    else if (strcmp("util", element) == 0)
        return sar_analyzer_all_obj->block_devices_lowest.util_val[x];
    else
        return EXIT_FAILURE;
}

double get_network_lowest_val(int x, const char *element)
{
    if (strcmp("rxpck", element) == 0)
        return sar_analyzer_all_obj->networks_lowest.rxpck_val[x];
    else if (strcmp("txpck", element) == 0)
        return sar_analyzer_all_obj->networks_lowest.txpck_val[x];
    else if (strcmp("rxkb", element) == 0)
        return sar_analyzer_all_obj->networks_lowest.rxkb_val[x];
    else if (strcmp("txkb", element) == 0)
        return sar_analyzer_all_obj->networks_lowest.txkb_val[x];
    else if (strcmp("rxerr", element) == 0)
        return sar_analyzer_all_obj->networks_lowest.rxerr_val[x];
    else if (strcmp("txerr", element) == 0)
        return sar_analyzer_all_obj->networks_lowest.txerr_val[x];
    else if (strcmp("rxdrop", element) == 0)
        return sar_analyzer_all_obj->networks_lowest.rxdrop_val[x];
    else if (strcmp("txdrop", element) == 0)
        return sar_analyzer_all_obj->networks_lowest.txdrop_val[x];
    else
        return EXIT_FAILURE;
}

/* -- avg_lowest date(for sar_analyzer_obj) -- */

const char *get_cpu_avg_lowest_date(int x, const char *element)
{
    if (strcmp("usr", element) == 0)
        return sar_analyzer_obj->date_cpus_avg_lowest.cpu_usr_date[x];
    else if (strcmp("sys", element) == 0)
        return sar_analyzer_obj->date_cpus_avg_lowest.cpu_sys_date[x];
    else if (strcmp("iowait", element) == 0)
        return sar_analyzer_obj->date_cpus_avg_lowest.cpu_iowait_date[x];
    else if (strcmp("idle", element) == 0)
        return sar_analyzer_obj->date_cpus_avg_lowest.cpu_idle_date[x];
    else
        return "error";
}

const char *get_tasks_avg_lowest_date(const char *element)
{
    if (strcmp("proc", element) == 0)
        return sar_analyzer_obj->date_tasks_avg_lowest.proc_date;
    else if (strcmp("cswch", element) == 0)
        return sar_analyzer_obj->date_tasks_avg_lowest.cswch_date;
    else
        return "error";
}

const char *get_pswap_avg_lowest_date(const char *element)
{
    if (strcmp("pswpin", element) == 0)
        return sar_analyzer_obj->date_pswaps_avg_lowest.pswpin_date;
    else if (strcmp("pswpout", element) == 0)
        return sar_analyzer_obj->date_pswaps_avg_lowest.pswpout_date;
    else
        return "error";
}

const char *get_paging_avg_lowest_date(const char *element)
{
    if (strcmp("pgpgin", element) == 0)
        return sar_analyzer_obj->date_pagings_avg_lowest.pgpgin_date;
    else if (strcmp("pgpgout", element) == 0)
        return sar_analyzer_obj->date_pagings_avg_lowest.pgpgout_date;
    else if (strcmp("fault", element) == 0)
        return sar_analyzer_obj->date_pagings_avg_lowest.fault_date;
    else if (strcmp("majflt", element) == 0)
        return sar_analyzer_obj->date_pagings_avg_lowest.majflt_date;
    else if (strcmp("vmeff", element) == 0)
        return sar_analyzer_obj->date_pagings_avg_lowest.vmeff_date;
    else
        return "error";
}

const char *get_io_transfer_rate_avg_lowest_date(const char *element)
{
    if (strcmp("tps", element) == 0)
        return sar_analyzer_obj->date_io_transfer_rates_avg_lowest.tps_date;
    else if (strcmp("bread", element) == 0)
       return sar_analyzer_obj->date_io_transfer_rates_avg_lowest.bread_date;
    else if (strcmp("bwrtn", element) == 0)
        return sar_analyzer_obj->date_io_transfer_rates_avg_lowest.bwrtn_date;
    else
        return "error";
}

const char *get_memory_avg_lowest_date(const char *element)
{
    if (strcmp("memused", element) == 0)
        return sar_analyzer_obj->date_memories_avg_lowest.memused_date;
    else if (strcmp("kbcommit", element) == 0)
        return sar_analyzer_obj->date_memories_avg_lowest.kbcommit_date;
    else if (strcmp("commit", element) == 0)
        return sar_analyzer_obj->date_memories_avg_lowest.commit_date;
    else
        return "error";
}

const char *get_swpused_avg_lowest_date(void)
{
    return sar_analyzer_obj->date_swaps_avg_lowest.swpused_date;
}

const char *get_kernel_table_avg_lowest_date(const char *element)
{
    if (strcmp("dentunusd", element) == 0)
        return sar_analyzer_obj->date_kernel_tables_avg_lowest.dentunusd_date;
    else if (strcmp("file", element) == 0)
        return sar_analyzer_obj->date_kernel_tables_avg_lowest.file_date;
    else if (strcmp("inode", element) == 0)
        return sar_analyzer_obj->date_kernel_tables_avg_lowest.inode_date;
    else
        return "error";
}

const char *get_ldavg_avg_lowest_date(const char *element)
{
    if (strcmp("runq_sz", element) == 0)
        return sar_analyzer_obj->date_ldavgs_avg_lowest.runq_sz_date;
    else if (strcmp("plist_sz", element) == 0)
        return sar_analyzer_obj->date_ldavgs_avg_lowest.plist_sz_date;
    else if (strcmp("ldavg_one", element) == 0)
        return sar_analyzer_obj->date_ldavgs_avg_lowest.ldavg_one_date;
    else if (strcmp("ldavg_five", element) == 0)
        return sar_analyzer_obj->date_ldavgs_avg_lowest.ldavg_five_date;
    else if (strcmp("ldavg_15", element) == 0)
        return sar_analyzer_obj->date_ldavgs_avg_lowest.ldavg_15_date;
    else
        return "error";
}

const char *get_block_device_avg_lowest_date(int x, const char *element)
{
    if (strcmp("areqsz", element) == 0)
        return sar_analyzer_obj->date_block_devices_avg_lowest.areqsz_date[x];
    else if (strcmp("util", element) == 0)
        return sar_analyzer_obj->date_block_devices_avg_lowest.util_date[x];
    else
        return "error";
}

const char *get_network_avg_lowest_date(int x, const char *element)
{
    if (strcmp("rxpck", element) == 0)
        return sar_analyzer_obj->date_networks_avg_lowest.rxpck_date[x];
    else if (strcmp("txpck", element) == 0)
        return sar_analyzer_obj->date_networks_avg_lowest.txpck_date[x];
    else if (strcmp("rxkb", element) == 0)
        return sar_analyzer_obj->date_networks_avg_lowest.rxkb_date[x];
    else if (strcmp("txkb", element) == 0)
        return sar_analyzer_obj->date_networks_avg_lowest.txkb_date[x];
    else if (strcmp("rxerr", element) == 0)
        return sar_analyzer_obj->date_networks_avg_lowest.rxerr_date[x];
    else if (strcmp("txerr", element) == 0)
        return sar_analyzer_obj->date_networks_avg_lowest.txerr_date[x];
    else if (strcmp("rxdrop", element) == 0)
        return sar_analyzer_obj->date_networks_avg_lowest.rxdrop_date[x];
    else if (strcmp("txdrop", element) == 0)
        return sar_analyzer_obj->date_networks_avg_lowest.txdrop_date[x];
    else
        return "error";
}

/* -- lowest date(for sar_analyzer_all_obj) -- */
/* -- object should be sar_analyzer_all_obj -- */

const char *get_cpu_lowest_date(int x, const char *element)
{
    if (strcmp("usr", element) == 0)
        return sar_analyzer_all_obj->date_cpus_lowest.cpu_usr_date[x];
    else if (strcmp("sys", element) == 0)
        return sar_analyzer_all_obj->date_cpus_lowest.cpu_sys_date[x];
    else if (strcmp("iowait", element) == 0)
        return sar_analyzer_all_obj->date_cpus_lowest.cpu_iowait_date[x];
    else if (strcmp("idle", element) == 0)
        return sar_analyzer_all_obj->date_cpus_lowest.cpu_idle_date[x];
    else
        return "error";
}

const char *get_tasks_lowest_date(const char *element)
{
    if (strcmp("proc", element) == 0)
        return sar_analyzer_all_obj->date_tasks_lowest.proc_date;
    else if (strcmp("cswch", element) == 0)
        return sar_analyzer_all_obj->date_tasks_lowest.cswch_date;
    else
        return "error";
}

const char *get_pswap_lowest_date(const char *element)
{
    if (strcmp("pswpin", element) == 0)
        return sar_analyzer_all_obj->date_pswaps_lowest.pswpin_date;
    else if (strcmp("pswpout", element) == 0)
        return sar_analyzer_all_obj->date_pswaps_lowest.pswpout_date;
    else
        return "error";
}

const char *get_paging_lowest_date(const char *element)
{
    if (strcmp("pgpgin", element) == 0)
        return sar_analyzer_all_obj->date_pagings_lowest.pgpgin_date;
    else if (strcmp("pgpgout", element) == 0)
        return sar_analyzer_all_obj->date_pagings_lowest.pgpgout_date;
    else if (strcmp("fault", element) == 0)
        return sar_analyzer_all_obj->date_pagings_lowest.fault_date;
    else if (strcmp("majflt", element) == 0)
        return sar_analyzer_all_obj->date_pagings_lowest.majflt_date;
    else if (strcmp("vmeff", element) == 0)
        return sar_analyzer_all_obj->date_pagings_lowest.vmeff_date;
    else
        return "error";
}

const char *get_io_transfer_rate_lowest_date(const char *element)
{
    if (strcmp("tps", element) == 0)
        return sar_analyzer_all_obj->date_io_transfer_rates_lowest.tps_date;
    else if (strcmp("bread", element) == 0)
        return sar_analyzer_all_obj->date_io_transfer_rates_lowest.bread_date;
    else if (strcmp("bwrtn", element) == 0)
        return sar_analyzer_all_obj->date_io_transfer_rates_lowest.bwrtn_date;
    else
        return "error";
}

const char *get_memory_lowest_date(const char *element)
{
    if (strcmp("memused", element) == 0)
        return sar_analyzer_all_obj->date_memories_lowest.memused_date;
    else if (strcmp("kbcommit", element) == 0)
        return sar_analyzer_all_obj->date_memories_lowest.kbcommit_date;
    else if (strcmp("commit", element) == 0)
        return sar_analyzer_all_obj->date_memories_lowest.commit_date;
    else
        return "error";
}

const char *get_swpused_lowest_date(void)
{
    return sar_analyzer_all_obj->date_swaps_lowest.swpused_date;
}

const char *get_kernel_table_lowest_date(const char *element)
{
    if (strcmp("dentunusd", element) == 0)
        return sar_analyzer_all_obj->date_kernel_tables_lowest.dentunusd_date;
    else if (strcmp("file", element) == 0)
        return sar_analyzer_all_obj->date_kernel_tables_lowest.file_date;
    else if (strcmp("inode", element) == 0)
        return sar_analyzer_all_obj->date_kernel_tables_lowest.inode_date;
    else
        return "error";
}

const char *get_ldavg_lowest_date(const char *element)
{
    if (strcmp("runq_sz", element) == 0)
        return sar_analyzer_all_obj->date_ldavgs_lowest.runq_sz_date;
    else if (strcmp("plist_sz", element) == 0)
        return sar_analyzer_all_obj->date_ldavgs_lowest.plist_sz_date;
    else if (strcmp("ldavg_one", element) == 0)
        return sar_analyzer_all_obj->date_ldavgs_lowest.ldavg_one_date;
    else if (strcmp("ldavg_five", element) == 0)
        return sar_analyzer_all_obj->date_ldavgs_lowest.ldavg_five_date;
    else if (strcmp("ldavg_15", element) == 0)
        return sar_analyzer_all_obj->date_ldavgs_lowest.ldavg_15_date;
    else
        return "error";
}

const char *get_block_device_lowest_date(int x, const char *element)
{
    if (strcmp("areqsz", element) == 0)
        return sar_analyzer_all_obj->date_block_devices_lowest.areqsz_date[x];
    else if (strcmp("util", element) == 0)
        return sar_analyzer_all_obj->date_block_devices_lowest.util_date[x];
    else
        return "error";
}

const char *get_network_lowest_date(int x, const char *element)
{
    if (strcmp("rxpck", element) == 0)
        return sar_analyzer_all_obj->date_networks_lowest.rxpck_date[x];
    else if (strcmp("txpck", element) == 0)
        return sar_analyzer_all_obj->date_networks_lowest.txpck_date[x];
    else if (strcmp("rxkb", element) == 0)
        return sar_analyzer_all_obj->date_networks_lowest.rxkb_date[x];
    else if (strcmp("txkb", element) == 0)
        return sar_analyzer_all_obj->date_networks_lowest.txkb_date[x];
    else if (strcmp("rxerr", element) == 0)
        return sar_analyzer_all_obj->date_networks_lowest.rxerr_date[x];
    else if (strcmp("txerr", element) == 0)
        return sar_analyzer_all_obj->date_networks_lowest.txerr_date[x];
    else if (strcmp("rxdrop", element) == 0)
        return sar_analyzer_all_obj->date_networks_lowest.rxdrop_date[x];
    else if (strcmp("txdrop", element) == 0)
        return sar_analyzer_all_obj->date_networks_lowest.txdrop_date[x];
    else
        return "error";
}

/* -- lowest time(for sar_analyzer_all_obj) -- */
/* -- object should be sar_analyzer_all_obj -- */

const char *get_cpu_lowest_time(int x, const char *element)
{
    if (strcmp("usr", element) == 0)
        return sar_analyzer_all_obj->date_cpus_lowest.cpu_usr_time[x];
    else if (strcmp("sys", element) == 0)
        return sar_analyzer_all_obj->date_cpus_lowest.cpu_sys_time[x];
    else if (strcmp("iowait", element) == 0)
        return sar_analyzer_all_obj->date_cpus_lowest.cpu_iowait_time[x];
    else if (strcmp("idle", element) == 0)
        return sar_analyzer_all_obj->date_cpus_lowest.cpu_idle_time[x];
    else
        return "error";
}

const char *get_tasks_lowest_time(const char *element)
{
    if (strcmp("proc", element) == 0)
        return sar_analyzer_all_obj->date_tasks_lowest.proc_time;
    else if (strcmp("cswch", element) == 0)
        return sar_analyzer_all_obj->date_tasks_lowest.cswch_time;
    else
        return "error";
}

const char *get_pswap_lowest_time(const char *element)
{
    if (strcmp("pswpin", element) == 0)
        return sar_analyzer_all_obj->date_pswaps_lowest.pswpin_time;
    else if (strcmp("pswpout", element) == 0)
        return sar_analyzer_all_obj->date_pswaps_lowest.pswpout_time;
    else
        return "error";
}

const char *get_paging_lowest_time(const char *element)
{
    if (strcmp("pgpgin", element) == 0)
        return sar_analyzer_all_obj->date_pagings_lowest.pgpgin_time;
    else if (strcmp("pgpgout", element) == 0)
        return sar_analyzer_all_obj->date_pagings_lowest.pgpgout_time;
    else if (strcmp("fault", element) == 0)
        return sar_analyzer_all_obj->date_pagings_lowest.fault_time;
    else if (strcmp("majflt", element) == 0)
        return sar_analyzer_all_obj->date_pagings_lowest.majflt_time;
    else if (strcmp("vmeff", element) == 0)
        return sar_analyzer_all_obj->date_pagings_lowest.vmeff_time;
    else
        return "error";
}

const char *get_io_transfer_rate_lowest_time(const char *element)
{
    if (strcmp("tps", element) == 0)
        return sar_analyzer_all_obj->date_io_transfer_rates_lowest.tps_time;
    else if (strcmp("bread", element) == 0)
        return sar_analyzer_all_obj->date_io_transfer_rates_lowest.bread_time;
    else if (strcmp("bwrtn", element) == 0)
        return sar_analyzer_all_obj->date_io_transfer_rates_lowest.bwrtn_time;
    else
        return "error";
}

const char *get_memory_lowest_time(const char *element)
{
    if (strcmp("memused", element) == 0)
        return sar_analyzer_all_obj->date_memories_lowest.memused_time;
    else if (strcmp("kbcommit", element) == 0)
        return sar_analyzer_all_obj->date_memories_lowest.kbcommit_time;
    else if (strcmp("commit", element) == 0)
        return sar_analyzer_all_obj->date_memories_lowest.commit_time;
    else
        return "error";
}

const char *get_swpused_lowest_time(void)
{
    return sar_analyzer_all_obj->date_swaps_lowest.swpused_time;
}

const char *get_kernel_table_lowest_time(const char *element)
{
    if (strcmp("dentunusd", element) == 0)
        return sar_analyzer_all_obj->date_kernel_tables_lowest.dentunusd_time;
    else if (strcmp("file", element) == 0)
        return sar_analyzer_all_obj->date_kernel_tables_lowest.file_time;
    else if (strcmp("inode", element) == 0)
        return sar_analyzer_all_obj->date_kernel_tables_lowest.inode_time;
    else
        return "error";
}

const char *get_ldavg_lowest_time(const char *element)
{
    if (strcmp("runq_sz", element) == 0)
        return sar_analyzer_all_obj->date_ldavgs_lowest.runq_sz_time;
    else if (strcmp("plist_sz", element) == 0)
        return sar_analyzer_all_obj->date_ldavgs_lowest.plist_sz_time;
    else if (strcmp("ldavg_one", element) == 0)
        return sar_analyzer_all_obj->date_ldavgs_lowest.ldavg_one_time;
    else if (strcmp("ldavg_five", element) == 0)
        return sar_analyzer_all_obj->date_ldavgs_lowest.ldavg_five_time;
    else if (strcmp("ldavg_15", element) == 0)
        return sar_analyzer_all_obj->date_ldavgs_lowest.ldavg_15_time;
    else
        return "error";
}

const char *get_block_device_lowest_time(int x, const char *element)
{
    if (strcmp("areqsz", element) == 0)
        return sar_analyzer_all_obj->date_block_devices_lowest.areqsz_time[x];
    else if (strcmp("util", element) == 0)
        return sar_analyzer_all_obj->date_block_devices_lowest.util_time[x];
    else
        return "error";
}

const char *get_network_lowest_time(int x, const char *element)
{
    if (strcmp("rxpck", element) == 0)
        return sar_analyzer_all_obj->date_networks_lowest.rxpck_time[x];
    else if (strcmp("txpck", element) == 0)
        return sar_analyzer_all_obj->date_networks_lowest.txpck_time[x];
    else if (strcmp("rxkb", element) == 0)
        return sar_analyzer_all_obj->date_networks_lowest.rxkb_time[x];
    else if (strcmp("txkb", element) == 0)
        return sar_analyzer_all_obj->date_networks_lowest.txkb_time[x];
    else if (strcmp("rxerr", element) == 0)
        return sar_analyzer_all_obj->date_networks_lowest.rxerr_time[x];
    else if (strcmp("txerr", element) == 0)
        return sar_analyzer_all_obj->date_networks_lowest.txerr_time[x];
    else if (strcmp("rxdrop", element) == 0)
        return sar_analyzer_all_obj->date_networks_lowest.rxdrop_time[x];
    else if (strcmp("txdrop", element) == 0)
        return sar_analyzer_all_obj->date_networks_lowest.txdrop_time[x];
    else
        return "error";
}

/* -- spike val -- */
/* -- object should be sar_analyzer_all_obj -- */

double get_cpu_spike_val(int x, const char *element)
{
    if (strcmp("usr", element) == 0)
        return sar_analyzer_all_obj->cpus_spike.cpu_usr_val[x];
    else if (strcmp("sys", element) == 0)
        return sar_analyzer_all_obj->cpus_spike.cpu_sys_val[x];
    else if (strcmp("iowait", element) == 0)
        return sar_analyzer_all_obj->cpus_spike.cpu_iowait_val[x];
    else if (strcmp("idle", element) == 0)
        return sar_analyzer_all_obj->cpus_spike.cpu_idle_val[x];
    else
        return EXIT_FAILURE;
}

double get_tasks_spike_val(const char *element)
{
    if (strcmp("proc", element) == 0)
        return sar_analyzer_all_obj->tasks_spike.proc_val;
    else if (strcmp("cswch", element) == 0)
        return sar_analyzer_all_obj->tasks_spike.cswch_val;
    else
        return EXIT_FAILURE;
}

double get_pswap_spike_val(const char *element)
{
    if (strcmp("pswpin", element) == 0)
        return sar_analyzer_all_obj->pswaps_spike.pswpin_val;
    else if (strcmp("pswpout", element) == 0)
        return sar_analyzer_all_obj->pswaps_spike.pswpout_val;
    else
        return EXIT_FAILURE;
}

double get_paging_spike_val(const char *element)
{
    if (strcmp("pgpgin", element) == 0)
        return sar_analyzer_all_obj->pagings_spike.pgpgin_val;
    else if (strcmp("pgpgout", element) == 0)
        return sar_analyzer_all_obj->pagings_spike.pgpgout_val;
    else if (strcmp("fault", element) == 0)
        return sar_analyzer_all_obj->pagings_spike.fault_val;
    else if (strcmp("majflt", element) == 0)
        return sar_analyzer_all_obj->pagings_spike.majflt_val;
    else if (strcmp("vmeff", element) == 0)
        return sar_analyzer_all_obj->pagings_spike.vmeff_val;
    else
        return EXIT_FAILURE;
}

double get_io_transfer_rate_spike_val(const char *element)
{
    if (strcmp("tps", element) == 0)
        return sar_analyzer_all_obj->io_transfer_rates_spike.tps_val;
    else if (strcmp("bread", element) == 0)
        return sar_analyzer_all_obj->io_transfer_rates_spike.bread_val;
    else if (strcmp("bwrtn", element) == 0)
        return sar_analyzer_all_obj->io_transfer_rates_spike.bwrtn_val;
    else
        return EXIT_FAILURE;
}

double get_memory_spike_val(const char *element)
{
    if (strcmp("memused", element) == 0)
        return sar_analyzer_all_obj->memories_spike.memused_val;
    else if (strcmp("kbcommit", element) == 0)
        return sar_analyzer_all_obj->memories_spike.kbcommit_val;
    else if (strcmp("commit", element) == 0)
        return sar_analyzer_all_obj->memories_spike.commit_val;
    else
        return EXIT_FAILURE;
}

double get_swpused_spike_val(void)
{
    return sar_analyzer_all_obj->swaps_spike.swpused_val;
}

int get_kernel_table_spike_val(const char *element)
{
    if (strcmp("dentunusd", element) == 0)
        return sar_analyzer_all_obj->kernel_tables_spike.dentunusd_val;
    else if (strcmp("file", element) == 0)
        return sar_analyzer_all_obj->kernel_tables_spike.file_val;
    else if (strcmp("inode", element) == 0)
        return sar_analyzer_all_obj->kernel_tables_spike.inode_val;
    else
        return EXIT_FAILURE;
}

double get_ldavg_spike_val(const char *element)
{
    if (strcmp("runq_sz", element) == 0)
        return sar_analyzer_all_obj->ldavgs_spike.runq_sz_val;
    else if (strcmp("plist_sz", element) == 0)
        return sar_analyzer_all_obj->ldavgs_spike.plist_sz_val;
    else if (strcmp("ldavg_one", element) == 0)
        return sar_analyzer_all_obj->ldavgs_spike.ldavg_one_val;
    else if (strcmp("ldavg_five", element) == 0)
        return sar_analyzer_all_obj->ldavgs_spike.ldavg_five_val;
    else if (strcmp("ldavg_15", element) == 0)
        return sar_analyzer_all_obj->ldavgs_spike.ldavg_15_val;
    else
        return EXIT_FAILURE;
}

double get_block_device_spike_val(int x, const char *element)
{
    if (strcmp("areqsz", element) == 0)
        return sar_analyzer_all_obj->block_devices_spike.areqsz_val[x];
    else if (strcmp("util", element) == 0)
        return sar_analyzer_all_obj->block_devices_spike.util_val[x];
    else
        return EXIT_FAILURE;
}

double get_network_spike_val(int x, const char *element)
{
    if (strcmp("rxpck", element) == 0)
        return sar_analyzer_all_obj->networks_spike.rxpck_val[x];
    else if (strcmp("txpck", element) == 0)
        return sar_analyzer_all_obj->networks_spike.txpck_val[x];
    else if (strcmp("rxkb", element) == 0)
        return sar_analyzer_all_obj->networks_spike.rxkb_val[x];
    else if (strcmp("txkb", element) == 0)
        return sar_analyzer_all_obj->networks_spike.txkb_val[x];
    else if (strcmp("rxerr", element) == 0)
        return sar_analyzer_all_obj->networks_spike.rxerr_val[x];
    else if (strcmp("txerr", element) == 0)
        return sar_analyzer_all_obj->networks_spike.txerr_val[x];
    else if (strcmp("rxdrop", element) == 0)
        return sar_analyzer_all_obj->networks_spike.rxdrop_val[x];
    else if (strcmp("txdrop", element) == 0)
        return sar_analyzer_all_obj->networks_spike.txdrop_val[x];
    else
        return EXIT_FAILURE;
}

/* -- spike date(for sar_analyzer_all_obj) -- */
/* -- object should be sar_analyzer_all_obj -- */

const char *get_cpu_spike_date(int x, const char *element)
{
    if (strcmp("usr", element) == 0)
        return sar_analyzer_all_obj->date_cpus_spike.cpu_usr_date[x];
    else if (strcmp("sys", element) == 0)
        return sar_analyzer_all_obj->date_cpus_spike.cpu_sys_date[x];
    else if (strcmp("iowait", element) == 0)
        return sar_analyzer_all_obj->date_cpus_spike.cpu_iowait_date[x];
    else if (strcmp("idle", element) == 0)
        return sar_analyzer_all_obj->date_cpus_spike.cpu_idle_date[x];
    else
        return "error";
}

const char *get_tasks_spike_date(const char *element)
{
    if (strcmp("proc", element) == 0)
        return sar_analyzer_all_obj->date_tasks_spike.proc_date;
    else if (strcmp("cswch", element) == 0)
        return sar_analyzer_all_obj->date_tasks_spike.cswch_date;
    else
        return "error";
}

const char *get_pswap_spike_date(const char *element)
{
    if (strcmp("pswpin", element) == 0)
        return sar_analyzer_all_obj->date_pswaps_spike.pswpin_date;
    else if (strcmp("pswpout", element) == 0)
        return sar_analyzer_all_obj->date_pswaps_spike.pswpout_date;
    else
        return "error";
}

const char *get_paging_spike_date(const char *element)
{
    if (strcmp("pgpgin", element) == 0)
        return sar_analyzer_all_obj->date_pagings_spike.pgpgin_date;
    else if (strcmp("pgpgout", element) == 0)
        return sar_analyzer_all_obj->date_pagings_spike.pgpgout_date;
    else if (strcmp("fault", element) == 0)
        return sar_analyzer_all_obj->date_pagings_spike.fault_date;
    else if (strcmp("majflt", element) == 0)
        return sar_analyzer_all_obj->date_pagings_spike.majflt_date;
    else if (strcmp("vmeff", element) == 0)
        return sar_analyzer_all_obj->date_pagings_spike.vmeff_date;
    else
        return "error";
}

const char *get_io_transfer_rate_spike_date(const char *element)
{
    if (strcmp("tps", element) == 0)
        return sar_analyzer_all_obj->date_io_transfer_rates_spike.tps_date;
    else if (strcmp("bread", element) == 0)
        return sar_analyzer_all_obj->date_io_transfer_rates_spike.bread_date;
    else if (strcmp("bwrtn", element) == 0)
        return sar_analyzer_all_obj->date_io_transfer_rates_spike.bwrtn_date;
    else
        return "error";
}

const char *get_memory_spike_date(const char *element)
{
    if (strcmp("memused", element) == 0)
        return sar_analyzer_all_obj->date_memories_spike.memused_date;
    else if (strcmp("kbcommit", element) == 0)
        return sar_analyzer_all_obj->date_memories_spike.kbcommit_date;
    else if (strcmp("commit", element) == 0)
        return sar_analyzer_all_obj->date_memories_spike.commit_date;
    else
        return "error";
}

const char *get_swpused_spike_date(void)
{
    return sar_analyzer_all_obj->date_swaps_spike.swpused_date;
}

const char *get_kernel_table_spike_date(const char *element)
{
    if (strcmp("dentunusd", element) == 0)
        return sar_analyzer_all_obj->date_kernel_tables_spike.dentunusd_date;
    else if (strcmp("file", element) == 0)
        return sar_analyzer_all_obj->date_kernel_tables_spike.file_date;
    else if (strcmp("inode", element) == 0)
        return sar_analyzer_all_obj->date_kernel_tables_spike.inode_date;
    else
        return "error";
}

const char *get_ldavg_spike_date(const char *element)
{
    if (strcmp("runq_sz", element) == 0)
        return sar_analyzer_all_obj->date_ldavgs_spike.runq_sz_date;
    else if (strcmp("plist_sz", element) == 0)
        return sar_analyzer_all_obj->date_ldavgs_spike.plist_sz_date;
    else if (strcmp("ldavg_one", element) == 0)
        return sar_analyzer_all_obj->date_ldavgs_spike.ldavg_one_date;
    else if (strcmp("ldavg_five", element) == 0)
        return sar_analyzer_all_obj->date_ldavgs_spike.ldavg_five_date;
    else if (strcmp("ldavg_15", element) == 0)
        return sar_analyzer_all_obj->date_ldavgs_spike.ldavg_15_date;
    else
        return "error";
}

const char *get_block_device_spike_date(int x, const char *element)
{
    if (strcmp("areqsz", element) == 0)
        return sar_analyzer_all_obj->date_block_devices_spike.areqsz_date[x];
    else if (strcmp("util", element) == 0)
        return sar_analyzer_all_obj->date_block_devices_spike.util_date[x];
    else
        return "error";
}

const char *get_network_spike_date(int x, const char *element)
{
    if (strcmp("rxpck", element) == 0)
        return sar_analyzer_all_obj->date_networks_spike.rxpck_date[x];
    else if (strcmp("txpck", element) == 0)
        return sar_analyzer_all_obj->date_networks_spike.txpck_date[x];
    else if (strcmp("rxkb", element) == 0)
        return sar_analyzer_all_obj->date_networks_spike.rxkb_date[x];
    else if (strcmp("txkb", element) == 0)
        return sar_analyzer_all_obj->date_networks_spike.txkb_date[x];
    else if (strcmp("rxerr", element) == 0)
        return sar_analyzer_all_obj->date_networks_spike.rxerr_date[x];
    else if (strcmp("txerr", element) == 0)
        return sar_analyzer_all_obj->date_networks_spike.txerr_date[x];
    else if (strcmp("rxdrop", element) == 0)
        return sar_analyzer_all_obj->date_networks_spike.rxdrop_date[x];
    else if (strcmp("txdrop", element) == 0)
        return sar_analyzer_all_obj->date_networks_spike.txdrop_date[x];
    else
        return "error";
}

/* -- spike time(for sar_analyzer_all_obj) -- */
/* -- object should be sar_analyzer_all_obj -- */

const char *get_cpu_spike_time(int x, const char *element)
{
    if (strcmp("usr", element) == 0)
        return sar_analyzer_all_obj->date_cpus_spike.cpu_usr_time[x];
    else if (strcmp("sys", element) == 0)
        return sar_analyzer_all_obj->date_cpus_spike.cpu_sys_time[x];
    else if (strcmp("iowait", element) == 0)
        return sar_analyzer_all_obj->date_cpus_spike.cpu_iowait_time[x];
    else if (strcmp("idle", element) == 0)
        return sar_analyzer_all_obj->date_cpus_spike.cpu_idle_time[x];
    else
        return "error";
}

const char *get_tasks_spike_time(const char *element)
{
    if (strcmp("proc", element) == 0)
        return sar_analyzer_all_obj->date_tasks_spike.proc_time;
    else if (strcmp("cswch", element) == 0)
        return sar_analyzer_all_obj->date_tasks_spike.cswch_time;
    else
        return "error";
}

const char *get_pswap_spike_time(const char *element)
{
    if (strcmp("pswpin", element) == 0)
        return sar_analyzer_all_obj->date_pswaps_spike.pswpin_time;
    else if (strcmp("pswpout", element) == 0)
        return sar_analyzer_all_obj->date_pswaps_spike.pswpout_time;
    else
        return "error";
}

const char *get_paging_spike_time(const char *element)
{
    if (strcmp("pgpgin", element) == 0)
        return sar_analyzer_all_obj->date_pagings_spike.pgpgin_time;
    else if (strcmp("pgpgout", element) == 0)
        return sar_analyzer_all_obj->date_pagings_spike.pgpgout_time;
    else if (strcmp("fault", element) == 0)
        return sar_analyzer_all_obj->date_pagings_spike.fault_time;
    else if (strcmp("majflt", element) == 0)
        return sar_analyzer_all_obj->date_pagings_spike.majflt_time;
    else if (strcmp("vmeff", element) == 0)
        return sar_analyzer_all_obj->date_pagings_spike.vmeff_time;
    else
        return "error";
}

const char *get_io_transfer_rate_spike_time(const char *element)
{
    if (strcmp("tps", element) == 0)
        return sar_analyzer_all_obj->date_io_transfer_rates_spike.tps_time;
    else if (strcmp("bread", element) == 0)
        return sar_analyzer_all_obj->date_io_transfer_rates_spike.bread_time;
    else if (strcmp("bwrtn", element) == 0)
        return sar_analyzer_all_obj->date_io_transfer_rates_spike.bwrtn_time;
    else
        return "error";
}

const char *get_memory_spike_time(const char *element)
{
    if (strcmp("memused", element) == 0)
        return sar_analyzer_all_obj->date_memories_spike.memused_time;
    else if (strcmp("kbcommit", element) == 0)
        return sar_analyzer_all_obj->date_memories_spike.kbcommit_time;
    else if (strcmp("commit", element) == 0)
        return sar_analyzer_all_obj->date_memories_spike.commit_time;
    else
        return "error";
}

const char *get_swpused_spike_time(void)
{
    return sar_analyzer_all_obj->date_swaps_spike.swpused_time;
}

const char *get_kernel_table_spike_time(const char *element)
{
    if (strcmp("dentunusd", element) == 0)
        return sar_analyzer_all_obj->date_kernel_tables_spike.dentunusd_time;
    else if (strcmp("file", element) == 0)
        return sar_analyzer_all_obj->date_kernel_tables_spike.file_time;
    else if (strcmp("inode", element) == 0)
        return sar_analyzer_all_obj->date_kernel_tables_spike.inode_time;
    else
        return "error";
}

const char *get_ldavg_spike_time(const char *element)
{
    if (strcmp("runq_sz", element) == 0)
        return sar_analyzer_all_obj->date_ldavgs_spike.runq_sz_time;
    else if (strcmp("plist_sz", element) == 0)
        return sar_analyzer_all_obj->date_ldavgs_spike.plist_sz_time;
    else if (strcmp("ldavg_one", element) == 0)
        return sar_analyzer_all_obj->date_ldavgs_spike.ldavg_one_time;
    else if (strcmp("ldavg_five", element) == 0)
        return sar_analyzer_all_obj->date_ldavgs_spike.ldavg_five_time;
    else if (strcmp("ldavg_15", element) == 0)
        return sar_analyzer_all_obj->date_ldavgs_spike.ldavg_15_time;
    else
        return "error";
}

const char *get_block_device_spike_time(int x, const char *element)
{
    if (strcmp("areqsz", element) == 0)
        return sar_analyzer_all_obj->date_block_devices_spike.areqsz_time[x];
    else if (strcmp("util", element) == 0)
        return sar_analyzer_all_obj->date_block_devices_spike.util_time[x];
    else
        return "error";
}

const char *get_network_spike_time(int x, const char *element)
{
    if (strcmp("rxpck", element) == 0)
        return sar_analyzer_all_obj->date_networks_spike.rxpck_time[x];
    else if (strcmp("txpck", element) == 0)
        return sar_analyzer_all_obj->date_networks_spike.txpck_time[x];
    else if (strcmp("rxkb", element) == 0)
        return sar_analyzer_all_obj->date_networks_spike.rxkb_time[x];
    else if (strcmp("txkb", element) == 0)
        return sar_analyzer_all_obj->date_networks_spike.txkb_time[x];
    else if (strcmp("rxerr", element) == 0)
        return sar_analyzer_all_obj->date_networks_spike.rxerr_time[x];
    else if (strcmp("txerr", element) == 0)
        return sar_analyzer_all_obj->date_networks_spike.txerr_time[x];
    else if (strcmp("rxdrop", element) == 0)
        return sar_analyzer_all_obj->date_networks_spike.rxdrop_time[x];
    else if (strcmp("txdrop", element) == 0)
        return sar_analyzer_all_obj->date_networks_spike.txdrop_time[x];
    else
        return "error";
}

/* -- spike date each file -- */
/* -- object should be sar_analyzer_spike_obj -- */

const char *get_cpu_spike_date_each_file(int x, int y, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("usr", element) == 0)
            return sar_analyzer_spike_obj->date_cpus_spike_each_file.cpu_usr_spike_date_each_file[x][y];
        else if (strcmp("sys", element) == 0)
            return sar_analyzer_spike_obj->date_cpus_spike_each_file.cpu_sys_spike_date_each_file[x][y];
        else if (strcmp("iowait", element) == 0)
            return sar_analyzer_spike_obj->date_cpus_spike_each_file.cpu_iowait_spike_date_each_file[x][y];
        else if (strcmp("idle", element) == 0)
            return sar_analyzer_spike_obj->date_cpus_spike_each_file.cpu_idle_spike_date_each_file[x][y];
        else
            return "error";
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("usr", element) == 0)
            return sar_analyzer_spike_obj->date_cpus_spike_each_file.cpu_usr_highest_date_each_file[x][y];
        else if (strcmp("sys", element) == 0)
            return sar_analyzer_spike_obj->date_cpus_spike_each_file.cpu_sys_highest_date_each_file[x][y];
        else if (strcmp("iowait", element) == 0)
            return sar_analyzer_spike_obj->date_cpus_spike_each_file.cpu_iowait_highest_date_each_file[x][y];
        else if (strcmp("idle", element) == 0)
            return sar_analyzer_spike_obj->date_cpus_spike_each_file.cpu_idle_highest_date_each_file[x][y];
        else
            return "error";
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("usr", element) == 0)
            return sar_analyzer_spike_obj->date_cpus_spike_each_file.cpu_usr_lowest_date_each_file[x][y];
        else if (strcmp("sys", element) == 0)
            return sar_analyzer_spike_obj->date_cpus_spike_each_file.cpu_sys_lowest_date_each_file[x][y];
        else if (strcmp("iowait", element) == 0)
            return sar_analyzer_spike_obj->date_cpus_spike_each_file.cpu_iowait_lowest_date_each_file[x][y];
        else if (strcmp("idle", element) == 0)
            return sar_analyzer_spike_obj->date_cpus_spike_each_file.cpu_idle_lowest_date_each_file[x][y];
        else
            return "error";
    } else
        return "error";
}

const char *get_tasks_spike_date_each_file(int x, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("proc", element) == 0)
            return sar_analyzer_spike_obj->date_tasks_spike_each_file.proc_spike_date_each_file[x];
        else if (strcmp("cswch", element) == 0)
            return sar_analyzer_spike_obj->date_tasks_spike_each_file.cswch_spike_date_each_file[x];
        else
            return "error";
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("proc", element) == 0)
            return sar_analyzer_spike_obj->date_tasks_spike_each_file.proc_highest_date_each_file[x];
        else if (strcmp("cswch", element) == 0)
            return sar_analyzer_spike_obj->date_tasks_spike_each_file.cswch_highest_date_each_file[x];
        else
            return "error";
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("proc", element) == 0)
            return sar_analyzer_spike_obj->date_tasks_spike_each_file.proc_lowest_date_each_file[x];
        else if (strcmp("cswch", element) == 0)
            return sar_analyzer_spike_obj->date_tasks_spike_each_file.cswch_lowest_date_each_file[x];
        else
            return "error";
    } else
        return "error";
}

const char *get_pswap_spike_date_each_file(int x, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("pswpin", element) == 0)
            return sar_analyzer_spike_obj->date_pswaps_spike_each_file.pswpin_spike_date_each_file[x];
        else if (strcmp("pswpout", element) == 0)
            return sar_analyzer_spike_obj->date_pswaps_spike_each_file.pswpout_spike_date_each_file[x];
        else
            return "error";
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("pswpin", element) == 0)
            return sar_analyzer_spike_obj->date_pswaps_spike_each_file.pswpin_highest_date_each_file[x];
        else if (strcmp("pswpout", element) == 0)
            return sar_analyzer_spike_obj->date_pswaps_spike_each_file.pswpout_highest_date_each_file[x];
        else
            return "error";
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("pswpin", element) == 0)
            return sar_analyzer_spike_obj->date_pswaps_spike_each_file.pswpin_lowest_date_each_file[x];
        else if (strcmp("pswpout", element) == 0)
            return sar_analyzer_spike_obj->date_pswaps_spike_each_file.pswpout_lowest_date_each_file[x];
        else
            return "error";
    } else
        return "error";
}

const char *get_paging_spike_date_each_file(int x, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("pgpgin", element) == 0)
            return sar_analyzer_spike_obj->date_pagings_spike_each_file.pgpgin_spike_date_each_file[x];
        else if (strcmp("pgpgout", element) == 0)
            return sar_analyzer_spike_obj->date_pagings_spike_each_file.pgpgout_spike_date_each_file[x];
        else if (strcmp("fault", element) == 0)
            return sar_analyzer_spike_obj->date_pagings_spike_each_file.fault_spike_date_each_file[x];
        else if (strcmp("majflt", element) == 0)
            return sar_analyzer_spike_obj->date_pagings_spike_each_file.majflt_spike_date_each_file[x];
        else if (strcmp("vmeff", element) == 0)
            return sar_analyzer_spike_obj->date_pagings_spike_each_file.vmeff_spike_date_each_file[x];
        else
            return "error";
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("pgpgin", element) == 0)
            return sar_analyzer_spike_obj->date_pagings_spike_each_file.pgpgin_highest_date_each_file[x];
        else if (strcmp("pgpgout", element) == 0)
            return sar_analyzer_spike_obj->date_pagings_spike_each_file.pgpgout_highest_date_each_file[x];
        else if (strcmp("fault", element) == 0)
            return sar_analyzer_spike_obj->date_pagings_spike_each_file.fault_highest_date_each_file[x];
        else if (strcmp("majflt", element) == 0)
            return sar_analyzer_spike_obj->date_pagings_spike_each_file.majflt_highest_date_each_file[x];
        else if (strcmp("vmeff", element) == 0)
            return sar_analyzer_spike_obj->date_pagings_spike_each_file.vmeff_highest_date_each_file[x];
        else
            return "error";
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("pgpgin", element) == 0)
            return sar_analyzer_spike_obj->date_pagings_spike_each_file.pgpgin_lowest_date_each_file[x];
        else if (strcmp("pgpgout", element) == 0)
            return sar_analyzer_spike_obj->date_pagings_spike_each_file.pgpgout_lowest_date_each_file[x];
        else if (strcmp("fault", element) == 0)
            return sar_analyzer_spike_obj->date_pagings_spike_each_file.fault_lowest_date_each_file[x];
        else if (strcmp("majflt", element) == 0)
            return sar_analyzer_spike_obj->date_pagings_spike_each_file.majflt_lowest_date_each_file[x];
        else if (strcmp("vmeff", element) == 0)
            return sar_analyzer_spike_obj->date_pagings_spike_each_file.vmeff_lowest_date_each_file[x];
        else
            return "error";
    } else
        return "error";
}

const char *get_io_transfer_rate_spike_date_each_file(int x, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("tps", element) == 0)
            return sar_analyzer_spike_obj->date_io_transfer_rates_spike_each_file.tps_spike_date_each_file[x];
        else if (strcmp("bread", element) == 0)
            return sar_analyzer_spike_obj->date_io_transfer_rates_spike_each_file.bread_spike_date_each_file[x];
        else if (strcmp("bwrtn", element) == 0)
            return sar_analyzer_spike_obj->date_io_transfer_rates_spike_each_file.bwrtn_spike_date_each_file[x];
        else
            return "error";
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("tps", element) == 0)
            return sar_analyzer_spike_obj->date_io_transfer_rates_spike_each_file.tps_highest_date_each_file[x];
        else if (strcmp("bread", element) == 0)
            return sar_analyzer_spike_obj->date_io_transfer_rates_spike_each_file.bread_highest_date_each_file[x];
        else if (strcmp("bwrtn", element) == 0)
            return sar_analyzer_spike_obj->date_io_transfer_rates_spike_each_file.bwrtn_highest_date_each_file[x];
        else
            return "error";
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("tps", element) == 0)
            return sar_analyzer_spike_obj->date_io_transfer_rates_spike_each_file.tps_lowest_date_each_file[x];
        else if (strcmp("bread", element) == 0)
            return sar_analyzer_spike_obj->date_io_transfer_rates_spike_each_file.bread_lowest_date_each_file[x];
        else if (strcmp("bwrtn", element) == 0)
            return sar_analyzer_spike_obj->date_io_transfer_rates_spike_each_file.bwrtn_lowest_date_each_file[x];
        else
            return "error";
    } else
        return "error";
}

const char *get_memory_spike_date_each_file(int x, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("memused", element) == 0)
            return sar_analyzer_spike_obj->date_memories_spike_each_file.memused_spike_date_each_file[x];
        else if (strcmp("kbcommit", element) == 0)
            return sar_analyzer_spike_obj->date_memories_spike_each_file.kbcommit_spike_date_each_file[x];
        else if (strcmp("commit", element) == 0)
            return sar_analyzer_spike_obj->date_memories_spike_each_file.commit_spike_date_each_file[x];
        else
            return "error";
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("memused", element) == 0)
            return sar_analyzer_spike_obj->date_memories_spike_each_file.memused_highest_date_each_file[x];
        else if (strcmp("kbcommit", element) == 0)
            return sar_analyzer_spike_obj->date_memories_spike_each_file.kbcommit_highest_date_each_file[x];
        else if (strcmp("commit", element) == 0)
            return sar_analyzer_spike_obj->date_memories_spike_each_file.commit_highest_date_each_file[x];
        else
            return "error";
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("memused", element) == 0)
            return sar_analyzer_spike_obj->date_memories_spike_each_file.memused_lowest_date_each_file[x];
        else if (strcmp("kbcommit", element) == 0)
            return sar_analyzer_spike_obj->date_memories_spike_each_file.kbcommit_lowest_date_each_file[x];
        else if (strcmp("commit", element) == 0)
            return sar_analyzer_spike_obj->date_memories_spike_each_file.commit_lowest_date_each_file[x];
        else
            return "error";
    } else
        return "error";
}

const char *get_swpused_spike_date_each_file(int x, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0)
        return sar_analyzer_spike_obj->date_swaps_spike_each_file.swpused_spike_date_each_file[x];
    else if (strcmp("highest", analyze_item) == 0)
        return sar_analyzer_spike_obj->date_swaps_spike_each_file.swpused_highest_date_each_file[x];
    else if (strcmp("lowest", analyze_item) == 0)
        return sar_analyzer_spike_obj->date_swaps_spike_each_file.swpused_lowest_date_each_file[x];
    else
        return "error";
}

const char *get_kernel_table_spike_date_each_file(int x, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("dentunusd", element) == 0)
            return sar_analyzer_spike_obj->date_kernel_tables_spike_each_file.dentunusd_spike_date_each_file[x];
        else if (strcmp("file", element) == 0)
            return sar_analyzer_spike_obj->date_kernel_tables_spike_each_file.file_spike_date_each_file[x];
        else if (strcmp("inode", element) == 0)
            return sar_analyzer_spike_obj->date_kernel_tables_spike_each_file.inode_spike_date_each_file[x];
        else
            return "error";
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("dentunusd", element) == 0)
            return sar_analyzer_spike_obj->date_kernel_tables_spike_each_file.dentunusd_highest_date_each_file[x];
        else if (strcmp("file", element) == 0)
            return sar_analyzer_spike_obj->date_kernel_tables_spike_each_file.file_highest_date_each_file[x];
        else if (strcmp("inode", element) == 0)
            return sar_analyzer_spike_obj->date_kernel_tables_spike_each_file.inode_highest_date_each_file[x];
        else
            return "error";
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("dentunusd", element) == 0)
            return sar_analyzer_spike_obj->date_kernel_tables_spike_each_file.dentunusd_lowest_date_each_file[x];
        else if (strcmp("file", element) == 0)
            return sar_analyzer_spike_obj->date_kernel_tables_spike_each_file.file_lowest_date_each_file[x];
        else if (strcmp("inode", element) == 0)
            return sar_analyzer_spike_obj->date_kernel_tables_spike_each_file.inode_lowest_date_each_file[x];
        else
            return "error";
    } else
        return "error";
}

const char *get_ldavg_spike_date_each_file(int x, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("runq_sz", element) == 0)
            return sar_analyzer_spike_obj->date_ldavgs_spike_each_file.runq_sz_spike_date_each_file[x];
        else if (strcmp("plist_sz", element) == 0)
            return sar_analyzer_spike_obj->date_ldavgs_spike_each_file.plist_sz_spike_date_each_file[x];
        else if (strcmp("ldavg_one", element) == 0)
            return sar_analyzer_spike_obj->date_ldavgs_spike_each_file.ldavg_one_spike_date_each_file[x];
        else if (strcmp("ldavg_five", element) == 0)
            return sar_analyzer_spike_obj->date_ldavgs_spike_each_file.ldavg_five_spike_date_each_file[x];
        else if (strcmp("ldavg_15", element) == 0)
            return sar_analyzer_spike_obj->date_ldavgs_spike_each_file.ldavg_15_spike_date_each_file[x];
        else
            return "error";
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("runq_sz", element) == 0)
            return sar_analyzer_spike_obj->date_ldavgs_spike_each_file.runq_sz_highest_date_each_file[x];
        else if (strcmp("plist_sz", element) == 0)
            return sar_analyzer_spike_obj->date_ldavgs_spike_each_file.plist_sz_highest_date_each_file[x];
        else if (strcmp("ldavg_one", element) == 0)
            return sar_analyzer_spike_obj->date_ldavgs_spike_each_file.ldavg_one_highest_date_each_file[x];
        else if (strcmp("ldavg_five", element) == 0)
            return sar_analyzer_spike_obj->date_ldavgs_spike_each_file.ldavg_five_highest_date_each_file[x];
        else if (strcmp("ldavg_15", element) == 0)
            return sar_analyzer_spike_obj->date_ldavgs_spike_each_file.ldavg_15_highest_date_each_file[x];
        else
            return "error";
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("runq_sz", element) == 0)
            return sar_analyzer_spike_obj->date_ldavgs_spike_each_file.runq_sz_lowest_date_each_file[x];
        else if (strcmp("plist_sz", element) == 0)
            return sar_analyzer_spike_obj->date_ldavgs_spike_each_file.plist_sz_lowest_date_each_file[x];
        else if (strcmp("ldavg_one", element) == 0)
            return sar_analyzer_spike_obj->date_ldavgs_spike_each_file.ldavg_one_lowest_date_each_file[x];
        else if (strcmp("ldavg_five", element) == 0)
            return sar_analyzer_spike_obj->date_ldavgs_spike_each_file.ldavg_five_lowest_date_each_file[x];
        else if (strcmp("ldavg_15", element) == 0)
            return sar_analyzer_spike_obj->date_ldavgs_spike_each_file.ldavg_15_lowest_date_each_file[x];
        else
            return "error";
    } else
        return "error";
}

const char *get_block_device_spike_date_each_file(int x, int y, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("areqsz", element) == 0)
            return sar_analyzer_spike_obj->date_block_devices_spike_each_file.areqsz_spike_date_each_file[x][y];
        else if (strcmp("util", element) == 0)
            return sar_analyzer_spike_obj->date_block_devices_spike_each_file.util_spike_date_each_file[x][y];
        else
            return "error";
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("areqsz", element) == 0)
            return sar_analyzer_spike_obj->date_block_devices_spike_each_file.areqsz_highest_date_each_file[x][y];
        else if (strcmp("util", element) == 0)
            return sar_analyzer_spike_obj->date_block_devices_spike_each_file.util_highest_date_each_file[x][y];
        else
            return "error";
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("areqsz", element) == 0)
            return sar_analyzer_spike_obj->date_block_devices_spike_each_file.areqsz_lowest_date_each_file[x][y];
        else if (strcmp("util", element) == 0)
            return sar_analyzer_spike_obj->date_block_devices_spike_each_file.util_lowest_date_each_file[x][y];
        else
            return "error";
    } else
        return "error";
}

const char *get_network_spike_date_each_file(int x, int y, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("rxpck", element) == 0)
            return sar_analyzer_spike_obj->date_networks_spike_each_file.rxpck_spike_date_each_file[x][y];
        else if (strcmp("txpck", element) == 0)
            return sar_analyzer_spike_obj->date_networks_spike_each_file.txpck_spike_date_each_file[x][y];
        else if (strcmp("rxkb", element) == 0)
            return sar_analyzer_spike_obj->date_networks_spike_each_file.rxkb_spike_date_each_file[x][y];
        else if (strcmp("txkb", element) == 0)
            return sar_analyzer_spike_obj->date_networks_spike_each_file.txkb_spike_date_each_file[x][y];
        else if (strcmp("rxerr", element) == 0)
            return sar_analyzer_spike_obj->date_networks_spike_each_file.rxerr_spike_date_each_file[x][y];
        else if (strcmp("txerr", element) == 0)
            return sar_analyzer_spike_obj->date_networks_spike_each_file.txerr_spike_date_each_file[x][y];
        else if (strcmp("rxdrop", element) == 0)
            return sar_analyzer_spike_obj->date_networks_spike_each_file.rxdrop_spike_date_each_file[x][y];
        else if (strcmp("txdrop", element) == 0)
            return sar_analyzer_spike_obj->date_networks_spike_each_file.txdrop_spike_date_each_file[x][y];
        else
            return "error";
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("rxpck", element) == 0)
            return sar_analyzer_spike_obj->date_networks_spike_each_file.rxpck_highest_date_each_file[x][y];
        else if (strcmp("txpck", element) == 0)
            return sar_analyzer_spike_obj->date_networks_spike_each_file.txpck_highest_date_each_file[x][y];
        else if (strcmp("rxkb", element) == 0)
            return sar_analyzer_spike_obj->date_networks_spike_each_file.rxkb_highest_date_each_file[x][y];
        else if (strcmp("txkb", element) == 0)
            return sar_analyzer_spike_obj->date_networks_spike_each_file.txkb_highest_date_each_file[x][y];
        else if (strcmp("rxerr", element) == 0)
            return sar_analyzer_spike_obj->date_networks_spike_each_file.rxerr_highest_date_each_file[x][y];
        else if (strcmp("txerr", element) == 0)
            return sar_analyzer_spike_obj->date_networks_spike_each_file.txerr_highest_date_each_file[x][y];
        else if (strcmp("rxdrop", element) == 0)
            return sar_analyzer_spike_obj->date_networks_spike_each_file.rxdrop_highest_date_each_file[x][y];
        else if (strcmp("txdrop", element) == 0)
            return sar_analyzer_spike_obj->date_networks_spike_each_file.txdrop_highest_date_each_file[x][y];
        else
            return "error";
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("rxpck", element) == 0)
            return sar_analyzer_spike_obj->date_networks_spike_each_file.rxpck_lowest_date_each_file[x][y];
        else if (strcmp("txpck", element) == 0)
            return sar_analyzer_spike_obj->date_networks_spike_each_file.txpck_lowest_date_each_file[x][y];
        else if (strcmp("rxkb", element) == 0)
            return sar_analyzer_spike_obj->date_networks_spike_each_file.rxkb_lowest_date_each_file[x][y];
        else if (strcmp("txkb", element) == 0)
            return sar_analyzer_spike_obj->date_networks_spike_each_file.txkb_lowest_date_each_file[x][y];
        else if (strcmp("rxerr", element) == 0)
            return sar_analyzer_spike_obj->date_networks_spike_each_file.rxerr_lowest_date_each_file[x][y];
        else if (strcmp("txerr", element) == 0)
            return sar_analyzer_spike_obj->date_networks_spike_each_file.txerr_lowest_date_each_file[x][y];
        else if (strcmp("rxdrop", element) == 0)
            return sar_analyzer_spike_obj->date_networks_spike_each_file.rxdrop_lowest_date_each_file[x][y];
        else if (strcmp("txdrop", element) == 0)
            return sar_analyzer_spike_obj->date_networks_spike_each_file.txdrop_lowest_date_each_file[x][y];
        else
            return "error";
    } else if (strcmp("down", analyze_item) == 0) {
        if (strcmp("rxpck", element) == 0)
            return sar_analyzer_spike_obj->date_networks_spike_each_file.rxpck_down_date_each_file[x][y];
        else if (strcmp("txpck", element) == 0)
            return sar_analyzer_spike_obj->date_networks_spike_each_file.txpck_down_date_each_file[x][y];
        else if (strcmp("rxkb", element) == 0)
            return sar_analyzer_spike_obj->date_networks_spike_each_file.rxkb_down_date_each_file[x][y];
        else if (strcmp("txkb", element) == 0)
            return sar_analyzer_spike_obj->date_networks_spike_each_file.txkb_down_date_each_file[x][y];
        else if (strcmp("rxerr", element) == 0)
            return sar_analyzer_spike_obj->date_networks_spike_each_file.rxerr_down_date_each_file[x][y];
        else if (strcmp("txerr", element) == 0)
            return sar_analyzer_spike_obj->date_networks_spike_each_file.txerr_down_date_each_file[x][y];
        else if (strcmp("rxdrop", element) == 0)
            return sar_analyzer_spike_obj->date_networks_spike_each_file.rxdrop_down_date_each_file[x][y];
        else if (strcmp("txdrop", element) == 0)
            return sar_analyzer_spike_obj->date_networks_spike_each_file.txdrop_down_date_each_file[x][y];
        else
            return "error";
    } else
        return "error";
}

/* -- time-span spike date each file -- */

const char *get_cpu_time_span_spike_date_each_file(int x, int y, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("usr", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_cpus_time_span_spike_each_file.cpu_usr_time_span_spike_date_each_file[x][y];
        else if (strcmp("sys", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_cpus_time_span_spike_each_file.cpu_sys_time_span_spike_date_each_file[x][y];
        else if (strcmp("iowait", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_cpus_time_span_spike_each_file.cpu_iowait_time_span_spike_date_each_file[x][y];
        else if (strcmp("idle", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_cpus_time_span_spike_each_file.cpu_idle_time_span_spike_date_each_file[x][y];
        else
            return "error";
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("usr", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_cpus_time_span_spike_each_file.cpu_usr_time_span_highest_date_each_file[x][y];
        else if (strcmp("sys", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_cpus_time_span_spike_each_file.cpu_sys_time_span_highest_date_each_file[x][y];
        else if (strcmp("iowait", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_cpus_time_span_spike_each_file.cpu_iowait_time_span_highest_date_each_file[x][y];
        else if (strcmp("idle", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_cpus_time_span_spike_each_file.cpu_idle_time_span_highest_date_each_file[x][y];
        else
            return "error";
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("usr", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_cpus_time_span_spike_each_file.cpu_usr_time_span_lowest_date_each_file[x][y];
        else if (strcmp("sys", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_cpus_time_span_spike_each_file.cpu_sys_time_span_lowest_date_each_file[x][y];
        else if (strcmp("iowait", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_cpus_time_span_spike_each_file.cpu_iowait_time_span_lowest_date_each_file[x][y];
        else if (strcmp("idle", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_cpus_time_span_spike_each_file.cpu_idle_time_span_lowest_date_each_file[x][y];
        else
            return "error";
    } else
        return "error";
}

const char *get_tasks_time_span_spike_date_each_file(int x, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("proc", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_tasks_time_span_spike_each_file.proc_time_span_spike_date_each_file[x];
        else if (strcmp("cswch", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_tasks_time_span_spike_each_file.cswch_time_span_spike_date_each_file[x];
        else
            return "error";
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("proc", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_tasks_time_span_spike_each_file.proc_time_span_highest_date_each_file[x];
        else if (strcmp("cswch", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_tasks_time_span_spike_each_file.cswch_time_span_highest_date_each_file[x];
        else
            return "error";
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("proc", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_tasks_time_span_spike_each_file.proc_time_span_lowest_date_each_file[x];
        else if (strcmp("cswch", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_tasks_time_span_spike_each_file.cswch_time_span_lowest_date_each_file[x];
        else
            return "error";
    } else
        return "error";
}

const char *get_pswap_time_span_spike_date_each_file(int x, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("pswpin", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_pswaps_time_span_spike_each_file.pswpin_time_span_spike_date_each_file[x];
        else if (strcmp("pswpout", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_pswaps_time_span_spike_each_file.pswpout_time_span_spike_date_each_file[x];
        else
            return "error";
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("pswpin", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_pswaps_time_span_spike_each_file.pswpin_time_span_highest_date_each_file[x];
        else if (strcmp("pswpout", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_pswaps_time_span_spike_each_file.pswpout_time_span_highest_date_each_file[x];
        else
            return "error";
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("pswpin", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_pswaps_time_span_spike_each_file.pswpin_time_span_lowest_date_each_file[x];
        else if (strcmp("pswpout", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_pswaps_time_span_spike_each_file.pswpout_time_span_lowest_date_each_file[x];
        else
            return "error";
    } else
        return "error";
}

const char *get_paging_time_span_spike_date_each_file(int x, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("pgpgin", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_pagings_time_span_spike_each_file.pgpgin_time_span_spike_date_each_file[x];
        else if (strcmp("pgpgout", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_pagings_time_span_spike_each_file.pgpgout_time_span_spike_date_each_file[x];
        else if (strcmp("fault", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_pagings_time_span_spike_each_file.fault_time_span_spike_date_each_file[x];
        else if (strcmp("majflt", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_pagings_time_span_spike_each_file.majflt_time_span_spike_date_each_file[x];
        else if (strcmp("vmeff", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_pagings_time_span_spike_each_file.vmeff_time_span_spike_date_each_file[x];
        else
            return "error";
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("pgpgin", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_pagings_time_span_spike_each_file.pgpgin_time_span_highest_date_each_file[x];
        else if (strcmp("pgpgout", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_pagings_time_span_spike_each_file.pgpgout_time_span_highest_date_each_file[x];
        else if (strcmp("fault", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_pagings_time_span_spike_each_file.fault_time_span_highest_date_each_file[x];
        else if (strcmp("majflt", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_pagings_time_span_spike_each_file.majflt_time_span_highest_date_each_file[x];
        else if (strcmp("vmeff", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_pagings_time_span_spike_each_file.vmeff_time_span_highest_date_each_file[x];
        else
            return "error";
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("pgpgin", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_pagings_time_span_spike_each_file.pgpgin_time_span_lowest_date_each_file[x];
        else if (strcmp("pgpgout", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_pagings_time_span_spike_each_file.pgpgout_time_span_lowest_date_each_file[x];
        else if (strcmp("fault", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_pagings_time_span_spike_each_file.fault_time_span_lowest_date_each_file[x];
        else if (strcmp("majflt", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_pagings_time_span_spike_each_file.majflt_time_span_lowest_date_each_file[x];
        else if (strcmp("vmeff", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_pagings_time_span_spike_each_file.vmeff_time_span_lowest_date_each_file[x];
        else
            return "error";
    } else
        return "error";
}

const char *get_io_transfer_rate_time_span_spike_date_each_file(int x, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("tps", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_io_transfer_rates_time_span_spike_each_file.tps_time_span_spike_date_each_file[x];
        else if (strcmp("bread", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_io_transfer_rates_time_span_spike_each_file.bread_time_span_spike_date_each_file[x];
        else if (strcmp("bwrtn", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_io_transfer_rates_time_span_spike_each_file.bwrtn_time_span_spike_date_each_file[x];
        else
            return "error";
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("tps", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_io_transfer_rates_time_span_spike_each_file.tps_time_span_highest_date_each_file[x];
        else if (strcmp("bread", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_io_transfer_rates_time_span_spike_each_file.bread_time_span_highest_date_each_file[x];
        else if (strcmp("bwrtn", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_io_transfer_rates_time_span_spike_each_file.bwrtn_time_span_highest_date_each_file[x];
        else
            return "error";
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("tps", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_io_transfer_rates_time_span_spike_each_file.tps_time_span_lowest_date_each_file[x];
        else if (strcmp("bread", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_io_transfer_rates_time_span_spike_each_file.bread_time_span_lowest_date_each_file[x];
        else if (strcmp("bwrtn", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_io_transfer_rates_time_span_spike_each_file.bwrtn_time_span_lowest_date_each_file[x];
        else
            return "error";
    } else
        return "error";
}

const char *get_memory_time_span_spike_date_each_file(int x, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("memused", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_memories_time_span_spike_each_file.memused_time_span_spike_date_each_file[x];
        else if (strcmp("kbcommit", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_memories_time_span_spike_each_file.kbcommit_time_span_spike_date_each_file[x];
        else if (strcmp("commit", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_memories_time_span_spike_each_file.commit_time_span_spike_date_each_file[x];
        else
            return "error";
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("memused", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_memories_time_span_spike_each_file.memused_time_span_highest_date_each_file[x];
        else if (strcmp("kbcommit", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_memories_time_span_spike_each_file.kbcommit_time_span_highest_date_each_file[x];
        else if (strcmp("commit", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_memories_time_span_spike_each_file.commit_time_span_highest_date_each_file[x];
        else
            return "error";
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("memused", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_memories_time_span_spike_each_file.memused_time_span_lowest_date_each_file[x];
        else if (strcmp("kbcommit", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_memories_time_span_spike_each_file.kbcommit_time_span_lowest_date_each_file[x];
        else if (strcmp("commit", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_memories_time_span_spike_each_file.commit_time_span_lowest_date_each_file[x];
        else
            return "error";
    } else
        return "error";
}

const char *get_swpused_time_span_spike_date_each_file(int x, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0)
        return sar_analyzer_time_span_spike_obj->date_swaps_time_span_spike_each_file.swpused_time_span_spike_date_each_file[x];
    else if (strcmp("highest", analyze_item) == 0)
        return sar_analyzer_time_span_spike_obj->date_swaps_time_span_spike_each_file.swpused_time_span_highest_date_each_file[x];
    else if (strcmp("lowest", analyze_item) == 0)
        return sar_analyzer_time_span_spike_obj->date_swaps_time_span_spike_each_file.swpused_time_span_lowest_date_each_file[x];
    else
        return "error";
}

const char *get_kernel_table_time_span_spike_date_each_file(int x, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("dentunusd", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_kernel_tables_time_span_spike_each_file.dentunusd_time_span_spike_date_each_file[x];
        else if (strcmp("file", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_kernel_tables_time_span_spike_each_file.file_time_span_spike_date_each_file[x];
        else if (strcmp("inode", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_kernel_tables_time_span_spike_each_file.inode_time_span_spike_date_each_file[x];
        else
            return "error";
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("dentunusd", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_kernel_tables_time_span_spike_each_file.dentunusd_time_span_highest_date_each_file[x];
        else if (strcmp("file", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_kernel_tables_time_span_spike_each_file.file_time_span_highest_date_each_file[x];
        else if (strcmp("inode", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_kernel_tables_time_span_spike_each_file.inode_time_span_highest_date_each_file[x];
        else
            return "error";
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("dentunusd", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_kernel_tables_time_span_spike_each_file.dentunusd_time_span_lowest_date_each_file[x];
        else if (strcmp("file", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_kernel_tables_time_span_spike_each_file.file_time_span_lowest_date_each_file[x];
        else if (strcmp("inode", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_kernel_tables_time_span_spike_each_file.inode_time_span_lowest_date_each_file[x];
        else
            return "error";
    } else
        return "error";
}

const char *get_ldavg_time_span_spike_date_each_file(int x, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("runq_sz", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_ldavgs_time_span_spike_each_file.runq_sz_time_span_spike_date_each_file[x];
        else if (strcmp("plist_sz", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_ldavgs_time_span_spike_each_file.plist_sz_time_span_spike_date_each_file[x];
        else if (strcmp("ldavg_one", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_ldavgs_time_span_spike_each_file.ldavg_one_time_span_spike_date_each_file[x];
        else if (strcmp("ldavg_five", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_ldavgs_time_span_spike_each_file.ldavg_five_time_span_spike_date_each_file[x];
        else if (strcmp("ldavg_15", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_ldavgs_time_span_spike_each_file.ldavg_15_time_span_spike_date_each_file[x];
        else
            return "error";
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("runq_sz", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_ldavgs_time_span_spike_each_file.runq_sz_time_span_highest_date_each_file[x];
        else if (strcmp("plist_sz", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_ldavgs_time_span_spike_each_file.plist_sz_time_span_highest_date_each_file[x];
        else if (strcmp("ldavg_one", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_ldavgs_time_span_spike_each_file.ldavg_one_time_span_highest_date_each_file[x];
        else if (strcmp("ldavg_five", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_ldavgs_time_span_spike_each_file.ldavg_five_time_span_highest_date_each_file[x];
        else if (strcmp("ldavg_15", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_ldavgs_time_span_spike_each_file.ldavg_15_time_span_highest_date_each_file[x];
        else
            return "error";
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("runq_sz", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_ldavgs_time_span_spike_each_file.runq_sz_time_span_lowest_date_each_file[x];
        else if (strcmp("plist_sz", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_ldavgs_time_span_spike_each_file.plist_sz_time_span_lowest_date_each_file[x];
        else if (strcmp("ldavg_one", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_ldavgs_time_span_spike_each_file.ldavg_one_time_span_lowest_date_each_file[x];
        else if (strcmp("ldavg_five", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_ldavgs_time_span_spike_each_file.ldavg_five_time_span_lowest_date_each_file[x];
        else if (strcmp("ldavg_15", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_ldavgs_time_span_spike_each_file.ldavg_15_time_span_lowest_date_each_file[x];
        else
            return "error";
    } else
        return "error";
}

const char *get_block_device_time_span_spike_date_each_file(int x, int y, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("areqsz", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_block_devices_time_span_spike_each_file.areqsz_time_span_spike_date_each_file[x][y];
        else if (strcmp("util", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_block_devices_time_span_spike_each_file.util_time_span_spike_date_each_file[x][y];
        else
            return "error";
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("areqsz", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_block_devices_time_span_spike_each_file.areqsz_time_span_highest_date_each_file[x][y];
        else if (strcmp("util", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_block_devices_time_span_spike_each_file.util_time_span_highest_date_each_file[x][y];
        else
            return "error";
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("areqsz", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_block_devices_time_span_spike_each_file.areqsz_time_span_lowest_date_each_file[x][y];
        else if (strcmp("util", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_block_devices_time_span_spike_each_file.util_time_span_lowest_date_each_file[x][y];
        else
            return "error";
    } else
        return "error";
}

/* -- spike time each file -- */

const char *get_cpu_spike_time_each_file(int x, int y, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("usr", element) == 0)
            return sar_analyzer_spike_obj->date_cpus_spike_each_file.cpu_usr_spike_time_each_file[x][y];
        else if (strcmp("sys", element) == 0)
            return sar_analyzer_spike_obj->date_cpus_spike_each_file.cpu_sys_spike_time_each_file[x][y];
        else if (strcmp("iowait", element) == 0)
            return sar_analyzer_spike_obj->date_cpus_spike_each_file.cpu_iowait_spike_time_each_file[x][y];
        else if (strcmp("idle", element) == 0)
            return sar_analyzer_spike_obj->date_cpus_spike_each_file.cpu_idle_spike_time_each_file[x][y];
        else
            return "error";
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("usr", element) == 0)
            return sar_analyzer_spike_obj->date_cpus_spike_each_file.cpu_usr_highest_time_each_file[x][y];
        else if (strcmp("sys", element) == 0)
            return sar_analyzer_spike_obj->date_cpus_spike_each_file.cpu_sys_highest_time_each_file[x][y];
        else if (strcmp("iowait", element) == 0)
            return sar_analyzer_spike_obj->date_cpus_spike_each_file.cpu_iowait_highest_time_each_file[x][y];
        else if (strcmp("idle", element) == 0)
            return sar_analyzer_spike_obj->date_cpus_spike_each_file.cpu_idle_highest_time_each_file[x][y];
        else
            return "error";
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("usr", element) == 0)
            return sar_analyzer_spike_obj->date_cpus_spike_each_file.cpu_usr_lowest_time_each_file[x][y];
        else if (strcmp("sys", element) == 0)
            return sar_analyzer_spike_obj->date_cpus_spike_each_file.cpu_sys_lowest_time_each_file[x][y];
        else if (strcmp("iowait", element) == 0)
            return sar_analyzer_spike_obj->date_cpus_spike_each_file.cpu_iowait_lowest_time_each_file[x][y];
        else if (strcmp("idle", element) == 0)
            return sar_analyzer_spike_obj->date_cpus_spike_each_file.cpu_idle_lowest_time_each_file[x][y];
        else
            return "error";
    } else
        return "error";
}

const char *get_tasks_spike_time_each_file(int x, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("proc", element) == 0)
            return sar_analyzer_spike_obj->date_tasks_spike_each_file.proc_spike_time_each_file[x];
        else if (strcmp("cswch", element) == 0)
            return sar_analyzer_spike_obj->date_tasks_spike_each_file.cswch_spike_time_each_file[x];
        else
            return "error";
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("proc", element) == 0)
            return sar_analyzer_spike_obj->date_tasks_spike_each_file.proc_highest_time_each_file[x];
        else if (strcmp("cswch", element) == 0)
            return sar_analyzer_spike_obj->date_tasks_spike_each_file.cswch_highest_time_each_file[x];
        else
            return "error";
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("proc", element) == 0)
            return sar_analyzer_spike_obj->date_tasks_spike_each_file.proc_lowest_time_each_file[x];
        else if (strcmp("cswch", element) == 0)
            return sar_analyzer_spike_obj->date_tasks_spike_each_file.cswch_lowest_time_each_file[x];
        else
            return "error";
    } else
        return "error";
}

const char *get_pswap_spike_time_each_file(int x, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("pswpin", element) == 0)
            return sar_analyzer_spike_obj->date_pswaps_spike_each_file.pswpin_spike_time_each_file[x];
        else if (strcmp("pswpout", element) == 0)
            return sar_analyzer_spike_obj->date_pswaps_spike_each_file.pswpout_spike_time_each_file[x];
        else
            return "error";
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("pswpin", element) == 0)
            return sar_analyzer_spike_obj->date_pswaps_spike_each_file.pswpin_highest_time_each_file[x];
        else if (strcmp("pswpout", element) == 0)
            return sar_analyzer_spike_obj->date_pswaps_spike_each_file.pswpout_highest_time_each_file[x];
        else
            return "error";
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("pswpin", element) == 0)
            return sar_analyzer_spike_obj->date_pswaps_spike_each_file.pswpin_lowest_time_each_file[x];
        else if (strcmp("pswpout", element) == 0)
            return sar_analyzer_spike_obj->date_pswaps_spike_each_file.pswpout_lowest_time_each_file[x];
        else
            return "error";
    } else
        return "error";
}

const char *get_paging_spike_time_each_file(int x, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("pgpgin", element) == 0)
            return sar_analyzer_spike_obj->date_pagings_spike_each_file.pgpgin_spike_time_each_file[x];
        else if (strcmp("pgpgout", element) == 0)
            return sar_analyzer_spike_obj->date_pagings_spike_each_file.pgpgout_spike_time_each_file[x];
        else if (strcmp("fault", element) == 0)
            return sar_analyzer_spike_obj->date_pagings_spike_each_file.fault_spike_time_each_file[x];
        else if (strcmp("majflt", element) == 0)
            return sar_analyzer_spike_obj->date_pagings_spike_each_file.majflt_spike_time_each_file[x];
        else if (strcmp("vmeff", element) == 0)
            return sar_analyzer_spike_obj->date_pagings_spike_each_file.vmeff_spike_time_each_file[x];
        else
            return "error";
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("pgpgin", element) == 0)
            return sar_analyzer_spike_obj->date_pagings_spike_each_file.pgpgin_highest_time_each_file[x];
        else if (strcmp("pgpgout", element) == 0)
            return sar_analyzer_spike_obj->date_pagings_spike_each_file.pgpgout_highest_time_each_file[x];
        else if (strcmp("fault", element) == 0)
            return sar_analyzer_spike_obj->date_pagings_spike_each_file.fault_highest_time_each_file[x];
        else if (strcmp("majflt", element) == 0)
            return sar_analyzer_spike_obj->date_pagings_spike_each_file.majflt_highest_time_each_file[x];
        else if (strcmp("vmeff", element) == 0)
            return sar_analyzer_spike_obj->date_pagings_spike_each_file.vmeff_highest_time_each_file[x];
        else
            return "error";
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("pgpgin", element) == 0)
            return sar_analyzer_spike_obj->date_pagings_spike_each_file.pgpgin_lowest_time_each_file[x];
        else if (strcmp("pgpgout", element) == 0)
            return sar_analyzer_spike_obj->date_pagings_spike_each_file.pgpgout_lowest_time_each_file[x];
        else if (strcmp("fault", element) == 0)
            return sar_analyzer_spike_obj->date_pagings_spike_each_file.fault_lowest_time_each_file[x];
        else if (strcmp("majflt", element) == 0)
            return sar_analyzer_spike_obj->date_pagings_spike_each_file.majflt_lowest_time_each_file[x];
        else if (strcmp("vmeff", element) == 0)
            return sar_analyzer_spike_obj->date_pagings_spike_each_file.vmeff_lowest_time_each_file[x];
        else
            return "error";
    } else
        return "error";
}

const char *get_io_transfer_rate_spike_time_each_file(int x, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("tps", element) == 0)
            return sar_analyzer_spike_obj->date_io_transfer_rates_spike_each_file.tps_spike_time_each_file[x];
        else if (strcmp("bread", element) == 0)
            return sar_analyzer_spike_obj->date_io_transfer_rates_spike_each_file.bread_spike_time_each_file[x];
        else if (strcmp("bwrtn", element) == 0)
            return sar_analyzer_spike_obj->date_io_transfer_rates_spike_each_file.bwrtn_spike_time_each_file[x];
        else
            return "error";
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("tps", element) == 0)
            return sar_analyzer_spike_obj->date_io_transfer_rates_spike_each_file.tps_highest_time_each_file[x];
        else if (strcmp("bread", element) == 0)
            return sar_analyzer_spike_obj->date_io_transfer_rates_spike_each_file.bread_highest_time_each_file[x];
        else if (strcmp("bwrtn", element) == 0)
            return sar_analyzer_spike_obj->date_io_transfer_rates_spike_each_file.bwrtn_highest_time_each_file[x];
        else
            return "error";
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("tps", element) == 0)
            return sar_analyzer_spike_obj->date_io_transfer_rates_spike_each_file.tps_lowest_time_each_file[x];
        else if (strcmp("bread", element) == 0)
            return sar_analyzer_spike_obj->date_io_transfer_rates_spike_each_file.bread_lowest_time_each_file[x];
        else if (strcmp("bwrtn", element) == 0)
            return sar_analyzer_spike_obj->date_io_transfer_rates_spike_each_file.bwrtn_lowest_time_each_file[x];
        else
            return "error";
    } else
        return "error";
}

const char *get_memory_spike_time_each_file(int x, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("memused", element) == 0)
            return sar_analyzer_spike_obj->date_memories_spike_each_file.memused_spike_time_each_file[x];
        else if (strcmp("kbcommit", element) == 0)
            return sar_analyzer_spike_obj->date_memories_spike_each_file.kbcommit_spike_time_each_file[x];
        else if (strcmp("commit", element) == 0)
            return sar_analyzer_spike_obj->date_memories_spike_each_file.commit_spike_time_each_file[x];
        else
            return "error";
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("memused", element) == 0)
            return sar_analyzer_spike_obj->date_memories_spike_each_file.memused_highest_time_each_file[x];
        else if (strcmp("kbcommit", element) == 0)
            return sar_analyzer_spike_obj->date_memories_spike_each_file.kbcommit_highest_time_each_file[x];
        else if (strcmp("commit", element) == 0)
            return sar_analyzer_spike_obj->date_memories_spike_each_file.commit_highest_time_each_file[x];
        else
            return "error";
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("memused", element) == 0)
            return sar_analyzer_spike_obj->date_memories_spike_each_file.memused_lowest_time_each_file[x];
        else if (strcmp("kbcommit", element) == 0)
            return sar_analyzer_spike_obj->date_memories_spike_each_file.kbcommit_lowest_time_each_file[x];
        else if (strcmp("commit", element) == 0)
            return sar_analyzer_spike_obj->date_memories_spike_each_file.commit_lowest_time_each_file[x];
        else
            return "error";
    } else
        return "error";
}

const char *get_swpused_spike_time_each_file(int x, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0)
        return sar_analyzer_spike_obj->date_swaps_spike_each_file.swpused_spike_time_each_file[x];
    else if (strcmp("highest", analyze_item) == 0)
        return sar_analyzer_spike_obj->date_swaps_spike_each_file.swpused_highest_time_each_file[x];
    else if (strcmp("lowest", analyze_item) == 0)
        return sar_analyzer_spike_obj->date_swaps_spike_each_file.swpused_lowest_time_each_file[x];
    else
        return "error";
}

const char *get_kernel_table_spike_time_each_file(int x, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("dentunusd", element) == 0)
            return sar_analyzer_spike_obj->date_kernel_tables_spike_each_file.dentunusd_spike_time_each_file[x];
        else if (strcmp("file", element) == 0)
            return sar_analyzer_spike_obj->date_kernel_tables_spike_each_file.file_spike_time_each_file[x];
        else if (strcmp("inode", element) == 0)
            return sar_analyzer_spike_obj->date_kernel_tables_spike_each_file.inode_spike_time_each_file[x];
        else
            return "error";
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("dentunusd", element) == 0)
            return sar_analyzer_spike_obj->date_kernel_tables_spike_each_file.dentunusd_highest_time_each_file[x];
        else if (strcmp("file", element) == 0)
            return sar_analyzer_spike_obj->date_kernel_tables_spike_each_file.file_highest_time_each_file[x];
        else if (strcmp("inode", element) == 0)
            return sar_analyzer_spike_obj->date_kernel_tables_spike_each_file.inode_highest_time_each_file[x];
        else
            return "error";
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("dentunusd", element) == 0)
            return sar_analyzer_spike_obj->date_kernel_tables_spike_each_file.dentunusd_lowest_time_each_file[x];
        else if (strcmp("file", element) == 0)
            return sar_analyzer_spike_obj->date_kernel_tables_spike_each_file.file_lowest_time_each_file[x];
        else if (strcmp("inode", element) == 0)
            return sar_analyzer_spike_obj->date_kernel_tables_spike_each_file.inode_lowest_time_each_file[x];
        else
            return "error";
    } else
        return "error";
}

const char *get_ldavg_spike_time_each_file(int x, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("runq_sz", element) == 0)
            return sar_analyzer_spike_obj->date_ldavgs_spike_each_file.runq_sz_spike_time_each_file[x];
        else if (strcmp("plist_sz", element) == 0)
            return sar_analyzer_spike_obj->date_ldavgs_spike_each_file.plist_sz_spike_time_each_file[x];
        else if (strcmp("ldavg_one", element) == 0)
            return sar_analyzer_spike_obj->date_ldavgs_spike_each_file.ldavg_one_spike_time_each_file[x];
        else if (strcmp("ldavg_five", element) == 0)
            return sar_analyzer_spike_obj->date_ldavgs_spike_each_file.ldavg_five_spike_time_each_file[x];
        else if (strcmp("ldavg_15", element) == 0)
            return sar_analyzer_spike_obj->date_ldavgs_spike_each_file.ldavg_15_spike_time_each_file[x];
        else
            return "error";
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("runq_sz", element) == 0)
            return sar_analyzer_spike_obj->date_ldavgs_spike_each_file.runq_sz_highest_time_each_file[x];
        else if (strcmp("plist_sz", element) == 0)
            return sar_analyzer_spike_obj->date_ldavgs_spike_each_file.plist_sz_highest_time_each_file[x];
        else if (strcmp("ldavg_one", element) == 0)
            return sar_analyzer_spike_obj->date_ldavgs_spike_each_file.ldavg_one_highest_time_each_file[x];
        else if (strcmp("ldavg_five", element) == 0)
            return sar_analyzer_spike_obj->date_ldavgs_spike_each_file.ldavg_five_highest_time_each_file[x];
        else if (strcmp("ldavg_15", element) == 0)
            return sar_analyzer_spike_obj->date_ldavgs_spike_each_file.ldavg_15_highest_time_each_file[x];
        else
            return "error";
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("runq_sz", element) == 0)
            return sar_analyzer_spike_obj->date_ldavgs_spike_each_file.runq_sz_lowest_time_each_file[x];
        else if (strcmp("plist_sz", element) == 0)
            return sar_analyzer_spike_obj->date_ldavgs_spike_each_file.plist_sz_lowest_time_each_file[x];
        else if (strcmp("ldavg_one", element) == 0)
            return sar_analyzer_spike_obj->date_ldavgs_spike_each_file.ldavg_one_lowest_time_each_file[x];
        else if (strcmp("ldavg_five", element) == 0)
            return sar_analyzer_spike_obj->date_ldavgs_spike_each_file.ldavg_five_lowest_time_each_file[x];
        else if (strcmp("ldavg_15", element) == 0)
            return sar_analyzer_spike_obj->date_ldavgs_spike_each_file.ldavg_15_lowest_time_each_file[x];
        else
            return "error";
    } else
        return "error";
}

const char *get_block_device_spike_time_each_file(int x, int y, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("areqsz", element) == 0)
            return sar_analyzer_spike_obj->date_block_devices_spike_each_file.areqsz_spike_time_each_file[x][y];
        else if (strcmp("util", element) == 0)
            return sar_analyzer_spike_obj->date_block_devices_spike_each_file.util_spike_time_each_file[x][y];
        else
            return "error";
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("areqsz", element) == 0)
            return sar_analyzer_spike_obj->date_block_devices_spike_each_file.areqsz_highest_time_each_file[x][y];
        else if (strcmp("util", element) == 0)
            return sar_analyzer_spike_obj->date_block_devices_spike_each_file.util_highest_time_each_file[x][y];
        else
            return "error";
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("areqsz", element) == 0)
            return sar_analyzer_spike_obj->date_block_devices_spike_each_file.areqsz_lowest_time_each_file[x][y];
        else if (strcmp("util", element) == 0)
            return sar_analyzer_spike_obj->date_block_devices_spike_each_file.util_lowest_time_each_file[x][y];
        else
            return "error";
    } else
        return "error";
}

const char *get_network_spike_time_each_file(int x, int y, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("rxpck", element) == 0)
            return sar_analyzer_spike_obj->date_networks_spike_each_file.rxpck_spike_time_each_file[x][y];
        else if (strcmp("txpck", element) == 0)
            return sar_analyzer_spike_obj->date_networks_spike_each_file.txpck_spike_time_each_file[x][y];
        else if (strcmp("rxkb", element) == 0)
            return sar_analyzer_spike_obj->date_networks_spike_each_file.rxkb_spike_time_each_file[x][y];
        else if (strcmp("txkb", element) == 0)
            return sar_analyzer_spike_obj->date_networks_spike_each_file.txkb_spike_time_each_file[x][y];
        else if (strcmp("rxerr", element) == 0)
            return sar_analyzer_spike_obj->date_networks_spike_each_file.rxerr_spike_time_each_file[x][y];
        else if (strcmp("txerr", element) == 0)
            return sar_analyzer_spike_obj->date_networks_spike_each_file.txerr_spike_time_each_file[x][y];
        else if (strcmp("rxdrop", element) == 0)
            return sar_analyzer_spike_obj->date_networks_spike_each_file.rxdrop_spike_time_each_file[x][y];
        else if (strcmp("txdrop", element) == 0)
            return sar_analyzer_spike_obj->date_networks_spike_each_file.txdrop_spike_time_each_file[x][y];
        else
            return "error";
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("rxpck", element) == 0)
            return sar_analyzer_spike_obj->date_networks_spike_each_file.rxpck_highest_time_each_file[x][y];
        else if (strcmp("txpck", element) == 0)
            return sar_analyzer_spike_obj->date_networks_spike_each_file.txpck_highest_time_each_file[x][y];
        else if (strcmp("rxkb", element) == 0)
            return sar_analyzer_spike_obj->date_networks_spike_each_file.rxkb_highest_time_each_file[x][y];
        else if (strcmp("txkb", element) == 0)
            return sar_analyzer_spike_obj->date_networks_spike_each_file.txkb_highest_time_each_file[x][y];
        else if (strcmp("rxerr", element) == 0)
            return sar_analyzer_spike_obj->date_networks_spike_each_file.rxerr_highest_time_each_file[x][y];
        else if (strcmp("txerr", element) == 0)
            return sar_analyzer_spike_obj->date_networks_spike_each_file.txerr_highest_time_each_file[x][y];
        else if (strcmp("rxdrop", element) == 0)
            return sar_analyzer_spike_obj->date_networks_spike_each_file.rxdrop_highest_time_each_file[x][y];
        else if (strcmp("txdrop", element) == 0)
            return sar_analyzer_spike_obj->date_networks_spike_each_file.txdrop_highest_time_each_file[x][y];
        else
            return "error";
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("rxpck", element) == 0)
            return sar_analyzer_spike_obj->date_networks_spike_each_file.rxpck_lowest_time_each_file[x][y];
        else if (strcmp("txpck", element) == 0)
            return sar_analyzer_spike_obj->date_networks_spike_each_file.txpck_lowest_time_each_file[x][y];
        else if (strcmp("rxkb", element) == 0)
            return sar_analyzer_spike_obj->date_networks_spike_each_file.rxkb_lowest_time_each_file[x][y];
        else if (strcmp("txkb", element) == 0)
            return sar_analyzer_spike_obj->date_networks_spike_each_file.txkb_lowest_time_each_file[x][y];
        else if (strcmp("rxerr", element) == 0)
            return sar_analyzer_spike_obj->date_networks_spike_each_file.rxerr_lowest_time_each_file[x][y];
        else if (strcmp("txerr", element) == 0)
            return sar_analyzer_spike_obj->date_networks_spike_each_file.txerr_lowest_time_each_file[x][y];
        else if (strcmp("rxdrop", element) == 0)
            return sar_analyzer_spike_obj->date_networks_spike_each_file.rxdrop_lowest_time_each_file[x][y];
        else if (strcmp("txdrop", element) == 0)
            return sar_analyzer_spike_obj->date_networks_spike_each_file.txdrop_lowest_time_each_file[x][y];
        else
            return "error";
    } else if (strcmp("down", analyze_item) == 0) {
        if (strcmp("rxpck", element) == 0)
            return sar_analyzer_spike_obj->date_networks_spike_each_file.rxpck_down_time_each_file[x][y];
        else if (strcmp("txpck", element) == 0)
            return sar_analyzer_spike_obj->date_networks_spike_each_file.txpck_down_time_each_file[x][y];
        else if (strcmp("rxkb", element) == 0)
            return sar_analyzer_spike_obj->date_networks_spike_each_file.rxkb_down_time_each_file[x][y];
        else if (strcmp("txkb", element) == 0)
            return sar_analyzer_spike_obj->date_networks_spike_each_file.txkb_down_time_each_file[x][y];
        else if (strcmp("rxerr", element) == 0)
            return sar_analyzer_spike_obj->date_networks_spike_each_file.rxerr_down_time_each_file[x][y];
        else if (strcmp("txerr", element) == 0)
            return sar_analyzer_spike_obj->date_networks_spike_each_file.txerr_down_time_each_file[x][y];
        else if (strcmp("rxdrop", element) == 0)
            return sar_analyzer_spike_obj->date_networks_spike_each_file.rxdrop_down_time_each_file[x][y];
        else if (strcmp("txdrop", element) == 0)
            return sar_analyzer_spike_obj->date_networks_spike_each_file.txdrop_down_time_each_file[x][y];
        else
            return "error";
    } else
        return "error";
}

/* -- time-span spike time each file -- */

const char *get_cpu_time_span_spike_time_each_file(int x, int y, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("usr", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_cpus_time_span_spike_each_file.cpu_usr_time_span_spike_time_each_file[x][y];
        else if (strcmp("sys", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_cpus_time_span_spike_each_file.cpu_sys_time_span_spike_time_each_file[x][y];
        else if (strcmp("iowait", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_cpus_time_span_spike_each_file.cpu_iowait_time_span_spike_time_each_file[x][y];
        else if (strcmp("idle", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_cpus_time_span_spike_each_file.cpu_idle_time_span_spike_time_each_file[x][y];
        else
            return "error";
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("usr", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_cpus_time_span_spike_each_file.cpu_usr_time_span_highest_time_each_file[x][y];
        else if (strcmp("sys", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_cpus_time_span_spike_each_file.cpu_sys_time_span_highest_time_each_file[x][y];
        else if (strcmp("iowait", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_cpus_time_span_spike_each_file.cpu_iowait_time_span_highest_time_each_file[x][y];
        else if (strcmp("idle", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_cpus_time_span_spike_each_file.cpu_idle_time_span_highest_time_each_file[x][y];
        else
            return "error";
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("usr", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_cpus_time_span_spike_each_file.cpu_usr_time_span_lowest_time_each_file[x][y];
        else if (strcmp("sys", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_cpus_time_span_spike_each_file.cpu_sys_time_span_lowest_time_each_file[x][y];
        else if (strcmp("iowait", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_cpus_time_span_spike_each_file.cpu_iowait_time_span_lowest_time_each_file[x][y];
        else if (strcmp("idle", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_cpus_time_span_spike_each_file.cpu_idle_time_span_lowest_time_each_file[x][y];
        else
            return "error";
    } else
        return "error";
}

const char *get_tasks_time_span_spike_time_each_file(int x, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("proc", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_tasks_time_span_spike_each_file.proc_time_span_spike_time_each_file[x];
        else if (strcmp("cswch", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_tasks_time_span_spike_each_file.cswch_time_span_spike_time_each_file[x];
        else
            return "error";
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("proc", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_tasks_time_span_spike_each_file.proc_time_span_highest_time_each_file[x];
        else if (strcmp("cswch", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_tasks_time_span_spike_each_file.cswch_time_span_highest_time_each_file[x];
        else
            return "error";
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("proc", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_tasks_time_span_spike_each_file.proc_time_span_lowest_time_each_file[x];
        else if (strcmp("cswch", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_tasks_time_span_spike_each_file.cswch_time_span_lowest_time_each_file[x];
        else
            return "error";
    } else
        return "error";
}

const char *get_pswap_time_span_spike_time_each_file(int x, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("pswpin", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_pswaps_time_span_spike_each_file.pswpin_time_span_spike_time_each_file[x];
        else if (strcmp("pswpout", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_pswaps_time_span_spike_each_file.pswpout_time_span_spike_time_each_file[x];
        else
            return "error";
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("pswpin", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_pswaps_time_span_spike_each_file.pswpin_time_span_highest_time_each_file[x];
        else if (strcmp("pswpout", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_pswaps_time_span_spike_each_file.pswpout_time_span_highest_time_each_file[x];
        else
            return "error";
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("pswpin", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_pswaps_time_span_spike_each_file.pswpin_time_span_lowest_time_each_file[x];
        else if (strcmp("pswpout", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_pswaps_time_span_spike_each_file.pswpout_time_span_lowest_time_each_file[x];
        else
            return "error";
    } else
        return "error";
}

const char *get_paging_time_span_spike_time_each_file(int x, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("pgpgin", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_pagings_time_span_spike_each_file.pgpgin_time_span_spike_time_each_file[x];
        else if (strcmp("pgpgout", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_pagings_time_span_spike_each_file.pgpgout_time_span_spike_time_each_file[x];
        else if (strcmp("fault", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_pagings_time_span_spike_each_file.fault_time_span_spike_time_each_file[x];
        else if (strcmp("majflt", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_pagings_time_span_spike_each_file.majflt_time_span_spike_time_each_file[x];
        else if (strcmp("vmeff", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_pagings_time_span_spike_each_file.vmeff_time_span_spike_time_each_file[x];
        else
            return "error";
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("pgpgin", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_pagings_time_span_spike_each_file.pgpgin_time_span_highest_time_each_file[x];
        else if (strcmp("pgpgout", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_pagings_time_span_spike_each_file.pgpgout_time_span_highest_time_each_file[x];
        else if (strcmp("fault", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_pagings_time_span_spike_each_file.fault_time_span_highest_time_each_file[x];
        else if (strcmp("majflt", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_pagings_time_span_spike_each_file.majflt_time_span_highest_time_each_file[x];
        else if (strcmp("vmeff", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_pagings_time_span_spike_each_file.vmeff_time_span_highest_time_each_file[x];
        else
            return "error";
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("pgpgin", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_pagings_time_span_spike_each_file.pgpgin_time_span_lowest_time_each_file[x];
        else if (strcmp("pgpgout", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_pagings_time_span_spike_each_file.pgpgout_time_span_lowest_time_each_file[x];
        else if (strcmp("fault", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_pagings_time_span_spike_each_file.fault_time_span_lowest_time_each_file[x];
        else if (strcmp("majflt", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_pagings_time_span_spike_each_file.majflt_time_span_lowest_time_each_file[x];
        else if (strcmp("vmeff", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_pagings_time_span_spike_each_file.vmeff_time_span_lowest_time_each_file[x];
        else
            return "error";
    } else
        return "error";
}

const char *get_io_transfer_rate_time_span_spike_time_each_file(int x, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("tps", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_io_transfer_rates_time_span_spike_each_file.tps_time_span_spike_time_each_file[x];
        else if (strcmp("bread", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_io_transfer_rates_time_span_spike_each_file.bread_time_span_spike_time_each_file[x];
        else if (strcmp("bwrtn", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_io_transfer_rates_time_span_spike_each_file.bwrtn_time_span_spike_time_each_file[x];
        else
            return "error";
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("tps", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_io_transfer_rates_time_span_spike_each_file.tps_time_span_highest_time_each_file[x];
        else if (strcmp("bread", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_io_transfer_rates_time_span_spike_each_file.bread_time_span_highest_time_each_file[x];
        else if (strcmp("bwrtn", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_io_transfer_rates_time_span_spike_each_file.bwrtn_time_span_highest_time_each_file[x];
        else
            return "error";
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("tps", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_io_transfer_rates_time_span_spike_each_file.tps_time_span_lowest_time_each_file[x];
        else if (strcmp("bread", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_io_transfer_rates_time_span_spike_each_file.bread_time_span_lowest_time_each_file[x];
        else if (strcmp("bwrtn", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_io_transfer_rates_time_span_spike_each_file.bwrtn_time_span_lowest_time_each_file[x];
        else
            return "error";
    } else
        return "error";
}

const char *get_memory_time_span_spike_time_each_file(int x, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("memused", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_memories_time_span_spike_each_file.memused_time_span_spike_time_each_file[x];
        else if (strcmp("kbcommit", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_memories_time_span_spike_each_file.kbcommit_time_span_spike_time_each_file[x];
        else if (strcmp("commit", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_memories_time_span_spike_each_file.commit_time_span_spike_time_each_file[x];
        else
            return "error";
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("memused", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_memories_time_span_spike_each_file.memused_time_span_highest_time_each_file[x];
        else if (strcmp("kbcommit", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_memories_time_span_spike_each_file.kbcommit_time_span_highest_time_each_file[x];
        else if (strcmp("commit", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_memories_time_span_spike_each_file.commit_time_span_highest_time_each_file[x];
        else
            return "error";
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("memused", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_memories_time_span_spike_each_file.memused_time_span_lowest_time_each_file[x];
        else if (strcmp("kbcommit", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_memories_time_span_spike_each_file.kbcommit_time_span_lowest_time_each_file[x];
        else if (strcmp("commit", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_memories_time_span_spike_each_file.commit_time_span_lowest_time_each_file[x];
        else
            return "error";
    } else
        return "error";
}

const char *get_swpused_time_span_spike_time_each_file(int x, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0)
        return sar_analyzer_time_span_spike_obj->date_swaps_time_span_spike_each_file.swpused_time_span_spike_time_each_file[x];
    else if (strcmp("highest", analyze_item) == 0)
        return sar_analyzer_time_span_spike_obj->date_swaps_time_span_spike_each_file.swpused_time_span_highest_time_each_file[x];
    else if (strcmp("lowest", analyze_item) == 0)
        return sar_analyzer_time_span_spike_obj->date_swaps_time_span_spike_each_file.swpused_time_span_lowest_time_each_file[x];
    else
        return "error";
}

const char *get_kernel_table_time_span_spike_time_each_file(int x, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("dentunusd", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_kernel_tables_time_span_spike_each_file.dentunusd_time_span_spike_time_each_file[x];
        else if (strcmp("file", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_kernel_tables_time_span_spike_each_file.file_time_span_spike_time_each_file[x];
        else if (strcmp("inode", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_kernel_tables_time_span_spike_each_file.inode_time_span_spike_time_each_file[x];
        else
            return "error";
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("dentunusd", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_kernel_tables_time_span_spike_each_file.dentunusd_time_span_highest_time_each_file[x];
        else if (strcmp("file", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_kernel_tables_time_span_spike_each_file.file_time_span_highest_time_each_file[x];
        else if (strcmp("inode", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_kernel_tables_time_span_spike_each_file.inode_time_span_highest_time_each_file[x];
        else
            return "error";
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("dentunusd", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_kernel_tables_time_span_spike_each_file.dentunusd_time_span_lowest_time_each_file[x];
        else if (strcmp("file", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_kernel_tables_time_span_spike_each_file.file_time_span_lowest_time_each_file[x];
        else if (strcmp("inode", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_kernel_tables_time_span_spike_each_file.inode_time_span_lowest_time_each_file[x];
        else
            return "error";
    } else
        return "error";
}

const char *get_ldavg_time_span_spike_time_each_file(int x, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("runq_sz", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_ldavgs_time_span_spike_each_file.runq_sz_time_span_spike_time_each_file[x];
        else if (strcmp("plist_sz", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_ldavgs_time_span_spike_each_file.plist_sz_time_span_spike_time_each_file[x];
        else if (strcmp("ldavg_one", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_ldavgs_time_span_spike_each_file.ldavg_one_time_span_spike_time_each_file[x];
        else if (strcmp("ldavg_five", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_ldavgs_time_span_spike_each_file.ldavg_five_time_span_spike_time_each_file[x];
        else if (strcmp("ldavg_15", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_ldavgs_time_span_spike_each_file.ldavg_15_time_span_spike_time_each_file[x];
        else
            return "error";
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("runq_sz", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_ldavgs_time_span_spike_each_file.runq_sz_time_span_highest_time_each_file[x];
        else if (strcmp("plist_sz", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_ldavgs_time_span_spike_each_file.plist_sz_time_span_highest_time_each_file[x];
        else if (strcmp("ldavg_one", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_ldavgs_time_span_spike_each_file.ldavg_one_time_span_highest_time_each_file[x];
        else if (strcmp("ldavg_five", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_ldavgs_time_span_spike_each_file.ldavg_five_time_span_highest_time_each_file[x];
        else if (strcmp("ldavg_15", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_ldavgs_time_span_spike_each_file.ldavg_15_time_span_highest_time_each_file[x];
        else
            return "error";
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("runq_sz", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_ldavgs_time_span_spike_each_file.runq_sz_time_span_lowest_time_each_file[x];
        else if (strcmp("plist_sz", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_ldavgs_time_span_spike_each_file.plist_sz_time_span_lowest_time_each_file[x];
        else if (strcmp("ldavg_one", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_ldavgs_time_span_spike_each_file.ldavg_one_time_span_lowest_time_each_file[x];
        else if (strcmp("ldavg_five", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_ldavgs_time_span_spike_each_file.ldavg_five_time_span_lowest_time_each_file[x];
        else if (strcmp("ldavg_15", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_ldavgs_time_span_spike_each_file.ldavg_15_time_span_lowest_time_each_file[x];
        else
            return "error";
    } else
        return "error";
}

const char *get_block_device_time_span_spike_time_each_file(int x, int y, const char *element, const char *analyze_item)
{
    if (strcmp("spike", analyze_item) == 0) {
        if (strcmp("areqsz", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_block_devices_time_span_spike_each_file.areqsz_time_span_spike_time_each_file[x][y];
        else if (strcmp("util", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_block_devices_time_span_spike_each_file.util_time_span_spike_time_each_file[x][y];
        else
            return "error";
    } else if (strcmp("highest", analyze_item) == 0) {
        if (strcmp("areqsz", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_block_devices_time_span_spike_each_file.areqsz_time_span_highest_time_each_file[x][y];
        else if (strcmp("util", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_block_devices_time_span_spike_each_file.util_time_span_highest_time_each_file[x][y];
        else
            return "error";
    } else if (strcmp("lowest", analyze_item) == 0) {
        if (strcmp("areqsz", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_block_devices_time_span_spike_each_file.areqsz_time_span_lowest_time_each_file[x][y];
        else if (strcmp("util", element) == 0)
            return sar_analyzer_time_span_spike_obj->date_block_devices_time_span_spike_each_file.util_time_span_lowest_time_each_file[x][y];
        else
            return "error";
    } else
        return "error";
}
