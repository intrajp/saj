/*
 *  common.c - common functions 
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
#include "../common/global.h"
#include "common.h"
#include "cfg.h"
#include "analyze.h"

/* member_obj */
struct member_data member_obj_raw =
    {
        "\0", /* each member name */
        0, /* each member's mcinfo. 1 is mcinfo and 0 is sosreport */
        false, /* each member's read_dir. true reads dir ( some not dir will be included ) */
        false, /* read directory recursively. true reads dir recursively */
        false, /* read files in the root directory. true reads files in the root dir */
        "\0", /* each member sub_title */
        0, /* each member's item number */
        0, /* each member's file number */
        {{"\0"}}, /* each member's item name */
        {{"\0"}}, /* each member's file names */
        0, /* each member's item max */
        NULL /* next pointer */
    };

/* sos_dir_file_obj */
struct dir_file_name sos_dir_file_obj_raw = 
    {{"test.txt", "test.txt", "test.txt", "19700101000000","test.txt", "test.txt", "test.txt"}};

/* hostname_sos_obj */
struct line_data hostname_sos_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* sos_version_obj */
struct line_data sos_version_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* sos_header_obj */
struct line_data sos_header_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* sos_analyze_file_obj */
struct line_data sos_analyze_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* sos_subtitle_analyze_obj */
struct line_data sos_subtitle_analyze_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* sos_subtitle_general_obj */
struct line_data sos_subtitle_general_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* sos_subtitle_member_obj */
struct line_data sos_subtitle_member_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* line_obj */
struct line_data sos_line_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* tail_obj */
struct line_data sos_tail_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* dir_read_obj */
struct line_data dir_read_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* log_obj */
struct line_data log_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };


/* making pointers to the structs */
volatile node_m* member_obj = &member_obj_raw;
struct dir_file_name *sos_dir_file_obj = &sos_dir_file_obj_raw;
struct line_data* hostname_sos_obj = &hostname_sos_obj_raw;
struct line_data* sos_version_obj = &sos_version_obj_raw;
struct line_data* sos_header_obj = &sos_header_obj_raw;
struct line_data* sos_analyze_obj = &sos_analyze_obj_raw;
struct line_data* sos_subtitle_analyze_obj = &sos_subtitle_analyze_obj_raw;
struct line_data* sos_subtitle_general_obj = &sos_subtitle_general_obj_raw;
struct line_data* sos_subtitle_member_obj = &sos_subtitle_member_obj_raw;
struct line_data* sos_line_obj = &sos_line_obj_raw;
struct line_data* sos_tail_obj = &sos_tail_obj_raw;
struct line_data* dir_read_obj = &dir_read_obj_raw;
struct line_data* log_obj = &log_obj_raw;

char* str_arr_tmp[MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR];
char* str_arr_tmp_2[MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR];

static int __log_info(node** obj, const char* str)
{
    char log_string[MAX_LINE_LENGTH + 1];  
    memset(log_string, '\0', sizeof(log_string));
    strncpy(log_string, str, MAX_LINE_LENGTH);
    printf("%s\n", log_string);
    append_list(&log_obj, log_string);

    return 0;
}

int initialize_objects(void)
{
    /* initialize the member list object (node_m) */
    init_member(&member_obj);
    /* initialize the line list object (node) */
    /* sos_dir_file_obj doesn't need to be initialized */
    init_list(&hostname_sos_obj);
    init_list(&sos_version_obj);
    init_list(&sos_header_obj);
    init_list(&sos_analyze_obj);
    init_list(&sos_subtitle_analyze_obj);
    init_list(&sos_subtitle_general_obj);
    init_list(&sos_subtitle_member_obj);
    init_list(&sos_line_obj);
    init_list(&sos_tail_obj);
    init_list(&tmp_obj);
    init_list(&dir_read_obj);
    init_list(&log_obj);
    return 0;
}

static int __is_file(const char* path)
{
    struct stat path_stat;
    lstat(path, &path_stat);
    if (S_ISDIR(path_stat.st_mode))
        return 0;
    return 1;
}

