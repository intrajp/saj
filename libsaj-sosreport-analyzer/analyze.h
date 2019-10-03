/*
 *  analyze.h - analyze definitions
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

#ifndef SOSREPORT_ANALYZER_ANALYZE_H
#define SOSREPORT_ANALYZER_ANALYZE_H

#include "../common/global.h"
#include "common.h"

/*
 * comment_analyzed_content()
 *
 * This function comments something from file read 
 *
 */
int comment_analyzed_content(const char* file_name, const char* file_name_this);

/*
 * content()
 *
 * This function checks if the line is empty 
 * if not return 1
 *
 */
int content(const char* line);

/*
 * dns()
 *
 * This function checks if the line 'DNS' exists
 * if not return 1
 *
 */
int dns(const char* line);

/*
 * gro()
 *
 * This function checks if the line 'generic-receive-offload: on' exists
 * in ethtool_-k files,
 * if not return 1
 *
 */
int gro(const char* line);

/*
 * mii_stat()
 *
 * This function checks if the line 'MII Status: down' exists
 * in proc/net/bondig/bondX files,
 * if not return 1
 *
 */
int mii_stat(const char* line);

/*
 * ethtool_unrecoverable_error()
 *
 * This function checks if the line 'unrecoverable_errors: <NUMBER>' is > 0 
 * in ethtool_-S files,
 * if not return 1
 *
 */
int ethtool_unrecoverable_error(const char* line);

/*
 * nic_has_no_carrier()
 *
 * This function checks if the line has 'NIC: <NO-CARRIER...'
 * in ip_-a file,
 * if not return 1
 *
 */
int nic_has_no_carrier(const char* line);

/*
 * etc_hosts_has_no_hostname()
 *
 * This function checks if the line has 'hostname' of the machine.
 * in 'etc/hosts' file,
 * if not return 1
 *
 */
int etc_hosts_has_no_hostname(const char* line);

/*
 * is_network_setting_file()
 *
 * This function checks if the file is network setting file
 * if so, return 1
 *
 */
int is_some_file(const char* file_pattern, const char* file_name,
    char file_name_this[MAX_FILE_NAME_LENGTH]);

#endif /* SOSREPORT_ANALYZER_ANALYZE_H */
