#include <gmock/gmock.h>
#include "view_interface.hpp"

class ObserverInterface;

class MockView : public ViewInterface {
 public:
  MOCK_METHOD1(add_observer,
	       void(ObserverInterface *));

  MOCK_METHOD0(render_game,
      void());
};
