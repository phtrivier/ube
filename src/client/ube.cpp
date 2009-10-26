#include <config.h>
#include <locale.h>
#include "gettext.h"
#define _(String) gettext (String)

#include <greeter.hpp>

#include <iostream>
#include <cstdio>
using namespace std;

#include "SDL.h"  
#include "SDL_image.h"

#include <stdio.h>
#include <stdlib.h> /* for exit() */

#include "lua_script_runner.hpp"
#include "resource_resolver.hpp"
#include "stat_file_checker.hpp"

int main(int argc, char ** argv) {
  
  cout << "For info, LOCALEDIR is  : " << LOCALEDIR << endl;
  cout << "For info, DATADIR is  : " << DATADIR << endl;
  
  setlocale (LC_ALL, "");
  bindtextdomain (PACKAGE, LOCALEDIR);
  textdomain (PACKAGE);

  // Just for a lest ... normally I have done everything required ... 
  fprintf(stdout, _("Hello %s. What's the craic today ?\n"), "prout");

  Greeter g("PHT");
  g.greet();
  
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
  resolver.setPrefixes(prefixes,2);

  string fileName = resolver.getImageFileName("gnu.png");
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
 
  SDL_BlitSurface(image, &src, screen, &dest);
  SDL_Flip(screen);

  bool running = true;
  while (running) {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
      switch(event.type)
	{  
	case SDL_KEYDOWN:
	  /* handle keyboard stuff here */				
	  running = false;
	  break;
	  
	case SDL_QUIT:
	  /* Set whatever flags are necessary to */
	  /* end the main game loop here */
	  running = false;
	  break;
	}
    }
  }

  LuaScriptRunner runner;

  return 0;
}
