AC_INIT([ube],[0.1],[phtrivier@yahoo.fr])
AM_INIT_AUTOMAKE([foreign -Wall -Werror])
AM_GNU_GETTEXT([external])
AM_GNU_GETTEXT_VERSION([0.17])
AC_PROG_CXX
AC_PROG_RANLIB

SDL_VERSION=1.2.13
AM_PATH_SDL($SDL_VERSION, :,
            AC_MSG_ERROR([*** SDL version $SDL_VERSION not found!]))


# I can't get AX_LUA_HEADERS to work and define LUA_INCLUDE ... 
# Plus, I need to define --with-lua-headers first (which is broken on ubuntu..
# So for the moment I'll go with embedding the library in the app ...
# however someday I'll need this : 
# AX_WITH_LUA
# AX_LUA_HEADERS
# AX_LUA_VERSION(501)

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([ 
	Makefile
   	src/Makefile
   	src/engine/Makefile
   	src/client/Makefile
	po/Makefile.in
	data/Makefile
	data/images/Makefile
])
AC_OUTPUT
		