#ifndef _SDL_VIEW_HPP_
#define _SDL_VIEW_HPP_

#include "abstract_view.hpp"
#include "SDL.h"

// Music test
#include "SDL_mixer.h"

class AbstractResourceResolver;

/**
 * A game view that uses SDL.
 */
class SdlView : public AbstractView { 

  SDL_Surface * pScreen_;

  AbstractResourceResolver * pResolver_;

  SDL_Surface * pGnuImage_;

  SDL_Rect src_;
  SDL_Rect dest_;

public:

  // For sound test
  static bool music_started_;
  static Mix_Music * pMusic_;
  static void musicDone();

  SdlView(AbstractResourceResolver * ipResolver_);

  ~SdlView();

  void render_game();
  
};

#endif // _SDL_VIEW_HPP_
