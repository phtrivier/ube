#include <gtest/gtest.h>
#include <gmock/gmock.h>

// For some very starnge reason, although client_tests is complied exactly like ube.cpp, it cannot get linked to 
// logging.o, which normally contains the definition of 
// Logging::ps_logger ... So I don't really get why I have to do this !!

int main(int argc, char **argv) {
  // ::testing::InitGoogleTest(&argc, argv);
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}
