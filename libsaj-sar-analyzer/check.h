/*
 *  check.h - check definitions
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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#ifndef SAJ_CHECK_H
#define SAJ_CHECK_H

/* These are declared externally and should be used in sanity checker */
int cpu = 0;
int proc_s = 0;
int pswpin_s = 0;
int pgpgin_s = 0;
int tps = 0;
int kbmemfree = 0;
int kbswpfree = 0;
int kbhugfree = 0;
int dentunusd = 0;
int runq_sz = 0;
int dev = 0;
int rxpck_s = 0;
int rxerr_s = 0;
int call_s = 0;
int scall_s = 0;
int totsck = 0;
int squeezd = 0;

int cpu_avg_checked_int = 0; 
int proc_s_avg_checked_int = 0; 
int pswpin_s_avg_checked_int = 0; 
int pgpgin_s_avg_checked_int = 0;
int tps_avg_checked_int = 0;
int kbmemfree_avg_checked_int = 0; 
int kbswpfree_avg_checked_int = 0; 
int kbhugfree_avg_checked_int = 0;
int dentunusd_avg_checked_int = 0; 
int runq_sz_avg_checked_int = 0; 
int dev_avg_checked_int = 0;
int rxpck_s_avg_checked_int = 0; 
int rxerr_s_avg_checked_int = 0;
int call_s_avg_checked_int = 0;
int scall_s_avg_checked_int = 0;
int totsck_avg_checked_int = 0;
int squeezd_avg_checked_int = 0;

char *cpu_avg_checked = "NG"; 
char *proc_s_avg_checked = "NG"; 
char *pswpin_s_avg_checked = "NG";
char *pgpgin_s_avg_checked = "NG";
char *tps_avg_checked = "NG";
char *kbmemfree_avg_checked = "NG"; 
char *kbswpfree_avg_checked = "NG";
char *kbhugfree_avg_checked = "NG";
char *dentunusd_avg_checked = "NG";
char *runq_sz_avg_checked = "NG";
char *dev_avg_checked = "NG";
char *rxpck_s_avg_checked = "NG";
char *rxerr_s_avg_checked = "NG";
char *call_s_avg_checked = "NG";
char *scall_s_avg_checked = "NG";
char *totsck_avg_checked = "NG";
char *squeezd_avg_checked = "NG";

void initialize_avg_checked_int(void);
#endif /* SAJ_CHECK_H */
