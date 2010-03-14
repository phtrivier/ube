#include "game_loop.hpp"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <stdexcept>
using namespace std;

#include "mvc/tests/mock_controller.hpp"
#include "mvc/tests/mock_view.hpp"
#include "mvc/tests/mock_clock.hpp"

#include "mock_game_mode.hpp"

namespace {
  class GameLoopTest : public ::testing::Test {
  protected:
    GameLoopTest() {
    }

    virtual ~GameLoopTest() {
    }

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }

  };

  TEST_F(GameLoopTest, CanRegisterModesByName) {
    /*
    MockView mv;
    MockController mc;
    GameMode mode1(&mc,&mv);
    GameMode mode2(&mc,&mv);
    */
    MockClock c;
    MockGameMode mode1;
    MockGameMode mode2;

    GameLoop loop(&c);

    EXPECT_CALL(mode1,add_observer(&loop));
    EXPECT_CALL(mode2,add_observer(&loop));
    
    loop.register_game_mode("mode1",&mode1);
    loop.register_game_mode("mode2",&mode2);

    loop.set_current_game_mode("mode2");
    ASSERT_EQ(&mode2, loop.get_current_game_mode());

    ASSERT_THROW(loop.set_current_game_mode("foo"),std::logic_error);
  }

} // Namespace
