#ifndef _IN_GAME_MODEL_HPP_
#define _IN_GAME_MODEL_HPP_

#include "engine/puzzle.hpp"
#include <assert.h>

class PathFinderInterface;

/**
 * Model for the bulk of the game
 */
class InGameModel { 

public:

  //FIXME(pht) : should'nt the puzzle be a dependency, too ?
  InGameModel(PathFinderInterface & dep_path_finder):
    dep_path_finder_(dep_path_finder),
    goal_i_(-1),
    goal_j_(-1),
    last_goal_i_(-1),
    last_goal_j_(-1),
    current_move_index_(0)
  {
  }

  ~InGameModel() {
  }
  
  Puzzle & get_puzzle() {
    return *dep_puzzle_;
  }

  void set_puzzle(Puzzle & dep_puzzle) {
    this->dep_puzzle_ = &dep_puzzle;
  }
  
  void update_path();

  void set_goal(int i_i, int i_j) {
    goal_i_ = i_i;
    goal_j_ = i_j;
  }

  int current_move_index() {
    return current_move_index_;
  }

  void set_current_move_index(int i_index) {
    assert(i_index < (int) dep_puzzle_->moves().size());
    current_move_index_ = i_index;
  }

 
private:
  Puzzle * dep_puzzle_;
  PathFinderInterface & dep_path_finder_;

  // Position of the current goal in the path
  int goal_i_;
  int goal_j_;
  
  // Position of the last goal for which a path
  // was computed
  int last_goal_i_;
  int last_goal_j_;

  // Index of the move currently selected in the puzzle.
  int current_move_index_;

  bool has_goal_changed();

};

#endif // _IN_GAME_MODEL_HPP_
