/*
 * line_data.c - object functions 
 * This file contains the contents of saj.
 *
 * Copyright (C) 2019 Shintaro Fujiwara
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301 USA
 */

#include <string.h>
#include "common.h"
#include "line_data.h"

/* tmp_obj */
struct line_data tmp_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* tmp2_obj */
struct line_data2 tmp2_obj_raw =
    {
        "\0", /* each line */
        "\0", /* each line */
        NULL /* next pointer */
    };

struct line_data* tmp_obj = &tmp_obj_raw;
struct line_data2* tmp2_obj = &tmp2_obj_raw;

int init_list(node** obj)
{
    *obj = NULL;

    return 0;
}

int init_list2(node2** obj)
{
    *obj = NULL;

    return 0;
}

static node* __allocate_mem_to_one_node( void )
{
    return (struct line_data*)calloc(1, sizeof(struct line_data));
}

static node2* __allocate_mem_to_one_node2( void )
{
    return (struct line_data2*)calloc(1, sizeof(struct line_data2));
}

static int __insert_node_top_of_the_list(node** obj, char* line)
{
    /* setting current obj to the new obj */
    node *obj_next = *obj;
    *obj = __allocate_mem_to_one_node();
    /* setting current obj the the next pointer, this makes new object to the top of the list */
    set_list(*obj, line, obj_next);

    return 0;
}

static int __insert_node_top_of_the_list2(node2** obj, char* line, char* line2)
{
    /* setting current obj to the new obj */
    node2 *obj_next = *obj;
    *obj = __allocate_mem_to_one_node2();
    /* setting current obj the the next pointer, this makes new object to the top of the list */
    set_list2(*obj, line, line2, obj_next);

    return 0;
}

void set_list(node* obj, char* line, node* obj_next)
{
    const char* test_line = "\0";
    size_t len = 0;
    len = strlen(line);
    if (len < 0) {
        fprintf(stderr, "can't set %s\n", line);
        exit (EXIT_FAILURE);
    }
    if (len > MAX_LINE_LENGTH)
        strncpy((char*)obj->_line, test_line, 1);
    else
        strncpy((char*)obj->_line, line, MAX_LINE_LENGTH - 1);
    obj->next = obj_next;
    free(obj_next);
}

void set_list2(node2* obj, char* line, char* line2, node2* obj_next)
{
    const char* test_line = "\0";
    const char* test_line2 = "\0";
    size_t len, len2 = 0;
    len = strlen(line);
    len2 = strlen(line2);
    if (len < 0) {
        fprintf(stderr, "can't set %s\n", line);
        exit (EXIT_FAILURE);
    }
    if (len2 < 0) {
        fprintf(stderr, "can't set %s\n", line2);
        exit (EXIT_FAILURE);
    }
    if ((len > MAX_LINE_LENGTH) && (len2 > MAX_LINE_LENGTH)) {
        strncpy((char*)obj->_line, test_line, 1);
        strncpy((char*)obj->_line2, test_line2, 1);
    } else {
        strncpy((char*)obj->_line, line, MAX_LINE_LENGTH - 1);
        strncpy((char*)obj->_line2, line2, MAX_LINE_LENGTH - 1);
    }
    obj->next = obj_next;
    free(obj_next);
}

int append_list(node** obj, char* line)
{
    /* if no node found in the object, insert node in the very top of it */
    if (*obj == NULL) {
        __insert_node_top_of_the_list(obj, line);
    /* if some node exists in the object, find the very last of it and appending the new node */
    } else {
        node *obj_new = *obj;
        while (obj_new->next != NULL)
            obj_new = obj_new->next;
        obj_new->next = __allocate_mem_to_one_node();
        set_list(obj_new->next, line, NULL);
    }

    return 0;
}

int append_list2(node2** obj, char* line, char* line2)
{
    /* if no node2 found in the object, insert node2 in the very top of it */
    if (*obj == NULL) {
        __insert_node_top_of_the_list2(obj, line, line2);
    /* if some node2 exists in the object, find the very last of it and appending the new node2 */
    } else {
        node2 *obj_new = *obj;
        while (obj_new->next != NULL)
            obj_new = obj_new->next;
        obj_new->next = __allocate_mem_to_one_node2();
        set_list2(obj_new->next, line, line2, NULL);
    }

    return 0;
}

/* presently, not used */
int bubble_sort_object_by_the_string(char* str_arr[MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR], node** obj) 
{
    node* ptr_tmp = *obj;
    char str_cmp_member[MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR][MAX_LINE_LENGTH];
    for (int i = 0; i < MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR; i++)
        memset(str_cmp_member[i], '\0', sizeof(str_cmp_member[i])); 
    char* str_tmp = NULL;
    int obj_size = 0, ii = 0;

    /* read from object and copy strings to an array */
    while (ptr_tmp != NULL) {
        str_arr[obj_size] = (char*) & (ptr_tmp->_line[0]); 
        obj_size++;
        ptr_tmp = ptr_tmp->next;
    }
    /* bubble sort the array */
    for (int j= 0; j < obj_size; j++) {
        /* This makes largest item to the end of an array. */
        for (int i = 0; i < obj_size - (1 + j); i++) {
            ii = i + 1;
            if (strcmp(str_arr[i], str_arr[ii]) > 0) {
                str_tmp = str_arr[i]; 
                str_arr[i] = str_arr[ii]; 
                str_arr[ii] = str_tmp; 
            }
        }
    }
    /* end bubble sort */
    return obj_size;
}

