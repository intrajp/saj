/*
 *  make_report.h - make_report definitions
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

#ifndef SAJ_MAKE_REPORT_H
#define SAJ_MAKE_REPORT_H

/*
 * This function writes postscript header to postscript file.
 *
 */
int append_header_to_ps_objs(node** obj, FILE* fp_w);

/*
 * This function writes rectangular to postscript file.
 *
 */
int append_rectangular_to_ps_objs(node** obj, FILE* fp_w, const char* element);

/*
 * This function writes postscript labels to postscript file.
 *
 */
int append_labels_to_ps_obj(node** obj, FILE* fp_w, const char* item);

#endif /* SAJ_MAKE_REPORT_H */
