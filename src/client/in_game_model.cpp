/**
 * This is Free Software. See COPYING for information.
 */
#include "in_game_model.hpp"

#include "engine/move.hpp"
#include "engine/puzzle.hpp"
#include "engine/path_finder_interface.hpp"

#include "common/logging.hpp"

#include <assert.h>

void
InGameModel::update_path()
{
  if (has_valid_move() || !has_valid_goal()) {
    dep_puzzle_->clear_path();
  } else {
    // If required, look for a path
    if (has_goal_changed() || has_player_moved()) {
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
      last_goal_j_ = goal_j_;

      last_player_i_ = dep_puzzle_->get_player_i();
      last_player_j_ = dep_puzzle_->get_player_j();

    }
  }
}

void
InGameModel::move_player(int i_i, int i_j) 
{
  assert(dep_puzzle_->is_valid_position(i_i, i_j));
  dep_puzzle_->put_player(i_i, i_j);
}

bool
InGameModel::has_valid_move()
{
  return current_move_index_ == -1;
}

bool
InGameModel::has_valid_goal()
{
  return goal_i_ >= 0 && goal_j_ >= 0 &&
    goal_i_ < dep_puzzle_->get_h() &&
    goal_j_ < dep_puzzle_->get_w();
}

bool
InGameModel::has_goal_changed() 
{
  LOG_D("in_game_model") << "Last goal i : " << last_goal_i_;
  LOG_D("in_game_model") << "Goal i : " << goal_i_;
  LOG_D("in_game_model") << "Last goal j : " << last_goal_j_;
  LOG_D("in_game_model") << "Goal j : " << goal_j_;
  
  bool res =  goal_i_ != last_goal_i_ || goal_j_ != last_goal_j_;
  LOG_D("in_game_model") << "Has goal changed ? " << res;
  return res;
}

bool
InGameModel::has_player_moved()
{
  bool res = last_player_i_ != dep_puzzle_->get_player_i() ||
    last_player_j_ != dep_puzzle_->get_player_j();
  return res;
}


void
InGameModel::set_next_available_move_as_current()
{
  std::vector<Move> & moves = dep_puzzle_->moves();
  int size = moves.size();
  bool found = false;
  current_move_index_ = -1;
  for (int i = 0 ; !found && i < size ; ++i) {
    if (moves[i].available()) {
      current_move_index_ = i;
      found = true;
    }
  }
}

bool
InGameModel::is_puzzle_finished()
{
  return dep_puzzle_->is_finished();
}