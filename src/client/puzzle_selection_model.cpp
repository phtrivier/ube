#include "puzzle_selection_model.hpp"

void 
PuzzleSelectionModel::fill_puzzle_list()
{
  add_puzzle("First puzzle", "puzzle1.lua");
  add_puzzle("Second puzzle", "puzzle2.lua");
  add_puzzle("Big puzzle", "puzzle3.lua");
}

void
PuzzleSelectionModel::add_puzzle(std::string i_name, 
				 std::string i_file_name) 
{
  puzzle_names_.push_back(i_name);
  puzzle_file_names_.push_back(i_file_name);
}
