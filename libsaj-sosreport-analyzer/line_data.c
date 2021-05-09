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
    if (((strcmp(item, "cpu_usr") == 0) || (strcmp(item, "memory_memused") == 0) ||
        (strcmp(item, "block_device_util") == 0) || (strcmp(item, "ldavg_one") == 0)) && (data_lines == 0)) {
        fprintf(fp_w, "%s\n", "<svg width=\"1010\" height=\"160\" xmlns=\"http://www.w3.org/2000/svg\">");
        fprintf(fp_w, "%s\n", "  <line x1=\"10\" y1=\"10\" x2=\"10\" y2=\"110\" stroke=\"gray\"/>");
        fprintf(fp_w, "%s\n", "  <line x1=\"10\" y1=\"10\" x2=\"1010\" y2=\"10\" stroke=\"gray\"/>");
        fprintf(fp_w, "%s\n", "  <line x1=\"10\" y1=\"110\" x2=\"1010\" y2=\"110\" stroke=\"gray\"/>");
        fprintf(fp_w, "%s\n", "  <line x1=\"1010\" y1=\"10\" x2=\"1010\" y2=\"110\" stroke=\"gray\"/>");
    } else {
        fprintf(fp_w, "%s\n", str);
    }
}

void file_write_date_svg(char* item, char* str, int data_lines, double width, char* start, FILE* fp_w)
{
    if (((strcmp(item, "cpu_usr") == 0) || (strcmp(item, "memory_memused") == 0) ||
        (strcmp(item, "block_device_util") == 0) || (strcmp(item, "ldavg_one") == 0)) && (data_lines == 0)) {
        fprintf(fp_w, "%s\n", "<g font-family=\"sans-serif\" fill=\"black\" font-size=\"10\">");
        char str_date[MAX_LINE_LENGTH];
        memset(str_date, '\0', sizeof(str_date));
        char* str_date_first = NULL;
        if (strcmp(start, "start") == 0)
            str_date_first = "  <text x=\"10\" y=\"120\">";
        if (strcmp(start, "end") == 0)
            str_date_first = "  <text x=\"955\" y=\"120\">";
        char* str_date_last = "</text>";
        snprintf(str_date, MAX_LINE_LENGTH, "%s%s%s\n", str_date_first, str, str_date_last);
        fprintf(fp_w, "%s", str_date);
    }
}

void file_write_time_svg(char* item, char* str, int data_lines, double width, char* start, FILE* fp_w)
{
    if (((strcmp(item, "cpu_usr") == 0) || (strcmp(item, "memory_memused") == 0) ||
        (strcmp(item, "block_device_util") == 0) || (strcmp(item, "ldavg_one") == 0)) && (data_lines == 0)) {
        char str_time[MAX_LINE_LENGTH];
        memset(str_time, '\0', sizeof(str_time));
        char* str_time_first = NULL;
        if (strcmp(start, "start") == 0)
            str_time_first = "  <text x=\"10\" y=\"130\">";
        if (strcmp(start, "end") == 0)
            str_time_first = "  <text x=\"955\" y=\"130\">";
        char* str_time_last = "</text>";
        snprintf(str_time, MAX_LINE_LENGTH, "%s%s%s\n", str_time_first, str, str_time_last);
        fprintf(fp_w, "%s", str_time);
        fprintf(fp_w, "%s\n", "</g>");
    }
}

void write_linux_line_to_file(node** obj, char* item, FILE* fp_w)
{
    char* str_thisbox_pre;
    char str_thisbox[MAX_LINE_LENGTH];
    memset(str_thisbox, '\0', sizeof(str_thisbox));
    char* str_linux_first = "  <text x=\"50\" y=\"8\">";
    char* str_linux_last = "</text>";
    str_thisbox_pre = search_first_string(obj, "Linux");
    char* cpus = get_cpus_from_string(str_thisbox_pre);
    terminate_string(str_thisbox_pre, 3, " ");
    if (strcmp(item, " CPU All ") == 0)
        snprintf(str_thisbox, MAX_LINE_LENGTH, "%s%s %s%s%s\n", str_linux_first, str_thisbox_pre,
            cpus, item, str_linux_last);
    else
        snprintf(str_thisbox, MAX_LINE_LENGTH, "%s%s %s%s\n", str_linux_first, str_thisbox_pre,
            item, str_linux_last);
    fprintf(fp_w, "%s", str_thisbox);
}

