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
#include "sdl_view.hpp"
#include "sdl_controller.hpp"
#include "sdl_clock.hpp"
#include "game_mode.hpp"
#include "game_loop.hpp"

int main(int argc, char ** argv) {
  
  /* Initialize defaults, Video and Audio subsystems */
  if((SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO)==-1)) { 
    printf("Could not initialize SDL: %s.\n", SDL_GetError());
    return -1;
  }
  
  /* Clean up on exit */
  atexit(SDL_Quit);

  const StatFileChecker checker;
  ResourceResolver resolver(checker);
  const char* prefixes[2] = { PREFIX, ".."};
  resolver.set_prefixes(prefixes,2);

  setlocale(LC_ALL, "");

  bindtextdomain (PACKAGE, resolver.get_locale_dir().c_str());
  textdomain(PACKAGE);

  SdlController controller;

  SdlView view(&resolver);

  GameMode mode(&controller, &view);

  SdlClock clock;
  GameLoop loop(&clock);

  loop.register_game_mode("mode", &mode);
  loop.set_current_game_mode("mode");

  printf("Starting the loop ....\n");
  loop.loop();

  return 0;
}
