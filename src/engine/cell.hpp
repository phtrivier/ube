#ifndef _CELL_HPP_
#define _CELL_HPP_

/**
 * A cell of a puzzle.
 */
class Cell { 

  // Position on the board. 
  // Should be positive.
  int i_, j_;

  // Type of cell. 
  // Should be one of the constants defined below.
  int type_;

public:

  // Constants to represent cell types.
  // Note(pht) : I deliberately use ints here instead
  // of an enum, because in the future I want
  // it to be possible to dynamically add 
  // cell types.
  static const int EMPTY = 0;
  static const int IN = 1;
  static const int OUT = 2;
  static const int WALKABLE = 3;
  
  Cell(int iI, int iJ, int iType) : i_(iI), j_(iJ), type_(iType) {
  }

  int getI() {
    return i_;
  }

  int getJ() {
    return j_;
  }

  bool isEmpty() {
    return type_ == EMPTY;
  }

  bool isIn() {
    return type_ == IN;
  }

  bool isOut() {
    return type_ == OUT;
  }

  bool isWalkable() {
    return type_ == WALKABLE;
  }
  
};

#endif // _CELL_HPP_
