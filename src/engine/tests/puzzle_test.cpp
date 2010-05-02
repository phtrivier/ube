#include "puzzle.hpp"
#include "cell.hpp"
#include "move.hpp"

#include "mvc/tests/mock_command.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <stdexcept>
using namespace std;

namespace {
  class PuzzleTest : public ::testing::Test {
  protected:
    PuzzleTest() {
    }

    virtual ~PuzzleTest() {
    }

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }

  };

  TEST_F(PuzzleTest, InitializesWithEmptyCells) {
    Puzzle p;
    p.set_dimensions(5,6);
    ASSERT_EQ(5, p.get_w());
    ASSERT_EQ(6, p.get_h());
    ASSERT_EQ(NULL, p.get_cell_at(0,0));
    ASSERT_EQ(NULL, p.get_cell_at(5,4));
  }

  TEST_F(PuzzleTest, LetsYouSetCell) {
    Puzzle p;
    p.set_dimensions(3,4);
    Cell c1(0,1,Cell::IN);
    p.add_cell(&c1);
    ASSERT_EQ(0, p.get_cell_at(0,1)->get_i());
    ASSERT_EQ(1, p.get_cell_at(0,1)->get_j());
    ASSERT_TRUE(p.get_cell_at(0,1)->is_in());
  }

  TEST_F(PuzzleTest, PutsPlayerAtEntrance) {
    Puzzle p;
    p.set_dimensions(2,1);
    Cell c1(0,0,Cell::OUT);
    Cell c2(0,1,Cell::IN);
    p.add_cell(&c1);
    p.add_cell(&c2);
    ASSERT_EQ(-1, p.get_player_i());
    ASSERT_EQ(-1, p.get_player_j());
    ASSERT_EQ(0, p.enters_player());
    ASSERT_EQ(0, p.get_player_i());
    ASSERT_EQ(1, p.get_player_j());
  }

  TEST_F(PuzzleTest, ShoutsIfThereIsNoEntrance) {
    Puzzle p;
    p.set_dimensions(2,1);
    Cell c1(0,0,Cell::WALKABLE);
    Cell c2(0,1,Cell::OUT);
    p.add_cell(&c1);
    p.add_cell(&c2);
    ASSERT_EQ(-1, p.enters_player());
  }
  
  TEST_F(PuzzleTest, CanMovePlayerToANonEmptyPosition) {
    Puzzle p;
    p.set_dimensions(4,1);
    Cell c1(0,0,Cell::IN);
    Cell c2(0,1,Cell::WALKABLE);
    Cell c3(0,2,Cell::EMPTY);
    Cell c4(0,3,Cell::OUT);

    p.add_cell(&c1);
    p.add_cell(&c2);
    p.add_cell(&c3);
    p.add_cell(&c4);

    ASSERT_EQ(0, p.enters_player());
    ASSERT_EQ(0,p.put_player(0,1));
    ASSERT_EQ(0, p.get_player_i());
    ASSERT_EQ(1, p.get_player_j());
    ASSERT_EQ(-1, p.put_player(0,2)); // TODO(pht) differentiate codes ? 
    ASSERT_EQ(0, p.get_player_i());
    ASSERT_EQ(1, p.get_player_j());
    ASSERT_EQ(-1, p.put_player(-3,42)); // TODO(pht) differentiate codes ? 
    ASSERT_EQ(0, p.get_player_i());
    ASSERT_EQ(1, p.get_player_j());

  }

  TEST_F(PuzzleTest, MaintainsAMapOfAvailableMoves) {
    Puzzle p;
    ASSERT_EQ(0, (int) p.moves().size());
    p.add_move(MoveType::DOUBLE);
    p.add_move(MoveType::SINGLE);
    ASSERT_EQ(2, (int) p.moves().size());
    ASSERT_EQ(MoveType::DOUBLE, p.moves().at(0).type());
    ASSERT_TRUE(p.moves().at(0).available());
    ASSERT_EQ(0, p.use_move(0));
    ASSERT_FALSE(p.moves().at(0).available());
    ASSERT_EQ(0, p.revert_move(0));
    ASSERT_TRUE(p.moves().at(0).available());
  }

  TEST_F(PuzzleTest, CanHaveScriptsOnSomeCells) {
    Puzzle p;
    p.set_dimensions(2,1);
    Cell c1(0,0,Cell::WALKABLE);
    Cell c2(0,1,Cell::OUT);
    p.add_cell(&c1);
    p.add_cell(&c2);

    ASSERT_FALSE(p.has_script(0,0));
    ASSERT_FALSE(p.has_script(0,1));

    MockCommand script;
    p.add_script(0,1,&script);

    ASSERT_FALSE(p.has_script(0,0));
    ASSERT_TRUE(p.has_script(0,1));
    
    ASSERT_EQ(&script, p.get_script_at(0,1));

    EXPECT_CALL(script, execute()).Times(1);
    EXPECT_CALL(script, undo()).Times(1);

    p.do_script_at(0,1);
    p.undo_script_at(0,1);

  }

  TEST_F(PuzzleTest, SetOverlays) {
    Puzzle p;
    p.set_dimensions(2,2);
    p.set_overlay(0,0,1);
    ASSERT_TRUE(p.has_overlay(0,0));
    ASSERT_EQ(1, p.get_overlay(0,0));
  }

} // Namespace
