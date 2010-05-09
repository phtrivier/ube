#include <gmock/gmock.h>
#include "client/selection_renderer_interface.hpp"

#include <string>

class MockPuzzleSelectionRenderer : public PuzzleSelectionRendererInterface {

public:

  MOCK_METHOD2(render_item_name,
	       void(std::string & i_name, int i_index));

  MOCK_METHOD2(get_mouse_position_as_item_index,
	       int(int i_x, int i_y));

  MOCK_METHOD0(flush, void());
  MOCK_METHOD0(clear, void());

  MOCK_METHOD1(highlight_item_name, 
	       void(int i_index));

  MOCK_METHOD2(is_on_back_button,
	       bool(int, int));

};
