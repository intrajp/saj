/*
 *  global.c - common functions 
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>
#include <errno.h>
#include "global.h"
#include "../libsaj-sar-analyzer/common.h" 
#include "../libsaj-sosreport-analyzer/common.h" 

int remove_the_last_slash_from_dir_name(const char* dir_name)
{
    char str_tmp[MAX_FILE_NAME_LENGTH];
    memset(str_tmp, '\0', sizeof(str_tmp));
    char str_r[MAX_FILE_NAME_LENGTH];
    memset(str_r, '\0', sizeof(str_r));
    char str_set[MAX_FILE_NAME_LENGTH];
    memset(str_set, '\0', sizeof(str_set));
    size_t dir_len = strlen(dir_name);
    strncpy(str_tmp, reverse_the_string(str_r, (char*)dir_name),
        MAX_FILE_NAME_LENGTH - 1);

    static int set_dirname = 0;

    /* if last one is '/' */
    if (str_tmp[0] == 47) {
        reverse_the_string(str_set, str_tmp);
        str_set[dir_len - 1] = '\0';
        remove_the_last_slash_from_dir_name(str_set);
        
    }
    if (set_dirname == 0) {
        printf("dir_name_copied:%s\n",dir_name);
        printf("set_dirname:%d\n", set_dirname);
        strncpy(sos_dir_file_obj->dir_file_names.dirname, dir_name,
            MAX_FILE_NAME_LENGTH);
        set_dirname = 1;
    }
    return 0;
}

char* reverse_the_string(char* str_r, char* str_tmp)
{
    int i = 0;
    int j = 0;
    size_t strlen_str_tmp = 0;
    char tmp;
    //strlen_str_tmp = (int)strlen(str_tmp);
    strlen_str_tmp = strlen(str_tmp);
    j = strlen_str_tmp - 1;
    strncpy(str_r, str_tmp, MAX_FILE_NAME_LENGTH);
    while (i < j)
    {
        tmp = str_r[i];
        str_r[i] = str_r[j];
        str_r[j] = tmp;
        i++;
        j--;
    }
    return str_r;
}

char* cut_str_by_the_last_slash(char* str_b, char* str_tmp, size_t str_len)
{
    size_t i = 0;
    strncpy(str_b, str_tmp, str_len);
    for (i = 0; i < str_len; i ++)
        str_b[i] = str_tmp[i];
    str_b[i + 1] = '\0';

    return str_b;
}

char* cut_str_by_the_last_given_str(char* str_b, char* str_tmp, const char* delimiter)
{
    size_t str_len = 0;
    int cut_len = 0;
    str_len = strlen(str_tmp);
    char str_r[MAX_FILE_NAME_LENGTH];
    memset(str_r, '\0', sizeof(str_r));
    reverse_the_string(str_r, str_tmp);
    /* default means ascii '/' */
    size_t i_delimiter = 47;
    if (strcmp(delimiter, "_") == 0)
        i_delimiter = 95;
    for (size_t i = 0; i < str_len; i++) {
        if (str_r[i] == i_delimiter) {
            cut_len = i + 1;
            break;
        }
    }
    cut_len = str_len - cut_len;
    strncpy(str_b, str_tmp, MAX_FILE_NAME_LENGTH);
    str_b[cut_len + 1] = '\0';

    return str_b;
}

char* cut_str_from_the_last_given_str(char* str_ret, char* str_tmp, const char* delimiter)
{
    size_t str_len = 0;
    str_len = strlen(str_tmp);
    size_t i = 0;
    size_t l = 0;
    /* default means ascii '/' */
    size_t i_delimiter = 47;
    if (strcmp(delimiter, "_") == 0)
        i_delimiter = 95;
    for (i = 0; i < str_len; i ++) {
        if (str_tmp[i] == i_delimiter) {
            l = i;
            break;
        }
    }
    char str_[MAX_FILE_NAME_LENGTH];
    memset(str_, '\0', sizeof(str_)); 
    for (i = 0; i < l; i ++)
        str_[i] = str_tmp[i];
    char str_r[MAX_FILE_NAME_LENGTH];
    memset(str_r, '\0', sizeof(str_r));
    strncpy(str_ret, reverse_the_string(str_r, str_), MAX_FILE_NAME_LENGTH);

    return str_ret;
}
