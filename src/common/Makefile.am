noinst_LIBRARIES=libube-common.a
libube_common_a_SOURCES=lua_helper.hpp \
	gettext.h  i18n.hpp \
	silent_ostream.hpp \
	log_level.hpp logging.hpp logging.cpp \
	logger_interface.hpp \
	cout_logger.hpp \
	silent_logger.hpp \
	file_checker_interface.hpp \
	resource_resolver_interface.hpp \
	prefix_resource_resolver.hpp prefix_resource_resolver.cpp \
	stat_file_checker.hpp stat_file_checker.cpp

if MINGW
AM_CPPFLAGS=-DSRCDIR=\"${srcdir}\" \
	-DLUADIR=\"${luadir}\" \
	-Wall -Werror \
	-I$(srcdir)/../../include \
	$(BOOST_CPPFLAGS) \
	$(LUA_INCLUDE)
else
AM_CPPFLAGS=-DSRCDIR=\"${srcdir}\" \
	-DLUADIR=\"${luadir}\" \
	-Wall -Werror \
	-I$(srcdir)/../../include \
	$(BOOST_CPPFLAGS)
endif

# There is one program that aggreatates all tests cases
check_PROGRAMS = common-tests
common_tests_SOURCES= tests/common_tests.cpp \
	tests/prefix_resource_resolver_test.cpp \
	tests/mock_file_checker.hpp \
	tests/mock_resource_resolver.hpp \
	tests/stat_file_checker_test.cpp

# The program needs to be compiled with 
common_tests_LDADD=libube-common.a -L$(top_srcdir)/lib -lgtest -lgmock -llua -ldl

# This means common-tests is run when using 'make check'.
TESTS = common-tests
