/**
 * This is Free Software. See COPYING for information.
 */
#ifndef _PUZZLE_SELECTION_MODE_FACTORY_HPP_
#define _PUZZLE_SELECTION_MODE_FACTORY_HPP_

#include "sdl_controller.hpp"
#include "puzzle_selection_view.hpp"
#include "puzzle_selection_model.hpp"
#include "puzzle_selection_renderer_interface.hpp"

#include <boost/shared_ptr.hpp>

class GameMode;
class GameModeInterface;

/**
 * Factory to create and initialize a puzzle selection mode
 */
class PuzzleSelectionModeFactory { 

public:

  PuzzleSelectionModeFactory(PuzzleSelectionRendererInterface & dep_renderer) :
    dep_renderer_(dep_renderer),
    controller_(),
    model_(),
    view_(dep_renderer_, model_, controller_)
  {
  }

  ~PuzzleSelectionModeFactory();

  int create_mode();

  boost::shared_ptr<GameModeInterface> & get_mode() {
    return mode_;
  }

private:

  PuzzleSelectionRendererInterface & dep_renderer_;
  
  SdlController controller_;
  PuzzleSelectionModel model_;
  PuzzleSelectionView view_;

  boost::shared_ptr<GameModeInterface> mode_;

};

#endif // _PUZZLE_SELECTION_MODE_FACTORY_HPP_
