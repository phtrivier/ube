#ifndef _SDL_VIEW_HPP_
#define _SDL_VIEW_HPP_

#include "abstract_view.hpp"
#include <SDL.h>

class ResourceResolver;

/**
 * A game view that uses SDL.
 */
class SdlView : public AbstractView { 

  SDL_Surface * pScreen_;

  ResourceResolver * pResolver_;

  SDL_Surface * pGnuImage_;

  SDL_Rect src_;
  SDL_Rect dest_;

public:

  SdlView(ResourceResolver * ipResolver_);

  ~SdlView();

  void render_game();
  
};

#endif // _SDL_VIEW_HPP_
