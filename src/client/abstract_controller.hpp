#ifndef _ABSTRACT_CONTROLLER_HPP_
#define _ABSTRACT_CONTROLLER_HPP_

#include "observable.hpp"

// TODO : Add dependency on models ... 

/**
 * Base class for controllers.
 */
class AbstractController : public Observable { 

public:

  /**
   * Check if any new event should be handled.
   */
  virtual bool check_events() = 0;

  /**
   * Handles the last event provided by check_events.
   */
  virtual void handle_event() = 0;
};

#endif // _ABSTRACT_CONTROLLER_HPP_
