#include "puzzle_selection_view.hpp"

#include "mvc/controller_interface.hpp"

#include "puzzle_selection_model.hpp"
#include "puzzle_selection_geometry.hpp"
#include "puzzle_selection_renderer_interface.hpp"
#include "game_event.hpp"

#include <vector>
#include <string>

void
PuzzleSelectionView::render_game()
{

  int mouse_x = dep_controller_.mouse_x();
  int mouse_y = dep_controller_.mouse_y();
  int puzzle_index = dep_renderer_.get_mouse_position_as_puzzle_index(mouse_x, mouse_y);
  if (puzzle_index != -1 && puzzle_index < dep_model_.get_puzzle_count()) {
    dep_model_.set_hovered_puzzle_index(puzzle_index);
  }

  dep_renderer_.clear();
  std::vector<std::string> puzzle_names = dep_model_.get_puzzle_names();
  if (dep_model_.has_hovered_puzzle()) {
    dep_renderer_.highlight_puzzle_name(dep_model_.get_hovered_puzzle_index());
  }
  for (int i = 0 ; i < dep_model_.get_puzzle_count() ; i++) {
    dep_renderer_.render_puzzle_name(puzzle_names[i], i);
  }

  dep_renderer_.flush();
}

void
PuzzleSelectionView::handle_event(int i_event)
{

  if (i_event == GameEvent::MOUSE_CLICKED) {
    int mouse_x = dep_controller_.mouse_x();
    int mouse_y = dep_controller_.mouse_y();
    int puzzle_index = dep_renderer_.get_mouse_position_as_puzzle_index(mouse_x, mouse_y);
    
    if (puzzle_index != -1 && puzzle_index < dep_model_.get_puzzle_count()) {
      dep_model_.set_selected_puzzle_index(puzzle_index);
      dep_controller_.fire_event(GameEvent::PUZZLE_SELECTED);
    }
  }
}
