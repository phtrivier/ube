#ifndef _PUZZLE_SELECTION_RENDERER_INTERFACE_HPP_
#define _PUZZLE_SELECTION_RENDERER_INTERFACE_HPP_

#include "renderer_interface.hpp"

#include <string>

/**
 * Class that knows how to render a list of puzzles for selection
 */
class PuzzleSelectionRendererInterface :
  public RendererInterface
{ 

public:

  PuzzleSelectionRendererInterface() :
    RendererInterface() {
  }

  virtual ~PuzzleSelectionRendererInterface() {
  }

  virtual void render_puzzle_name(std::string & i_name, int i_index) = 0;
  
};

#endif // _PUZZLE_SELECTION_RENDERER_INTERFACE_HPP_
