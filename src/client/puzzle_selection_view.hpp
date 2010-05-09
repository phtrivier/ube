/**
 * This is Free Software. See COPYING for information.
 */
#ifndef _PUZZLE_SELECTION_VIEW_HPP_
#define _PUZZLE_SELECTION_VIEW_HPP_

#include "puzzle_selection_renderer_interface.hpp"
#include "selection_view.hpp"
#include "puzzle_selection_model.hpp"

class ControllerInterface;

/**
 * View for the puzzle selection screen
 */
class PuzzleSelectionView :
  public SelectionView
{ 
  
public:
  
  PuzzleSelectionView(PuzzleSelectionRendererInterface & dep_renderer,
		      PuzzleSelectionModel & dep_model,
		      ControllerInterface & dep_controller) :
    SelectionView(dep_renderer, dep_model, dep_controller),
    dep_puzzle_selection_renderer_(dep_renderer)
  {
  }

  ~PuzzleSelectionView() {
  }

  void render_game();

  void handle_event(int iEventCode);

protected:

  PuzzleSelectionRendererInterface & dep_puzzle_selection_renderer_;

};

#endif // _PUZZLE_SELECTION_VIEW_HPP_
