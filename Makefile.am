# Makefile.am - use automake to generate Makefile.in
#

SUBDIRS = libsaj-sar-analyzer libsaj-sosreport-analyzer src gui

SAJ_CONF_PATH = @SAJ_CONF_PATH@
SAJ_MCINFO_CONF_PATH = @SAJ_MCINFO_CONF_PATH@
SAJ_DATA_PATH = @SAJ_DATA_PATH@
SAJ_INCLUDE_PATH = @SAJ_INCLUDE_PATH@
SAJ_SOSREPORT_ANALYZER_LIB_PATH = @SAJ_SOSREPORT_ANALYZER_LIB_PATH@
SAJ_SAR_ANALYZER_LIB_PATH = @SAJ_SAR_ANALYZER_LIB_PATH@

install-data-local: install-saj_conf install-saj_mcinfo_conf install-saj_data install-saj_include install-saj_sosreport_analyzer_lib install-saj_sar_analyzer_lib install-saj_gui
uninstall-local: uninstall-saj_conf uninstall-saj_mcinfo_conf uninstall-saj_data uninstall-saj_include uninstall-saj_sosreport_analyzer_lib uninstall-saj_sar_analyzer_lib uninstall-saj_gui

# install a default saj configuration file if it is not already there
install-saj_conf:
	@if [ -f $(DESTDIR)$(SAJ_CONF_PATH) ]; then \
            echo "$(DESTDIR)$(SAJ_CONF_PATH) already exists, install will not overwrite"; \
	else \
            $(mkinstalldirs) `dirname $(DESTDIR)$(SAJ_CONF_PATH)`; \
            $(INSTALL) -m 644 $(srcdir)/saj.conf.example $(DESTDIR)$(SAJ_CONF_PATH); \
	fi

uninstall-saj_conf:
	-rm -f $(DESTDIR)$(SAJ_CONF_PATH)

# install a default saj-mcinfo configuration file if it is not already there
install-saj_mcinfo_conf:
	@if [ -f $(DESTDIR)$(SAJ_MCINFO_CONF_PATH) ]; then \
            echo "$(DESTDIR)$(SAJ_MCINFO_CONF_PATH) already exists, install will not overwrite"; \
	else \
            $(mkinstalldirs) `dirname $(DESTDIR)$(SAJ_MCINFO_CONF_PATH)`; \
            $(INSTALL) -m 644 $(srcdir)/saj-mcinfo.conf.example $(DESTDIR)$(SAJ_MCINFO_CONF_PATH); \
	fi

uninstall-saj_mcinfo_conf:
	-rm -f $(DESTDIR)$(SAJ_MCINFO_CONF_PATH)

# install saj.conf.example and saj-mcinfo.conf.example
install-saj_data:
	@if [ -f $(DESTDIR)$(SAJ_DATA_PATH) ]; then \
            $(INSTALL) -m 644 $(srcdir)/saj.conf.example $(DESTDIR)$(SAJ_DATA_PATH)/saj.conf.example; \
            $(INSTALL) -m 644 $(srcdir)/saj-mcinfo.conf.example $(DESTDIR)$(SAJ_DATA_PATH)/saj-mcinfo.conf.example; \
            $(INSTALL) -m 644 $(srcdir)/conf/saj.conf.example $(DESTDIR)$(SAJ_DATA_PATH)/saj.conf.example; \
            $(INSTALL) -m 644 $(srcdir)/conf/saj-mcinfo.conf.example $(DESTDIR)$(SAJ_DATA_PATH)/saj-mcinfo.conf.example; \
            $(INSTALL) -m 644 $(srcdir)/README $(DESTDIR)$(SAJ_DATA_PATH)/README; \
	else \
            $(MKDIR_P) $(DESTDIR)$(SAJ_DATA_PATH); \
            $(INSTALL) -m 644 $(srcdir)/saj.conf.example $(DESTDIR)$(SAJ_DATA_PATH)/saj.conf.example; \
            $(INSTALL) -m 644 $(srcdir)/saj-mcinfo.conf.example $(DESTDIR)$(SAJ_DATA_PATH)/saj-mcinfo.conf.example; \
            $(INSTALL) -m 644 $(srcdir)/conf/saj.conf.example $(DESTDIR)$(SAJ_DATA_PATH)/saj.conf.example; \
            $(INSTALL) -m 644 $(srcdir)/conf/saj-mcinfo.conf.example $(DESTDIR)$(SAJ_DATA_PATH)/saj-mcinfo.conf.example; \
            $(INSTALL) -m 644 $(srcdir)/README $(DESTDIR)$(SAJ_DATA_PATH)/README; \
	fi

uninstall-saj_data:
	-rm -rf $(DESTDIR)$(SAJ_DATA_PATH)

