#ifndef _GAME_MODE_HPP_
#define _GAME_MODE_HPP_

class AbstractController;

/**
 * Compose Controler and View to handle a part of the game.
 */
class GameMode { 

  AbstractController * pController_;
  
public:

  GameMode(AbstractController * ipController) : pController_(ipController) {
  }

  /**
   * Update the state of the game based on 
   * the events received.
   *
   * @param iDelta nb of ms elapsed since last update.
   */
  void update_game(int iDelta);
  
};

#endif // _GAME_MODE_HPP_
