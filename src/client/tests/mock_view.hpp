#include <gmock/gmock.h>
#include "abstract_view.hpp"

class AbstractObserver;

class MockView : public AbstractView {
 public:
  MOCK_METHOD1(add_observer,
	       void(AbstractObserver *));

  MOCK_METHOD0(render_game,
      void());
};
