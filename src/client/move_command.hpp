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
  MoveCommand(InGameModel & dep_model, int i_index):
    CommandInterface(),
    dep_model_(dep_model),
    move_index_(i_index) 
  {
  }

  ~MoveCommand() {
  }
  
  void execute();
  
  void undo();

private:
  
  InGameModel & dep_model_;
  int move_index_;
  

};

#endif // _MOVE_COMMAND_HPP_
