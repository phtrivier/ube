#include <gmock/gmock.h>
#include "client/command_factory_interface.hpp"

class MockCommandFactory : public CommandFactoryInterface {
 public:
  MOCK_METHOD4(createMoveCommand,
	       CommandInterface*(InGameModel & i_model, int i_index, int i_i, int i_j));
};
