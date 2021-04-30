/*
 *  member_data.h - object definitions
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
#include "cfg.h" 
#include "../common/common_member_data.h" 

#ifndef SOSREPORT_ANALYZER_MEMBER_DATA_H
#define SOSREPORT_ANALYZER_MEMBER_DATA_H

int init_member(volatile node_m **obj);
node_m *allocate_mem_to_one_node_m(void);
/*
int insert_node_m_top_of_the_list(volatile node_m **obj, char *member,
    int mcinfo, bool read_dir, bool dir_recursive_read, bool dir_root_read,
     char *sub_title, int item_max);
*/
void set_member(volatile node_m *obj, char *member, int mcinfo, bool read_dir,
    bool dir_recursive_read, bool dir_root_read, char *sub_title,
        volatile node_m *obj_next, int item_max);
int append_member(volatile node_m **obj, char *member, int mcinfo, bool read_dir,
    bool dir_recursive_read, bool dir_root_read, char *sub_title, int item_max );

/*
 * Function Name: search_member ()
 *
 * This function search given string from the node and if found, set string to char array
 *
 *  Caller :
 *
 *  Calls : none
 *
 */
char *search_member(node_m **obj, const char *member, char result[MAX_MEMBER_LENGTH]);

int delete_obj_m(node_m **obj);
int clear_member(volatile node_m **obj);

#endif /* SOSREPORT_ALANYZER_MEMBER_DATA_H */
