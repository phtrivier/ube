#include "lua_puzzle_loader.hpp"

#include "common/logging.hpp"
#include "common/lua_helper.hpp"
#include "common/resource_resolver_interface.hpp"

#include "puzzle.hpp"

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <cstdlib>
#include <iostream>
using namespace std;

int lua_puzzle_set_dimensions(lua_State * ipLuaState) {
  Puzzle * pPuzzle = (Puzzle *) lua_touserdata(ipLuaState,1);
  int w = lua_tointeger(ipLuaState,2);
  int h = lua_tointeger(ipLuaState,3);
  // TODO(pht) : handle possible negative values here (we're not in the baricade yet !)
  pPuzzle->set_dimensions(w,h);
  return 0;
}

int lua_puzzle_loader_set_row(lua_State * ipLuaState) {
  Puzzle * pPuzzle = (Puzzle *) lua_touserdata(ipLuaState,1);
  LuaPuzzleLoader * pPuzzleLoader = (LuaPuzzleLoader *) lua_touserdata(ipLuaState,2);
  int i = lua_tointeger(ipLuaState,3);
  const char * row = lua_tostring(ipLuaState, 4);
  // TODO(pht) : handle possible bad chars in the row (untranslatable ones, we're not in the baricade yet !)
  pPuzzleLoader->set_row(i,pPuzzle,row);
  return 0;
}

int lua_puzzle_add_move(lua_State * i_p_lua_state) {
  Puzzle * p_puzzle = (Puzzle *) lua_touserdata(i_p_lua_state, 1);
  int move_type = lua_tointeger(i_p_lua_state,2);
  assert(p_puzzle != NULL);
  assert(move_type >= 0);
  p_puzzle->add_move(move_type);
  return 0;
}

void
LuaPuzzleLoader::register_lua_functions() 
{

  std::cout << "Registering in child version ... " << std::endl;

  LOG_D("lua") << "Registering functions for puzzle loader" << std::endl;

  // This puzzle loader will be accessible 
  // to the script as "cpp_puzzle_loader"
  // Fixme : this might onl
  lua_pushlightuserdata(get_lua_state(),this);
  lua_setglobal(get_lua_state(), "cpp_puzzle_loader");

  lua_pushcfunction(get_lua_state(), lua_puzzle_set_dimensions);
  lua_setglobal(get_lua_state(), "cpp_puzzle_set_dimensions");

  lua_pushcfunction(get_lua_state(), lua_puzzle_loader_set_row);
  lua_setglobal(get_lua_state(), "cpp_puzzle_loader_set_row");

  lua_pushcfunction(get_lua_state(), lua_puzzle_add_move);
  lua_setglobal(get_lua_state(), "cpp_puzzle_add_move");

  load_lua_engine_file("puzzle_lib.lua");

}

void
LuaPuzzleLoader::load_lua_puzzle_file(const char * iFileName)
{
  load_lua_file(get_resolver().get_puzzle_lua_file_name(iFileName));
}

int
LuaPuzzleLoader::load_puzzle_file(const char * iFileName, 
				  Puzzle * oPuzzle) {

  // The puzzle will be accessible to the script as 
  // a global "cpp_puzzle" variable.
  lua_pushlightuserdata(get_lua_state(), oPuzzle);
  lua_setglobal(get_lua_state(), "cpp_puzzle");

  load_lua_puzzle_file(iFileName);
  // TODO(pht) : propagate error codes
  return 0;
}
