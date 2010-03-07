#include "sdl_in_game_renderer.hpp"

#include "common/tests/mock_resource_resolver.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <stdexcept>
using namespace std;

namespace {
  class SdlInGameRendererTest : public ::testing::Test {
  protected:
    SdlInGameRendererTest() {
    }

    virtual ~SdlInGameRendererTest() {
    }

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }

  };

  TEST_F(SdlInGameRendererTest, ConvertsAMousePointToACellPosition) {
    MockResourceResolver resolver;
    SdlInGameRenderer renderer(resolver);
    // FIXME : use class constant here
    int offset = 40;
    ASSERT_EQ(0, renderer.mouse_x_as_puzzle_column(offset));
    ASSERT_EQ(1, renderer.mouse_x_as_puzzle_column(offset+33));
    ASSERT_EQ(-1, renderer.mouse_x_as_puzzle_column(offset-33));
    ASSERT_EQ(0, renderer.mouse_y_as_puzzle_line(offset));
    ASSERT_EQ(1, renderer.mouse_y_as_puzzle_line(offset + 33));
    ASSERT_EQ(-1, renderer.mouse_y_as_puzzle_line(offset -33));
  }

} // Namespace
