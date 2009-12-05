#include "sdl_controller.hpp"
#include "game_event.hpp"

#include <cstdio>

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
  }
}
