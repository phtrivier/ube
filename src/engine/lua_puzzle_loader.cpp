#include "lua_puzzle_loader.hpp"

#include "common/lua_helper.hpp"
#include "common/abstract_resource_resolver.hpp"

#include "puzzle.hpp"

#include <stdio.h>
#include <string.h>
#include <cstdlib>
#include <iostream>
using namespace std;

#include "boost/format.hpp"
using boost::format;

void
LuaPuzzleLoader::close_lua_state()
{
  lua_close(pLuaState_);
}

int lua_puzzle_set_dimensions(lua_State * ipLuaState) {
  Puzzle * pPuzzle = (Puzzle *) lua_touserdata(ipLuaState,1);
  int w = lua_tointeger(ipLuaState,2);
  int h = lua_tointeger(ipLuaState,3);
  pPuzzle->set_dimensions(w,h);
  return 0;
}

int lua_puzzle_loader_set_row(lua_State * ipLuaState) {
  Puzzle * pPuzzle = (Puzzle *) lua_touserdata(ipLuaState,1);
  LuaPuzzleLoader * pPuzzleLoader = (LuaPuzzleLoader *) lua_touserdata(ipLuaState,2);
  int i = lua_tointeger(ipLuaState,3);
  const char * row = lua_tostring(ipLuaState, 4);
  pPuzzleLoader->set_row(i,pPuzzle,row);
  return 0;
}

void 
LuaPuzzleLoader::init_lua_state() 
{
  pLuaState_ = lua_open();
  luaL_openlibs(pLuaState_);

  // This puzzle loader will be accessible to the script as "cpp_puzzle_loader"
  // Fixme : this might onl
  lua_pushlightuserdata(pLuaState_,this);
  lua_setglobal(pLuaState_, "cpp_puzzle_loader");

  lua_pushcfunction(pLuaState_, lua_puzzle_set_dimensions);
  lua_setglobal(pLuaState_, "cpp_puzzle_set_dimensions");

  lua_pushcfunction(pLuaState_, lua_puzzle_loader_set_row);
  lua_setglobal(pLuaState_, "cpp_puzzle_loader_set_row");

  load_lua_engine_file("puzzle_lib.lua");

}

// Might not be very usefull, actually ... 
void
LuaPuzzleLoader::error(const char * fmt, ...)
{
  // TODO(pht) : throw instead of killing
  // The problem is formatting the message ... 
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
    throw runtime_error(str(format("cannot run lua file: %1%") % lua_tostring(pLuaState_, -1)));
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
