#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "common/logging.hpp"

int main(int argc, char **argv) {

  Logging::disable_logging();

  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}
