#ifndef _SDL_IN_GAME_RENDERER_HPP_
#define _SDL_IN_GAME_RENDERER_HPP_

#include "in_game_renderer_interface.hpp"

#include <map>

#include "SDL.h"

class ResourceResolverInterface;

/**
 * InGameRenderer that uses SDL to do the renderering.
 * Note(pht) : this could actually become simply an SdlRenderer, and
 * implements several interfaces, since I don't want to scater the code to init videos an stuff
 * everywhere in the code .... 
 */
class SdlInGameRenderer : 
  public InGameRendererInterface
{ 

public:
  SdlInGameRenderer(ResourceResolverInterface & dep_resolver) : 
    InGameRendererInterface(),
    dep_resolver_(dep_resolver)
  {
    // Note that SDL_Surface is not created here, but in the Init Method...
  }

  ~SdlInGameRenderer();

  /**
   * Initialize the renderer.
   * @return 0 if initialization went fine, -1 otherwise.
   *  If an error occurs, it is probably a good idea to look at SDL_GetError for
   *  more info.
   */ 
  int init();

  void clear();

  void render_cell(int i_i, int i_j, int i_cell_type);

  void flush();

private:

  ResourceResolverInterface & dep_resolver_;

  std::map<int, SDL_Surface *> cell_images_;

  SDL_Surface * p_screen_;

  Uint32 black_;

  /**
   * Load all the images necessary to display
   * cells.
   *
   * @returns 0 if cell was loaded, -1 otherwise
   */
  int load_cell_images();

  /**
   * Load the image necessary to display a cell.
   * 
   * @param i_cell_type 
   * @param o_pp_surface output address of the image after loading
   * @returns 0 if cell was loaded, -1 otherwise
   */
  int load_cell_image(int i_cell_type, SDL_Surface ** o_pp_surface);

};

#endif // _SDL_IN_GAME_RENDERER_HPP_
