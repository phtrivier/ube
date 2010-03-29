#ifndef _PUZZLE_SELECTION_GEOMETRY_HPP_
#define _PUZZLE_SELECTION_GEOMETRY_HPP_

#define NAMES_X0 50
#define NAMES_Y0 100
#define NAMES_H 40
#define NAMES_W 700
#define NAMES_DELTA 20

/**
 * Geometry of the puzzle selection screen
 */
class PuzzleSelectionGeometry { 

public:

  int get_mouse_position_as_puzzle_index(int i_x, int i_y);

  int get_puzzle_name_x(int i_index);
  
  int get_puzzle_name_y(int i_index);

};

#endif // _PUZZLE_SELECTION_GEOMETRY_HPP_
