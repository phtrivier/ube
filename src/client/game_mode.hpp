#ifndef _GAME_MODE_HPP_
#define _GAME_MODE_HPP_

#include "game_mode_interface.hpp"

class AbstractController;
class ViewInterface;
class AbstractObserver;

/**
 * Compose Controler and View to handle a part of the game.
 */
class GameMode : public GameModeInterface { 

  AbstractController * pController_;
  ViewInterface * pView_;

public:

  GameMode(AbstractController * ipController, ViewInterface * ipView) : 
    GameModeInterface(), 
    pController_(ipController), 
    pView_(ipView) {
  }

  void update_game(int iDelta);

  void render_game();

  void add_observer(AbstractObserver *o);
  
};

#endif // _GAME_MODE_HPP_
