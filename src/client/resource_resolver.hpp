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

  /**
   * Check all prefixes provided by setPrefixes.
   * If one of the prefixes point to an 
   * existing folder, pPrefix_ is set to this 
   * value.
   *
   * @return true if any of the prefixes point to
   *    an existing folder.
   */
  bool checkPrefixes();

  /**
   * Get a safe prefix to look for files.
   * The first time it is called, it uses checkPrefixes
   * to get a valid prefix from the list supplied
   * to setPrefixes.
   *
   * @return the first prefix pointing to an existing folder
   * in the list supplied by setPrefixes, or "" if none
   * was found.
   */
  std::string getSafePrefix();

  // Clear the prefixes allocated in the prefixes_ vector.
  void clearPrefixes();

public:
  ResourceResolver(const AbstractFileChecker & iChecker) : pChecker_(&iChecker) {
    pPrefix_ = NULL;
  }
  ~ResourceResolver();

  void setPrefixes(const char* iPrefixes[], int iPrefixCount);

  /**
   * Gives the root folder containing locale files.
   * Under linux, this should be something like PREFIX/share/locale.
   * Under windows, this should be ../share/locale
   */
  std::string getLocaleDir();

  /**
   * Gives the expected position of an image.
   * 
   * Under linux, this should be under PREFIX/share/ube/images.
   * Under windows, this should be under ../share/ube/images.
   *
   * @param iImageName name of the image, with prefix (eg "foo.png")
   */
  std::string getImageFileName(const char * iImageName);

  // TODO : Same thing with 'standard lua scripts'

};

#endif //_RESOURCE_RESOLVER_HPP_
