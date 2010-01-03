#include "observable.hpp"
#include "observer_interface.hpp"

using namespace std;

void
Observable::add_observer(ObserverInterface * ipObserver) {
  observers_.push_back(ipObserver);
}

void 
Observable::fire_event(int iEventCode) {
  vector<ObserverInterface *>::iterator it = observers_.begin();
  while (it != observers_.end()) {
    (*it)->handle_event(iEventCode);
    ++it;
  }
}
