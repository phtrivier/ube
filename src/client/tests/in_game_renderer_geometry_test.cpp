#include "in_game_renderer_geometry.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <stdexcept>
using namespace std;

namespace {
  class InGameRendererGeometryTest : public ::testing::Test {
  protected:
    InGameRendererGeometryTest() {
    }

    virtual ~InGameRendererGeometryTest() {
    }

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }

  };

  TEST_F(InGameRendererGeometryTest, ConvertsAMousePointToACellPosition) {
    InGameRendererGeometry geometry;
    // FIXME : use class constant here
    int offset = 40;
    ASSERT_EQ(0, geometry.mouse_x_as_puzzle_column(offset));
    ASSERT_EQ(1, geometry.mouse_x_as_puzzle_column(offset+33));
    ASSERT_EQ(-1, geometry.mouse_x_as_puzzle_column(offset-33));
    ASSERT_EQ(0, geometry.mouse_y_as_puzzle_line(offset));
    ASSERT_EQ(1, geometry.mouse_y_as_puzzle_line(offset + 33));
    ASSERT_EQ(-1, geometry.mouse_y_as_puzzle_line(offset -33));
  }

} // Namespace
