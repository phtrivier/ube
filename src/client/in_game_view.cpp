#include "in_game_view.hpp"

#include "common/logging.hpp"
#include "engine/cell.hpp"
#include "engine/puzzle.hpp"

#include "game_event.hpp"
#include "in_game_model.hpp"
#include "in_game_renderer_interface.hpp"
#include "controller_interface.hpp"

#include <assert.h>

void
InGameView::render_game() {
  dep_renderer_.clear();
  render_puzzle(dep_model_.get_puzzle());
  render_selected_cell(dep_model_.get_puzzle());
  render_path(dep_model_);
  render_player(dep_model_.get_puzzle());
  dep_renderer_.render_moves(dep_model_);
  update_goal(dep_model_);
  dep_renderer_.flush();
}

void
InGameView::handle_event(int iEventCode) {
  if (iEventCode == GameEvent::MOUSE_CLICKED) {
    int mouse_x = dep_controller_.mouse_x();
    int mouse_y = dep_controller_.mouse_y();
    int i = dep_renderer_.mouse_y_as_puzzle_line(mouse_y);
    int j = dep_renderer_.mouse_x_as_puzzle_column(mouse_x);

    // FIXME(pht) : the following really looks like it belongs to the model... 

    if (i!=-1 && j!=-1 && 
	dep_model_.get_puzzle().is_valid_position(i,j)) {

      if (dep_model_.get_puzzle().get_cell_at(i,j)->is_in_path()) {
	// FIXME(pht) : use the Command pattern to make the following undo-able
	dep_model_.get_puzzle().moves()[dep_model_.current_move_index()].use();
	dep_model_.get_puzzle().put_player(i,j);

	// Change the current move to be the next available one
	dep_model_.set_next_available_move_as_current();
      }
    }

    // FIXME(pht) : again, some of this really belongs to the model, but
    // I am not in the mood for creating methods ;)
    int move_index = dep_renderer_.mouse_position_as_move_index(mouse_x, mouse_y);
    if (move_index != -1 && 
	move_index < (int) dep_model_.get_puzzle().moves().size()) {
      if (dep_model_.get_puzzle().moves()[move_index].available()) {
	  dep_model_.set_current_move_index(move_index);
      }
    }
  }
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
	  /*
	  dep_renderer_.render_selected_cell(i,j);
	  */
	  dep_renderer_.render_banned_cell(i,j);
	}
      }
    }
  }
}

void 
InGameView::update_goal(InGameModel & i_model) {
  // Update the position of the cursor
  int mouse_x = dep_controller_.mouse_x();
  int mouse_y = dep_controller_.mouse_y();
  int j = dep_renderer_.mouse_x_as_puzzle_column(mouse_x);
  if (j != -1) {
    int i = dep_renderer_.mouse_y_as_puzzle_line(mouse_y);
    if (i != -1) {
      i_model.set_goal(i,j);
    }
  }
}

void
InGameView::render_path(InGameModel & i_model) {
  
  // Render the existing path if any (note that both stuff
  // could be done in another order, but one frame
  // should not be too much to cause a glitch)
  Puzzle & puzzle = i_model.get_puzzle();
  for (int i = 0 ; i < puzzle.get_h() ; i++) {
    for (int j = 0 ; j < puzzle.get_w() ; j++) {
      if (puzzle.get_cell_at(i,j)->is_in_path()) {
	// TODO : render other kind of cell
	dep_renderer_.render_selected_cell(i,j);
      }
    }
  }
  
}

void
InGameView::render_player(const Puzzle & i_puzzle) {
  if (i_puzzle.get_player_i() != -1 &&
      i_puzzle.get_player_j() != -1) {
    dep_renderer_.render_player(i_puzzle.get_player_i(), i_puzzle.get_player_j());
  }
}
