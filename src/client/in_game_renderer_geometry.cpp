#include "in_game_renderer_geometry.hpp"

int
InGameRendererGeometry::mouse_x_as_puzzle_column(int i_x) {
  // TODO(pht) : Handler case where the position is bigger than the screen size
  int res = -1;
  if (i_x >= 0) {
    res = ((i_x - CELLS_X) / CELLS_W);
  }
  return res;
}

int
InGameRendererGeometry::mouse_y_as_puzzle_line(int i_y) {
  // TODO(pht) : Handler case where the position is bigger than the screen size
  int res = -1;
  if (i_y >= 0) {
    res = ((i_y - CELLS_Y) / CELLS_H);
  }
  return res;
}

int
InGameRendererGeometry::mouse_position_as_move_index(int i_x, int i_y) 
{
  int res = -1;
  
  int x = i_x - MOVES_X;
  int y = i_y - MOVES_Y;
  int w = MOVES_W + 10;

  if (y >0 && y < MOVES_H) {
    if (x % w < MOVES_W) {
      res = x / w;
    }
  }

  return res;
}

bool 
InGameRendererGeometry::is_on_undo_button(int i_x, int i_y)
{
  return (i_x > UNDO_X && i_x < UNDO_X + UNDO_W) &&
    (i_y > UNDO_Y && i_y < UNDO_Y + UNDO_H);
}

bool 
InGameRendererGeometry::is_on_redo_button(int i_x, int i_y)
{
  return (i_x > REDO_X && i_x < REDO_X + REDO_W) &&
    (i_y > REDO_Y && i_y < REDO_Y + REDO_H);
}
