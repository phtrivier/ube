#include "in_game_command_factory.hpp"

#include "move_command.hpp"

CommandInterface * 
InGameCommandFactory::createMoveCommand(InGameModel & i_model, int i_index, int i_i, int i_j) {
  return new MoveCommand(i_model, i_index, i_i, i_j);
}

