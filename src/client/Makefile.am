lib_LIBRARIES=libube-client.a
libube_client_a_SOURCES=gettext.h \
	game_mode_interface.hpp game_mode.hpp game_mode.cpp \
	game_event.hpp \
	game_loop.hpp game_loop.cpp \
	sdl_clock.hpp sdl_clock.cpp \
	sdl_controller.hpp sdl_controller.cpp \
	renderer_interface.hpp \
	in_game_renderer_interface.hpp \
	in_game_renderer_geometry.hpp in_game_renderer_geometry.cpp \
	in_game_model.hpp in_game_model.cpp \
	in_game_view.hpp in_game_view.cpp \
	in_game_mode.hpp in_game_mode.cpp \
	sdl_renderer.hpp sdl_renderer.cpp \
	sdl_in_game_renderer.hpp sdl_in_game_renderer.cpp \
	in_game_mode_factory.hpp in_game_mode_factory.cpp \
	option_parser.hpp option_parser.cpp \
	command_factory_interface.hpp \
	in_game_command_factory.hpp in_game_command_factory.cpp \
	move_command.hpp move_command.cpp \
	in_game_command_stack.hpp in_game_command_stack.cpp \
	ube_game.hpp ube_game.cpp \
	puzzle_selection_model.hpp puzzle_selection_model.cpp \
	puzzle_selection_renderer_interface.hpp \
	puzzle_selection_geometry.hpp puzzle_selection_geometry.cpp \
	puzzle_selection_view.hpp puzzle_selection_view.cpp \
	puzzle_selection_mode.hpp puzzle_selection_mode.cpp \
	puzzle_selection_mode_factory.hpp puzzle_selection_mode_factory.cpp \
	sdl_puzzle_selection_renderer.hpp  sdl_puzzle_selection_renderer.cpp

ube_PROGRAMS = ube
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
SDL_MIXER_LIBS = -lSDL_mixer
POPT_LIBS=-lpopt

if MINGW
PROJECT_LIBS=libube-client.a \
	../mvc/libube-mvc.a \
	../engine/libube-engine.a \
	../common/libube-common.a
else
PROJECT_LIBS=libube-client.a \
	../mvc/libube-mvc.a \
	../engine/libube-engine.a \
	../common/libube-common.a \
	../lua/liblua.a
endif

ube_LDADD=$(PROJECT_LIBS) \
	$(POPT_LIBS) \
	$(SDL_image_LIBS) $(SDL_TTF_LIBS) $(SDL_mixer_LIBS) \
	$(SDL_IMAGE_LIBS) $(SDL_MIXER_LIBS) \
	$(LIBINTL) $(LUA_LIB)

check_PROGRAMS=client-tests
client_tests_SOURCES=tests/client_tests.cpp \
	tests/mock_command_factory.hpp \
	tests/mock_game_mode.hpp \
	tests/mock_in_game_renderer.hpp \
	tests/mock_puzzle_selection_renderer.hpp \
	tests/game_mode_test.cpp \
	tests/game_loop_test.cpp \
	tests/in_game_view_test.cpp \
	tests/option_parser_test.cpp \
	tests/in_game_renderer_geometry_test.cpp \
	tests/in_game_command_stack_test.cpp \
	tests/puzzle_selection_model_test.cpp \
	tests/puzzle_selection_view_test.cpp \
	tests/in_game_model_test.cpp 

client_tests_LDADD=$(PROJECT_LIBS) \
	-L$(top_srcdir)/lib -lgtest -lgmock \
	$(POPT_LIBS) \
	$(SDL_image_LIBS) $(SDL_TTF_LIBS) $(SDL_mixer_LIBS) \
	$(SDL_IMAGE_LIBS) $(SDL_MIXER_LIBS) \
	$(LIBINTL) $(LUA_LIB)

TESTS = client-tests
