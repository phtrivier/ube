#include "lua_path_finder.hpp"
#include "cell.hpp"
#include "puzzle.hpp"
#include "move.hpp"

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
  class LuaPathFinderTest : public ::testing::Test {
  protected:
    LuaPathFinderTest() {
    }

    virtual ~LuaPathFinderTest() {
    }

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }

  };

  TEST_F(LuaPathFinderTest, FindsTrivialPathInShortPuzzle) {
    
    Puzzle p;
    p.set_dimensions(2,1);
    Cell c1(0,0,Cell::WALKABLE);
    Cell c2(0,1,Cell::WALKABLE);
    p.add_cell(&c1);
    p.add_cell(&c2);

    ASSERT_FALSE(p.get_cell_at(0,0)->is_in_path());
    ASSERT_FALSE(p.get_cell_at(0,1)->is_in_path());

    MockResourceResolver resolver;

    EXPECT_CALL(resolver, get_engine_lua_path()).
      WillOnce(Return(str(format("%1%/lua/?.lua") % SRCDIR)));

    EXPECT_CALL(resolver, get_engine_lua_file_name(StrEq("path_finder_lib.lua")))
      .WillOnce(Return(str(format("%1%/lua/path_finder_lib.lua") % SRCDIR)));

    LuaPathFinder finder(resolver);

    ASSERT_EQ(1, finder.find_path(p, 0, 0, 0, 1, MoveType::SINGLE));

    ASSERT_TRUE(p.get_cell_at(0,0)->is_in_path());
    ASSERT_TRUE(p.get_cell_at(0,1)->is_in_path());

  }

  TEST_F(LuaPathFinderTest, FindsTrivialPathInBiggerPuzzle) {

    Puzzle p;
    int w = 9;
    int h = 9;
    p.set_dimensions(w,h);

    for (int i = 0 ; i < h ; i++) {
      for (int j = 0 ; j < w ; j++) {
	Cell * c = new Cell(i,j, Cell::WALKABLE);
	p.add_cell(c);
      }
    }
      
    MockResourceResolver resolver;

    EXPECT_CALL(resolver, get_engine_lua_path()).
      WillOnce(Return(str(format("%1%/lua/?.lua") % SRCDIR)));

    EXPECT_CALL(resolver, get_engine_lua_file_name(StrEq("path_finder_lib.lua")))
      .WillOnce(Return(str(format("%1%/lua/path_finder_lib.lua") % SRCDIR)));

    LuaPathFinder finder(resolver);

    ASSERT_EQ(0, finder.find_path(p, 5, 1, (w-1), (h-1), MoveType::DOUBLE));
    ASSERT_EQ(1, finder.find_path(p, 5, 1, 5, 7, MoveType::DOUBLE));

  }

  TEST_F(LuaPathFinderTest, CanReachBordersOfPuzzle) {

    Puzzle p;
    p.set_dimensions(3,2);
    Cell c1(0,0,Cell::WALKABLE);
    Cell c2(0,1,Cell::WALKABLE);
    Cell c3(0,2,Cell::IN);
    Cell c4(1,0,Cell::OUT);
    Cell c5(1,1,Cell::WALKABLE);
    Cell c6(1,2,Cell::WALKABLE);

    p.add_cell(&c1);
    p.add_cell(&c2);
    p.add_cell(&c3);
    p.add_cell(&c4);
    p.add_cell(&c5);
    p.add_cell(&c6);

    MockResourceResolver resolver;

    EXPECT_CALL(resolver, get_engine_lua_path()).
      WillOnce(Return(str(format("%1%/lua/?.lua") % SRCDIR)));

    EXPECT_CALL(resolver, get_engine_lua_file_name(StrEq("path_finder_lib.lua")))
      .WillOnce(Return(str(format("%1%/lua/path_finder_lib.lua") % SRCDIR)));

    LuaPathFinder finder(resolver);

    ASSERT_EQ(1, finder.find_path(p, 0, 2, 1, 0, MoveType::SINGLE));
    
  }

  

} // Namespace
