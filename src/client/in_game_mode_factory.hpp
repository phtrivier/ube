#ifndef _IN_GAME_MODE_FACTORY_HPP_
#define _IN_GAME_MODE_FACTORY_HPP_

#include "engine/cell_factory.hpp"

#include <string>

#include <boost/shared_ptr.hpp>

class GameMode;
class ResourceResolverInterface;
class InGameRendererInterface;
class SdlController;
class InGameView;
class InGameModel;
class Puzzle;
class LuaPathFinder;

/**
 * Factory to create and initialize an InGameMode.
 */
class InGameModeFactory { 

public:

  // FIXME(pht) : shouldn't the renderer be a dependency, also ? 
  InGameModeFactory(ResourceResolverInterface & dep_resolver,
		    InGameRendererInterface & dep_renderer,
		    std::string puzzle_file_name) :
    dep_resolver_(dep_resolver),
    dep_renderer_(dep_renderer),
    puzzle_file_name_(puzzle_file_name),
    p_view_(NULL),
    p_model_(NULL),
    p_puzzle_(NULL),
    p_controller_(NULL),
    p_path_finder_(NULL)
  {
  }

  ~InGameModeFactory();

  int create_mode();

  boost::shared_ptr<GameMode> & get_mode();

  /**
   * Load a puzzle file by its file name.
   * @param i_file_name : puzzle name, with extension (eg "puzzle1.lua")
   */
  int load_puzzle(std::string & i_file_name);

private:

  ResourceResolverInterface & dep_resolver_;
  InGameRendererInterface & dep_renderer_;

  std::string puzzle_file_name_;

  InGameView * p_view_;
  InGameModel * p_model_;
  Puzzle * p_puzzle_;
  SdlController * p_controller_;
  LuaPathFinder * p_path_finder_;
  CellFactory cell_factory_;

  boost::shared_ptr<GameMode> mode_;

};

#endif // _IN_GAME_MODE_FACTORY_HPP_
