#include <gmock/gmock.h>
#include "controller_interface.hpp"

class AbstractObserver;

class MockController : public ControllerInterface {
 public:

  MOCK_METHOD1(add_observer,
	       void(AbstractObserver *));

  MOCK_METHOD0(check_events,
      bool());
  MOCK_METHOD0(handle_event,
      void());
};
