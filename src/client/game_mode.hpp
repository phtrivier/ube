/**
 * This is Free Software. See COPYING for information.
 */
#ifndef _GAME_MODE_HPP_
#define _GAME_MODE_HPP_

#include "game_mode_interface.hpp"

class ControllerInterface;
class ViewInterface;
class ObserverInterface;

/**
 * Compose Controler and View to handle a part of the game.
 */
class GameMode : 
  public GameModeInterface 
{ 

public:

  GameMode(ControllerInterface * ipController, 
	   ViewInterface * ipView) : 
    GameModeInterface(), 
    pController_(ipController), 
    pView_(ipView) {
  }

  void update_game(int iDelta);

  void render_game();

  void add_observer(ObserverInterface *o);

private:
  ControllerInterface * pController_;
  ViewInterface * pView_;
  
};

#endif // _GAME_MODE_HPP_