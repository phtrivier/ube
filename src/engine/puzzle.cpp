#include "puzzle.hpp"
#include "cell.hpp"

#include <cstddef>
#include <sstream>
#include <iostream>
#include <stdexcept>
using namespace std;

void Puzzle::ensure_valid_position(int iI, int iJ) const {
  if (iI<0 || iI >= h_ || iJ >= w_ || iJ < 0) {
    std::ostringstream msg;
    msg << "Invalid position : (" 
	<< iI << "," << iJ << ")";
    throw logic_error(msg.str());
  }
}

void Puzzle::setDimensions(int iW, int iH) {

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
    for (int j = 0 ; j < w_ ; j++) {
      cells_[i][j] = NULL;
    }
  }
}

void Puzzle::addCell(Cell * ipCell) {
  if (ipCell == NULL) {
    throw logic_error("Null Cell");
  }
  ensure_valid_position(ipCell->getI(), ipCell->getJ());
  cells_[ipCell->getI()][ipCell->getJ()] = ipCell;  
}

Cell* Puzzle::getCellAt(int iI, int iJ) const {
  ensure_valid_position(iI, iJ);
  return cells_[iI][iJ];
}


