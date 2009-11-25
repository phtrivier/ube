#include "game_mode.hpp"
#include "mock_controller.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>
using ::testing::Return;

#include <stdexcept>
using namespace std;

namespace {
  class GameModeTest : public ::testing::Test {
  protected:
    GameModeTest() {
    }

    virtual ~GameModeTest() {
    }

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }

  };

  TEST_F(GameModeTest, GetsAndProcessEventsFromController) {

    MockController mc;
    // TODO : MockView
    GameMode gm(&mc);

    EXPECT_CALL(mc,check_events())
      .WillOnce(Return(false))
      .WillOnce(Return(true));

    EXPECT_CALL(mc,handle_event());

    // First call will get nothing
    gm.update_game(10);
    // Second call will get an event and process it
    gm.update_game(10);

  }

} // Namespace