static int __read_analyze_dir(const volatile char* member, const char* dname, int recursive,
                              int mcinfo, int sar_only)
{
    DIR* dir = NULL;
    struct dirent *dp;
    size_t str_len = 0;
    size_t str_len_fname_part = 0;
    size_t str_len_dname_full = 0;
    char* fname_part = NULL;
    char* dname_full = (char *)dname;
    char full_path[MAX_FILE_NAME_LENGTH];  
    char read_path[MAX_FILE_NAME_LENGTH];  
    char str_ret[MAX_FILE_NAME_LENGTH];  
    char str_orig[MAX_FILE_NAME_LENGTH];  
    char fname_part_path[MAX_FILE_NAME_LENGTH];  
    char log_string_1[MAX_LINE_LENGTH];  
    char log_string_2[MAX_LINE_LENGTH];  
    char log_string_3[MAX_LINE_LENGTH];  
    char log_string_4[MAX_LINE_LENGTH];  
    char log_string_5[MAX_LINE_LENGTH];  
    memset(full_path, '\0', sizeof(full_path)); 
    memset(read_path, '\0', sizeof(read_path)); 
    memset(str_orig, '\0', sizeof(str_orig)); 
    memset(fname_part_path, '\0', sizeof(fname_part_path)); 
    memset(log_string_1, '\0', sizeof(log_string_1)); 
    memset(log_string_2, '\0', sizeof(log_string_2)); 
    memset(log_string_3, '\0', sizeof(log_string_3)); 
    memset(log_string_4, '\0', sizeof(log_string_4)); 
    memset(log_string_5, '\0', sizeof(log_string_5)); 

    snprintf(full_path, MAX_LINE_LENGTH, "%s/%s", dname, member);

    str_len = strlen(full_path);
    if (str_len == 0) {
        fprintf(stderr, "Path 1 is too short (%s): %ld %s\n", full_path, str_len, strerror(errno));
        free_sosreport_analyzer_obj(sar_only);
        exit(EXIT_FAILURE);
    }
    full_path[str_len] = '\0';

    char str_c[MAX_FILE_NAME_LENGTH];
    memset(str_c, '\0', sizeof(str_c));
    char str_r[MAX_FILE_NAME_LENGTH];
    memset(str_r, '\0', sizeof(str_r));
    fname_part = cut_str_from_the_last_given_str(str_ret, reverse_the_string(str_r, full_path), "/");

    snprintf(fname_part_path, MAX_LINE_LENGTH, "%s", fname_part);
    str_len_fname_part = strlen(fname_part);
    str_len_dname_full = str_len - str_len_fname_part;
    if (str_len_dname_full == 0) {
        fprintf(stderr, "Path 2 is too short %ld %s\n", str_len_dname_full, strerror(errno));
        free_sosreport_analyzer_obj(sar_only);
        exit(EXIT_FAILURE);
    }

    /* replace the full directory name */
    if (recursive == 0)
        cut_str_by_the_last_given_str(dname_full, full_path, "/");
    if (dname_full != NULL) {
        /* if open directory fails, exit with error message,
         * and print that the member should be set to 'skip'.
         */
        if ((dir = opendir(dname_full)) == NULL) 
            /* not to segfault */
            return 1;
    }

    char* str = NULL;
    int i = 0;
    /* limit of fname_part files to be analyzed */
    int str_arr_valid_size = 0;

    /* read from directory and set in an array */
    for (dp = readdir(dir), i = 0; dp != NULL; dp = readdir(dir)) {
        char full_path_plus_str[MAX_LINE_LENGTH - 100];  
        char filename[MAX_LINE_LENGTH - 100];  
        memset(full_path_plus_str, '\0', sizeof(full_path_plus_str)); 
        memset(filename, '\0', sizeof(filename)); 

        str = dp->d_name;

        if ((dp->d_type != DT_REG) && (dp->d_type != DT_DIR) && (dp->d_type != DT_LNK))
            continue;

        /*###FIX ME
         * cil or hll... is selinux stuff and human can't read, so...
         * others have big one, compressed or selinux modules.
         * in proc/ there are some files which have only write permissions and couldn't be read.
         *
         * We should check file with a function and if the file is too big, skip it. 
         * Now, if file size is over MAX_ANALYZE_FILE_SIZE (default 10Mbytes), skip it.
         */
        snprintf(filename, MAX_LINE_LENGTH, "%s%s", dname_full, str);
        struct stat st;
        stat(filename, &st);

        if (access(str, R_OK) == 0)
            continue;

        size_t size = 0;
        size = st.st_size;
        if (size == 0) {
            snprintf(log_string_1, MAX_LINE_LENGTH, "Skipping this file:%s (file size is %ld)",
                filename,size);
            append_list(&log_obj, log_string_1);
            continue;
        }
        if (size > MAX_ANALYZE_FILE_SIZE) {
            snprintf(log_string_2, MAX_LINE_LENGTH, "Skipping this file:%s (file size %ld exceeds %d)",
                filename, size, MAX_ANALYZE_FILE_SIZE);
            append_list(&log_obj, log_string_2);
            continue;
        }

        if (((strcmp((const char*)member, "cmdlog/") == 0) && (strstr(str, "verbose") != NULL)) ||
            (((strcmp((const char*)member, "etc/") == 0) || (strcmp ((const char *)member, "etc/selinux/") == 0)) &&
            ((strstr(str, "cil") != NULL) || (strstr (str, "hll") != NULL))) ||
            ((strstr((const char*)member, "etc/") != NULL) && ((strstr(str, ".bin") != NULL ) || (strstr(str, ".kern") != NULL))) ||
            ((strstr((const char*)member, "etc/") != NULL) && ((strstr(str, ".db") != NULL ) || (strstr(str, "policy.") != NULL))) ||
            ((strstr((const char*)member, "etc/") != NULL) && ((strstr(str, "lang_ext") != NULL) || (strstr(str, ".pp") != NULL))) ||
            ((strcmp((const char*)member, "etc/") == 0) && (strstr(str, "commit_num") != NULL)) ||
            ((strstr((const char*)member, "etc/pki/") != NULL) && (strcmp(str, "cacerts") == 0)) ||
            ((strstr((const char*)member, "etc/") != NULL) && (strcmp(str, "cacerts") == 0)) ||
            ((strcmp((const char*)member, "proc/") == 0) && ((strstr(str, "register") != NULL) || (strstr(str, "compact_memory") != NULL))) ||
            ((strcmp((const char*)member, "proc/") == 0) && ((strstr(str, "flush") != NULL))) ||
            ((strcmp((const char*)member, "proc/") == 0) && ((strstr(filename, "proc/1") != NULL))) ||
            ((strcmp((const char*)member, "proc/") == 0) && ((strstr(filename, "proc/2") != NULL))) ||
            ((strcmp((const char*)member, "proc/") == 0) && ((strstr(filename, "proc/3") != NULL))) ||
            ((strcmp((const char*)member, "proc/") == 0) && ((strstr(filename, "proc/4") != NULL))) ||
            ((strcmp((const char*)member, "proc/") == 0) && ((strstr(filename, "proc/5") != NULL))) ||
            ((strcmp((const char*)member, "proc/") == 0) && ((strstr(filename, "proc/6") != NULL))) ||
            ((strcmp((const char*)member, "proc/") == 0) && ((strstr(filename, "proc/7") != NULL))) ||
            ((strcmp((const char*)member, "proc/") == 0) && ((strstr(filename, "proc/8") != NULL))) ||
            ((strcmp((const char*)member, "proc/") == 0) && ((strstr(filename, "proc/9") != NULL))) ||
            ((strcmp((const char*)member, "proc/") == 0) && ((strstr(str, "purge") != NULL) || (strstr(str, "rebase") != NULL)))||
            /* sometimes ethtool_-d files are too big */
            ((strcmp((const char*)member, "sos_commands/networking/") == 0) && ((strstr(filename, "ethtool_-d") != NULL))) ||
            (strstr((const char*)filename, ".gz") != NULL) || 
            (strstr((const char*)filename, ".zip") != NULL) || 
            ((strcmp((const char*)member, "var/") == 0) && (strstr(str, "sa0") != NULL)) ||
            ((strcmp((const char*)member, "var/") == 0) && (strstr(str, "sa1") != NULL)) ||
            ((strcmp((const char*)member, "var/") == 0) && (strstr(str, "sa2") != NULL)) ||
            ((strcmp((const char*)member, "var/") == 0) && (strstr(str, "sa3") != NULL)) ||
            ((strcmp((const char*)member, "var/") == 0) && (strstr(str, "nova") != NULL))) {
            snprintf(log_string_3, MAX_LINE_LENGTH, "Skipping this file:%s (Invalid file.)", filename);
            append_list(&log_obj, log_string_3);
            continue;
        }
        /* should be edited here if new member is added */
        if  ( 
              ((strcmp((const char*)member, "etc/") == 0) && 
              (((strstr(filename, "etc/NetworkManager/") != NULL)) ||
              ((strstr(filename, "etc/X11/") != NULL)) ||
              ((strstr(filename, "etc/alternatives/") != NULL)) ||
              ((strstr(filename, "etc/alsa/") != NULL)) ||
              ((strstr(filename, "etc/anacrontab") != NULL)) ||
              ((strstr(filename, "etc/ansible/") != NULL)) ||
              ((strstr(filename, "etc/audit/") != NULL)) ||
              ((strstr(filename, "etc/chrony.conf") != NULL)) ||
              ((strstr(filename, "etc/corosync/") != NULL)) ||
              ((strstr(filename, "etc/crontab") != NULL)) ||
              ((strstr(filename, "etc/cron.deny") != NULL)) ||
              ((strstr(filename, "etc/cron.d/") != NULL)) ||
              ((strstr(filename, "etc/cron.hourly/") != NULL)) ||
              ((strstr(filename, "etc/cron.daily/") != NULL)) ||
              ((strstr(filename, "etc/cron.weekly/") != NULL)) ||
              ((strstr(filename, "etc/cron.monthly/") != NULL)) ||
              ((strstr(filename, "etc/cups/") != NULL)) ||
              ((strstr(filename, "etc/dbus-1/") != NULL)) ||
              ((strstr(filename, "etc/default/") != NULL)) ||
              ((strstr(filename, "etc/dhcp/") != NULL)) ||
              ((strstr(filename, "etc/dnf/") != NULL)) ||
              ((strstr(filename, "etc/dnsmasq.conf") != NULL)) ||
              ((strstr(filename, "etc/dracut.conf") != NULL)) ||
              ((strstr(filename, "etc/environment") != NULL)) ||
              ((strstr(filename, "etc/fcoe/") != NULL)) ||
              ((strstr(filename, "etc/fedora-release") != NULL)) ||
              ((strstr(filename, "etc/firewalld/") != NULL)) ||
              ((strstr(filename, "etc/fstab") != NULL)) ||
              ((strstr(filename, "etc/gdm/") != NULL)) ||
              ((strstr(filename, "etc/grub.d/") != NULL)) ||
              ((strstr(filename, "etc/gss/") != NULL)) ||
              ((strstr(filename, "etc/gssproxy/") != NULL)) ||
              ((strstr(filename, "etc/host") != NULL)) ||
              ((strstr(filename, "etc/httpd/") != NULL)) ||
              ((strstr(filename, "etc/iproute2/") != NULL)) ||
              ((strstr(filename, "etc/ipsec.conf") != NULL)) ||
              ((strstr(filename, "etc/ipsec.d/") != NULL)) ||
              ((strstr(filename, "etc/java/") != NULL)) ||
              ((strstr(filename, "etc/kdump.conf") != NULL)) ||
              ((strstr(filename, "etc/krb5.conf") != NULL)) ||
              ((strstr(filename, "etc/krb5.conf.d/") != NULL)) ||
              ((strstr(filename, "etc/ld.so.conf") != NULL)) ||
              ((strstr(filename, "etc/ld.so.conf.d/") != NULL)) ||
              ((strstr(filename, "etc/libvirt/") != NULL)) ||
              ((strstr(filename, "etc/locale.conf") != NULL)) ||
              ((strstr(filename, "etc/logrotate.conf") != NULL)) ||
              ((strstr(filename, "etc/logrotate.d/") != NULL)) ||
              ((strstr(filename, "etc/lvm/") != NULL)) ||
              ((strstr(filename, "etc/machine-id") != NULL)) ||
              ((strstr(filename, "etc/mail/") != NULL)) ||
              ((strstr(filename, "etc/modprobe.d/") != NULL)) ||
              ((strstr(filename, "etc/multipath.conf") != NULL)) ||
              ((strstr(filename, "sos_commands/multipath/") != NULL)) ||
              ((strstr(filename, "etc/networks") != NULL)) ||
              ((strstr(filename, "etc/nfs.conf") != NULL)) ||
              ((strstr(filename, "etc/nfsmount.conf") != NULL)) ||
              ((strstr(filename, "etc/nftables/") != NULL)) ||
              ((strstr(filename, "etc/nslcd.conf") != NULL)) ||
              ((strstr(filename, "etc/nsswitch.conf") != NULL)) ||
              ((strstr(filename, "etc/oddjobd/") != NULL)) ||
              ((strstr(filename, "etc/oddjobd.conf.d/") != NULL)) ||
              ((strstr(filename, "etc/openldap/") != NULL)) ||
              ((strstr(filename, "etc/os-release") != NULL)) ||
              ((strstr(filename, "etc/pam.d/") != NULL)) ||
              ((strstr(filename, "etc/pki/") != NULL)) ||
              ((strstr(filename, "etc/postfix/") != NULL)) ||
              ((strstr(filename, "etc/ppp/") != NULL)) ||
              ((strstr(filename, "etc/rc.d") != NULL)) ||
              ((strstr(filename, "etc/redhat-release") != NULL)) ||
              ((strstr(filename, "etc/resolv.conf") != NULL)) ||
              ((strstr(filename, "etc/rsyslog.conf") != NULL)) ||
              ((strstr(filename, "etc/samba/") != NULL)) ||
              ((strstr(filename, "etc/selinux/") != NULL)) ||
              ((strstr(filename, "etc/sestatus.conf") != NULL)) ||
              ((strstr(filename, "etc/snmp/") != NULL)) ||
              ((strstr(filename, "etc/sos.conf") != NULL)) ||
              ((strstr(filename, "etc/ssh/") != NULL)) ||
              ((strstr(filename, "etc/sudoers") != NULL)) ||
              ((strstr(filename, "etc/sudoers.d/") != NULL)) ||
              ((strstr(filename, "etc/sysconfig/") != NULL)) ||
              ((strstr(filename, "etc/sysconfig/network-scripts/ifcfg-") != NULL)) ||
              ((strstr(filename, "etc/systemd/system/") != NULL)) ||
              ((strstr(filename, "etc/systemd/") != NULL)) ||
              ((strstr(filename, "etc/system-release") != NULL)) ||
              ((strstr(filename, "etc/sysctl.conf") != NULL)) ||
              ((strstr(filename, "etc/udev/") != NULL)) ||
              ((strstr(filename, "etc/vconsole.conf") != NULL)) ||
              ((strstr(filename, "etc/yum.conf") != NULL)) ||
              ((strstr(filename, "etc/yum.repos.d/") != NULL)) ||
              ((strstr(filename, "etc/yum/") != NULL)))) ||
              ((strcmp((const char*)member, "proc/") == 0 ) &&
              (((strstr(filename, "proc/buddyinfo") != NULL)) ||
              ((strstr(filename, "proc/cpuinfo") != NULL)) ||
              ((strstr(filename, "proc/interrupts") != NULL)) ||
              ((strstr(filename, "proc/iomem") != NULL)) ||
              ((strstr(filename, "proc/meminfo") != NULL)) ||
              ((strstr(filename, "proc/net/bonding/") != NULL)) ||
              ((strstr(filename, "proc/net/dev") != NULL)) ||
              ((strstr(filename, "proc/net/sockstat") != NULL)) ||
              ((strstr(filename, "proc/slabinfo") != NULL)) ||
              ((strstr(filename, "proc/timer_list") != NULL)) ||
              ((strstr(filename, "proc/timer_stats") != NULL)) ||
              ((strstr(filename, "proc/vmallocinfo") != NULL)) ||
              ((strstr(filename, "proc/vmstat") != NULL)) ||
              ((strstr(filename, "proc/zoneinfo" ) != NULL)))) ||
              ((strcmp((const char*)member, "sos_commands/") == 0 ) &&
              (((strstr(filename, "sos_commands/abrt/") != NULL)) ||
              ((strstr(filename, "sos_commands/alternatives/") != NULL)) ||
              ((strstr(filename, "sos_commands/ansible/") != NULL)) ||
              ((strstr(filename, "sos_commands/apache/") != NULL)) ||
              ((strstr(filename, "sos_commands/auditd/") != NULL)) ||
              ((strstr(filename, "sos_commands/block/") != NULL)) || 
              ((strstr(filename, "sos_commands/boot/") != NULL)) || 
              ((strstr(filename, "sos_commands/bootloader/") != NULL)) || 
              ((strstr(filename, "sos_commands/btrfs/") != NULL)) || 
              ((strstr(filename, "sos_commands/ceph/") != NULL)) || 
              ((strstr(filename, "sos_commands/cgroups/") != NULL)) || 
              ((strstr(filename, "sos_commands/chrony/") != NULL)) || 
              ((strstr(filename, "sos_commands/corosync/") != NULL)) || 
              ((strstr(filename, "sos_commands/crypto/") != NULL)) || 
              ((strstr(filename, "sos_commands/cups/") != NULL)) || 
              ((strstr(filename, "sos_commands/date/") != NULL)) || 
              ((strstr(filename, "sos_commands/dbus/") != NULL)) || 
              ((strstr(filename, "sos_commands/devicemapper/") != NULL)) ||
              ((strstr(filename, "sos_commands/devices/") != NULL)) ||
              ((strstr(filename, "sos_commands/dnf/") != NULL)) ||
              ((strstr(filename, "sos_commands/docker/") != NULL)) ||
              ((strstr(filename, "sos_commands/dracut/") != NULL)) ||
              ((strstr(filename, "sos_commands/fcoe/") != NULL)) ||
              ((strstr(filename, "sos_commands/filesys/") != NULL)) ||
              ((strstr(filename, "sos_commands/firewalld/") != NULL)) ||
              ((strstr(filename, "sos_commands/gdm/") != NULL)) ||
              ((strstr(filename, "sos_commands/gfs2/") != NULL)) ||
              ((strstr(filename, "sos_commands/gluster/") != NULL)) ||
              ((strstr(filename, "sos_commands/haproxy/") != NULL)) ||
              ((strstr(filename, "sos_commands/host/hostname") != NULL)) ||
              ((strstr(filename, "sos_commands/host/uptime") != NULL)) ||
              ((strstr(filename, "sos_commands/hpasm/") != NULL)) ||
              ((strstr(filename, "sos_commands/i18n/") != NULL)) ||
              ((strstr(filename, "sos_commands/ipmitool/") != NULL)) ||
              ((strstr(filename, "sos_commands/java/") != NULL)) ||
              ((strstr(filename, "sos_commands/kernel/lsmod") != NULL)) ||
              ((strstr(filename, "sos_commands/kernel/sysctl_-a") != NULL)) ||
              ((strstr(filename, "sos_commands/kernel/uname_-a") != NULL)) ||
              ((strstr(filename, "sos_commands/krb5/") != NULL)) ||
              ((strstr(filename, "sos_commands/kvm/") != NULL)) ||
              ((strstr(filename, "sos_commands/last/last") != NULL)) ||
              ((strstr(filename, "sos_commands/ldap/") != NULL)) ||
              ((strstr(filename, "sos_commands/libraries/") != NULL)) ||
              ((strstr(filename, "sos_commands/libvirt/") != NULL)) ||
              ((strstr(filename, "sos_commands/logrotate/") != NULL)) ||
              ((strstr(filename, "sos_commands/logs/journalctl_--disk-usage") != NULL)) ||
              ((strstr(filename, "sos_commands/logs/journalctl_--no-pager") != NULL)) ||
              ((strstr(filename, "sos_commands/lstopo/") != NULL)) ||
              ((strstr(filename, "sos_commands/lvm2/") != NULL)) ||
              ((strstr(filename, "sos_commands/md/") != NULL)) ||
              ((strstr(filename, "sos_commands/memory/") != NULL)) ||
              ((strstr(filename, "sos_commands/networking/") != NULL)) ||
              ((strstr(filename, "sos_commands/networkmanager/") != NULL)) ||
              ((strstr(filename, "sos_commands/nis/") != NULL)) ||
              ((strstr(filename, "sos_commands/numa/") != NULL)) ||
              ((strstr(filename, "sos_commands/opengl/") != NULL)) ||
              ((strstr(filename, "sos_commands/openshift/") != NULL)) ||
              ((strstr(filename, "sos_commands/openswan/") != NULL)) ||
              ((strstr(filename, "sos_commands/pam/") != NULL)) ||
              ((strstr(filename, "sos_commands/pci/lspci_-nnvv") != NULL)) ||
              ((strstr(filename, "sos_commands/pci/") != NULL)) ||
              ((strstr(filename, "sos_commands/perl/") != NULL)) ||
              ((strstr(filename, "sos_commands/postfix/") != NULL)) ||
              ((strstr(filename, "sos_commands/ppp/") != NULL)) ||
              ((strstr(filename, "sos_commands/processor/") != NULL)) ||
              ((strstr(filename, "sos_commands/process/ps_auxwww") != NULL)) ||
              ((strstr(filename, "sos_commands/process/") != NULL)) ||
              ((strstr(filename, "sos_commands/release/lsb_release") != NULL)) ||
              ((strstr(filename, "sos_commands/release/") != NULL)) ||
              ((strstr(filename, "sos_commands/ruby/") != NULL)) ||
              ((strstr(filename, "sos_commands/samba/") != NULL)) ||
              ((strstr(filename, "sos_commands/sar/") != NULL)) ||
              ((strstr(filename, "sos_commands/scsi/lsscsi/") != NULL)) ||
              ((strstr(filename, "sos_commands/selinux/") != NULL)) ||
              ((strstr(filename, "sos_commands/sendmail/") != NULL)) ||
              ((strstr(filename, "sos_commands/soundcard/") != NULL)) ||
              ((strstr(filename, "sos_commands/sssd/") != NULL)) ||
              ((strstr(filename, "sos_commands/startup/") != NULL)) ||
              ((strstr(filename, "sos_commands/sunrpc/") != NULL)) ||
              ((strstr(filename, "sos_commands/systemtap/") != NULL)) ||
              ((strstr(filename, "sos_commands/usb/") != NULL)) ||
              ((strstr(filename, "sos_commands/virsh/") != NULL)) ||
              ((strstr(filename, "sos_commands/x11/") != NULL)) ||
              ((strstr(filename, "sos_commands/yum/") != NULL)) ||
              ((strstr(filename, "sos_commands/wireless/") != NULL)))) ||
              ((strcmp((const char*)member, "sos_commands/networking/") == 0 ) &&
              (((strstr(filename, "sos_commands/networking/ethtool_-S") != NULL)) ||
              ((strstr(filename, "sos_commands/networking/ethtool_-i") != NULL)) ||
              ((strstr(filename, "ip_addr") != NULL)))) ||
              ((strcmp((const char*)member, "usr/") == 0) &&
              (((strcmp(str, "usr/lib/dracut/") == 0)) ||
              ((strcmp(str, "usr/lib/udev/") == 0)) ||
              ((strcmp(str, "usr/lib/modules/") == 0)) ||
              ((strcmp(str, "usr/lib/sysctl.d/") == 0)) ||
              ((strcmp(str, "usr/lib/systemd/") == 0)) ||
              ((strcmp(str, "usr/share/alsa/") == 0)) ||
              ((strcmp(str, "usr/share/crypto-policies/") == 0)) ||
              ((strcmp(str, "usr/share/zoneinfo/") == 0)))) ||
              ((strcmp((const char*)member, "var/") == 0) &&
              (((strstr(str, "journal") != NULL )) ||
              ((strstr(filename, "var/log/audit/") != NULL)) ||
              ((strstr(filename, "var/log/cron") != NULL)) ||
              ((strstr(filename, "var/lib/chrony/") != NULL)) ||
              ((strstr(filename, "var/lib/dbus/") != NULL)) ||
              ((strstr(filename, "var/log/firewalld") != NULL)) ||
              ((strstr(filename, "var/lib/httpd/") != NULL)) ||
              ((strstr(filename, "var/lib/logrotate/") != NULL)) ||
              ((strstr(filename, "var/log/messages") != NULL)) ||
              ((strstr(filename, "var/log/secure") != NULL)) ||
              ((strstr(filename, "var/log/sa") != NULL)) ||
              ((strstr(filename, "var/crash/") != NULL)) || 
              ((strcmp(str, "dmesg") == 0))))
            ) {
            snprintf(log_string_4, MAX_LINE_LENGTH,
                "Skipping this file:%s (Should have already been analyzed.)",
                filename);
            append_list(&log_obj, log_string_4);
            continue;
        }

        /* We've already eliminated files which we try not to read, so here,
         * we try to read files recursively
         */
        volatile node_m* ptr_tmp_m = member_obj;
        while (ptr_tmp_m != NULL) {
            if (
                ((strcmp((const char*)ptr_tmp_m->_member, (const char*)member) == 0) &&
                    (ptr_tmp_m->mcinfo == mcinfo)
                     && (ptr_tmp_m->dir_recursive_read == true))
                &&
                /* try to read all files in the directory */
                ((recursive == 0) || (recursive == 1))
            ) {
                if (dp->d_type == DT_DIR) {
                    snprintf(full_path_plus_str, MAX_LINE_LENGTH, "%s%s/", dname_full, str);
                    /* call myself and read files in the directory */
                    snprintf(log_string_5, MAX_LINE_LENGTH, "Reading files in the directory '%s'",
                        full_path_plus_str);
                    append_list(&log_obj, log_string_5);
                    __read_analyze_dir(member, full_path_plus_str, 1, mcinfo, sar_only);
                }
            }
            ptr_tmp_m = ptr_tmp_m->next;
        }

        int do_continue = 0;
        ptr_tmp_m = member_obj;
        while (ptr_tmp_m != NULL) {
            if (
                    ((strcmp((const char*)ptr_tmp_m->_member, (const char*)member) == 0) &&
                        (ptr_tmp_m->mcinfo == mcinfo) &&
                    (ptr_tmp_m->dir_recursive_read == true) && (ptr_tmp_m->dir_root_read == false))
                    &&
                    /* try to read all files in the directory */
                    (recursive == 0)
               ) {
                do_continue = 1;
                break;
            }
            ptr_tmp_m = ptr_tmp_m->next;
        }

        if (do_continue == 1)
            continue;

        /*
         *  find files with name fname_part 
         */
        if (strstr(str, fname_part) != NULL) {
            /* so, only fname_part files will remain */
            snprintf(read_path, MAX_LINE_LENGTH, "%s%s", dname_full, str);
            /* read directory of which member's read_dir is true */
            ptr_tmp_m = member_obj;
            while (ptr_tmp_m != NULL) {
                if ((strcmp((const char*)ptr_tmp_m->_member, (const char*)member) == 0) &&
                   (ptr_tmp_m->mcinfo == mcinfo) && (ptr_tmp_m->read_dir == true)) {
                    /* file names will be stored ( not sorted yet ) */
                    append_list(&tmp_obj, read_path);
                }
                ptr_tmp_m = ptr_tmp_m->next;
            }
            i++; /* needed here */
            str_arr_valid_size++;
            if (str_arr_valid_size > MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR)
                break;
        }
    }
    closedir(dir);

    return 0;
}

