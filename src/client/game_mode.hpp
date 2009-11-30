#ifndef _GAME_MODE_HPP_
#define _GAME_MODE_HPP_

class AbstractController;
class AbstractView;

/**
 * Compose Controler and View to handle a part of the game.
 */
class GameMode { 

  AbstractController * pController_;
  AbstractView * pView_;

public:

  GameMode(AbstractController * ipController, AbstractView * ipView) : pController_(ipController), pView_(ipView) {
  }

  /**
   * Update the state of the game based on 
   * the events received.
   *
   * @param iDelta nb of ms elapsed since last update.
   */
  void update_game(int iDelta);

  /**
   * Renders the current state of the game.
   */
  void render_game();
  
};

#endif // _GAME_MODE_HPP_
