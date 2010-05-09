/**
 * This is Free Software. See COPYING for information.
 */
#ifndef _PUZZLE_SELECTION_MODEL_HPP_
#define _PUZZLE_SELECTION_MODEL_HPP_

#include "selection_model.hpp"
#include "chapter.hpp"

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
    SelectionModel(),
    chapter_("")
  {
  }

  ~PuzzleSelectionModel() {
  }

  std::string get_selected_puzzle_file_name() {
    assert(has_selected());
    return chapter_.puzzle_file_name_at(selected_index());
  }

  std::vector<std::string> & get_puzzle_names() {
    return chapter_.puzzle_names();
  }

  int get_item_count() {
    return (int) chapter_.size();
  }

  void set_chapter(Chapter & i_chapter) {
    chapter_ = i_chapter;
  }

  std::vector<std::string> get_item_names() {
    return chapter_.puzzle_names();
  }
  
private:

  Chapter chapter_;

};

#endif // _PUZZLE_SELECTION_MODEL_HPP_
