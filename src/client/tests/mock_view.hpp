#include <gmock/gmock.h>
#include "abstract_view.hpp"

class MockView : public AbstractView {
 public:
  MOCK_METHOD0(render_game,
      void());
};
