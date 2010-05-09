/**
 * This is Free Software. See COPYING for information.
 */

#ifndef _CHAPTER_SELECTION_MODEL_HPP_
#define _CHAPTER_SELECTION_MODEL_HPP_

#include "selection_model.hpp"
#include "chapter.hpp"

#include <assert.h>
#include <string>
#include <vector>

#include <boost/foreach.hpp>


/**
 * Model for the selection of a chapter
 */
class ChapterSelectionModel : 
  public SelectionModel
{ 

public:

  ChapterSelectionModel():
    SelectionModel()
  {
    fill_chapters();
  }

  ~ChapterSelectionModel();

  Chapter & get_selected_chapter() {
    assert(has_selected());
    return *(chapters_[selected_index()]);
  }
  
  void clear() {
    chapters_.clear();
  }
  
  void fill_chapters();

  int get_item_count() {
    return chapters_.size();
  }
  
  std::vector<std::string> get_item_names() {
    std::vector<std::string> res;
    BOOST_FOREACH(Chapter * p_chapter, chapters_) {
      res.push_back(p_chapter->chapter_name());
    }
    return res;
  }

  bool has_chapter_with_puzzle(std::string i_puzzle_file_name);

  Chapter & get_chapter_with_puzzle(std::string i_puzzle_file_name);

private:
  
  std::vector<Chapter *> chapters_;

};

#endif // _CHAPTER_SELECTION_MODEL_HPP_
