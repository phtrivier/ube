/**
 * This is Free Software. See COPYING for information.
 */
#ifndef _PUZZLE_HPP_
#define _PUZZLE_HPP_

#include "move.hpp"
#include <vector>

class Cell;
class CommandInterface;

/**
 * The board of the game.
 */
class Puzzle { 

public:

  Puzzle() : 
    cells_(NULL),
    scripts_(NULL),
    overlays_(NULL),
    w_(-1), 
    h_(-1), 
    player_i_(-1),
    player_j_(-1)
  {
  }

  ~Puzzle() {
    clear_cells();
  }

  /**
   * Clears all cells in the puzzle,
   * reset dimensions and list of moves.
   */
  void clear();

  /**
   * Set the dimensions of the puzzle, 
   * and prepare it for cell settings.
   * This must be called before any call to 
   * setCellAt.
   */
  void set_dimensions(int iW, int iH);

  int get_w() const {
    return w_;
  }

  int get_h() const {
    return h_;
  }

  /**
   * Add a cell to the puzzle.
   * The cell is added a its corresponding (i,j) position.
   *
   * FIXME(pht) : does the puzzle take ownership of the cell ? 
   * @param ipCell a pointer to a cell.
   */
  void add_cell(Cell * ipCell);

  /**
   * Find a cell by its position.
   * @param iI the line
   * @param iJ the column
   * @return a pointer to the corresponding cell (might be NULL)
   */
  Cell* get_cell_at(int iI, int iJ) const;

  // Is a position valid on this board ?
  bool is_valid_position(int iI, int iJ) const;

  /**
   * Puts the player at the entrance of the puzzle.
   * @return -1 if no entrance was defined in the puzzle, 0 otherwise.
   */
  int enters_player();

  /**
   * Position of the player. -1 if not set.
   */
  int get_player_i() const {
    return player_i_;
  }

  /**
   * Position of the player. -1 if not set.
   */
  int get_player_j() const {
    return player_j_;
  }

  /**
   * Changes the position of the player.
   * @returns -1 if the player cannot be moved becaused the position is invalid or empty.
   *  0 otherwise.
   */
  int put_player(int i_i, int i_j);

  /**
   * Moves that can be used.
   */
  std::vector<Move> & moves() {
    return moves_;
  }

  void add_move(int i_type);

  /**
   * Mark moves at a given index as unuvailable
   */
  int use_move(int i_index);

  int revert_move(int i_index);

  /**
   * Mark a position as being in the last 
   * computed path.
   */
  void mark_in_path(int i_i, int i_j);

  /**
   * Unmark all the cells previously marked as
   * in the last computed path.
   */
  void clear_path();

  /**
   * Has the player reached the exit ? 
   */
  bool is_finished();

  bool has_script(int i_i, int i_j);

  CommandInterface * get_script_at(int i_i, int i_j);

  void add_script(int i_i, int i_j, CommandInterface * i_p_script);

  void do_script_at(int i_i, int i_j);

  void undo_script_at(int i_i, int i_j);

  bool has_overlay(int i_i, int i_j) const;

  int get_overlay(int i_i, int i_j) const;
  
  void set_overlay(int i_i, int i_j, int i_type);

private:

  // Cells
  // Cells are not owned by the puzzle (the puzzle should
  // not try and dealocate them)
  Cell*** cells_;

  // Scripts
  // Scripts are not owned by the puzzle, neither.
  // TODO(pht) : use something more efficient than a sparse matrix ?
  CommandInterface *** scripts_;

  // Overlay types
  int ** overlays_;
  
  // Dimensions
  int w_,h_;

  // Position of the player
  int player_i_;
  int player_j_;

  // Moves
  std::vector<Move> moves_;

  // Clear all the cells
  void clear_cells();

};

#endif // _PUZZLE_HPP_