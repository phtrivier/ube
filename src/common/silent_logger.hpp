#ifndef _SILENT_LOGGER_HPP_
#define _SILENT_LOGGER_HPP_

#include <iostream>

#include "logger_interface.hpp"

/**
 * A logger that outputs nothing (usefull for tests)
 */
class SilentLogger :
  public LoggerInterface
{ 

public:

  SilentLogger() {
  }

  ~SilentLogger() {
  }

  void debug(std::string i_msg) const {
  }
  
  void log(std::string i_msg) const {
  }
  
  void error(std::string i_msg) const {
  }
  
};

#endif // _SILENT_LOGGER_HPP_
