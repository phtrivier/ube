#ifndef _LUA_PUZZLE_LOADER_HPP_
#define _LUA_PUZZLE_LOADER_HPP_

#include "puzzle_loader.hpp"
#include <string>

class AbstractResourceResolver;
struct lua_State;

/**
 * Puzzle loader from Lua file.
 *
 * It should be used in conjunction with a ResourceResolver
 * to find lua files.
 */
class LuaPuzzleLoader : public PuzzleLoader { 

  // Resolver to look both for engine and puzzle lua files.
  AbstractResourceResolver * pResolver_;
  
  // Lua context
  lua_State * pLuaState_;

  /**
   * Report an error with its state. Kills the program
   * TODO : make if throw instead.
   */
  void error(const char * fmt, ...);
  
  /**
   * Try and load an engine lua file, using the resource resolver to find it.
   */
  void load_lua_engine_file(const char * iFileName);

  /**
   * Try and load an puzzle lua file, using the resource resolver to find it.
   */
  void load_lua_puzzle_file(const char * iFileName);

  /**
   * Loads a lua file with its absolute path.
   */
  void load_lua_file(std::string iFilePath);

  void init_lua_state();
  void close_lua_state();

public:
  LuaPuzzleLoader(CellFactory * ipFactory, AbstractResourceResolver * ipResolver) : PuzzleLoader(ipFactory), 
										    pResolver_(ipResolver) {
    init_lua_state();
  }

  ~LuaPuzzleLoader() {
    close_lua_state();
  }

  /**
   * Initialize a puzzle from a lua file.
   *
   * @param iFileName name of the puzzle file. The resource resolver will be used to locate the file.
   *   The file name should have extension, but no prefix (eg 'puzzle1.lua'.)
   * @param oPuzzle the puzzle to be initialized.
   */
  void load_puzzle_file(const char * iFileName, Puzzle * oPuzzle);

};

#endif // _LUA_PUZZLE_LOADER_HPP_
