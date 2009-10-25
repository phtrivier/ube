AC_INIT([ube],[0.1],[phtrivier@yahoo.fr])
AM_INIT_AUTOMAKE([foreign -Wall -Werror])
AM_GNU_GETTEXT([external])
AM_GNU_GETTEXT_VERSION([0.17])
AC_PROG_CXX
AC_PROG_RANLIB

SDL_VERSION=1.2.13
AM_PATH_SDL($SDL_VERSION, :,
            AC_MSG_ERROR([*** SDL version $SDL_VERSION not found!]))

# Check for SDL_image library
AC_CHECK_LIB(SDL_image, IMG_LoadPNG_RW, , 
	     AC_MSG_ERROR([*** Unable to find SDL_image libary with PNG support
	     		       (http://www.libsdl.org/projects/SDL_image/)]))

# You might need to define --with-lua-prefix and --with-lua-suffix to use this
AX_LUA_HEADERS
AX_LUA_LIBS

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
		