/* sort svg obj */
int bubble_sort_object_by_the_string2(char* str_arr[20000], node2** obj) 
{
    node2* ptr_tmp = *obj;
    char* str_tmp = NULL;
    int obj_size = 0, ii = 0;

    memset(str_arr, '\0', 20000); 

    /* read from object and copy strings to an array */
    while (ptr_tmp != NULL) {
        str_arr[obj_size] = (char*) ptr_tmp->_line; 
        obj_size++;
        ptr_tmp = ptr_tmp->next;
    }
    /* bubble sort the array */
    for (int j= 0; j < obj_size; j++) {
        /* This makes largest item to the end of an array. */
        for (int i = 0; i < obj_size - (1 + j); i++) {
            ii = i + 1;
            if (strcmp(str_arr[i], str_arr[ii]) > 0) {
                str_tmp = str_arr[i]; 
                str_arr[i] = str_arr[ii]; 
                str_arr[ii] = str_tmp; 
                str_tmp = NULL; 
            }
        }
    }
    /* end bubble sort */
    free(ptr_tmp);
    return obj_size;
}

char* search_list(node** obj, const volatile char* line, char result[MAX_LINE_LENGTH])
{
    node* ptr_tmp = *obj;
    char str_cmp_line[MAX_LINE_LENGTH];
    memset(str_cmp_line, '\0', MAX_LINE_LENGTH); 
    char str_cmp__line[MAX_LINE_LENGTH];
    memset(str_cmp__line, '\0', MAX_LINE_LENGTH); 
    strcpy(str_cmp_line, (const char *) line);
    memset(result, '\0', MAX_LINE_LENGTH); 
    char* result_p = & (result[MAX_LINE_LENGTH]);

    const char s[8] = "="; /* this is the delimiter */

    while (ptr_tmp != NULL) {
        strcpy(str_cmp__line, ptr_tmp->_line);
        char *token = NULL;
        token = strtok((char*)str_cmp__line, s);
        if ((strcmp(str_cmp__line, "") != 0) && (strcmp(str_cmp_line, token) == 0)) {
            strcpy(result, ptr_tmp->_line);
            return result_p;
        }
        ptr_tmp = ptr_tmp->next;
    }

    return result_p;
}

char* search_first_string(node** obj, char* str)
{
    node* ptr_tmp = *obj;
    while (ptr_tmp != NULL) {
        if (strstr(ptr_tmp->_line, str) != NULL)
            return (char*) ptr_tmp->_line;
        ptr_tmp = ptr_tmp->next;
    }
    return "nothing";
}

int print_and_file_write_analyzed_files(node** obj, const char* expression , const char* word, FILE* fp_w)
{
    node* ptr_tmp = *obj;
    while (ptr_tmp != NULL) {
        /* moving next, do something, moving next ... */
        char str_tmp[MAX_LINE_LENGTH] = "#";
        size_t str_len = 0;
        str_len = strlen(ptr_tmp->_line);
        if (str_len < 0)
        {
            fprintf(stderr, "can't set %s\n", ptr_tmp->_line);
            exit(EXIT_FAILURE);
        }
        if (str_len >= 0) {
            strncpy(str_tmp, ptr_tmp->_line, MAX_LINE_LENGTH - 1); 
        }

        if (strstr(str_tmp, expression) != NULL) {
          if (word != NULL) {
              printf("%s\n", str_tmp);
          }
          if (fp_w != NULL)
              fprintf(fp_w, "%s\n", str_tmp);
        }
        ptr_tmp = ptr_tmp->next;
    }
    return 0;
}

void print_list(node** obj)
{
    node* ptr_tmp = *obj;
    while (ptr_tmp != NULL) {
        printf("%s\n", ptr_tmp->_line);
        ptr_tmp = ptr_tmp->next;
    }
}

void print_list2(node2** obj)
{
    node2* ptr_tmp = *obj;
    while (ptr_tmp != NULL) {
        printf("%s,", ptr_tmp->_line);
        printf("%s\n", ptr_tmp->_line2);
        ptr_tmp = ptr_tmp->next;
    }
}

const char* echo_list(node** obj)
{
    node* ptr_tmp = *obj;
    while (ptr_tmp != NULL) {
        return(ptr_tmp->_line);
        ptr_tmp = ptr_tmp->next;
    }
    return(ptr_tmp->_line);
}

void file_write_list(node** obj, FILE* fp_w)
{
    node* ptr_tmp = *obj;
    while (ptr_tmp != NULL) {
        fprintf(fp_w, "%s\n", ptr_tmp->_line);
        ptr_tmp = ptr_tmp->next;
    }
    ptr_tmp = NULL;
    free(ptr_tmp);
}

