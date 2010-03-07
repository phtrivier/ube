#include "command_stack.hpp"

#include "command_interface.hpp"

#include <assert.h>

CommandStack::~CommandStack()
{
  // Deletes all the pointers in the command stack.
  int size = (int) commands_.size();
  for (int i = 0 ; i < size ; i++) {
    CommandInterface * p_command = commands_.back();
    assert(p_command != NULL);
    commands_.pop_back();
    delete(p_command);
  }
}

void
CommandStack::doCommand(CommandInterface * i_p_command)
{
  assert(i_p_command != NULL);

  // Doing a command means the commands that
  // are afterwards in the stack cannot be undone anymore ; 
  // We need to remove them from the stack.
  // This has the nice property that the new command
  // must be put exactly at the end of the stack, which is
  // efficient enough.

  for (int top_index = (commands_.size() -1 ) ; 
       top_index > undo_index_ ; 
       top_index--) {

    // Call the destructors of 
    // the commands, ensuring there is no
    // memory leak. Which is why the stack takes
    // ownership of the pointer...
    CommandInterface * p_command = commands_.back();
    assert(p_command != NULL);
    commands_.pop_back();
    delete(p_command);

  }

  commands_.push_back(i_p_command);
  // The next thing to undo should be exactly the last
  // thing we just put. And it should not be possible
  // to redo anything.
  undo_index_++;
  redo_index_ = -1;
  assert(undo_index_ == (int) (commands_.size() - 1));

  // Oh, and we had something to, ahem, *do*, by the way.
  i_p_command->execute();
  
}

void
CommandStack::undoLast()
{
  if (canUndo()) {
    assert(undo_index_ < (int) commands_.size());
    CommandInterface * to_undo = commands_[undo_index_];
    assert(to_undo != NULL);

    to_undo->undo();

    redo_index_ = undo_index_;
    undo_index_--;

  }
}

void
CommandStack::redoLast()
{
  if (canRedo()) {
    assert(redo_index_ < (int) commands_.size());
    CommandInterface * to_redo = commands_[redo_index_];
    assert(to_redo != NULL);
    
    to_redo->execute();

    undo_index_ = redo_index_;
    if (redo_index_ == (int) commands_.size() - 1) {
      redo_index_ = -1;
    } else {
      redo_index_++;
    }
  }
}
