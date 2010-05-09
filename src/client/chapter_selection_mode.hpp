/**
 * This is Free Software. See COPYING for information.
 */
#ifndef _CHAPTER_SELECTION_MODE_HPP_
#define _CHAPTER_SELECTION_MODE_HPP_

#include "game_mode.hpp"
#include "chapter_selection_model.hpp"

#include "mvc/controller_interface.hpp"
#include "mvc/view_interface.hpp"


/**
 * GameMode for chapter selection
 */
class ChapterSelectionMode :
  public GameMode
{
public:
  ChapterSelectionMode(ControllerInterface & dep_controller, 
		      ViewInterface & dep_view, 
		      ChapterSelectionModel & dep_model):
    GameMode(&dep_controller, &dep_view),
    dep_model_(dep_model)
  {
  }
  
  void update_game(int iDelta);

  ChapterSelectionModel & get_model() {
    return dep_model_;
  }

private:

  ChapterSelectionModel & dep_model_;

};

#endif // _CHAPTER_SELECTION_MODE_HPP_
