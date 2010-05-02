/**
 * This is Free Software. See COPYING for information.
 */
#include "in_game_model_loader.hpp"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <stdexcept>
using namespace std;

#include "common/tests/mock_resource_resolver.hpp"
#include "common/stat_file_checker.hpp"

#include "engine/cell.hpp"
#include "engine/tests/mock_path_finder.hpp"

#include "client/in_game_model.hpp"

using ::testing::Return;
using ::testing::StrEq;

#include "boost/format.hpp"
using boost::format;


namespace {
  class InGameModelLoaderTest : public ::testing::Test {

  public:

    MockResourceResolver resolver_;
    InGameModelLoader * p_loader_;

  protected:
    InGameModelLoaderTest() {
    }

    virtual ~InGameModelLoaderTest() {
    }

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }

    void load_puzzle_from_file(std::string i_file_name, InGameModel & o_model) {
      EXPECT_CALL(resolver_, get_engine_lua_path()).
	WillOnce(Return(str(format("%1%/../engine/lua/?.lua") % SRCDIR)));

      EXPECT_CALL(resolver_, get_engine_lua_file_name(StrEq("puzzle_lib.lua")))
	.WillOnce(Return(str(format("%1%/../engine/lua/puzzle_lib.lua") % SRCDIR)));

      EXPECT_CALL(resolver_, get_puzzle_lua_file_name(StrEq(i_file_name)))
	.WillOnce(Return(str(format("%1%/tests/lua/%2%") % SRCDIR % i_file_name)));
    
      p_loader_ = new InGameModelLoader(resolver_);
      p_loader_->load_puzzle_file(i_file_name.c_str(), o_model);
    }


  };

  TEST_F(InGameModelLoaderTest, LoadsPuzzleFromFile) {
    MockPathFinder pf;
    InGameModel model(pf);
    load_puzzle_from_file("model_loader_test/puzzle1.lua", model);
    
    ASSERT_EQ(3, model.get_puzzle().get_w());
    ASSERT_EQ(4, model.get_puzzle().get_h());

    ASSERT_TRUE(model.get_puzzle().get_cell_at(2,0)->is_in());
    ASSERT_TRUE(model.get_puzzle().get_cell_at(1,2)->is_out());
    ASSERT_TRUE(model.get_puzzle().get_cell_at(0,0)->is_empty());
    ASSERT_TRUE(model.get_puzzle().get_cell_at(2,1)->is_walkable());

    ASSERT_EQ(2, (int) model.get_puzzle().moves().size());
    ASSERT_EQ(MoveType::DOUBLE, model.get_puzzle().moves().at(0).type());
    ASSERT_TRUE(model.get_puzzle().moves().at(0).available());
  }

  TEST_F(InGameModelLoaderTest, CanTriggerMessages) {
    MockPathFinder pf;
    InGameModel model(pf);
    ASSERT_TRUE(model.get_message().empty());
    load_puzzle_from_file("model_loader_test/puzzle_with_messages.lua", model);
    ASSERT_EQ("Hello !", model.get_message());
    model.set_message("");
    ASSERT_TRUE(model.get_message().empty());
  }



} // Namespace
