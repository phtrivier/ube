AC_INIT([ube],[0.3.0],[phtrivier@yahoo.fr])
AM_INIT_AUTOMAKE([foreign -Wall -Werror])
AM_GNU_GETTEXT([external])
AM_GNU_GETTEXT_VERSION([0.17])
AC_PROG_CXX
AC_PROG_RANLIB

PKG_CHECK_MODULES([SDL], [sdl >= 1.2.13])

PKG_CHECK_EXISTS([SDL_image], [PKG_CHECK_MODULES([SDL_image], [SDL_image >= 1.2])], [AC_CHECK_LIB(SDL_image, IMG_LoadPNG_RW,,AC_MSG_ERROR([*** Unable to find SDL_image libary]))])

PKG_CHECK_EXISTS([SDL_mixer], [PKG_CHECK_MODULES([SDL_mixer], [SDL_mixer >= 1.2])], [AC_CHECK_LIB(SDL_mixer, Mix_LoadMUS,,AC_MSG_ERROR([*** Unable to find SDL_mixer libary]))])

AC_CHECK_LIB([SDL_ttf], [TTF_Init], , AC_MSG_WARN([Could not find ttf lib]))

AC_CHECK_LIB([popt], [poptGetContext], , AC_MSG_WARN([Could not find popt lib]))

AX_BOOST_BASE([1.34])

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([ 
	Makefile
   	src/Makefile
	src/lua/Makefile
	src/common/Makefile
   	src/engine/Makefile
   	src/mvc/Makefile
   	src/client/Makefile
	po/Makefile.in
	data/Makefile
	data/images/Makefile
	data/images/png/Makefile
	data/fonts/Makefile
	data/ogg/Makefile
	data/lua/Makefile
	data/lua/puzzles/Makefile
])
AC_OUTPUT
		