# install header files (not all, yet) 
install-saj_include:
	@if [ -d $(DESTDIR)$(SAJ_INCLUDE_PATH) ]; then \
            $(INSTALL) -m 644 $(srcdir)/common/global.h $(DESTDIR)$(SAJ_INCLUDE_PATH)/global.h; \
            $(INSTALL) -m 644 $(srcdir)/common/common_line_data.h $(DESTDIR)$(SAJ_INCLUDE_PATH)/common_line_data.h; \
            $(INSTALL) -m 644 $(srcdir)/libsaj-sosreport-analyzer/cfg.h $(DESTDIR)$(SAJ_INCLUDE_PATH)/cfg.h; \
            $(INSTALL) -m 644 $(srcdir)/libsaj-sosreport-analyzer/common.h $(DESTDIR)$(SAJ_INCLUDE_PATH)/common.h; \
            $(INSTALL) -m 644 $(srcdir)/libsaj-sosreport-analyzer/line_data.h $(DESTDIR)$(SAJ_INCLUDE_PATH)/line_data.h; \
	else \
            $(MKDIR_P) $(DESTDIR)$(SAJ_INCLUDE_PATH); \
            $(INSTALL) -m 644 $(srcdir)/common/global.h $(DESTDIR)$(SAJ_INCLUDE_PATH)/global.h; \
            $(INSTALL) -m 644 $(srcdir)/common/common_line_data.h $(DESTDIR)$(SAJ_INCLUDE_PATH)/common_line_data.h; \
            $(INSTALL) -m 644 $(srcdir)/libsaj-sosreport-analyzer/cfg.h $(DESTDIR)$(SAJ_INCLUDE_PATH)/cfg.h; \
            $(INSTALL) -m 644 $(srcdir)/libsaj-sosreport-analyzer/common.h $(DESTDIR)$(SAJ_INCLUDE_PATH)/common.h; \
            $(INSTALL) -m 644 $(srcdir)/libsaj-sosreport-analyzer/line_data.h $(DESTDIR)$(SAJ_INCLUDE_PATH)/line_data.h; \
	fi

uninstall-saj_include:
	-rm -rf $(DESTDIR)$(SAJ_INCLUDE_PATH)

# install libsaj-sosreport-analyzer.so
install-saj_sosreport_analyzer_lib:
	@if [ -f $(DESTDIR)$(SAJ_SOSREPORT_ANALYZER_LIB_PATH) ]; then \
            $(INSTALL) -m 775 $(srcdir)/libsaj-sosreport-analyzer/.libs/libsaj-sosreport-analyzer.so $(DESTDIR)$(SAJ_SOSREPORT_ANALYZER_LIB_PATH)/libsaj-sosreport-analyzer.so; \
	else \
            $(MKDIR_P) $(DESTDIR)$(SAJ_SOSREPORT_ANALYZER_LIB_PATH); \
            $(INSTALL) -m 775 $(srcdir)/libsaj-sosreport-analyzer/.libs/libsaj-sosreport-analyzer.so $(DESTDIR)$(SAJ_SOSREPORT_ANALYZER_LIB_PATH)/libsaj-sosreport-analyzer.so; \
	fi

uninstall-saj_sosreport_analyzer_lib:
	-rm -f $(DESTDIR)$(SAJ_SOSREPORT_ANALYZER_LIB_PATH)/libsaj-sosreport-analyzer.so

# install libsaj-sar-analyzer.so
install-saj_sar_analyzer_lib:
	@if [ -f $(DESTDIR)$(SAJ_SAR_ANALYZER_LIB_PATH) ]; then \
            $(INSTALL) -m 775 $(srcdir)/libsaj-sar-analyzer/.libs/libsaj-sar-analyzer.so $(DESTDIR)$(SAJ_SAR_ANALYZER_LIB_PATH)/libsaj-sar-analyzer.so; \
	else \
            $(MKDIR_P) $(DESTDIR)$(SAJ_SAR_ANALYZER_LIB_PATH); \
            $(INSTALL) -m 775 $(srcdir)/libsaj-sar-analyzer/.libs/libsaj-sar-analyzer.so $(DESTDIR)$(SAJ_SAR_ANALYZER_LIB_PATH)/libsaj-sar-analyzer.so; \
	fi

uninstall-saj_sar_analyzer_lib:
	-rm -f $(DESTDIR)$(SAJ_SAR_ANALYZER_LIB_PATH)/libsaj-sar-analyzer.so

install-saj_gui:
	$(INSTALL) -m 775 $(srcdir)/gui/saj-gui /usr/local/bin/saj-gui

uninstall-saj_gui:
	-rm -f /usr/local/bin/saj-gui

clean-local:

clean-all:
	$(RM) Makefile
	$(RM) Makefile.in
	$(RM) aclocal.m4
	$(RM) ar-lib
	$(RM) compile
	$(RM) config.*
	$(RM) configure
	$(RM) depcomp
	$(RM) install-sh
	$(RM) libtool
	$(RM) ltmain.sh
	$(RM) missing
	$(RM) libsaj-sar-analyzer/Makefile
	$(RM) libsaj-sar-analyzer/Makefile.in
	$(RM) libsaj-sar-analyzer/*.la
	$(RM) libsaj-sar-analyzer/*.lo
	$(RM) libsaj-sar-analyzer/*.o
	$(RM) libsaj-sosreport-analyzer/Makefile
	$(RM) libsaj-sosreport-analyzer/Makefile.in
	$(RM) libsaj-sosreport-analyzer/*.la
	$(RM) libsaj-sosreport-analyzer/*.lo
	$(RM) libsaj-sosreport-analyzer/*.o
	$(RM) src/Makefile
	$(RM) src/Makefile.in
	$(RM) src/cmp-saj
	$(RM) src/saj
	$(RM) src/*.o
	$(RM) gui/Makefile
	$(RM) gui/Makefile.in
	$(RM) gui/saj-gui
	$(RM) gui/*.o
	$(RM) gui/moc_*
	-rm -rf ./autom4te.cache
	-rm -rf ./.deps/
	-rm -rf .libs _libs
	-rm -f *.lo
	-rm -rf libsaj-sar-analyzer/.deps/
	-rm -rf libsaj-sar-analyzer/.libs/
	-rm -rf libsaj-sosreport-analyzer/.deps/
	-rm -rf libsaj-sosreport-analyzer/.libs/
	-rm -rf src/.deps/
	-rm -rf src/.libs/
	-rm -rf gui/.deps/
