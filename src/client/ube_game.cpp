#include "ube_game.hpp"

#include "option_parser.hpp"
#include "sdl_controller.hpp"
#include "sdl_clock.hpp"
#include "game_mode.hpp"
#include "in_game_model.hpp"
#include "sdl_in_game_renderer.hpp"
#include "in_game_mode_factory.hpp"
#include "in_game_mode.hpp"
#include "sdl_puzzle_selection_renderer.hpp"
#include "puzzle_selection_mode_factory.hpp"
#include "puzzle_selection_mode.hpp"
#include "game_event.hpp"

#include "common/logging.hpp"

#include <config.h>
#include <assert.h>

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
UbeGame::prepare_sdl()
{
  int res = 0;
  if((SDL_Init(SDL_INIT_VIDEO)==-1)) { 
    res = -1;
  } else {
    p_screen_ = SDL_SetVideoMode(800, 600, 8, SDL_SWSURFACE);
    if (p_screen_ == NULL) {
      res = -1;
    } else {
      if (TTF_Init() == -1) {
	ttf_preparation_error_message("Could not initialize TTF %1%");
	res = -1;
      } else {
	
	std::string title = str(format("ube v%1%") % VERSION);
	SDL_WM_SetCaption(title.c_str(), title.c_str());

	atexit(SDL_Quit);
      }
    }
  }
  if (res != 0) {
    sdl_preparation_error_message("Could not initialize SDL : %1%.\n");
  }
  return res;
}

int
UbeGame::prepare_game_modes()
{

  int res = prepare_puzzle_selection_mode();
  if (res == 0) {
    
    // FIXME(pht) : the code about the puzzle should
    // probably be somewhere else ? 
    // Note : I'll need to charge a given puzzle
    
    LOG_D("main") << "Do we have a puzzle name ? " << dep_option_parser_.has_puzzle_file_name() << std::endl;
  
    if (dep_option_parser_.has_puzzle_file_name()) {
      LOG_D("main") << "Getting puzzle file name" << std::endl;
      std::string puzzle_file_name = dep_option_parser_.get_puzzle_file_name();
      LOG_D("main") << "Puzzle file name : " << puzzle_file_name << std::endl;
      LOG_D("main") << "Puzzle file name's c_str() : " << puzzle_file_name.c_str() << std::endl;
      res = prepare_in_game_mode(puzzle_file_name);
    }
  }
  return res;
}


int
UbeGame::prepare_puzzle_selection_mode()
{
  assert(p_screen_ != NULL);

  p_puzzle_selection_renderer_ = new SdlPuzzleSelectionRenderer(dep_resolver_, p_screen_);
  int res = p_puzzle_selection_renderer_->init();
  if (res != 0) {
    sdl_preparation_error_message("Error while initializing sdl_renderer : %1%\n");
  } else {
    p_puzzle_selection_mode_factory_ = new PuzzleSelectionModeFactory(*p_puzzle_selection_renderer_);
    res = p_puzzle_selection_mode_factory_->create_mode();
    if (res != 0) {
      sdl_preparation_error_message("Error creating puzzle_selection_mode : %1%\n");
    } else {
      p_puzzle_selection_mode_ = static_cast<PuzzleSelectionMode*>(p_puzzle_selection_mode_factory_->get_mode().get());
      register_game_mode("puzzle-selection", p_puzzle_selection_mode_);
    }
  }
  return res;
}


int
UbeGame::prepare_in_game_mode(std::string & i_puzzle_file_name)
{
  // Assume the screen has been prepared in prepare_sdl
  assert(p_screen_ != NULL);

  int res = -1;

  if (p_in_game_mode_factory_ == NULL) {
    // Note(pht) : that could "look" simplier to let the factory create
    // SdlInGameRenderer, but then I would need to pass the screen explicitely, 
    // and that kinda breaks the "No SDL in Factory interface, like..."
    p_in_game_renderer_ = new SdlInGameRenderer(dep_resolver_, p_screen_);
    res = p_in_game_renderer_->init();
    if (res != 0) {
      sdl_preparation_error_message("Error while initializing sdl_renderer : %1%\n");
    } else {

      p_in_game_mode_factory_ = new InGameModeFactory(dep_resolver_,
						      *p_in_game_renderer_,
						      i_puzzle_file_name);

      res = p_in_game_mode_factory_->create_mode();
      if (res != 0) {
	sdl_preparation_error_message("Error creating in_game_mode : %1%\n");
      } else {
	p_in_game_mode_ = static_cast<InGameMode *>(p_in_game_mode_factory_->get_mode().get());
	register_game_mode("in-game", p_in_game_mode_);
      }
    }
  } else {
    p_in_game_mode_factory_->load_puzzle(i_puzzle_file_name);
  }

  return res;
}

void
UbeGame::sdl_preparation_error_message(std::string i_msg)
{
   preparation_error_message_.append(str(format(i_msg) % SDL_GetError()));
 }

void
UbeGame::ttf_preparation_error_message(std::string i_msg)
{
   preparation_error_message_.append(str(format(i_msg) % TTF_GetError()));
}

void
UbeGame::play()
{
  if (dep_option_parser_.has_puzzle_file_name()) {
    set_current_game_mode("in-game");
  } else {
    set_current_game_mode("puzzle-selection");
  }

  loop();

  std::cout << std::endl;
  std::cout << "Thanks for playing !" << std::endl;
}

void
UbeGame::handle_event(int i_event_code)
{
  GameLoop::handle_event(i_event_code);

  switch (i_event_code) {
  case GameEvent::PUZZLE_SELECTED : {
    // FIXME(pht) : move some of this to prepare
    std::string puzzle_file_name = p_puzzle_selection_mode_->get_model().get_selected_puzzle_file_name();
    prepare_in_game_mode(puzzle_file_name);
    set_current_game_mode("in-game");
    break;
  }
  case (GameEvent::PUZZLE_FINISHED) : {
    LOG_D("ube_game") << "-----------------------" << std::endl;
    LOG_D("ube_game") << "Reseting model" << std::endl;
    p_puzzle_selection_mode_->get_model().reset();
    LOG_D("ube_game") << "model has hovered ? " << p_puzzle_selection_mode_->get_model().has_hovered_puzzle() << std::endl;
    set_current_game_mode("puzzle-selection");
    break;
  }
  }
}
