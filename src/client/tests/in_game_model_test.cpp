#include "client/in_game_model.hpp"
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

  TEST_F(InGameModelTest, DoesNotRecomputePathForSillyMoves) {
    
  }

} // Namespace
