#include "in_game_view.hpp"
#include "in_game_model.hpp"
#include "in_game_renderer_interface.hpp"

#include "engine/cell.hpp"
#include "engine/puzzle.hpp"

#include <assert.h>

void
InGameView::render_game() {
  dep_renderer_.clear();
  render_puzzle(dep_model_.get_puzzle());
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
