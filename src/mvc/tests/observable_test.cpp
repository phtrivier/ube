#include "mvc/tests/mock_observer.hpp"

#include "mvc/observable.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <stdexcept>
using namespace std;

namespace {
  class ObservableTest : public ::testing::Test {
  protected:
    ObservableTest() {
    }

    virtual ~ObservableTest() {
    }

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }

  };

  TEST_F(ObservableTest, NotifiesAllObserversOfEvent) {
    Observable o;
    MockObserver mo1;
    MockObserver mo2;

    o.add_observer(&mo1);
    o.add_observer(&mo2);

    EXPECT_CALL(mo1, handle_event(12));
    EXPECT_CALL(mo2, handle_event(12));

    o.fire_event(12);

  }

} // Namespace
