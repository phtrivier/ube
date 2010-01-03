lib_LIBRARIES=libube-client.a
libube_client_a_SOURCES=gettext.h \
	observer_interface.hpp \
	controller_interface.hpp \
	view_interface.hpp \
	clock_interface.hpp \
	observable.hpp observable.cpp \
	game_mode.hpp game_mode.cpp \
	game_event.hpp \
	game_loop.hpp game_loop.cpp \
	sdl_clock.hpp sdl_clock.cpp \
	sdl_controller.hpp sdl_controller.cpp \
	sdl_view.hpp sdl_view.cpp

bin_PROGRAMS = ube
ube_SOURCES = ube.cpp

# TODO : Find a way not to have to repeat this ... 
luadir=${datadir}/@PACKAGE@/lua

AM_CPPFLAGS= -DLOCALEDIR=\"${datadir}/locale\" \
	-DDATADIR=\"${datadir}/@PACKAGE@\" \
	-DLUADIR=\"${luadir}\" \
	-DPREFIX=\"${prefix}\" \
	-Wall -Werror -enable-assert\
	-I$(srcdir)/../../include \
	-I$(srcdir)/../ \
	$(SDL_CFLAGS) \
	$(LUA_INCLUDE)

SDL_TTF_LIBS = -lSDL_ttf -lfreetype
SDL_IMAGE_LIBS = -lSDL_image -lpng -ltiff -ljpeg -lz

ube_LDADD=../common/libube-common.a \
	../engine/libube-engine.a \
	libube-client.a \
	$(LUA_LIB) $(LIBINTL) \
	$(SDL_LIBS) $(SDL_IMAGE_LIBS) $(SDL_TTF_LIBS)

check_PROGRAMS=client-tests
client_tests_SOURCES=tests/client_tests.cpp \
	tests/mock_observer.hpp \
	tests/mock_controller.hpp \
	tests/mock_view.hpp \
	tests/mock_clock.hpp \
	tests/observable_test.cpp \
	tests/game_mode_test.cpp \
	tests/game_loop_test.cpp

client_tests_LDADD=../common/libube-common.a \
	../engine/libube-engine.a \
	libube-client.a \
	-L$(top_srcdir)/lib -lgtest -lgmock -llua -ldl

TESTS = client-tests
