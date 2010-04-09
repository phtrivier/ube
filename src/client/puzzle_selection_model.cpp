#include "puzzle_selection_model.hpp"

#include "common/i18n.hpp"

void 
PuzzleSelectionModel::fill_puzzle_list()
{
  add_puzzle(_("From here to there (you can move, like.)"), "tutorial0.lua");
  add_puzzle(_("Twice as fast (you can move even faster, like.)"), "tutorial0a.lua");
  add_puzzle(_("Ouch, a wall. You can cross it. Trust me."), "tutorial1.lua");
  add_puzzle(_("Okay, let's get funnier..."), "tutorial2.lua");
  add_puzzle(_("Relax. You'll pick up along the way."), "tutorial3.lua");
  add_puzzle(_("Too simple ? Let's see..."), "tutorial4.lua");
}

void
PuzzleSelectionModel::add_puzzle(std::string i_name, 
				 std::string i_file_name) 
{
  puzzle_names_.push_back(i_name);
  puzzle_file_names_.push_back(i_file_name);
}
