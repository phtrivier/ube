/**
 * This is Free Software. See COPYING for information.
 */
#ifndef _SELECTION_RENDERER_INTERFACE_HPP_
#define _SELECTION_RENDERER_INTERFACE_HPP_

#include "renderer_interface.hpp"

#include <string>

/**
 * Class that knows how to render a list of puzzles for selection
 */
class SelectionRendererInterface :
  public RendererInterface
{ 

public:

  SelectionRendererInterface() :
    RendererInterface() {
  }

  virtual ~SelectionRendererInterface() {
  }

  virtual void render_item_name(std::string & i_name, int i_index) = 0;

  virtual int get_mouse_position_as_item_index(int i_x, int i_y) = 0;

  virtual void highlight_item_name(int i_index) = 0;
  
};

#endif // _SELECTION_RENDERER_INTERFACE_HPP_
