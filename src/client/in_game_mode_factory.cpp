#include "in_game_mode_factory.hpp"

#include "engine/cell_factory.hpp"
#include "engine/puzzle.hpp"
#include "engine/puzzle_loader.hpp"

#include "game_mode.hpp"
#include "in_game_model.hpp"
#include "in_game_view.hpp"
#include "sdl_controller.hpp"
#include "sdl_in_game_renderer.hpp"

InGameModeFactory::~InGameModeFactory() {
  mode_.reset();
  if (p_view_ != NULL) {
    delete p_view_;
  }
  if (p_model_ != NULL) {
    delete p_model_;
  }
  if (p_puzzle_ != NULL) {
    delete p_puzzle_;
  }
  if (p_controller_ != NULL) {
    delete p_controller_;
  }
}

int
InGameModeFactory::create_mode() {
  int res = -1;

  p_renderer_ = new SdlInGameRenderer(dep_resolver_);
  res = p_renderer_->init();

  if (res == 0) {
    // TODO : initialize the model better than this ? Or what ? 
    CellFactory factory;
    PuzzleLoader loader(&factory);
    p_puzzle_ = new Puzzle();
    p_puzzle_->set_dimensions(2,2);
    loader.set_row(0, p_puzzle_, "#I");
    loader.set_row(1, p_puzzle_, "-O");

    // Bring things together
    p_model_ = new InGameModel();
    p_model_->set_puzzle(*p_puzzle_);
    p_view_ = new InGameView(*p_renderer_, *p_model_);
    p_controller_ = new SdlController();
    mode_ = boost::shared_ptr<GameMode>(new GameMode(p_controller_, p_view_));
  }

  return res;
}

boost::shared_ptr<GameMode> &
InGameModeFactory::get_mode() {
  return mode_;
}
