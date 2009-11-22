#include <gmock/gmock.h>
#include "abstract_observer.hpp"

class MockObserver : public AbstractObserver {
 public:
  MOCK_METHOD1(handle_event,void(int iEventCode));
};
