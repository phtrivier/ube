#include "move_command.hpp"

#include "client/in_game_model.hpp"

void
MoveCommand::execute()
{

  old_i = dep_model_.get_puzzle().get_player_i();
  old_j = dep_model_.get_puzzle().get_player_j();

  dep_model_.get_puzzle().moves()[move_index].use();
  dep_model_.get_puzzle().put_player(target_i_,target_j_);

  // Change the current move to be the next available one
  dep_model_.set_next_available_move_as_current();

}

void
MoveCommand::undo()
{
  // TODO
}

