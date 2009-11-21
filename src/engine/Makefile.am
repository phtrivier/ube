lib_LIBRARIES=libube-engine.a
libube_engine_a_SOURCES=gettext.h lua_helper.hpp \
	cell.hpp \
	cell_factory.hpp cell_factory.cpp \
	puzzle.hpp puzzle.cpp \
	abstract_file_checker.hpp \
	resource_resolver.hpp resource_resolver.cpp \
	stat_file_checker.hpp stat_file_checker.cpp \
	puzzle_loader.hpp puzzle_loader.cpp \
	lua_puzzle_loader.hpp lua_puzzle_loader.cpp
#	puzzle.hpp puzzle.cpp lua_puzzle.hpp lua_puzzle.cpp\
# 	lua_script_runner.hpp lua_script_runner.cpp

# TODO : Find a way to make sure this file is available ...
luadir=${datadir}/@PACKAGE@/lua/engine
lua_DATA=lua/story_lib.lua

AM_CPPFLAGS=-DSRCDIR=\"${srcdir}\" \
	-DLUADIR=\"${luadir}\" \
	-Wall -Werror \
	-I$(srcdir)/../../include \
	$(LUA_INCLUDE) \
	$(BOOST_CPPFLAGS)

# There is one program that aggreatates all tests cases
check_PROGRAMS = engine-tests
engine_tests_SOURCES= tests/engine_tests.cpp \
	tests/cell_test.cpp \
	tests/cell_factory_test.cpp \
	tests/puzzle_test.cpp \
	tests/resource_resolver_test.cpp \
	tests/mock_file_checker.hpp \
	tests/stat_file_checker_test.cpp \
	tests/puzzle_loader_test.cpp \
	tests/lua_puzzle_loader_test.cpp
#	tests/lua_script_runner_test.cpp

# The program needs to be compiled with 
engine_tests_LDADD=libube-engine.a -L$(top_srcdir)/lib -lgtest -lgmock -llua -ldl

# You should include here any local file that a test program.
# Otherwise it won't be included in the distribution, 
# and make distcheck will fail.
EXTRA_DIST=${lua_DATA}
#	tests/lua/lua_script_runner_test_story1.lua

# This means engine-tests is run when using 'make check'.
TESTS = engine-tests
