/**
 * This is Free Software. See COPYING for information.
 */
#include <stat_file_checker.hpp>

#include <sys/types.h>
#include <sys/stat.h>

#include <string>

bool
StatFileChecker::is_folder_present(const std::string iPath) const
{
  return has_stat_mode(iPath, S_IFDIR);
}

bool
StatFileChecker::is_file_present(const std::string iPath) const
{
  return has_stat_mode(iPath, S_IFREG);
}

bool
StatFileChecker::has_stat_mode(const std::string iPath, mode_t mode) const {
  bool res = false;
  struct stat status;
  int statRes = stat(iPath.c_str(),&status);
  if (statRes == 0 ) {
    res = status.st_mode & mode;
  }
  return res;
}