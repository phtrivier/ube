#include "game_mode.hpp"
#include "abstract_controller.hpp"
#include "abstract_view.hpp"

#include <cassert>

void
GameMode::update_game(int iDelta) 
{
  if (pController_->check_events()) {
    pController_->handle_event();
  }
}

void
GameMode::render_game() 
{
  assert(pView_ != NULL);
  pView_->render_game();
}