/* These are the items to be analyzed not statically nor checked by multi-lines */
static int system_information = 0;
static int processor_information = 0;
static int bios_information = 0;
static int memory_array_information = 0;
static int memory_information = 0;
static int soft_lockup = 0;

/*
 * append_item_to_line_obj()
 *
 * This function check line and if something matches, append to line_obj 
 *
 */
static int __append_item_to_sos_line_obj(char* line, const char* member, const char* item)
{
    /* ### FIXME
     * These should echo only needed lines, note item number is limited by the new function
     */
    /* First, check if item has 'all'. When item is 'all', should echo every lines */
    if (strcmp(item, "all") == 0)
            return 0;
    if ((strcmp(member, "dmidecode") == 0) && (strcmp(item, "Processor") == 0)) {
        /* This should be the first line of the related paragraph, so set 1 to the parameter */
        if (strcmp(line, "Processor Information") == 0)
            processor_information = 1;
        /* set 0 to the parameter for this part */
        if (strstr(line , "Socket Designation:") != 0) {
            processor_information = 0;
            return 1;
        }
        if (processor_information == 1)
            return 2;
        /* This should be the last line of the related paragraph, so append to object keep 0 to the parameter */
        if (strstr(line , "Version:") != NULL) {
            processor_information = 0;
            return 2;
        }
    } else if ((strcmp(member, "dmidecode") == 0) && (strcmp(item, "bios") == 0)) {
        /* This should be the first line of the related paragraph, so set 1 to the parameter */
        if (strcmp(line, "BIOS Information") == 0)
            bios_information = 1;
        /* set 0 to the parameter for this part */
        if (strstr(line , "Characteristics:") != 0) {
            bios_information = 0;
            return 1;
        }
        if (bios_information == 1)
            return 2;
        /* This should be the last line of the related paragraph, so append to object keep 0 to the parameter */
        if (strstr(line , "BIOS Revision:") != NULL) {
            bios_information = 0;
            return 2;
        }
    } else if ((strcmp(member, "dmidecode") == 0) && (strcmp(item, "memory") == 0)) {
        /* This should be the first line of the related paragraph, so set 1 to the parameter */
        if (strcmp(line, "Physical Memory Array") == 0)
            memory_array_information = 1;
        /* set 0 to the parameter for this part */
        if (strstr(line, "Handle") != NULL) {
            memory_array_information = 0;
            return 1;
        }
        if (memory_array_information == 1)
            return 2;

        /* set 1 to the parameter for this part */
        if (strcmp(line, "Memory Device") == 0) {
            memory_information = 1;
            return 2;
        }
        /* append only this line */
        if ((memory_information == 1) && (strstr(line , "Size:") != NULL)) {
            memory_information = 0;
            append_list(&sos_line_obj, line);
        }
    } else if ((strcmp(member, "dmidecode") == 0) && (strcmp(item, "System") == 0)) {
        /* This should be the first line of the related paragraph, so set 1 to the parameter */
        if (strcmp(line, "System Information") == 0)
            system_information = 1;
        /* set 0 to the parameter for this part */
        if (strstr(line , "UUID:") != 0) {
            system_information = 0;
            return 1;
        }
        if (system_information == 1)
            return 2;
        /* This should be the last line of the related paragraph, so append to object keep 0 to the parameter */
        if (strstr(line , "Family:") != NULL) {
            system_information = 0;
            return 2;
        }
    } else if ((strcmp(member, "var/log/messages") == 0) && (strcmp(item, "lockup") == 0)) {
        /* This should be the first line of the related paragraph, so set 1 to the parameter */
        if (strstr(line, "soft lockup") != NULL)
            soft_lockup = 1;
        /* This should be the last line of the related paragraph, so append to object and set 0 to the parameter */
        if (strstr(line, "Code:") != NULL) {
            soft_lockup = 0;
            return 0;
        }
        /* During the related paragraph, append to object */
        if (soft_lockup == 1)
            return 2;
    } else {
    /* ### FIXME
     * These should echo matched lines which had been set by config file, note item number is 
     * limited by the member object. members which could have only one item is excluded here.
     * Another way of saying is, these may have item 'all' or others.
     */
        if (strstr(line , item) != NULL)
            return 0;
        else
            return 1;
    }
    return 1; 
}

