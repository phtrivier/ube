#ifndef _COUT_LOGGER_HPP_
#define _COUT_LOGGER_HPP_

#include <iostream>

#include "logger_interface.hpp"

/**
 * A logger that outputs everything to cout / cerr
 */
class CoutLogger :
  public LoggerInterface
{ 

public:

  CoutLogger() {
  }

  ~CoutLogger() {
  }

  void debug(std::string i_msg) const {
    std::cout << i_msg << std::endl;
  }
  
  void log(std::string i_msg) const {
    std::cout << i_msg << std::endl;
  }
  
  void error(std::string i_msg) const {
    std::cerr << i_msg << std::endl;
  }
  
};

#endif // _COUT_LOGGER_HPP_
