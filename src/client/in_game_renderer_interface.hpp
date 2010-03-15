#ifndef _IN_GAME_RENDERER_INTERFACE_HPP_
#define _IN_GAME_RENDERER_INTERFACE_HPP_

class InGameModel;

/**
 * renderer for in game view.
 */
class InGameRendererInterface { 

public:

  virtual ~InGameRendererInterface() {
  }

  /**
   * Clears the screen
   */
  virtual void clear() = 0;
  
  /**
   * Renders a cell at a given position.
   */
  virtual void render_cell(int i_i, int i_j, int i_cell_type) = 0;

  /**
   * Finalize renderering
   */
  virtual void flush() = 0;

  /**
   * Convert a pointer x position to a column of the puzzle.
   *
   * @param i_x a mouse position, relative to the screen
   * @returns a column index if the curser is on top of a potential puzzle cell (even an 
   *   empty one), -1 otherwise.
   */
  virtual int mouse_x_as_puzzle_column(int i_x) = 0;

  /**
   * Convert a pointer y position to a column of the puzzle.
   *
   * @param i_y a mouse position, relative to the screen
   * @returns a line index if the curser is on top of a potential puzzle cell (even an 
   *   empty one), -1 otherwise.
   */
  virtual int mouse_y_as_puzzle_line(int i_y) = 0;

  /**
   * The mouse position as a "move" button index, or 
   * -1 if it is not on top of a "move" button.
   */
  virtual int mouse_position_as_move_index(int i_x, int i_y) = 0;

  /**
   * Marks the cell at a given position as the selected one.
   */
  virtual void render_selected_cell(int i_i, int i_j) = 0;

  virtual void render_banned_cell(int i_i, int i_j) = 0;

  /**
   * Display the player in the maze.
   */
  virtual void render_player(int i_i, int i_j) = 0;

  /**
   * Displays the list of available moves
   */
  virtual void render_moves(InGameModel & i_model) = 0;
 

};

#endif // _IN_GAME_RENDERER_INTERFACE_HPP_
