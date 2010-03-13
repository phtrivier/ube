#ifndef _GAME_EVENT_HPP_
#define _GAME_EVENT_HPP_


/**
 * Codes for game events
 */
class GameEvent { 

public:

  // User request to quit the game
  static const int QUIT = 0;
  static const int MOUSE_CLICKED = 1;
  static const int UNDO = 2;
  static const int REDO = 3;
    
};

#endif // _GAME_EVENT_HPP_
