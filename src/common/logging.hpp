#ifndef _LOGGING_HPP_
#define _LOGGING_HPP_

#include "logger_interface.hpp"

#include <string>

/**
 * Singleton class with facilities for logging.
 *
 * The methods of Logging should not be used by themselves. Rather, one should use the 
 * LOG_D, LOG_L, LOG_E macros.
 *
 * The idea is that those macros can be brutally redefined so that nothings can logged
 * in the actual application. 
 */
class Logging {
public:

  static void debug(std::string i_msg, std::string i_category) {
    // TODO : take category into account
    if (getLogger() != NULL) {
      getLogger()->debug(i_msg);
    }
  }

  static void log(std::string i_msg, std::string i_category) {
    // TODO : take category into account
    if (getLogger() != NULL) {
      getLogger()->log(i_msg);
    }
  }

  static void error(std::string i_msg) {
    // TODO : take category into account
    if (getLogger() != NULL) {
      getLogger()->error(i_msg);
    }
  }

  /**
   * A static instance of a logger, set by setLogger.
   */
  static LoggerInterface * getLogger() {
    return Logging::ps_logger;
  }

  static void setLogger(LoggerInterface & i_logger) {
    ps_logger = &i_logger;
  }

  static LoggerInterface * ps_logger;

};

// Macro to trace message.
// TODO : disable the worst versions
#define LOG_D(msg, category) Logging::debug((msg),(category));
#define LOG_L(msg, category) Logging::debug((msg),(category));
#define LOG_E(msg) Logging.error((msg));

#endif // _LOGGING_HPP_
