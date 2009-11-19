#include "stat_file_checker.hpp"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

namespace {
  class StatFileCheckerTest : public ::testing::Test {
  };

  TEST_F(StatFileCheckerTest, KnowsWhetherFolderExists){
    // Note : this should only work on a POSIX, unix-like system. 
    // That's enough for me, for the moment.
    StatFileChecker checker;
    EXPECT_TRUE(checker.is_folder_present("/usr"));
    EXPECT_TRUE(checker.is_folder_present("."));
    EXPECT_FALSE(checker.is_folder_present("foobar"));
  }

  TEST_F(StatFileCheckerTest, KnowsWhetherFileExists){
    // Again, this is a cheat, because I don't want to create file. 
    // So I just check that the executable exists. 
    // Change this if the executable name ever change...
    StatFileChecker checker;
    EXPECT_TRUE(checker.is_file_present("./engine-tests"));
    EXPECT_FALSE(checker.is_file_present("./foobar"));
  }

}
