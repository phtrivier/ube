#include "puzzle_loader.hpp"
#include "cell_factory.hpp"
#include "puzzle.hpp"

#include <stdexcept>
#include <cstring>
#include "boost/format.hpp"
using boost::format;

void PuzzleLoader::set_row(int i, Puzzle * poPuzzle, const char * row) {
   
  // Dimensions check
  if (i<0 || i >= poPuzzle->get_h()) {
    throw std::logic_error(str(format("Bad row index %1%") % i));
  } else {
    int w_row = strlen(row);
    if ( w_row != poPuzzle->get_w()) {
      throw std::logic_error(str(format("Bad row width %1%") % w_row));
    }
  }

  for (int j = 0 ; j < poPuzzle->get_w() ; j++) {
    poPuzzle->add_cell(pFactory_->make_cell(i,j, row[j]));
  }

}

