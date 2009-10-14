lib_LIBRARIES=libube-engine.a
libube_engine_a_SOURCES=greeter.hpp greeter.cpp gettext.h amplifier.hpp

AM_CPPFLAGS=-Wall -Werror -I$(srcdir)/../../include

# Typicall configuration to have tests
# TODO : automake macro to make this simpler ? 
check_PROGRAMS = engine-tests
# Boring part : manually adding all the source files for which a test is done ...
engine_tests_SOURCES= tests/engine_tests.cpp tests/greeter_test.cpp tests/mock_amplifier.hpp
engine_tests_LDADD=$(srcdir)/../engine/libube-engine.a -L$(srcdir)/../../lib -lgtest -lgmock

# This means engine-tests is run when using 'make check'.
TESTS = engine-tests

