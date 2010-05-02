/**
 * This is Free Software. See COPYING for information.
 */
#ifndef _IN_GAME_VIEW_HPP_
#define _IN_GAME_VIEW_HPP_

#include "mvc/view_interface.hpp"

#include "client/in_game_command_factory.hpp"
#include "client/in_game_command_stack.hpp"

class Puzzle;
class InGameModel;
class InGameRendererInterface;
class ControllerInterface;

/**
 * View for the main screen of the game.
 */
class InGameView :
  public ViewInterface
{ 

public:

  InGameView(InGameRendererInterface & dep_renderer, 
	     InGameModel & dep_model,
	     ControllerInterface & dep_controller) :
    ViewInterface(),
    dep_renderer_(dep_renderer),
    dep_model_(dep_model),
    dep_controller_(dep_controller),
    command_stack_(command_factory_),
    has_message_(false)
  {
  }

  ~InGameView() {
  }

  void render_game();

  void handle_event(int iEventCode);

  /**
   * Render the content of a puzzle to the screen.
   */
  void render_puzzle(const Puzzle & i_puzzle);
  
  void render_selected_cell(InGameModel & i_model);

  void update_goal(InGameModel & i_model);

  void render_path(InGameModel & i_model);

  void render_player(const Puzzle & i_puzzle);

  void render_overlays(const Puzzle & i_puzzle);

  void update_hovered_move(InGameModel & i_model);

private:

  // Dependencies
  InGameRendererInterface & dep_renderer_;
  InGameModel & dep_model_;
  ControllerInterface & dep_controller_;

  InGameCommandFactory command_factory_;
  InGameCommandStack command_stack_;

  bool has_message_;

  void handle_mouse_click();
  void check_cell_click(int mouse_x, int mouse_y);
  void check_move_click(int mouse_x, int mouse_y);
  void check_undo_click(int mouse_x, int mouse_y);
  void check_redo_click(int mouse_x, int mouse_y);
  void check_message_box_click(int mouse_x, int mouse_y);


};

#endif // _IN_GAME_VIEW_HPP_
