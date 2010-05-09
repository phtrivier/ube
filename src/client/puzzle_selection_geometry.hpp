/**
 * This is Free Software. See COPYING for information.
 */
#ifndef _PUZZLE_SELECTION_GEOMETRY_HPP_
#define _PUZZLE_SELECTION_GEOMETRY_HPP_

#define NAMES_X0 50
#define NAMES_Y0 100
#define NAMES_H 40
#define NAMES_W 700
#define NAMES_DELTA 20

#define BACK_X0 20
#define BACK_Y0 570
#define BACK_W 100
#define BACK_H 50


/**
 * Geometry of the puzzle selection screen
 */
class PuzzleSelectionGeometry { 

public:

  int get_mouse_position_as_puzzle_index(int i_x, int i_y);

  int get_puzzle_name_x(int i_index);
  
  int get_puzzle_name_y(int i_index);

  bool is_on_back_button(int i_x, int i_y);
  
  bool is_in_box(int i_x, int i_y, int i_x0, int i_y0, int i_w, int i_h) {
    return (i_x > i_x0 && i_x < i_x0 + i_w && 
	    i_y > i_y0 && i_y < i_y0 + i_h);
  }

};

#endif // _PUZZLE_SELECTION_GEOMETRY_HPP_
