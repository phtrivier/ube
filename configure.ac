AC_INIT([ube],[0.1.0],[phtrivier@yahoo.fr])
AM_INIT_AUTOMAKE([foreign -Wall -Werror])
AM_GNU_GETTEXT([external])
AM_GNU_GETTEXT_VERSION([0.17])
AC_PROG_CXX
AC_PROG_RANLIB

PKG_CHECK_MODULES([SDL], [sdl >= 1.2.13])

PKG_CHECK_EXISTS([SDL_image], 
			      PKG_CHECK_MODULES([SDL_image], [SDL_image], , 
               			      AC_CHECK_LIB(SDL_image, IMG_LoadPNG_RW)))

PKG_CHECK_EXISTS([SDL_mixer], 
			      PKG_CHECK_MODULES([SDL_mixer], [SDL_mixer], ,
	 			      AC_CHECK_LIB(SDL_mixer, Mix_LoadMUS)))

AC_CHECK_LIB([SDL_ttf], [TTF_Init], , AC_MSG_WARN([Could not find ttf lib]))

AC_CHECK_LIB([popt], [poptGetContext], , AC_MSG_WARN([Could not find popt lib]))

dnl PKG_CHECK_EXISTS([SDL_image],
dnl   PKG_CHECK_MODULES([SDL_image],
dnl      AC_CHECK_LIB(SDL_image, IMG_LoadPNG_RW)))

dnl AC_CHECK_LIB(SDL_image, IMG_LoadPNG_RW, , ,)
dnl AC_CHECK_LIB(SDL_mixer, MIX_LoadMUS, , ,)
dnl AC_CHECK_LIB(SDL_ttf, TTF_OpenFontRW, , ,)
dnl PKG_CHECK_MODULES([SDL_image], [SDL_image])
dnl PKG_CHECK_MODULES([SDL_mixer], [SDL_mixer])
#PKG_CHECK_MODULES([SDL_ttf], [SDL_ttf])
dnl PKG_CHECK_MODULES([SDL_mixer])
dnl PKG_CHECK_MODULES([SDL_ttf])

dnl SDL_VERSION=1.2.13
dnl AM_PATH_SDL($SDL_VERSION, :,
dnl             AC_MSG_ERROR([*** SDL version $SDL_VERSION not found!]))

dnl # Check for SDL_image library
dnl AC_SEARCH_LIBS(IMG_LoadPNG_RW, SDL_image, , 
dnl  	     AC_MSG_WARN([*** Unable to find SDL_image libary with PNG support
dnl 	     		      Are you cross compiling ?
dnl 	     		       (http://www.libsdl.org/projects/SDL_image/)]))

dnl AC_SEARCH_LIBS(TTF_OpenFontRW, SDL_ttf, , 
dnl  	     AC_MSG_WARN([*** Unable to find SDL_ttf library.
dnl 	     		      Are you cross compiling ?]))

dnl AC_SEARCH_LIBS(Mix_LoadMUS, SDL_mixer, , 
dnl              AC_MSG_WARN([*** Unable to find SDL_mixer library.
dnl                               Are you cross compiling ? ]))			
			    
# You might need to define --with-lua-prefix and --with-lua-suffix to use this
AX_LUA_HEADERS
AX_LUA_LIBS

AX_BOOST_BASE([1.34])

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([ 
	Makefile
   	src/Makefile
	src/common/Makefile
   	src/engine/Makefile
   	src/mvc/Makefile
   	src/client/Makefile
	po/Makefile.in
	data/Makefile
	data/images/Makefile
	data/fonts/Makefile
	data/ogg/Makefile
	data/lua/Makefile
	data/lua/puzzles/Makefile
])
AC_OUTPUT
		