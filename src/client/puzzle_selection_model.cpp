/**
 * This is Free Software. See COPYING for information.
 */
#include "puzzle_selection_model.hpp"

void 
PuzzleSelectionModel::fill_puzzle_list()
{
  add_puzzle("From here to there (you can move, like.)", "tutorial0.lua");
  add_puzzle("Twice as fast (you can move even faster, like.)", "tutorial1.lua");
  add_puzzle("Ouch, a wall. You can cross it. Trust me.", "tutorial2.lua");
  add_puzzle("Okay, let's get funnier...", "tutorial3.lua");
  add_puzzle("Relax. You'll pick up along the way.", "tutorial4.lua");
  add_puzzle("Too simple ? Let's see...", "tutorial5.lua");
}

void
PuzzleSelectionModel::add_puzzle(std::string i_name, 
				 std::string i_file_name) 
{
  puzzle_names_.push_back(i_name);
  puzzle_file_names_.push_back(i_file_name);
}