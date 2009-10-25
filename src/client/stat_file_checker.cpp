#include <stat_file_checker.hpp>

#include <sys/types.h>
#include <sys/stat.h>

#include <string>

bool
StatFileChecker::isFolderPresent(const std::string iPath) const
{
  return hasStatMode(iPath, S_IFDIR);
}

bool
StatFileChecker::isFilePresent(const std::string iPath) const
{
  return hasStatMode(iPath, S_IFREG);
}

bool
StatFileChecker::hasStatMode(const std::string iPath, mode_t mode) const {
  bool res = false;
  struct stat status;
  int statRes = stat(iPath.c_str(),&status);
  if (statRes == 0 ) {
    res = status.st_mode & mode;
  }
  return res;
}

