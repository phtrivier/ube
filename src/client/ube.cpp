/**
 * This is Free Software. See COPYING for information.
 */
#include "common/i18n.hpp"
#include "common/logging.hpp"
#include "common/prefix_resource_resolver.hpp"
#include "common/cout_logger.hpp"
#include "common/silent_logger.hpp"
#include "common/stat_file_checker.hpp"

#include "sdl_clock.hpp"
#include "option_parser.hpp"
#include "ube_game.hpp"

#include "config.h"

#include <iostream>
#include <cstdio>
#include <stdio.h>
#include <stdlib.h> /* for exit() */
using namespace std;

#include <boost/shared_ptr.hpp>
#include <boost/format.hpp>
using boost::format;

#include "SDL.h"  
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"

void show_version() {
  std::cout << str(format(_("ube %1%")) % PACKAGE_VERSION) << std::endl;
}

void show_copyright() {
  show_version();
  std::cout << _("Copyright (c) 2010 Pierre-Henri Trivier") << std::endl;
  std::cout << std::endl;
  std::cout << _("This is free software, licensed under the MIT ('X11') License.") << std::endl;
  std::cout << _("See <http://www.opensource.org/licenses/mit-license.php>") << std::endl;
  std::cout << _("There is NO WARRANTY, to the extend permitted by law.") << std::endl;
  std::cout << std::endl;
  std::cout << _("Written by Pierre-Henri Trivier") << std::endl;
}

int main(int argc, char ** argv) {

  boost::shared_ptr<LoggerInterface> logger( new CoutLogger());
;
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
  setlocale(LC_ALL, "");
  bindtextdomain(PACKAGE, resolver.get_locale_dir().c_str());
  textdomain(PACKAGE);

  // Parse options
  OptionParser parser;
  if (parser.parse_options(argc, (const char **) argv) != 0) {
    printf("Error while parsing options ... TODO : use popt to generate a nice message\n");
    return -1;
  }

  if (parser.should_show_version()) {
    show_version();
  } else if (parser.should_show_copyright()) {
    show_copyright();
  } else {
    
    SdlClock clock;

    // Actually prepare and run the game
    UbeGame ube(&clock, resolver, parser);
    if (ube.prepare_game() != 0) {
      std::cout << "Error while preparing game" << std::endl;
      std::cout << "Error message : " << ube.get_preparation_error_message() << std::endl;
    } else {
      ube.play();
    }

  }

  return 0;
}
