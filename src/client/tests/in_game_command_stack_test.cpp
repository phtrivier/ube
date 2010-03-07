#include "client/in_game_command_stack.hpp"

#include "client/tests/mock_command_factory.hpp"
#include "client/in_game_model.hpp"

#include "mvc/tests/mock_command.hpp"

#include "engine/tests/mock_path_finder.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <stdexcept>
using namespace std;

using ::testing::Return;
using ::testing::Eq;
using ::testing::ByRef;
using ::testing::_;

namespace {
  class InGameCommandStackTest : public ::testing::Test {
  protected:
    InGameCommandStackTest() {
    }

    virtual ~InGameCommandStackTest() {
    }

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }

  };

  TEST_F(InGameCommandStackTest, UsesCommandsCreatedByFactory) {
    MockCommandFactory f;
    InGameCommandStack s(f);

    MockPathFinder pf;
    InGameModel model(pf);

    MockCommand * move1 = new MockCommand();

    // This is why I hate c++.
    // Writing this does not work because I would have to 
    // define equality for InGameModel. WTF would I ? 
    // Why can't I just use references ? 
    //    EXPECT_CALL(f, createMoveCommand(Eq(ByRef(model)), 1)).WillOnce(Return(move1));
    EXPECT_CALL(f, createMoveCommand(_, 1)).WillOnce(Return(move1));
    EXPECT_CALL(*move1, execute()).Times(1);
    EXPECT_CALL(*move1, undo()).Times(1);

    s.doMove(model,1);
    s.undoLast();

  }

} // Namespace
