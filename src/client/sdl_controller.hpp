#ifndef _SDL_CONTROLLER_HPP_
#define _SDL_CONTROLLER_HPP_

#include "abstract_controller.hpp"

// Forward declaration possible ? 
#include "SDL.h"

/**
 * A basic controller that uses SDL to poll the keyboard.
 */
class SdlController : public AbstractController { 

  SDL_Event lastSdlEvent_;
  
public:

  SdlController() : AbstractController() {
  }

  virtual ~SdlController() {
    // Do I need to call something here, again ? 
  }

  bool check_events();

  void handle_event();
};

#endif // _SDL_CONTROLLER_HPP_
