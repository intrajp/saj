/*
 *  cfg.c - configuration functions 
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

#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> /* for is_space */
#include <dirent.h>
#include <stddef.h>
#include <errno.h>
#include <pwd.h>
#include "common.h"
#include "cfg.h"

/* should be set to NULL, this will be checked in cfg_init()
 *
 * This function works like strtok() except that the original string is
 *  not modified and a pointer within str to where the next token begins
 *  is returned (this can be used to pass to the function on the next
 *  iteration). If no more tokens are found or the token will not fit in
 *  the buffer, NULL is returned. 
 */
static char* __get_token(char** line, char* buf, size_t buflen)
{
    size_t len;

    if ((line == NULL) || (*line == NULL) || (**line == '\0') || (buf == NULL))
        return NULL;

    /* find the beginning and length of the token */
    *line += strspn (*line, TOKEN_DELIM);
    len = strcspn (*line, TOKEN_DELIM);

    /* check if there is a token */
    if (len == 0) {
        *line = NULL ;
        return NULL;
    }

    /* limit the token length */
    if (len >= buflen)
        len = buflen - 1;

    /* copy the token */
    strncpy(buf, *line, len);
    buf[len] = '\0';

    /* skip to the next token */
    *line += len;
    *line += strspn(*line, TOKEN_DELIM);

    /* return the token ( should be member name )*/
    return buf;
}

/*
 * This function checks item string length in the conf file 
 */
static int __check_item_string_length(const char* token, const char* member)
{
    size_t strlen_token = strlen(token);
    if (strlen_token > MAX_ITEM_STRING_LENGTH) {
        fprintf(stderr, "item '%s' for '%s' is too long (%ld)\n", token, member, strlen_token);
        return 1;
    }
    if (strlen_token < MIN_ITEM_STRING_LENGTH) {
        fprintf(stderr, "item '%s' for '%s' is too short (%ld)\n", token, member, strlen_token);
        return 1;
    }
    return 0;
}

/*
 * This function sets items to struct which are read from config file to the member object.
 */
static int __set_token_to_member_obj_item_arr(const char* member, char* line, int mcinfo, int sar_only, FILE* fp)
{
    const char s[ 8 ] = " \t\n\r"; /* this is the delimiter */
    char* token = NULL;
    int x = 0;

    /* get the first token */
    volatile  node_m* ptr_tmp_m = member_obj;
    while (ptr_tmp_m != NULL) {
        if ((strcmp((const char*)ptr_tmp_m->_member, (const char*)member) == 0) && (ptr_tmp_m->mcinfo == mcinfo)) {
            token = strtok(line, s);
            if (strcmp(token, "skip") == 0)
                return 1;
            if (__check_item_string_length(token, member) == 1) {
                free_sosreport_analyzer_obj(sar_only);
                fclose(fp);
                exit(EXIT_FAILURE);
            }
            strncpy((char*)ptr_tmp_m->item_names.item_name [x], token, MAX_ITEM_STRINGS);
            ptr_tmp_m->item_num = x + 1;
            /* get the next token ... */
            while (token != NULL) {
                if (ptr_tmp_m->item_num > ptr_tmp_m->item_max) {
                    fprintf(stderr, "In member: '%s', item number exceeds item_max (%d) in '%s'.\n",member, ptr_tmp_m->item_max, token);
                    fprintf(stderr, "Remove the item string '%s' of member '%s' in conf file.\n", token,member);
                    free_sosreport_analyzer_obj(sar_only);
                    fclose(fp);
                    exit(EXIT_FAILURE);
                }
                token = strtok(NULL, s);
                if (token == NULL)
                    return 0;
                x++;
                strncpy((char*)ptr_tmp_m->item_names.item_name [x], token, MAX_ITEM_STRINGS);
                ptr_tmp_m->item_num = x + 1;
            }
        }
        ptr_tmp_m = ptr_tmp_m->next;
    }
    return 0;
}

/*
 * This function sets items which are read from config file to the member object.
 */
static int __set_items_to_member_obj(const char* keyword, char* line, int mcinfo, int sar_only, FILE* fp)
{
    /* Maybe make this to a function? */
    volatile node_m* ptr_tmp_m = member_obj;
    while (ptr_tmp_m != NULL) {
        /* line is the items, so here we set those items to member object */
        if ((ptr_tmp_m->mcinfo == mcinfo) && (strcmp((const char*)ptr_tmp_m->_member, keyword) == 0)) {
            if (__set_token_to_member_obj_item_arr(keyword, line, mcinfo, sar_only, fp) == 1)
                return 1;
            return 0;
        }
        ptr_tmp_m = ptr_tmp_m->next;
    }
    return 1;
}

