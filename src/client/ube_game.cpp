#include "ube_game.hpp"

#include "option_parser.hpp"
#include "sdl_controller.hpp"
#include "sdl_clock.hpp"
#include "game_mode.hpp"
#include "game_loop.hpp"
#include "in_game_model.hpp"
#include "sdl_in_game_renderer.hpp"
#include "in_game_mode_factory.hpp"

#include "common/logging.hpp"

#include "SDL.h"  
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"

#include <boost/format.hpp>
using boost::format;

int
UbeGame::prepare_game() 
{
  int res = prepare_sdl();
  if (res == 0) {
    res = prepare_game_modes();
  }

  return res;
}

int
UbeGame::prepare_in_game_mode()
{
  p_in_game_renderer_ = new SdlInGameRenderer(dep_resolver_);
  int res = p_in_game_renderer_->init();
  if (res != 0) {
    preparation_error_message_.append(str(format("Error while initializing sdl_renderer : %1%\n") % SDL_GetError()));
  } else {

    // FIXME(pht) : the code about the puzzle should
    // probably be somewhere else ? 
    // Note : I'll need to charge a given puzzle
    std::string puzzle_file_name = "puzzle1.lua";

    LOG_D("main") << "Do we have a puzzle name ? " << dep_option_parser_.has_puzzle_file_name() << std::endl;

    if (dep_option_parser_.has_puzzle_file_name()) {
      LOG_D("main") << "Getting puzzle file name" << std::endl;
      puzzle_file_name = dep_option_parser_.get_puzzle_file_name();
    }
    
    LOG_D("main") << "Puzzle file name : " << puzzle_file_name << std::endl;
    LOG_D("main") << "Puzzle file name's c_str() : " << puzzle_file_name.c_str() << std::endl;
    
    p_in_game_mode_factory_ = new InGameModeFactory(dep_resolver_,
						    *p_in_game_renderer_,
						    puzzle_file_name);
						
    
    res = p_in_game_mode_factory_->create_mode();
    if (res != 0) {
      preparation_error_message_.append(str(format("Error creating in_game_mode : %1%\n") % SDL_GetError())); 
    }
  }
  return res;
}

int
UbeGame::prepare_game_modes()
{
  return prepare_in_game_mode();
}

int
UbeGame::prepare_sdl()
{
  int res = 0;
  if((SDL_Init(SDL_INIT_VIDEO)==-1)) { 
    preparation_error_message_.append(str(format("Could not initialize SDL: %1%.\n") % SDL_GetError()));
    res = -1;
  } else {
    atexit(SDL_Quit);
  }
  return res;
}

void
UbeGame::play()
{
  boost::shared_ptr<GameMode> mode = p_in_game_mode_factory_->get_mode();
  assert(mode.get() != NULL);

  SdlClock clock;

  GameLoop loop(&clock);

  loop.register_game_mode("in-game", mode.get()); // FIXME : it would be better to use a reference here, wouldn't it ?
  loop.set_current_game_mode("in-game");

  loop.loop();

  std::cout << std::endl;
  std::cout << "Thanks for playing !" << std::endl;

}
