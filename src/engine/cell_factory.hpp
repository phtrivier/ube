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
  Cell * make_cell(int iI, int iJ, char iLetter) const;
};

#endif // _CELL_FACTORY_HPP_
