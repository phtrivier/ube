bin_PROGRAMS = ube
ube_SOURCES = ube.cpp gettext.h

AM_CPPFLAGS= -DLOCALEDIR=\"$(datadir)/locale\" -Wall -Werror -I$(srcdir)/../engine

ube_LDADD=../engine/libube-engine.a -lSDL

# FIXME(pht) : I need the libintl to be passed to the windows binaries, also ... and it seems to be null for the moment !!
# ube_LDADD=$(srcdir)/../engine/libube-engine.a -L$(LIBINTL)
