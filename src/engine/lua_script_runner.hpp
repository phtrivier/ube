#ifndef _LUA_SCRIPT_RUNNER_HPP_
#define _LUA_SCRIPT_RUNNER_HPP_

#include <stdio.h>
#include <string.h>
#include <cstdlib>

#include <iostream>
#include <string>

#include "lua_helper.hpp"
class Puzzle;

#include "puzzle.hpp"
#include "lua_puzzle.hpp"

class LuaScriptRunner {
  lua_State *L;
public:
  LuaScriptRunner() {
    L = lua_open();
    luaL_openlibs(L);

    // TODO : Load a standard lua file (story.lua)
    try_and_load_file("lua/story_lib.lua");
    // TODO : Register functions from the "puzzle" lib
    lua_pushcfunction(L, lua_puzzle_set_name);
    lua_setglobal(L, "puzzle_set_name");
  }
  ~LuaScriptRunner() {
    lua_close(L);
  }
  int error(const char *fmt, ...);
  void try_and_load_file(std::string file_name);
  void visit_cell(std::string cell_name, Puzzle & iPuzzle);
};

#endif // _LUA_SCRIPT_RUNNER_HPP_
