#include <gmock/gmock.h>
#include "observer_interface.hpp"

class MockObserver : public ObserverInterface {
 public:
  MOCK_METHOD1(handle_event,void(int iEventCode));
};
