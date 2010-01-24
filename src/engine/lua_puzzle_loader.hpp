#ifndef _LUA_PUZZLE_LOADER_HPP_
#define _LUA_PUZZLE_LOADER_HPP_

#include "lua_state_holder.hpp"
#include "puzzle_loader.hpp"

#include <iostream>
using namespace std;

class ResourceResolverInterface;
//K struct lua_State;

/**
 * Puzzle loader from Lua file.
 *
 * It should be used in conjunction with a ResourceResolver
 * to find lua files.
 */
class LuaPuzzleLoader : 
  public LuaStateHolder, 
  public PuzzleLoader
{ 
public:
  LuaPuzzleLoader(CellFactory * ipFactory, 
		  ResourceResolverInterface & dep_resolver) : 

    LuaStateHolder(dep_resolver), 
    PuzzleLoader(ipFactory)
  {
    //K init_lua_state();
    cout << "ctor puzzle_loader" << endl;
    register_lua_functions();
  }

  ~LuaPuzzleLoader() {
    //K close_lua_state();
  }

  /**
   * Initialize a puzzle from a lua file.
   *
   * @param iFileName name of the puzzle file. The resource resolver will be used to locate the file.
   *   The file name should have extension, but no prefix (eg 'puzzle1.lua'.)
   * @param oPuzzle the puzzle to be initialized.
   * @return TODO(pht) error code in case something goes wrong
   */
  int load_puzzle_file(const char * iFileName, Puzzle * oPuzzle);

  void register_lua_functions();

private:

  // Resolver to look both for engine and puzzle lua files.
  //K ResourceResolverInterface * pResolver_;
  
  // Lua context
  //K  lua_State * pLuaState_;

  /**
   * Report an error with its state. Kills the program
   * TODO : make if throw instead.
   */
  // K void error(const char * fmt, ...);
  
  /**
   * Try and load an puzzle lua file, using the resource resolver to find it.
   */
  void load_lua_puzzle_file(const char * iFileName);

};

#endif // _LUA_PUZZLE_LOADER_HPP_
