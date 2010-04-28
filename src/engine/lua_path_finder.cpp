/**
 * This is Free Software. See COPYING for information.
 */
#include "lua_path_finder.hpp"

#include "common/lua_helper.hpp"

#include "cell.hpp"
#include "puzzle.hpp"

#include <assert.h>

int
LuaPathFinder::find_path(Puzzle & o_puzzle, 
			 int i_i0, int i_j0, 
			 int i_i1, int i_j1, 
			 int move_type)
{

  int res = -1;

  if (i_i0 < 0 
      || i_j0 < 0 
      || i_i1 >= o_puzzle.get_h() 
      || i_j1 >= o_puzzle.get_w()) {
    return -1;
  }

  // find_path should return 0 if no path is found, 1 if 
  // a path is found, and -1 in case of an error.
  // That is, the same as this function, like. 
  // Also, the puzzle state should have been changed to
  // reflect the positions of the new cells in 
  // the path.
  lua_getglobal(get_lua_state(), "find_path");
  lua_pushlightuserdata(get_lua_state(), &o_puzzle);
  lua_pushnumber(get_lua_state(), i_i0);
  lua_pushnumber(get_lua_state(), i_j0);
  lua_pushnumber(get_lua_state(), i_i1);
  lua_pushnumber(get_lua_state(), i_j1);
  lua_pushnumber(get_lua_state(), move_type);

  if (lua_pcall(get_lua_state(), 6, 1, 0) == 0) {
    /* retrieve result */
    if (lua_isnumber(get_lua_state(), -1)) {
      res = lua_tonumber(get_lua_state(), -1);
      lua_pop(get_lua_state(), 1);  /* pop returned value */
    }
  } 
  
  return res;
}

/**
 * Is a cell in a puzzle reachable ? 
 * 
 */
int lua_is_cell_reachable(lua_State * i_p_state) 
{
  Puzzle * p_puzzle = (Puzzle *) lua_touserdata(i_p_state,1);
  int i = lua_tointeger(i_p_state, 2);
  int j = lua_tointeger(i_p_state, 3);

  bool res = false;

  if (p_puzzle->is_valid_position(i,j)) {
    Cell * cell = p_puzzle->get_cell_at(i,j);
    // Fixme : improve this, some cells
    // will be empty but not walkable ;)
    res = !cell->is_empty();
  }

  lua_pushboolean(i_p_state, res);
  return 1;
}

/**
 * Mark that a cell was found in the previous path.
 */
int lua_mark_cell_in_path(lua_State * i_p_state)
{
  Puzzle * p_puzzle = (Puzzle *) lua_touserdata(i_p_state,1);
  int i = lua_tointeger(i_p_state, 2);
  int j = lua_tointeger(i_p_state, 3);
  
  assert(p_puzzle->is_valid_position(i,j));
  p_puzzle->mark_in_path(i,j);

  return 0;
}

void
LuaPathFinder::register_path_finding_lua_function()
{

  lua_pushcfunction(get_lua_state(), lua_mark_cell_in_path);
  lua_setglobal(get_lua_state(), "cpp_mark_cell_in_path");

  lua_pushcfunction(get_lua_state(), lua_is_cell_reachable);
  lua_setglobal(get_lua_state(), "cpp_is_cell_reachable");

  load_lua_engine_file("path_finder_lib.lua");
}
