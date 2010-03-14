#ifndef _UBE_GAME_HPP_
#define _UBE_GAME_HPP_

#include <string>

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

  SdlInGameRenderer * p_in_game_renderer_;
  InGameModeFactory * p_in_game_mode_factory_;

  int prepare_sdl();
  int prepare_game_modes();
  int prepare_in_game_mode();

};

#endif // _UBE_GAME_HPP_
