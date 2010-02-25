#include "in_game_renderer_interface.hpp"
#include <gmock/gmock.h>

#include <vector>

class Move;

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
  MOCK_METHOD2(render_selected_cell,
	       void (int i_i, int i_j));
  MOCK_METHOD2(render_player,
	       void (int i_i, int i_j));
  MOCK_METHOD1(render_moves,
	       void (std::vector<Move> & i_moves));

};
