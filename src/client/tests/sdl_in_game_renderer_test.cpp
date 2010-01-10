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
    ASSERT_EQ(0, renderer.mouse_x_as_puzzle_column(0));
    ASSERT_EQ(1, renderer.mouse_x_as_puzzle_column(33));
    ASSERT_EQ(-1, renderer.mouse_x_as_puzzle_column(-33));
    ASSERT_EQ(0, renderer.mouse_y_as_puzzle_line(0));
    ASSERT_EQ(1, renderer.mouse_y_as_puzzle_line(33));
    ASSERT_EQ(-1, renderer.mouse_y_as_puzzle_line(-33));
  }

} // Namespace
