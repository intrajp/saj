# configure.ac - process this file with autoconf to produce configure
#
# Copyright (C) 2019 Shintaro Fujiwara 
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
# 02110-1301 USA

AC_PREREQ([2.69])
AC_COPYRIGHT(
[Copyright (C) 2019 Shintaro Fujiwara 

This configure script is derived from configure.ac which is free software;
you can redistribute it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version. See the
configure.ac file for more details.])

# initialize and set version and bugreport address
AC_INIT([saj], [0.4.1], [shintaro.fujiwara@gmail.com])
RELEASE_MONTH="Jul 2021"
AC_SUBST(RELEASE_MONTH)
AC_CONFIG_MACRO_DIR([m4])

# display notice and initialize automake
AC_MSG_NOTICE([configuring AC_PACKAGE_TARNAME AC_PACKAGE_VERSION])
#AM_INIT_AUTOMAKE([1.11.2 --warnings=all])
AM_INIT_AUTOMAKE([subdir-objects])
AC_CONFIG_SRCDIR([src/saj.c])

# create a config.h file (Automake will add -DHAVE_CONFIG_H)
#AC_CONFIG_HEADERS([config.h])

# check locale
LOCALE_THIS=`locale | grep LANG | cut -d= -f2`

# conditional behaivor
AM_CONDITIONAL(LANG_JP, test `locale | grep LANG | cut -d= -f2 | cut -d. -f1` = "ja_JP" )

# check for programs
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL
AM_PROG_CC_C_O
AC_USE_SYSTEM_EXTENSIONS
AC_PROG_LN_S
AM_PROG_AR

LT_INIT

AC_ENABLE_SHARED
AC_DISABLE_STATIC
AC_PROG_LIBTOOL(libtool)

# check for debugging options
AC_ARG_ENABLE(debug,
              AS_HELP_STRING([--enable-debug],
                             [enable extensive debugging and logging]),
              [if test "x$enableval" != "xno" ; then CFLAGS="-g -DDEBUG $CFLAGS" ; fi])

# check for extra compiler warnings
DESIRED_CFLAGS="-Wall -std=gnu99 -fstack-protector"
AC_ARG_ENABLE(warnings,
              AS_HELP_STRING([--enable-warnings],
                             [enable extra compiler warnings (gcc)]),
              [if test "x$enableval" != "no"
               then
                 CFLAGS="$CFLAGS -pedantic -Wall -Wshadow -Wpointer-arith -Wcast-align -Wstrict-prototypes -Wmissing-prototypes -Wnested-externs -Waggregate-return -Wmissing-declarations -Wunused -Wformat=2 -Wswitch-default -Wswitch-enum -Wfloat-equal -Wbad-function-cast -Wredundant-decls -std=gnu99"
                 DESIRED_CFLAGS="$DESIRED_CFLAGS -Wextra -Wdeclaration-after-statement -Werror-implicit-function-declaration -Werror=implicit"
               fi])
test_gcc_flag() {
    AC_LANG_CONFTEST([AC_LANG_PROGRAM()])
    $CC -c conftest.c $CFLAGS $@ > /dev/null 2> /dev/null
    ret=$?
    rm -f conftest.o
    return $ret
}
for flag in $DESIRED_CFLAGS
do
    AC_MSG_CHECKING([whether $CC accepts $flag])
    if test_gcc_flag $flag
    then
        CFLAGS="$CFLAGS $flag"
        AC_MSG_RESULT([yes])
    else
        AC_MSG_RESULT([no])
    fi
done

# checks for availability of header files

AC_CHECK_HEADERS([stdbool.h stdlib.h stdio.h string.h time.h dirent.h errno.h ctype.h math.h sys/stat.h fcntl.h limits.h getopt.h])

# other general checks
AC_C_INLINE
AC_C_CONST

# checks for availability of common functions
AC_CHECK_FUNCS([sigaction snprintf])
AC_SEARCH_LIBS(socket, socket)
AC_CHECK_FUNCS([strcasecmp strncasecmp strchr strcspn strspn strtol strtoul strtoull strndup])
AC_CHECK_FUNCS([malloc realloc atexit])
AC_FUNC_FORK
AC_CHECK_FUNCS(__assert_fail)
AC_SEARCH_LIBS(clock_gettime, rt)
AC_CHECK_FUNCS([setusershell getusershell endusershell getgrouplist])
AC_CHECK_DECLS([setusershell, getusershell, endusershell])

