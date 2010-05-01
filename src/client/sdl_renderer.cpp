/**
 * This is Free Software. See COPYING for information.
 */
#include "sdl_renderer.hpp"

#include "common/resource_resolver_interface.hpp"

#include <assert.h>

#include "SDL_image.h"

int 
SdlRenderer::init()
{
  black_ = rgb(0x00, 0x00, 0x00);
  white_ = rgb(0xFF, 0xFF, 0xFF);
  gray_  = rgb(0x32, 0x8C, 0x8C);
  blue_  = rgb(0,0,0xFF);
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

int
SdlRenderer::load_font(const char * i_name, int i_ptsize, TTF_Font ** o_pp_font) {
  int res = -1;
  std::string file_name = get_resolver().get_font_file_name(i_name);
  *o_pp_font = TTF_OpenFont(file_name.c_str(), i_ptsize);
  if (o_pp_font != NULL) {
    res = 0;
  }
  return res;
}

void
SdlRenderer::render_text(std::string i_text, int i_x, int i_y, TTF_Font * i_p_font)
{
  LOG_D("puzzle_selection") << "Rendering text : " << i_text << std::endl;

  // FIXME(pht) : ideally, the text surface only has to be
  // computed once and can be reused, can't it ? 
  SDL_Surface * text_surface;
  SDL_Color white = {255,255,255};
  if (!(text_surface = TTF_RenderUTF8_Blended(i_p_font, i_text.c_str(), white))) {
    printf("Error while printing text %s\n", TTF_GetError());
    LOG_D("puzzle_selection") << "Could not create renderering surface ; " << TTF_GetError() << std::endl;
  } else {
    SDL_Rect dst;
    dst.x = i_x;
    dst.y = i_y;
    LOG_D("puzzle_selection") << "Blitting text surface on screen" << dst.x << "," << dst.y << "," << dst.w << "," << dst.h << std::endl;
    
    SDL_BlitSurface(text_surface, NULL, get_screen(), &dst);
    SDL_FreeSurface(text_surface);
  }
}
