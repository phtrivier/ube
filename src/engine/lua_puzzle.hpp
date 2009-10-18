#include "puzzle.hpp"
#include "lua_helper.hpp"

// At the cost of writing this kinds
// of silly wrapper functions, 
// you can make pretty much any function 
// of the puzzle class available to lua...
static int lua_puzzle_set_name(lua_State * L) {
  Puzzle * a_ptr_puzzle = (Puzzle *) lua_touserdata(L,1);
  const char * name = lua_tostring(L,2);
  a_ptr_puzzle->set_name(name);
  return 0;
}