FILE* file_open_check(FILE* fp, const char* file_name, const char* mode, int sar_only)
{
    fp = NULL;
    if ((fp = fopen(file_name, mode)) == NULL) {
        fprintf(stderr, "can't open file (%s): %s\n", file_name, strerror(errno));
        exit(EXIT_FAILURE);
    }
    return fp;
}

typedef struct _check_str
{
   int result ;
   check_str_exists func; /* function pointer */

} STR;

typedef struct _comment_analyzed
{
   comment_analyzed func; /* function pointer */

} COMMENT;

static int __read_file(const char* file_name, const volatile char* member, int files, int mcinfo,
                       int sar_only)
{
    size_t file_name_len = strlen(file_name);
    char* hairline2 = "<<<<";
    char* blank_line = "";

    char log_string_1[MAX_LINE_LENGTH];
    char log_string_2[MAX_LINE_LENGTH];
    char log_string_3[MAX_LINE_LENGTH];
    char log_string_4[MAX_LINE_LENGTH];
    char log_string_5[MAX_LINE_LENGTH];
    memset(log_string_1, '\0', sizeof(log_string_1));
    memset(log_string_2, '\0', sizeof(log_string_2));
    memset(log_string_3, '\0', sizeof(log_string_3));
    memset(log_string_4, '\0', sizeof(log_string_4));
    memset(log_string_5, '\0', sizeof(log_string_5));

    if (file_name_len == 0) {
        fprintf(stderr, "no file name supplied (%s): %ld %s\n", file_name, file_name_len, strerror(errno));
        free_sosreport_analyzer_obj(sar_only);
        exit (EXIT_FAILURE);
    }
    if (file_name_len > MAX_FULL_PATH_LENGTH) {
        fprintf(stderr, "file name too long (%s): %ld %s\n", file_name, file_name_len, strerror(errno));
        free_sosreport_analyzer_obj(sar_only);
        exit(EXIT_FAILURE);
    }
    FILE* fp;
    int lnr = 0;
    size_t i = 0;
    char linebuf[MAX_LINE_LENGTH];
    char* line;
    int file_this = 0;
    /* int file_content_empty = 1; */
    int file_gro_on = 1;
    int file_bond_on = 1;
    int file_ethtool_unrecoverable_on = 1;
    int file_nic_has_no_carrier_on = 1;
    int file_etc_hosts_has_no_hostname_on = 1;
    int file_pattern_net = 0;
    int file_pattern_bond = 0;
    int file_pattern_ethtool_unrecoverable = 0;
    int file_dns_empty = 0;
    int file_pattern_nic_has_no_carrier = 0;
    int file_pattern_etc_hosts_has_no_hostname = 0;

    /* open file */
    if ((fp=fopen(file_name, "r")) == NULL)
        return 1;
    struct stat filebuf;
    time_t file_time = 0;
    struct tm *file_time_local;
    char file_time_str[MAX_LINE_LENGTH];
    char f_t[100];
    stat(file_name, &filebuf);
    file_time = filebuf.st_mtime;
    file_time_local = localtime(&file_time);
    strftime(f_t, sizeof(f_t), "%Y/%m/%d %H:%M", file_time_local);
    snprintf(file_time_str, MAX_LINE_LENGTH - 1, "mtime(%s)", f_t);

    volatile node_m* ptr_tmp_m = member_obj;
    while (ptr_tmp_m != NULL) {
        if ((strcmp((const char*)ptr_tmp_m->_member, (const char*)member) == 0) && (ptr_tmp_m->mcinfo == mcinfo)) {
            append_list(&sos_line_obj, blank_line);
            append_list(&sos_line_obj, hairline2);
            append_list(&sos_line_obj, (char*)file_name);
            append_list(&sos_line_obj, file_time_str);
            append_list(&sos_line_obj, blank_line);
        }
        ptr_tmp_m = ptr_tmp_m->next;
    }
    /* prepare to analyze, (getting items) */    
    char* item_arr_tmp[25] = {""};
    ptr_tmp_m = member_obj;
    /* check if this is a file */
    file_this = __is_file(file_name);
    while (ptr_tmp_m != NULL) {
        if ((strcmp((const char*)ptr_tmp_m->_member, (const char*)member) == 0) &&
            (ptr_tmp_m->mcinfo == mcinfo)) {
            for (int x = 0; x < ptr_tmp_m->item_num ; x++)
                item_arr_tmp[x] = (char*)ptr_tmp_m->item_names.item_name[x];
            break;
        }
        ptr_tmp_m = ptr_tmp_m->next;
    }
    char file_name_this[MAX_FILE_NAME_LENGTH];
    memset(file_name_this, '\0', sizeof(file_name_this));
    file_pattern_net = is_some_file("netsetting", file_name, file_name_this);
    file_pattern_bond = is_some_file("bond_chk", file_name, file_name_this);
    file_pattern_ethtool_unrecoverable = is_some_file("ethtool_unrecoverable", file_name, file_name_this);
    file_pattern_ethtool_unrecoverable = is_some_file("ethtool_unrecoverable", file_name, file_name_this);
    file_pattern_nic_has_no_carrier = is_some_file("nic_has_no_carrier", file_name, file_name_this);
    file_pattern_etc_hosts_has_no_hostname = is_some_file("etc_hosts_has_no_hostname", file_name, file_name_this);

    /* declaring content obj */
    STR content_obj_raw;
    STR *content_obj = &content_obj_raw;
    /* declaring comment obj */
    COMMENT comment_obj_raw;
    COMMENT *comment_obj = &comment_obj_raw;

    /* read file and parse lines */
    while (fgets(linebuf, sizeof(linebuf), fp) != NULL) {
        /* sos analyze stuff */
        if (file_this) {
            if ((file_pattern_net == 2) && (file_gro_on)) {
                content_obj->func = gro;
                file_gro_on = content_obj->result = content_obj->func(line);
            }
            /*
             * if (file_content_empty) {
             *   content_obj->func = content;
             *   file_content_empty = content_obj->result = content_obj->func(line);
             * }
             */
            if (file_pattern_net == 1) {
                content_obj->func = dns;
                file_dns_empty = content_obj->result = content_obj->func(line);
            }
            if ((file_pattern_bond == 1) && (file_bond_on)) {
                content_obj->func = mii_stat;
                file_bond_on = content_obj->result = content_obj->func(line);
            }
            if ((file_pattern_ethtool_unrecoverable == 1) && (file_ethtool_unrecoverable_on)) {
                content_obj->func = ethtool_unrecoverable_error;
                file_ethtool_unrecoverable_on = content_obj->result = content_obj->func(line);
            }
            if ((file_pattern_nic_has_no_carrier == 1) && (file_nic_has_no_carrier_on)) {
                content_obj->func = nic_has_no_carrier;
                file_nic_has_no_carrier_on = content_obj->result = content_obj->func(line);
            }
            if ((file_pattern_etc_hosts_has_no_hostname == 1) && (file_etc_hosts_has_no_hostname_on)) {
                content_obj->func = etc_hosts_has_no_hostname;
                file_etc_hosts_has_no_hostname_on = content_obj->result = content_obj->func(line);
            }
        }
        /* end sos analyze stuff */
        lnr++;
        line = linebuf;
        if (strstr(file_name, "hostname") != NULL)
            append_list(&hostname_sos_obj, line);
        int x = 1;

        /* strip newline */
        i = strlen(line);
        if ((i > MAX_LINE_LENGTH) || (i <= 0) || (line[i - 1] != '\n')) {
            snprintf(log_string_5, MAX_LINE_LENGTH - 1,
                "%s:%d: line too long or last line missing newline. Skipping this line.",
                    file_name, lnr);
            __log_info(&log_obj, log_string_5);
            continue;
        }
        line[i - 1] = '\0';
 
        /* ignore comment lines */
        /*if (line[ 0 ] == '#')
            continue;*/
        if (
            (strstr(line,"a") == NULL)
            && (strstr(line,"b") == NULL)
            && (strstr(line,"c") == NULL)
            && (strstr(line,"d") == NULL)
            && (strstr(line,"e") == NULL)
            && (strstr(line,"f") == NULL)
            && (strstr(line,"g") == NULL)
            && (strstr(line,"h") == NULL)
            && (strstr(line,"i") == NULL)
            && (strstr(line,"j") == NULL)
            && (strstr(line,"k") == NULL)
            && (strstr(line,"l") == NULL)
            && (strstr(line,"m") == NULL)
            && (strstr(line,"n") == NULL)
            && (strstr(line,"o") == NULL)
            && (strstr(line,"p") == NULL)
            && (strstr(line,"q") == NULL)
            && (strstr(line,"r") == NULL)
            && (strstr(line,"s") == NULL)
            && (strstr(line,"t") == NULL)
            && (strstr(line,"u") == NULL)
            && (strstr(line,"v") == NULL)
            && (strstr(line,"w") == NULL)
            && (strstr(line,"x") == NULL)
            && (strstr(line,"y") == NULL)
            && (strstr(line,"z") == NULL)
            && (strstr(line,"A") == NULL)
            && (strstr(line,"B") == NULL)
            && (strstr(line,"C") == NULL)
            && (strstr(line,"D") == NULL)
            && (strstr(line,"E") == NULL)
            && (strstr(line,"F") == NULL)
            && (strstr(line,"G") == NULL)
            && (strstr(line,"H") == NULL)
            && (strstr(line,"I") == NULL)
            && (strstr(line,"J") == NULL)
            && (strstr(line,"K") == NULL)
            && (strstr(line,"L") == NULL)
            && (strstr(line,"M") == NULL)
            && (strstr(line,"N") == NULL)
            && (strstr(line,"O") == NULL)
            && (strstr(line,"P") == NULL)
            && (strstr(line,"Q") == NULL)
            && (strstr(line,"R") == NULL)
            && (strstr(line,"S") == NULL)
            && (strstr(line,"T") == NULL)
            && (strstr(line,"U") == NULL)
            && (strstr(line,"V") == NULL)
            && (strstr(line,"W") == NULL)
            && (strstr(line,"X") == NULL)
            && (strstr(line,"Y") == NULL)
            && (strstr(line,"Z") == NULL)
            && (strstr(line,"0") == NULL)
            && (strstr(line,"1") == NULL)
            && (strstr(line,"2") == NULL)
            && (strstr(line,"3") == NULL)
            && (strstr(line,"4") == NULL)
            && (strstr(line,"5") == NULL)
            && (strstr(line,"6") == NULL)
            && (strstr(line,"7") == NULL)
            && (strstr(line,"8") == NULL)
            && (strstr(line,"9") == NULL)
        )
            continue;
        /* Skipping line including certain word for certain member */
        if (
            ((strcmp((char*)member, "sos_commands/logs/journalctl_--no-pager") == 0) ||
            (strcmp((char*)member, "var/log/messages") == 0)) &&
            ((strstr(line, "sysstat-collect") != NULL) ||
            (strstr(line, "sysstat-summary") != NULL))
        )
            continue;

        /* strip trailing spaces */
        for (i--; (i > 0) && isspace(line[i -1]) ; i--)
            line[i -1] = '\0';
        /* read each item from items related and if match, write to list */
        for (x = 0; x < ptr_tmp_m->item_num ; x++) {
            if (__append_item_to_sos_line_obj(line, (const char*)member, item_arr_tmp[x]) != 1) {
                append_list(&sos_line_obj, line);
                break;
            }
        }
    }
    /* after reading all lines, close the file pointer */
    fclose(fp);

    /* analyze obj stuff */
    if (file_this) {
        if ((file_dns_empty) || (file_gro_on == 0) || (file_bond_on == 0) ||
           (file_ethtool_unrecoverable_on == 0) || (file_nic_has_no_carrier_on == 0) ||
           (file_etc_hosts_has_no_hostname_on == 0)) {
            comment_obj->func = comment_analyzed_content;
            comment_obj->func(file_name, file_name_this);
        }
    }
    /* end analyze obj stuff */

    return 0;
}

