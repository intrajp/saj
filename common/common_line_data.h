/*
 *  common_line_data.h - object definitions
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

#ifndef SAJ_COMMON_LINE_DATA_H
#define SAJ_COMMON_LINE_DATA_H

/* --max-stackframe=2007048 / 4096 = 489, so... */
#define MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR 488

/* the maximum line length in the sar file */
#define MAX_LINE_LENGTH  4096 

/* ---------- macros ( tweak if needed ) ---------- */

/*
 * Type for line retrieved from a file.
 */

typedef struct line_data
{
    const char _line[MAX_LINE_LENGTH - 1];
    struct line_data *next;

} node;

/*
 * Type for line retrieved from a svg file.
 */
typedef struct line_data2
{
    const char _line[MAX_LINE_LENGTH];
    const char _line2[MAX_LINE_LENGTH];
    struct line_data2 *next;

} node2;

/*
 * Declare type of file_data which should contain dir or file name 
 */
typedef struct
{
    /* file name to be written */
    char dirname[MAX_LINE_LENGTH];
    /* sos file name to be written */
    char sos_file_name_to_be_written[MAX_LINE_LENGTH];
    /* sos analyze file name to be written */
    char sos_analyze_file_name_to_be_written[MAX_LINE_LENGTH];
    /* sos analyze file time */
    char sos_analyze_file_time[MAX_LINE_LENGTH];
    /* sar file name to be written */
    char sar_file_name_to_be_written[MAX_LINE_LENGTH];
    /* svg file name to be written */
    char svg_file_name_to_be_written[MAX_LINE_LENGTH];
    /* log file name to be written */
    char log_file_name_to_be_written[MAX_LINE_LENGTH];
} file_data;

/*
 * This should become a living object
 *
 */
struct dir_file_name
{
    file_data dir_file_names;
};

/**** line_data things ****/

/*
 * Function Name: set_list()
 *
 * This function sets values to the list object (node) 
 *
 *  Caller : insert_node_top_of_the_list()
 *  Caller : append_list()
 *
 */
void set_list(node *obj, char *line, node *obj_next);

/*
 * Function Name: set_list2()
 *
 * This function sets values to the list2 object (node2) 
 *
 *  Caller : insert_node_top_of_the_list2()
 *  Caller : append_list2()
 *
 */
void set_list2(node2 *obj, char *line, char *line2, node2 *obj_next);

/*
 * Function Name: append_list()
 *
 * This function appends new object to the list object (node) 
 *
 *  Caller : allocate_mem_to_one_node()
 *  Caller : set_list()
 *
 *  Calls : allocate_mem_to_one_node()
 *  Calls : insert_node_top_of_the_list()
 *
 */
int append_list(node **obj, char *line);

/*
 * Function Name: append_list2()
 *
 * This function appends new object to the list2 object (node2) 
 *
 *  Caller : allocate_mem_to_one_node2()
 *  Caller : set_list2()
 *
 *  Calls : allocate_mem_to_one_node2()
 *  Calls : insert_node_top_of_the_list2()
 *
 */
int append_list2(node2 **obj, char *line, char *line2);

/*
 * Function Name: move_obj_to_the_last()
 *
 * This function moves some objects to the last by file no.x  
 *
 * Caller : main()
 *
 */
int move_obj_to_the_last(node **obj, int x);

/*
 * Function Name: print_and_file_write_analyzed_files ()
 *
 * This function searchs list object (node) by the given expression and print and write to file 
 *
 *  Caller : main ()
 *
 */
int print_and_file_write_analyzed_files(node **obj, const char *expression, const char *word, FILE *fp_w);

/*
 * Function Name: print_list()
 *
 * This function prints the list nodes
 *
 *  Caller : main()
 *
 */
void print_list(node **obj);

/*
 * Function Name: print_list2()
 *
 * This function prints the list2 nodes
 *
 *  Caller : main()
 *
 */
void print_list2(node2 **obj);

/*
 * Function Name: file_write_list()
 * 
 * This function writes list nodes to the file
 *
 *  Caller : main()
 *
 */
void file_write_list(node **obj, FILE *fp_w);

/*
 * Function Name: file_write_list2()
 * 
 * This function writes list2 nodes to the file
 *
 *  Caller : main()
 *
 */
void file_write_list2(node2 **obj, FILE *fp_w);

/*
 * Function Name: init_list()
 *
 * This function initializes the line list object ( node ) 
 *
 *  Caller : create_sar_analyzer_obj()
 *
 */
int init_list(node **obj);

/*
 * Function Name: init_list2()
 *
 * This function initializes the line2 list object ( node2 ) 
 *
 *  Caller : create_sar_analyzer_obj()
 *
 */
int init_list2(node2 **obj);

/*
 * Function Name: clear_list()
 *
 * This function clears the line list object (node) 
 *
 *  Caller : free_sar_analyzer_obj()
 *
 *  Calls : delete_obj()
 *
 */
int clear_list(node **obj);

/*
 * Function Name: clear_list2()
 *
 * This function clears the line list2 object (node2) 
 *
 *  Caller : free_sar_analyzer_obj()
 *
 *  Calls : delete_obj()
 *
 */
int clear_list2(node2 **obj);

#endif /* SAJ_COMMON_LINE_DATA_H */
