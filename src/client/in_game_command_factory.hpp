#ifndef _IN_GAME_COMMAND_FACTORY_HPP_
#define _IN_GAME_COMMAND_FACTORY_HPP_

#include "command_factory_interface.hpp"

class InGameModel;

/**
 * Command Factory for actual moves.
 */
class InGameCommandFactory :
  public CommandFactoryInterface

{ 

public:

  InGameCommandFactory() : CommandFactoryInterface() {
  }

  ~InGameCommandFactory() {
  }

  CommandInterface * createMoveCommand(InGameModel & i_model, int i_index);

};

#endif // _IN_GAME_COMMAND_FACTORY_HPP_
