/*
 *  cfg.h - configuration definition 
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

#ifndef SOSREPORT_ANALYZER__CFG_H
#define SOSREPORT_ANALYZER__CFG_H

#include "../common/global.h"
#include "../common/common_line_data.h"
#include "../common/common_member_data.h"

/* the maximum line length in the configuration file */
#define MAX_LINE_LENGTH    4096

/* the delimiters of tokens */
#define TOKEN_DELIM "="

/* This function reads config file. */
int cfg_read(const char* file_name, int mcinfo, int sar_only);

#endif /* SOSREPORT_ANALYZER__CFG_H */
