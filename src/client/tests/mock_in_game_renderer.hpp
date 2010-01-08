#include "in_game_renderer_interface.hpp"
#include <gmock/gmock.h>

class MockInGameRenderer : public InGameRendererInterface {
 public:
  MOCK_METHOD0(clear,
	       void());
  MOCK_METHOD3(render_cell,
      void(int i_i, int i_j, int i_cell_type));
  MOCK_METHOD0(flush,
	       void());
};
