#ifndef _LOGGING_HPP_
#define _LOGGING_HPP_

#include "log_level.hpp"
#include "logger_interface.hpp"
#include "silent_ostream.hpp"
#include <assert.h>

#include <string>
#include <list>

/**
 * Singleton class with facilities for logging.
 *
 * Logging is enabled by using the Logging::init_logging(..) method.
 * A Logger must be configured to do this ; for convenience, the SilentLogger class 
 * can be used to prevent any logging.
 *
 * The methods of Logging should not be used by themselves. Rather, one should use the 
 * LOG_D, LOG_L, LOG_E macros, in this form : 
 *
 * LOG_D("toto") << "Foo : " << 12 << ", bar : " << 13;
 *
 * Note that to compile a main program that does use logging, you will have to use Logging::disable_logging().
 *
 * I know, this sucks.
 *
 * The idea is that those macros can be brutally redefined so that nothings can logged
 * in the actual application. 
 *
 */
class Logging {
public:

  /**
   * Disable logging.
   * This function is defined in the logging.cpp file, so
   * calling this simply makes sure that the static symbols
   * defined here are available. This is a hack, it will be fixed.
   */
  static void disable_logging();

  // Utility method to set the logger of the Logging singleton
  static void init_logging(LoggerInterface & i_logger) {
    get_instance().set_logger(i_logger);
  }

  // Utility method to add a category to the Logging singleton
  static void add_logging_category(std::string i_category) {
    get_instance().add_category(i_category);
  }

  static std::ostream & debug_ostream(std::string i_category) {
    return Logging::get_instance().get_ostream(LogLevel::DEBUG, i_category);
  }

  static std::ostream & log_ostream(std::string i_category) {
    return Logging::get_instance().get_ostream(LogLevel::LOG, i_category);
  }

  static std::ostream & error_ostream() {
    return Logging::get_instance().get_ostream(LogLevel::ERROR);
  }

protected:

  Logging() {
    p_default_appender_ = new SilentOstream();
    p_categories_ = new std::list<std::string>();
  }

  ~Logging() {
    // This is called because the singleton is defined as a static, local variable
    // (this is a Meyers Singleton)
    delete p_default_appender_;
    p_categories_->clear();
    delete p_categories_;
  }

  static Logging & get_instance() {
    // Meyers singleton
    static Logging s_local_instance;
    return s_local_instance;
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
  
  bool is_category_enabled(LogLevel::Level i_level, 
			   std::string & i_category);


  void add_category(std::string i_category) {
    assert(p_categories_ != NULL);
    p_categories_->push_front(i_category);
  }

  std::ostream & get_ostream(LogLevel::Level i_level, std::string i_category="");

};

/**
 * Those are the actual macros to use.
 * TODO(pht) : if NDEBUG or something, get rid of the logs completely !
 */
#define LOG_D(category) Logging::debug_ostream(category) 
#define LOG_L(category) Logging::log_ostream(category) 
#define LOG_E() Logging::error_ostream()

#endif // _LOGGING_HPP_
