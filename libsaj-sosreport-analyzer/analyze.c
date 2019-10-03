/*
 *  analyze.c - analyze functions 
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
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>
#include <errno.h>
#include "analyze.h"

int comment_analyzed_content(const char* file_name, const char* file_name_this)
{
    char str[MAX_LINE_LENGTH];
    memset(str, '\0', sizeof(str));
    if (strstr(file_name, "ifcfg-") != NULL) {
        snprintf(str, MAX_LINE_LENGTH - 1, "%s has no 'DNS' string.", file_name);
        append_list(&sos_analyze_obj, str);
        append_list(&sos_analyze_obj, " Consider setting DNS=x.x.x.x");
    } else if (strstr(file_name, "etc/resolv.conf") != NULL) {
        append_list(&sos_analyze_obj, " There should be a network trouble.");
        append_list(&sos_analyze_obj, " Add DNS servers to /etc/resolv.conf.");
        append_list(&sos_analyze_obj, " Add these lines to /etc/NetworkManager/NetworkManager.conf.");
        append_list(&sos_analyze_obj, " ----");
        append_list(&sos_analyze_obj, " [main]");
        append_list(&sos_analyze_obj, " dns=none");
        append_list(&sos_analyze_obj, " ----");
        append_list(&sos_analyze_obj, " Restart NetworkManager.");
    } else if (strstr(file_name, "sos_commands/networking/ethtool_-k") != NULL) {
        char str_f[MAX_FILE_NAME_LENGTH - 200];
        memset(str_f, '\0', sizeof(str_f));
        cut_str_from_the_last_given_str(str_f, reverse_the_string(str_f, (char *)file_name_this), "_");
        snprintf(str, MAX_FILE_NAME_LENGTH, " %s generic-receive-offload is on. \n Consider setting '# ethtool %s -k gro off'", str_f, str_f);
        append_list(&sos_analyze_obj, str);
    } else if (strstr(file_name, "proc/net/bonding/bond") != NULL) {
        char str_f[MAX_FILE_NAME_LENGTH - 200];
        memset(str_f, '\0', sizeof(str_f));
        snprintf(str, MAX_LINE_LENGTH - 1, "%s has down nic.", file_name);
        append_list(&sos_analyze_obj, str);
    } else if (strstr(file_name, "sos_commands/networking/ethtool_-S") != NULL) {
        char str_f[MAX_FILE_NAME_LENGTH - 200];
        memset(str_f, '\0', sizeof(str_f));
        snprintf(str, MAX_LINE_LENGTH - 1, "%s has unrecoverable errors.", file_name);
        append_list(&sos_analyze_obj, str);
    } else if (strstr(file_name, "ip_addr") != NULL) {
        char str_f[MAX_FILE_NAME_LENGTH - 200];
        memset(str_f, '\0', sizeof(str_f));
        snprintf(str, MAX_LINE_LENGTH - 1, "Found NICS in %s which has no carrier.", file_name);
        append_list(&sos_analyze_obj, str);
    } else if (strstr(file_name, "etc/hosts") != NULL) {
        char str_f[MAX_FILE_NAME_LENGTH - 200];
        memset(str_f, '\0', sizeof(str_f));
        size_t i = 0;
        i = strlen(echo_list(&hostname_sos_obj));
        /* stripping off '\n'*/
        char* str_tmp;
        str_tmp = (char*)echo_list(&hostname_sos_obj);
	if ((echo_list(&hostname_sos_obj)[i - 1] == '\n')) {
            str_tmp = (char*)echo_list(&hostname_sos_obj);
	    str_tmp[i - 1] = '\0';
        }
        snprintf(str, MAX_LINE_LENGTH - 1, "%s has no hostname '%s'.\nConsider setting '%s' to /etc/hosts.",
                 file_name, str_tmp, str_tmp);
        append_list(&sos_analyze_obj, str);
    } else {
        /*
         * snprintf(str, MAX_LINE_LENGTH - 1, "%s has no content.", file_name);
         * append_list(&sos_analyze_obj, str);
         */
    }
    return 0;
}

int content(const char* line)
{
    if (line[0] != '#')
        return 0;
    else 
        return 1;
    return 1;
}

int dns(const char* line)
{
    if (strstr(line, "DNS") != NULL)
        return 0;
    else 
        return 1;
    return 1;
}

int gro(const char* line)
{
    if (strstr(line, "generic-receive-offload: on") != NULL)
        return 0;
    else 
        return 1;
    return 1;
}

int mii_stat(const char* line)
{
    if (strstr(line, "MII Status: down") != NULL)
        return 0;
    else 
        return 1;
    return 1;
}

int ethtool_unrecoverable_error(const char* line)
{
    if ((strstr(line, "unrecoverable_errors") != NULL) &&
       (strstr(line, ": 0") == 0)) {
           return 0;
    }
    return 1;
}

int nic_has_no_carrier(const char* line)
{
    if (strstr(line, "NO-CARRIER") != NULL)
        return 0;
    return 1;
}

int etc_hosts_has_no_hostname(const char* line)
{
    if (strstr(line, echo_list(&hostname_sos_obj)) != NULL)
        return 1;
    return 0;
}

int is_some_file(const char* file_pattern, const char* file_name, char file_name_this[MAX_FILE_NAME_LENGTH])
{
    size_t file_len = 0;
    char str_r[MAX_FILE_NAME_LENGTH];
    memset(str_r, '\0', sizeof(str_r));
    file_len = strlen(file_name);
    reverse_the_string(str_r, (char*)file_name);
    for (size_t i =0; i < file_len; i++) {
        if (str_r[i] == '/') {
            str_r[i] = '\0';
        }
    }
    /* This will get filename from full path */
    /* Always remember that 'file_name_this' has no path information */
    reverse_the_string(file_name_this, str_r);
    if (strcmp("netsetting", file_pattern) == 0) {
        if (strstr(file_name_this, "ifcfg-") != NULL)
            return 1;
        if (strstr(file_name_this, "ethtool_-k") != NULL)
            return 2;
    } else if (strcmp("bond_chk", file_pattern) == 0) {
        if (strstr(file_name_this, "bond") != NULL)
            return 1;
    } else if (strcmp("ethtool_unrecoverable", file_pattern) == 0) {
        if (strstr(file_name_this, "ethtool_-S") != NULL)
            return 1;
    } else if (strcmp("nic_has_no_carrier", file_pattern) == 0) {
        if (strstr(file_name_this, "ip_addr") != NULL)
            return 1;
    } else if (strcmp("etc_hosts_has_no_hostname", file_pattern) == 0) {
        if ((strstr(file_name_this, "hosts") != NULL) &&
             (strstr(file_name_this, "hosts.") == 0))
            return 1;
    } else 
        return 0; 
    return 0;
}
