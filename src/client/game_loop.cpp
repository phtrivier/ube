#include "game_loop.hpp"

#include "common/logging.hpp"
#include "game_mode.hpp"
#include "clock_interface.hpp"
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

  Logging::log("prout", "prout");

  while (running_) {
    LOG_D("----------- LOOP BEGIN --------", "game_loop")

    LOG_D("Restarting clock", "game_loop")
    pClock_->restart();

    while (!pClock_->is_time_to_render()) {

      LOG_D("Not time to render", "game_loop");

      LOG_D("updating mode", "game_loop");
      get_current_game_mode()->update_game(pClock_->get_delta());

      LOG_D("Ticking...", "game_loop");
      pClock_->tick();
    }

    LOG_D("Time to render !", "game_loop")
    
    // printf("Time to render, will render..\n");
    get_current_game_mode()->render_game();

    LOG_D("Render finished", "game_loop")

    LOG_D("----------- LOOP END --------", "game_loop")

  }
}


void 
GameLoop::handle_event(int iEventCode) 
{
  if (iEventCode == GameEvent::QUIT) {
    running_ = false;
  }
}
