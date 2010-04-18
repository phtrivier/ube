/**
 * This is Free Software. See COPYING for information.
 */
#ifndef _SDL_RENDERER_HPP_
#define _SDL_RENDERER_HPP_

#include <string>

#include "SDL.h"


class ResourceResolverInterface;

/**
 * Root class for all renderer based on SDL.
 */
class SdlRenderer { 

public:

  /**
   * Constructor.
   *
   * @param i_p_screen SDL Surface for the screen. The surface
   * should already have been successfully initialized, and is not
   * owned by the renderer, or cleared in the destructor.
   */
  SdlRenderer(ResourceResolverInterface & dep_resolver, SDL_Surface * dep_p_screen) :
    dep_resolver_(dep_resolver),
    dep_p_screen_(dep_p_screen) {
  }

  /**
   * Destructor.
   */
  virtual ~SdlRenderer() {
  }

  /**
   * Generic purpose initialization.
   * It should *not* initialize the SDL screen.
   */
  virtual int init();

  /**
   * Flip the screen.
   */
  void flush();
  
protected : 

  // Quick access to colors
  Uint32 black_;
  Uint32 white_;
  Uint32 gray_;
  Uint32 blue_;

  /**
   * Access to the screen surface.
   */
  inline SDL_Surface * get_screen() {
    return dep_p_screen_;
  }

  /**
   * Access to there resource resolver
   */
  inline ResourceResolverInterface & get_resolver() {
    return dep_resolver_;
  }

  /**
   * Safely clear an image
   */
  inline void clear_image(SDL_Surface * i_p_image) {
    if (i_p_image != NULL) {
      SDL_FreeSurface(i_p_image);
    }
  }

  /**
   * Loads an image by its name.
   *
   * @param i_image_name name with suffix (eg "cell_0.png")
   * @param o_pp_surface output address of the surface afer loading
   * @returns 0 if image was loaded, -1 otherwise.
   */
  int load_image(std::string i_image_name, SDL_Surface ** o_pp_surface);

  /**
   * Helper function to created RGB color based on 
   * the screen surface.
   */
  Uint32 rgb(Uint8 r, Uint8 g, Uint8 b);


private:

  ResourceResolverInterface & dep_resolver_;
  SDL_Surface * dep_p_screen_;

};

#endif // _SDL_RENDERER_HPP_
