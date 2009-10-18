#include <config.h>
#include <locale.h>
#include "gettext.h"
#define _(String) gettext (String)

#include <greeter.hpp>

#include <iostream>
#include <cstdio>
using namespace std;

#include "SDL.h"   /* All SDL apps need this */
#include <stdio.h>
#include <stdlib.h> /* for exit() */

int main(int argc, char ** argv) {
  
  // printf("This is %s. Thanks for watching\n", PACKAGE_STRING);

  cout << "For info, LOCALEDIR is  : " << LOCALEDIR << endl;
  cout << "For info, DATADIR is  : " << DATADIR << endl;
  
  setlocale (LC_ALL, "");
  bindtextdomain (PACKAGE, LOCALEDIR);
  textdomain (PACKAGE);

  // Just for a lest ... normally I have done everything required ... 
  printf(_("Hello %s. What's the craic today ?\n"), "prout");

  Greeter g("PHT");
  g.greet();
  
  SDL_Surface* screen = NULL;

  /* Initialize defaults, Video and Audio subsystems */
  if((SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO)==-1)) { 
    printf("Could not initialize SDL: %s.\n", SDL_GetError());
    exit(-1);
  }
  
  /* Clean up on exit */
  atexit(SDL_Quit);

  screen = SDL_SetVideoMode(640, 480, 8, SDL_SWSURFACE);
  if ( screen == NULL ) {
    fprintf(stderr, "Couldn't set 640x480x8 video mode: %s\n", SDL_GetError());
    exit(1);
  }
  
  sleep(5);

  exit(0);
}
