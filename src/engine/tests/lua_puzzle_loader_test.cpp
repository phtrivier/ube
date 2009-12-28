#include "lua_puzzle_loader.hpp"
#include "cell.hpp"
#include "puzzle.hpp"
#include "cell_factory.hpp"

#include "common/tests/mock_resource_resolver.hpp"
#include "common/stat_file_checker.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>
using ::testing::Return;
using ::testing::StrEq;

#include "boost/format.hpp"
using boost::format;

#include <stdexcept>
using namespace std;



namespace {
  class LuaPuzzleLoaderTest : public ::testing::Test {
  protected:
    LuaPuzzleLoaderTest() {
    }

    virtual ~LuaPuzzleLoaderTest() {
    }

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }

  };

  TEST_F(LuaPuzzleLoaderTest, CanLoadPuzzleFile) {

    CellFactory f;

    MockResourceResolver resolver;
    EXPECT_CALL(resolver, get_engine_lua_file_name(StrEq("puzzle_lib.lua")))
      .WillOnce(Return(str(format("%1%/lua/puzzle_lib.lua") % SRCDIR)));

    EXPECT_CALL(resolver, get_puzzle_lua_file_name(StrEq("puzzle_loader_test/puzzle1.lua")))
      .WillOnce(Return(str(format("%1%/tests/lua/puzzle_loader_test/puzzle1.lua") % SRCDIR)));
    
    LuaPuzzleLoader loader(&f,&resolver);
    Puzzle p;
    loader.load_puzzle_file("puzzle_loader_test/puzzle1.lua", &p);
    
    ASSERT_EQ(3, p.get_w());
    ASSERT_EQ(4, p.get_h());

    ASSERT_TRUE(p.get_cell_at(2,0)->is_in());
    ASSERT_TRUE(p.get_cell_at(1,2)->is_out());
    ASSERT_TRUE(p.get_cell_at(0,0)->is_empty());
    ASSERT_TRUE(p.get_cell_at(2,1)->is_walkable());
    
  }

} // Namespace
