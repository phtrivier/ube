#ifndef _CONTROLLER_INTERFACE_HPP_
#define _CONTROLLER_INTERFACE_HPP_

#include "observable.hpp"

// TODO : Add dependency on models ... 

/**
 * Base class for controllers.
 */
class ControllerInterface : public Observable { 

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
};

#endif // _CONTROLLER_INTERFACE_HPP_
