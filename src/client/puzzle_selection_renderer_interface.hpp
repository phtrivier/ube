#ifndef _PUZZLE_SELECTION_RENDERER_INTERFACE_HPP_
#define _PUZZLE_SELECTION_RENDERER_INTERFACE_HPP_

#include "selection_renderer_interface.hpp"

/**
 * Renderer for puzzle selection.
 */
class PuzzleSelectionRendererInterface : 
  public SelectionRendererInterface
{ 
public:

  PuzzleSelectionRendererInterface() :
    SelectionRendererInterface() {
  }

  ~PuzzleSelectionRendererInterface() {
  }

  // Just a try, without extending anything
  virtual bool is_on_back_button(int i_x, int i_y) = 0;
};

#endif // _PUZZLE_SELECTION_RENDERER_INTERFACE_HPP_
