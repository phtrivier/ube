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
  };

  TEST_F(ResourceResolverTest, UsesEachPrefixInTurnToLookForLocale) {
    EXPECT_CALL(checker_, isFolderPresent(StrEq("foo"))).WillOnce(Return(false));
    EXPECT_CALL(checker_, isFolderPresent(StrEq("bar"))).WillOnce(Return(false));
    EXPECT_CALL(checker_, isFolderPresent(StrEq("baz"))).WillOnce(Return(true));

    const char* prefixes[3] = {"foo", "bar", "baz"};
    pResolver_->setPrefixes(prefixes,3);

    ASSERT_EQ("baz/share/locale",pResolver_->getLocaleDir());
    // There should be no check the second time
    ASSERT_EQ("baz/share/locale",pResolver_->getLocaleDir());
  }

  TEST_F(ResourceResolverTest, UsesAllPrefixToLookForImages) {
    EXPECT_CALL(checker_, isFolderPresent(StrEq("foo"))).WillOnce(Return(false));
    EXPECT_CALL(checker_, isFolderPresent(StrEq("bar"))).WillOnce(Return(false));
    EXPECT_CALL(checker_, isFolderPresent(StrEq("baz"))).WillOnce(Return(true));

    const char* prefixes[3] = {"foo", "bar", "baz"};
    pResolver_->setPrefixes(prefixes,3);
    
    ASSERT_EQ("baz/share/ube/images/toto.png",pResolver_->getImageFileName("toto.png"));
    // No checks the second time
    ASSERT_EQ("baz/share/ube/images/toto.png",pResolver_->getImageFileName("toto.png"));
  }

  TEST_F(ResourceResolverTest, UsesAllPrefixToLookForFonts) {
    EXPECT_CALL(checker_, isFolderPresent(StrEq("foo"))).WillOnce(Return(false));
    EXPECT_CALL(checker_, isFolderPresent(StrEq("bar"))).WillOnce(Return(false));
    EXPECT_CALL(checker_, isFolderPresent(StrEq("baz"))).WillOnce(Return(true));

    const char* prefixes[3] = {"foo", "bar", "baz"};
    pResolver_->setPrefixes(prefixes,3);
    
    ASSERT_EQ("baz/share/ube/fonts/Vera.ttf",pResolver_->getFontFileName("Vera.ttf"));
    // No checks the second time
    ASSERT_EQ("baz/share/ube/fonts/Vera.ttf",pResolver_->getFontFileName("Vera.ttf"));
  }

  TEST_F(ResourceResolverTest, ChecksFoldersAsLittleAsPossible) {
    EXPECT_CALL(checker_, isFolderPresent(StrEq("foo"))).WillOnce(Return(false));
    EXPECT_CALL(checker_, isFolderPresent(StrEq("bar"))).WillOnce(Return(false));
    EXPECT_CALL(checker_, isFolderPresent(StrEq("baz"))).WillOnce(Return(true));

    const char* prefixes[3] = {"foo", "bar", "baz"};
    pResolver_->setPrefixes(prefixes,3);

    ASSERT_EQ("baz/share/ube/images/toto.png",pResolver_->getImageFileName("toto.png"));
    // Only one checks
    ASSERT_EQ("baz/share/ube/images/tata.png",pResolver_->getImageFileName("tata.png"));
    ASSERT_EQ("baz/share/locale",pResolver_->getLocaleDir());
  }

  TEST_F(ResourceResolverTest, ReCheckFolderIfPrefixesAreSetAgain) {
    EXPECT_CALL(checker_, isFolderPresent(StrEq("foo"))).WillOnce(Return(false));
    EXPECT_CALL(checker_, isFolderPresent(StrEq("bar"))).WillOnce(Return(true));

    const char* prefixes[2] = {"foo", "bar"};
    pResolver_->setPrefixes(prefixes,2);

    ASSERT_EQ("bar/share/locale",pResolver_->getLocaleDir());
    ASSERT_EQ("bar/share/ube/images/tata.png",pResolver_->getImageFileName("tata.png"));

    const char * newPrefixes[1] = {"baz"};
    pResolver_->setPrefixes(newPrefixes,1);
    
    EXPECT_CALL(checker_, isFolderPresent(StrEq("baz"))).WillOnce(Return(true));
    
    ASSERT_EQ("baz/share/locale",pResolver_->getLocaleDir());
    ASSERT_EQ("baz/share/ube/images/tata.png",pResolver_->getImageFileName("tata.png"));
    
  }

  TEST_F(ResourceResolverTest, AppendsNoPrefixWhenNoneMatched) {
    ASSERT_EQ("share/locale", pResolver_->getLocaleDir());
    const char* prefixes[1] = {"baz"};
    pResolver_->setPrefixes(prefixes,1);

    // As long as you don't set prefixes to something that work, we will check.
    EXPECT_CALL(checker_, isFolderPresent(StrEq("baz"))).WillRepeatedly(Return(false));

    ASSERT_EQ("share/locale", pResolver_->getLocaleDir());
    ASSERT_EQ("share/locale", pResolver_->getLocaleDir());
  }

}
