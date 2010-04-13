/**
 * This is Free Software. See COPYING for information.
 */
#include "logging.hpp"

#include <algorithm>

void 
Logging::disable_logging() {
}

// TODO(pht):improve this so that if a category is added at level LOG, DEBUG is enabled
bool 
Logging::is_category_enabled(LogLevel::Level i_level, 
			     std::string & i_category) {
  bool res = false;
  if (i_level == LogLevel::ERROR) {
    res = true;
  } else {
    if (get_categories() != NULL) {
      std::list<std::string> * c  = get_categories();
      return std::find(c->begin(), c->end(), i_category) != c->end();
    }
  }
  return res;
}

std::ostream & 
Logging::get_ostream(LogLevel::Level i_level, std::string i_category) {
  std::ostream * res = get_default_appender();
  if (get_logger()!=NULL && is_category_enabled(i_level, i_category)) {
    get_logger() -> new_line(); 
    res = get_logger() -> get_appender(i_level);
  }
  return *res;
}