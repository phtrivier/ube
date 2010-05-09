/**
 * This is Free Software. See COPYING for information.
 */
#include "chapter_selection_mode_factory.hpp"

#include "sdl_controller.hpp"
#include "chapter_selection_mode.hpp"
#include "chapter_selection_geometry.hpp"
#include "chapter_selection_view.hpp"
#include "chapter_selection_mode.hpp"

ChapterSelectionModeFactory::~ChapterSelectionModeFactory()
{
}

int
ChapterSelectionModeFactory::create_mode() {
  
  int res = 0;

  mode_ = boost::shared_ptr<GameModeInterface>(new ChapterSelectionMode(controller_, view_, model_));

  controller_.add_observer(&view_);

  return res;
}
