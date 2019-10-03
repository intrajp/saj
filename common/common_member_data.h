/*
 *  common_member_data.h - object definitions
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

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#ifndef SAJ_COMMON_MEMBER_DATA_H
#define SAJ_COMMON_MEMBER_DATA_H

/* the maximum line length in the sar file */
#define MAX_LINE_LENGTH  4096 

/* the maximum member string length */
#define MAX_MEMBER_LENGTH  256 

/* the maximum item numbers in the configuration file */
#define MAX_ITEM_NUMBERS    25 

/* the maximum item strings in the configuration file */
#define MAX_ITEM_STRINGS    30 

/* 20 items each 30 bytes */
typedef struct
{
    char item_name [MAX_ITEM_NUMBERS][MAX_ITEM_STRINGS + 1];

} item_arr;

/* 488 files each 255 bytes */
typedef struct
{
    char file_name [MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR][MAX_FILE_NAME_LENGTH + 1];

} file_name_arr;

/*
 * for member.
 */

typedef struct member_data
{
    const char _member[MAX_MEMBER_LENGTH - 1];
    int mcinfo;
    bool read_dir;
    bool dir_recursive_read;
    bool dir_root_read;
    const char sub_title[MAX_MEMBER_LENGTH - 1];
    int item_num;
    int file_num;
    item_arr item_names;
    file_name_arr file_names;
    int item_max;
    struct member_data *next;

} node_m;

#endif /* SAJ_COMMON_MEMBER_DATA_H */
