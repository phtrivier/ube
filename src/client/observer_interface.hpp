#ifndef _OBSERVER_INTERFACE_HPP_
#define _OBSERVER_INTERFACE_HPP_

/**
 * Base class for observers.
 */
class ObserverInterface { 

public:

  virtual ~ObserverInterface() {
  }

  virtual void handle_event(int iEventCode) = 0;

};

#endif // _OBSERVER_INTERFACE_HPP_
