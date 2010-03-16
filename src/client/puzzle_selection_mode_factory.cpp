#include "puzzle_selection_mode_factory.hpp"

#include "sdl_controller.hpp"
#include "puzzle_selection_mode.hpp"
#include "puzzle_selection_geometry.hpp"
#include "puzzle_selection_view.hpp"
#include "puzzle_selection_mode.hpp"

PuzzleSelectionModeFactory::~PuzzleSelectionModeFactory()
{
  delete p_view_;
  delete p_model_;
  delete p_controller_;
}

int
PuzzleSelectionModeFactory::create_mode() {
  
  int res = 0;

  // FIXME(pht) : this is duplicated in factories, or templatable
  p_controller_ = new SdlController();
  p_model_ = new PuzzleSelectionModel();
  p_view_ = new PuzzleSelectionView(dep_renderer_, *p_model_, *p_controller_);

  mode_ = boost::shared_ptr<GameModeInterface>(new PuzzleSelectionMode(*p_controller_, *p_view_, *p_model_));

  // FIXME(pht) : this is duplicated in factories
  if (p_controller_ != NULL && p_view_ != NULL) {
    p_controller_->add_observer(p_view_);
  } else {
    res = -1;
  }

  return res;

}

