## unfold.sh - utility script for saj.
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

FILES=$(ls -l | awk '{ print $9 }')
counter=0
for i in $FILES
do
    if [[ "${i}" == *"tar.gz" ]]; then
        echo "${i}"
        tar zxvf "${i}"
    elif [[ "${i}" == *"tar.xz" ]]; then
        echo "${i}"
        tar xvf "${i}"
    elif [[ "${i}" == *".gz" ]]; then
        echo "${i}"
        gunzip -d "${i}"
    elif [[ "${i}" == *".zip" ]]; then
        echo "${i}"
        unzip "${i}"
    fi
    let counter=$counter+1
done
echo "unfolded ${counter} files"
