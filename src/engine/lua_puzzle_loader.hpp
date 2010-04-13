/**
 * This is Free Software. See COPYING for information.
 */
#ifndef _LUA_PUZZLE_LOADER_HPP_
#define _LUA_PUZZLE_LOADER_HPP_

#include "lua_state_holder.hpp"
#include "puzzle_loader.hpp"

#include "script_runner_interface.hpp"

#include <iostream>
using namespace std;

class ResourceResolverInterface;
class LuaCommand;
class Puzzle;

/**
 * Puzzle loader from Lua file.
 *
 * It should be used in conjunction with a ResourceResolver
 * to find lua files.
 */
class LuaPuzzleLoader :
  public ScriptRunnerInterface,
  public LuaStateHolder, 
  public PuzzleLoader
{ 
public:
  LuaPuzzleLoader(CellFactory * ipFactory, 
		  ResourceResolverInterface & dep_resolver) : 
    ScriptRunnerInterface(),
    LuaStateHolder(dep_resolver), 
    PuzzleLoader(ipFactory)
  {
    register_lua_functions();
  }

  ~LuaPuzzleLoader() {
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

  /**
   * Creates a script command to be used on a puzzle.
   * The loader should retain ownership of the command.
   */
  LuaCommand * create_script(int index, Puzzle * i_p_puzzle);

  void do_script(int i_index, Puzzle * o_p_puzzle);

  void undo_script(int i_index, Puzzle * o_p_puzzle);

private:
 
  /**
   * Try and load an puzzle lua file, using the resource resolver to find it.
   */
  void load_lua_puzzle_file(const char * iFileName);

};

#endif // _LUA_PUZZLE_LOADER_HPP_