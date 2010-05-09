/**
 * This is Free Software. See COPYING for information.
 */
#ifndef _PUZZLE_SELECTION_MODEL_HPP_
#define _PUZZLE_SELECTION_MODEL_HPP_

#include "selection_model.hpp"

#include <assert.h>
#include <vector>
#include <string>

/**
 * Model for the selection of a puzzle
 */
class PuzzleSelectionModel : 
  public SelectionModel
{ 

public:

  PuzzleSelectionModel():
    SelectionModel()
  {
    fill_puzzle_list();
  }

  ~PuzzleSelectionModel() {
  }

  std::string get_selected_puzzle_file_name() {
    assert(has_selected());
    return puzzle_file_names_[selected_index()];
  }

  std::vector<std::string> get_puzzle_names() {
    return puzzle_names_;
  }

  int get_puzzle_count() {
    return (int) puzzle_names_.size();
  }

  /**
   * Clear the lists of puzzles.
   */
  void clear();

private:

  // List of the "human readible" names of the puzzle
  std::vector<std::string> puzzle_names_;
  // List of the lua file names for puzzles
  std::vector<std::string> puzzle_file_names_;

  /**
   * Add a puzzle to this model
   * @param name the string displayed to select this model
   * @param file_name the name of the lua puzzle file to load (eg "tutorial1.lua") 
   */
  void add_puzzle(std::string name, std::string file_name);

  void fill_puzzle_list();

};

#endif // _PUZZLE_SELECTION_MODEL_HPP_
