#ifndef _PUZZLE_SELECTION_RENDERER_INTERFACE_HPP_
#define _PUZZLE_SELECTION_RENDERER_INTERFACE_HPP_


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
  virtual void is_on_back_button(int i_x, int i_y) = 0;
};

#endif // _PUZZLE_SELECTION_RENDERER_INTERFACE_HPP_
