/**
 * This is Free Software. See COPYING for information.
 */
#ifndef _LUA_PATH_FINDER_HPP_
#define _LUA_PATH_FINDER_HPP_

#include "lua_state_holder.hpp"
#include "path_finder_interface.hpp"

/**
 * PathFinder using Lua for computations.
 */
class LuaPathFinder :
  public PathFinderInterface,
  public LuaStateHolder
{

public:

  LuaPathFinder(ResourceResolverInterface & dep_resolver) :
    PathFinderInterface(),
    LuaStateHolder(dep_resolver)
  {
    register_path_finding_lua_function();
  }
  
  ~LuaPathFinder() {
  }

  int find_path(Puzzle & o_puzzle, 
		int i_i0, int i_j0, 
		int i_i1, int i_j1, 
		int move_type);

private:

  void register_path_finding_lua_function();
  
};

#endif // _LUA_PATH_FINDER_HPP_
