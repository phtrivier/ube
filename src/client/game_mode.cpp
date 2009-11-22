#include "game_mode.hpp"
#include "abstract_controller.hpp"

void
GameMode::update_game(int iDelta) 
{
  if (pController_->check_events()) {
    pController_->handle_event();
  }
}
