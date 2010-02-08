#include "sdl_controller.hpp"

#include "common/logging.hpp"
#include "game_event.hpp"
#include "in_game_model.hpp"

#include <cstdio>

#include "boost/format.hpp"
using namespace boost;

bool
SdlController::check_events() {
  bool res = false;
  if (SDL_PollEvent(&last_sdl_event_)) {
    res = true;
  }
  return res;
}

void
SdlController::handle_event() {
  if (last_sdl_event_.type == SDL_KEYDOWN) {
    fire_event(GameEvent::QUIT);
  } else if (last_sdl_event_.type == SDL_QUIT) {
    fire_event(GameEvent::QUIT);
  } else if (last_sdl_event_.type == SDL_MOUSEMOTION) {
    mouse_x_ = last_sdl_event_.motion.x;
    mouse_y_ = last_sdl_event_.motion.y;
  } else if (last_sdl_event_.type == SDL_MOUSEBUTTONDOWN) {
    fire_event(GameEvent::MOUSE_CLICKED);
  }
}
