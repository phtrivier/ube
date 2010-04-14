/**
 * This is Free Software. See COPYING for information.
 */
#ifndef _LOGGER_HPP_
#define _LOGGER_HPP_

#include "log_level.hpp"
#include <string>

/**
 * A class that log messages
 */
class LoggerInterface { 

public:
  virtual ~LoggerInterface() {
  }

  // TODO : use an enum instead of int for the level
  virtual std::ostream * get_appender(enum LogLevel::Level) const = 0;

  virtual void new_line() const = 0;

};

#endif // _LOGGER_HPP_