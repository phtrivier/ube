#ifndef _PUZZLE_SELECTION_GEOMETRY_HPP_
#define _PUZZLE_SELECTION_GEOMETRY_HPP_


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
