# Makefile.am - use automake to generate Makefile.in

AM_CXFLAGS = $(INIT_CFLAGS)
AM_CPPFLAGS = -I$(top_srcdir)/libsaj-sar-analyzer -I$(top_srcdir)/libsaj-sosreport-analyzer
AM_LDFLAGS = -L$(top_srcdir)/libsaj-sar-analyzer -Wl,-rpath,/usr/local/lib -L$(top_srcdir)/libsaj-sosreport-analyzer -Wl,-rpath,/usr/local/lib

all:
	qmake-qt4
	make

clean-local:

