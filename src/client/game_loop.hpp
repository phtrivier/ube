#ifndef _GAME_LOOP_HPP_
#define _GAME_LOOP_HPP_

#include "observer_interface.hpp"
#include <string>
#include <map>

// Forward declare should be enough
#include "game_mode_interface.hpp"
class ClockInterface;

/**
 * Main game loop.
 */
class GameLoop : public ObserverInterface { 

  // Current game mode.
  GameModeInterface * pCurrentGameMode_;

  // Map of game modes, by names
  std::map<std::string, GameModeInterface *> gameModes_;

  // Clcok
  ClockInterface * pClock_;

  // Is the game running ? 
  bool running_;
  
public:

  GameLoop(ClockInterface * ipClock) : pClock_(ipClock) {
    running_=false;
  }

  virtual ~GameLoop() {
  }

  /**
   * Register a game mode. The game loop starts observing any event 
   * provided by the game mode, and the mode becomes eligible for
   * being set with set_current_game_mode.
   * TODO(pht) : use a reference instead of a pointer, the game loop does not own the game mode.
   */
  void register_game_mode(std::string iModeName, GameModeInterface * ipGameMode);
  
  /**
   * Force the current game mode.
   *
   * @param iModelName the name of a game mode. The mode should have been registered 
   * previously, or a logic_error will be thrown.
   */
  void set_current_game_mode(std::string iModeName);
  
  /**
   * The current game mode.
   */
  GameModeInterface * get_current_game_mode() {
    return pCurrentGameMode_;
  }
 
  /**
   * Start the infamous game loop.
   */
  void loop();

  /**
   * Handles events from any 
   */
  void handle_event(int iEventCode);
};

#endif // _GAME_LOOP_HPP_
