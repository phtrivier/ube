#include "puzzle_loader.hpp"

#include "cell.hpp"
#include "puzzle.hpp"
#include "cell_factory.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <stdexcept>
using namespace std;

namespace {
  class PuzzleLoaderTest : public ::testing::Test {

  protected:
    CellFactory f;
    PuzzleLoader * pLoader_;

    PuzzleLoaderTest() {
    }

    virtual ~PuzzleLoaderTest() {
    }

    virtual void SetUp() {
      pLoader_ = new PuzzleLoader(&f);
    }

    virtual void TearDown() {
      delete pLoader_;
    }

  };

  TEST_F(PuzzleLoaderTest, CanLoadAPuzzleRow) {
    Puzzle p;
    p.set_dimensions(2,2);

    pLoader_->set_row(0,&p,"#I");
    pLoader_->set_row(1,&p,"-O");
    
    ASSERT_TRUE(p.get_cell_at(0,0)->is_empty());
    ASSERT_TRUE(p.get_cell_at(0,1)->is_in());
    ASSERT_TRUE(p.get_cell_at(1,0)->is_walkable());
    ASSERT_TRUE(p.get_cell_at(1,1)->is_out());
  }

} // Namespace
