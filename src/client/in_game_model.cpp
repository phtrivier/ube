#include "in_game_model.hpp"

#include "engine/move.hpp"
#include "engine/puzzle.hpp"
#include "engine/path_finder_interface.hpp"

#include <assert.h>

void
InGameModel::update_path()
{
  if (current_move_index_ == -1) {
    // No node is in the path !
    dep_puzzle_->clear_path();
  } else {
    // If required, look for a path
    if (has_goal_changed()) {

      assert(goal_i_ != -1);
      assert(goal_j_ != -1);

      dep_puzzle_->clear_path();

      assert(current_move_index_ < (int) dep_puzzle_->moves().size());
      int move_type = dep_puzzle_->moves()[current_move_index_].type();
    
      dep_path_finder_.find_path(dep_puzzle_,
				 dep_puzzle_->get_player_i(),
				 dep_puzzle_->get_player_j(),
				 goal_i_,
				 goal_j_,
				 move_type);

      last_goal_i_ = goal_i_;
      last_goal_i_ = goal_j_;
    }
  }
}

bool
InGameModel::has_goal_changed() 
{
  return goal_i_ != last_goal_i_ || goal_j_ != last_goal_j_;
}

void
InGameModel::set_next_available_move_as_current()
{
  std::vector<Move> & moves = dep_puzzle_->moves();
  int size = moves.size();
  bool found = false;
  current_move_index_ = -1;
  for (int i = 0 ; !found && i < size ; i++) {
    if (moves[i].available()) {
      current_move_index_ = i;
    }
  }
}
