/**
 * This is Free Software. See COPYING for information.
 */
#include "game_loop.hpp"

#include "common/logging.hpp"

#include "mvc/clock_interface.hpp"

#include "game_mode.hpp"
#include "game_event.hpp"

#include <cstdio>

#include <boost/format.hpp>
using boost::format;

#include <cassert>

void 
GameLoop::register_game_mode(std::string iModeName, GameModeInterface * ipGameMode)
{
  assert(ipGameMode != NULL);
  assert(!iModeName.empty());
  ipGameMode->add_observer(this);
  gameModes_[iModeName] = ipGameMode;
}
  
void 
GameLoop::set_current_game_mode(std::string iModeName)
{
  if (gameModes_.find(iModeName) == gameModes_.end()) {
    throw std::logic_error(str(format("Invalid game mode name <%1%>") % iModeName));
  }
  pCurrentGameMode_ =  gameModes_[iModeName];
}
  
 
void 
GameLoop::loop() 
{
  assert(pClock_!=NULL);
  assert(get_current_game_mode() != NULL);
  assert(running_ == false);

  pClock_->init();

  running_ = true;

  while (running_) {
    LOG_D("loop") << "----------- LOOP BEGIN --------";

    LOG_D("loop") << "Restarting clock";
    pClock_->restart();

    while (!pClock_->is_time_to_render()) {

      LOG_D("game-loop") << "Not time to render";

      LOG_D("game-loop") << "Updating game";
      get_current_game_mode()->update_game(pClock_->get_delta());

      LOG_D("game-loop") << "Ticking";
      pClock_->tick();
    }

    LOG_D("game-loop") << "Time to render !";
    
    // printf("Time to render, will render..\n");
    get_current_game_mode()->render_game();

    LOG_D("game-loop") << "----------- LOOP END --------";

  }
}


void 
GameLoop::handle_event(int iEventCode) 
{
  if (iEventCode == GameEvent::QUIT) {
    running_ = false;
  }
}