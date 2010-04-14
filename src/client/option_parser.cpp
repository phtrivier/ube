/**
 * This is Free Software. See COPYING for information.
 */
#include "option_parser.hpp"

#include "common/i18n.hpp"
#include "common/logging.hpp"

#include <assert.h>


extern "C" {
#include <popt.h>
}

OptionParser::~OptionParser() {
  poptFreeContext(opt_con_);
}

int 
OptionParser::parse_options(int i_argc, const char ** i_argv) {
  int res = 0;

  s_puzzle_file_name_ = NULL;

  struct poptOption optionsTable[] = {
    { "puzzle",
      'p',
      POPT_ARG_STRING,
      &s_puzzle_file_name_,
      0,
      _("Specify a puzzle file name.\nIt should be the name of an existing lua file, like 'puzzle1.lua'.\nThe file should be residing in the standard shared/ube/lua/puzzles folder.like 'puzzle1.lua'"),
      _("PUZZLE FILE NAME")},
    POPT_AUTOHELP
    { NULL, 0, 0, NULL, 0 }
  };

  LOG_D("parser") << "Parsing option tables" << std::endl;

  opt_con_ = poptGetContext(NULL, i_argc, i_argv, optionsTable, 0);

  LOG_D("parser") << "Option table parsed" << std::endl;

  int c;
  while ((c = poptGetNextOpt(opt_con_)) >= 0) {
    // What should I do ? 
  }

  if (c < -1) {
    res=c;
  }
  return res;
}

bool
OptionParser::has_puzzle_file_name() const {
  return s_puzzle_file_name_ != NULL;
}

std::string
OptionParser::get_puzzle_file_name() const {
  assert(has_puzzle_file_name());
  return std::string(s_puzzle_file_name_);
}
