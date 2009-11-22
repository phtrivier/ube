#ifndef _ABSTRACT_OBSERVER_HPP_
#define _ABSTRACT_OBSERVER_HPP_


/**
 * Base class for observers.
 */
class AbstractObserver { 

public:

  ~AbstractObserver(){
  }

  virtual void handle_event(int iEventCode) = 0;

};

#endif // _ABSTRACT_OBSERVER_HPP_
