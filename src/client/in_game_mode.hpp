/**
 * This is Free Software. See COPYING for information.
 */
#ifndef _IN_GAME_MODE_HPP_
#define _IN_GAME_MODE_HPP_

#include "game_mode.hpp"
#include "in_game_model.hpp"

#include "mvc/controller_interface.hpp"
#include "mvc/view_interface.hpp"

/**
 * GameMode for the main gameplay.
 */
class InGameMode : 
  public GameMode 
{ 
public:

  InGameMode(ControllerInterface & dep_controller, 
	     ViewInterface & dep_view, 
	     InGameModel & dep_model):
    GameMode(&dep_controller, &dep_view),
    dep_model_(dep_model)
  {
  }

  void update_game(int iDelta);
 
private:
  InGameModel & dep_model_;

};

#endif // _IN_GAME_MODE_HPP_