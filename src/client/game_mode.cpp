/**
 * This is Free Software. See COPYING for information.
 */
#include "game_mode.hpp"

#include "mvc/controller_interface.hpp"
#include "mvc/view_interface.hpp"

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

void
GameMode::add_observer(ObserverInterface *o)
{
  Observable::add_observer(o);
  pController_->add_observer(o);
}