#include "client/puzzle_selection_model.hpp"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <stdexcept>
using namespace std;

namespace {
  class PuzzleSelectionModelTest : public ::testing::Test {
  protected:
    PuzzleSelectionModelTest() {
    }

    virtual ~PuzzleSelectionModelTest() {
    }

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }

  };

  TEST_F(PuzzleSelectionModelTest, KnowsListOfSelectablePuzzle) {

    PuzzleSelectionModel m;
    ASSERT_FALSE(m.has_selected_puzzle());

    std::vector<std::string> names = m.get_puzzle_names();
    EXPECT_EQ("First puzzle", names[0]);
    
    m.set_selected_puzzle_index(0);

    ASSERT_TRUE(m.has_selected_puzzle());

    EXPECT_EQ("puzzle1.lua", m.get_selected_puzzle_file_name());
    
    
  }

} // Namespace
