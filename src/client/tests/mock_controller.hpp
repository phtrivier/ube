#include <gmock/gmock.h>
#include "controller_interface.hpp"

class ObserverInterface;

class MockController : public ControllerInterface {
 public:

  MOCK_METHOD1(add_observer,
	       void(ObserverInterface *));

  MOCK_METHOD0(check_events,
      bool());
  MOCK_METHOD0(handle_event,
      void());
  MOCK_CONST_METHOD0(mouse_x,
      int());
  MOCK_CONST_METHOD0(mouse_y,
      int());

};