# check the name of the saj configuration file
AC_ARG_WITH(saj-conf-file,
            AS_HELP_STRING([--with-saj-conf-file=PATH],
                           [path to saj configuration file @<:@/etc/saj.conf@:>@]),
            [ SAJ_CONF_PATH="$with_saj_conf_file" ],
            [ SAJ_CONF_PATH="/etc/saj.conf" ])
AC_DEFINE_UNQUOTED(SAJ_CONF_PATH, "$SAJ_CONF_PATH", [Path to saj configuration file.])
AC_SUBST(SAJ_CONF_PATH)

# check the name of the saj-mcinfo configuration file
AC_ARG_WITH(saj-mcinfo-conf-file,
            AS_HELP_STRING([--with-saj-mcinfo-conf-file=PATH],
                           [path to saj-mcinfo configuration file @<:@/etc/saj-mcinfo.conf@:>@]),
            [ SAJ_MCINFO_CONF_PATH="$with_saj_mcinfo_conf_file" ],
            [ SAJ_MCINFO_CONF_PATH="/etc/saj-mcinfo.conf" ])
AC_DEFINE_UNQUOTED(SAJ_MCINFO_CONF_PATH, "$SAJ_MCINFO_CONF_PATH", [Path to saj-mcinfo configuration file.])
AC_SUBST(SAJ_MCINFO_CONF_PATH)

# check the name of the data file
AC_ARG_WITH(saj-data-file,
            AS_HELP_STRING([--with-saj-data-file=PATH],
                           [path to saj data file @<:@/usr/share/saj/saj.conf.example@:>@]),
            [ SAJ_DATA_PATH="$with_saj_data_file" ],
            [ SAJ_DATA_PATH="/usr/share/saj" ])
AC_DEFINE_UNQUOTED(SAJ_DATA_PATH, "$SAJ_DATA_PATH", [Path to saj data file.])
AC_SUBST(SAJ_DATA_PATH)

# check the name of the include/saj file
AC_ARG_WITH(saj-include-file,
            AS_HELP_STRING([--with-saj-include-file=PATH],
                           [path to saj include file @<:@/usr/local/include/saj/cfg.h@:>@]),
            [ SAJ_INCLUDE_PATH="$with_saj_include_file" ],
            [ SAJ_INCLUDE_PATH="/usr/local/include/saj" ])
AC_DEFINE_UNQUOTED(SAJ_INCLUDE_PATH, "$SAJ_INCLUDE_PATH", [Path to saj include file.])
AC_SUBST(SAJ_INCLUDE_PATH)

# check the name of the libsaj-sosreport-analyzer file
AC_ARG_WITH(saj-sosreport-analyzer-lib-file,
            AS_HELP_STRING([--with-saj-sosreport-analyzer-lib-file=PATH],
                           [path to saj-sosreport-analyzer lib file @<:@/usr/local/lib/libsaj-sosreport-analyzer.so@:>@]),
            [ SAJ_SOSREPORT_ANALYZER_LIB_PATH="$with_saj_sosreport_analyzer_lib_file" ],
            [ SAJ_SOSREPORT_ANALYZER_LIB_PATH="/usr/local/lib" ])
AC_DEFINE_UNQUOTED(SAJ_SOSREPORT_ANALYZER_LIB_PATH, "$SAJ_SOSREPORT_ANALYZER_LIB_PATH", [Path to saj-sosreport-analyzer lib file.])
AC_SUBST(SAJ_SOSREPORT_ANALYZER_LIB_PATH)

# check the name of the libsaj-sar-analyzer file
AC_ARG_WITH(saj-sar-analyzerd-lib-file,
            AS_HELP_STRING([--with-saj-sar-analyzer-lib-file=PATH],
                           [path to saj-sar-analyzer lib file @<:@/usr/local/lib/libsaj-sar-analyzer.so@:>@]),
            [ SAJ_SAR_ANALYZER_LIB_PATH="$with_saj_sar_analyzer_lib_file" ],
            [ SAJ_SAR_ANALYZER_LIB_PATH="/usr/local/lib" ])
AC_DEFINE_UNQUOTED(SAJ_SAR_ANALYZER_LIB_PATH, "$SAJ_SAR_ANALYZER_LIB_PATH", [Path to saj-sar-analyzer lib file.])
AC_SUBST(SAJ_SAR_ANALYZER_LIB_PATH)


AC_CONFIG_FILES([
  Makefile
  libsaj-sosreport-analyzer/Makefile
  libsaj-sar-analyzer/Makefile
  src/Makefile
])
AC_OUTPUT
