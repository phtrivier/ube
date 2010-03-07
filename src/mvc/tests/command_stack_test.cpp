#include <command_stack.hpp>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

namespace {
  class CommandStackTest : public ::testing::Test {
  protected:
    CommandStackTest() {
    }

    virtual ~CommandStackTest() {
    }

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }

  };

  TEST_F(CommandStackTest, DoesNothingWhenEmpty) {
    ASSERT_TRUE(true);
  }

} // Namespace
