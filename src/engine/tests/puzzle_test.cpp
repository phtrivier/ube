#include <puzzle.hpp>
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
    ASSERT_EQ(NULL, p.getCellAt(4,5));
  }
  
  TEST_F(PuzzleTest, ThrowsExceptionIfDimensionsAreNegative) {
    Puzzle p;
    ASSERT_THROW(p.setDimensions(0,0), logic_error);
    ASSERT_THROW(p.setDimensions(1,0), logic_error);
    ASSERT_THROW(p.setDimensions(0,1), logic_error);
    ASSERT_THROW(p.setDimensions(-1,1), logic_error);
    ASSERT_THROW(p.setDimensions(1,-1), logic_error);
    ASSERT_THROW(p.setDimensions(-1,-1), logic_error);
  }


} // Namespace
