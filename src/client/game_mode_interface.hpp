#ifndef _GAME_MODE_INTERFACE_HPP_
#define _GAME_MODE_INTERFACE_HPP_

#include "observable.hpp"

/**
 * Base class for game modes
 */
class GameModeInterface : public Observable { 

public:

  GameModeInterface() : Observable() {
  }

  virtual ~GameModeInterface() {
  }

  /**
   * Update the state of the game based on 
   * the events received.
   *
   * @param iDelta nb of ms elapsed since last update.
   */
  virtual void update_game(int iDelta) = 0;

  /**
   * Renders the current state of the game.
   */
  virtual void render_game() = 0;

};

#endif // _GAME_MODE_INTERFACE_HPP_
