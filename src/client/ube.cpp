/**
 * This is Free Software. See COPYING for information.
 */
#include "common/i18n.hpp"
#include "common/cout_logger.hpp"
#include "common/logging.hpp"
#include "common/prefix_resource_resolver.hpp"
#include "common/silent_logger.hpp"
#include "common/stat_file_checker.hpp"

#include "option_parser.hpp"
#include "sdl_clock.hpp"
#include "ube_game.hpp"

#include "config.h"

#include <cstdio>
#include <boost/shared_ptr.hpp>
#include <iostream>
#include <stdio.h>
#include <stdlib.h> /* for exit() */
#include "SDL.h"  
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"

using namespace std;


int main(int argc, char ** argv) {

  boost::shared_ptr<LoggerInterface> logger( new CoutLogger());

  Logging::init_logging(*logger);
  // TODO : add the loading of some configuration for the categories
  // Logging::add_logging_category("sdl_in_game_renderer");
  // Logging::add_logging_category("main");
  // Logging::add_logging_category("parser");
  //  Logging::add_logging_category("cell");
  // Logging::add_logging_category("in_game_view");
  //  Logging::add_logging_category("puzzle_selection");
  //Logging::add_logging_category("view");
  //Logging::add_logging_category("ube_game");

  // Prepare a resource resolver
  const StatFileChecker checker;
  PrefixResourceResolver resolver(checker);
  const char* prefixes[2] = { PREFIX, ".."};
  resolver.set_prefixes(prefixes,2);

  // Init i18n

  std::cout << "Preparing gettext with LC_ALL :" << LC_ALL << std::endl;
  std::cout << "PACKAGE text domain to bind :" << PACKAGE << std::endl;
  std::cout << "Resolve locale dir : " << resolver.get_locale_dir().c_str() << std::endl;

  setlocale(LC_ALL, "");
  bindtextdomain(PACKAGE, resolver.get_locale_dir().c_str());
  textdomain(PACKAGE);

  // Parse options
  OptionParser parser;
  if (parser.parse_options(argc, (const char **) argv) != 0) {
    printf("Error while parsing options ... TODO : use popt to generate a nice message\n");
    return -1;
  }

  SdlClock clock;

  // Actually prepare and run the game
  UbeGame ube(&clock, resolver, parser);
  if (ube.prepare_game() != 0) {
    std::cout << "Error while preparing game" << std::endl;
    std::cout << "Error message : " << ube.get_preparation_error_message() << std::endl;
  } else {
    ube.play();
  }

  return 0;
}
