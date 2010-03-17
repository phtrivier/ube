#include "puzzle_selection_model.hpp"

void 
PuzzleSelectionModel::fill_puzzle_list()
{
  add_puzzle("Tutorial", "tutorial0.lua");
  add_puzzle("Second puzzle", "tutorial1.lua");
  add_puzzle("Big puzzle", "tutorial2.lua");
}

void
PuzzleSelectionModel::add_puzzle(std::string i_name, 
				 std::string i_file_name) 
{
  puzzle_names_.push_back(i_name);
  puzzle_file_names_.push_back(i_file_name);
}
