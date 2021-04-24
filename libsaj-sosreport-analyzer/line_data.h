/*
 *  line_data.h - object definitions
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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../libsaj-sar-analyzer/common.h" 
#include "../common/common_line_data.h" 

#ifndef SOSREPORT_ANALYZER_LINE_DATA_H
#define SOSREPORT_ANALYZER_LINE_DATA_H

int init_list(node** obj);
int init_list2(node2** obj);
void set_list(node* obj, char* line, node* obj_next);
void set_list2(node2* obj, char* line, char* line2, node2* obj_next);
int append_list(node** obj, char* line);
int append_list2(node2** obj, char* line, char* line2);
int bubble_sort_object_by_the_string(char* str_arr[MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR], node** obj);
int print_and_file_write_analyzed_files(node** obj, const char* expression , const char* word, FILE* fp_w);
void print_list(node** obj);
void print_list2(node2** obj);
const char* echo_list(node** obj);
void file_write_list(node** obj, FILE* fp_w);
void file_write_list2(node2** obj, FILE* fp_w);
void file_write_list_(node** obj, FILE* fp_w);
int clear_list(node** obj);
int clear_list2(node2** obj);

/*
 * Function Name: search_list ()
 *
 * This function search given string from the node and if found, set string to char array
 *
 *  Caller : read_file_pre ()
 *
 *  Calls : none
 *
 */
char* search_list(node** obj, const volatile char* line, char result[MAX_LINE_LENGTH]);


#endif /* SOSREPORT_ALANYZER_LINE_DATA_H */
