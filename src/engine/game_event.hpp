/**
 * This is Free Software. See COPYING for information.
 */
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
  static const int PUZZLE_SELECTED = 4;
  static const int PUZZLE_FINISHED = 5;
  static const int NEXT_MOVE = 6;
  static const int CHAPTER_SELECTED = 7;
  static const int BACK_TO_CHAPTER_SELECTION = 8;
};

#endif // _GAME_EVENT_HPP_
