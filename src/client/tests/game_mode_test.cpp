#include "game_mode.hpp"
#include "mock_controller.hpp"
#include "mock_view.hpp"

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
    MockView mv;
    GameMode gm(&mc, &mv);

    EXPECT_CALL(mc,check_events())
      .WillOnce(Return(false))
      .WillOnce(Return(true));
    EXPECT_CALL(mc,handle_event());

    // First call will get nothing
    gm.update_game(10);
    // Second call will get an event and process it
    gm.update_game(10);

  }

  TEST_F(GameModeTest, UsesViewToRenderTheContent) {
    MockController mc;
    MockView mv;
    GameMode gm(&mc, &mv);

    EXPECT_CALL(mv, render_game()).Times(1);

    gm.render_game();
  }


} // Namespace