/*
 * This function appends member strings to header object.
 */
static int __append_member_strings_to_header_obj(int mcinfo)
{
    /* appending member strigs with their items which had been set by config file */
    /* the order of these depends on member object, so member object should be consistent */
    char str_tmp[MAX_FILE_NAME_LENGTH]; 
    char str_tmp_items[MAX_FILE_NAME_LENGTH]; 
    memset(str_tmp, '\0', MAX_FILE_NAME_LENGTH); 
    memset(str_tmp_items, '\0', MAX_FILE_NAME_LENGTH); 

    /* No worry, member_obj is a global object */
    volatile node_m* ptr_tmp_m = member_obj;

    while (ptr_tmp_m != NULL) {
        if ((mcinfo == 1 && ptr_tmp_m->mcinfo == 0) || (mcinfo == 0 && ptr_tmp_m->mcinfo == 1)) {
            ptr_tmp_m = ptr_tmp_m->next;
            continue;
        } else {
            if (strcmp((const char*)ptr_tmp_m->sub_title, "") != 0 )
                append_list( &sos_header_obj, (char*)ptr_tmp_m->sub_title);
            /* we should add all the array elements of items here */
            memset(str_tmp, '\0', MAX_FILE_NAME_LENGTH); 
            memset(str_tmp_items, '\0', MAX_FILE_NAME_LENGTH); 
            snprintf((char*)str_tmp, strlen ((const char*)ptr_tmp_m->_member) + 2, "%s=", ptr_tmp_m->_member);
            for (int i = 0; i < ptr_tmp_m->item_num; i++)
            {
                if (i > 0)
                    strcat(str_tmp_items," ");
                strcat(str_tmp_items, (const char*)ptr_tmp_m->item_names.item_name[i]);
            }
            strcat (str_tmp, str_tmp_items);
            append_list (&sos_header_obj, str_tmp);
        }
        ptr_tmp_m = ptr_tmp_m->next;
    }
    append_list(&sos_header_obj, "--------");
    return 0;
}

