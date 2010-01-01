#ifndef _RESOURCE_RESOLVER_INTERFACE_HPP_
#define _RESOURCE_RESOLVER_INTERFACE_HPP_

#include <string>

/**
 * Interface to reach resources.
 */
class ResourceResolverInterface { 

public:

  virtual ~ResourceResolverInterface() {
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

#endif // _RESOURCE_RESOLVER_INTERFACE_HPP_
