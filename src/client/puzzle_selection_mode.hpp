#ifndef _PUZZLE_SELECTION_MODE_HPP_
#define _PUZZLE_SELECTION_MODE_HPP_

#include "game_mode.hpp"
#include "puzzle_selection_model.hpp"

#include "mvc/controller_interface.hpp"
#include "mvc/view_interface.hpp"

// Note that it looks A LOT like the other mode code .. 

/**
 * GameMode for the puzzle selection
 */
class PuzzleSelectionMode :
  public GameMode
{ 

public:

    PuzzleSelectionMode(ControllerInterface & dep_controller, 
	       ViewInterface & dep_view, 
	       PuzzleSelectionModel & dep_model):
    GameMode(&dep_controller, &dep_view),
    dep_model_(dep_model)
  {
  }

  void update_game(int iDelta);

private:

  PuzzleSelectionModel & dep_model_;

};

#endif // _PUZZLE_SELECTION_MODE_HPP_
