lib_LIBRARIES=libube-engine.a
libube_engine_a_SOURCES=greeter.hpp greeter.cpp gettext.h amplifier.hpp

AM_CPPFLAGS=-Wall -Werror -I$(srcdir)/../../include

# Typicall configuration to have tests
check_PROGRAMS = engine-tests
engine_tests_SOURCES= tests/engine_tests.cpp tests/greeter_test.cpp tests/mock_amplifier.hpp
engine_tests_LDADD=libube-engine.a -L$(top_srcdir)/lib -lgtest -lgmock

# This means engine-tests is run when using 'make check'.
TESTS = engine-tests

