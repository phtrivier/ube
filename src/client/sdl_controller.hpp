#ifndef _SDL_CONTROLLER_HPP_
#define _SDL_CONTROLLER_HPP_

#include "controller_interface.hpp"

// Forward declaration possible ? 
#include "SDL.h"

/**
 * A basic controller that uses SDL to poll the keyboard.
 */
class SdlController : public ControllerInterface { 

public:

  SdlController() : ControllerInterface() {
  }

  ~SdlController() {
  }

  bool check_events();

  void handle_event();

  int mouse_x() const {
    return mouse_x_;
  }
  
  int mouse_y() const {
    return mouse_y_;
  }

private:

  SDL_Event last_sdl_event_;

  int mouse_x_;
  int mouse_y_;
  
};

#endif // _SDL_CONTROLLER_HPP_
