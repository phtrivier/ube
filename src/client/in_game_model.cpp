#include "in_game_model.hpp"

#include "engine/move.hpp"
#include "engine/puzzle.hpp"
#include "engine/path_finder_interface.hpp"

#include <assert.h>

void
InGameModel::update_path()
{
  if (has_goal_changed()) {

    assert(goal_i_ != -1);
    assert(goal_j_ != -1);

    dep_puzzle_->clear_path();
    dep_path_finder_.find_path(dep_puzzle_,
			       dep_puzzle_->get_player_i(),
			       dep_puzzle_->get_player_j(),
			       goal_i_,
			       goal_j_,
			       MoveType::SINGLE);

    last_goal_i_ = goal_i_;
    last_goal_i_ = goal_j_;
  }
}

bool
InGameModel::has_goal_changed() 
{
  return goal_i_ != last_goal_i_ || goal_j_ != last_goal_j_;
}
