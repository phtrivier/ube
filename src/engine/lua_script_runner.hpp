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
  std::string lua_base_prefix;
public:
  LuaScriptRunner(std::string iLua_base_prefix=LUADIR); 
  ~LuaScriptRunner();
  int error(const char *fmt, ...);
  void try_and_load_file(std::string file_name, std::string prefix=LUADIR);
  void visit_cell(std::string cell_name, Puzzle & iPuzzle);
};

#endif // _LUA_SCRIPT_RUNNER_HPP_
