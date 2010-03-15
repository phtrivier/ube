#include "puzzle_selection_view.hpp"

#include "mvc/tests/mock_controller.hpp"

#include "client/tests/mock_puzzle_selection_renderer.hpp"
#include "client/puzzle_selection_model.hpp"

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

    EXPECT_CALL(renderer, render_puzzle_name(_,_)).Times(model.get_puzzle_count());

    v.render_game();

  }

} // Namespace
