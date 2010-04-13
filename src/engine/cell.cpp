/**
 * This is Free Software. See COPYING for information.
 */
#include "cell.hpp"

#include "common/logging.hpp"

#include <iostream>

const int Cell::CELL_TYPES[] = { EMPTY, IN, OUT, WALKABLE };

Cell::~Cell() {
  LOG_D("cell") << "dtor called on cell at " << i_ << "," << j_ << std::endl;
}