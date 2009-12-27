#include "prefix_resource_resolver.hpp"
#include "tests/mock_file_checker.hpp"

#include <string>
using namespace std;

#include <gtest/gtest.h>
#include <gmock/gmock.h>
using ::testing::Return;
using ::testing::StrEq;


namespace {
  class PrefixResourceResolverTest  : public ::testing::Test {
  public:
    MockFileChecker checker_;
    PrefixResourceResolver * pResolver_;
    PrefixResourceResolverTest() {
      pResolver_ = new PrefixResourceResolver(checker_);
    }
    virtual ~PrefixResourceResolverTest(){
      delete pResolver_;
    }

    virtual void SetUp() {
      const char* prefixes[3] = {"foo", "bar", "baz"};
      pResolver_->set_prefixes(prefixes,3);
    }

    void expectsThreeFolderCheck() {
      EXPECT_CALL(checker_, is_folder_present(StrEq("foo"))).WillOnce(Return(false));
      EXPECT_CALL(checker_, is_folder_present(StrEq("bar"))).WillOnce(Return(false));
      EXPECT_CALL(checker_, is_folder_present(StrEq("baz"))).WillOnce(Return(true));
    }

  };

  TEST_F(PrefixResourceResolverTest, UsesEachPrefixInTurnToLookForLocale) {
    expectsThreeFolderCheck();
    ASSERT_EQ("baz/share/locale",pResolver_->get_locale_dir());
    // There should be no check the second time
    ASSERT_EQ("baz/share/locale",pResolver_->get_locale_dir());
  }

  TEST_F(PrefixResourceResolverTest, UsesAllPrefixToLookForImages) {
    expectsThreeFolderCheck();
    ASSERT_EQ("baz/share/ube/images/toto.png",pResolver_->get_image_file_name("toto.png"));
    // No checks the second time
    ASSERT_EQ("baz/share/ube/images/toto.png",pResolver_->get_image_file_name("toto.png"));
  }

  TEST_F(PrefixResourceResolverTest, UsesAllPrefixToLookForFonts) {
    expectsThreeFolderCheck();
    ASSERT_EQ("baz/share/ube/fonts/Vera.ttf",pResolver_->get_font_file_name("Vera.ttf"));
    // No checks the second time
    ASSERT_EQ("baz/share/ube/fonts/Vera.ttf",pResolver_->get_font_file_name("Vera.ttf"));
  }

  TEST_F(PrefixResourceResolverTest, ChecksFoldersAsLittleAsPossible) {
    expectsThreeFolderCheck();
    ASSERT_EQ("baz/share/ube/images/toto.png",pResolver_->get_image_file_name("toto.png"));
    // Only one checks
    ASSERT_EQ("baz/share/ube/images/tata.png",pResolver_->get_image_file_name("tata.png"));
    ASSERT_EQ("baz/share/locale",pResolver_->get_locale_dir());
  }

  TEST_F(PrefixResourceResolverTest, UsesAllPrefixToLookForEngineLuaFiles) {
    expectsThreeFolderCheck();
    ASSERT_EQ("baz/share/ube/lua/engine/test.lua",pResolver_->get_engine_lua_file_name("test.lua"));
    // No checks the second time
    ASSERT_EQ("baz/share/ube/lua/engine/test.lua",pResolver_->get_engine_lua_file_name("test.lua"));
  }

  TEST_F(PrefixResourceResolverTest, UsesAllPrefixToLookForPuzzleLuaFiles) {
    expectsThreeFolderCheck();
    ASSERT_EQ("baz/share/ube/lua/puzzles/puzzle1.lua",pResolver_->get_puzzle_lua_file_name("puzzle1.lua"));
    // No checks the second time
    ASSERT_EQ("baz/share/ube/lua/puzzles/puzzle1.lua",pResolver_->get_puzzle_lua_file_name("puzzle1.lua"));
  }
  
}
