lib_LIBRARIES=libube-engine.a
libube_engine_a_SOURCES=greeter.hpp greeter.cpp gettext.h amplifier.hpp

AM_CPPFLAGS=-DSRCDIR=\"${srcdir}\" -Wall -Werror -I$(srcdir)/../../include

# There is one program that aggreatates all tests cases
check_PROGRAMS = engine-tests
engine_tests_SOURCES= tests/engine_tests.cpp \
	tests/greeter_test.cpp \
	tests/mock_amplifier.hpp

# The program needs to be compiled with 
engine_tests_LDADD=libube-engine.a -L$(top_srcdir)/lib -lgtest -lgmock

# You should include here any local file that a test program.
# Otherwise it won't be included in the distribution, 
# and make distcheck will fail.
EXTRA_DIST=tests/script1.lua

# This means engine-tests is run when using 'make check'.
TESTS = engine-tests
