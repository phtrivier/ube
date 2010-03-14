noinst_LIBRARIES=libube-mvc.a
libube_mvc_a_SOURCES=command_stack.hpp command_stack.cpp \
	command_interface.hpp \
	clock_interface.hpp \
	observer_interface.hpp \
	observable.hpp observable.cpp \
	controller_interface.hpp view_interface.hpp

# TODO : Find a way to make sure this file is available ...
# luadir=${datadir}/@PACKAGE@/lua/mvc
# lua_DATA=lua/puzzle_lib.lua \
# 	lua/path_finder_lib.lua \
# 	lua/agenda.lua \
# 	lua/node.lua \
# 	lua/move.lua

AM_CPPFLAGS=-DSRCDIR=\"${srcdir}\" \
	-DLUADIR=\"${luadir}\" \
	-Wall -Werror \
	-I$(srcdir)/../../include \
	-I$(srcdir)/../ \
	$(BOOST_CPPFLAGS)

# There is one program that aggreatates all tests cases
check_PROGRAMS = mvc-tests
mvc_tests_SOURCES= tests/mvc_tests.cpp \
	tests/mock_command.hpp \
	tests/command_stack_test.cpp \
	tests/mock_observer.hpp \
	tests/mock_clock.hpp \
	tests/mock_controller.hpp \
	tests/mock_view.hpp \
	tests/observable_test.cpp

# The program needs to be compiled with 
mvc_tests_LDADD=libube-mvc.a \
	../engine/libube-engine.a \
	../common/libube-common.a \
	-L$(top_srcdir)/lib -lgtest -lgmock -llua -ldl

# You should include here any local file that a test program.
# Otherwise it won't be included in the distribution, 
# and make distcheck will fail.
# EXTRA_DIST=${lua_DATA} \
# 	tests/lua/puzzle_loader_test/puzzle1.lua

# This means mvc-tests is run when using 'make check'.
TESTS = mvc-tests
