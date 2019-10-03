/*
 *  common.h - common definitions
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

#include "../common/global.h"
#include "line_data.h"
#include "member_data.h"

#ifndef SOSREPORT_ANALYZER_COMMON_H
#define SOSREPORT_ANALYZER_COMMON_H

/*
 * These are pointers to the global data, it should be available
 * once sosreport_analyzer_init() was called.
 *
 * These structs are for ones of which should read directory,
 * or matched files in the directory.
 */

volatile extern node_m* member_obj;

extern struct line_data* tmp_obj;
extern struct dir_file_name* sos_dir_file_obj;
extern struct line_data* hostname_sos_obj;
extern struct line_data* sos_version_obj;
extern struct line_data* sos_header_obj;
extern struct line_data* sos_analyze_obj;

extern struct line_data* sos_subtitle_analyze_obj;
extern struct line_data* sos_subtitle_general_obj;
extern struct line_data* sos_subtitle_member_obj;
extern struct line_data* sos_line_obj;
extern struct line_data* sos_tail_obj;

/* temporary object before sorting file names */
extern struct line_data* log_obj;

/* temporary object before sorting file names */
extern struct line_data* tmp_obj;

extern struct line_data* dir_read_obj;

/* we use this one for temporary array for directory read */
extern char* str_arr_tmp[MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR];

/* function pointers for analyze obj */
typedef int (*check_str_exists)(const char* line);
typedef int (*comment_analyzed)(const char* file_name, const char* file_name_this);

int append_members(void);

int initialize_objects(void);

FILE* file_open_check(FILE* fp, const char* file_name, const char* mode, int sar_only);

/*
 * read_file_pre()
 *
 * This function convey data to function read_file
 *
 */
int read_file_pre(const volatile char* member, const char* dir_name, int mcinfo,
                  int sar_only, const char* sos_file_all_write, const char* log_file_write,
                  int i);

/* 
 *  Function Name: check_result_dir()
 *
 *  This function checks result directory.
 *  If result directory does not exist, creates it.
 *
 *  Caller : main()
 *
 *  Calls : none
 *
 */
int check_result_dir(const char* dname, int sar_only, int tmp);

/* 
 *  Function Name: is_dir_present()
 *
 *  This function checks directory.
 *  If directory does not exist, returns 1.
 *  If directory exists returns 0.
 *
 *  Caller : main()
 *
 *  Calls : none
 *
 */
int is_dir_present(const char* dname, int sar_only);

/* 
 *  Function Name: is_sos_dir_present()
 *
 *  This function checks sos directory.
 *  If directory does not exist, returns 1.
 *  If directory exists returns 0.
 *
 *  Caller : main()
 *
 *  Calls : none
 *
 */
int is_sos_dir_present(const char* dname, int sar_only, int mcinfo);

/* 
 *  Function Name: check_time_span_str()
 *
 *  This function checks time-span string.
 *  If it's fine, returns 1, and if not returns 0
 *  should be in style '00:00-00:00' and no other
 *  Caller : main()
 *
 *  Calls : none
 *
 */
int check_time_span_str(const char* time_span_str);

/*
 * Function Name: get_dirname()
 *
 * This function returns dirname for analyzed result
 * 
 * Caller : main()
 *
 * Calls : none
 *
 */
const char* get_dirname(char[MAX_LINE_LENGTH]);

/*
 * Function Name: get_sos_file_name_to_be_written()
 *
 * This function returns sos_file_name_to_be_written for analyzed result
 * 
 * Caller : main()
 *
 * Calls : none
 *
 */
const char* get_sos_file_name_to_be_written(void);

/*
 * Function Name: get_sos_analyze_file_time()
 *
 * This function returns sos_analyze_file_time for analyzed result
 * 
 * Caller : main()
 *
 * Calls : none
 *
 */
const char* get_sos_analyze_file_time(void);

/*
 * Function Name: get_sos_analyze_file_name_to_be_written()
 *
 * This function returns sos_file_name_to_be_written for analyzed result
 * 
 * Caller : main()
 *
 * Calls : none
 *
 */
const char* get_sos_analyze_file_name_to_be_written(void);

/*
 * Function Name: get_sar_file_name_to_be_written()
 *
 * This function returns sar_file_name_to_be_written for analyzed result
 * 
 * Caller : main()
 *
 * Calls : none
 *
 */
const char* get_sar_file_name_to_be_written(void);

/*
 * Function Name: get_ps_file_name_to_be_written()
 *
 * This function returns ps_file_name_to_be_written for analyzed result
 * 
 * Caller : main()
 *
 * Calls : none
 *
 */
const char* get_ps_file_name_to_be_written(void);

/*
 * Function Name: get_log_file_name_to_be_written()
 *
 * This function returns log_file_name_to_be_written for analyzed result
 * 
 * Caller : main()
 *
 * Calls : none
 *
 */
const char* get_log_file_name_to_be_written(void);

/*
 *  Function Name: sos_file_to_write()
 *
 *  This function sets file name to be written to the sosreport_analyzer_obj.
 *
 *  Caller : main()
 *
 */
void sos_file_to_write(int sar_only);

/*
 * free_sosreport_analyzer_obj()
 *
 * This function frees sosreport-analyzer objects
 *
 */
void free_sosreport_analyzer_obj(int sar_only);


#endif /* SOSREPORT_ANALYZER_COMMON_H */
