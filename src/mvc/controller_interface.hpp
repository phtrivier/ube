/**
 * This is Free Software. See COPYING for information.
 */
#ifndef _CONTROLLER_INTERFACE_HPP_
#define _CONTROLLER_INTERFACE_HPP_

#include "mvc/observable.hpp"

// TODO : Add dependency on models ... 

/**
 * Base class for controllers.
 */
class ControllerInterface : 
  public Observable 
{ 

public:

  ControllerInterface() : Observable() {
  }

  virtual ~ControllerInterface() {
  }

  /**
   * Check if any new event should be handled.
   */
  virtual bool check_events() = 0;

  /**
   * Handles the last event provided by check_events.
   */
  virtual void handle_event() = 0;

  /**
   * X position of the mouse pointer
   */
  virtual int mouse_x() const = 0;

  /**
   * Y position of the mouse pointer
   */
  virtual int mouse_y() const = 0;
  
};

#endif // _CONTROLLER_INTERFACE_HPP_
