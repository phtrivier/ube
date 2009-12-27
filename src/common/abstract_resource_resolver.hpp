#ifndef _ABSTRACT_RESOURCE_RESOLVER_HPP_
#define _ABSTRACT_RESOURCE_RESOLVER_HPP_

#include <string>

/**
 * Interface to reach resources.
 */
class AbstractResourceResolver { 

public:

  AbstractResourceResolver() {
  }

  virtual ~AbstractResourceResolver() {
  }

  /**
   * Gives the root folder containing locale files.
   */
  virtual std::string get_locale_dir() = 0;

  /**
   * Gives the expected location of an image file.
   * 
   * @param iImageName name of the image, with suffix (eg "foo.png")
   */
  virtual std::string get_image_file_name(const char * iImageName) = 0;

  /**
   * Gives the expected location of a font file
   * 
   * @param iFontName name of the font, with suffix (eg "Vera.ttf")
   */
  virtual std::string get_font_file_name(const char * iFontName) = 0;

  /**
   * Gives the expected location of an engine Lua file
   * 
   * @param iFontName name of the file, with suffix (eg "story_lib.lua")
   */
  virtual std::string get_engine_lua_file_name(const char *iFileName) = 0;

  /**
   * Gives the expected location of a puzzle Lua file
   * 
   * @param iFontName name of the file, with suffix (eg "puzzle.lua")
   */
  virtual std::string get_puzzle_lua_file_name(const char *iFileName) = 0;

};

#endif // _ABSTRACT_RESOURCE_RESOLVER_HPP_
