/**
 * This is Free Software. See COPYING for information.
 */
#ifndef _CHAPTER_SELECTION_MODE_FACTORY_HPP_
#define _CHAPTER_SELECTION_MODE_FACTORY_HPP_

#include "sdl_controller.hpp"
#include "chapter_selection_view.hpp"
#include "chapter_selection_model.hpp"
#include "selection_renderer_interface.hpp"

#include <boost/shared_ptr.hpp>

class GameMode;
class GameModeInterface;

/**
 * Factory to create and initialize a puzzle selection mode
 */
class ChapterSelectionModeFactory { 

public:

  ChapterSelectionModeFactory(SelectionRendererInterface & dep_renderer) :
    dep_renderer_(dep_renderer),
    controller_(),
    model_(),
    view_(dep_renderer_, model_, controller_)
  {
  }

  ~ChapterSelectionModeFactory();

  int create_mode();

  boost::shared_ptr<GameModeInterface> & get_mode() {
    return mode_;
  }

private:

  SelectionRendererInterface & dep_renderer_;
  
  SdlController controller_;
  ChapterSelectionModel model_;
  ChapterSelectionView view_;

  boost::shared_ptr<GameModeInterface> mode_;

};

#endif // _CHAPTER_SELECTION_MODE_FACTORY_HPP_
