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
    p.setDimensions(5,6);
    ASSERT_EQ(5, p.getW());
    ASSERT_EQ(6, p.getH());
    ASSERT_EQ(NULL, p.getCellAt(0,0));
    ASSERT_EQ(NULL, p.getCellAt(5,4));
  }
  
  TEST_F(PuzzleTest, RefusesSettingNegativeDimensions) {
    Puzzle p;
    ASSERT_THROW(p.setDimensions(0,0), logic_error);
    ASSERT_THROW(p.setDimensions(1,0), logic_error);
    ASSERT_THROW(p.setDimensions(0,1), logic_error);
    ASSERT_THROW(p.setDimensions(-1,1), logic_error);
    ASSERT_THROW(p.setDimensions(1,-1), logic_error);
    ASSERT_THROW(p.setDimensions(-1,-1), logic_error);
  }

  TEST_F(PuzzleTest, LetsYouSetCell) {
    Puzzle p;
    p.setDimensions(3,4);
    Cell c1(0,1,Cell::IN);
    p.addCell(&c1);
    ASSERT_EQ(0, p.getCellAt(0,1)->getI());
    ASSERT_EQ(1, p.getCellAt(0,1)->getJ());
    ASSERT_TRUE(p.getCellAt(0,1)->isIn());

    Cell all_neg(-1,-1, Cell::IN);
    ASSERT_THROW(p.addCell(&all_neg), logic_error);

    Cell one_neg(1,-1, Cell::IN);
    ASSERT_THROW(p.addCell(&one_neg), logic_error);

    Cell other_neg(-1,1, Cell::IN);
    ASSERT_THROW(p.addCell(&other_neg), logic_error);

    Cell one_two_big(0,12, Cell::IN);
    ASSERT_THROW(p.addCell(&one_two_big), logic_error);

    Cell other_too_big(12,0, Cell::IN);
    ASSERT_THROW(p.addCell(&other_too_big), logic_error);
  }

  TEST_F(PuzzleTest, RefusesLookingAtInvalidPosition) {
    Puzzle p;
    p.setDimensions(3,4);
    ASSERT_THROW(p.getCellAt(-1,-1), logic_error);
    ASSERT_THROW(p.getCellAt(0,-1), logic_error);
    ASSERT_THROW(p.getCellAt(-1,0), logic_error);
    ASSERT_THROW(p.getCellAt(12,0), logic_error);
    ASSERT_THROW(p.getCellAt(0,12), logic_error);
  }

} // Namespace
