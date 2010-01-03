#ifndef _GAME_MODE_HPP_
#define _GAME_MODE_HPP_

#include "game_mode_interface.hpp"

class ControllerInterface;
class ViewInterface;
class ObserverInterface;

/**
 * Compose Controler and View to handle a part of the game.
 */
class GameMode : public GameModeInterface { 

  ControllerInterface * pController_;
  ViewInterface * pView_;

public:

  GameMode(ControllerInterface * ipController, ViewInterface * ipView) : 
    GameModeInterface(), 
    pController_(ipController), 
    pView_(ipView) {
  }

  void update_game(int iDelta);

  void render_game();

  void add_observer(ObserverInterface *o);
  
};

#endif // _GAME_MODE_HPP_
