noinst_LIBRARIES=libube-engine.a
libube_engine_a_SOURCES=cell.hpp cell.cpp \
	cell_factory.hpp cell_factory.cpp \
	move.hpp move.cpp \
	puzzle.hpp puzzle.cpp \
	puzzle_loader.hpp puzzle_loader.cpp \
	lua_puzzle_loader.hpp lua_puzzle_loader.cpp \
	lua_state_holder.hpp lua_state_holder.cpp \
	lua_path_finder.hpp lua_path_finder.cpp

# TODO : Find a way to make sure this file is available ...
luadir=${datadir}/@PACKAGE@/lua/engine
lua_DATA=lua/puzzle_lib.lua \
	lua/path_finder_lib.lua \
	lua/agenda.lua \
	lua/node.lua \
	lua/move.lua

AM_CPPFLAGS=-DSRCDIR=\"${srcdir}\" \
	-DLUADIR=\"${luadir}\" \
	-Wall -Werror \
	-I$(srcdir)/../../include \
	-I$(srcdir)/../ \
	$(LUA_INCLUDE) \
	$(BOOST_CPPFLAGS)

# There is one program that aggreatates all tests cases
check_PROGRAMS = engine-tests
engine_tests_SOURCES= tests/engine_tests.cpp \
	tests/cell_test.cpp \
	tests/cell_factory_test.cpp \
	tests/puzzle_test.cpp \
	tests/puzzle_loader_test.cpp \
	tests/lua_puzzle_loader_test.cpp \
	tests/lua_path_finder_test.cpp

# The program needs to be compiled with 
engine_tests_LDADD=libube-engine.a ../common/libube-common.a -L$(top_srcdir)/lib -lgtest -lgmock -llua -ldl

# You should include here any local file that a test program.
# Otherwise it won't be included in the distribution, 
# and make distcheck will fail.
EXTRA_DIST=${lua_DATA} \
	tests/lua/puzzle_loader_test/puzzle1.lua

# This means engine-tests is run when using 'make check'.
TESTS = engine-tests
