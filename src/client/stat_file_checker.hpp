#ifndef _STAT_FILE_CHECKER_HPP
#define _STAT_FILE_CHECKER_HPP

#include <abstract_file_checker.hpp>
#include <sys/stat.h>

class StatFileChecker : public AbstractFileChecker {
  bool hasStatMode(const std::string iPath, mode_t mode) const;
public:
  bool isFolderPresent(const std::string iPath) const;
  bool isFilePresent(const std::string iPath) const;
};

#endif //_STAT_FILE_CHECKER_HPP
