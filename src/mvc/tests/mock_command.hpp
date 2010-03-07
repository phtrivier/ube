#include <gmock/gmock.h>
#include "mvc/command_interface.hpp"

class MockCommand : public CommandInterface {
 public:
  MOCK_METHOD0(execute,
      void());
  MOCK_METHOD0(undo,
      void());
};
