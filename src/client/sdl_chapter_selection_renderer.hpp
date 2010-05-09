/**
 * This is Free Software. See COPYING for information.
 */
#ifndef _SDL_CHAPTER_SELECTION_RENDERER_HPP_
#define _SDL_CHAPTER_SELECTION_RENDERER_HPP_

#include "selection_renderer_interface.hpp"

#include "chapter_selection_geometry.hpp"

#include "sdl_renderer.hpp"

#include <string>

// Note : bad case of "a renderer is a geometry" where I would
// really like to say "a renderer has a geometry".
// *sigh*.

/**
 * chapter selection renderer based on SDL
 */
class SdlChapterSelectionRenderer : 
  public SelectionRendererInterface,
  public ChapterSelectionGeometry,
  public SdlRenderer
{ 

public:

  SdlChapterSelectionRenderer(ResourceResolverInterface & dep_resolver, SDL_Surface * dep_p_screen) :
    SelectionRendererInterface(),
    SdlRenderer(dep_resolver, dep_p_screen),
    p_bg_(NULL)
  {

  }

  ~SdlChapterSelectionRenderer();

  int init();

  void clear();

  void flush();

  void render_item_name(std::string & i_name, int i_index);
 
  int get_mouse_position_as_item_index(int i_x, int i_y);

  void highlight_item_name(int i_index);

private:

  SDL_Surface * p_bg_;
  
  TTF_Font * p_font_;

};

#endif // _SDL_CHAPTER_SELECTION_RENDERER_HPP_
