#include "move_command.hpp"

#include "client/in_game_model.hpp"

void
MoveCommand::execute()
{

  old_i_ = dep_model_.get_puzzle().get_player_i();
  old_j_ = dep_model_.get_puzzle().get_player_j();

  dep_model_.get_puzzle().moves()[move_index_].use();
  dep_model_.move_player(target_i_, target_j_);

  // Change the current move to be the next available one
  dep_model_.set_next_available_move_as_current();

}

void
MoveCommand::undo()
{
  dep_model_.get_puzzle().moves()[move_index_].revert();
  dep_model_.move_player(old_i_, old_j_);

  // Change the current move to be the one just cancelled
  dep_model_.set_current_move_index(move_index_);
}

