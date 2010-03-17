#ifndef _CELL_HPP_
#define _CELL_HPP_

/**
 * A cell of a puzzle.
 */
class Cell { 

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

  static const int CELL_TYPES[];
  static const int CELL_TYPES_COUNT = 4;
  
  Cell(int iI, int iJ, int iType) : i_(iI), j_(iJ), type_(iType) , in_path_(false) {
  }

  ~Cell();

  int get_i() {
    return i_;
  }

  int get_j() {
    return j_;
  }

  bool is_empty() {
    return type_ == EMPTY;
  }

  bool is_in() {
    return type_ == IN;
  }

  bool is_out() {
    return type_ == OUT;
  }

  bool is_walkable() {
    return type_ == WALKABLE;
  }

  int get_type() {
    return type_;
  }
  
  bool is_in_path() {
    return in_path_;
  }

  void set_in_path(bool i_in_path) {
    in_path_ = i_in_path;
  }

private:

  // Position on the board. 
  // Should be positive.
  int i_, j_;

  // Type of cell. 
  // Should be one of the constants defined below.
  int type_;

  // Is the cell in the last path computed on this puzzle ? 
  bool in_path_;

};

#endif // _CELL_HPP_