static int __read_file_from_analyze_dir(node** obj, const volatile char* member, int mcinfo,
                                        int sar_only, FILE* fp_w, const char* sos_file_all_write,
                                        int i)
{
    char log_string[MAX_LINE_LENGTH - 1];  
    memset(log_string, '\0', sizeof(log_string)); 

    volatile node_m* ptr_tmp_m = member_obj;
    while (ptr_tmp_m != NULL) {
        if ((strcmp((const char*)ptr_tmp_m->_member, (const char*)member) == 0) &&
            (ptr_tmp_m->mcinfo == mcinfo))
            if (strcmp((const char*)ptr_tmp_m->item_names.item_name[0], "") == 0)
                return 0;
        ptr_tmp_m = ptr_tmp_m->next;
    }
    int files = 0;
    node* ptr_tmp = NULL;
    ptr_tmp = *obj;
    pid_t cpid;
    char sos_file_all_write_tmp_special[MAX_FILE_NAME_LENGTH];
    while (ptr_tmp != NULL) {
        if (strcmp(ptr_tmp->_line, "") == 0) {
            files ++;
            ptr_tmp = ptr_tmp->next;
            continue;
        }

        /* Again we can fork() and read each file for certain members */
        if ((strcmp((const char*)member, "var/log/sa/sar") == 0) ||
            (strcmp((const char*)member, "var/log/anaconda/") == 0)) {
            clear_list(&sos_line_obj);
            init_list(&sos_line_obj);
            char result_tmp_pre[MAX_LINE_LENGTH - 100]; 
            memset(result_tmp_pre, '\0', MAX_LINE_LENGTH - 100); 
            char result_tmp[MAX_LINE_LENGTH - 100]; 
            memset(result_tmp, '\0', MAX_LINE_LENGTH - 100); 
            char* hairline1 = "########";
            char* hairline2 = "<<<<";
            search_list(&sos_header_obj, member, result_tmp_pre);
            snprintf(result_tmp, MAX_LINE_LENGTH - 1, "(config setting is %s)", result_tmp_pre);
            if (files==0) {
                append_list(&sos_line_obj, "");
                append_list(&sos_line_obj, hairline1);
                append_list(&sos_line_obj, hairline2);
                append_list(&sos_line_obj, result_tmp);
                append_list(&sos_line_obj, "");
            }
            snprintf(sos_file_all_write_tmp_special, MAX_LINE_LENGTH - 1, "%s_%d",
                sos_file_all_write, i);
            cpid = fork();
            if (cpid == -1) {
                perror("fork");
                free_sosreport_analyzer_obj(sar_only);
                exit(EXIT_FAILURE);
            }
            if (cpid == 0) {
                snprintf(log_string, MAX_LINE_LENGTH + 18, "Read '%s'", ptr_tmp->_line);
                __log_info(&log_obj, log_string);
                __read_file(ptr_tmp->_line, member, files, mcinfo, sar_only);
                file_write_list(&sos_line_obj, fp_w);
                /* close the file pointer */
                fclose(fp_w);
                _exit(EXIT_SUCCESS);
            }
        } else {
            snprintf(log_string, MAX_LINE_LENGTH + 10, "Read '%s'", ptr_tmp->_line);
            __log_info(&log_obj, log_string);
            __read_file(ptr_tmp->_line, member, files, mcinfo, sar_only);
        }
        files ++;
        ptr_tmp = ptr_tmp->next;
    }
    return 0;
}

