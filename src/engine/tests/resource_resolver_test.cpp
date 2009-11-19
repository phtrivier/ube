#include <resource_resolver.hpp>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
using ::testing::Return;
using ::testing::StrEq;

#include "tests/mock_file_checker.hpp"
#include <string>
using namespace std;

namespace {
  class ResourceResolverTest  : public ::testing::Test {
  public:
    MockFileChecker checker_;
    ResourceResolver * pResolver_;
    ResourceResolverTest() {
      pResolver_ = new ResourceResolver(checker_);
    }
    virtual ~ResourceResolverTest(){
      delete pResolver_;
    }

    virtual void SetUp() {
      EXPECT_CALL(checker_, is_folder_present(StrEq("foo"))).WillOnce(Return(false));
      EXPECT_CALL(checker_, is_folder_present(StrEq("bar"))).WillOnce(Return(false));
      EXPECT_CALL(checker_, is_folder_present(StrEq("baz"))).WillOnce(Return(true));

      const char* prefixes[3] = {"foo", "bar", "baz"};
      pResolver_->set_prefixes(prefixes,3);
    }

  };

  TEST_F(ResourceResolverTest, UsesEachPrefixInTurnToLookForLocale) {
    ASSERT_EQ("baz/share/locale",pResolver_->get_locale_dir());
    // There should be no check the second time
    ASSERT_EQ("baz/share/locale",pResolver_->get_locale_dir());
  }

  TEST_F(ResourceResolverTest, UsesAllPrefixToLookForImages) {
    ASSERT_EQ("baz/share/ube/images/toto.png",pResolver_->get_image_file_name("toto.png"));
    // No checks the second time
    ASSERT_EQ("baz/share/ube/images/toto.png",pResolver_->get_image_file_name("toto.png"));
  }

  TEST_F(ResourceResolverTest, UsesAllPrefixToLookForFonts) {
    ASSERT_EQ("baz/share/ube/fonts/Vera.ttf",pResolver_->get_font_file_name("Vera.ttf"));
    // No checks the second time
    ASSERT_EQ("baz/share/ube/fonts/Vera.ttf",pResolver_->get_font_file_name("Vera.ttf"));
  }

  TEST_F(ResourceResolverTest, ChecksFoldersAsLittleAsPossible) {
    ASSERT_EQ("baz/share/ube/images/toto.png",pResolver_->get_image_file_name("toto.png"));
    // Only one checks
    ASSERT_EQ("baz/share/ube/images/tata.png",pResolver_->get_image_file_name("tata.png"));
    ASSERT_EQ("baz/share/locale",pResolver_->get_locale_dir());
  }

  TEST_F(ResourceResolverTest, UsesAllPrefixToLookForLuaFiles) {
    ASSERT_EQ("baz/share/ube/lua/test.lua",pResolver_->get_engine_lua_file_name("test.lua"));
    // No checks the second time
    ASSERT_EQ("baz/share/ube/lua/test.lua",pResolver_->get_engine_lua_file_name("test.lua"));
  }

}
