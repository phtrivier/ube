#ifndef _MOVE_COMMAND_HPP_
#define _MOVE_COMMAND_HPP_

#include "mvc/command_interface.hpp"

class InGameModel;

/**
 * A command to move in a puzzle.
 */
class MoveCommand : 
  public CommandInterface
{ 
public:
  MoveCommand(InGameModel & dep_model, int i_index, int target_i, int target_j):
    CommandInterface(),
    dep_model_(dep_model),
    move_index_(i_index),
    old_i(-1),
    old_j(-1),
    target_i_(target_i),
    target_j_(target_j),
  {
  }

  ~MoveCommand() {
  }
  
  void execute();
  
  void undo();

private:
  
  InGameModel & dep_model_;
  int move_index_;

  int old_i;
  int old_j;
  
  int target_i_;
  int target_j_;

};

#endif // _MOVE_COMMAND_HPP_
