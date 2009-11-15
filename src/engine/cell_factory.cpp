#include "cell_factory.hpp"
#include "cell.hpp"

#include <sstream>
#include <iostream>
#include <stdexcept>

Cell * CellFactory::make_cell(int iI, int iJ, char iLetter) const {

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
  default : 
    std::ostringstream msg;
    msg << "Invalid cell type " << iLetter;
    throw std::logic_error(msg.str());
  }
  
  return new Cell(iI, iJ, type);
}
