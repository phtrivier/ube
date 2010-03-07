#include "in_game_command_stack.hpp"

#include "command_factory_interface.hpp"
#include "in_game_model.hpp"

void
InGameCommandStack::doMove(InGameModel & i_model, int i_index) 
{
  CommandInterface * p_command = dep_command_factory_.createMoveCommand(i_model, i_index);
  assert(p_command != NULL);
  doCommand(p_command);
}
