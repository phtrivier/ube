#include <gmock/gmock.h>
#include "mvc/clock_interface.hpp"

class MockClock : public ClockInterface {
 public:
  MOCK_METHOD0(init,
      void());
  MOCK_METHOD0(restart,
      void());
  MOCK_METHOD0(is_time_to_render,
      bool());
  MOCK_METHOD0(tick,
      void());
  MOCK_METHOD0(get_delta,
      int());
};
