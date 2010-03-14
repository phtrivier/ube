#ifndef _VIEW_INTERFACE_HPP_
#define _VIEW_INTERFACE_HPP_

#include "mvc/observer_interface.hpp"

/**
 * A generic view.
 */
class ViewInterface:
  public ObserverInterface
{ 

public:

  virtual ~ViewInterface() {
  }

  virtual void render_game() = 0;
  
  virtual void handle_event(int iEventCode) = 0;

};

#endif // _VIEW_INTERFACE_HPP_
