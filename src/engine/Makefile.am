lib_LIBRARIES=libube-engine.a
libube_engine_a_SOURCES=greeter.hpp greeter.cpp \
	gettext.h lua_helper.hpp \
	amplifier.hpp \
	puzzle.hpp puzzle.cpp lua_puzzle.hpp lua_puzzle.cpp\
	lua_script_runner.hpp lua_script_runner.cpp

# TODO : Find a way to make sure this file is available ...
luadir=${datadir}/@PACKAGE@/lua
lua_DATA=lua/story_lib.lua

AM_CPPFLAGS=-DSRCDIR=\"${srcdir}\" \
	-DLUADIR=\"${luadir}\" \
	-Wall -Werror \
	-I$(srcdir)/../../include

# There is one program that aggreatates all tests cases
check_PROGRAMS = engine-tests
engine_tests_SOURCES= tests/engine_tests.cpp \
	tests/greeter_test.cpp \
	tests/mock_amplifier.hpp \
	tests/lua_script_runner_test.cpp

# The program needs to be compiled with 
engine_tests_LDADD=libube-engine.a -L$(top_srcdir)/lib -lgtest -lgmock -llua -ldl

# You should include here any local file that a test program.
# Otherwise it won't be included in the distribution, 
# and make distcheck will fail.
EXTRA_DIST=${lua_DATA} \
	tests/lua/lua_script_runner_test_story1.lua

# This means engine-tests is run when using 'make check'.
TESTS = engine-tests
