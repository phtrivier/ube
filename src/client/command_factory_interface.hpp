#ifndef _COMMAND_FACTORY_INTERFACE_HPP_
#define _COMMAND_FACTORY_INTERFACE_HPP_

class InGameModel;
class CommandInterface;

/**
 * Factory for command objects
 */
class CommandFactoryInterface { 

public:

  virtual ~CommandFactoryInterface() { };

  /**
   * Creates a move command for the move at
   * a given index in a model.
   *
   * The ownership of the created command is 
   * transfered to the caller.   
   */
  virtual CommandInterface * createMoveCommand(InGameModel & i_model, int i_index) = 0;
  
};

#endif // _COMMAND_FACTORY_INTERFACE_HPP_
