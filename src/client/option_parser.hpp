/**
 * This is Free Software. See COPYING for information.
 */
#ifndef _OPTION_PARSER_HPP_
#define _OPTION_PARSER_HPP_

#include <string>

#include "popt.h"

/**
 * Parser for command line options
 */
class OptionParser { 

public:

  OptionParser() {
    should_show_version_ = 0;
    should_show_copyright_ = 0;
  }

  ~OptionParser();

  /**
   * Parse command line options.
   *
   * @return 0 if everything went fine, -1 otherwise.
   */
  int parse_options(int i_argc, const char ** i_argv);

  /**
   * Was a puzzle file name parsed from the arguments ? 
   */
  bool has_puzzle_file_name() const;
  
  /**
   * The puzzle file name fiven as argument.
   */
  std::string get_puzzle_file_name() const;

  /**
   * Has the 'version' option been used ? 
   */
  bool should_show_version() const {
    return (should_show_version_ != 0);
  }

  bool should_show_copyright() const {
    return (should_show_copyright_ != 0);
  }


private:

  poptContext opt_con_;

  // Should be allocated by popt
  const char * s_puzzle_file_name_;

  // Should be filled by popt
  int should_show_version_;
  int should_show_copyright_;

};

#endif // _OPTION_PARSER_HPP_
