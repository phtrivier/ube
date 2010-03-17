#include "cell_factory.hpp"
#include "cell.hpp"

#include <assert.h>
#include <sstream>
#include <iostream>
#include <stdexcept>

bool 
CellFactory::is_valid_cell_letter(char iLetter) const {
  bool res = false;
  switch(iLetter) {
  case 'I':
  case 'O':
  case '#':
  case '-':
    res = true;
  }
  return res;
}

Cell * 
CellFactory::make_cell(int iI, int iJ, char iLetter) {

  assert(is_valid_cell_letter(iLetter));

  int type = Cell::EMPTY;

  switch(iLetter) {
  case 'I' :
    type = Cell::IN;
    break;
  case 'O' : 
    type = Cell::OUT;
    break;
  case '#' : 
    type = Cell::EMPTY;
    break;
  case '-' :
    type = Cell::WALKABLE;
    break;
  }

  Cell * res = new Cell(iI, iJ, type);
  created_cells_.push_back(res);
  
  return res;
}

void
CellFactory::delete_created_cells()
{
  for (int i = 0 ; i < (int) created_cells_.size() ; ++i) {
    assert(created_cells_[i] != NULL);
    delete created_cells_[i];
  }
  created_cells_.clear();
}
