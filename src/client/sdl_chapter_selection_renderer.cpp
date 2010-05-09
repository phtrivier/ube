/**
 * This is Free Software. See COPYING for information.
 */
#include "sdl_chapter_selection_renderer.hpp"

#include "common/i18n.hpp"
#include "common/logging.hpp"
#include "common/resource_resolver_interface.hpp"

#include <assert.h>

#include <boost/format.hpp>
using boost::format;

int
SdlChapterSelectionRenderer::init() 
{
  SdlRenderer::init();
  int res = load_image("bg_puzzle_selection.png", &p_bg_);
  if (res == 0) {
    res = load_font("FreeSans.ttf", 18, &p_font_);
  }

  return res;
}

SdlChapterSelectionRenderer::~SdlChapterSelectionRenderer()
{
  // Release font
  if (p_font_ != NULL) {
    TTF_CloseFont(p_font_);
  }
  // Release bg
  clear_image(p_bg_);
}

void
SdlChapterSelectionRenderer::clear() 
{
  assert(get_screen() != NULL);
  SDL_BlitSurface(p_bg_, NULL, get_screen(), NULL);

  // FIXME(pht) : i18n this
  render_text(_("Please choose a chapter"), 300, 40, p_font_);
  render_text(str(format("ube v%1%") % VERSION), 10, 570, p_font_);
}

void
SdlChapterSelectionRenderer::flush() 
{
  SdlRenderer::flush();
}

void
SdlChapterSelectionRenderer::render_item_name(std::string & i_name,
					       int i_index)
{
  assert(p_font_ != NULL); 

  LOG_D("chapter_selection") << "Rendering name " << i_name << " at index " << i_index << std::endl;

  std::string msg = str(format(_("Chapter %1% : %2%")) % (i_index + 1) % i_name);

  render_text(msg, get_chapter_name_x(i_index), get_chapter_name_y(i_index), p_font_);
 
}

int
SdlChapterSelectionRenderer::get_mouse_position_as_item_index(int i_x, int i_y)
{
  return ChapterSelectionGeometry::get_mouse_position_as_chapter_index(i_x,i_y);
}

void 
SdlChapterSelectionRenderer::highlight_item_name(int i_index) 
{
  SDL_Rect dst;
  dst.x = CHAPTERS_X0 - 5;
  dst.y = get_chapter_name_y(i_index) - 5;
  dst.w = CHAPTERS_W + 10;
  dst.h = CHAPTERS_H - 5;
  SDL_FillRect(get_screen(), &dst, gray_); 
}
