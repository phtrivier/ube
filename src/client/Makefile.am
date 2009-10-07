# datadir = @datadir@
# localedir = $(datadir)/locale
# DEFS = -DLOCALEDIR=\"$(localedir)\" @DEFS@

#AM_CPPFLAGS= -DLOCALEDIR=\"$(localedir)\"

bin_PROGRAMS = ube
ube_SOURCES = ube.cpp gettext.h

AM_CPPFLAGS= -DLOCALEDIR=\"$(datadir)/locale\" -Wall -Werror -I$(srcdir)/../engine

#ube_CPPFLAGS=-DLOCALEDIR=\"$(localedir)\" -Wall -Werror -I$(srcdir)/../engine
ube_LDADD=$(srcdir)/../engine/libube-engine.a

LDADD=$(LIBINTL)