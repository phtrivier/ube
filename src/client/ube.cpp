#include "common/logging.hpp"
#include "common/prefix_resource_resolver.hpp"
#include "common/cout_logger.hpp"
#include "common/silent_logger.hpp"
#include "common/stat_file_checker.hpp"

#include "option_parser.hpp"

#include "ube_game.hpp"

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

int main(int argc, char ** argv) {

  boost::shared_ptr<LoggerInterface> logger( new CoutLogger());
;
  Logging::init_logging(*logger);
  // TODO : add the loading of some configuration for the categories
  Logging::add_logging_category("sdl_in_game_renderer");
  Logging::add_logging_category("main");
  Logging::add_logging_category("parser");
  //  Logging::add_logging_category("puzzle_selection");

  //  Logging::add_logging_category("view");

  // Prepare a resource resolver
  const StatFileChecker checker;
  PrefixResourceResolver resolver(checker);
  const char* prefixes[2] = { PREFIX, ".."};
  resolver.set_prefixes(prefixes,2);

  // Init i18n
  setlocale(LC_ALL, "");
  bindtextdomain (PACKAGE, resolver.get_locale_dir().c_str());
  textdomain(PACKAGE);

  // Parse options
  OptionParser parser;
  if (parser.parse_options(argc, (const char **) argv) != 0) {
    printf("Error while parsing options ... TODO : use popt to generate a nice message\n");
    return -1;
  }

  // Actually prepare and run the game
  UbeGame ube(resolver, parser);
  if (ube.prepare_game() != 0) {
    std::cout << "Error while preparing game" << std::endl;
    std::cout << "Error message : " << ube.get_preparation_error_message() << std::endl;
  } else {
    ube.play();
  }

  return 0;
}
