#include <cell.hpp>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

namespace {
  class CellTest : public ::testing::Test {
  protected:
    CellTest() {
    }

    virtual ~CellTest() {
    }

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }

  };

  TEST_F(CellTest, IsEmptyBasedOnType) {
    Cell c(0,1, Cell::EMPTY);
    ASSERT_EQ(0, c.get_i());
    ASSERT_EQ(1, c.get_j());
    ASSERT_TRUE(c.is_empty());
  }

} // Namespace
