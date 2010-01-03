#include "sdl_clock.hpp"

#include "common/logging.hpp"

#include <boost/format.hpp>
using namespace boost;


bool
SdlClock::is_time_to_render()
{

  LOG_D("clock") << "Ticks : " << SDL_GetTicks();
  LOG_D("clock") << "NextGameTick : " << nextGameTick_;
  LOG_D("clock") << "loop_s :" << loops_;

  return (SDL_GetTicks() < nextGameTick_ || 
	  loops_ > MAX_FRAMESKIP);
}

void 
SdlClock::tick() 
{
  Uint32 now = SDL_GetTicks();
  delta_ = now - lastGameTick_;
  lastGameTick_ = now;
  
  nextGameTick_ += SKIP_TICKS;
  loops_++;

  //test(not to trash the CPU ....)
  SDL_Delay(5);

}
