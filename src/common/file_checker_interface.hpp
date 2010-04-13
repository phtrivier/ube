/**
 * This is Free Software. See COPYING for information.
 */
#ifndef _FILE_CHECKER_INTERFACE_HPP_
#define _FILE_CHECKER_INTERFACE_HPP_

#include <string>

class FileCheckerInterface {
public:

  virtual ~FileCheckerInterface() {
  }

  /**
   * Does a folder exists ? 
   *
   * @param iPath : absolute path to a folder.
   * @returns true if the path points to an existing folder.
   */
  virtual bool is_folder_present(const std::string iPath) const = 0;

  /**
   * Does a file exists ? 
   *
   * @param iPath : absolute path to a file.
   * @returns true if the path points to an existing file.
   */
  virtual bool is_file_present(const std::string iPath) const = 0;
  
};

#endif // _FILE_CHECKER_INTERFACE_HPP_