/**
 * This is Free Software. See COPYING for information.
 */
#ifndef _SDL_APP_HPP_
#define _SDL_APP_HPP_

#include <SDL.h>

class SdlApp {
  
private:
  bool            running_;
  SDL_Surface*    screen_;
public:
  SdlApp();
  bool init();
  int execute();
  void handleEvent(const SDL_Event* iEvent);
  void loop();
  void render();
  void cleanup();
};

#endif // _SDL_APP_HPP_