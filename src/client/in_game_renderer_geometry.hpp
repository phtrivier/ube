/**
 * This is Free Software. See COPYING for information.
 */
#ifndef _IN_GAME_RENDERER_GEOMETRY_HPP_
#define _IN_GAME_RENDERER_GEOMETRY_HPP_

// FIXME(pht) : would'nt it be better if those constants
// here ? 
#define MOVES_X (20 + 64 + 10 + 64 + 10)
#define MOVES_Y 450
#define MOVES_H 64
#define MOVES_W 128

#define CELLS_X 40
#define CELLS_Y 40
#define CELLS_W 32
#define CELLS_H 32

#define UNDO_X 20
#define UNDO_Y 450
#define UNDO_H 64
#define UNDO_W 64

#define REDO_X UNDO_X + UNDO_W
#define REDO_Y 450
#define REDO_H 64
#define REDO_W 64

/**
 * Geometry of the screen.
 */
class InGameRendererGeometry
{ 

public:

  InGameRendererGeometry() {
  }

  virtual ~InGameRendererGeometry() {
  }

  int mouse_x_as_puzzle_column(int i_x);
  
  int mouse_y_as_puzzle_line(int i_y);
  
  int mouse_position_as_move_index(int i_x, int i_y);

  bool is_on_undo_button(int i_x, int i_y);

  bool is_on_redo_button(int i_x, int i_y);

};

#endif // _IN_GAME_RENDERER_GEOMETRY_HPP_
