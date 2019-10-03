# Makefile.am - use automake to generate Makefile.in

lib_LTLIBRARIES = libsaj-sar-analyzer.la

if LANG_JP 
libsaj_sar_analyzer_la_SOURCES=common_jp.c make_report.c sar_analyzer_jp.c setter_getter.c
else
libsaj_sar_analyzer_la_SOURCES=common.c make_report.c sar_analyzer.c setter_getter.c
endif

libsaj_sar_analyzer_la_LDFLAGS = -version-info 0:1:0

all:

clean-local:

