#include "sdl_puzzle_selection_renderer.hpp"

#include "common/logging.hpp"
#include "common/resource_resolver_interface.hpp"

#include <assert.h>

int
SdlPuzzleSelectionRenderer::init() 
{
  int res = load_image("bg.png", &p_bg_);
  if (res == 0) {
    res = load_font("FreeSans.ttf", 18, &p_font_);
  }

  return res;
}

int
SdlPuzzleSelectionRenderer::load_font(const char * i_name, int i_ptsize, TTF_Font ** o_pp_font) {
  int res = -1;
  std::string file_name = get_resolver().get_font_file_name(i_name);
  *o_pp_font = TTF_OpenFont(file_name.c_str(), i_ptsize);
  if (o_pp_font != NULL) {
    res = 0;
  }
  return res;
}

SdlPuzzleSelectionRenderer::~SdlPuzzleSelectionRenderer()
{
  // Release font
  if (p_font_ != NULL) {
    TTF_CloseFont(p_font_);
  }
  // Release bg
  clear_image(p_bg_);
}

void
SdlPuzzleSelectionRenderer::clear() 
{
  assert(get_screen() != NULL);
  SDL_BlitSurface(p_bg_, NULL, get_screen(), NULL);
}

void
SdlPuzzleSelectionRenderer::flush() 
{
  SdlRenderer::flush();
}

void
SdlPuzzleSelectionRenderer::render_puzzle_name(std::string & i_name,
					       int i_index)
{

  assert(p_font_ != NULL); 

  LOG_D("puzzle_selection") << "Rendering name " << i_name << " at index " << i_index << std::endl;

  // FIXME(pht) : ideally, the text surface only has to be
  // computed once and can be reused, can't it ? 
  SDL_Surface * text_surface;
  SDL_Color white = {255,255,255};
  if (!(text_surface = TTF_RenderText_Blended(p_font_, i_name.c_str(), white))) {
    printf("Error while printing text %s\n", TTF_GetError());

    LOG_D("puzzle_selection") << "Could not create renderering surface ; " << TTF_GetError() << std::endl;

  } else {
    SDL_Rect dst;
    dst.x = get_puzzle_name_x(i_index); // 50;
    dst.y = get_puzzle_name_y(i_index); // 50 + (40*i_index + 10);
    LOG_D("puzzle_selection") << "Blitting text surface on screen" << dst.x << "," << dst.y << "," << dst.w << "," << dst.h << std::endl;

    SDL_BlitSurface(text_surface, NULL, get_screen(), &dst);
    SDL_FreeSurface(text_surface);
  }
}

int
SdlPuzzleSelectionRenderer::get_mouse_position_as_puzzle_index(int i_x, int i_y)
{
  return PuzzleSelectionGeometry::get_mouse_position_as_puzzle_index(i_x,i_y);
}