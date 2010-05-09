/**
 * This is Free Software. See COPYING for information.
 */
#include "selection_view.hpp"

#include "engine/game_event.hpp"

#include "common/logging.hpp"

#include "mvc/controller_interface.hpp"

#include "selection_model.hpp"
#include "selection_renderer_interface.hpp"

#include <vector>
#include <string>

void
SelectionView::render_game()
{

  int mouse_x = dep_controller_.mouse_x();
  int mouse_y = dep_controller_.mouse_y();

  int item_index = dep_renderer_.get_mouse_position_as_item_index(mouse_x, mouse_y);

  if (item_index != -1 && item_index < dep_model_.get_item_count()) {
    dep_model_.set_hovered_index(item_index);
  } else if (item_index == -1) {
    dep_model_.set_hovered_index(0);
  } else if (item_index > dep_model_.get_item_count()) {
    dep_model_.set_hovered_index(dep_model_.get_item_count() -1);
  }

  LOG_D("view") << "(after changed) Model has hovered ?" << dep_model_.has_hovered() << std::endl;
  LOG_D("view") << "(after changed) Model hovered ?" << dep_model_.get_hovered_index() << std::endl;

  dep_renderer_.clear();
  std::vector<std::string> item_names = dep_model_.get_item_names();
  if (dep_model_.has_hovered()) {
    dep_renderer_.highlight_item_name(dep_model_.get_hovered_index());
  }

  for (int i = 0 ; i < dep_model_.get_item_count() ; i++) {
    dep_renderer_.render_item_name(item_names[i], i);
  }

  dep_renderer_.flush();
}

void
SelectionView::handle_event(int i_event)
{
  if (i_event == GameEvent::MOUSE_CLICKED) {
    int mouse_x = dep_controller_.mouse_x();
    int mouse_y = dep_controller_.mouse_y();
    int item_index = dep_renderer_.get_mouse_position_as_item_index(mouse_x, mouse_y);

    if (item_index != -1 && item_index < dep_model_.get_item_count()) {
      dep_model_.set_selected_index(item_index);
    } else if (item_index == -1 
	       && dep_model_.has_hovered() 
	       && dep_model_.get_hovered_index() == 0) {

      dep_model_.set_selected_index(0);
    } else if (item_index > dep_model_.get_item_count()
	       && dep_model_.has_hovered()
	       && dep_model_.get_hovered_index() == dep_model_.get_item_count() - 1) {
      dep_model_.set_selected_index(dep_model_.get_item_count() - 1);
    }
   
  }
}
