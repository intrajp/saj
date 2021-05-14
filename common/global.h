/*
 *  global.h - common definitions
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

#ifndef SAJ_GLOBAL_H
#define SAJ_GLOBAL_H

#include <stddef.h>

#define PROGRAM_VERSION 0
#define PROGRAM_RELEASE 3
#define PROGRAM_SUB_RELEASE 1

/* the maximum line length of file name */
#define MAX_FULL_PATH_LENGTH  512

/* the maximum line length in the sar file */
#define MAX_LINE_LENGTH  4096

/* the maximum line length of file name */
#define MAX_FILE_NAME_LENGTH  255

/* the maximum analyze files */
#define MAX_ANALYZE_FILES 31

/* the maximum size of analyze file */
#define MAX_ANALYZE_FILE_SIZE 10485760 

/* the minimum string length of the item for member */
#define MIN_ITEM_STRING_LENGTH 2

/* the maximum string length of the item for member */
#define MAX_ITEM_STRING_LENGTH 25

/* the minimum string length of the member */
#define MIN_MEMBER_STRING_LENGTH 2

/* the maximum string length of the member */
#define MAX_MEMBER_STRING_LENGTH 100

/*
 * remove_the_last_slash_from_dir_name()
 *
 * This function removes the last slash from the string (dir_name)
 *
 */
int remove_the_last_slash_from_dir_name(const char* dir_name);

/*
 * reverse_the_string()
 *
 * This function reverse the string and set it to str_r and return
 *
 */
char* reverse_the_string(char* str_r, char* str_p);

/*
 * cut_str_from_the_last_given_str()
 *
 * This function returns the string from the last given str to 'str_ret'.
 * Please give delimiter.
 *
 */
char* cut_str_from_the_last_given_str(char* str_ret, char* str_tmp,
                                      const char* delimiter);

/*
 * cut_str_by_the_last_slash()
 *
 * This function returns the string to 'str_b' up to the last slash
 * when string given with the length. 
 *
 */
char* cut_str_by_the_last_slash(char* str_b, char* str_p, size_t str_len);

/*
 * cut_str_by_the_last_given_str()
 *
 * This function returns the string to the 'str_b' up to the last
 * given delimiter. 
 *
 */
char* cut_str_by_the_last_given_str(char* str_b, char* str_tmp,
                                    const char* delimiter);

#endif /* SAJ_GLOBAL_H */
