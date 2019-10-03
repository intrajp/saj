/*
 *  member_object.c - common functions 
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

/*
 *  booleans are 'read_dir', 'dir_recursive_read', 'dir_root_read'
 */
int append_members(void)
{
    /* for mcinfo */
    append_member(&member_obj, "proc/cpuinfo", 1, false, false, false, "", 12);
    append_member(&member_obj, "boot/grub/", 1, true, false, false, "", 12);
    append_member(&member_obj, "etc/sysconfig/network-scripts/ifcfg-", 1, true, false, false, "", 12);
    append_member(&member_obj, "cmdlog/", 1, true, true, true, "", 12);
    append_member(&member_obj, "etc/host", 1, true, false, false, "", 12);
    append_member(&member_obj, "proc/meminfo", 1, false, false, false, "", 12);
    append_member(&member_obj, "proc/zoneinfo", 1, false, false, false, "", 12);
    append_member(&member_obj, "proc/buddyinfo", 1, false, false, false, "", 12);
    append_member(&member_obj, "proc/slabinfo", 1, false, false, false, "", 12);
    append_member(&member_obj, "proc/vmstat", 1, false, false, false, "", 12);
    append_member(&member_obj, "proc/interrupts", 1, false, false, false, "", 12);
    append_member(&member_obj, "var/log/dmesg", 1, false, false, false, "", 12);
    append_member(&member_obj, "etc/crontab", 1, false, false, false, "", 12);
    append_member(&member_obj, "etc/cron.deny", 1, false, false, false, "", 12);
    append_member(&member_obj, "etc/cron.d/", 1, true, true, true, "", 12);
    append_member(&member_obj, "etc/cron.hourly/", 1, true, true, true, "", 12);
    append_member(&member_obj, "etc/cron.daily/", 1, true, true, true, "", 12);
    append_member(&member_obj, "etc/cron.weekly/", 1, true, true, true, "", 12);
    append_member(&member_obj, "etc/cron.monthly/", 1, true, true, true, "", 12);
    append_member(&member_obj, "var/spool/cron/", 1, true, true, true, "", 12);
    append_member(&member_obj, "var/log/messages", 1, true, false, false, "", 25);
    append_member(&member_obj, "var/crash/", 1, true, true, true, "", 12);
    append_member(&member_obj, "etc/", 1, true, true, true, "", 12);
    append_member(&member_obj, "dev/", 1, true, true, true, "", 12);
    append_member(&member_obj, "usr/", 1, true, true, true, "", 12);
    append_member(&member_obj, "var/", 1, true, true, true, "", 12);
    append_member(&member_obj, "proc/", 1, true, true, true, "", 12);
    /* for sosreport */
    /* general */
    append_member(&member_obj, "date", 0, false, false, false, "==== general ====", 12);
    append_member(&member_obj, "etc/fedora-release", 0, false, false, false, "", 12);
    append_member(&member_obj, "lsb-release", 0, false, false, false, "", 12);
    append_member(&member_obj, "etc/os-release", 0, false, false, false, "", 12);
    append_member(&member_obj, "etc/redhat-release", 0, false, false, false, "", 12);
    append_member(&member_obj, "etc/system-release", 0, false, false, false, "", 12);
    append_member(&member_obj, "sos_commands/release/", 0, true, true, true, "", 12);
    append_member(&member_obj, "uname", 0, false, false, false, "", 12);
    append_member(&member_obj, "hostname", 0, false, false, false, "", 12);
    append_member(&member_obj, "proc/timer_list", 0, false, false, false, "", 12);
    append_member(&member_obj, "proc/timer_stats", 0, false, false, false, "", 12);
    append_member(&member_obj, "uptime", 0, false, false, false, "", 12);
    append_member(&member_obj, "last", 0, false, false, false, "", 12);
    append_member(&member_obj, "etc/environment", 0, false, false, false, "", 12);
    append_member(&member_obj, "etc/machine-id", 0, false, false, false, "", 12);
    append_member(&member_obj, "etc/nsswitch.conf", 0, false, false, false, "", 12);
    append_member(&member_obj, "installed-rpms", 0, false, false, false, "", 12);
    append_member(&member_obj, "root/anaconda-ks.cfg", 0, false, false, false, "", 12);
    append_member(&member_obj, "dmidecode", 0, false, false, false, "", 12);
    append_member(&member_obj, "etc/default/", 0, true, true, true, "", 12);
    append_member(&member_obj, "sos_commands/boot/", 0, true, true, true, "", 12);
    append_member(&member_obj, "sos_commands/date/", 0, true, true, true, "", 12);
    append_member(&member_obj, "etc/vconsole.conf", 0, false, false, false, "", 12);
    append_member(&member_obj, "etc/locale.conf", 0, false, false, false, "", 12);
    append_member(&member_obj, "sos_commands/i18n/", 0, true, true, true, "", 12);
    append_member(&member_obj, "usr/share/zoneinfo/", 0, true, true, true, "", 12);
    /* etc/sysconfig */ 
    /*
     * Here, we try to check only in the root dir and not recursive read directory, so 'true, false, true'. 
     * We read etc/sysconfig/network-scripts/ later.
     */ 
    append_member(&member_obj, "etc/sysconfig/", 0, true, false, true, "==== etc/sysconfig/ ====", 12);
    /* cpu */
    append_member(&member_obj, "proc/cpuinfo", 0, false, false, false, "==== cpu ====", 12);
    append_member(&member_obj, "proc/interrupts", 0, false, false, false, "", 12);
    append_member(&member_obj, "sos_commands/processor/", 0, true, true, true, "", 12);
    append_member(&member_obj, "sos_commands/numa/", 0, true, true, true, "", 12);
    /* module */
    append_member(&member_obj, "lsmod", 0, false, false, false, "==== module ====", 12);
    append_member(&member_obj, "etc/modprobe.d/", 0, true, true, true, "", 12);
    append_member(&member_obj, "usr/lib/modules/", 0, true, true, true, "", 12);
    /* FIX ME: - too many directories */
    //append_member ( &member_obj, "sys/module/", 0, true, true, false, "", 1);
    /* device */
    append_member(&member_obj, "lspci", 0, false, false, false, "==== device ====", 20);
    append_member(&member_obj, "sos_commands/pci/", 0, true, true, true, "", 12);
    append_member(&member_obj, "etc/udev/", 0, true, true, true, "", 12);
    append_member(&member_obj, "usr/lib/udev/", 0, true, true, true, "", 12);
    append_member(&member_obj, "sos_commands/devicemapper/", 0, true, true, true, "", 12);
    append_member(&member_obj, "sos_commands/devices/", 0, true, true, true, "", 12);
    append_member(&member_obj, "sos_commands/block/", 0, true, true, true, "", 12);
    append_member(&member_obj, "sys/block/", 0, true, true, true, "", 12);
    append_member(&member_obj, "sos_commands/ipmitool/", 0, true, true, true, "", 12);
    append_member(&member_obj, "sos_commands/scsi/lsscsi", 0, false, false, false, "", 12);
    append_member(&member_obj, "sos_commands/usb/", 0, true, true, true, "", 12);
    append_member(&member_obj, "run/blkid/", 0, true, true, true, "", 12);
    append_member(&member_obj, "etc/multipath.conf", 0, false, false, false, "", 12);
    append_member(&member_obj, "sos_commands/multipath/", 0, true, true, true, "", 12);
    append_member(&member_obj, "sys/devices/", 0, true, true, true, "", 12);
    /* file systems */
    append_member(&member_obj, "etc/fstab", 0, false, false, false, "==== file systems ====", 12);
    append_member(&member_obj, "sos_commands/filesys/", 0, true, true, true, "", 12);
    append_member(&member_obj, "etc/lvm/", 0, true, true, true, "", 12);
    append_member(&member_obj, "sos_commands/lvm2/", 0, true, true, true, "", 12);
    append_member(&member_obj, "sos_commands/btrfs/", 0, true, true, true, "", 12);
    append_member(&member_obj, "sos_commands/gfs2/", 0, true, true, true, "", 12);
    append_member( &member_obj, "sos_commands/gluster/", 0, true, true, true, "", 12);
    append_member(&member_obj, "sys/fs/", 0, true, true, true, "", 12);
    /* boot/grub */ 
    append_member(&member_obj, "grub2.cfg", 0, false, false, false, "==== boot/grub ====", 12);
    append_member(&member_obj, "boot/", 0, true, true, true, "", 12);
    append_member(&member_obj, "etc/grub.d/", 0, true, true, true, "", 12);
    append_member(&member_obj, "sos_commands/bootloader/", 0, true, true, true, "", 12);
    /* process */
    append_member(&member_obj, "ps", 0, false, false, false, "==== process ====", 12);
    append_member(&member_obj, "sos_commands/process/", 0, true, true, true, "", 12);
    /* disk usage */
    append_member(&member_obj, "df", 0, false, false, false, "==== disk usage ====", 12);
    append_member(&member_obj, "vgdisplay", 0, false, false, false, "", 12);
    append_member(&member_obj, "sos_commands/logs/journalctl_--disk-usage", 0, false, false, false, "", 12);
    append_member(&member_obj, "sos_commands/md/", 0, true, true, true, "", 12);
    /* memory usage */
    append_member(&member_obj, "free", 0, false, false, false, "==== memory usage ====", 12);
    append_member(&member_obj, "sos_commands/memory/", 0, true, true, true, "", 12);
    append_member(&member_obj, "proc/meminfo", 0, false, false, false, "", 12);
    append_member(&member_obj, "proc/zoneinfo", 0, false, false, false, "", 12);
    append_member(&member_obj, "proc/buddyinfo", 0, false, false, false, "", 12);
    append_member(&member_obj, "proc/slabinfo", 0, false, false, false, "", 12);
    append_member(&member_obj, "proc/vmstat", 0, false, false, false, "", 12);
    append_member(&member_obj, "proc/iomem", 0, false, false, false, "", 12);
    append_member(&member_obj, "proc/vmallocinfo", 0, false, false, false, "", 12);
    /* files */
    append_member(&member_obj, "lsof", 0, false, false, false, "==== files ====", 12);
    /* systemd */
    append_member(&member_obj, "etc/systemd/system/", 0, true, true, true, "==== systemd ====", 12);
    append_member(&member_obj, "etc/systemd/", 0, true, true, true, "", 12);
    append_member(&member_obj, "usr/lib/sysctl.d/", 0, true, true, true, "", 12);
    append_member(&member_obj, "usr/lib/systemd/", 0, true, true, true, "", 12);
    append_member(&member_obj, "run/systemd/", 0, true, true, true, "", 12);
    append_member(&member_obj, "sos_commands/startup/", 0, true, true, true, "", 12);
    append_member(&member_obj, "etc/rc.d/", 0, true, true, true, "", 12);
    /* kernel */
    append_member(&member_obj, "etc/kdump.conf", 0, false, false, false, "==== kernel ====", 12);
    append_member(&member_obj, "etc/sysctl.conf", 0, false, false, false, "", 12);
    append_member(&member_obj, "sos_commands/kernel/sysctl_-a", 0, false, false, false, "", 12);
    append_member(&member_obj, "var/crash/", 0, true, true, true, "", 12);
    append_member(&member_obj, "sos_commands/abrt/", 0, true, true, true, "", 12);
    append_member(&member_obj, "sos_commands/systemtap/", 0, true, true, true, "", 12);
    append_member(&member_obj, "sos_commands/cgroups/", 0, true, true, true, "", 12);
    append_member(&member_obj, "etc/dracut.conf", 0, false, false, false, "", 12);
    append_member(&member_obj, "usr/lib/dracut/", 0, true, true, true, "", 12);
    append_member(&member_obj, "sos_commands/dracut/", 0, true, true, true, "", 12);
    append_member(&member_obj, "sys/kernel/", 0, true, true, true, "", 12);
    /* libraries */
    append_member(&member_obj, "etc/ld.so.conf", 0, false, false, false, "==== libraries ====", 12);
    append_member(&member_obj, "etc/ld.so.conf.d/", 0, true, true, true, "", 12);
    append_member(&member_obj, "sos_commands/libraries/", 0, true, true, true, "", 12);
    /* networking */
    append_member(&member_obj, "etc/host", 0, true, false, false, "==== networking ====", 12);
    append_member(&member_obj, "ip_addr", 0, false, false, false, "", 12);
    append_member(&member_obj, "route", 0, false, false, false, "", 12);
    append_member(&member_obj, "etc/networks", 0, false, false, false, "", 12);
    append_member(&member_obj, "etc/resolv.conf", 0, false, false, false, "", 12);
    append_member(&member_obj, "etc/dnsmasq.conf", 0, false, false, false, "", 12);
    append_member(&member_obj, "etc/sysconfig/network-scripts/ifcfg-", 0, true, false, false, "", 12);
    append_member(&member_obj, "etc/firewalld/", 0, true, true, true, "", 12);
    append_member(&member_obj, "sos_commands/firewalld/", 0, true, true, true, "", 12);
    append_member(&member_obj, "var/log/firewalld", 0, false, false, false, "", 12);
    append_member(&member_obj, "etc/nftables/", 0, true, true, true, "", 12);
    append_member(&member_obj, "etc/iproute2/", 0, true, true, true, "", 12);
    append_member(&member_obj, "proc/net/dev", 0, false, false, false, "", 12);
    append_member(&member_obj, "proc/net/sockstat", 0, false, false, false, "", 12);
    append_member(&member_obj, "sos_commands/networking/ethtool_-S", 0, true, false, false, "", 12);
    append_member(&member_obj, "sos_commands/networking/ethtool_-i", 0, true, false, false, "", 12);
    append_member(&member_obj, "sos_commands/networking/", 0, true, true, true, "", 12);
    append_member(&member_obj, "etc/NetworkManager/", 0, true, true, true, "", 12);
    append_member(&member_obj, "sos_commands/networkmanager/", 0, true, true, true, "", 12);
    append_member(&member_obj, "sos_commands/wireless/", 0, true, true, true, "", 12);
    append_member(&member_obj, "netstat", 0, false, false, false, "", 12);
    append_member(&member_obj, "etc/ppp/", 0, true, true, true, "", 12);
    append_member(&member_obj, "sos_commands/ppp/", 0, true, true, true, "", 12);
    append_member(&member_obj, "etc/wvdial.conf", 0, false, false, false, "", 12);
    append_member(&member_obj, "proc/net/bonding/", 0, true, true, true, "", 12);
    /* security */
    append_member(&member_obj, "etc/sudoers", 0, false, false, false, "==== security ====", 12);
    append_member(&member_obj, "etc/sudoers.d/", 0, true, true, true, "", 12);
    append_member(&member_obj, "etc/pam.d/", 0, true, true, true, "", 12);
    append_member(&member_obj, "sos_commands/pam/", 0, true, true, true, "", 12);
    append_member(&member_obj, "etc/ssh/", 0, true, true, true, "", 12);
    append_member(&member_obj, "var/log/secure", 0, true, false, false, "", 12);
    append_member(&member_obj, "etc/audit/", 0, true, true, true, "", 12);
    append_member(&member_obj, "sos_commands/auditd/", 0, true, true, true, "", 12);
    append_member(&member_obj, "var/log/audit/", 0, true, true, true, "", 12);
    append_member(&member_obj, "sos_commands/crypto/", 0, true, true, true, "", 12);
    append_member(&member_obj, "etc/pki/", 0, true, true, true, "", 12);
    append_member(&member_obj, "etc/sestatus.conf", 0, false, false, false, "", 12);
    append_member(&member_obj, "etc/selinux/", 0, true, true, true, "", 12);
    append_member(&member_obj, "sos_commands/selinux/", 0, true, true, true, "", 12);
    append_member(&member_obj, "etc/krb5.conf", 0, false, false, false, "", 12);
    append_member(&member_obj, "etc/krb5.conf.d/", 0, true, true, true, "", 12);
    append_member(&member_obj, "sos_commands/krb5/", 0, true, true, true, "", 12);
    append_member(&member_obj, "etc/ipsec.conf", 0, false, false, false, "", 12);
    append_member(&member_obj, "etc/ipsec.d/", 0, true, true, true, "", 12);
    append_member(&member_obj, "usr/share/crypto-policies/", 0, true, true, true, "", 12);
    /* mail */
    append_member(&member_obj, "etc/mail/", 0, true, true, true, "==== mail ====", 12);
    append_member(&member_obj, "sos_commands/sendmail/", 0, true, true, true, "", 12);
    append_member(&member_obj, "etc/postfix/", 0, true, true, true, "", 12);
    append_member(&member_obj, "sos_commands/postfix/", 0, true, true, true, "", 12);
    /* GUI */
    append_member(&member_obj, "etc/X11/", 0, true, true, true, "==== GUI ====", 12);
    append_member(&member_obj, "sos_commands/x11/", 0, true, true, true, "", 12);
    append_member(&member_obj, "etc/gdm/", 0, true, true, true, "", 12);
    append_member(&member_obj, "sos_commands/gdm/", 0, true, true, true, "", 12);
    /* alternatives */
    append_member(&member_obj, "etc/alternatives/", 0, true, true, true, "==== alternatives ====", 12);
    append_member(&member_obj, "sos_commands/alternatives/", 0, true, true, true, "", 12);
    /* alsa */
    append_member(&member_obj, "etc/alsa/", 0, true, true, true, "==== alsa ====", 12);
    append_member(&member_obj, "sos_commands/soundcard/", 0, true, true, true, "", 12);
    append_member(&member_obj, "usr/share/alsa/", 0, true, true, true, "", 12);
    /* anaconda */
    append_member(&member_obj, "var/log/anaconda/", 0, true, true, true, "==== anaconda ====", 12);
    /* ansible */
    append_member(&member_obj, "etc/ansible/", 0, true, true, true, "==== ansible ====", 12);
    append_member(&member_obj, "sos_commands/ansible/", 0, true, true, true, "", 12);
    /* ceph */
    append_member(&member_obj, "sos_commands/ceph/", 0, true, true, true, "==== ceph ====", 12);
    /* corosync */
    append_member(&member_obj, "etc/corosync/", 0, true, true, true, "==== corosync ====", 12);
    append_member(&member_obj, "sos_commands/corosync/", 0, true, true, true, "", 12);
    /* cron */
    append_member(&member_obj, "etc/anacrontab", 0, false, false, false, "==== cron ====", 12);
    append_member(&member_obj, "etc/crontab", 0, false, false, false, "", 12);
    append_member(&member_obj, "etc/cron.deny", 0, false, false, false, "", 12);
    append_member(&member_obj, "etc/cron.d/", 0, true, true, true, "", 12);
    append_member(&member_obj, "etc/cron.hourly/", 0, true, true, true, "", 12);
    append_member(&member_obj, "etc/cron.daily/", 0, true, true, true, "", 12);
    append_member(&member_obj, "etc/cron.weekly/", 0, true, true, true, "", 12);
    append_member(&member_obj, "etc/cron.monthly/", 0, true, true, true, "", 12);
    append_member(&member_obj, "var/spool/cron/", 0, true, true, true, "", 12);
    append_member(&member_obj, "var/log/cron", 0, false, false, false, "", 12);
    /* chrony */
    append_member(&member_obj, "etc/chrony.conf", 0, false, false, false, "==== chrony ====", 12);
    append_member(&member_obj, "sos_commands/chrony/", 0, true, true, true, "", 12);
    append_member(&member_obj, "var/lib/chrony/", 0, true, true, true, "", 12);
    /* cups */
    append_member(&member_obj, "etc/cups/", 0, true, true, true, "==== cups ====", 12);
    append_member(&member_obj, "sos_commands/cups/", 0, true, true, true, "", 12);
    /* dbus */
    append_member(&member_obj, "etc/dbus-1/", 0, true, true, true, "==== dbus ====", 12);
    append_member(&member_obj, "sos_commands/dbus/", 0, true, true, true, "", 12);
    append_member(&member_obj, "var/lib/dbus/", 0, true, true, true, "", 12);
    /* dhcp */
    append_member(&member_obj, "etc/dhcp/", 0, true, true, true, "==== dhcp ====", 12);
    /* dnf/yum */
    append_member(&member_obj, "etc/yum.conf", 0, false, false, false, "==== dnf/yum ====", 12);
    append_member(&member_obj, "etc/yum.repos.d/", 0, true, true, true, "", 12);
    append_member(&member_obj, "etc/yum/", 0, true, true, true, "", 12);
    append_member(&member_obj, "sos_commands/yum/", 0, true, true, true, "", 12);
    append_member(&member_obj, "etc/dnf/", 0, true, true, true, "", 12 );
    append_member(&member_obj, "sos_commands/dnf/", 0, true, true, true, "", 12);
    /* docker */
    append_member(&member_obj, "sos_commands/docker/", 0, true, true, true, "", 12);
    /* fcoe */
    append_member(&member_obj, "etc/fcoe/", 0, true, true, true, "==== fcoe ====", 12);
    append_member(&member_obj, "sos_commands/fcoe/", 0, true, true, true, "", 12);
    /* gss */
    append_member(&member_obj, "etc/gss/", 0, true, true, true, "==== gss ====", 12);
    append_member(&member_obj, "etc/gssproxy/", 0, true, true, true, "", 12);
    /* haproxy */
    append_member(&member_obj, "sos_commands/haproxy/", 0, true, true, true, "==== haproxy ====", 12);
    /* hpasm */
    append_member(&member_obj, "sos_commands/hpasm/", 0, true, true, true, "==== hpasm ====", 12);
    /* httpd */
    append_member(&member_obj, "etc/httpd/", 0, true, true, true, "==== httpd ====", 12);
    append_member(&member_obj, "sos_commands/apache/", 0, true, true, true, "", 12);
    append_member(&member_obj, "var/log/httpd/", 0, true, true, true, "", 12);
    /* java */
    append_member(&member_obj, "etc/java/", 0, true, true, true, "==== java ====", 12);
    append_member(&member_obj, "sos_commands/java/", 0, true, true, true, "", 12);
    /* kvm/libvirt */
    append_member(&member_obj, "etc/libvirt/", 0, true, true, true, "==== libvirt/kvm ====", 12);
    append_member(&member_obj, "sos_commands/libvirt/", 0, true, true, true, "", 12);
    append_member(&member_obj, "run/libvirt/", 0, true, true, true, "", 12);
    append_member(&member_obj, "sos_commands/kvm/", 0, true, true, true, "", 12);
    append_member(&member_obj, "sos_commands/virsh/", 0, true, true, true, "", 12);
    append_member(&member_obj, "var/log/libvirt/", 0, true, true, true, "", 12);
    /* ldap */
    append_member(&member_obj, "etc/openldap/", 0, true, true, true, "==== ldap ====", 12);
    append_member(&member_obj, "etc/nslcd.conf", 0, false, false, false, "", 12);
    append_member(&member_obj, "sos_commands/ldap/", 0, true, true, true, "", 12);
    /* logrotate */
    append_member(&member_obj, "etc/logrotate.conf", 0, false, false, false, "==== logrotate ====", 12);
    append_member(&member_obj, "etc/logrotate.d/", 0, true, true, true, "", 12);
    append_member(&member_obj, "sos_commands/logrotate/", 0, true, true, true, "", 12);
    append_member(&member_obj, "var/lib/logrotate/", 0, true, true, true, "", 12);
    /* lstopo */
    append_member(&member_obj, "sos_commands/lstopo/", 0, true, true, true, "==== lstopo ====", 12);
    /* nfs */
    append_member(&member_obj, "etc/nfs.conf", 0, false, false, false, "==== nfs ====", 12);
    append_member(&member_obj, "etc/nfsmount.conf", 0, false, false, false, "", 12);
    append_member(&member_obj, "sos_commands/nis/", 0, true, true, true, "", 12);
    /* oddjobd */
    append_member(&member_obj, "etc/oddjobd/", 0, true, true, true, "==== oddjobd ====", 12);
    append_member(&member_obj, "etc/oddjobd.conf.d/", 0, true, true, true, "", 12);
    /* opengl */
    append_member(&member_obj, "sos_commands/opengl/", 0, true, true, true, "==== opengl ====", 12);
    /* openshift */
    append_member(&member_obj, "sos_commands/openshift/", 0, true, true, true, "==== openshift ====", 12);
    /* openswan */
    append_member(&member_obj, "sos_commands/openswan/", 0, true, true, true, "==== openswan ====", 12);
    /* perl */
    append_member(&member_obj, "sos_commands/perl/", 0, true, true, true, "", 12);
    /* rear */
    append_member(&member_obj, "etc/rear/", 0, true, true, true, "==== rear ====", 12);
    append_member(&member_obj, "sos_commands/rear/", 0, true, true, true, "", 12);
    append_member(&member_obj, "var/log/rear/", 0, true, true, true, "", 12);
    /* ruby */
    append_member(&member_obj, "sos_commands/ruby/", 0, true, true, true, "==== ruby ====", 12);
    /* samba */
    append_member(&member_obj, "etc/samba/", 0, true, true, true, "==== samba ====", 12);
    append_member(&member_obj, "sos_commands/samba/", 0, true, true, true, "", 12);
    /* sar */
    append_member(&member_obj, "sos_commands/sar/", 0, true, true, true, "==== sar ====", 12);
    append_member(&member_obj, "var/log/sa/sar", 0, true, false, false, "", 12);
    /* snmp */
    append_member(&member_obj, "etc/snmp/", 0, true, true, true, "==== snmp ====", 12);
    /* sos */
    append_member(&member_obj, "etc/sos.conf", 0, false, false, false, "==== sos ====", 12);
    /* sssd */
    append_member(&member_obj, "sos_commands/sssd/", 0, true, true, true, "==== sssd ====", 12);
    /* sunrpc */
    append_member(&member_obj, "sos_commands/sunrpc/", 0, true, true, true, "==== sunrpc ====", 12);
    /* logs and journals */
    append_member(&member_obj, "etc/rsyslog.conf", 0, false, false, false, "==== logs and journals ====", 12);
    append_member(&member_obj, "var/log/dmesg", 0, false, false, false, "", 12);
    append_member(&member_obj, "var/log/messages", 0, true, false, false, "", 25);
    append_member(&member_obj, "sos_commands/logs/journalctl_--no-pager", 0, true, false, false, "", 25);
    /* others ( default item is 'skip') */ 
    append_member(&member_obj, "lib/", 0, true, true, false, "==== others ====", 12);
    append_member(&member_obj, "etc/", 0, true, true, true, "", 12);
    append_member(&member_obj, "sos_commands/", 0, true, true, false, "", 12);
    append_member(&member_obj, "dev/", 0, true, false, false, "", 12);
    append_member(&member_obj, "usr/", 0, true, true, false, "", 12);
    append_member(&member_obj, "var/", 0, true, true, false, "", 12);
    append_member(&member_obj, "proc/", 0, true, true, true, "", 12);

    return 0;
}
