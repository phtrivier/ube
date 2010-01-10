#ifndef _OPTION_PARSER_HPP_
#define _OPTION_PARSER_HPP_

#include <string>

#include "popt.h"

/**
 * Parser for command line options
 */
class OptionParser { 

public:

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

private:

  poptContext opt_con_;

  // Should be allocated by popt
  const char * s_puzzle_file_name_;

};

#endif // _OPTION_PARSER_HPP_
