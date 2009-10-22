#include <config.h>
#include <locale.h>
#include "gettext.h"
#define _(String) gettext (String)

#include <greeter.hpp>

#include <iostream>
#include <cstdio>
using namespace std;

#include "SDL.h"  

#include <stdio.h>
#include <stdlib.h> /* for exit() */

#include "lua_script_runner.hpp"

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
  
  for (int i = 0 ; i < 100000 ; i++) {
    cout << ".";
  }

  LuaScriptRunner runner;

  return 0;
}
