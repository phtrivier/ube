/**
 * This is Free Software. See COPYING for information.
 */
#ifndef _COUT_LOGGER_HPP_
#define _COUT_LOGGER_HPP_

#include <iostream>

#include "logger_interface.hpp"

/**
 * A logger that outputs everything to cout / cerr.
 */
class CoutLogger :
  public LoggerInterface
{ 

public:

  std::ostream * get_appender(LogLevel::Level i_level) const {
    return &(std::cout);
  }
  
  void new_line() const {
    std::cout << std::endl;
  }

};

#endif // _COUT_LOGGER_HPP_