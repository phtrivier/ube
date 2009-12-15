#include "sdl_clock.hpp"

bool
SdlClock::is_time_to_render()
{
  /* FIXME(pht) : find a nicer debug solution. boost ? 
  printf("Checking for time_to_render\n");
  printf("SDL_GetTIcks() : %d\n", SDL_GetTicks());
  printf("nextGameTick_ : %d\n", nextGameTick_);
  printf("loops_ : %d\n", loops_);
  printf("MAX_FRAMESKIP : %d", MAX_FRAMESKIP);
  printf("SDL_GetTicks < nextGameTick_ ? %d\n", SDL_GetTicks() < nextGameTick_);
  */
  return (SDL_GetTicks() < nextGameTick_ || loops_ > MAX_FRAMESKIP);
}

void 
SdlClock::tick() 
{
  Uint32 now = SDL_GetTicks();
  delta_ = now - lastGameTick_;
  lastGameTick_ = now;
  
  nextGameTick_ += SKIP_TICKS;
  loops_++;
  // Give the other processes a bit of time
  SDL_Delay(10);
}
