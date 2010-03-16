#include <gmock/gmock.h>
#include "client/puzzle_selection_renderer_interface.hpp"

#include <string>

class MockPuzzleSelectionRenderer : public PuzzleSelectionRendererInterface {

public:

  MOCK_METHOD2(render_puzzle_name,
	       void(std::string & i_name, int i_index));

  MOCK_METHOD2(get_mouse_position_as_puzzle_index,
	       int(int i_x, int i_y));

  MOCK_METHOD0(flush, void());
  MOCK_METHOD0(clear, void());

};
