#include "cell_factory.hpp"
#include "cell.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <stdexcept>
using namespace std;

namespace {
  class CellFactoryTest : public ::testing::Test {
  protected:
    CellFactoryTest() {
    }

    virtual ~CellFactoryTest() {
    }

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }

  };

  TEST_F(CellFactoryTest, CreatesCellBasedOnLetter) {
    CellFactory f;
    Cell * cell;
    cell = f.make_cell(0,1,'#');
    ASSERT_EQ(0, cell->get_i());
    ASSERT_EQ(1, cell->get_j());
    ASSERT_TRUE(cell->is_empty());
    delete cell;

    cell = f.make_cell(0,1, 'I');
    ASSERT_TRUE(cell->is_in());
    delete cell;
  
    cell = f.make_cell(0,1, 'O');
    ASSERT_TRUE(cell->is_out());
    delete cell;

    cell = f.make_cell(0,1, '-');
    ASSERT_TRUE(cell->is_walkable());
    delete cell;

    ASSERT_THROW(f.make_cell(0,1,'Y'), logic_error);
  }

} // Namespace
