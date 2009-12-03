#ifndef _GAME_LOOP_HPP_
#define _GAME_LOOP_HPP_

#include "abstract_observer.hpp"
#include <string>
#include <map>

// Forward declare should be enough
#include "abstract_game_mode.hpp"

/**
 * Main game loop.
 */
class GameLoop : public AbstractObserver { 

  // Current game mode.
  AbstractGameMode * pCurrentGameMode_;

  // Map of game modes, by names
  std::map<std::string, AbstractGameMode *> gameModes_;
  
public:

  GameLoop() {
  }

  virtual ~GameLoop() {
  }

  /**
   * Register a game mode. The game loop starts observing any event 
   * provided by the game mode, and the mode becomes eligible for
   * being set with set_current_game_mode.
   */
  void register_game_mode(std::string iModeName, AbstractGameMode * ipGameMode);
  
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
  AbstractGameMode * get_current_game_mode() {
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
