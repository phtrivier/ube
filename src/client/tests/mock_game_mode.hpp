#include <gmock/gmock.h>
#include "game_mode_interface.hpp"

class AbstractObserver;

class MockGameMode : public GameModeInterface {
public:
  
  // TODO(pht) : if possible, get rid of this, it should a
  MOCK_METHOD1(add_observer,
	       void(AbstractObserver *));

  MOCK_METHOD1(update_game,
	       void(int));
  MOCK_METHOD0(render_game,
	       void());
};