void file_write_list_(node** obj, FILE* fp_w)
{
    node* ptr_tmp = *obj;
    while (ptr_tmp != NULL) {
        fprintf(fp_w, "%s", ptr_tmp->_line);
        ptr_tmp = ptr_tmp->next;
    }
    ptr_tmp = NULL;
    free(ptr_tmp);
}

char* get_sar_value_from_string(char* str)
{
    char* p = NULL;

    p = str;
    int i = 0;
    while(i<4) {
        if ((p == NULL) || (p+1 == NULL))
            break;
        p = strstr(p+1, ",");
        i++;
    }
    p = p+1;

    return p;
}

char* get_date_from_string(char* str)
{
    char* p = NULL;

    p = str;
    int i = 0;
    while(i<2) {
        if ((p == NULL) || (p+1 == NULL))
            break;
        p = strstr(p+1, ",");
        i++;
    }
    p = p+1;

    return p;
}

char* get_str_from_string(char* str, int count, char* delimiter)
{
    char* p = NULL;

    p = str;
    int i = 0;
    while(i<count) {
        if ((p == NULL) || (p+1 == NULL))
            break;
        p = strstr(p+1, delimiter);
        i++;
    }
    p = p+1;

    return p;
}

char* get_cpus_from_string(char* str)
{
    char* p = NULL;

    p = str;
    int i = 0;
    while(i<2) {
        if ((p == NULL) || (p+1 == NULL))
            break;
        p = strstr(p+1, "(");
        i++;
    }

    return p;
}

char* terminate_string(char* str, int point, char* delimiter)
{
    int position;
    char* p = NULL;

    p = str;
    int i = 0;
    while(i<point) {
        if ((p == NULL) || (p+1 == NULL))
            break;
        p = strstr(p+1, delimiter);
        i++;
    }
    if ((position = p - str) < 0)
        return str;

    str[position] = '\0'; 

    return str;
}

void file_write_svg(char* item, char* str, int data_lines, double width, FILE* fp_w)
{
    if ((strcmp(item, "cpu_usr") == 0) && (data_lines == 0)) {
        fprintf(fp_w, "%s\n", "<svg width=\"1010\" height=\"160\" xmlns=\"http://www.w3.org/2000/svg\">");
        fprintf(fp_w, "%s\n", "  <line x1=\"10\" y1=\"10\" x2=\"10\" y2=\"110\" stroke=\"gray\"/>");
        fprintf(fp_w, "%s\n", "  <line x1=\"10\" y1=\"10\" x2=\"1010\" y2=\"10\" stroke=\"gray\"/>");
        fprintf(fp_w, "%s\n", "  <line x1=\"10\" y1=\"110\" x2=\"1010\" y2=\"110\" stroke=\"gray\"/>");
    } else {
        fprintf(fp_w, "%s\n", str);
    }
}

void file_write_date_svg(char* item, char* str, int data_lines, double width, char* start, FILE* fp_w)
{
    if ((strcmp(item, "cpu_usr") == 0) && (data_lines == 0)) {
        fprintf(fp_w, "%s\n", "<g font-family=\"sans-serif\" fill=\"black\" font-size=\"10\">");
        char str_date[MAX_LINE_LENGTH];
        memset(str_date, '\0', sizeof(str_date));
        char* str_date_first = NULL;
        if (strcmp(start, "start") == 0)
            str_date_first = "   <text x=\"10\" y=\"120\">";
        if (strcmp(start, "end") == 0)
            str_date_first = "   <text x=\"955\" y=\"120\">";
        char* str_date_last = "</text>";
        snprintf(str_date, MAX_LINE_LENGTH, "%s%s%s\n", str_date_first, str, str_date_last);
        fprintf(fp_w, "%s", str_date);
        fprintf(fp_w, "%s\n", "</g>");
    }
}

void file_write_time_svg(char* item, char* str, int data_lines, double width, char* start, FILE* fp_w)
{
    if ((strcmp(item, "cpu_usr") == 0) && (data_lines == 0)) {
        char str_time[MAX_LINE_LENGTH];
        memset(str_time, '\0', sizeof(str_time));
        char* str_time_first = NULL;
        if (strcmp(start, "start") == 0)
            str_time_first = "   <text x=\"10\" y=\"130\">";
        if (strcmp(start, "end") == 0)
            str_time_first = "   <text x=\"955\" y=\"130\">";
        char* str_time_last = "</text>";
        snprintf(str_time, MAX_LINE_LENGTH, "%s%s%s\n", str_time_first, str, str_time_last);
        fprintf(fp_w, "%s", str_time);
    }
}

int clear_list(node** obj)
{
    while (*obj != NULL) {
        node* obj_new = (*obj) -> next;
        free(*obj);
        *obj = obj_new;
    }
    return 0;
}

int clear_list2(node2** obj)
{
    while (*obj != NULL) {
        node2* obj_new = (*obj) -> next;
        free(*obj);
        *obj = obj_new;
    }
    return 0;
}
