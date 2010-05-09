/**
 * This is Free Software. See COPYING for information.
 */
#ifndef _UBE_GAME_HPP_
#define _UBE_GAME_HPP_

#include "game_loop.hpp"

#include <string>

#include "SDL.h"

class ResourceResolverInterface;
class OptionParser;

class SdlChapterSelectionRenderer;
class ChapterSelectionModeFactory;
class ChapterSelectionMode;

class SdlPuzzleSelectionRenderer;
class PuzzleSelectionModeFactory;
class PuzzleSelectionMode;

class SdlInGameRenderer;
class InGameModeFactory;
class InGameMode;

class Chapter;

/**
 * Class for the meat of the game
 */
class UbeGame : 
  public GameLoop
{ 

public:

  UbeGame(ClockInterface * i_p_clock,
	  ResourceResolverInterface & dep_resolver,
	  OptionParser & dep_option_parser) :
    GameLoop(i_p_clock),
    dep_resolver_(dep_resolver),
    dep_option_parser_(dep_option_parser),
    preparation_error_message_(""),
    p_chapter_selection_renderer_(NULL),
    p_chapter_selection_mode_factory_(NULL),
    p_chapter_selection_mode_(NULL),
    p_puzzle_selection_renderer_(NULL),
    p_puzzle_selection_mode_factory_(NULL),
    p_puzzle_selection_mode_(NULL),
    p_in_game_renderer_(NULL),
    p_in_game_mode_factory_(NULL),
    p_in_game_mode_(NULL)
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
  
  void handle_event(int i_event_code);

private:
  ResourceResolverInterface & dep_resolver_;
  OptionParser & dep_option_parser_;

  std::string preparation_error_message_;

  // Screen is owned by the game.
  SDL_Surface * p_screen_;

  // TODO(pht) : probably only one of the three classes should really be needed...
  SdlChapterSelectionRenderer * p_chapter_selection_renderer_;
  ChapterSelectionModeFactory * p_chapter_selection_mode_factory_;
  ChapterSelectionMode * p_chapter_selection_mode_;

  SdlPuzzleSelectionRenderer * p_puzzle_selection_renderer_;
  PuzzleSelectionModeFactory * p_puzzle_selection_mode_factory_;
  PuzzleSelectionMode * p_puzzle_selection_mode_;

  SdlInGameRenderer * p_in_game_renderer_;
  InGameModeFactory * p_in_game_mode_factory_;
  InGameMode * p_in_game_mode_;

  int prepare_sdl();
  int prepare_game_modes();

  int prepare_chapter_selection_mode();
  int prepare_puzzle_selection_mode(Chapter & i_chapter);
  int prepare_in_game_mode(std::string & i_puzzle_file_name);

  /**
   * Appends the current SDL_GetError to
   * the "preparation_error_message"
   *
   * @param i_mgs, message, to be formatted by boost::format (in
   * should contain at least %1% to contain the actual SDL error.)
   */
  void sdl_preparation_error_message(std::string i_msg);

  void ttf_preparation_error_message(std::string i_msg);

};

#endif // _UBE_GAME_HPP_
