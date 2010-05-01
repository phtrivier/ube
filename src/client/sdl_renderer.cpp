/**
 * This is Free Software. See COPYING for information.
 */
#include "sdl_renderer.hpp"

#include "common/resource_resolver_interface.hpp"

#include <assert.h>
#include <vector>
#include <string>

#include "SDL_image.h"
#include <boost/foreach.hpp>
#include <boost/algorithm/string.hpp>

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

std::vector<std::string>
SdlRenderer::split_text_to_render(std::string i_text, TTF_Font * i_p_font, int i_max_w)
{
  std::vector<std::string> res;
  if (i_max_w == -1) {
    res.push_back(i_text);
  } else {
    // Split the string by spaces
    std::vector<std::string> tokens;
    boost::split(tokens, i_text, boost::is_any_of(" "));

    std::string line("");
    int token_index = 0;
    int token_count = tokens.size();
    int w = 0;
    int h = 0;
    BOOST_FOREACH(std::string token, tokens) {
      line.append(token);
      line.append(" ");
      token_index++;
      TTF_SizeUTF8(i_p_font, line.c_str(), &w, &h);
      if (w > i_max_w || token_index == token_count) {
	res.push_back(line);
	line = "";
      } 
    }
  }
  return res;
}

void
SdlRenderer::render_text(std::string i_text, int i_x, int i_y, TTF_Font * i_p_font, int i_max_w)
{
  LOG_D("puzzle_selection") << "Rendering text : " << i_text << std::endl;

  SDL_Color white = {255,255,255};

  std::vector<std::string> lines = split_text_to_render(i_text, i_p_font, i_max_w);

  int font_pixel_height = TTF_FontLineSkip(i_p_font);

  SDL_Rect dst;

  dst.x = i_x;

  int line_index = 0;

  BOOST_FOREACH(std::string line, lines) {
    SDL_Surface * text_surface = TTF_RenderUTF8_Blended(i_p_font, line.c_str(), white);
    dst.y = i_y + line_index * font_pixel_height;
    SDL_BlitSurface(text_surface, NULL, get_screen(), &dst);
    SDL_FreeSurface(text_surface);
    line_index++;
  }
  
}

