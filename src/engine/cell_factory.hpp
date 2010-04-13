/**
 * This is Free Software. See COPYING for information.
 */
#ifndef _CELL_FACTORY_HPP_
#define _CELL_FACTORY_HPP_

#include <vector>

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
  Cell * make_cell(int iI, int iJ, char iLetter);

  /**
   * Delete all the cells previously created by this 
   * factory.
   */
  void delete_created_cells();

private:

  std::vector<Cell *> created_cells_;

};

#endif // _CELL_FACTORY_HPP_