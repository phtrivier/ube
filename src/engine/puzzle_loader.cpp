/**
 * This is Free Software. See COPYING for information.
 */
#include "puzzle_loader.hpp"
#include "cell_factory.hpp"
#include "puzzle.hpp"

#include <stdexcept>
#include <cstring>
#include "boost/format.hpp"
using boost::format;

void PuzzleLoader::set_row(int i, Puzzle * poPuzzle, const char * row) {
  assert(poPuzzle != NULL);
  assert(row != NULL);
  assert(i>=0);
  assert(i < poPuzzle->get_h());
  assert(((int) strlen(row)) == poPuzzle->get_w());
  
  for (int j = 0 ; j < poPuzzle->get_w() ; j++) {
    assert(pFactory_->is_valid_cell_letter(row[j]));
    Cell * pNewCell = pFactory_->make_cell(i,j, row[j]);
    assert(pNewCell != NULL); // I did check before, so I should not get into any trouble !
    poPuzzle->add_cell(pNewCell);
  }

}