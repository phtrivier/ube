#include <gmock/gmock.h>
#include "abstract_controller.hpp"

class AbstractObserver;

class MockController : public AbstractController {
 public:

  MOCK_METHOD1(add_observer,
	       void(AbstractObserver *));

  MOCK_METHOD0(check_events,
      bool());
  MOCK_METHOD0(handle_event,
      void());
};
