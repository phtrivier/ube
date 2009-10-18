#include <greeter.hpp>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
using ::testing::AtLeast;

#include "tests/mock_amplifier.hpp"
#include <iostream>
#include <fstream>
using namespace std;

namespace {

  // The fixture for testing class Foo.
  class GreeterTest : public ::testing::Test {
  protected:
    // You can remove any or all of the following functions if its body
    // is empty.

    GreeterTest() {
      // You can do set-up work for each test here.
    }

    virtual ~GreeterTest() {
      // You can do clean-up work that doesn't throw exceptions here.
    }

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    virtual void SetUp() {
      // Code here will be called immediately after the constructor (right
      // before each test).
    }

    virtual void TearDown() {
      // Code here will be called immediately after each test (right
      // before the destructor).
    }
  
    // Objects declared here can be used by all tests in the test case for Foo.
  };

  TEST_F(GreeterTest, OneIsBiggerThanZero) {
    // You can break the test by using this line instead ... 
    // EXPECT_GT(0,1);
    EXPECT_GT(1,0);
  }

  TEST_F(GreeterTest, UsesAmplifierToShout) {

    MockAmplifier mock;
    EXPECT_CALL(mock, amplify("Hello pht!!\n")).Times(AtLeast(1));

    Greeter g("pht");
    g.shout(mock);
  }

  TEST_F(GreeterTest, CouldUseLocalFileIfItWanted) {
    cout << "For info, SRCDIR is " << SRCDIR << endl;

    char buffer[256];
    sprintf(buffer, "%s/tests/script1.lua", SRCDIR);
    ifstream f;
    f.open(buffer);
    EXPECT_TRUE(f.good());
  }

} // Namespace
