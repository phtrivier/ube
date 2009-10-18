AC_INIT([ube],[0.1],[phtrivier@yahoo.fr])
AM_INIT_AUTOMAKE([foreign -Wall -Werror])
AM_GNU_GETTEXT([external])
AM_GNU_GETTEXT_VERSION([0.17])
AC_PROG_CXX
AC_PROG_RANLIB

SDL_VERSION=1.2.13
AM_PATH_SDL($SDL_VERSION, :,
            AC_MSG_ERROR([*** SDL version $SDL_VERSION not found!]))

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
		