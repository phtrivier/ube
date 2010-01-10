#include "in_game_view.hpp"

#include "common/logging.hpp"
#include "engine/cell.hpp"
#include "engine/puzzle.hpp"

#include "in_game_model.hpp"
#include "in_game_renderer_interface.hpp"
#include "controller_interface.hpp"

#include <assert.h>

void
InGameView::render_game() {
  dep_renderer_.clear();
  render_puzzle(dep_model_.get_puzzle());
  render_selected_cell(dep_model_.get_puzzle());
  dep_renderer_.flush();
}

void
InGameView::render_puzzle(const Puzzle & i_puzzle) {
  assert(i_puzzle.get_w() > 0);
  assert(i_puzzle.get_h() > 0);
  for (int i = 0 ; i < i_puzzle.get_h() ; i++) {
    for (int j= 0 ; j < i_puzzle.get_w() ; j++) {
      dep_renderer_.render_cell(i,j,i_puzzle.get_cell_at(i,j)->get_type());
    }
  }
}

void
InGameView::render_selected_cell(const Puzzle & i_puzzle) {
  int mouse_x = dep_controller_.mouse_x();
  int mouse_y = dep_controller_.mouse_y();

  LOG_D("view") << "Mouse position : [" << mouse_x << "," << mouse_y << "]";

  int j = dep_renderer_.mouse_x_as_puzzle_column(mouse_x);
  if (j != -1) {
    int i = dep_renderer_.mouse_y_as_puzzle_line(mouse_y);
    if (i != -1) {
      if (i_puzzle.is_valid_position(i,j)) {
	assert(i_puzzle.get_cell_at(i,j) != NULL);
	if (!i_puzzle.get_cell_at(i,j)->is_empty()) {
	  dep_renderer_.render_selected_cell(i,j);
	}
      }
    }
  }
}
