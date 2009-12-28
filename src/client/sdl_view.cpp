#include "sdl_view.hpp"

#include "common/abstract_resource_resolver.hpp"

#include <stdlib.h> /* for exit() */
#include <cassert>

#include "SDL.h"
#include "SDL_image.h"


bool SdlView::music_started_ = false;
Mix_Music * SdlView::pMusic_ = NULL;

// TODO : put the SDL ttf code back to also display some text !!

SdlView::SdlView(AbstractResourceResolver * ipResolver)
{
  assert(ipResolver != NULL);
  pResolver_ = ipResolver;
  
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
  temp = IMG_Load(pResolver_->get_image_file_name("gnu.png").c_str());
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

void
SdlView::render_game() 
{
  SDL_FillRect(pScreen_, NULL, SDL_MapRGB(pScreen_->format, 0x00, 0x00, 0xff));
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
