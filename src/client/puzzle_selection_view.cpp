#include "puzzle_selection_view.hpp"

#include "puzzle_selection_model.hpp"
#include "puzzle_selection_renderer_interface.hpp"

#include <vector>
#include <string>

void
PuzzleSelectionView::render_game()
{
  std::vector<std::string> puzzle_names = dep_model_.get_puzzle_names();
  for (int i = 0 ; i < dep_model_.get_puzzle_count() ; i++) {
    dep_renderer_.render_puzzle_name(puzzle_names[i], i);
  }
}

void
PuzzleSelectionView::handle_event(int i_event)
{

}
