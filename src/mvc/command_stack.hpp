#ifndef _COMMAND_STACK_HPP_
#define _COMMAND_STACK_HPP_

#include <vector>

class CommandInterface;

/**
 * A stack for doing / undoing commands.
 */
class CommandStack { 

public:

  CommandStack() : undo_index_(-1), redo_index_(-1) {
  }

  ~CommandStack();

  /**
   * Execute a command and set it as the top
   * of the command stack.
   *
   * Does nothing if the stack is empty.
   * 
   * @param i_p_command : pointer to a command. The stack
   *  takes ownership of the command.
   */
  void doCommand(CommandInterface * i_p_command);

  /**
   * Undo the last command done.
   *
   * Does nothing if there is nothing to undo.
   */ 
  void undoLast();

  /**
   * Redo the last undone command.
   *
   * Does nothing if there is nothing to redo.
   */
  void redoLast();

private:

  std::vector<CommandInterface *> commands_;

  /**
   * Index of the next command that can be undone.
   */
  int undo_index_;

  /**
   * Index of the next command that can be redone.
   */
  int redo_index_;

  /**
   * Is there anything to undo ?
   */
  bool canUndo() {
    return undo_index_ != -1;
  }

  /**
   * Is there anything to redo ?
   */
  bool canRedo() {
    return redo_index_ != -1;
  }


};

#endif // _COMMAND_STACK_HPP_
