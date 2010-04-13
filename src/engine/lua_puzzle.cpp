/**
 * This is Free Software. See COPYING for information.
 */
#include "lua_puzzle.hpp"

// So if the function is not called
int lua_puzzle_set_name(lua_State * L) {
  Puzzle * a_ptr_puzzle = (Puzzle *) lua_touserdata(L,1);
  const char * name = lua_tostring(L,2);
  a_ptr_puzzle->set_name(name);
  return 0;
}