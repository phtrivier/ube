/**
 * This is Free Software. See COPYING for information.
 */
#include "sdl_controller.hpp"

#include "common/logging.hpp"
#include "engine/game_event.hpp"
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

    SDLKey key_sim = last_sdl_event_.key.keysym.sym;

    if (key_sim == SDLK_z) {
      fire_event(GameEvent::UNDO);
    } else if (key_sim == SDLK_y) {
      fire_event(GameEvent::REDO);
    } else if (key_sim == SDLK_r) {
      fire_event(GameEvent::RELOAD_PUZZLE);
    } else if (key_sim == SDLK_ESCAPE) {
      fire_event(GameEvent::QUIT);
    } else if (key_sim == SDLK_TAB) {
      fire_event(GameEvent::NEXT_MOVE);
    }
    
  } else if (last_sdl_event_.type == SDL_QUIT) {
    fire_event(GameEvent::QUIT);
  } else if (last_sdl_event_.type == SDL_MOUSEMOTION) {
    mouse_x_ = last_sdl_event_.motion.x;
    mouse_y_ = last_sdl_event_.motion.y;
  } else if (last_sdl_event_.type == SDL_MOUSEBUTTONDOWN) {
    fire_event(GameEvent::MOUSE_CLICKED);
  }
}
