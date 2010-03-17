#ifndef _SDL_PUZZLE_SELECTION_RENDERER_HPP_
#define _SDL_PUZZLE_SELECTION_RENDERER_HPP_

#include "puzzle_selection_renderer_interface.hpp"

#include "puzzle_selection_geometry.hpp"

#include "sdl_renderer.hpp"

#include <string>

#include "SDL_ttf.h"

// Note : bad case of "a renderer is a geometry" where I would
// really like to say "a renderer has a geometry".
// *sigh*.

/**
 * puzzle selection renderer based on SDL
 */
class SdlPuzzleSelectionRenderer : 
  public PuzzleSelectionRendererInterface,
  public PuzzleSelectionGeometry,
  public SdlRenderer
{ 

public:

  SdlPuzzleSelectionRenderer(ResourceResolverInterface & dep_resolver, SDL_Surface * dep_p_screen) :
    PuzzleSelectionRendererInterface(),
    SdlRenderer(dep_resolver, dep_p_screen),
    p_bg_(NULL)
  {

  }

  ~SdlPuzzleSelectionRenderer();

  int init();

  void clear();

  void flush();

  void render_puzzle_name(std::string & i_name, int i_index);
 
  int get_mouse_position_as_puzzle_index(int i_x, int i_y);

private:

  SDL_Surface * p_bg_;
  
  TTF_Font * p_font_;
  
  int load_font(const char * i_name, int i_ptsize, TTF_Font ** o_pp_font);

  void render_text(std::string i_text, int i_x, int i_y);

};

#endif // _SDL_PUZZLE_SELECTION_RENDERER_HPP_
