bin_PROGRAMS = ube
ube_SOURCES = ube.cpp \
	gettext.h \
	sdl_app.hpp sdl_app.cpp	

# TODO : Find a way not to have to repeat this ... 
luadir=${datadir}/@PACKAGE@/lua

AM_CPPFLAGS= -DLOCALEDIR=\"$(datadir)/locale\" \
	-DDATADIR=\"${datadir}/@PACKAGE@\" \
	-DLUADIR=\"${luadir}\" \
	-Wall -Werror \
	-I$(srcdir)/../engine \
	$(LUA_INCLUDE) \
	$(SDL_CFLAGS) 

ube_LDADD=../engine/libube-engine.a $(LUA_LIB) $(LIBINTL) $(SDL_LIBS)
