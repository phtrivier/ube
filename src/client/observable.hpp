#ifndef _OBSERVABLE_HPP_
#define _OBSERVABLE_HPP_

#include <vector>

class AbstractObserver;

/**
 * Things that can fire event.
 */
class Observable { 

  std::vector<AbstractObserver *> observers_;

public:

  Observable() {
  }

  virtual ~Observable() {
  }

  /**
   * Add an observer.
   *
   */
  virtual void add_observer(AbstractObserver * ipObserver);

  /**
   * Notify all registered observers
   * that an event occured.
   */
  void fire_event(int iEventCode);

};

#endif // _OBSERVABLE_HPP_
