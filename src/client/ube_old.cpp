#include <config.h>
#include <locale.h>
#include "gettext.h"
#define _(String) gettext (String)

// #include <greeter.hpp>

#include <iostream>
#include <cstdio>
using namespace std;

#include "SDL.h"  
#include "SDL_image.h"
#include "SDL_ttf.h"

#include <stdio.h>
#include <stdlib.h> /* for exit() */

#include "resource_resolver.hpp"
#include "stat_file_checker.hpp"

int main(int argc, char ** argv) {
  
  cout << "For info, LOCALEDIR is  : " << LOCALEDIR << endl;
  cout << "For info, DATADIR is  : " << DATADIR << endl;
  SDL_Surface* screen = NULL;

  /* Initialize defaults, Video and Audio subsystems */
  if((SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO)==-1)) { 
    printf("Could not initialize SDL: %s.\n", SDL_GetError());
    return -1;
  }
  
  /* Clean up on exit */
  atexit(SDL_Quit);

  screen = SDL_SetVideoMode(640, 480, 8, SDL_SWSURFACE);
  if ( screen == NULL ) {
    fprintf(stderr, "Couldn't set 640x480x8 video mode: %s\n", SDL_GetError());
    exit(1);
  }

  SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0x00, 0x00, 0xff));

  SDL_Surface *image;
  SDL_Surface *temp;
 
  const StatFileChecker checker;
  ResourceResolver resolver(checker);
  const char* prefixes[2] = { PREFIX, ".."};
  resolver.set_prefixes(prefixes,2);

  setlocale (LC_ALL, "");
  // TODO(pht) : shouldn't I change this to use the locale
  // from the resolver instead of LOCALEDIR ? 
  bindtextdomain (PACKAGE, resolver.get_locale_dir().c_str());
  textdomain (PACKAGE);

  if (TTF_Init() != 0) {
    printf("TTF_Init error : %s\n", TTF_GetError());
    exit(1);
  }

  TTF_Font *pFont;
  pFont = TTF_OpenFont(resolver.get_font_file_name("FreeSans.ttf").c_str(), 16);
  if (pFont == NULL) {
    printf("Could not load font : %s\n", TTF_GetError());
    exit(1);
  }

  // FIXME(pht) : I really need a "safe" way to print a string with args into a 
  // a buffer of variable size (ideally a string itself ... string.format ?)
  char text[256];
  sprintf(text, _("Hello %s. What's the craic today ?\n"), "pht");

  SDL_Color fg={255,255,255};
  SDL_Color bg={0,0,255};
  SDL_Surface * text_surface = TTF_RenderUTF8_Shaded(pFont, text, fg, bg);
  if (text_surface == NULL) {
    printf("Could not print text : %s\n", TTF_GetError());
  }
  
  SDL_Surface * solid_text = TTF_RenderUTF8_Solid(pFont, text, fg);
  SDL_Surface * blended_text = TTF_RenderUTF8_Blended(pFont, text, fg);

  fprintf(stdout, _("Hello %s. What's the craic today ?\n"), "prout");

  string fileName = resolver.get_image_file_name("gnu.png");
  cout << "Will look for image in path " << fileName << endl;

  temp = IMG_Load(fileName.c_str());
  if (temp == NULL) {
    printf("Unable to load bitmap: %s\n", SDL_GetError());
    return 1;
  }
  
  image = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);
  
  SDL_Rect src, dest;
 
  src.x = 0;
  src.y = 0;
  src.w = image->w;
  src.h = image->h;
 
  dest.x = 100;
  dest.y = 100;
  dest.w = image->w;
  dest.h = image->h;
 
  SDL_Rect textRect;
  textRect.x = 100;
  textRect.y = 250;
  textRect.w = text_surface->w;
  textRect.h = text_surface->h;

  SDL_Rect solidRect = { 100, 280, solid_text->w, solid_text->h };
  SDL_Rect blendedRect = { 100, 300, solid_text->w, solid_text->h };

  bool blue = true;
  bool running = true;
  SDL_Event event;
  while (running) {
    // FIXME(pht) : instead, use SDL_getTicks, plus a now / then counter,
    // along with SDL_Delay, to make the CPU consumption less horrible.
    while(SDL_PollEvent(&event)) {
      switch(event.type) {  
      case SDL_KEYDOWN:
	/* handle keyboard stuff here */				
	running = false;
	break;
	
      case SDL_QUIT:
	/* Set whatever flags are necessary to */
	/* end the main game loop here */
	running = false;
	break;
	
      case SDL_MOUSEMOTION:
	if (event.motion.x >= 100 && event.motion.x <= 100 + image->w 
	    && event.motion.y >= 100 && event.motion.y <= 100 + image->h) {
	  blue = false;
	} else {
	  blue = true;
	}
      }
      
      if (blue) {
	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0x00, 0x00, 0xff));
      } else {
       	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0x00, 0xff, 0x00));
      }

      SDL_BlitSurface(image, &src, screen, &dest);
      SDL_BlitSurface(text_surface, NULL, screen, &textRect);
      SDL_BlitSurface(solid_text, NULL, screen, &solidRect);
      SDL_BlitSurface(blended_text, NULL, screen, &blendedRect);

      SDL_Flip(screen);

      // // Of course in the real implementation you would have to count
      // // for how long it took to display the image, make sure the animation state
      // // is properly set, etc...
      SDL_Delay(30);

    }
  }

  return 0;
}
