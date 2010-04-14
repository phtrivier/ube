#include "sdl_renderer.hpp"

#include "common/resource_resolver_interface.hpp"

#include <assert.h>

#include "SDL_image.h"

int 
SdlRenderer::init()
{
  black_ = rgb(0x00, 0x00, 0x00);
  white_ = rgb(0xFF, 0xFF, 0xFF);
  return 0;
}

Uint32
SdlRenderer::rgb(Uint8 r, Uint8 g, Uint8 b)
{
  return SDL_MapRGB(dep_p_screen_->format, r, g, b);
}

int
SdlRenderer::load_image(std::string i_image_name, SDL_Surface ** o_pp_surface) {
  int res = -1;
  SDL_Surface * p_tmp = IMG_Load(dep_resolver_.get_image_file_name(i_image_name.c_str()).c_str());
  if (p_tmp != NULL) {
    *o_pp_surface = SDL_DisplayFormatAlpha(p_tmp);
    SDL_FreeSurface(p_tmp);
    res = 0;
  }
  return res;
}

void 
SdlRenderer::flush() {
  assert(dep_p_screen_ != NULL);
  SDL_Flip(dep_p_screen_);
}
