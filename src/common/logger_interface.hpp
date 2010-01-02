#ifndef _LOGGER_HPP_
#define _LOGGER_HPP_

#include <string>

/**
 * A class that log messages
 */
class LoggerInterface { 

public:
  virtual ~LoggerInterface() {
  }

  virtual void debug(std::string i_msg) const =0;
  virtual void log(std::string i_msg) const = 0;
  virtual void error(std::string i_msg) const =0;

};

#endif // _LOGGER_HPP_
