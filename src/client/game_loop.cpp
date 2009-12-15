#include "game_loop.hpp"
#include "game_mode.hpp"
#include "abstract_clock.hpp"
#include "game_event.hpp"

#include <cstdio>

#include <boost/format.hpp>
using boost::format;

#include <cassert>

void 
GameLoop::register_game_mode(std::string iModeName, AbstractGameMode * ipGameMode)
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

    pClock_->restart();

    while (!pClock_->is_time_to_render()) {
      // printf("Not time to render, updating the game state..\n");
      get_current_game_mode()->update_game(pClock_->get_delta());
      pClock_->tick();
    }

    // printf("Time to render, will render..\n");
    get_current_game_mode()->render_game();

  }
}


void 
GameLoop::handle_event(int iEventCode) 
{
  printf("handling event to quit %d\n", iEventCode);
  if (iEventCode == GameEvent::QUIT) {
    running_ = false;
  }
}
