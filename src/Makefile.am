# Makefile.am - use automake to generate Makefile.in

AM_CXFLAGS = $(INIT_CFLAGS)
AM_CPPFLAGS = -I$(top_srcdir)/libsaj-sar-analyzer -I$(top_srcdir)/libsaj-sosreport-analyzer
AM_LDFLAGS = -L$(top_srcdir)/libsaj-sar-analyzer -Wl,-rpath,/usr/local/lib -L$(top_srcdir)/libsaj-sosreport-analyzer -Wl,-rpath,/usr/local/lib

bin_PROGRAMS = cmp-saj saj
cmp_saj_SOURCES = cmp-saj.c
cmp_saj_LDADD = -lsaj-sosreport-analyzer -lsaj-sar-analyzer
saj_SOURCES = saj.c
saj_LDADD = -lsaj-sosreport-analyzer -lsaj-sar-analyzer


all:

clean-local:

