#ifndef _SILENT_LOGGER_HPP_
#define _SILENT_LOGGER_HPP_

#include <iostream>

#include "logger_interface.hpp"
#include "silent_ostream.hpp"

/**
 * A logger that outputs nothing (usefull for tests)
 */
class SilentLogger :
  public LoggerInterface,
  public SilentOstream
{ 

public:

  std::ostream * get_appender(LogLevel::Level i_level) const {
    return (std::ostream *) this;
  }
 
  void new_line() const {
  }

};

#endif // _SILENT_LOGGER_HPP_
