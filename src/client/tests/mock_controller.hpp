#include <gmock/gmock.h>
#include "abstract_controller.hpp"

class MockController : public AbstractController {
 public:
  MOCK_METHOD0(check_events,
      bool());
  MOCK_METHOD0(handle_event,
      void());
};
