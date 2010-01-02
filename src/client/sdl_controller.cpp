#include "sdl_controller.hpp"

#include "common/logging.hpp"
#include "game_event.hpp"

#include <cstdio>

#include "boost/format.hpp"
using namespace boost;

bool
SdlController::check_events() {
  // printf("Checking events...\n");
  bool res = false;
  if (SDL_PollEvent(&lastSdlEvent_)) {
    // printf("Event noticed %d\n", lastSdlEvent_.type);
    res = true;
  }
  return res;
}

void
SdlController::handle_event() {
  if (lastSdlEvent_.type == SDL_KEYDOWN) {
    //    printf("Key down handled, fire event to quit \n");
    fire_event(GameEvent::QUIT);
  } else if (lastSdlEvent_.type == SDL_QUIT) {
    fire_event(GameEvent::QUIT);
  } else if (lastSdlEvent_.type == SDL_MOUSEMOTION) {

    mouse_x_ = lastSdlEvent_.motion.x;
    mouse_y_ = lastSdlEvent_.motion.y;

    printf("Mouse position : %d,%d\n", lastSdlEvent_.motion.x, lastSdlEvent_.motion.y);

    // K
    // if (!was_in_gnu_ && is_in_gnu(lastSdlEvent_)) {
    //   //      printf("%d : Controller noticed we got IN the GNU\n", c);
    //   LOG_D("Controller saying to get in gnu", "ctrler");
    //   fire_event(GameEvent::MOUSE_IN_GNU);
    //   was_in_gnu_ = true;
    // } else if (was_in_gnu_ && !is_in_gnu(lastSdlEvent_)) {
    //   // printf("%d : Controller noticed we got OUT of the GNU\n", c);
    //   c++;
    //   LOG_D("Controller saying to get out of  gnu", "ctrler");
    //   fire_event(GameEvent::MOUSE_OUT_GNU);
    //   was_in_gnu_ = false;
    // }
  }
}

bool
SdlController::is_in_gnu(const SDL_Event & i_event) {
  bool res= (i_event.motion.x >= 100 && i_event.motion.x <= 250 
	     && i_event.motion.y >= 100 && i_event.motion.y <= 250);
  LOG_D("Testing is event is in gnu", "ctrler");
  LOG_D(str(format("X,Y : %1%,%2%") %  i_event.motion.x % i_event.motion.y) , "ctrler");
  LOG_D(str(format("X >= 100 : %1%") %  (i_event.motion.x >= 100)) , "ctrler");
  LOG_D(str(format("X <= 250 : %1%") %  (i_event.motion.x <= 250)) , "ctrler");
  LOG_D(str(format("Y >= 100 : %1%") %  (i_event.motion.y >= 100)) , "ctrler");
  LOG_D(str(format("Y <= 250 : %1%") %  (i_event.motion.y <= 250)) , "ctrler");
  LOG_D(str(format("Result : %1%") % res), "ctrler");
  return res;
}
