#ifndef _UBE_GAME_HPP_
#define _UBE_GAME_HPP_

#include <string>

#include "SDL.h"

class ResourceResolverInterface;
class OptionParser;
class SdlInGameRenderer;
class InGameModeFactory;

/**
 * Class for the meat of the game
 */
class UbeGame { 

public:

  UbeGame(ResourceResolverInterface & dep_resolver,
	  OptionParser & dep_option_parser) :
    dep_resolver_(dep_resolver),
    dep_option_parser_(dep_option_parser),
    preparation_error_message_(""),
    p_in_game_renderer_(NULL),
    p_in_game_mode_factory_(NULL)
  
  {
  }

  /**
   * Initialize resources, start the
   * SDL subsystems, etc..
   * @return 0 if everything went find, -1 if there was
   * an error.
   */
  int prepare_game();

  /**
   * If an error occured during the preparation
   * of the game, this will contain an (hopefully)
   * helpfull message.
   */
  std::string & get_preparation_error_message() {
    return preparation_error_message_;
  }

  /**
   * Start the main loop.
   */
  void play();
  
private:
  ResourceResolverInterface & dep_resolver_;
  OptionParser & dep_option_parser_;

  std::string preparation_error_message_;

  // Screen is owned by the game.
  SDL_Surface * p_screen_;

  // TODO(pht) : only the game_mode_factory should
  // be needed.
  SdlInGameRenderer * p_in_game_renderer_;
  InGameModeFactory * p_in_game_mode_factory_;

  int prepare_sdl();
  int prepare_game_modes();

  int prepare_puzzle_selection_mode();
  int prepare_in_game_mode();

  /**
   * Appends the current SDL_GetError to
   * the "preparation_error_message"
   *
   * @param i_mgs, message, to be formatted by boost::format (in
   * should contain at least %1% to contain the actual SDL error.)
   */
  void sdl_preparation_error_message(std::string i_msg);

};

#endif // _UBE_GAME_HPP_
