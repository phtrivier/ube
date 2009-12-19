#include "resource_resolver.hpp"
#include "abstract_file_checker.hpp"
#include <cassert>
using namespace std;

void 
ResourceResolver::set_prefixes(const char* iPrefixes[], int iPrefixCount) 
{
  clearPrefixes();
  // Make sure prefixes are check next time get_safe_prefix() is called.
  pPrefix_ = NULL;
  for (int i=0 ; i<iPrefixCount ; i++) {
    prefixes_.push_back(new string(iPrefixes[i]));
  }
  
}

ResourceResolver::~ResourceResolver() 
{
  clearPrefixes();
}

void
ResourceResolver::clearPrefixes() 
{
  vector<const string*>::iterator it = prefixes_.begin();
  while( it != prefixes_.end()) {
    if (*it != NULL) {
      delete *it;
    }
    ++it;
  }
  prefixes_.clear();
}

bool
ResourceResolver::check_prefixes() {
  assert(pChecker_!=NULL);
  vector<const string*>::iterator it = prefixes_.begin();
  bool found = false;
  while (!found && it != prefixes_.end()) {
    found = (pChecker_->is_folder_present(*(*it)));
    if (!found) {
      ++it;
    }
  }
  if (found) {
    pPrefix_ = *it;
  }
  return found;
}

string
ResourceResolver::get_safe_prefix()
{
  string res = "";
  if (pPrefix_ != NULL || check_prefixes()) {
    res = *pPrefix_;
    res.append("/");
  } 
  return res;
}

string 
ResourceResolver::get_locale_dir() 
{
  string res = get_safe_prefix();
  res.append("share/locale");
  return res;
}

string 
ResourceResolver::get_image_file_name(const char * iImageName) 
{
  return getResFileName("images", iImageName);
}

string 
ResourceResolver::get_font_file_name(const char * iFontName) 
{
  return getResFileName("fonts", iFontName);
}

string
ResourceResolver::get_lua_file_name(const char * iFileName, const char * iStandardPrefix, const char * iTestPrefix)
{
  string res;
  if (test_mode_) {
    res = SRCDIR;
    res.append(iTestPrefix);
    res.append(iFileName);
  } else {
    res = getResFileName(iStandardPrefix, iFileName);
  } 
  return res;
}

string 
ResourceResolver::get_engine_lua_file_name(const char * iFileName) 
{
  return get_lua_file_name(iFileName, "lua/engine", "/../engine/lua/");
}

string 
ResourceResolver::get_puzzle_lua_file_name(const char *iFileName)
{
  return get_lua_file_name(iFileName, "lua/puzzles", "/../engine/tests/lua/");
}

string
ResourceResolver::getResFileName(const char *iResType, const char * iResName)
{
  string res = get_safe_prefix();
  res.append("share/ube/");
  res.append(iResType);
  res.append("/");
  res.append(iResName);
  return res;
}