int create_svg_file(node2** obj, char* item, FILE* fp_w, int utility)
{
    int block_devices = get_block_device_numbers();
    // Here we set only 4 devices in this version.
    if (utility > 4)
        return 0;
    /* bubble sort svg obj */
    char* str_svg[20000] = { NULL };
    memset(str_svg, '\0', sizeof(str_svg));
    double size = bubble_sort_object_by_the_string2(str_svg, obj);
    /* end bubble sort svg obj */
    double horizontal_notch = 1000/size;
    double width = 10.0;
    char str_svg_draw[200000];
    memset(str_svg_draw, '\0', sizeof(str_svg_draw));
    if ((strcmp(item, "cpu_usr") == 0) || (strcmp(item, "memory_memused") == 0) ||
        ((strcmp(item, "block_device_util") == 0) && (utility == 1))) {
        strncat(str_svg_draw, "  <path stroke=\"green\" fill=\"none\" d=\"M 10 110 L " , 200000 - 1);
    } else if ((strcmp(item, "cpu_sys") == 0) || (strcmp(item, "ldavg_one") == 0)) {
        strncat(str_svg_draw, "  <path stroke=\"blue\" fill=\"none\" d=\"M 10 110 L " , 200000 - 1);
    } else if ((strcmp(item, "cpu_iowait") == 0) || (strcmp(item, "memory_swpused") == 0) ||
        (strcmp(item, "ldavg_15") == 0)) {
        strncat(str_svg_draw, "  <path stroke=\"red\" fill=\"none\" d=\"M 10 110 L " , 200000 - 1);
    // cpu_idle should start from upper position,so...
    } else if (strcmp(item, "cpu_idle") == 0) {
        strncat(str_svg_draw, "  <path stroke=\"orange\" fill=\"none\" d=\"M 10 10 L " , 200000 - 1);
    } else if (strcmp(item, "ldavg_five") == 0) {
        strncat(str_svg_draw, "  <path stroke=\"orange\" fill=\"none\" d=\"M 10 110 L " , 200000 - 1);
    } else if ((strcmp(item, "block_device_util") == 0) && (utility == 2)) {
        strncat(str_svg_draw, "  <path stroke=\"blue\" fill=\"none\" d=\"M 10 110 L " , 200000 - 1);
    } else if ((strcmp(item, "block_device_util") == 0) && (utility == 3)) {
        strncat(str_svg_draw, "  <path stroke=\"orange\" fill=\"none\" d=\"M 10 110 L " , 200000 - 1);
    // Here we set only 4 devices in this version.
    } else if ((strcmp(item, "block_device_util") == 0) && (utility == 4)) {
        strncat(str_svg_draw, "  <path stroke=\"mediumvioletred\" fill=\"none\" d=\"M 10 110 L " , 200000 - 1);
    }
    char str_horizontal_notch[256];
    memset(str_horizontal_notch, '\0', sizeof(str_horizontal_notch));
    char str_hundred[4];
    char str_fifty[3];
    char str_zero[2];
    char str_hight[MAX_FILE_NAME_LENGTH];
    char str_date[MAX_FILE_NAME_LENGTH];
    char str_date_only[MAX_FILE_NAME_LENGTH];
    char str_date_only_pre[MAX_FILE_NAME_LENGTH];
    char str_time_only[512];
    char str_device_name_this[100];
    char str_device_name[MAX_FILE_NAME_LENGTH];
    memset(str_hundred, '\0', sizeof(str_hundred));
    memset(str_fifty, '\0', sizeof(str_fifty));
    memset(str_zero, '\0', sizeof(str_zero));
    memset(str_hight, '\0', sizeof(str_hight));
    memset(str_date, '\0', sizeof(str_date));
    memset(str_date_only, '\0', sizeof(str_date_only));
    memset(str_date_only_pre, '\0', sizeof(str_date_only_pre));
    memset(str_time_only, '\0', sizeof(str_time_only));
    memset(str_device_name_this, '\0', sizeof(str_device_name_this));
    memset(str_device_name, '\0', sizeof(str_device_name));
    double j = 0.0;

    double highest_ldavg_one_val = 0.0;
    double highest_ldavg_five_val = 0.0;
    double highest_ldavg_15_val = 0.0;
    double val_sar = 0.0;

    // we should get highest value here for ldavg or others 
    if (strstr(item, "ldavg")) {
        for(int i=0; i<size; i++) {
            snprintf(str_hight, MAX_FILE_NAME_LENGTH, "%s ", get_sar_value_from_string(str_svg[i]));
            if (strstr(str_svg[i], "ldavg_one")) {
                if (highest_ldavg_one_val < atof(str_hight))
                    highest_ldavg_one_val = atof(str_hight);
            }
            if (strstr(str_svg[i], "ldavg_five")) {
                if (highest_ldavg_five_val < atof(str_hight))
                    highest_ldavg_five_val = atof(str_hight);
            }
            if (strstr(str_svg[i], "ldavg_15")) {
                if (highest_ldavg_15_val < atof(str_hight))
                    highest_ldavg_15_val = atof(str_hight);
            }
        }
    }

    double c_ldavg = 1.0;

    if (strcmp(item, "ldavg_15") == 0) {
        if ((highest_ldavg_one_val <= 0.125) && (highest_ldavg_five_val <= 0.125) && (highest_ldavg_15_val <= 0.125))
            c_ldavg = 800.0;
        else if ((highest_ldavg_one_val <= 0.25) && (highest_ldavg_five_val <= 0.25) && (highest_ldavg_15_val <= 0.25))
            c_ldavg = 400.0;
        else if ((highest_ldavg_one_val <= 0.5) && (highest_ldavg_five_val <= 0.5) && (highest_ldavg_15_val <= 0.5))
            c_ldavg = 200.0;
        else if ((highest_ldavg_one_val <= 1.0) && (highest_ldavg_five_val <= 1.0) && (highest_ldavg_15_val <= 1.0))
            c_ldavg = 100.0;
        else if ((highest_ldavg_one_val <= 2.0) && (highest_ldavg_five_val <= 2.0) && (highest_ldavg_15_val <= 2.0))
            c_ldavg = 50.0;
        else if ((highest_ldavg_one_val <= 5.0) && (highest_ldavg_five_val <= 5.0) && (highest_ldavg_15_val <= 5.0))
            c_ldavg = 20.0;
        else if ((highest_ldavg_one_val <= 10.0) && (highest_ldavg_five_val <= 10.0) && (highest_ldavg_15_val <= 10.0))
            c_ldavg = 10.0;
        else if ((highest_ldavg_one_val <= 20.0) && (highest_ldavg_five_val <= 20.0) && (highest_ldavg_15_val <= 20.0))
            c_ldavg = 5.0;
        else if ((highest_ldavg_one_val <= 40.0) && (highest_ldavg_five_val <= 40.0) && (highest_ldavg_15_val <= 40.0))
            c_ldavg = 2.5;
        else if ((highest_ldavg_one_val <= 80.0) && (highest_ldavg_five_val <= 80.0) && (highest_ldavg_15_val <= 80.0))
            c_ldavg = 1.25;
    }

    for(int i=0; i<size; i++) {
        // Here we set only 4 devices in this version.
        if ((strstr(str_svg[i], "CPU All")) || (strstr(str_svg[i], "used")) || (strstr(str_svg[i], "ldavg")) ||
            ((strstr(str_svg[i], "util")) && (utility <= 4))) {
            width = width + horizontal_notch;
            snprintf(str_horizontal_notch, MAX_FILE_NAME_LENGTH, "%f ", width);
            strncat(str_svg_draw, str_horizontal_notch, 200000 - 1);
            if (strstr(item, "ldavg")) {
                val_sar = atof(get_sar_value_from_string(str_svg[i]));
                val_sar = 110 - (val_sar * c_ldavg);
                snprintf(str_hight, MAX_FILE_NAME_LENGTH, "%f ", val_sar);
            } else {
                snprintf(str_hight, MAX_FILE_NAME_LENGTH, "%s ", get_sar_value_from_string(str_svg[i]));
            }
            snprintf(str_date, MAX_FILE_NAME_LENGTH, "%s ", get_date_from_string(str_svg[i]));
            snprintf(str_date_only_pre, MAX_FILE_NAME_LENGTH, "%s ", terminate_string(str_date, 2, ","));
            snprintf(str_date_only, MAX_FILE_NAME_LENGTH, "%s ", terminate_string(str_date, 1, ","));
            snprintf(str_time_only, MAX_FILE_NAME_LENGTH, "%s ", get_str_from_string(str_date_only_pre, 1, ","));
            strncat(str_svg_draw, str_hight, 200000 - 1);
            // block device utility starts from value 1
            if ((strcmp(item, "cpu_usr") == 0) || (strcmp(item, "memory_memused") == 0) || (strcmp(item, "ldavg_one") == 0) ||
                ((strcmp(item, "block_device_util") == 0) && (utility == 1))) {
                if (j == 0.0) {
                    file_write_svg(item, str_svg_draw, 0, width, fp_w); 
                    // start date and time
                    file_write_date_svg(item, str_date_only, 0, width, "start", fp_w); 
                    // percentage string 
                    if (strcmp(item, "ldavg_one") != 0) {
                        fprintf(fp_w, "%s\n", "  <text x=\"0\" y=\"10\">100</text>");
                        fprintf(fp_w, "%s\n", "  <text x=\"00\" y=\"60\">50</text>");
                        fprintf(fp_w, "%s\n", "  <text x=\"0\" y=\"110\">0</text>");
                    }
                    file_write_time_svg(item, str_time_only, 0, width, "start", fp_w); 
                }
            }
            j = j + 1.0;
        }           
        // absolute string 
        if ((strcmp(item, "ldavg_15") == 0) && (i == 0)) {
            fprintf(fp_w, "%s\n", "<g font-family=\"sans-serif\" fill=\"black\" font-size=\"10\">");
            if (c_ldavg == 800.0) {
                fprintf(fp_w, "%s\n", "  <text x=\"0\" y=\"10\">0.125</text>");
                fprintf(fp_w, "%s\n", "  <text x=\"00\" y=\"60\">0.0625</text>");
                fprintf(fp_w, "%s\n", "  <text x=\"0\" y=\"110\">0</text>");
            } else if (c_ldavg == 400.0) {
                fprintf(fp_w, "%s\n", "  <text x=\"0\" y=\"10\">0.25</text>");
                fprintf(fp_w, "%s\n", "  <text x=\"00\" y=\"60\">0.125</text>");
                fprintf(fp_w, "%s\n", "  <text x=\"0\" y=\"110\">0</text>");
            } else if (c_ldavg == 200.0) {
                fprintf(fp_w, "%s\n", "  <text x=\"0\" y=\"10\">0.5</text>");
                fprintf(fp_w, "%s\n", "  <text x=\"00\" y=\"60\">0.25</text>");
                fprintf(fp_w, "%s\n", "  <text x=\"0\" y=\"110\">0</text>");
            } else if (c_ldavg == 100.0) {
                fprintf(fp_w, "%s\n", "  <text x=\"0\" y=\"10\">1</text>");
                fprintf(fp_w, "%s\n", "  <text x=\"00\" y=\"60\">0.5</text>");
                fprintf(fp_w, "%s\n", "  <text x=\"0\" y=\"110\">0</text>");
            } else if (c_ldavg == 50.0) {
                fprintf(fp_w, "%s\n", "  <text x=\"0\" y=\"10\">2</text>");
                fprintf(fp_w, "%s\n", "  <text x=\"00\" y=\"60\">1</text>");
                fprintf(fp_w, "%s\n", "  <text x=\"0\" y=\"110\">0</text>");
            } else if (c_ldavg == 20.0) {
                fprintf(fp_w, "%s\n", "  <text x=\"0\" y=\"10\">5</text>");
                fprintf(fp_w, "%s\n", "  <text x=\"00\" y=\"60\">2.5</text>");
                fprintf(fp_w, "%s\n", "  <text x=\"0\" y=\"110\">0</text>");
            } else if (c_ldavg == 10.0) {
                fprintf(fp_w, "%s\n", "  <text x=\"0\" y=\"10\">10</text>");
                fprintf(fp_w, "%s\n", "  <text x=\"00\" y=\"60\">5</text>");
                fprintf(fp_w, "%s\n", "  <text x=\"0\" y=\"110\">0</text>");
            } else if (c_ldavg == 5.0) {
                fprintf(fp_w, "%s\n", "  <text x=\"0\" y=\"10\">20</text>");
                fprintf(fp_w, "%s\n", "  <text x=\"00\" y=\"60\">10</text>");
                fprintf(fp_w, "%s\n", "  <text x=\"0\" y=\"110\">0</text>");
            } else if (c_ldavg == 2.5) {
                fprintf(fp_w, "%s\n", "  <text x=\"0\" y=\"10\">40</text>");
                fprintf(fp_w, "%s\n", "  <text x=\"00\" y=\"60\">20</text>");
                fprintf(fp_w, "%s\n", "  <text x=\"0\" y=\"110\">0</text>");
            } else if (c_ldavg == 1.25) {
                fprintf(fp_w, "%s\n", "  <text x=\"0\" y=\"10\">80</text>");
                fprintf(fp_w, "%s\n", "  <text x=\"00\" y=\"60\">40</text>");
                fprintf(fp_w, "%s\n", "  <text x=\"0\" y=\"110\">0</text>");
            } else {
                fprintf(fp_w, "%s\n", "  <text x=\"0\" y=\"10\">100</text>");
                fprintf(fp_w, "%s\n", "  <text x=\"00\" y=\"60\">50</text>");
                fprintf(fp_w, "%s\n", "  <text x=\"0\" y=\"110\">0</text>");
            }
            fprintf(fp_w, "%s\n", "</g>");
        }
        // end date and time
        // We deduce 2 because last device name is 'ignore'.
        if (i == size - 2) {
            if (((strstr(str_svg[i], "util")) && (utility == 1)) ||
                (! strstr(str_svg[i], "util"))) {
                file_write_date_svg(item, str_date_only, 0, width, "end", fp_w); 
                file_write_time_svg(item, str_time_only, 0, width, "end", fp_w); 
            }
        }
    }
    strncat(str_svg_draw, "\"/>", 200000 - 1);
    fprintf(fp_w, "%s\n", str_svg_draw);
    if (strcmp(item, "cpu_idle") == 0) {
        fprintf(fp_w, "%s\n", "<g font-family=\"sans-serif\" fill=\"black\" font-size=\"10\">");
        fprintf(fp_w, "%s\n", "  <text x=\"10\" y=\"145\" fill=\"green\">cpu_usr</text>");
        fprintf(fp_w, "%s\n", "  <text x=\"10\" y=\"155\" fill=\"blue\">cpu_sys</text>");
        fprintf(fp_w, "%s\n", "  <text x=\"60\" y=\"145\" fill=\"red\">cpu_iowait</text>");
        fprintf(fp_w, "%s\n", "  <text x=\"60\" y=\"155\" fill=\"orange\">cpu_idle</text>");
        write_linux_line_to_file(&line_all_obj, " CPU All (%)", fp_w);
        fprintf(fp_w, "%s\n", "  <text x=\"900\" y=\"155\">Powered by saj.</text>");
        fprintf(fp_w, "%s\n", "</g>");
        fprintf(fp_w, "%s\n", "</svg>");
    } else if (strcmp(item, "memory_swpused") == 0) {
        fprintf(fp_w, "%s\n", "<g font-family=\"sans-serif\" fill=\"black\" font-size=\"10\">");
        fprintf(fp_w, "%s\n", "  <text x=\"10\" y=\"145\" fill=\"green\">memory_memused</text>");
        fprintf(fp_w, "%s\n", "  <text x=\"10\" y=\"155\" fill=\"red\">memory_swpused</text>");
        write_linux_line_to_file(&line_all_obj, " Memory (%)", fp_w);
        fprintf(fp_w, "%s\n", "  <text x=\"900\" y=\"155\">Powered by saj.</text>");
        fprintf(fp_w, "%s\n", "</g>");
        fprintf(fp_w, "%s\n", "</svg>");
    } else if (strcmp(item, "ldavg_15") == 0) {
        fprintf(fp_w, "%s\n", "<g font-family=\"sans-serif\" fill=\"black\" font-size=\"10\">");
        fprintf(fp_w, "%s\n", "  <text x=\"10\" y=\"145\" fill=\"blue\">ldavg_one</text>");
        fprintf(fp_w, "%s\n", "  <text x=\"10\" y=\"155\" fill=\"orange\">ldavg_five</text>");
        fprintf(fp_w, "%s\n", "  <text x=\"60\" y=\"145\" fill=\"red\">ldavg_15</text>");
        write_linux_line_to_file(&line_all_obj, " Load Average", fp_w);
        fprintf(fp_w, "%s\n", "  <text x=\"900\" y=\"155\">Powered by saj.</text>");
        fprintf(fp_w, "%s\n", "</g>");
        fprintf(fp_w, "%s\n", "</svg>");
    } else if (strcmp(item, "block_device_util") == 0) {
        if (utility == 1) {
            fprintf(fp_w, "%s\n", "<g font-family=\"sans-serif\" fill=\"black\" font-size=\"10\">");
            strncpy(str_device_name, "  <text x=\"10\" y=\"145\" fill=\"green\">", 43);
        } else if (utility == 2) {
            strncpy(str_device_name, "  <text x=\"10\" y=\"155\" fill=\"blue\">", 43);
        } else if (utility == 3) {
            strncpy(str_device_name, "  <text x=\"70\" y=\"145\" fill=\"orange\">", 43);
        // Here we set only 4 devices in this version.
        } else if (utility == 4) {
            strncpy(str_device_name, "  <text x=\"70\" y=\"155\" fill=\"mediumvioletred\">", 52);
        }
        snprintf(str_device_name_this, 100, "%s ", get_block_device_names(utility));
        strncat(str_device_name, str_device_name_this, 100);
        strncat(str_device_name, "</text>", MAX_FILE_NAME_LENGTH - 1);
        fprintf(fp_w, "%s\n", str_device_name);
        // Here we set only 4 devices in this version.
        // We deduce 1 because last device name is 'ignore'.
        if ((block_devices -1 == utility) || (utility == 4)){
            write_linux_line_to_file(&line_all_obj, " Disk util up to 4 device names (%)", fp_w);
            fprintf(fp_w, "%s\n", "  <text x=\"900\" y=\"155\">Powered by saj.</text>");
            fprintf(fp_w, "%s\n", "</g>");
            fprintf(fp_w, "%s\n", "</svg>");
        }
    }

    return 0;
}