/* this one should be here to be compared with MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR */
int obj_size = 0;

static int __read_file_pre_2(const volatile char* member, int next, int mcinfo, int sar_only,
                             int l, const char* sos_file_all_write, const char *log_file_write,
                             int i)
{
    if (next == 0)
        return 0;

    char sos_file_all_write_tmp[MAX_FILE_NAME_LENGTH];
    snprintf(sos_file_all_write_tmp, MAX_LINE_LENGTH - 1, "%s_%d", sos_file_all_write, i);
    FILE *fp_w = NULL;
    fp_w = file_open_check(fp_w, sos_file_all_write_tmp, "a", sar_only);
    /* if its a file */
    if (l == 1) {
        char str_tmp[MAX_LINE_LENGTH - 100]; 
        memset(str_tmp, '\0', sizeof(str_tmp)); 
        char str_tmp2[MAX_LINE_LENGTH];
        memset(str_tmp2, '\0', sizeof(str_tmp2));
        char str_tmp3[MAX_LINE_LENGTH - 100]; 
        memset(str_tmp3, '\0', sizeof(str_tmp3)); 

        snprintf(str_tmp, MAX_LINE_LENGTH - 1, "%s/%s", get_dirname(str_tmp3), member);
        snprintf(str_tmp2, MAX_LINE_LENGTH - 1, "file:%s", str_tmp);

        if (__read_file(str_tmp, member, 0, mcinfo, sar_only) == 1)
            fprintf(stderr, "can't open file (%s): %s\n", str_tmp, strerror(errno));
    }
    /* if its a directory */
    if (l == 0) {
        for (int x = 0; x < MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR; x++)
            str_arr_tmp[x] = NULL;
        /* now, we actually read files here for directory stuff */
        char* str_tmp;
        int ii = 0;
        /* read from object and copy strings to an array */
        while (tmp_obj != NULL) {
            if (obj_size > MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR)
                break;
            str_arr_tmp[obj_size] = (char*) & (tmp_obj->_line[0]); 
            obj_size++;
            tmp_obj = tmp_obj->next;
        }
        clear_list(&tmp_obj);
        /* bubble sort the array */
        for (int j = 0; j < obj_size; j++) {
            /* This makes largest item to the end of an array. */
            for (int i = 0; i < obj_size - (1+j); i++) {
                ii = i+1;
                if (strcmp (str_arr_tmp[i], str_arr_tmp[ii]) > 0) {
                    str_tmp = str_arr_tmp[i]; 
                    str_arr_tmp[i] = str_arr_tmp[ii]; 
                    str_arr_tmp[ii] = str_tmp; 
                }
            }
        }
        int k = 0;
        /* write back to an object */
        while (str_arr_tmp[k]  != NULL) {
            append_list(&tmp_obj, (char*)str_arr_tmp[k]); 
            k++;
        }
        /* now, read files */
        __read_file_from_analyze_dir(&tmp_obj, member, mcinfo, sar_only, fp_w, sos_file_all_write,i);
        if (tmp_obj != NULL)
            clear_list(&tmp_obj);
    }

    /* open result directory */
    char str_dir_result[MAX_FILE_NAME_LENGTH]; 
    memset(str_dir_result, '\0', sizeof(str_dir_result)); 
    strncpy(str_dir_result, "./saj-results", MAX_FILE_NAME_LENGTH);
    if (check_result_dir(str_dir_result, sar_only, 0) != 0)
        fprintf(stderr, "can't open dir %s (%s)\n", str_dir_result, strerror(errno));

    FILE* fp_log_w = NULL;
    /* open log file */
    fp_log_w = file_open_check(fp_log_w, log_file_write, "a", sar_only);
    /* sos analyze stuff */
    FILE* fp_analyze = NULL;
    fp_analyze =file_open_check(fp_analyze, get_sos_analyze_file_name_to_be_written(), "a", sar_only);
    file_write_list(&sos_analyze_obj, fp_analyze);
    /* end sos analyze stuff */

    file_write_list(&sos_line_obj, fp_w);
    file_write_list(&log_obj, fp_log_w);
    
    /* close the file pointer */
    fclose(fp_analyze);
    fclose(fp_w);
    fclose(fp_log_w);

    if (dir_read_obj != NULL)
        clear_list(&dir_read_obj);

    return 0;
}

int read_file_pre(const volatile char* member, const char* dir_name, int mcinfo,
                  int sar_only, const char* sos_file_all_write,
                  const char *log_file_write, int i)
{
    char log_string[MAX_LINE_LENGTH -1];  
    char log_string_1[MAX_LINE_LENGTH - 1];  
    char log_string_2[MAX_LINE_LENGTH - 1];  
    char log_string_3[MAX_LINE_LENGTH - 1];  
    char log_string_4[MAX_LINE_LENGTH - 1];  
    memset(log_string, '\0', sizeof(log_string)); 
    memset(log_string_1, '\0', sizeof(log_string_1)); 
    memset(log_string_2, '\0', sizeof(log_string_2)); 
    memset(log_string_3, '\0', sizeof(log_string_3)); 
    memset(log_string_4, '\0', sizeof(log_string_4)); 

    char str_tmp[MAX_LINE_LENGTH - 100]; 
    memset(str_tmp, '\0', sizeof(str_tmp)); 
    char str_tmp2[MAX_LINE_LENGTH];
    memset(str_tmp2, '\0', sizeof(str_tmp2));
    char result_tmp_pre[MAX_LINE_LENGTH - 100]; 
    memset(result_tmp_pre, '\0', sizeof(result_tmp_pre)); 

    char result_tmp[MAX_LINE_LENGTH - 100]; 
    memset(result_tmp, '\0', sizeof(result_tmp)); 
    char str_tmp3[MAX_LINE_LENGTH - 100]; 
    memset(str_tmp3, '\0', sizeof(str_tmp3)); 

    char *hairline1 = "########";
    char *hairline2 = "<<<<";

    search_list(&sos_header_obj, member, result_tmp_pre);
    snprintf(result_tmp, MAX_LINE_LENGTH - 1, "(config setting is %s)", result_tmp_pre);
    snprintf(str_tmp, MAX_LINE_LENGTH - 1, "%s/%s", get_dirname(str_tmp3), member);
    snprintf(str_tmp2, MAX_LINE_LENGTH - 1, "file:%s", str_tmp);

    volatile node_m *ptr_tmp_m = member_obj;
    while (ptr_tmp_m != NULL) {
        if (strcmp ((const char*)ptr_tmp_m->_member, (const char*)member) == 0 &&
            ptr_tmp_m->mcinfo == mcinfo) {
            if ((strcmp((const char*)member, "var/log/sa/sar") != 0) &&
                (strcmp((const char*)member, "var/log/anaconda/") != 0)) {
                append_list(&sos_line_obj, "");
                append_list(&sos_line_obj, hairline1);
                append_list(&sos_line_obj, hairline2);
                append_list(&sos_line_obj, result_tmp);
                append_list(&sos_line_obj, "");
            }
        }
        ptr_tmp_m = ptr_tmp_m->next;
    }
    /* for ones of which should read directory, or matched files in the directory */
    ptr_tmp_m = NULL;
    ptr_tmp_m = member_obj;
    while (ptr_tmp_m != NULL) {
        if ((strcmp((const char*)ptr_tmp_m->_member, (const char*)member) == 0) &&
            (ptr_tmp_m->mcinfo == mcinfo)) {
            /* here, we skip if item_name is empty ( originally, 'skip' ) */
            if (strcmp((const char*)ptr_tmp_m->item_names.item_name[0], "") == 0) {
                if (tmp_obj != NULL)
                    clear_list(&tmp_obj);
                return 0;
            }
            snprintf(log_string, MAX_LINE_LENGTH - 1, "analyze member '%s'",member);
            __log_info(&sos_line_obj, log_string);
            if (__read_analyze_dir(member, get_dirname(str_tmp3), 0, mcinfo, sar_only) == 1) {
                ptr_tmp_m = ptr_tmp_m->next;

                snprintf(log_string_1, MAX_LINE_LENGTH - 1, "can't open directory (%s/%s): %s",
                    str_tmp3, member, strerror(errno));
                __log_info(&log_obj, log_string_1 );
                if (strcmp((const char*)member, "var/crash/") == 0) {
                    snprintf(log_string_2, MAX_LINE_LENGTH - 1, "I skip 'var/crash/' automatically.");
                    snprintf(log_string_3, MAX_LINE_LENGTH - 1, "Do not set 'skip' to member 'var/crash/'.");
                    __log_info(&log_obj, log_string_2);
                    __log_info(&log_obj, log_string_3);
                } else {
                    snprintf(log_string_4, MAX_LINE_LENGTH - 1, "Skip '%s' and go on.",member);
                    __log_info(&log_obj, log_string_4);
                }
                return 0;
            }
            int l = 0;
            if (ptr_tmp_m->read_dir == false)
                l = 1;
            __read_file_pre_2(member, 1, mcinfo, sar_only, l, sos_file_all_write, log_file_write, i);
            return 0;
        }
        ptr_tmp_m = ptr_tmp_m->next;
    }
    return 0;
}

