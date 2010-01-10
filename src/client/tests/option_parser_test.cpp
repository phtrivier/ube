#include "option_parser.hpp"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <stdexcept>
using namespace std;

#include "popt.h"

namespace {
  class OptionParserTest : public ::testing::Test {
  protected:
    OptionParserTest() {
    }

    virtual ~OptionParserTest() {
    }

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }

  };

  TEST_F(OptionParserTest, ReadsPuzzleFileName) {
    OptionParser parser;

    std::string prog_name = "foobar";
    std::string puzzle_set = "--puzzle=puzzle1.lua";

    const char * argv[] = { prog_name.c_str(), puzzle_set.c_str() };

    parser.parse_options(2, argv);
    ASSERT_EQ("puzzle1.lua", parser.get_puzzle_file_name());
  }

  TEST_F(OptionParserTest, ReadsPuzzleFileNameWithShortVersion) {
    OptionParser parser;

    std::string prog_name = "foobar";
    std::string puzzle_set = "-p";
    std::string puzzle_name = "puzzle1.lua";

    const char * argv[] = { prog_name.c_str(), 
			    puzzle_set.c_str(),
			    puzzle_name.c_str()};

    ASSERT_EQ(0, parser.parse_options(3, argv));
    ASSERT_TRUE(parser.has_puzzle_file_name());
    ASSERT_EQ("puzzle1.lua", parser.get_puzzle_file_name());
  }

  TEST_F(OptionParserTest, ScreemsOnBadOptions) {
    OptionParser parser;

    std::string prog_name = "foobar";
    std::string puzzle_set = "--prout";
    std::string puzzle_name = "puzzle1.lua";

    const char * argv[] = { prog_name.c_str(), 
			    puzzle_set.c_str(),
			    puzzle_name.c_str()};

    ASSERT_EQ(POPT_ERROR_BADOPT, parser.parse_options(3, argv));
  }


} // Namespace
