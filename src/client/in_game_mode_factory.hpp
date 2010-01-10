#ifndef _IN_GAME_MODE_FACTORY_HPP_
#define _IN_GAME_MODE_FACTORY_HPP_

#include <boost/shared_ptr.hpp>
class GameMode;
class ResourceResolverInterface;
class InGameRendererInterface;
class SdlController;
class InGameView;
class InGameModel;
class Puzzle;

/**
 * Factory to create and initialize an InGameMode.
 */
class InGameModeFactory { 

public:

  // FIXME(pht) : shouldn't the renderer be a dependency, also ? 
  InGameModeFactory(ResourceResolverInterface & dep_resolver,
		    InGameRendererInterface & dep_renderer) :
    dep_resolver_(dep_resolver),
    dep_renderer_(dep_renderer)
  {
  }

  ~InGameModeFactory();

  int create_mode();

  boost::shared_ptr<GameMode> & get_mode();

private:

  ResourceResolverInterface & dep_resolver_;
  InGameRendererInterface & dep_renderer_;

  SdlController * p_controller_;
  InGameView * p_view_;
  InGameModel * p_model_;
  Puzzle * p_puzzle_;

  boost::shared_ptr<GameMode> mode_;

};

#endif // _IN_GAME_MODE_FACTORY_HPP_