int cfg_read(const char* file_name, int mcinfo, int sar_only)
{
    FILE* fp;
    int fd, rc, lnr = 0;
    struct stat st;
    char linebuf[MAX_LINE_LENGTH];
    char* line;
    char keyword[1024];
    int i;
    
    /* Here, we allow user's config file to be opend in the proper directory */
    const char* homedir;
    if ((homedir = getenv("HOME")) == NULL) {
        homedir = getpwuid(getuid())->pw_dir;
    }
    char config_dir_name_in_home[MAX_FILE_NAME_LENGTH];
    char config_file_name_in_home[MAX_FILE_NAME_LENGTH];
    snprintf(config_dir_name_in_home, MAX_FILE_NAME_LENGTH, "%s/.saj", homedir);
    if (mcinfo == 0)
        snprintf(config_file_name_in_home, MAX_FILE_NAME_LENGTH, "%s/.saj/saj.conf", homedir);
    else if (mcinfo == 1)
        snprintf(config_file_name_in_home, MAX_FILE_NAME_LENGTH, "%s/.saj/saj-mcinfo.conf", homedir);
    
    if (check_result_dir(config_dir_name_in_home, sar_only, 0) != 0) {
        fprintf(stderr, "can't open dir %s (%s)\n", config_dir_name_in_home, strerror(errno));
        free_sosreport_analyzer_obj(sar_only);
        exit(EXIT_FAILURE);
    }
    /* open config file */
    /* We first try to open config file in /etc */
    rc = open(file_name, O_NOFOLLOW | O_RDONLY);
    if (rc < 0) {
        if (errno != ENOENT) {
            fprintf(stderr, "Error - opening %s (%s)\n",
                file_name, strerror (errno));
            fprintf(stderr, "Config file %s doesn't exist.\n", file_name);
            free_sosreport_analyzer_obj(sar_only);
            exit(EXIT_FAILURE);
        }
    }
    /* Next, we try to open config file in HOME/.saj */
    rc = open(config_file_name_in_home, O_NOFOLLOW | O_RDONLY);
    /* If above fails, copy config file from /etc to HOME/saj */
    if (rc < 0) {
        char ch;
        FILE* source;
        FILE* target;
        if (mcinfo == 0)
            file_name = "/usr/share/saj/saj.conf.example";
        if (mcinfo == 1)
            file_name = "/usr/share/saj/saj-mcinfo.conf.example";
        source = fopen(file_name, "r");
        target = fopen(config_file_name_in_home, "w");
        while ((ch = fgetc(source)) != EOF)
           fputc(ch, target);
        printf("\nFile copied successfully.\n");
        fclose(source);
        fclose(target);

    }
    /* Now we are done with this, so replace file name variable for the future use.*/
    file_name = config_file_name_in_home;
    /* Again we open the config file with new pointer */
    rc = open(file_name, O_NOFOLLOW | O_RDONLY);
    if (rc < 0) {
        if (errno != ENOENT) {
            fprintf(stderr, "Error --- opening %s (%s)\n",
                file_name, strerror (errno));
            printf("Config file %s doesn't exist.\n", file_name);
            free_sosreport_analyzer_obj(sar_only);
            exit(EXIT_FAILURE);
        }
    }

    fd = rc;

    /* check the file's permissions: owned by root, not world writable,
     * not symlink.
     */
    char str_tmp2[ MAX_FILE_NAME_LENGTH ]; 
    memset(str_tmp2, '\0', sizeof(str_tmp2)); 
    snprintf(str_tmp2, MAX_LINE_LENGTH, "Config file %s opened for parsing",file_name);
    append_list(&sos_header_obj, str_tmp2);
    append_list(&sos_header_obj, "--------");

    if (fstat(fd, &st) < 0) {
        fprintf(stderr, "Error fstat'ing %s (%s)\n", file_name, strerror (errno)); 
        if (close (fd) == -1)
            fprintf(stderr, "Error closing file pointer %d (%s)\n", (int)fd, strerror(errno)); 
        free_sosreport_analyzer_obj(sar_only);
        exit(EXIT_FAILURE);
    }
    /*
    if (st.st_uid != 0) {
        fprintf(stderr, "Error - %s isn't owned by root\n", file_name); 
        if (close(fd) == -1)
            fprintf(stderr, "Error closing file pointer %d (%s)\n", (int)fd, strerror(errno)); 
        free_sosreport_analyzer_obj(sar_only);
        close(fd);
        exit(EXIT_FAILURE);
    }
    */
    if ((st.st_mode & S_IWOTH) == S_IWOTH) {
        fprintf(stderr, "Error - %s is world writable", file_name);
        if (close(fd) == -1)
            fprintf(stderr, "Error closing file pointer %d (%s)\n", (int)fd, strerror(errno)); 
        free_sosreport_analyzer_obj(sar_only);
        close(fd);
        exit(EXIT_FAILURE);
    }
    /* using macro to check file*/
    if (!S_ISREG(st.st_mode)) {
        fprintf(stderr, "Error - %s is not a regular file", file_name);
        if (close (fd) == -1)
            fprintf(stderr, "Error closing file pointer %d (%s)\n", (int)fd, strerror(errno)); 
        free_sosreport_analyzer_obj(sar_only);
        close(fd);
        exit(EXIT_FAILURE);
    }
    /* open config file */
    if ((fp = fopen (file_name,"r")) == NULL) {
        fprintf(stderr, "can't open config file (%s): %s", file_name, strerror(errno));
        if (close(fd) == -1 )
            fprintf(stderr, "Error closing file pointer %d (%s)\n", (int)fd, strerror(errno)); 
        free_sosreport_analyzer_obj(sar_only);
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    /* read file and parse lines */
    while (fgets(linebuf, sizeof(linebuf), fp) != NULL) {
        lnr++;
        line = linebuf;
        /* strip newline */
        i = (int)strlen(line);
        if ((i <= 0) || (line [i - 1] != '\n'))
        {
            fprintf(stderr, "%s:%d: line too long or last line missing newline\n", file_name, lnr);
            if (close(fd) == -1)
                fprintf(stderr, "Error closing file pointer %d (%s)\n", (int)fd, strerror(errno)); 
            free_sosreport_analyzer_obj(sar_only);
            fclose(fp);
            exit (EXIT_FAILURE);
        }
        line[i - 1] = '\0';
        /* ignore comment lines */
        if (line[0] == '#')
            continue;
        /* strip trailing spaces */
        for (i--; (i > 0) && isspace(line [i - 1]); i--)
            line [i - 1] = '\0';

        /* get keyword from line and ignore empty lines */
        if (__get_token(&line, keyword, sizeof(keyword)) == NULL)
            continue;
        if (__set_items_to_member_obj(keyword, line, mcinfo, sar_only, fp) == 1)
            continue;
    }
    /* we're done reading file, close */
    fclose(fp);

    __append_member_strings_to_header_obj(mcinfo);

    return 0;
}

