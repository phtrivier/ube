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
AC_SEARCH_LIBS(IMG_LoadPNG_RW, SDL_image, , 
 	     AC_MSG_WARN([*** Unable to find SDL_image libary with PNG support
	     		      Are you cross compiling ?
	     		       (http://www.libsdl.org/projects/SDL_image/)]))

AC_SEARCH_LIBS(TTF_OpenFontRW, SDL_ttf, , 
 	     AC_MSG_WARN([*** Unable to find SDL_ttf library.
	     		      Are you cross compiling ?]))

AC_SEARCH_LIBS(Mix_LoadMUS, SDL_mixer, , 
             AC_MSG_WARN([*** Unable to find SDL_mixer library.
                              Are you cross compiling ? ]))			    


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
   	src/client/Makefile
	po/Makefile.in
	data/Makefile
	data/images/Makefile
	data/fonts/Makefile
])
AC_OUTPUT
		