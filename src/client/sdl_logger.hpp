#ifndef _SDL_LOGGER_HPP_
#define _SDL_LOGGER_HPP_

#include "common/logger_interface.hpp"

#include <iostream>

#include "SDL.h"


/**
 * A logger that uses SDL_GetTicks() to timestamp everything.
 */
class SdlLogger :
  public LoggerInterface
{ 
public:
  void debug(std::string i_msg) const {
    std::cout << "DEBUG: " 
	      << SDL_GetTicks() 
	      << " - " 
	      << i_msg << std::endl;
  }
  
  void log(std::string i_msg) const {
    std::cout << "LOG  : " << SDL_GetTicks() << " - " << i_msg << std::endl;
  }
  
  void error(std::string i_msg) const {
    std::cout << "ERROR: " << SDL_GetTicks() << " - " << i_msg << std::endl;
  }
};

#endif // _SDL_LOGGER_HPP_
