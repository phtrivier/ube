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

#include "lua_puzzle_functions.hpp"

#define REGISTER_LUA_FN(lua_fn, cpp_fn)   lua_pushcfunction(get_lua_state(), lua_fn); \
  lua_setglobal(get_lua_state(), cpp_fn);

void
LuaPuzzleLoader::register_lua_functions() 
{

  LOG_D("lua") << "Registering functions for puzzle loader" << std::endl;

  // This puzzle loader will be accessible 
  // to the script as "cpp_puzzle_loader"
  // Fixme : this might onl
  lua_pushlightuserdata(get_lua_state(),this);
  lua_setglobal(get_lua_state(), "cpp_puzzle_loader");

  REGISTER_LUA_FN(lua_puzzle_set_dimensions, "cpp_puzzle_set_dimensions");

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

  lua_pushcfunction(get_lua_state(), lua_puzzle_set_start_message);
  lua_setglobal(get_lua_state(), "cpp_puzzle_set_start_message");

  REGISTER_LUA_FN(lua_puzzle_set_end_message, "cpp_puzzle_set_end_message");

  REGISTER_LUA_FN(lua_puzzle_set_script_message, "cpp_puzzle_set_script_message");

  load_lua_engine_file("puzzle_lib.lua");

}

void
LuaPuzzleLoader::load_lua_puzzle_file(const char * iFileName)
{
  load_lua_file(get_resolver().get_puzzle_lua_file_name(iFileName));
}

int
LuaPuzzleLoader::load_puzzle_file(const char * i_file_name, 
				  Puzzle & o_puzzle) {

  o_puzzle.clear();

  // The puzzle will be accessible to the script as 
  // a global "cpp_puzzle" variable.
  lua_pushlightuserdata(get_lua_state(), &o_puzzle);
  lua_setglobal(get_lua_state(), "cpp_puzzle");

  load_lua_puzzle_file(i_file_name);
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
