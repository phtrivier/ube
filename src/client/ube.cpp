#include "common/logging.hpp"
#include "common/prefix_resource_resolver.hpp"
#include "common/cout_logger.hpp"
#include "common/silent_logger.hpp"
#include "common/stat_file_checker.hpp"

#include "option_parser.hpp"
#include "sdl_view.hpp"
#include "sdl_controller.hpp"
#include "sdl_clock.hpp"
#include "game_mode.hpp"
#include "game_loop.hpp"
#include "in_game_model.hpp"
#include "sdl_in_game_renderer.hpp"
#include "in_game_mode_factory.hpp"

#include <config.h>
#include <locale.h>
#include "gettext.h"
#define _(String) gettext (String)
#include <iostream>
#include <cstdio>
#include <stdio.h>
#include <stdlib.h> /* for exit() */
using namespace std;

#include <boost/shared_ptr.hpp>

#include "SDL.h"  
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"


int main(int argc, const char ** argv) {

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

  boost::shared_ptr<LoggerInterface> logger( new CoutLogger());
  // boost::shared_ptr<LoggerInterface> logger( new SilentLogger());
  Logging::init_logging(*logger);
  // TODO : add the loading of some configuration for the categories
  Logging::add_logging_category("sdl_in_game_renderer");
  Logging::add_logging_category("main");
  Logging::add_logging_category("parser");

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

  SdlInGameRenderer renderer(resolver);
  int res = renderer.init();
  if (res != 0) {
    printf("Error while initializing sdl_renderer : %s\n", SDL_GetError());
    return -1;
  }
  //  SdlController controller;
  // SdlView view(resolver,controller);
  // // Or should it be the game_mode's job to do this ?
  // // or a factory whose job would be to create stuff !!
  // controller.add_observer(&view);

  OptionParser parser;
  if (parser.parse_options(argc, argv) != 0) {
    printf("Error while parsing options ... TODO : use popt to generate a nice message\n");
    return -1;
  }

  std::string puzzle_file_name = "puzzle1.lua";

  LOG_D("main") << "Do we have a puzzle name ? " << parser.has_puzzle_file_name() << std::endl;

  if (parser.has_puzzle_file_name()) {
    LOG_D("main") << "Getting puzzle file name" << std::endl;
    puzzle_file_name = parser.get_puzzle_file_name();
  }
  
  LOG_D("main") << "Puzzle file name : " << puzzle_file_name << std::endl;
  LOG_D("main") << "Puzzle file name's c_str() : " << puzzle_file_name.c_str() << std::endl;

  InGameModeFactory in_game_mode_factory(resolver, renderer, puzzle_file_name);
  int creation_res = in_game_mode_factory.create_mode();
  LOG_D("main") << "Creation of mode resulted in " << creation_res << std::endl;
  if ( creation_res != 0) {
    printf("Error while creating in_game_mode : %s", SDL_GetError());
    return -1;
  }
  boost::shared_ptr<GameMode> mode = in_game_mode_factory.get_mode();
  assert(mode.get() != NULL);

  SdlClock clock;
  GameLoop loop(&clock);

  loop.register_game_mode("in-game", mode.get()); // FIXME : it would be better to use a reference here, wouldn't it ?
  loop.set_current_game_mode("in-game");

  loop.loop();

  std::cout << std::endl;
  std::cout << "Thanks for playing !" << std::endl;

  return 0;
}
