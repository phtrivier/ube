#ifndef _SDL_CLOCK_HPP_
#define _SDL_CLOCK_HPP_

#include "abstract_clock.hpp"
#include <SDL.h>

/**
 * A clock that uses SDL_GetTicks
 */
class SdlClock : public AbstractClock{ 

  // Shamelessly inspired from http://dewitters.koonsolo.com/gameloop.html
  
  static const int TICKS_PER_SECOND = 100;
  static const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
  static const int MAX_FRAMESKIP = 10;

  int delta_;
  Uint32 lastGameTick_;
  Uint32 nextGameTick_;
  int loops_;
  
public:

  void init() {
    loops_ = 0;
    delta_ = 0 ; /// ?? 
    lastGameTick_ = SDL_GetTicks();
    nextGameTick_ = SDL_GetTicks();
  }

  void restart() {
    loops_ = 0;
  }

  bool is_time_to_render();
  
  void tick();

  int get_delta() {
    return delta_;
  }

};

#endif // _SDL_CLOCK_HPP_
