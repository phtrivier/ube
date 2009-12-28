#include "common/prefix_resource_resolver.hpp"
#include "common/stat_file_checker.hpp"
#include "sdl_view.hpp"
#include "sdl_controller.hpp"
#include "sdl_clock.hpp"
#include "game_mode.hpp"
#include "game_loop.hpp"

#include <config.h>
#include <locale.h>
#include "gettext.h"
#define _(String) gettext (String)
#include <iostream>
#include <cstdio>
#include <stdio.h>
#include <stdlib.h> /* for exit() */
using namespace std;

#include "SDL.h"  
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"


int main(int argc, char ** argv) {

/* We're going to be requesting certain things from our audio
     device, so we set them up beforehand */
  int audio_rate = 22050;
  Uint16 audio_format = AUDIO_S16; /* 16-bit stereo */
  int audio_channels = 2;
  int audio_buffers = 4096;

  /* Initialize defaults, Video and Audio subsystems */
  if((SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO)==-1)) { 
    printf("Could not initialize SDL: %s.\n", SDL_GetError());
    return -1;
  }

  // Music test
  /* This is where we open up our audio device.  Mix_OpenAudio takes
     as its parameters the audio format we'd /like/ to have. */
  if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers)) {
    printf("Unable to open audio!\n");
    return 1;
  }


  // This function gets the actual info from the audio system.
  // This could be used to compare with the expected one, and check for any inconsistencies? 
  /* If we actually care about what we got, we can ask here.  In this
     program we don't, but I'm showing the function call here anyway
     in case we'd want to know later. */
  // Mix_QuerySpec(&audio_rate, &audio_format, &audio_channels);

  
  /* Clean up on exit */
  atexit(SDL_Quit);

  const StatFileChecker checker;
  PrefixResourceResolver resolver(checker);
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
