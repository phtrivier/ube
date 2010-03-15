#ifndef _ABTRACT_IN_GAME_RENDERER_HPP_
#define _ABTRACT_IN_GAME_RENDERER_HPP_

#include "in_game_renderer_interface.hpp"

// FIXME(pht) : would'nt it be better if those constants
// here ? 
#define MOVES_X 20
#define MOVES_Y 450
#define MOVES_H 64
#define MOVES_W 128

#define CELLS_X 40
#define CELLS_Y 40
#define CELLS_W 32
#define CELLS_H 32

/**
 * Renderer that knows the geometry of the screen, but does actually
 * render stuff.
 *
 */
class AbtractInGameRenderer :
  public InGameRendererInterface
{ 

public:

  AbstractInGameRenderer() :
    InGameRendererInterface {
  }

  virtual ~AbstractInGameRenderer() {
  }

  virtual void clear() = 0;

  virtual void render_cell(int i_i, int i_j, int i_cell_type) = 0;

  virtual void flush() = 0;

  int mouse_x_as_puzzle_column(int i_x) = 0;
  
  int mouse_y_as_puzzle_line(int i_y) = 0;
  
  int mouse_position_as_move_index(int i_x, int i_y) = 0;

  virtual void render_selected_cell(int i_i, int i_j) = 0;

  virtual void render_banned_cell(int i_i, int i_j) = 0;

  virtual void render_player(int i_i, int i_j) = 0;

  virtual void render_moves(InGameModel & i_model) = 0;

};

#endif // _ABTRACT_IN_GAME_RENDERER_HPP_
