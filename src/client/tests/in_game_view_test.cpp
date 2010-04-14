#include "in_game_view.hpp"

#include "engine/puzzle.hpp"
#include "engine/puzzle_loader.hpp"
#include "engine/cell_factory.hpp"
#include "engine/cell.hpp"
#include "engine/tests/mock_path_finder.hpp"

#include "in_game_model.hpp"

#include "mock_in_game_renderer.hpp"
#include "mvc/tests/mock_controller.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>
using ::testing::Return;
using ::testing::_;
using ::testing::Eq;
using ::testing::NiceMock;

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
    MockPathFinder pf;
    InGameModel model(pf);
    MockInGameRenderer renderer;
    MockController controller;
    InGameView v(renderer,model, controller);

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

    MockController controller;
    
    MockPathFinder pf;
    InGameModel model(pf);
    model.set_puzzle(p);
    
    InGameView v(renderer, model, controller);

    EXPECT_CALL(renderer, clear());
    EXPECT_CALL(controller, mouse_x()).WillRepeatedly(Return(12));
    EXPECT_CALL(controller, mouse_y()).WillRepeatedly(Return(42));
    EXPECT_CALL(renderer, mouse_x_as_puzzle_column(12)).WillRepeatedly(Return(-1));
    EXPECT_CALL(renderer, render_cell(0,0,Cell::EMPTY));
    EXPECT_CALL(renderer, flush());

    v.render_game();
  
  }

  TEST_F(InGameViewTest, DoesNotMarkEmptyCellAsSelected) {
    Cell c(0,0,Cell::EMPTY);
    Puzzle p;
    p.set_dimensions(1,1);
    p.add_cell(&c);

    MockInGameRenderer renderer;

    MockController controller;
    
    MockPathFinder pf;
    InGameModel model(pf);
    model.set_puzzle(p);
    
    InGameView v(renderer, model, controller);

    EXPECT_CALL(renderer, clear());
    EXPECT_CALL(controller, mouse_x()).WillRepeatedly(Return(10));
    EXPECT_CALL(controller, mouse_y()).WillRepeatedly(Return(11));
    EXPECT_CALL(renderer, mouse_x_as_puzzle_column(10)).WillRepeatedly(Return(0));
    EXPECT_CALL(renderer, mouse_y_as_puzzle_line(11)).WillRepeatedly(Return(0));
    EXPECT_CALL(renderer, render_cell_in_path(_,_,_)).Times(0);
    EXPECT_CALL(renderer, render_cell(0,0,Cell::EMPTY));
    EXPECT_CALL(renderer, flush());

    v.render_game();

  }


  TEST_F(InGameViewTest, UsesControllerInfoToDisplayCurrentCell) {

    Cell c1(0,0,Cell::IN);
    Cell c2(0,1,Cell::WALKABLE);
    Cell c3(0,2,Cell::OUT);
        
    Puzzle p;
    p.set_dimensions(3,1);
    p.add_cell(&c1);
    p.add_cell(&c2);
    p.add_cell(&c3);

    MockInGameRenderer renderer;
    MockController controller;
    MockPathFinder pf;
    InGameModel model(pf);

    model.set_puzzle(p);
    
    InGameView v(renderer, model, controller);

    EXPECT_CALL(renderer, clear());
    EXPECT_CALL(controller, mouse_x()).WillRepeatedly(Return(42));
    EXPECT_CALL(controller, mouse_y()).WillRepeatedly(Return(12));
    EXPECT_CALL(renderer, mouse_x_as_puzzle_column(42)).WillRepeatedly(Return(1));
    EXPECT_CALL(renderer, mouse_y_as_puzzle_line(12)).WillRepeatedly(Return(0));
    EXPECT_CALL(renderer, render_cell(0,0,Cell::IN));
    EXPECT_CALL(renderer, render_cell(0,1,Cell::WALKABLE));
    EXPECT_CALL(renderer, render_cell(0,2,Cell::OUT));
    EXPECT_CALL(renderer, flush());
    v.render_game();
  }


  TEST_F(InGameViewTest, RendersEveryAvailableMoves) {
    
    Cell c1(0,0,Cell::IN);
    Cell c2(0,1,Cell::WALKABLE);
    Cell c3(0,2,Cell::OUT);
        
    Puzzle p;
    p.set_dimensions(3,1);
    p.add_cell(&c1);
    p.add_cell(&c2);
    p.add_cell(&c3);

    p.add_move(MoveType::DOUBLE);
    p.add_move(MoveType::SINGLE);

    NiceMock<MockInGameRenderer> renderer;
    MockController controller;
    MockPathFinder pf;
    InGameModel model(pf);
    model.set_puzzle(p);

    InGameView v(renderer, model, controller);

    /** FIXME : be more precise
    EXPECT_CALL(renderer, render_moves(Eq(p.moves())));
    */
    EXPECT_CALL(renderer, render_moves(_));

    v.render_game();

  }
  
} // Namespace
