#ifndef _IN_GAME_COMMAND_STACK_HPP_
#define _IN_GAME_COMMAND_STACK_HPP_

#include "mvc/command_stack.hpp"

class InGameModel;
class CommandFactoryInterface;

/**
 * Command stack for the regular game.
 */
class InGameCommandStack : 
  public CommandStack
{ 

public:
  
  InGameCommandStack(CommandFactoryInterface & dep_command_factory) : 
    CommandStack(),
    dep_command_factory_(dep_command_factory)
  {
  }

  ~InGameCommandStack() {
  }

  /**
   * Execute a command for the i-th move of
   * a model.
   */
  void doMove(InGameModel & i_model, int i_index, int i_i, int i_j);

private:

  CommandFactoryInterface & dep_command_factory_;
  
};

#endif // _IN_GAME_COMMAND_STACK_HPP_
