#include "sdl_view.hpp"
#include "SDL.h"
#include "SDL_image.h"
#include <stdlib.h> /* for exit() */
#include <cassert>

#include "resource_resolver.hpp"

// TODO : put the SDL ttf code back to also display some text !!

SdlView::SdlView(ResourceResolver * ipResolver)
{
  assert(ipResolver != NULL);
  pResolver_ = ipResolver;
  
  // Note : shouln't the screen be shared between all 
  // SDL_Views ?
  pScreen_ = SDL_SetVideoMode(640, 480, 8, SDL_SWSURFACE);
  if (pScreen_ == NULL) {
    // Or should I throw an exception ? 
    // Does this message need to be translated ? 
    fprintf(stderr, "Couldn't set 640x480x8 video mode: %s\n", SDL_GetError());
    // There is nothing I can do, so dying is an option...
    // But an exception would be nicer
    exit(1);
  }

  // Load the GNU image
  SDL_Surface *temp;
  temp = IMG_Load(pResolver_->get_image_file_name("gnu.png").c_str());
  if (temp == NULL) {
    printf("Unable to load bitmap: %s\n", SDL_GetError());
    exit(1);
  }
  pGnuImage_ = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);

  src_.x = 0;
  src_.y = 0;
  src_.w = pGnuImage_->w;
  src_.h = pGnuImage_->h;

  dest_.x = 100;
  dest_.y = 100;
  dest_.w = pGnuImage_->w;
  dest_.h = pGnuImage_->h;
}

SdlView::~SdlView() 
{
  SDL_FreeSurface(pGnuImage_);
  SDL_FreeSurface(pScreen_); // ?
}

void
SdlView::render_game() 
{
  SDL_FillRect(pScreen_, NULL, SDL_MapRGB(pScreen_->format, 0x00, 0x00, 0xff));
  SDL_BlitSurface(pGnuImage_, &src_, pScreen_, &dest_);
  SDL_Flip(pScreen_);
}
