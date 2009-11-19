lib_LIBRARIES=libube-client.a
libube_client_a_SOURCES=gettext.h \
	sdl_app.hpp sdl_app.cpp

bin_PROGRAMS = ube
ube_SOURCES = ube.cpp

# TODO : Find a way not to have to repeat this ... 
luadir=${datadir}/@PACKAGE@/lua

AM_CPPFLAGS= -DLOCALEDIR=\"${datadir}/locale\" \
	-DDATADIR=\"${datadir}/@PACKAGE@\" \
	-DLUADIR=\"${luadir}\" \
	-DPREFIX=\"${prefix}\" \
	-Wall -Werror \
	-I$(srcdir)/../../include \
	-I$(srcdir)/../engine \
	$(SDL_CFLAGS) \
	$(LUA_INCLUDE)

SDL_TTF_LIBS = -lSDL_ttf -lfreetype
SDL_IMAGE_LIBS = -lSDL_image -lpng -ltiff -ljpeg -lz

ube_LDADD=../engine/libube-engine.a libube-client.a $(LUA_LIB) $(LIBINTL) $(SDL_LIBS) $(SDL_IMAGE_LIBS) $(SDL_TTF_LIBS)

check_PROGRAMS=client-tests
client_tests_SOURCES=tests/client_tests.cpp

client_tests_LDADD=libube-client.a -L$(top_srcdir)/lib -lgtest -lgmock -llua -ldl

TESTS = client-tests
