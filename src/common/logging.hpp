#ifndef _LOGGING_HPP_
#define _LOGGING_HPP_

#include "log_level.hpp"
#include "logger_interface.hpp"
#include "silent_ostream.hpp"
#include <assert.h>

#include <string>
#include <list>
#include <algorithm>

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

  // Utility method to set the logger of the Logging singleton
  static void init_logging(LoggerInterface & i_logger) {
    get_instance()->set_logger(i_logger);
  }

  // Utility method to add a category to the Logging singleton
  static void add_logging_category(std::string i_category) {
    get_instance()->add_category(i_category);
  }

  static std::ostream & debug_ostream(std::string i_category) {
    std::ostream * res = Logging::get_instance()->get_default_appender();
    if (Logging::get_instance()->is_category_enabled(LogLevel::DEBUG, i_category)) {
      Logging::get_instance()->new_line(); 
      res = (Logging::get_instance()->get_appender(LogLevel::DEBUG, std::string(i_category)));
    }
    return *res;
  }

protected:

  Logging() {
    // Init stuff (like the default appender, or stuff like that)
    p_default_appender_ = new SilentOstream();
    p_categories_ = new std::list<std::string>();
  }

  ~Logging() {
    // Dealocate everything you own ...
  }

  // This should be the only ps_instance
  static Logging * ps_instance;

  static Logging * get_instance() {
    if (ps_instance == NULL) {
      ps_instance = new Logging();
    }
    return ps_instance;
  }
 
  LoggerInterface * dep_logger_;

  std::ostream * p_default_appender_;
  
  std::list<std::string> * p_categories_;

  /**
   * Setter for the current logger.
   */
  void set_logger(LoggerInterface & i_logger) {
    dep_logger_ = &i_logger;
  }

  /**
   * A static instance of a logger, set by set_logger.
   */
  LoggerInterface * get_logger() {
    return dep_logger_;
  }

  std::list<std::string> * get_categories() {
    return p_categories_;
  }

  std::ostream * get_default_appender() {
    return p_default_appender_;
  }
  
  bool is_category_enabled(LogLevel::Level i_level, std::string & i_category) {
    bool res = false;
    if (get_categories() != NULL) {
      std::list<std::string> * c  = get_categories();
      return std::find(c->begin(), c->end(), i_category) != c->end();
    }
    return res;
  }

  std::ostream * get_appender(LogLevel::Level i_level, std::string i_category) {
    std::ostream * res = get_default_appender();
    if (get_logger() != NULL && is_category_enabled(i_level, i_category)) {
      res = get_logger()->get_appender(i_level);
    }
    return res;
  }
 
  void add_category(std::string i_category) {
    assert(p_categories_ != NULL);
    p_categories_->push_front(i_category);
  }

  void new_line() {
    if (get_logger() != NULL) {
      get_logger()->new_line();
    }
  }

};

#define LOG_D(category) Logging::debug_ostream(category) 

// TODO : LOG_D, LOG_E

#endif // _LOGGING_HPP_