int check_time_span_str(const char* time_span_str)
{
    char str_tmp[12];
    memset(str_tmp, '\0', sizeof(str_tmp)); 
    strncpy(str_tmp, time_span_str, 11);
    int i = 0;
    for (i = 0; i < 11; i++) {
        if ((i == 0) || (i == 6))
            if ((str_tmp[i] != '0' ) && (str_tmp[i] != '1') && (str_tmp[i] != '2'))
                return 0;
        if ((i == 2) || (i == 8))
            if (str_tmp[i] != ':')
                return 0;
        if (i == 5)
            if (str_tmp[i] != '-')
                return 0;
        if ((i == 1) || (i == 3) || (i == 4) || (i == 7) || (i == 9) || (i == 10))
            if (
                (str_tmp[i] != '0') && (str_tmp[i] != '1') && (str_tmp[i] != '2') && 
                (str_tmp[i] != '3') && (str_tmp[i] != '4') && (str_tmp[i] != '5') && 
                (str_tmp[i] != '6') && (str_tmp[i] != '7') && (str_tmp[i] != '8') && 
                (str_tmp[i] != '9')
               )
                   return 0;
    }

    if (str_tmp[0] == '2') {
        if ((str_tmp[1] != '0') && (str_tmp[1] != '1') && (str_tmp[1] != '2') && (str_tmp[1] != '3'))
            return 0;
        if ((str_tmp[1] == '2') && ((str_tmp[6] == '1') || (str_tmp[6] == '0')))
            return 0;
        if ((str_tmp[1] == '1') && (str_tmp[6] == '0'))
            return 0;
    }

    if (str_tmp[0] == str_tmp[6]) {
        if (str_tmp[1] == '9')
            if (str_tmp[7] != '9')
                return 0;
        if (str_tmp[1] == '8')
            if ((str_tmp[7] != '9') && (str_tmp[7] != '8'))
                return 0;
        if (str_tmp[1] == '7')
            if ((str_tmp[7] != '9') && (str_tmp[7] != '8') && (str_tmp[7] != '7'))
                return 0;
        if (str_tmp[1] == '6')
            if ((str_tmp[7] != '9') && (str_tmp[7] != '8') && (str_tmp[7] != '7') && (str_tmp[7] != '6') )
                return 0;
        if (str_tmp[1] == '5')
            if ((str_tmp[7] == '4') || (str_tmp[7] == '3') || (str_tmp[7] == '2') || (str_tmp[7] == '1') || (str_tmp[7] == '0'))
                return 0;
        if (str_tmp[1] == '4')
            if ((str_tmp[7] == '3') || (str_tmp[7] == '2') || (str_tmp[7] == '1') || (str_tmp[7] == '0'))
                return 0;
        if (str_tmp[1] == '3')
            if ((str_tmp[7] == '2') || (str_tmp[7] == '1') || (str_tmp[7] == '0'))
                return 0;
        if (str_tmp[1] == '2')
            if ((str_tmp[7] == '1') || (str_tmp[7] == '0'))
                return 0;
        if (str_tmp[1] == '1')
            if (str_tmp[7] == '0')
                return 0;

        if (str_tmp[1] == str_tmp[7]) {
            if (str_tmp[3] == '9')
                if (str_tmp[9] != '9')
                    return 0;
            if (str_tmp[3] == '8')
                if ((str_tmp[9] != '9') && (str_tmp[9] != '8'))
                    return 0;
            if (str_tmp[3] == '7')
                if ((str_tmp[9] != '9') && (str_tmp[9] != '8') && (str_tmp[9] != '7'))
                    return 0;
            if (str_tmp[3] == '6')
                if ((str_tmp[9] != '9') && (str_tmp[9] != '8') && (str_tmp[9] != '7') && (str_tmp[9] != '6'))
                    return 0;
            if (str_tmp[3] == '5')
                if ((str_tmp[9] == '4') || (str_tmp[9] == '3') || (str_tmp[9] == '2') || (str_tmp[9] == '1') || (str_tmp[9] == '0'))
                    return 0;
            if (str_tmp[3] == '4')
                if ((str_tmp[9] == '3') || (str_tmp[9] == '2') || (str_tmp[9] == '1') || (str_tmp[9] == '0'))
                    return 0;
            if (str_tmp[3] == '3')
                if ((str_tmp[9] == '2') || (str_tmp[9] == '1') || (str_tmp[9] == '0'))
                    return 0;
            if (str_tmp[3] == '2')
                if ((str_tmp[9] == '1') || (str_tmp[9] == '0'))
                    return 0;
            if (str_tmp[3] == '1')
                if (str_tmp[9] == '0')
                    return 0;
        }
    }

    if (str_tmp[6] == '2')
        if ((str_tmp[7] != '0') && ( str_tmp[7] != '1') && (str_tmp[7] != '2') && (str_tmp[7] != '3'))
            return 0;
    if (((str_tmp[0] == '1') || ( str_tmp[0] == '2')) && (str_tmp[6] == '0'))
        return 0;
    if (((str_tmp[0] == '2') ) && ( ( str_tmp[6] == '0') || (str_tmp[6] == '1')))
        return 0;

    if (
        (str_tmp[0] == str_tmp[6]) &&
        (str_tmp[1] == str_tmp[7]) && 
        (str_tmp[3] == str_tmp[9])
       )
    {
        if (str_tmp[4] == '9')
            if (str_tmp[10] != '9')
                return 0;
        if (str_tmp[4] == '8')
            if ((str_tmp[10] != '9') && (str_tmp[10] != '8'))
                return 0;
        if (str_tmp[4] == '7')
            if ((str_tmp[10] != '9') && (str_tmp[10] != '8') && (str_tmp[10] != '7'))
                return 0;
        if (str_tmp[4] == '6')
            if ((str_tmp[10] != '9') && (str_tmp[10] != '8') && (str_tmp[10] != '7') && (str_tmp[10] != '6'))
                return 0;
        if (str_tmp[4] == '5')
            if ((str_tmp[10] == '4') || (str_tmp[10] == '3') || (str_tmp[10] == '2') || (str_tmp[10] == '1') || (str_tmp[10] == '0'))
                return 0;
        if (str_tmp[4] == '4')
            if ((str_tmp[10] == '3') || (str_tmp[10] == '2') || (str_tmp[10] == '1') || (str_tmp[10] == '0'))
                return 0;
        if (str_tmp[4] == '3')
            if ((str_tmp[10] == '2') || (str_tmp[10] == '1') || (str_tmp[10] == '0'))
                return 0;
        if (str_tmp[4] == '2')
            if ((str_tmp[10] == '1') || (str_tmp[10] == '0'))
                return 0;
        if (str_tmp[4] == '1')
            if (str_tmp[10] == '0')
                return 0;
    }

    return 1;
}

const char* get_dirname(char str_tmp[MAX_LINE_LENGTH])
{
    strncpy(str_tmp, sos_dir_file_obj->dir_file_names.dirname, MAX_LINE_LENGTH);
    return str_tmp;
}

const char* get_sos_file_name_to_be_written(void)
{
    return sos_dir_file_obj->dir_file_names.sos_file_name_to_be_written;
}

const char* get_sos_analyze_file_time(void)
{
    return sos_dir_file_obj->dir_file_names.sos_analyze_file_time;
}

const char* get_sos_analyze_file_name_to_be_written(void)
{
    return sos_dir_file_obj->dir_file_names.sos_analyze_file_name_to_be_written;
}

const char* get_sar_file_name_to_be_written(void)
{
    return sos_dir_file_obj->dir_file_names.sar_file_name_to_be_written;
}

const char* get_ps_file_name_to_be_written(void)
{
    return sos_dir_file_obj->dir_file_names.ps_file_name_to_be_written;
}

const char* get_log_file_name_to_be_written(void)
{
    return sos_dir_file_obj->dir_file_names.log_file_name_to_be_written;
}

int is_dir_present(const char* dname, int sar_only)
{
    size_t strlen_dname = strlen(dname);

    if (strlen_dname == 0) {
        fprintf(stderr, "Directory (%s) name is too short.: %s\n", dname, strerror(errno));
        return 0;
    }
    if (strlen_dname > NAME_MAX) {
        fprintf(stderr, "Directory (%s) name is too long.: %s\n", dname, strerror(errno));
        return 0;
    }
    if (dname != NULL) {
        DIR *dir = NULL;
        /* if open directory fails, return 1 */
        char str_tmp[NAME_MAX];
        strncpy(str_tmp, dname, NAME_MAX - 1);
        if ((dir = opendir(str_tmp)) == NULL) {
            fprintf(stderr, "can't open directory (%s): %s\n", dname, strerror(errno));
            free_sosreport_analyzer_obj(sar_only);
            return 1;
        } else
            closedir(dir);
    }
    return 0;
}

int is_sos_dir_present(const char* dname, int sar_only, int mcinfo)
{
    char sos_dir[NAME_MAX];
    memset(sos_dir, '\0', sizeof(sos_dir));
    if (mcinfo == 1)
        snprintf(sos_dir, MAX_LINE_LENGTH - 1, "%s/cmdlog", dname);
    else if (mcinfo == 0)
        snprintf(sos_dir, MAX_LINE_LENGTH - 1, "%s/sos_commands", dname);
    if (sos_dir != NULL) {
        DIR* dir = NULL;
        /* if open directory fails, return 1 */
        if ((dir = opendir(sos_dir)) == NULL) {
            fprintf(stderr, "Dir check - \ncan't open directory (%s):\n%s\n", sos_dir, strerror(errno));
            free_sosreport_analyzer_obj(sar_only);
            return 1;
        } else
            closedir(dir);
    }
    return 0;
}

