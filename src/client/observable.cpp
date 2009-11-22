#include "observable.hpp"
#include "abstract_observer.hpp"

using namespace std;

void
Observable::add_observer(AbstractObserver * ipObserver) {
  observers_.push_back(ipObserver);
}

void 
Observable::fire_event(int iEventCode) {
  vector<AbstractObserver *>::iterator it = observers_.begin();
  while (it != observers_.end()) {
    (*it)->handle_event(iEventCode);
    ++it;
  }
}
