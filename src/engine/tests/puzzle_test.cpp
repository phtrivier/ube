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

  TEST_F(PuzzleTest, LetsYouSetCell) {
    Puzzle p;
    p.set_dimensions(3,4);
    Cell c1(0,1,Cell::IN);
    p.add_cell(&c1);
    ASSERT_EQ(0, p.get_cell_at(0,1)->get_i());
    ASSERT_EQ(1, p.get_cell_at(0,1)->get_j());
    ASSERT_TRUE(p.get_cell_at(0,1)->is_in());
  }

} // Namespace
