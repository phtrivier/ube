#ifndef _MOCK_RESOURCE_RESOLVER_HPP_
#define _MOCK_RESOURCE_RESOLVER_HPP_

#include <gmock/gmock.h>
#include "common/resource_resolver_interface.hpp"

/**
 * Mock resource resolver
 */

class MockResourceResolver : public ResourceResolverInterface {
 public:
  MOCK_METHOD0(get_locale_dir,
      std::string());
  MOCK_METHOD1(get_image_file_name,
      std::string(const char * iImageName));
  MOCK_METHOD1(get_font_file_name,
      std::string(const char * iFontName));
  MOCK_METHOD0(get_engine_lua_path,
	       std::string());
  MOCK_METHOD1(get_engine_lua_file_name,
      std::string(const char *iFileName));
  MOCK_METHOD1(get_puzzle_lua_file_name,
      std::string(const char *iFileName));
  MOCK_METHOD1(get_music_file_name,
      std::string(const char *iFileName));
};

#endif // _MOCK_RESOURCE_RESOLVER_HPP_
