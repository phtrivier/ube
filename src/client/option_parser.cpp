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
}

int 
OptionParser::parse_options(int i_argc, const char ** i_argv) {
  int res = 0;

  s_puzzle_file_name_ = NULL;

  // TODO(pht) : make this table an attribute of the object, 
  // so that I can use the poptDisplayHelp and poptDisplayUsage stuff to 
  // display a nicer 'help' page, and display usage in case of argument error.
  struct poptOption optionsTable[] = {
    { "puzzle",
      'p',
      POPT_ARG_STRING,
      &s_puzzle_file_name_,
      0,
      _("Specify a puzzle file name. It should be the name of an existing lua file, like 'puzzle1.lua'. The file should be residing in the standard shared/ube/lua/puzzles folder."),
      _("PUZZLE FILE NAME")},

    { "version",
      'v',
      POPT_ARG_NONE,
      &should_show_version_,
      1,
      _("Show version number"),
      NULL},

    { "copyright",
      '\0',
      POPT_ARG_NONE,
      &should_show_copyright_,
      1,
      _("Show copyright info"),
      NULL},



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
    poptPrintUsage(opt_con_, stdout, 1);
  }

  poptFreeContext(opt_con_);

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

