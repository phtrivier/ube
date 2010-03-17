#include "puzzle.hpp"
#include "cell.hpp"
#include "move.hpp"

#include <assert.h>
#include <cstddef>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std;

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

bool Puzzle::is_valid_position(int iI, int iJ) const {
  if (iI < 0) return false;
  if (iI >= h_) return false;
  if (iJ < 0) return false;
  if (iJ >= w_) return false;
  return true;
}

int Puzzle::enters_player() {
  int res = -1;
  for (int i = 0 ; res == -1 && i < h_ ; i++) {
    for (int j = 0 ; res == -1 && j < w_ ; j++) {
      if (cells_[i][j]->is_in()) {
	player_i_ = i;
	player_j_ = j;
	res = 0;
      }
    }
  }
  return res;
}

int Puzzle::put_player(int i_i, int i_j) {
  int res = -1;
  if (is_valid_position(i_i,i_j)) {
    if (!cells_[i_i][i_j]->is_empty()) {
      player_i_ = i_i;
      player_j_ = i_j;
      res = 0;
    }
  }
  return res;
}

void Puzzle::add_move(int i_type) {
  Move move(i_type);
  moves_.push_back(move);
}

int Puzzle::use_move(int i_index) {
  int res = -1;
  assert(i_index >= 0);
  assert(moves_.size() - i_index > 0);
  if (moves_[i_index].available()) {
    moves_[i_index].use();
    res = 0;
  }
  return res;
}

int Puzzle::revert_move(int i_index) {
  int res = -1;
  assert(i_index >= 0);
  assert(moves_.size() - i_index > 0);
  if (!moves_[i_index].available()) {
    moves_[i_index].revert();
    res = 0;
  }
  return res;
}

void
Puzzle::mark_in_path(int i_i, int i_j) 
{
  assert(is_valid_position(i_i, i_j));
  if (get_cell_at(i_i, i_j) != NULL) {
    get_cell_at(i_i,i_j)->set_in_path(true);
  }  
}

void
Puzzle::clear_path()
{
  for (int i = 0 ; i < h_ ; i++) {
    for (int j = 0 ; j < w_ ; j++) {
      if (get_cell_at(i,j) != NULL) {
	get_cell_at(i,j)->set_in_path(false);
      }
    }
  }
}

void
Puzzle::clear_cells()
{
  for (int i = 0 ; i < h_ ; i++) {
    if (cells_[i] != NULL) {
      delete[] cells_[i];
    }
  }
  if (cells_ != NULL) {
    delete[] cells_;
  }
}

bool
Puzzle::is_finished()
{
  return is_valid_position(player_i_, player_j_) &&
    get_cell_at(player_i_, player_j_)->is_out();
}
