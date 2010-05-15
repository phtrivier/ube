/**
 * This is Free Software. See COPYING for information.
 */

#include "chapter.hpp"
#include "chapter_selection_model.hpp"

#include "common/i18n.hpp"

#include <assert.h>
#include <boost/foreach.hpp>

ChapterSelectionModel::~ChapterSelectionModel()
{
  BOOST_FOREACH(Chapter * p_chapter, chapters_) {
    delete p_chapter;
  }
  chapters_.clear();
}

void
ChapterSelectionModel::fill_chapters()
{
  Chapter * p_tutorial = new Chapter(_("Tutorial"));
  p_tutorial->add_puzzle(_("Let's find the exit, for a start..."), "tutorial0.lua");
  p_tutorial->add_puzzle(_("Sometimes you have to jump."), "tutorial1.lua");
  p_tutorial->add_puzzle(_("A wall. You can cross it. Trust me."), "tutorial2.lua");
  p_tutorial->add_puzzle(_("Let's complicate a bit (just a bit.)"), "tutorial3.lua");
  p_tutorial->add_puzzle(_("You'll find a solution along the way..."), "tutorial4.lua");
  p_tutorial->add_puzzle(_("Be wise. Clock wise."), "tutorial5.lua");
  p_tutorial->add_puzzle(_("Looks easy ? Look again..."), "tutorial6.lua");
  p_tutorial->add_puzzle(_("Still too simple ? Let's see..."), "tutorial7.lua");
  chapters_.push_back(p_tutorial);

  Chapter * p_begin = new Chapter(_("Beginning"));
  p_begin->add_puzzle(_("A knight. My kingdom for a knight !"), "begin0.lua");
  chapters_.push_back(p_begin);

}


bool 
ChapterSelectionModel::has_chapter_with_puzzle(std::string i_puzzle_file_name)
{
  bool res = false;
  BOOST_FOREACH(Chapter * p_chapter, chapters_) {
    if (p_chapter->has_puzzle_file_name(i_puzzle_file_name)) {
      res = true;
      break;
    }
  }
  return res;
}

Chapter & 
ChapterSelectionModel::get_chapter_with_puzzle(std::string i_puzzle_file_name)
{
  Chapter * res = NULL;
  BOOST_FOREACH(Chapter * p_chapter, chapters_) {
    if (p_chapter->has_puzzle_file_name(i_puzzle_file_name)) {
      res = p_chapter;
      break;
    }
  }
  assert(res != NULL);
  return *res;
}
