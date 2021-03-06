/**
 * This is Free Software. See COPYING for information.
 */
#include "sdl_puzzle_selection_renderer.hpp"

#include "common/i18n.hpp"
#include "common/logging.hpp"
#include "common/resource_resolver_interface.hpp"

#include <assert.h>
#include <config.h>

#include <boost/format.hpp>
using boost::format;

int
SdlPuzzleSelectionRenderer::init() 
{
  SdlRenderer::init();
  int res = load_image("bg_puzzle_selection.png", &p_bg_);
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

  // FIXME(pht) : i18n this
  render_text(_("Please choose a level"), 300, 40);
  render_text(_("(Oh, and please, don't shoot the coder, he's doing his best.)"), 170, 510);
  render_text(str(format("ube v%1%") % VERSION), 10, 570);
}

void
SdlPuzzleSelectionRenderer::flush() 
{
  SdlRenderer::flush();
}

void
SdlPuzzleSelectionRenderer::render_text(std::string i_text, int i_x, int i_y)
{
  LOG_D("puzzle_selection") << "Rendering text : " << i_text << std::endl;

  // FIXME(pht) : ideally, the text surface only has to be
  // computed once and can be reused, can't it ? 
  SDL_Surface * text_surface;
  SDL_Color white = {255,255,255};
  if (!(text_surface = TTF_RenderUTF8_Blended(p_font_, i_text.c_str(), white))) {
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

void
SdlPuzzleSelectionRenderer::render_puzzle_name(std::string & i_name,
					       int i_index)
{

  assert(p_font_ != NULL); 

  LOG_D("puzzle_selection") << "Rendering name " << i_name << " at index " << i_index << std::endl;

  std::string msg = str(format(_("Level %1% : %2%")) % (i_index + 1) % i_name);

  render_text(msg, get_puzzle_name_x(i_index), get_puzzle_name_y(i_index));
 
}

int
SdlPuzzleSelectionRenderer::get_mouse_position_as_puzzle_index(int i_x, int i_y)
{
  return PuzzleSelectionGeometry::get_mouse_position_as_puzzle_index(i_x,i_y);
}

void 
SdlPuzzleSelectionRenderer::highlight_puzzle_name(int i_index) 
{
  SDL_Rect dst;
  dst.x = NAMES_X0 - 5;
  dst.y = get_puzzle_name_y(i_index) - 5;
  dst.w = NAMES_W + 10;
  dst.h = NAMES_H - 5;
  SDL_FillRect(get_screen(), &dst, gray_); 
}
