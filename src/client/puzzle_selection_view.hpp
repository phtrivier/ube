#ifndef _PUZZLE_SELECTION_VIEW_HPP_
#define _PUZZLE_SELECTION_VIEW_HPP_

#include "mvc/view_interface.hpp"

class PuzzleSelectionRendererInterface;
class PuzzleSelectionModel;
class ControllerInterface;

/**
 * View for the puzzle selection screen
 */
class PuzzleSelectionView :
  public ViewInterface
{ 
  
public:
  
  PuzzleSelectionView(PuzzleSelectionRendererInterface & dep_renderer,
		      PuzzleSelectionModel & dep_model,
		      ControllerInterface & dep_controller) :
    ViewInterface(),
    dep_renderer_(dep_renderer),
    dep_model_(dep_model),
    dep_controller_(dep_controller)
  {
  }

  ~PuzzleSelectionView() {
  }

  void render_game();

  void handle_event(int iEventCode);

private:

  PuzzleSelectionRendererInterface & dep_renderer_;
  PuzzleSelectionModel & dep_model_;
  ControllerInterface & dep_controller_;

};

#endif // _PUZZLE_SELECTION_VIEW_HPP_
