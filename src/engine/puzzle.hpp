#ifndef _PUZZLE_HPP_
#define _PUZZLE_HPP_

class Cell;



/**
 * The board of the game.
 */
class Puzzle { 

public:

  Puzzle() {
    w_ = h_ = -1;
  }

  ~Puzzle() {
  }

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

private:

  // Dimensions
  int w_,h_;

  // Cells
  Cell*** cells_;

};

#endif // _PUZZLE_HPP_
