#include "lua_command.hpp"

#include "engine/puzzle.hpp"
#include "engine/tests/mock_script_runner.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <stdexcept>
using namespace std;

namespace {
  class LuaCommandTest : public ::testing::Test {
  protected:
    LuaCommandTest() {
    }

    virtual ~LuaCommandTest() {
    }

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }

  };

  TEST_F(LuaCommandTest, DoesSomethingCool) {
    MockScriptRunner runner;
    Puzzle p;
    LuaCommand c(1, p, runner);
    EXPECT_CALL(runner, do_script(1, &p)).Times(1);
    EXPECT_CALL(runner, undo_script(1, &p)).Times(1);
    c.execute();
    c.undo();
  }

} // Namespace
