bin_PROGRAMS = bin/larch bin/larcht

ACLOCAL_AMFLAGS = -I m4

bin_larch_SOURCES = src/larch.cpp \
vendor/easylogging++.h \
vendor/gsl.h \
src/larch_types.hpp \
src/stringpattern.cpp \
src/stringpattern.hpp \
src/strutil.cpp \
src/strutil.hpp \
src/tcpconnection.cpp \
src/tcpconnection.hpp \
src/tcplistener.cpp \
src/tcplistener.hpp \
src/webdatafetcher.cpp \
src/webdatafetcher.hpp \
src/web_request.cpp \
src/web_request.hpp \
src/web_response.cpp \
src/web_response.hpp \
src/web_server.cpp \
src/web_server.hpp \
src/web_static_file.cpp \
src/web_static_file.hpp

bin_larcht_SOURCES = src/larcht.cpp \
src/easylogging++.h \
vendor/gsl.h \
src/larch_types.hpp \
src/stringpattern.cpp \
src/stringpattern.hpp \
src/strutil.cpp \
src/strutil.hpp \
src/tcpconnection.cpp \
src/tcpconnection.hpp \
src/tcplistener.cpp \
src/tcplistener.hpp \
src/webdatafetcher.cpp \
src/webdatafetcher.hpp \
src/web_request.cpp \
src/web_request.hpp \
src/web_response.cpp \
src/web_response.hpp \
src/web_server.cpp \
src/web_server.hpp \
src/web_static_file.cpp \
src/web_static_file.hpp

AM_CXXFLAGS = -I src -I vendor

format-code :
	for i in ${bin_larch_SOURCES}; do clang-format-3.5 -style=Google -i $$i; done

