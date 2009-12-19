lib_LIBRARIES=libube-common.a
libube_common_a_SOURCES=gettext.h lua_helper.hpp \
	abstract_file_checker.hpp \
	resource_resolver.hpp resource_resolver.cpp \
	stat_file_checker.hpp stat_file_checker.cpp

AM_CPPFLAGS=-DSRCDIR=\"${srcdir}\" \
	-DLUADIR=\"${luadir}\" \
	-Wall -Werror \
	-I$(srcdir)/../../include \
	$(LUA_INCLUDE) \
	$(BOOST_CPPFLAGS)

# There is one program that aggreatates all tests cases
check_PROGRAMS = common-tests
common_tests_SOURCES= tests/common_tests.cpp \
	tests/resource_resolver_test.cpp \
	tests/mock_file_checker.hpp \
	tests/stat_file_checker_test.cpp

# The program needs to be compiled with 
common_tests_LDADD=libube-common.a -L$(top_srcdir)/lib -lgtest -lgmock -llua -ldl

# This means common-tests is run when using 'make check'.
TESTS = common-tests
