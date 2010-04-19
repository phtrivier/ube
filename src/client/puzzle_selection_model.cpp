/**
 * This is Free Software. See COPYING for information.
 */
#include "puzzle_selection_model.hpp"

#include "common/i18n.hpp"

void 
PuzzleSelectionModel::fill_puzzle_list()
{
  add_puzzle(_("Let's find the exit, for a start..."), "tutorial0.lua");
  add_puzzle(_("Sometimes you have to jump."), "tutorial1.lua");
  add_puzzle(_("A wall. You can cross it. Trust me."), "tutorial2.lua");
  add_puzzle(_("Let's complicate a bit (just a bit.)"), "tutorial3.lua");
  add_puzzle(_("You'll find a solution along the way..."), "tutorial4.lua");
  add_puzzle(_("Be wise. Clock wise."), "tutorial5.lua");
  add_puzzle(_("Looks easy ? Look again..."), "tutorial6.lua");
  add_puzzle(_("Still too simple ? Let's see..."), "tutorial7.lua");
}

void
PuzzleSelectionModel::add_puzzle(std::string i_name, 
				 std::string i_file_name) 
{
  puzzle_names_.push_back(i_name);
  puzzle_file_names_.push_back(i_file_name);
}
