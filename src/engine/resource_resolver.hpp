#ifndef _RESOURCE_RESOLVER_HPP_
#define _RESOURCE_RESOLVER_HPP_

// #include <stdio.h>
// #include <string.h>
#include <string>
#include <vector>

class AbstractFileChecker;

class ResourceResolver {
  // External dependency, to check for folder / file existence
  const AbstractFileChecker * pChecker_;

  // List of copies of prefixes set by the user
  std::vector<const std::string *> prefixes_;

  // Known prefix that worked to find a resource.
  // Once this is set, no further check is
  // ever done.
  const std::string * pPrefix_;

  // In test scenarios, lua files are in a completely different location.
  // If this flag is on, get_engine_lua_file_name will point to SRCDIR/engine/lua instead
  // of using the prefixes.
  bool test_mode_;

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
  std::string getResFileName(const char *iResType, const char * iResName);

public:
  ResourceResolver(const AbstractFileChecker & iChecker) : pChecker_(&iChecker) {
    pPrefix_ = NULL;
    test_mode_ = false;
  }
  ~ResourceResolver();

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
   * Under linux, this should be under PREFIX/share/ube/lua.
   * Under windows, this should be under ../share/ube/lua.
   *
   * @param iFontName name of the font, with suffix (eg "story_lib.lua")
   */
  std::string get_engine_lua_file_name(const char *iFileName);

  /**
   * Make this resource_resolver look for lua files in SRCDIR/engine/lua
   * instead of using the prefixes.
   */
  void set_test_mode(bool iMode) {
    test_mode_ = iMode;
  }

};

#endif //_RESOURCE_RESOLVER_HPP_
