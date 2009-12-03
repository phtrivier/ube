#ifndef _GAME_MODE_HPP_
#define _GAME_MODE_HPP_

#include "abstract_game_mode.hpp"

class AbstractController;
class AbstractView;
class AbstractObserver;

/**
 * Compose Controler and View to handle a part of the game.
 */
class GameMode : public AbstractGameMode { 

  AbstractController * pController_;
  AbstractView * pView_;

public:

  GameMode(AbstractController * ipController, AbstractView * ipView) : AbstractGameMode(), pController_(ipController), pView_(ipView) {
  }

  void update_game(int iDelta);

  void render_game();

  void add_observer(AbstractObserver *o);
  
};

#endif // _GAME_MODE_HPP_
