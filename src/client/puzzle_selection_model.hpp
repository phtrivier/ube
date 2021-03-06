/**
 * This is Free Software. See COPYING for information.
 */
#ifndef _PUZZLE_SELECTION_MODEL_HPP_
#define _PUZZLE_SELECTION_MODEL_HPP_

#include <vector>
#include <string>

/**
 * Model for the selection of a puzzle
 */
class PuzzleSelectionModel { 

public:

  PuzzleSelectionModel():
    puzzle_index_(-1),
    hovered_index_(-1)
  {
    fill_puzzle_list();
  }

  ~PuzzleSelectionModel() {
  }

  bool has_selected_puzzle() {
    return puzzle_index_ != -1;
  }
  
  std::string get_selected_puzzle_file_name() {
    return puzzle_file_names_[puzzle_index_];
  }

  void set_selected_puzzle_index(int i_index) {
    // TODO : assert
    puzzle_index_ = i_index;
  }

  std::vector<std::string> get_puzzle_names() {
    return puzzle_names_;
  }

  int get_puzzle_count() {
    return (int) puzzle_names_.size();
  }

  bool has_hovered_puzzle() {
    return hovered_index_ != -1;
  }

  int get_hovered_puzzle_index() {
    return hovered_index_;
  }

  void set_hovered_puzzle_index(int i_index) {
    hovered_index_ = i_index;
  }

  void reset() {
    puzzle_index_ = -1;
    hovered_index_ = -1;
  }
  
private:

  // Index of the puzzle selected (clicked on). -1 means
  // no puzzle has been selected yet.
  int puzzle_index_;

  // Index of the puzzle name hovered on. -1 means
  // the mouse is not on top of a puzzle name.
  int hovered_index_;

  // List of the "human readible" names of the puzzle
  std::vector<std::string> puzzle_names_;
  // List of the lua file names for puzzles
  std::vector<std::string> puzzle_file_names_;

  void fill_puzzle_list();

  void add_puzzle(std::string name, std::string file_name);

};

#endif // _PUZZLE_SELECTION_MODEL_HPP_