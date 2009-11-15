#include <lua_script_runner.hpp>
#include <puzzle.hpp>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

namespace {

  class LuaScriptRunnerTest : public ::testing::Test {
  };

  /* Puzzle class will change, and I don't really need a name that much.
  TEST_F(LuaScriptRunnerTest, CanRunScriptOnPuzzle) {
    // Create a scriptRunner (Note 
    std::string prefix = SRCDIR;
    prefix.append("/lua");
    LuaScriptRunner runner(prefix);
    // Load a known story file
    runner.try_and_load_file("tests/lua/lua_script_runner_test_story1.lua",SRCDIR);
    // Create a puzzle with a given name
    Puzzle p("foo");
    // Check the name
    EXPECT_EQ("foo", p.get_name());
    // Visit cells on the runner    runner.visit_cell(
    runner.visit_cell("toto",p);
    EXPECT_EQ("Baz", p.get_name());
    runner.visit_cell("tata",p);
    runner.visit_cell("tutu",p);
    EXPECT_EQ("Bar", p.get_name());
    // Check the name of the puzzle changed
  }
  */
}

