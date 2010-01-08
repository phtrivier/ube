#ifndef _IN_GAME_VIEW_HPP_
#define _IN_GAME_VIEW_HPP_

#include "view_interface.hpp"

class Puzzle;
class InGameModel;
class InGameRendererInterface;

/**
 * View for the main screen of the game.
 */
class InGameView :
  public ViewInterface
{ 

public:

  InGameView(InGameRendererInterface & dep_renderer, InGameModel & dep_model) :
    ViewInterface(),
    dep_renderer_(dep_renderer),
    dep_model_(dep_model)
  {
  }

  ~InGameView() {
  }

  void render_game();

  /**
   * Render the content of a puzzle to the screen.
   */
  void render_puzzle(const Puzzle & i_puzzle);
  
private:

  // Dependencies
  InGameRendererInterface & dep_renderer_;
  InGameModel & dep_model_;
};

#endif // _IN_GAME_VIEW_HPP_
