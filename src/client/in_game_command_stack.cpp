/**
 * This is Free Software. See COPYING for information.
 */
#include "in_game_command_stack.hpp"

#include "command_factory_interface.hpp"
#include "in_game_model.hpp"

void
InGameCommandStack::doMove(InGameModel & i_model, int i_index, int i_i, int i_j) 
{
  CommandInterface * p_command = dep_command_factory_.createMoveCommand(i_model, i_index, i_i, i_j);
  assert(p_command != NULL);
  doCommand(p_command);
}