int create_html_file(char* file_name, FILE* fp_w)
{
    char* file_name_base;
    file_name_base = get_str_from_string(file_name, 3, "/");
    char str_file_name_cpu[MAX_FILE_NAME_LENGTH];
    char str_file_name_memory[MAX_FILE_NAME_LENGTH];
    char str_file_name_disk[MAX_FILE_NAME_LENGTH];
    char str_file_name_ldavg[MAX_FILE_NAME_LENGTH];
    memset(str_file_name_cpu, '\0', sizeof(str_file_name_cpu));
    memset(str_file_name_memory, '\0', sizeof(str_file_name_memory));
    memset(str_file_name_disk, '\0', sizeof(str_file_name_disk));
    memset(str_file_name_ldavg, '\0', sizeof(str_file_name_ldavg));
    snprintf(str_file_name_cpu, MAX_FILE_NAME_LENGTH, "%s%s%s", "<img src=", file_name_base, "-cpu-.svg />");
    snprintf(str_file_name_memory, MAX_FILE_NAME_LENGTH, "%s%s%s", "<img src=", file_name_base, "-memory-.svg />");
    snprintf(str_file_name_disk, MAX_FILE_NAME_LENGTH, "%s%s%s", "<img src=", file_name_base, "-disk-.svg />");
    snprintf(str_file_name_ldavg, MAX_FILE_NAME_LENGTH, "%s%s%s", "<img src=", file_name_base, "-ldavg-.svg />");
    fprintf(fp_w, "%s\n", "<html>");
    fprintf(fp_w, "%s\n", "<body>");
    fprintf(fp_w, "%s\n", str_file_name_cpu);
    fprintf(fp_w, "%s\n", str_file_name_memory);
    fprintf(fp_w, "%s\n", str_file_name_disk);
    fprintf(fp_w, "%s\n", str_file_name_ldavg);
    fprintf(fp_w, "%s\n", "<br />");
    fprintf(fp_w, "%s\n", "</body>");
    fprintf(fp_w, "%s\n", "</html>");
    return 0;
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
