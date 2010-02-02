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
   * The expected location of a font file
   * 
   * @param iFontName name of the font, with suffix (eg "Vera.ttf")
   */
  virtual std::string get_font_file_name(const char * iFontName) = 0;

  /**
   * The lua path to load engine lua files.
   *
   * This can be used to replace 'package.path" in lua scripts to allow require.
   *
   * Should be something like "foo/bar/whatever/engine/lua/?.lua
   */
  virtual std::string get_engine_lua_path() = 0;

  /**
   * The expected location of an engine Lua file
   * 
   * @param iFileName name of the file, with suffix (eg "story_lib.lua")
   */
  virtual std::string get_engine_lua_file_name(const char *iFileName) = 0;

  /**
   * The expected location of a puzzle Lua file
   * 
   * @param iFiletName name of the file, with suffix (eg "puzzle.lua")
   */
  virtual std::string get_puzzle_lua_file_name(const char *iFileName) = 0;

  /**
   * The expected location of a music file
   *
   * @param  iMusicName name of the file, with suffix (eg "music.ogg")
   */
  virtual std::string get_music_file_name(const char *iMusicName) = 0;

};

#endif // _RESOURCE_RESOLVER_INTERFACE_HPP_
