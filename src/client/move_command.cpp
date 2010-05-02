/**
 * This is Free Software. See COPYING for information.
 */
#include "move_command.hpp"

#include "client/in_game_model.hpp"

#include <string>

void
MoveCommand::execute()
{

  old_i_ = dep_model_.get_puzzle().get_player_i();
  old_j_ = dep_model_.get_puzzle().get_player_j();

  dep_model_.get_puzzle().moves()[move_index_].use();
  dep_model_.move_player(target_i_, target_j_);

  if (dep_model_.get_puzzle().has_script(target_i_, target_j_)) {
    dep_model_.get_puzzle().do_script_at(target_i_, target_j_);

    if (dep_model_.get_puzzle().has_script_message()) {
      dep_model_.set_message(dep_model_.get_puzzle().get_script_message());
      dep_model_.get_puzzle().set_script_message(std::string(""));
    }

  }

  // Change the current move to be the next available one
  dep_model_.set_next_available_move_as_current();
  
}

void
MoveCommand::undo()
{

  if (dep_model_.get_puzzle().has_script(target_i_, target_j_)) {
    dep_model_.get_puzzle().undo_script_at(target_i_, target_j_);
  }

  dep_model_.get_puzzle().moves()[move_index_].revert();
  dep_model_.move_player(old_i_, old_j_);

  // Change the current move to be the one just cancelled
  dep_model_.set_current_move_index(move_index_);
}
