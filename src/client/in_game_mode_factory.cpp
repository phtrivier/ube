/**
 * This is Free Software. See COPYING for information.
 */
#include "in_game_mode_factory.hpp"

#include "engine/cell_factory.hpp"
#include "engine/puzzle.hpp"
#include "engine/puzzle_loader.hpp"
#include "engine/lua_puzzle_loader.hpp"
#include "engine/lua_path_finder.hpp"

#include "game_mode.hpp"
#include "in_game_model.hpp"
#include "in_game_view.hpp"
#include "in_game_mode.hpp"
#include "sdl_controller.hpp"
#include "in_game_renderer_interface.hpp"

InGameModeFactory::~InGameModeFactory() {
  mode_.reset();
  delete p_view_;
  delete p_model_;
  delete p_puzzle_;
  delete p_controller_;
  delete p_puzzle_loader_;
}

int
InGameModeFactory::load_puzzle(std::string & i_file_name)
{
  if (p_puzzle_ == NULL) {
    p_puzzle_ = new Puzzle();
  } else {
    // At least one puzzle was already 
    // created. To avoid memory leak, 
    // we ask the factory to get rid 
    // of all created cells.
    p_puzzle_->clear();
    cell_factory_.delete_created_cells();
  }

  if (p_puzzle_loader_ == NULL) {
    p_puzzle_loader_ = new LuaPuzzleLoader(&cell_factory_, dep_resolver_);
  }

  int res = p_puzzle_loader_->load_puzzle_file(i_file_name.c_str(), p_puzzle_);
  if (res == 0) {
    // TODO(pht) : this looks kinda strange ... maybe the model should be the sole responsible for clearing everything ? 
    // Also, what if the model was responsible for creating the puzzle (I very rarely create a model without 
    // a puzzle ... and it would simplify a few things ... 
    p_puzzle_->enters_player();
    if (p_model_ != NULL) {
      p_model_->set_first_available_move_as_current();
    }
  }
  // TODO : Otherwise, display any lua error message from
  // preparation ? (ideally, loader should have the error...)

  return res;

}

int
InGameModeFactory::create_mode() {
  int res = 0;

  res = load_puzzle(puzzle_file_name_);

  if (res == 0) {
    // Bring things together

    // Create controller (always the same in my cases...)
    p_controller_ = new SdlController();

    // Create the model (will be different from time to time)
    //K p_path_finder_ = new LuaPathFinder(dep_resolver_);
    // TODO(pht) : no dynamic alloc really needed, actually... 
    p_model_ = new InGameModel(path_finder_);
    p_model_->set_puzzle(*p_puzzle_);

    // Create the view (will typically need the controllers and
    // model, but can be anything !
    p_view_ = new InGameView(dep_renderer_, *p_model_, *p_controller_);

    // Create the mode iteself
    mode_ = boost::shared_ptr<InGameMode>(new InGameMode(*p_controller_, *p_view_, *p_model_));

    // Link the controller and the view (could be done the same for all, no ?)
    if (p_controller_ != NULL && p_view_ != NULL) {
      p_controller_->add_observer(p_view_);
    } else {
      res = -1;
    }
  }

  return res;
}

boost::shared_ptr<GameMode> &
InGameModeFactory::get_mode() {
  return mode_;
}
