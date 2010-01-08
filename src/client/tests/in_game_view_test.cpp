#include "in_game_view.hpp"
#include "mock_in_game_renderer.hpp"
#include "in_game_model.hpp"
#include "engine/puzzle.hpp"
#include "engine/puzzle_loader.hpp"
#include "engine/cell_factory.hpp"
#include "engine/cell.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>
using ::testing::Return;

#include <stdexcept>
using namespace std;

namespace {
  class InGameViewTest : public ::testing::Test {
  protected:
    InGameViewTest() {
    }

    virtual ~InGameViewTest() {
    }

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }

  };

  TEST_F(InGameViewTest, RendersAllCellsForPuzzle) {

    CellFactory f;
    PuzzleLoader loader(&f);
    Puzzle p;
    p.set_dimensions(3,2);
    loader.set_row(0,&p, "###");
    loader.set_row(1,&p, "I-O");

    // TODO : MockController c; ... and also a model, maybe ? 
    InGameModel model;
    MockInGameRenderer renderer;
    InGameView v(renderer,model);

    EXPECT_CALL(renderer, render_cell(0,0,Cell::EMPTY));
    EXPECT_CALL(renderer, render_cell(0,1,Cell::EMPTY));
    EXPECT_CALL(renderer, render_cell(0,2,Cell::EMPTY));
    EXPECT_CALL(renderer, render_cell(1,0,Cell::IN));
    EXPECT_CALL(renderer, render_cell(1,1,Cell::WALKABLE));
    EXPECT_CALL(renderer, render_cell(1,2,Cell::OUT));

    v.render_puzzle(p);
    
  }

  TEST_F(InGameViewTest, UsesPuzzleFromModelToRenderGame) {

    Cell c(0,0,Cell::EMPTY);
        
    Puzzle p;
    p.set_dimensions(1,1);
    p.add_cell(&c);

    MockInGameRenderer renderer;
    
    InGameModel model;
    model.set_puzzle(p);
    
    InGameView v(renderer, model);

    EXPECT_CALL(renderer, clear());
    EXPECT_CALL(renderer, render_cell(0,0,Cell::EMPTY));
    EXPECT_CALL(renderer, flush());

    v.render_game();
  
  }

  
} // Namespace
