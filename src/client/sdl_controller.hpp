#ifndef _SDL_CONTROLLER_HPP_
#define _SDL_CONTROLLER_HPP_

#include "abstract_controller.hpp"

// Forward declaration possible ? 
#include "SDL.h"

/**
 * A basic controller that uses SDL to poll the keyboard.
 */
class SdlController : public AbstractController { 

public:

  SdlController() : AbstractController() {
    was_in_gnu_ = false;
  }

  virtual ~SdlController() {
    // Do I need to call something here, again ? 
  }

  bool check_events();

  void handle_event();

  int get_mouse_x() const {
    return mouse_x_;
  }
  
  int get_mouse_y() const {
    return mouse_y_;
  }

private:

  SDL_Event lastSdlEvent_;
  bool was_in_gnu_;
  
  bool is_in_gnu(const SDL_Event & i_event);

  int mouse_x_;
  int mouse_y_;
  
};

#endif // _SDL_CONTROLLER_HPP_
