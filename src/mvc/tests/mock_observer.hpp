#include <gmock/gmock.h>
#include "mvc/observer_interface.hpp"

class MockObserver : public ObserverInterface {
 public:
  MOCK_METHOD1(handle_event,void(int iEventCode));
};
