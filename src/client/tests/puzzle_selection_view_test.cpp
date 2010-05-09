#include "puzzle_selection_view.hpp"

#include "puzzle_selection_geometry.hpp"
#include "mvc/tests/mock_controller.hpp"
#include "client/puzzle_selection_model.hpp"

#include "client/tests/mock_selection_renderer.hpp"
#include "client/tests/mock_puzzle_selection_renderer.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <stdexcept>
using namespace std;

using ::testing::_;

namespace {
  class PuzzleSelectionViewTest : public ::testing::Test {
  protected:
    PuzzleSelectionViewTest() {
    }

    virtual ~PuzzleSelectionViewTest() {
    }

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }

  };

  TEST_F(PuzzleSelectionViewTest, UsesRendererToRender) {
    MockPuzzleSelectionRenderer renderer;
    PuzzleSelectionModel model;
    MockController controller;

    PuzzleSelectionView v(renderer, model, controller);

    EXPECT_CALL(renderer, render_item_name(_,_)).Times(model.get_item_count());

    v.render_game();

  }

} // Namespace
