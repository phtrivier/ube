/**
 * This is Free Software. See COPYING for information.
 */
#include "lua_puzzle_loader.hpp"

#include "puzzle.hpp"
#include "lua_command.hpp"

#include "common/logging.hpp"
#include "common/lua_helper.hpp"
#include "common/resource_resolver_interface.hpp"

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
  int res = (int) p_puzzle->moves().size() - 1;
  lua_pushinteger(i_p_lua_state, res);
  return 1;
}

int lua_puzzle_add_script(lua_State * i_p_lua_state) {
  Puzzle * p_puzzle = (Puzzle *) lua_touserdata(i_p_lua_state, 1);
  LuaPuzzleLoader * p_puzzle_loader = (LuaPuzzleLoader *) lua_touserdata(i_p_lua_state, 2);
  assert(p_puzzle_loader != NULL);

  int i = lua_tointeger(i_p_lua_state,3);
  int j = lua_tointeger(i_p_lua_state,4);
  int index = lua_tointeger(i_p_lua_state,5);
  
  LuaCommand * p_command = p_puzzle_loader->create_script(index, p_puzzle);
  p_puzzle->add_script(i,j,p_command);
  return 0;
}

int lua_puzzle_add_puzzle_move(lua_State * i_p_lua_state) {
  Puzzle * p_puzzle = (Puzzle *) lua_touserdata(i_p_lua_state, 1);
  int move_type = lua_tointeger(i_p_lua_state,2);
  p_puzzle->add_move(move_type);
  int res = (int) p_puzzle->moves().size() - 1;
  lua_pushinteger(i_p_lua_state, res);
  return 1;
}

int lua_puzzle_remove_move(lua_State * i_p_lua_state) {
  Puzzle * p_puzzle = (Puzzle *) lua_touserdata(i_p_lua_state, 1);
  int move_index = lua_tointeger(i_p_lua_state,2);
  assert(move_index < (int) p_puzzle->moves().size());
  p_puzzle->moves().erase( p_puzzle->moves().begin() + move_index);
  return 0;
}
  
int lua_puzzle_set_overlay(lua_State * i_p_lua_state) {
  Puzzle * p_puzzle = (Puzzle *) lua_touserdata(i_p_lua_state, 1);
  assert(p_puzzle != NULL);
  int i = lua_tointeger(i_p_lua_state,2);
  int j = lua_tointeger(i_p_lua_state,3);
  int type = lua_tointeger(i_p_lua_state,4);
  // FIXME(pht) : this is from outside, it should be checked
  p_puzzle->set_overlay(i,j,type);
  return 0;
}

void
LuaPuzzleLoader::register_lua_functions() 
{

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

  lua_pushcfunction(get_lua_state(), lua_puzzle_remove_move);
  lua_setglobal(get_lua_state(), "cpp_puzzle_remove_move");

  lua_pushcfunction(get_lua_state(), lua_puzzle_add_script);
  lua_setglobal(get_lua_state(), "cpp_puzzle_add_script");

  lua_pushcfunction(get_lua_state(), lua_puzzle_set_overlay);
  lua_setglobal(get_lua_state(), "cpp_puzzle_set_overlay");

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

  assert(oPuzzle != NULL);
  oPuzzle->clear();

  // The puzzle will be accessible to the script as 
  // a global "cpp_puzzle" variable.
  lua_pushlightuserdata(get_lua_state(), oPuzzle);
  lua_setglobal(get_lua_state(), "cpp_puzzle");

  load_lua_puzzle_file(iFileName);
  // TODO(pht) : propagate error codes
  return 0;
}

LuaCommand * 
LuaPuzzleLoader::create_script(int i_index, Puzzle * i_p_puzzle)
{
  LuaCommand * res = new LuaCommand(i_index, *i_p_puzzle, *this);
  // TODO : store the command somewhere to be 
  // able to delete it !
  return res;
}

void 
LuaPuzzleLoader::do_script(int i_index, Puzzle * o_p_puzzle)
{
  lua_getfield(get_lua_state(), LUA_GLOBALSINDEX, "do_script");
  lua_pushinteger(get_lua_state(), i_index);
  lua_pushlightuserdata(get_lua_state(), o_p_puzzle);
  lua_call(get_lua_state(), 2, 0);
}

void 
LuaPuzzleLoader::undo_script(int i_index, Puzzle * o_p_puzzle)
{
  lua_getfield(get_lua_state(), LUA_GLOBALSINDEX, "undo_script");
  lua_pushinteger(get_lua_state(), i_index);
  lua_pushlightuserdata(get_lua_state(), o_p_puzzle);
  lua_call(get_lua_state(), 2, 0);
}