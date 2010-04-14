/**
 * This is Free Software. See COPYING for information.
 */
#ifndef _IN_GAME_MODEL_HPP_
#define _IN_GAME_MODEL_HPP_

#include "engine/puzzle.hpp"
#include <assert.h>

class PathFinderInterface;

class Move;

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
    last_player_i_(-1),
    last_player_j_(-1),
    current_move_index_(0),
    hovered_move_index_(-1)
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

  /**
   * If either the goal (mouse position) or the position of the player
   * have changed since last call, clear the pathfinding information
   * of the puzzle and try to compute a path from the current player's
   * position to the goal.
   */
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

  Move & current_move() {
    assert(current_move_index_ < (int) dep_puzzle_->moves().size());
    return dep_puzzle_->moves()[current_move_index_];
  }
 
  /**
   * Changes the current selected move to 
   * the first one that is still available.
   */
  void set_next_available_move_as_current();

  /**
   * Move the player to a given position.
   * This clears pathfinding.
   */
  void move_player(int i_i, int i_j);

  /**
   * Does the mouse currently point to a valid cell ?
   */
  bool has_valid_goal();

  /**
   * Is a valid move currently selected ? 
   */
  bool has_valid_move();

  /**
   * Has the player reached the out cell of the puzzle ?
   */
  bool is_puzzle_finished();

  /**
   * Is an index valid for a move ? 
   */
  bool is_valid_move_index(int i_index) {
    return (i_index > -1 && i_index < (int) dep_puzzle_->moves().size());
  }

  /**
   * Is a move at a given index available ? 
   */
  bool is_move_available(int i_index) {
    return (is_valid_move_index(i_index) && dep_puzzle_->moves()[i_index].available());
  }

  int hovered_move_index() {
    return hovered_move_index_;
  }

  void set_hovered_move_index(int i_index)  {
    hovered_move_index_ = i_index;
  }

  /**
   * Has the goal changed since last call to update_path ?
   */
  bool has_goal_changed();

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

  // Last position of the player for which a path
  // was computed
  int last_player_i_;
  int last_player_j_;

  // Index of the move currently selected in the puzzle.
  int current_move_index_;

  // Index of the move currently roled over by the mouse, or -1 if none is.
  int hovered_move_index_;

  /**
   * Has the player's position changed since last call
   * to update_path ? 
   */
  bool has_player_moved();


};

#endif // _IN_GAME_MODEL_HPP_
