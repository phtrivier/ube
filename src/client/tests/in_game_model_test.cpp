#include "client/in_game_model.hpp"

#include "engine/puzzle.hpp"
#include "engine/cell.hpp"

#include "engine/tests/mock_path_finder.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <stdexcept>
using namespace std;

namespace {
  class InGameModelTest : public ::testing::Test {
  protected:
    InGameModelTest() {
    }

    virtual ~InGameModelTest() {
    }

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }

  };

  TEST_F(InGameModelTest, TreatsPuzzleBorderAsValidGoalds) {
    
    MockPathFinder pf;
    InGameModel model(pf);

    Puzzle & p = model.get_puzzle() ;
    p.set_dimensions(2,1);
    Cell c1(0,0, Cell::OUT);
    Cell c2(0,1, Cell::IN);
    p.add_cell(&c1);
    p.add_cell(&c2);
    

    model.set_goal(0,0);
    ASSERT_TRUE(model.has_valid_goal());

  }

} // Namespace
