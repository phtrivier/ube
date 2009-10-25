lib_LIBRARIES=libube-client.a
libube_client_a_SOURCES=gettext.h \
	sdl_app.hpp sdl_app.cpp	\
	abstract_file_checker.hpp \
	resource_resolver.hpp resource_resolver.cpp

bin_PROGRAMS = ube
ube_SOURCES = ube.cpp

# TODO : Find a way not to have to repeat this ... 
luadir=${datadir}/@PACKAGE@/lua

AM_CPPFLAGS= -DLOCALEDIR=\"${datadir}/locale\" \
	-DDATADIR=\"${datadir}/@PACKAGE@\" \
	-DLUADIR=\"${luadir}\" \
	-Wall -Werror \
	-I$(srcdir)/../../include \
	-I$(srcdir)/../engine \
	$(SDL_CFLAGS) \
	$(LUA_INCLUDE)

ube_LDADD=../engine/libube-engine.a libube-client.a $(LUA_LIB) $(LIBINTL) $(SDL_LIBS)

check_PROGRAMS=client-tests
client_tests_SOURCES=tests/client_tests.cpp \
	tests/resource_resolver_test.cpp \
	tests/mock_file_checker.hpp

client_tests_LDADD=libube-client.a -L$(top_srcdir)/lib -lgtest -lgmock -llua -ldl

TESTS = client-tests
