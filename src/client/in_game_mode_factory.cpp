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
  delete p_controller_;
}

int
InGameModeFactory::load_puzzle(std::string & i_file_name)
{
  model_.get_puzzle().clear();
  cell_factory_.delete_created_cells();
  int res = in_game_model_loader_.load_puzzle_file(i_file_name.c_str(), model_);
  return res;
}

int
InGameModeFactory::create_mode() {
  int res = 0;

  res = load_puzzle(puzzle_file_name_);

  if (res == 0) {
    // Create controller (always the same in my cases...)
    p_controller_ = new SdlController();

    // Create the view (will typically need the controllers and
    // model, but can be anything !
    p_view_ = new InGameView(dep_renderer_, model_, *p_controller_);
    // Create the mode iteself
    mode_ = boost::shared_ptr<InGameMode>(new InGameMode(*p_controller_, *p_view_, model_));

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
