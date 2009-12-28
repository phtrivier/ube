#include "puzzle.hpp"
#include "cell.hpp"

#include <assert.h>
#include <cstddef>
#include <sstream>
#include <iostream>
#include <stdexcept>
using namespace std;

bool Puzzle::is_valid_position(int iI, int iJ) const {
  if (iI < 0) return false;
  if (iI >= h_) return false;
  if (iJ < 0) return false;
  if (iJ >= w_) return false;
  return true;
}

void Puzzle::set_dimensions(int iW, int iH) {
  assert(iW > 0);
  assert(iH > 0);

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

void Puzzle::add_cell(Cell * ipCell) {
  assert(ipCell != NULL);
  assert(is_valid_position(ipCell->get_i(), ipCell->get_j()));
  cells_[ipCell->get_i()][ipCell->get_j()] = ipCell;  
}

Cell* Puzzle::get_cell_at(int iI, int iJ) const {
  assert(is_valid_position(iI, iJ));
  return cells_[iI][iJ];
}


