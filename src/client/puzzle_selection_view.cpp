/**
 * This is Free Software. See COPYING for information.
 */
#include "puzzle_selection_view.hpp"

#include "common/logging.hpp"

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

  LOG_D("view") << "Rendering puzzle selection" << std::endl;
  LOG_D("view") << "Model has hovered ?" << dep_model_.has_hovered_puzzle() << std::endl;
  
  int mouse_x = dep_controller_.mouse_x();
  int mouse_y = dep_controller_.mouse_y();

  LOG_D("view") << "Mouse x " << mouse_x << std::endl;
  LOG_D("view") << "Mouse y " << mouse_y << std::endl;

  LOG_D("view") << "Model has hovered ?" << dep_model_.has_hovered_puzzle() << std::endl;
  
  int puzzle_index = dep_renderer_.get_mouse_position_as_puzzle_index(mouse_x, mouse_y);

  LOG_D("view") << "Puzzle index ?" << puzzle_index << std::endl;

  if (puzzle_index != -1 && puzzle_index < dep_model_.get_puzzle_count()) {
    dep_model_.set_hovered_puzzle_index(puzzle_index);
  } else if (puzzle_index == -1) {
    dep_model_.set_hovered_puzzle_index(0);
  } else if (puzzle_index > dep_model_.get_puzzle_count()) {
    dep_model_.set_hovered_puzzle_index(dep_model_.get_puzzle_count() -1);
  }

  LOG_D("view") << "(after changed) Model has hovered ?" << dep_model_.has_hovered_puzzle() << std::endl;
  LOG_D("view") << "(after changed) Model hovered ?" << dep_model_.get_hovered_puzzle_index() << std::endl;
  

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
    } else if (puzzle_index == -1 
	       && dep_model_.has_hovered_puzzle() 
	       && dep_model_.get_hovered_puzzle_index() == 0) {

      dep_model_.set_selected_puzzle_index(0);
    } else if (puzzle_index > dep_model_.get_puzzle_count()
	       && dep_model_.has_hovered_puzzle()
	       && dep_model_.get_hovered_puzzle_index() == dep_model_.get_puzzle_count() - 1) {
      dep_model_.set_selected_puzzle_index(dep_model_.get_puzzle_count() - 1);
    }
    
    if (dep_model_.has_selected_puzzle()) {
      dep_controller_.fire_event(GameEvent::PUZZLE_SELECTED);
    }
      
  }
}