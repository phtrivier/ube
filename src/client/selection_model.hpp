/**
 * This is Free Software. See COPYING for information.
 */
#ifndef _SELECTION_MODEL_HPP_
#define _SELECTION_MODEL_HPP_

#include <vector>
#include <string>

/**
 * Generic model for the selection of stuff
 */
class SelectionModel { 

public:

  SelectionModel():
    selected_index_(-1),
    hovered_index_(-1)
  {
  }

  ~SelectionModel() {
  }

  int selected_index() {
    return selected_index_;
  }

  int hovered_index() {
    return hovered_index_;
  }

  bool has_selected() {
    return selected_index_ != -1;
  }
  
  void set_selected_index(int i_index) {
    selected_index_ = i_index;
  }

  bool has_hovered() {
    return hovered_index_ != -1;
  }

  int get_hovered_index() {
    return hovered_index_;
  }

  void set_hovered_index(int i_index) {
    hovered_index_ = i_index;
  }

  void reset() {
    selected_index_ = -1;
    hovered_index_ = -1;
  }

private:

  // Index of the selected item (clicked on). -1 means
  // no item has been selected yet.
  int selected_index_;

  // Index of the puzzle name hovered on. -1 means
  // the mouse is not on top of a puzzle name.
  int hovered_index_;

};

#endif // _SELECTION_MODEL_HPP_
