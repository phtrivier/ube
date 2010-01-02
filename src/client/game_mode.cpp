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
  
  /*
  int i = 0;
  while (i < 10 && pController_->check_events()) {
    pController_->handle_event();
    i++;
  }
  */
}

void
GameMode::render_game() 
{
  assert(pView_ != NULL);
  pView_->render_game();
}

void
GameMode::add_observer(AbstractObserver *o)
{
  Observable::add_observer(o);
  pController_->add_observer(o);
}
