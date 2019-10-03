/*
 *  check.c - check functions 
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

#include "check.h"

void initialize_avg_checked_int(void) 
{
    cpu = 0;
    proc_s = 0;
    pswpin_s = 0;
    pgpgin_s = 0;
    tps = 0;
    kbmemfree = 0;
    kbswpfree = 0;
    kbhugfree = 0;
    dentunusd = 0;
    runq_sz = 0;
    dev = 0;
    rxpck_s = 0;
    rxerr_s = 0;
    call_s = 0;
    scall_s = 0;
    totsck = 0;
    squeezd = 0;

    cpu_avg_checked_int = 0; 
    proc_s_avg_checked_int = 0; 
    pswpin_s_avg_checked_int = 0; 
    pgpgin_s_avg_checked_int = 0;
    tps_avg_checked_int = 0;
    kbmemfree_avg_checked_int = 0; 
    kbswpfree_avg_checked_int = 0; 
    kbhugfree_avg_checked_int = 0;
    dentunusd_avg_checked_int = 0; 
    runq_sz_avg_checked_int = 0; 
    dev_avg_checked_int = 0;
    rxpck_s_avg_checked_int = 0; 
    rxerr_s_avg_checked_int = 0;
    call_s_avg_checked_int = 0;
    scall_s_avg_checked_int = 0;
    totsck_avg_checked_int = 0;
    squeezd_avg_checked_int = 0;

    cpu_avg_checked = "NG"; 
    proc_s_avg_checked = "NG"; 
    pswpin_s_avg_checked = "NG";
    pgpgin_s_avg_checked = "NG";
    tps_avg_checked = "NG";
    kbmemfree_avg_checked = "NG"; 
    kbswpfree_avg_checked = "NG";
    kbhugfree_avg_checked = "NG";
    dentunusd_avg_checked = "NG";
    runq_sz_avg_checked = "NG";
    dev_avg_checked = "NG";
    rxpck_s_avg_checked = "NG";
    rxerr_s_avg_checked = "NG";
    call_s_avg_checked = "NG";
    scall_s_avg_checked = "NG";
    totsck_avg_checked = "NG";
    squeezd_avg_checked = "NG";
}
