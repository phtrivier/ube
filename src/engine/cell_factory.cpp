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
CellFactory::make_cell(int iI, int iJ, char iLetter) const {

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
  
  return new Cell(iI, iJ, type);
}
