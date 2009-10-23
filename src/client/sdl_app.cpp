#include "sdl_app.hpp"

SdlApp::SdlApp() {
  screen_ = NULL;
  running_ = true;
}

int SdlApp::execute() {
  if (init() == false) {
    return -1;
  }
  SDL_Event event;
  while (running_) {
    while (SDL_PollEvent(&event)) {
      handleEvent(&event);
    }
    loop();
    render();
  }
  cleanup();
  return 0;
}

bool SdlApp::init() {
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return false;
    }

    if((screen_ = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {
        return false;
    }

    return true;
}

void SdlApp::loop() {
}

void SdlApp::render() {

}

void SdlApp::handleEvent(const SDL_Event* iEvent) {
    if(iEvent->type == SDL_QUIT) {
        running_ = false;
    }
}

void SdlApp::cleanup() {
  SDL_FreeSurface(screen_);
  SDL_Quit();
}
