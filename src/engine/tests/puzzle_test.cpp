#include "puzzle.hpp"
#include "cell.hpp"

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
  
  TEST_F(PuzzleTest, RefusesSettingNegativeDimensions) {
    Puzzle p;
    ASSERT_THROW(p.set_dimensions(0,0), logic_error);
    ASSERT_THROW(p.set_dimensions(1,0), logic_error);
    ASSERT_THROW(p.set_dimensions(0,1), logic_error);
    ASSERT_THROW(p.set_dimensions(-1,1), logic_error);
    ASSERT_THROW(p.set_dimensions(1,-1), logic_error);
    ASSERT_THROW(p.set_dimensions(-1,-1), logic_error);
  }

  TEST_F(PuzzleTest, LetsYouSetCell) {
    Puzzle p;
    p.set_dimensions(3,4);
    Cell c1(0,1,Cell::IN);
    p.add_cell(&c1);
    ASSERT_EQ(0, p.get_cell_at(0,1)->get_i());
    ASSERT_EQ(1, p.get_cell_at(0,1)->get_j());
    ASSERT_TRUE(p.get_cell_at(0,1)->is_in());

    Cell all_neg(-1,-1, Cell::IN);
    ASSERT_THROW(p.add_cell(&all_neg), logic_error);

    Cell one_neg(1,-1, Cell::IN);
    ASSERT_THROW(p.add_cell(&one_neg), logic_error);

    Cell other_neg(-1,1, Cell::IN);
    ASSERT_THROW(p.add_cell(&other_neg), logic_error);

    Cell one_two_big(0,12, Cell::IN);
    ASSERT_THROW(p.add_cell(&one_two_big), logic_error);

    Cell other_too_big(12,0, Cell::IN);
    ASSERT_THROW(p.add_cell(&other_too_big), logic_error);
  }

  TEST_F(PuzzleTest, RefusesLookingAtInvalidPosition) {
    Puzzle p;
    p.set_dimensions(3,4);
    ASSERT_THROW(p.get_cell_at(-1,-1), logic_error);
    ASSERT_THROW(p.get_cell_at(0,-1), logic_error);
    ASSERT_THROW(p.get_cell_at(-1,0), logic_error);
    ASSERT_THROW(p.get_cell_at(12,0), logic_error);
    ASSERT_THROW(p.get_cell_at(0,12), logic_error);
  }

} // Namespace
