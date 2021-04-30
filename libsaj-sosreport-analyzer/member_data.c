/*
 * member_data.c - object functions 
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

#include "common.h"
#include "member_data.h"

int init_member (volatile node_m** obj)
{
    *obj = NULL;

    return 0;
}

static int __insert_node_m_top_of_the_list(volatile node_m** obj, char* member,
    int mcinfo, bool read_dir, bool dir_recursive_read, bool dir_root_read,
        char* sub_title, int item_max)
{
    /* setting current obj to the new obj */
    volatile node_m* obj_next = *obj;
    *obj = allocate_mem_to_one_node_m();
    /* setting current obj the the next pointer, this makes new object to the top of the list */
    set_member(*obj, member, mcinfo, read_dir, dir_recursive_read, dir_root_read,
        sub_title, obj_next, item_max);

    return 0;
}

node_m* allocate_mem_to_one_node_m (void)
{
    return(struct member_data*) calloc(1, sizeof(struct member_data));
}

void set_member(volatile node_m* obj, char* member, int mcinfo, bool read_dir,
    bool dir_recursive_read, bool dir_root_read, char* sub_title,
        volatile node_m* obj_next, int item_max)
{
    size_t len = 0;

    const char* test_member = "\0";
    len = strlen(member);
    if (len < 0)
    {
        fprintf(stderr, "can't set %s\n", member);
        exit(EXIT_FAILURE);
    }
    if (len > MAX_MEMBER_LENGTH)
        strncpy((char*)obj->_member, test_member, 1);
    else
        strncpy((char*)obj->_member, member, MAX_MEMBER_LENGTH - 1);

    const char* test_sub_title = "\0";
    len = strlen(sub_title);
    if (len < 0) {
        fprintf(stderr, "can't set %s\n", sub_title);
        exit(EXIT_FAILURE);
    }
    if (len > MAX_LINE_LENGTH)
        strncpy((char*)obj->sub_title, test_sub_title, 1);
    else
        strncpy((char*)obj->sub_title, sub_title, MAX_MEMBER_LENGTH - 1);

    obj->mcinfo = mcinfo;
    obj->read_dir = read_dir;
    obj->dir_recursive_read = dir_recursive_read;
    obj->dir_root_read = dir_root_read;
    obj->item_max = item_max;
    obj->next = (node_m *)obj_next;
    free((void*)obj_next);
}

int append_member(volatile node_m** obj, char* member, int mcinfo, bool read_dir,
    bool dir_recursive_read, bool dir_root_read, char* sub_title, int item_max)
{
    /* if no node_m found in the object, insert node_m in the very top of it */
    if (*obj == NULL) {
        __insert_node_m_top_of_the_list(obj, member, mcinfo, read_dir,
            dir_recursive_read, dir_root_read, sub_title, item_max);
    /* if some node_m exists in the object, find the very last of it and appending the new node_m */
    } else {
        volatile node_m* obj_new = *obj;
        while (obj_new->next != NULL)
            obj_new = obj_new->next;
        obj_new->next = allocate_mem_to_one_node_m();
        set_member(obj_new->next, member, mcinfo, read_dir, dir_recursive_read,
            dir_root_read, sub_title, NULL, item_max);
    }

    return 0;
}

int bubble_sort_object_m_by_the_string(node_m** obj,
    char* str_arr[MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR]) 
{
    
    node_m* ptr_tmp = *obj;
    char str_cmp_member[MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR][MAX_LINE_LENGTH];
    int i = 0;
    for (i = 0; i < MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR; i++)
        memset(str_cmp_member[i], '\0', sizeof(str_cmp_member[i])); 
    char *str_tmp;
    int obj_size = 0, j = 0, ii = 0;

    /* read from object and copy strings to an array */
    while (ptr_tmp != NULL) {
        str_arr[obj_size] = (char *) & (ptr_tmp->_member[0]); 
        obj_size++;
        ptr_tmp = ptr_tmp->next;
    }
    /* bubble sort the array */
    for (j= 0; j < obj_size; j++) {
        /* This makes largest item to the end of an array. */
        for (i = 0; i < obj_size - (1 + j); i++) {
            ii = i + 1;
            if (strcmp (str_arr[i], str_arr[ii]) > 0 ) {
                str_tmp = str_arr[i]; 
                str_arr[i] = str_arr[ii]; 
                str_arr[ii] = str_tmp; 
            }
        }
    }

    /* end bubble sort */
    return obj_size;
}

char* search_member(node_m** obj, const char* member, char result[MAX_MEMBER_LENGTH])
{
    node_m* ptr_tmp = *obj;
    char str_cmp_member[MAX_MEMBER_LENGTH];
    memset(str_cmp_member, '\0', MAX_MEMBER_LENGTH); 
    char str_cmp__member[MAX_MEMBER_LENGTH];
    memset(str_cmp__member, '\0', MAX_MEMBER_LENGTH); 
    strcpy(str_cmp_member, member);
    memset(result, '\0', MAX_MEMBER_LENGTH); 
    char* result_p = & (result[MAX_MEMBER_LENGTH]);

    const char s[8] = "="; /* this is the delimiter */

    while (ptr_tmp != NULL) {
        strcpy(str_cmp__member, (const char *)ptr_tmp->_member);

        char* token = NULL;
        token = strtok((char*)str_cmp__member, s);

        if ((strcmp(str_cmp__member, "") != 0) && (strstr(str_cmp_member, token) != NULL)) {
            strcpy(result, (const char*)ptr_tmp->_member);
            return(result_p);
        }
        ptr_tmp = ptr_tmp->next;
    }

    return result_p;
}

int delete_obj_m(node_m** obj)
{
    node_m* obj_new = (*obj)->next;
    free ((void*)*obj);
    *obj = obj_new;

    return 0;
}

int clear_member(volatile node_m** obj)
{
    while (*obj != NULL)
    {
        node_m* obj_new = (*obj)-> next;
        free ((void*)*obj);
        *obj = obj_new;
    }
    return 0;
}
