#include "sdl_clock.hpp"

#include "common/logging.hpp"

#include <boost/format.hpp>
using namespace boost;


bool
SdlClock::is_time_to_render()
{

  LOG_D(str(format("Ticks : %1%") % SDL_GetTicks() ), "clock");
  LOG_D(str(format("nextGameTick_ : %1%") % nextGameTick_) , "clock");
  LOG_D(str(format("loops_ : %1%") % loops_) , "clock");

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
