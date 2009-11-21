#include "lua_puzzle_loader.hpp"
#include "lua_helper.hpp"
#include "puzzle.hpp"
#include "resource_resolver.hpp"

#include <stdio.h>
#include <string.h>
#include <cstdlib>
#include <iostream>
using namespace std;

void
LuaPuzzleLoader::close_lua_state()
{
  lua_close(pLuaState_);
}

int lua_puzzle_set_dimensions(lua_State * ipLuaState) {
  //  Puzzle * a_ptr_puzzle = (Puzzle *) lua_touserdata(L,1);
  Puzzle * pPuzzle = (Puzzle *) lua_touserdata(ipLuaState,1);
  int w = lua_tointeger(ipLuaState,2);
  int h = lua_tointeger(ipLuaState,3);
  pPuzzle->set_dimensions(w,h);

  return 0;
}

void 
LuaPuzzleLoader::init_lua_state() 
{
  pLuaState_ = lua_open();
  luaL_openlibs(pLuaState_);

  lua_pushcfunction(pLuaState_, lua_puzzle_set_dimensions);
  lua_setglobal(pLuaState_, "lua_puzzle_set_dimensions");

  /* LEFT FOR THE MOMENT
  lua_pushcfunction(pLuaState_, lua_puzzle_loader_set_row);
  lua_setglobal(pLuaState, "lua_puzzle_loader_set_row");
  */

  load_lua_engine_file("puzzle_lib.lua");

}

void
LuaPuzzleLoader::error(const char * fmt, ...)
{
  // TODO(pht) : throw instead of killing
  va_list argp;
  va_start(argp, fmt);
  vfprintf(stderr, fmt, argp);
  va_end(argp);
  lua_close(pLuaState_);
  exit(-1);
}

void
LuaPuzzleLoader::load_lua_file(std::string iFileName)
{
  if (luaL_loadfile(pLuaState_, iFileName.c_str()) || 
      lua_pcall(pLuaState_, 0, 0, 0)) {
    error("cannot run lua file: %s",
	  lua_tostring(pLuaState_, -1));
  }
}

void
LuaPuzzleLoader::load_lua_engine_file(const char * iFileName)
{
  load_lua_file(pResolver_->get_engine_lua_file_name(iFileName));
 
}

void
LuaPuzzleLoader::load_lua_puzzle_file(const char * iFileName)
{
  load_lua_file(pResolver_->get_puzzle_lua_file_name(iFileName));
}

void 
LuaPuzzleLoader::load_puzzle_file(const char * iFileName, 
				  Puzzle * oPuzzle) {

  // The puzzle will be accessible to the script as 
  // a global "cpp_puzzle" variable.
  lua_pushlightuserdata(pLuaState_, oPuzzle);
  lua_setglobal(pLuaState_, "cpp_puzzle");
  load_lua_puzzle_file(iFileName);
}
