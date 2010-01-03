#include "sdl_view.hpp"

#include "common/resource_resolver_interface.hpp"
#include "common/logging.hpp"

#include "sdl_controller.hpp"
#include "game_event.hpp"

#include <cstdio>
#include <cassert>

#include "SDL.h"
#include "SDL_image.h"

#include <boost/format.hpp>
using namespace boost;

bool SdlView::music_started_ = false;
Mix_Music * SdlView::pMusic_ = NULL;

// TODO : put the SDL ttf code back to also display some text !!
SdlView::SdlView(ResourceResolverInterface & dep_resolver,
		 SdlController & dep_controller) : 
  ViewInterface(),
  ObserverInterface(),
  dep_resolver_(dep_resolver),
  dep_controller_(dep_controller)
{
  blue_ = true;

  // Note : shouln't the screen be shared between all 
  // SDL_Views ?
  pScreen_ = SDL_SetVideoMode(640, 480, 8, SDL_SWSURFACE);
  if (pScreen_ == NULL) {
    // Or should I throw an exception ? 
    // Does this message need to be translated ? 
    fprintf(stderr, "Couldn't set 640x480x8 video mode: %s\n", SDL_GetError());
    // There is nothing I can do, so dying is an option...
    // But an exception would be nicer
    exit(1);
  }

  // Load the GNU image
  SDL_Surface *temp;
  temp = IMG_Load(dep_resolver_.get_image_file_name("gnu.png").c_str());
  if (temp == NULL) {
    printf("Unable to load bitmap: %s\n", SDL_GetError());
    exit(1);
  }
  pGnuImage_ = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);

  src_.x = 0;
  src_.y = 0;
  src_.w = pGnuImage_->w;
  src_.h = pGnuImage_->h;

  dest_.x = 100;
  dest_.y = 100;
  dest_.w = pGnuImage_->w;
  dest_.h = pGnuImage_->h;

  blue_color_ = SDL_MapRGB(pScreen_->format, 0x00, 0x00, 0xff);
  green_color_ = SDL_MapRGB(pScreen_->format, 0x00, 0xff, 0x00);
  

}

SdlView::~SdlView() 
{
  SDL_FreeSurface(pGnuImage_);
  SDL_FreeSurface(pScreen_); // ?
}

void 
SdlView::musicDone() {
  Mix_HaltMusic();
  Mix_FreeMusic(SdlView::pMusic_);
  SdlView::pMusic_ = NULL;
}

bool
SdlView::is_in_gnu()
{
  int x = dep_controller_.get_mouse_x();
  int y = dep_controller_.get_mouse_y();

  return (x >= 100 && x <= 250 && y >= 100 && y <= 250);
}

void
SdlView::render_game() 
{

  LOG_D(str(format("View - drawning, blue is %1%") % blue_), "view");

  if (blue_ && is_in_gnu()) {
    blue_ = false;
  } else if (!blue_ && !is_in_gnu()) {
    blue_ = true;
  }
  
  if (blue_) {
    SDL_FillRect(pScreen_, NULL, blue_color_);
  } else {
    SDL_FillRect(pScreen_, NULL, green_color_);
  }

  SDL_BlitSurface(pGnuImage_, &src_, pScreen_, &dest_);
  SDL_Flip(pScreen_);

  // If this is the first time we render, load a music and start playing it.
  // This is just for a quick test and should not go into the final code !
  if (!SdlView::music_started_) {
    SdlView::pMusic_ = Mix_LoadMUS("/home/phtrivier/prj/ube/data/ogg/music.ogg");
    if (SdlView::pMusic_ == NULL) {
      printf("Unable to load music file : %s", Mix_GetError());    
      exit(-1);
    } else {
      Mix_PlayMusic(SdlView::pMusic_, 0);
      Mix_HookMusicFinished(SdlView::musicDone); 
      // ... so apparently it is *hard* to pass a 
      // C++ method to a C function ... so I will need to have some singleton here :(
    }
    // Only load once ... 
    music_started_ = true;
  }

}

void
SdlView::handle_event(int iEventCode) {
  if (iEventCode == GameEvent::MOUSE_IN_GNU) {
    blue_ = false;
  } else if (iEventCode == GameEvent::MOUSE_OUT_GNU) {
    blue_ = true;
  } 
}
