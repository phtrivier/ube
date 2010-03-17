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
}

int
InGameModeFactory::load_puzzle(std::string & i_file_name)
{
  if (p_puzzle_ == NULL) {
    p_puzzle_ = new Puzzle();
  } else {
    p_puzzle_->clear();
  }

  // FIXME(pht) : reuse a loader instead of recreating one ?
  CellFactory factory;

  LuaPuzzleLoader loader(&factory, dep_resolver_);

  int res = loader.load_puzzle_file(i_file_name.c_str(), p_puzzle_);
  if (res == 0) {
    p_puzzle_->enters_player();
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
    p_path_finder_ = new LuaPathFinder(dep_resolver_);
    p_model_ = new InGameModel(*p_path_finder_);
    p_model_->set_puzzle(*p_puzzle_);
    p_controller_ = new SdlController();
    p_view_ = new InGameView(dep_renderer_, *p_model_, *p_controller_);
    mode_ = boost::shared_ptr<InGameMode>(new InGameMode(*p_controller_, *p_view_, *p_model_));
    if (p_controller_ != NULL && p_view_ != NULL) {
      p_controller_->add_observer(p_view_);
    }
  }

  return res;
}

boost::shared_ptr<GameMode> &
InGameModeFactory::get_mode() {
  return mode_;
}
