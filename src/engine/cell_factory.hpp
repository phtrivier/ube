#ifndef _CELL_FACTORY_HPP_
#define _CELL_FACTORY_HPP_

class Cell;

/**
 * This class is used to create puzzle cell from 
 * letters.
 * 
 * Standard letters are : 
 *  # for empty cells
 *  I for the entry
 *  O for the exit
 *  - for walkable cells
 */
class CellFactory { 

public:

  /**
   * Is a letter parsable as a cell ? 
   *
   * @param iLetter : a letter 
   */
  bool is_valid_cell_letter(char iLetter) const;

  /**
   * Create a cell for a given letter.
   *
   * @param iI : a row index (should be positive)
   * @param iJ : a column index (should be positive)
   * @param iLetter : a letter representing a cell (should be valid, as defined by is_valid_cell_letter)
   */
  Cell * make_cell(int iI, int iJ, char iLetter) const;
};

#endif // _CELL_FACTORY_HPP_
