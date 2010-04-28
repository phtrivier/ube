/**
 * This is Free Software. See COPYING for information.
 */
#ifndef _IN_GAME_MODEL_LOADER_HPP_
#define _IN_GAME_MODEL_LOADER_HPP_

#include "engine/cell_factory.hpp"
#include "engine/lua_puzzle_loader.hpp"

class InGameModel;

/**
 * Loader for InGameModel
 */
class InGameModelLoader : 
  public LuaPuzzleLoader
{ 
public:
  
  InGameModelLoader(ResourceResolverInterface & dep_resolver):
    LuaPuzzleLoader(&cell_factory_, dep_resolver)
  {
    
  }

  /**
   * Load a model from a puzzle file.
   */
  int load_puzzle_file(const char * i_file_name, InGameModel & o_model);

private:

  CellFactory cell_factory_;
  
};

#endif // _IN_GAME_MODEL_LOADER_HPP_
