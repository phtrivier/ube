#ifndef _ABSTRACT_FILE_CHECKER_HPP_
#define _ABSTRACT_FILE_CHECKER_HPP_

#include <string>

class AbstractFileChecker {
public:

  virtual ~AbstractFileChecker() {
  }

  /**
   * Does a folder exists ? 
   *
   * @param iPath : absolute path to a folder.
   * @returns true if the path points to an existing folder.
   */
  virtual bool isFolderPresent(const std::string iPath) const = 0;

  /**
   * Does a file exists ? 
   *
   * @param iPath : absolute path to a file.
   * @returns true if the path points to an existing file.
   */
  virtual bool isFilePresent(const std::string iPath) const = 0;
  
};

#endif // _ABSTRACT_FILE_CHECKER_HPP_
