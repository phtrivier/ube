#ifndef _SDL_VIEW_HPP_
#define _SDL_VIEW_HPP_

#include "view_interface.hpp"
#include "observer_interface.hpp"
#include "SDL.h"

// Music test
#include "SDL_mixer.h"

class ResourceResolverInterface;
class SdlController;

/**
 * A game view that uses SDL.
 */
class SdlView : 
  public ViewInterface, 
  public ObserverInterface 
{ 
public:

  // Constructor
  SdlView(ResourceResolverInterface & dep_resolver,
	  SdlController & dep_controller);
  // Desctructor
  ~SdlView();

  // For sound test
  static bool music_started_;
  static Mix_Music * pMusic_;
  static void musicDone();

  void render_game();

  void handle_event(int iEventCode);

private:
  // Dependencies
  ResourceResolverInterface & dep_resolver_;
  SdlController & dep_controller_;

  // Private stuff
  SDL_Surface * pScreen_;

  SDL_Surface * pGnuImage_;

  SDL_Rect src_;
  SDL_Rect dest_;

  bool blue_;

  Uint32 green_color_;
  Uint32 blue_color_;

  bool is_in_gnu();
  
};

#endif // _SDL_VIEW_HPP_
