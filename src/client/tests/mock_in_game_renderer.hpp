#include "in_game_renderer_interface.hpp"
#include <gmock/gmock.h>

class InGameModel;

class MockInGameRenderer : public InGameRendererInterface {
 public:
  MOCK_METHOD0(clear,
	       void());
  MOCK_METHOD3(render_cell,
      void(int i_i, int i_j, int i_cell_type));

  MOCK_METHOD0(flush,
	       void());

  MOCK_METHOD1(mouse_x_as_puzzle_column,
	       int(int i_x));
  MOCK_METHOD1(mouse_y_as_puzzle_line,
	       int(int i_y));

  MOCK_METHOD2(mouse_position_as_move_index,
	       int(int i_x, int i_y));

  MOCK_METHOD2(render_selected_cell,
	       void (int i_i, int i_j));

  MOCK_METHOD2(render_banned_cell,
	       void (int i_i, int i_j));

  MOCK_METHOD2(render_player,
	       void (int i_i, int i_j));

  MOCK_METHOD1(render_moves,
	       void (InGameModel & i_model));

  MOCK_METHOD2(render_ui, void(bool i_can_undo, bool i_can_redo));

  MOCK_METHOD2(is_on_undo_button,
	       bool (int i_x, int i_y));

  MOCK_METHOD2(is_on_redo_button,
	       bool (int i_x, int i_y));


};
