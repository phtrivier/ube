#ifndef _SELECTION_VIEW_HPP_
#define _SELECTION_VIEW_HPP_

#include "mvc/view_interface.hpp"

class SelectionModel;
class SelectionRendererInterface;
class ControllerInterface;

/**
 * Generic view for screens where something has to be selected in a list
 */
class SelectionView : 
  public ViewInterface
{ 

public:

  SelectionView(SelectionRendererInterface & dep_renderer,
		SelectionModel & dep_model,
		ControllerInterface & dep_controller):
    ViewInterface(),
    dep_renderer_(dep_renderer),
    dep_model_(dep_model),
    dep_controller_(dep_controller)
  {
  }

  ~SelectionView() {
  }
  
  void render_game();

  void handle_event(int iEventCode);

protected:

  SelectionRendererInterface & dep_renderer_;
  SelectionModel & dep_model_;
  ControllerInterface & dep_controller_;

};

#endif // _SELECTION_VIEW_HPP_
