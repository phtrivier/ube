#include "puzzle.hpp"
#include <cstddef>

#include <sstream>
#include <iostream>
#include <stdexcept>
using namespace std;

void
Puzzle::setDimensions(int iW, int iH) {

  if (iW <= 0 || iH <= 0) {
    std::ostringstream msg;
    msg << "Invalid dimensions : (" 
	<< iW << "," << iH << ")";
    throw logic_error(msg.str());
  }

  w_ = iW;
  h_ = iH;
  cells_ = new Cell**[h_];
  for (int i = 0 ; i < iH ; i++) {
    cells_[i] = new Cell*[w_];
    for (int j = 0 ; j < iW ; j++) {
      cells_[i][j] = NULL;
    }
  }
}

Cell*
Puzzle::getCellAt(int iI, int IJ) const {
  // TODO
  return 0;
}
