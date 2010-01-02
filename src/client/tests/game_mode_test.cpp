#include "game_mode.hpp"
#include "mock_controller.hpp"
#include "mock_observer.hpp"
#include "mock_view.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>
using ::testing::Return;

#include <stdexcept>
using namespace std;

namespace {
  class DISABLED_GameModeTest : public ::testing::Test {
  protected:
    DISABLED_GameModeTest() {
    }

    virtual ~DISABLED_GameModeTest() {
    }

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }

  };

  TEST_F(DISABLED_GameModeTest, GetsAndProcessEventsFromController) {

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

  TEST_F(DISABLED_GameModeTest, UsesViewToRenderTheContent) {
    MockController mc;
    MockView mv;
    GameMode gm(&mc, &mv);

    EXPECT_CALL(mv, render_game()).Times(1);

    gm.render_game();
  }

  TEST_F(DISABLED_GameModeTest, AddObserversToControllerAndView) {
    MockObserver o;
    MockController mc;
    MockView mv;
    
    GameMode gm(&mc, &mv);

    EXPECT_CALL(mc, add_observer(&o));
    EXPECT_CALL(o, handle_event(12));

    gm.add_observer(&o);
    gm.fire_event(12);
		
    
  }



} // Namespace
