#include "lua_script_runner.hpp"

#include <stdio.h>
#include <string.h>
#include <cstdlib>
#include <iostream>
using namespace std;

LuaScriptRunner::LuaScriptRunner(std::string iLua_base_prefix) : lua_base_prefix(iLua_base_prefix) {
  L = lua_open();
  luaL_openlibs(L);
  try_and_load_file("story_lib.lua", lua_base_prefix);
  lua_pushcfunction(L, lua_puzzle_set_name);
  lua_setglobal(L, "puzzle_set_name");
}

LuaScriptRunner::~LuaScriptRunner() {
  lua_close(L);
}

int LuaScriptRunner::error (const char *fmt, ...) {
  va_list argp;
  va_start(argp, fmt);
  vfprintf(stderr, fmt, argp);
  va_end(argp);
  lua_close(L);
  exit(-1);
}

void LuaScriptRunner::try_and_load_file(std::string file_name,std::string prefix) {

  std::string absolute_file_name = prefix;
  absolute_file_name.append("/");
  absolute_file_name.append(file_name);
  
  //  sprintf(buffer, "%s/%s", absolute_file_name,file_name.c_str());
  if (luaL_loadfile(L, absolute_file_name.c_str()) || lua_pcall(L, 0, 0, 0))
    error("cannot run configuration file: %s",
	  lua_tostring(L, -1));
}

void LuaScriptRunner::visit_cell(std::string cell_name, Puzzle & iPuzzle) {
  lua_getglobal(L, "story_visit_cell");
  lua_pushstring(L, cell_name.c_str());
  lua_pushlightuserdata(L, &iPuzzle);
  if (lua_pcall(L,2,0,0) != 0) {
    error("could not run script for cell:%s",lua_tostring(L,-1));
  }
}

