#include "game_loop.hpp"
#include "game_mode.hpp"

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
}


void 
GameLoop::handle_event(int iEventCode) 
{
  
}
