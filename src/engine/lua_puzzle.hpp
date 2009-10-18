#include "puzzle.hpp"
#include "lua_helper.hpp"

// At the cost of writing this kinds
// of silly wrapper functions, 
// you can make pretty much any function 
// of the puzzle class available to lua...
int lua_puzzle_set_name(lua_State * L);
