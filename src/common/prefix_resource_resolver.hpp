#ifndef _PREFIX_RESOURCE_RESOLVER_HPP_
#define _PREFIX_RESOURCE_RESOLVER_HPP_

#include "resource_resolver_interface.hpp"

#include <string>
#include <vector>

class FileCheckerInterface;

class PrefixResourceResolver :  public ResourceResolverInterface {
  // External dependency, to check for folder / file existence
  const FileCheckerInterface * pChecker_;

  // List of copies of prefixes set by the user
  std::vector<const std::string *> prefixes_;

  // Known prefix that worked to find a resource.
  // Once this is set, no further check is
  // ever done.
  const std::string * pPrefix_;

  /**
   * Check all prefixes provided by set_prefixes.
   * If one of the prefixes point to an 
   * existing folder, pPrefix_ is set to this 
   * value.
   *
   * @return true if any of the prefixes point to
   *    an existing folder.
   */
  bool check_prefixes();

  /**
   * Get a safe prefix to look for files.
   * The first time it is called, it uses check_prefixes
   * to get a valid prefix from the list supplied
   * to set_prefixes.
   *
   * @return the first prefix pointing to an existing folder
   * in the list supplied by set_prefixes, or "" if none
   * was found.
   */
  std::string get_safe_prefix();

  // Clear the prefixes allocated in the prefixes_ vector.
  void clearPrefixes();

  // Utility functions to look for a kind of resource
  std::string get_res_file_name(const char *iResType, const char * iResName);

public:
  PrefixResourceResolver(const FileCheckerInterface & iChecker) : ResourceResolverInterface(), pChecker_(&iChecker)  {
    pPrefix_ = NULL;
  }
  ~PrefixResourceResolver();

  void set_prefixes(const char* iPrefixes[], int iPrefixCount);

  /**
   * Gives the root folder containing locale files.
   * Under linux, this should be something like PREFIX/share/locale.
   * Under windows, this should be ../share/locale
   */
  std::string get_locale_dir();

  /**
   * Gives the expected location of an image file.
   * 
   * Under linux, this should be under PREFIX/share/ube/images.
   * Under windows, this should be under ../share/ube/images.
   *
   * @param iImageName name of the image, with suffix (eg "foo.png")
   */
  std::string get_image_file_name(const char * iImageName);

  /**
   * Gives the expected location of a font file
   * 
   * Under linux, this should be under PREFIX/share/ube/fonts.
   * Under windows, this should be under ../share/ube/fonts.
   *
   * @param iFontName name of the font, with suffix (eg "Vera.ttf")
   */
  std::string get_font_file_name(const char * iFontName);

  /**
   * Gives the expected location of an engine Lua file
   * 
   * Under linux, this should be under PREFIX/share/ube/lua/engine.
   * Under windows, this should be under ../share/ube/lua/engine.
   *
   * @param iFontName name of the file, with suffix (eg "story_lib.lua")
   */
  std::string get_engine_lua_file_name(const char *iFileName);

  /**
   * Gives the expected location of a puzzle Lua file
   * 
   * Under linux, this should be under PREFIX/share/ube/lua/puzzles.
   * Under windows, this should be under ../share/ube/lua/puzzles.
   *
   * @param iFontName name of the file, with suffix (eg "puzzle.lua")
   */
  std::string get_puzzle_lua_file_name(const char *iFileName);
  
};

#endif //_PREFIX_RESOURCE_RESOLVER_HPP_
