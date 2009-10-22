bin_PROGRAMS = ube
ube_SOURCES = ube.cpp gettext.h

# TODO : Find a way not to have to repeat this ... 
luadir=${datadir}/@PACKAGE@/lua

AM_CPPFLAGS= -DLOCALEDIR=\"$(datadir)/locale\" \
	-DDATADIR=\"${datadir}/@PACKAGE@\" \
	-DLUADIR=\"${luadir}\" \
	-Wall -Werror \
	-I$(srcdir)/../engine  \
	$(SDL_CFLAGS) \
	$(LUA_INCLUDE)
	-I$(srcdir)/../../include

# LUA_LIBS=-L$(top_srcdir)/lib -llua -ldl

ube_LDADD=../engine/libube-engine.a $(LUA_LIB) $(SDL_LIBS) 

# FIXME(pht) : I need the libintl to be passed to the windows binaries, also ... and it seems to be null for the moment !!
# ube_LDADD=$(srcdir)/../engine/libube-engine.a -L$(LIBINTL)
