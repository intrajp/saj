## align_netstat.sh - utility script for saj.
## This file contains the contents of saj.
##
##  Copyright (C) 2019 Shintaro Fujiwara
##
##  This library is free software; you can redistribute it and/or
##  modify it under the terms of the GNU Lesser General Public
##  License as published by the Free Software Foundation; either
##  version 2.1 of the License, or (at your option) any later version.
##
##  This library is distributed in the hope that it will be useful,
##  but WITHOUT ANY WARRANTY; without even the implied warranty of
##  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
##  Lesser General Public License for more details.
##
##  You should have received a copy of the GNU Lesser General Public
##  License along with this library; if not, write to the Free Software
##  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
##  02110-1301 USA
####
##
## tweek if needed
##

#!/bin/bash

PROC_NET_NETSTAT=$1
if [ -z ${PROC_NET_NETSTAT} ] || [[ "${PROC_NET_NETSTAT}" != *"netstat" ]]; then
    echo "give proc/net/netstat"
    exit 1
fi
count=0
while read line
do
    if [ $count -eq 0 ]; then
        IFS=' ' read -r -a arr0 <<<  $(echo ${line})
    fi
    if [ $count -eq 1 ]; then
        IFS=' ' read -r -a arr1 <<<  $(echo ${line})
    fi
    if [ $count -eq 2 ]; then
        IFS=' ' read -r -a arr2 <<<  $(echo ${line})
    fi
    if [ $count -eq 3 ]; then
        IFS=' ' read -r -a arr3 <<<  $(echo ${line})
    fi
    count=$((count+1))
done < "${PROC_NET_NETSTAT}"
####
for index in "${!arr0[@]}"
do
    echo "${arr0[index]} ${arr1[index]}"
done
echo "----"
for index in "${!arr2[@]}"
do
    echo "${arr2[index]} ${arr3[index]}"
done
exit 0
