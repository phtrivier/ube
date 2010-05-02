/**
 * This is Free Software. See COPYING for information.
 */
#include "in_game_model.hpp"

#include "engine/game_event.hpp"
#include "engine/move.hpp"
#include "engine/puzzle.hpp"
#include "engine/path_finder_interface.hpp"

#include "common/logging.hpp"

#include <assert.h>

void
InGameModel::update_path()
{
  if (has_valid_move() || !has_valid_goal()) {
    puzzle_.clear_path();
  } else {
    // If required, look for a path
    if (has_goal_changed() || has_player_moved()) {
      assert(goal_i_ != -1);
      assert(goal_j_ != -1);

      puzzle_.clear_path();

      assert(current_move_index_ < (int) puzzle_.moves().size());
      int move_type = puzzle_.moves()[current_move_index_].type();
    
      dep_path_finder_.find_path(puzzle_,
				 puzzle_.get_player_i(),
				 puzzle_.get_player_j(),
				 goal_i_,
				 goal_j_,
				 move_type);

      last_goal_i_ = goal_i_;
      last_goal_j_ = goal_j_;

      last_player_i_ = puzzle_.get_player_i();
      last_player_j_ = puzzle_.get_player_j();

    }
  }
}

void
InGameModel::move_player(int i_i, int i_j) 
{
  assert(puzzle_.is_valid_position(i_i, i_j));
  puzzle_.put_player(i_i, i_j);
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
    goal_i_ < puzzle_.get_h() &&
    goal_j_ < puzzle_.get_w();
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
  bool res = last_player_i_ != puzzle_.get_player_i() ||
    last_player_j_ != puzzle_.get_player_j();
  return res;
}


void
InGameModel::set_first_available_move_as_current()
{
  std::vector<Move> & moves = puzzle_.moves();
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

void
InGameModel::set_next_available_move_as_current()
{
  std::vector<Move> & moves = puzzle_.moves();
  int size = moves.size();
  bool found = false;
  int old_index = current_move_index_;

  do {
    current_move_index_ = (current_move_index_ + 1) % size;
    if (moves[current_move_index_].available()) {
      found = true;
    }
  } while (!found && current_move_index_ != old_index);

}


bool
InGameModel::is_puzzle_finished()
{
  return puzzle_.is_finished();
}
