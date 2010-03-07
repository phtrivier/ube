#include "mvc/command_stack.hpp"

#include "mvc/tests/mock_command.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

namespace {
  class CommandStackTest : public ::testing::Test {
  protected:
    CommandStackTest() {
    }

    virtual ~CommandStackTest() {
    }

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }

  };

  TEST_F(CommandStackTest, DoesNothingWhenThereIsNothingToDo) {
    CommandStack s;
    s.undoLast();
    s.redoLast();
    s.redoLast();
    s.undoLast();
  }

  TEST_F(CommandStackTest, UsesCommandsInOrder) {
    CommandStack s;

    MockCommand * m1 = new MockCommand();
    MockCommand * m2 = new MockCommand();

    EXPECT_CALL(*m1, execute()).Times(1);
    EXPECT_CALL(*m2, execute()).Times(2);
    EXPECT_CALL(*m2, undo()).Times(1);
    
    s.doCommand(m1);
    s.doCommand(m2);
    
    s.undoLast();
    s.redoLast();
  }

  TEST_F(CommandStackTest, RestartRedoingQueueAtNewAction) {
    CommandStack s;

    MockCommand * first = new MockCommand();
    MockCommand * second = new MockCommand();
    MockCommand * alternate = new MockCommand();
    
    EXPECT_CALL(*first, execute()).Times(1);
    EXPECT_CALL(*second, execute()).Times(1);
    EXPECT_CALL(*second, undo()).Times(1);
    EXPECT_CALL(*alternate, execute()).Times(2);
    EXPECT_CALL(*alternate, undo()).Times(1);
        
    s.doCommand(first);
    s.doCommand(second);
    
    s.undoLast();
    
    s.doCommand(alternate);

    // This call should have no consequences
    s.redoLast();

    // Now we undo and redo the alternate command
    s.undoLast();
    s.redoLast();
    
  }

  TEST_F(CommandStackTest, ComplicatedScenarioWithBranching) {
    
    CommandStack s;

    MockCommand * first = new MockCommand();
    MockCommand * second = new MockCommand();
    MockCommand * third = new MockCommand();
    MockCommand * alternateSecond = new MockCommand();
    MockCommand * alternateThird = new MockCommand();

    // Do First
    // Do Second
    // Do Third
    // Undo third
    // Undo Second
    // Do alternate second
    // Undo alternate second
    // Redo alternate second
    // Do alternate third
    // Undo alternate third
    // Undo alternate second
    // Undo first
    // Redo first

    EXPECT_CALL(*first, execute()).Times(2);
    EXPECT_CALL(*second, execute()).Times(1);
    EXPECT_CALL(*second, undo()).Times(1);
    EXPECT_CALL(*third, execute()).Times(1);
    EXPECT_CALL(*third, undo()).Times(1);
    EXPECT_CALL(*alternateSecond, execute()).Times(2);
    EXPECT_CALL(*alternateSecond, undo()).Times(2);
    EXPECT_CALL(*alternateThird, execute()).Times(1);
    EXPECT_CALL(*alternateThird, undo()).Times(1);

    s.doCommand(first);
    s.doCommand(second);
    s.doCommand(third);
    s.undoLast();
    s.undoLast();
    s.doCommand(alternateSecond);
    s.undoLast();
    s.redoLast();
    s.doCommand(alternateThird);
    s.undoLast();
    s.undoLast();
    s.undoLast();
    s.redoLast();

  }


} // Namespace
