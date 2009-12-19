#ifndef _STAT_FILE_CHECKER_HPP
#define _STAT_FILE_CHECKER_HPP

#include "abstract_file_checker.hpp"
#include <sys/stat.h>

class StatFileChecker : public AbstractFileChecker {
  bool has_stat_mode(const std::string iPath, mode_t mode) const;
public:
  bool is_folder_present(const std::string iPath) const;
  bool is_file_present(const std::string iPath) const;
};

#endif //_STAT_FILE_CHECKER_HPP
