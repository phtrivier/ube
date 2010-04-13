/**
 * This is Free Software. See COPYING for information.
 */
#ifndef _OBSERVABLE_HPP_
#define _OBSERVABLE_HPP_

#include <vector>

class ObserverInterface;

/**
 * Things that can fire event.
 */
class Observable { 

  std::vector<ObserverInterface *> observers_;

public:

  Observable() {
  }

  virtual ~Observable() {
  }

  /**
   * Add an observer.
   *
   */
  virtual void add_observer(ObserverInterface * ipObserver);

  /**
   * Notify all registered observers
   * that an event occured.
   */
  void fire_event(int iEventCode);

};

#endif // _OBSERVABLE_HPP_