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

  void load_puzzle_from_file(std::string i_file_name, Puzzle * o_p_puzzle) {
    CellFactory f;

    MockResourceResolver resolver;

    EXPECT_CALL(resolver, get_engine_lua_path()).
      WillOnce(Return(str(format("%1%/lua/?.lua") % SRCDIR)));

    EXPECT_CALL(resolver, get_engine_lua_file_name(StrEq("puzzle_lib.lua")))
      .WillOnce(Return(str(format("%1%/lua/puzzle_lib.lua") % SRCDIR)));

    EXPECT_CALL(resolver, get_puzzle_lua_file_name(StrEq(i_file_name)))
      .WillOnce(Return(str(format("%1%/tests/lua/%2%") % SRCDIR % i_file_name)));
    
    LuaPuzzleLoader loader(&f,resolver);
    loader.load_puzzle_file(i_file_name.c_str(), o_p_puzzle);

  }


  TEST_F(LuaPuzzleLoaderTest, CanLoadPuzzleFile) {

    Puzzle p;

    load_puzzle_from_file("puzzle_loader_test/puzzle1.lua", &p);

    ASSERT_EQ(3, p.get_w());
    ASSERT_EQ(4, p.get_h());

    ASSERT_TRUE(p.get_cell_at(2,0)->is_in());
    ASSERT_TRUE(p.get_cell_at(1,2)->is_out());
    ASSERT_TRUE(p.get_cell_at(0,0)->is_empty());
    ASSERT_TRUE(p.get_cell_at(2,1)->is_walkable());

    ASSERT_EQ(2, (int) p.moves().size());
    ASSERT_EQ(MoveType::DOUBLE, p.moves().at(0).type());
    ASSERT_TRUE(p.moves().at(0).available());
  }

			     
  TEST_F(LuaPuzzleLoaderTest, LoadsPuzzleWithBorders) {

    Puzzle p;

    load_puzzle_from_file("puzzle_loader_test/puzzle2.lua", &p);

    ASSERT_EQ(3, p.get_w());
    ASSERT_EQ(4, p.get_h());

    ASSERT_TRUE(p.get_cell_at(1,2)->is_in());
    ASSERT_TRUE(p.get_cell_at(2,0)->is_out());
    ASSERT_TRUE(p.get_cell_at(0,0)->is_empty());
    ASSERT_TRUE(p.get_cell_at(1,0)->is_walkable());

    ASSERT_EQ(1, (int) p.moves().size());
    ASSERT_EQ(MoveType::SINGLE, p.moves().at(0).type());
    ASSERT_TRUE(p.moves().at(0).available());
    
  }


} // Namespace
