/**
 * This is Free Software. See COPYING for information.
 */
#include "puzzle_selection_mode_factory.hpp"

#include "sdl_controller.hpp"
#include "puzzle_selection_mode.hpp"
#include "puzzle_selection_geometry.hpp"
#include "puzzle_selection_view.hpp"
#include "puzzle_selection_mode.hpp"

PuzzleSelectionModeFactory::~PuzzleSelectionModeFactory()
{
}

int
PuzzleSelectionModeFactory::create_mode() {
  
  int res = 0;

  mode_ = boost::shared_ptr<GameModeInterface>(new PuzzleSelectionMode(controller_, view_, model_));

  controller_.add_observer(&view_);

  return res;

}
