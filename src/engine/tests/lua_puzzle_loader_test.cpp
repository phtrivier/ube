#include "lua_puzzle_loader.hpp"
#include "cell.hpp"
#include "puzzle.hpp"
#include "cell_factory.hpp"
#include "lua_command.hpp"

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

  public:

    CellFactory f_;
    MockResourceResolver resolver_;
    LuaPuzzleLoader * p_loader_;

  protected:
    LuaPuzzleLoaderTest() {
    }

    virtual ~LuaPuzzleLoaderTest() {
    }

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }

    void load_puzzle_from_file(std::string i_file_name, Puzzle * o_p_puzzle) {
      EXPECT_CALL(resolver_, get_engine_lua_path()).
	WillOnce(Return(str(format("%1%/lua/?.lua") % SRCDIR)));

      EXPECT_CALL(resolver_, get_engine_lua_file_name(StrEq("puzzle_lib.lua")))
	.WillOnce(Return(str(format("%1%/lua/puzzle_lib.lua") % SRCDIR)));

      EXPECT_CALL(resolver_, get_puzzle_lua_file_name(StrEq(i_file_name)))
	.WillOnce(Return(str(format("%1%/tests/lua/%2%") % SRCDIR % i_file_name)));
    
      p_loader_ = new LuaPuzzleLoader(&f_,resolver_);
      p_loader_->load_puzzle_file(i_file_name.c_str(), o_p_puzzle);
    }

  };

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

  TEST_F(LuaPuzzleLoaderTest, ClearsMoveListWhenReloadingAPuzzle) {
    Puzzle p;
    load_puzzle_from_file("puzzle_loader_test/puzzle2.lua", &p);
    ASSERT_EQ(1, (int) p.moves().size());
    p.moves()[0].use();
    ASSERT_FALSE(p.moves()[0].available());
    load_puzzle_from_file("puzzle_loader_test/puzzle1.lua", &p);
    ASSERT_EQ(2, (int) p.moves().size());
    ASSERT_TRUE(p.moves()[0].available());
  }

  TEST_F(LuaPuzzleLoaderTest, LoadedPuzzlesCanBeCleared) {
    Puzzle p;
    load_puzzle_from_file("puzzle_loader_test/puzzle2.lua", &p);
    ASSERT_EQ(1, (int) p.moves().size());
    load_puzzle_from_file("puzzle_loader_test/puzzle1.lua", &p);
    ASSERT_EQ(2, (int) p.moves().size());
    p.clear();
    p.clear();
    load_puzzle_from_file("puzzle_loader_test/puzzle2.lua", &p);
    ASSERT_EQ(1, (int) p.moves().size());
  }

  TEST_F(LuaPuzzleLoaderTest, LoadsScriptInPuzzle) {
    Puzzle p;
    load_puzzle_from_file("puzzle_loader_test/puzzle_with_scripts.lua", &p);
    ASSERT_TRUE(p.has_script(0,2));
    LuaCommand * p_script1 = static_cast<LuaCommand*>(p.get_script_at(0,2));
    ASSERT_TRUE(p_script1 != NULL);
    ASSERT_EQ(1, p_script1->get_index());
    
    // Script at 0,1 should be the kind that adds a "SINGLE" move
    ASSERT_EQ(1, (int) p.moves().size());
    p.do_script_at(0,2);
    ASSERT_EQ(2, (int) p.moves().size());
    ASSERT_EQ(MoveType::DOUBLE, p.moves().at(1).type());
    p.undo_script_at(0,2);
    ASSERT_EQ(1, (int) p.moves().size());
    
  }

} // Namespace
