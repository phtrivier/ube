noinst_LIBRARIES=libube-engine.a
libube_engine_a_SOURCES=cell.hpp cell.cpp \
	cell_factory.hpp cell_factory.cpp \
	move.hpp move.cpp \
	game_event.hpp \
	puzzle.hpp puzzle.cpp \
	puzzle_loader.hpp puzzle_loader.cpp \
	lua_puzzle_functions.hpp \
	lua_puzzle_loader.hpp lua_puzzle_loader.cpp \
	lua_state_holder.hpp lua_state_holder.cpp \
	path_finder_interface.hpp \
	lua_path_finder.hpp lua_path_finder.cpp \
	script_runner_interface.hpp \
	lua_command.hpp lua_command.cpp

# TODO : Find a way to make sure this file is available ...
luadir=${datadir}/@PACKAGE@/lua/engine
lua_DATA=lua/puzzle_lib.lua \
	lua/path_finder_lib.lua \
	lua/agenda.lua \
	lua/node.lua \
	lua/move.lua \
	lua/archive.lua \
	lua/script.lua \
	lua/pick_move.lua \
	lua/i18n.lua

if MINGW
AM_CPPFLAGS=-DSRCDIR=\"${srcdir}\" \
	-DLUADIR=\"${luadir}\" \
	-Wall -Werror \
	-I$(srcdir)/../../include \
	-I$(srcdir)/../ \
	$(LUA_INCLUDE) \
	$(BOOST_CPPFLAGS)
else
AM_CPPFLAGS=-DSRCDIR=\"${srcdir}\" \
	-DLUADIR=\"${luadir}\" \
	-Wall -Werror \
	-I$(srcdir)/../../include \
	-I$(srcdir)/../ \
	-I$(srcdir)/../lua \
	$(BOOST_CPPFLAGS)
endif

# There is one program that aggreatates all tests cases
check_PROGRAMS = engine-tests 
engine_tests_SOURCES= tests/engine_tests.cpp \
	tests/cell_test.cpp \
	tests/cell_factory_test.cpp \
	tests/puzzle_test.cpp \
	tests/puzzle_loader_test.cpp \
	tests/lua_puzzle_loader_test.cpp \
	tests/lua_path_finder_test.cpp \
	tests/mock_path_finder.hpp \
	tests/mock_script_runner.hpp \
	tests/lua_command_test.cpp

# 	../mvc/libube-mvc.a

if MINGW
engine_tests_LDADD=libube-engine.a \
	../mvc/libube-mvc.a \
	../common/libube-common.a \
	-L$(top_srcdir)/lib -lgtest -lgmock -llua -ldl
else
engine_tests_LDADD=libube-engine.a \
	../common/libube-common.a \
	../mvc/libube-mvc.a \
	../lua/liblua.a \
	-L$(top_srcdir)/lib -lgtest -lgmock -ldl
endif

# You should include here any local file that a test program.
# Otherwise it won't be included in the distribution, 
# and make distcheck will fail.
EXTRA_DIST=${lua_DATA} \
	tests/lua/puzzle_loader_test/puzzle1.lua \
	tests/lua/puzzle_loader_test/puzzle2.lua \
	tests/lua/puzzle_loader_test/puzzle_with_scripts.lua \
	tests/lua/puzzle_loader_test/puzzle_with_numbered_cells.lua \
	tests/lua/puzzle_loader_test/puzzle_with_messages.lua

# This means engine-tests is run when using 'make check'.
TESTS = engine-tests
