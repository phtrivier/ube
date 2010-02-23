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
	in_game_renderer_interface.hpp \
	in_game_model.hpp in_game_model.cpp \
	in_game_view.hpp in_game_view.cpp \
	in_game_mode.hpp in_game_mode.cpp \
	sdl_in_game_renderer.hpp sdl_in_game_renderer.cpp \
	in_game_mode_factory.hpp in_game_mode_factory.cpp \
	option_parser.hpp option_parser.cpp

bin_PROGRAMS = ube
ube_SOURCES = ube.cpp

# TODO : Find a way not to have to repeat this ... 
luadir=${datadir}/@PACKAGE@/lua

AM_CPPFLAGS= -g -DLOCALEDIR=\"${datadir}/locale\" \
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
SDL_MIXER_LIBS =  -lSDL_mixer -logg -lvorbis -lsmpeg

ube_LDADD=libube-client.a \
	../engine/libube-engine.a \
	../common/libube-common.a \
	-lpopt \
	$(SDL_MIXER_LIBS) $(SDL_LIBS) $(SDL_IMAGE_LIBS) $(SDL_TTF_LIBS) \
	$(LUA_LIB) $(LIBINTL)

check_PROGRAMS=client-tests
client_tests_SOURCES=tests/client_tests.cpp \
	tests/mock_observer.hpp \
	tests/mock_controller.hpp \
	tests/mock_view.hpp \
	tests/mock_clock.hpp \
	tests/mock_in_game_renderer.hpp \
	tests/observable_test.cpp \
	tests/game_mode_test.cpp \
	tests/game_loop_test.cpp \
	tests/in_game_view_test.cpp \
	tests/option_parser_test.cpp \
	tests/sdl_in_game_renderer_test.cpp

client_tests_LDADD=libube-client.a \
	../engine/libube-engine.a \
	../common/libube-common.a \
	-L$(top_srcdir)/lib -lgtest -lgmock -llua -ldl -lpopt

TESTS = client-tests