int check_result_dir(const char* dname, int sar_only, int tmp)
{
    size_t strlen_dname = strlen(dname);

    char log_string_1[MAX_LINE_LENGTH];  
    char log_string_2[MAX_LINE_LENGTH];  
    char log_string_3[MAX_LINE_LENGTH];  
    char log_string_4[MAX_LINE_LENGTH];  
    char log_string_5[MAX_LINE_LENGTH];  
    char log_string_6[MAX_LINE_LENGTH];  
    char log_string_7[MAX_LINE_LENGTH];  
    memset(log_string_1, '\0', sizeof(log_string_1)); 
    memset(log_string_2, '\0', sizeof(log_string_2)); 
    memset(log_string_3, '\0', sizeof(log_string_3)); 
    memset(log_string_4, '\0', sizeof(log_string_4)); 
    memset(log_string_5, '\0', sizeof(log_string_5)); 
    memset(log_string_6, '\0', sizeof(log_string_6)); 
    memset(log_string_7, '\0', sizeof(log_string_7)); 

    if (strlen_dname == 0) {
        fprintf(stderr, "Directory (%s) name is too short.: %s\n", dname, strerror(errno));
        return 0;
    }
    if (strlen_dname > NAME_MAX) {
        fprintf(stderr, "Directory (%s) name is too long.: %s\n", dname, strerror(errno));
        return 0;
    }
    if (dname != NULL) {
        const char *dname_tmp = dname;
        DIR* dir = NULL;
        DIR* dir_tmp = NULL;
        /* if open directory fails, create it, if it fails, exit with error message */
        char str_tmp[NAME_MAX];
        strncpy(str_tmp, dname, NAME_MAX - 1);
        if ((dir = opendir(str_tmp)) == NULL) {
            snprintf(log_string_1, MAX_LINE_LENGTH, "can't open directory (%s): %s",
                dname, strerror(errno));
            snprintf(log_string_2, MAX_LINE_LENGTH - 1, "creating directory %s", dname);
            snprintf(log_string_3, MAX_LINE_LENGTH - 1, "created directory %s", dname);
            snprintf(log_string_4, MAX_LINE_LENGTH - 1, "can't open directory %s", dname);
            snprintf(log_string_5, MAX_LINE_LENGTH - 1, "directory %s exists", dname);
            __log_info(&log_obj, log_string_1);
            __log_info(&log_obj, log_string_2);
            if (mkdir(dname, 0755) == 0) 
                __log_info(&log_obj, log_string_3);
            else {
                __log_info(&log_obj, log_string_4);
                free_sosreport_analyzer_obj(sar_only);
                exit(EXIT_FAILURE);
            }
        }
        else
            __log_info(&log_obj, log_string_5);
        closedir(dir);

        if (tmp == 1) {
            strcat ((char *)dname_tmp, "/tmp");
            if ((dir_tmp = opendir(dname_tmp)) == NULL) {
                if (mkdir(dname_tmp, 0755) == 0) {
                    snprintf(log_string_6, MAX_LINE_LENGTH - 1, "created directory %s",
                        dname_tmp);
                    __log_info(&log_obj, log_string_6);
                } else {
                    snprintf(log_string_7, MAX_LINE_LENGTH - 1, "created directory failed %s",
                        dname_tmp);
                    __log_info(&log_obj, log_string_7);
                    free_sosreport_analyzer_obj(sar_only);
                    exit(EXIT_FAILURE);
                }
            }
            closedir(dir_tmp);
        }
    }
    return 0;
}

void sos_file_to_write(int sar_only)
{
    char* result_dir = "saj-results";
    char* result_dir_with_slash = "saj-results/";

    char buff_dir[MAX_FILE_NAME_LENGTH]; 
    memset(buff_dir, '\0', sizeof(buff_dir)); 
    strcpy(buff_dir, result_dir );
    char buff_dir_analyzed[MAX_FILE_NAME_LENGTH]; 
    memset(buff_dir_analyzed, '\0', sizeof(buff_dir_analyzed));
    char buff_dir_analyzed_graph[MAX_FILE_NAME_LENGTH]; 
    memset(buff_dir_analyzed_graph, '\0', sizeof(buff_dir_analyzed_graph));
    char buff_sos[MAX_FILE_NAME_LENGTH];
    memset(buff_sos, '\0', sizeof(buff_sos));
    char buff_analyze[MAX_FILE_NAME_LENGTH];
    memset(buff_analyze, '\0', sizeof(buff_analyze));
    char buff_sar[MAX_FILE_NAME_LENGTH]; 
    memset(buff_sar, '\0', sizeof(buff_sar));
    char buff_ps[MAX_FILE_NAME_LENGTH]; 
    memset(buff_ps, '\0', sizeof(buff_ps));
    char buff_log[MAX_FILE_NAME_LENGTH]; 
    memset(buff_log, '\0', sizeof(buff_log)); 

    char buff2[ MAX_FILE_NAME_LENGTH];
    memset(buff2, '\0', sizeof(buff2));
    char f_t[40];
    memset (f_t, '\0', sizeof(f_t));

    char str_tmp[MAX_LINE_LENGTH]; 
    memset(str_tmp, '\0', sizeof(str_tmp)); 

    strcpy(buff2, get_dirname(str_tmp));
    /* firstly, we create results directory */
    check_result_dir(buff_dir, sar_only, 0);
    char str_ret[MAX_FILE_NAME_LENGTH]; 
    /* secondly, we create sosreport directory which has been analyed in the results directory we've just created */
    if (strstr(buff2, "/") != NULL) {
        size_t strlen_buff2 = strlen(buff2);
        if (strlen_buff2 == 0) {
            fprintf(stderr, "buff2 is too short (%s): %ld %s\n",buff2, strlen_buff2, strerror(errno));
            free_sosreport_analyzer_obj(sar_only);
            exit(EXIT_FAILURE);
        }
        char str_c[MAX_FILE_NAME_LENGTH];
        memset(str_c, '\0', sizeof(str_c));
        char str_r[MAX_FILE_NAME_LENGTH];
        memset(str_r, '\0', sizeof(str_r));
        strncpy(buff_dir_analyzed, cut_str_from_the_last_given_str(str_ret, reverse_the_string(str_r, buff2
            ), "/"), MAX_FILE_NAME_LENGTH - 1);
    } else
        strcpy(buff_dir_analyzed, buff2);
    strcat(buff_dir, "/" );
    strcat(buff_dir, buff_dir_analyzed);

    check_result_dir(buff_dir, sar_only, 0);

    strcpy(buff_dir_analyzed_graph, buff_dir);
    strcat(buff_dir_analyzed_graph, "/graphs");
    check_result_dir(buff_dir_analyzed_graph, sar_only, 0);
    /* thirdly, we set file name */
    strcat(buff_sos, result_dir_with_slash);
    strcat(buff_analyze, result_dir_with_slash);
    strcat(buff_sar, result_dir_with_slash);
    strcat(buff_log, result_dir_with_slash);

    strcat(buff_sos, buff_dir_analyzed);
    strcat(buff_analyze, buff_dir_analyzed);
    strcat(buff_sar, buff_dir_analyzed);
    strcat(buff_ps, buff_dir_analyzed_graph);
    strcat(buff_log, buff_dir_analyzed);

    strcat(buff_sos, "/");
    strcat(buff_analyze, "/");
    strcat(buff_sar, "/");
    strcat(buff_ps, "/");
    strcat(buff_log, "/");

    strcat(buff_sos, buff_dir_analyzed);
    strcat(buff_analyze, buff_dir_analyzed);
    strcat(buff_sar, buff_dir_analyzed);
    strcat(buff_ps, buff_dir_analyzed);
    strcat(buff_log, buff_dir_analyzed);

    /* each analyed file should have unique name */
    struct tm* timenow;
    time_t now = time(NULL);
    timenow = localtime(&now);
    strftime(f_t, sizeof(f_t), "_%Y%m%d%H%M%S", timenow);
    strncpy(sos_dir_file_obj->dir_file_names.sos_analyze_file_time, f_t,
        MAX_FILE_NAME_LENGTH);

    /* for sos file */
    strncat(buff_sos, f_t, MAX_FILE_NAME_LENGTH - 1);
    strncat(buff_sos, ".txt", MAX_FILE_NAME_LENGTH - 1);
    /* Here we use strcpy. No worry, buff is surely under MAX_FILE_NAME_LENGTH */;
    strncpy(sos_dir_file_obj->dir_file_names.sos_file_name_to_be_written, buff_sos,
        MAX_FILE_NAME_LENGTH);

    /* for analyze file */
    strncat(buff_analyze, "_analyze", MAX_FILE_NAME_LENGTH - 1);
    strncat(buff_analyze, f_t, MAX_FILE_NAME_LENGTH - 1);
    strncat(buff_analyze, ".txt", MAX_FILE_NAME_LENGTH - 1);
    /* Here we use strcpy. No worry, buff is surely under MAX_FILE_NAME_LENGTH */;
    strncpy(sos_dir_file_obj->dir_file_names.sos_analyze_file_name_to_be_written,
        buff_analyze, MAX_FILE_NAME_LENGTH);

    /* for sar file */
    strncat(buff_sar, "_sar", MAX_FILE_NAME_LENGTH - 1);
    strncat(buff_sar, f_t, MAX_FILE_NAME_LENGTH - 1);
    strncat(buff_sar, ".txt", MAX_FILE_NAME_LENGTH - 1);
    /* Here we use strcpy. No worry, buff is surely under MAX_FILE_NAME_LENGTH */;
    strncpy(sos_dir_file_obj->dir_file_names.sar_file_name_to_be_written, buff_sar,
        MAX_FILE_NAME_LENGTH);

    /* for ps file */
    strncat(buff_ps, "_ps", MAX_FILE_NAME_LENGTH - 1);
    strncat(buff_ps, f_t, MAX_FILE_NAME_LENGTH - 1);
    /* Here we use strcpy. No worry, buff is surely under MAX_FILE_NAME_LENGTH */;
    strncpy(sos_dir_file_obj->dir_file_names.ps_file_name_to_be_written, buff_ps,
        MAX_FILE_NAME_LENGTH);

    /* for our log file */
    strncat(buff_log, "_log", MAX_FILE_NAME_LENGTH - 1);
    strncat(buff_log, f_t, MAX_FILE_NAME_LENGTH - 1);
    strncat(buff_log, ".log", MAX_FILE_NAME_LENGTH - 1);
    /* Here we use strcpy. No worry, buff is surely under MAX_FILE_NAME_LENGTH */;
    strncpy(sos_dir_file_obj->dir_file_names.log_file_name_to_be_written, buff_log,
        MAX_FILE_NAME_LENGTH);
}

void free_sosreport_analyzer_obj(int sar_only)
{
    if (member_obj != NULL) 
        clear_member(&member_obj); 
    if (hostname_sos_obj != NULL) 
        clear_list(&hostname_sos_obj); 
    if (sos_version_obj != NULL) 
        clear_list(&sos_version_obj); 
    if (sos_header_obj != NULL) 
        clear_list(&sos_header_obj); 
    if (sos_analyze_obj != NULL) 
        clear_list(&sos_analyze_obj); 
    if (sos_subtitle_analyze_obj != NULL) 
        clear_list(&sos_subtitle_analyze_obj); 
    if (sos_subtitle_general_obj != NULL) 
        clear_list(&sos_subtitle_general_obj); 
    if (sos_subtitle_member_obj != NULL) 
        clear_list(&sos_subtitle_member_obj); 

    if (sos_line_obj != NULL) 
        clear_list(&sos_line_obj); 
    if (sos_tail_obj != NULL ) 
        clear_list(&sos_tail_obj); 

    if (tmp_obj != NULL) 
        clear_list(&tmp_obj); 

    if (dir_read_obj != NULL) 
        clear_list(&dir_read_obj); 

    if (log_obj != NULL) 
        clear_list(&log_obj); 
}
