#ifndef _ABSTRACT_GAME_MODE_HPP_
#define _ABSTRACT_GAME_MODE_HPP_

#include "observable.hpp"

/**
 * Base class for game modes
 */
class AbstractGameMode : public Observable { 

public:

  AbstractGameMode() : Observable() {
  }

  virtual ~AbstractGameMode() {
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

#endif // _ABSTRACT_GAME_MODE_HPP_
