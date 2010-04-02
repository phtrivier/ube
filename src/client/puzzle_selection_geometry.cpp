#include "puzzle_selection_geometry.hpp"

int
PuzzleSelectionGeometry::get_mouse_position_as_puzzle_index(int i_x, int i_y) 
{
  int res = -1;
  int x = i_x - NAMES_X0;
  int y = i_y - NAMES_Y0;
  if (x > 0 && x < NAMES_W) {
    if (y > 0 ) {
      // NOTE(pht) : I know, this does'nt take the delta into
      // account, but that's just not important for the 
      // moment
      res = (y / NAMES_H); 
    }
  }
  return res;
}

int
PuzzleSelectionGeometry::get_puzzle_name_x(int i_index)
{
  return NAMES_X0;
}

int
PuzzleSelectionGeometry::get_puzzle_name_y(int i_index)
{
  return NAMES_Y0 + (NAMES_H *i_index + NAMES_DELTA);
}
