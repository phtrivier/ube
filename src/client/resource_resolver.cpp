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
    found = (pChecker_->isFolderPresent(*(*it)));
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
ResourceResolver::getResFileName(const char *iResType, const char * iResName)
{
  string res = get_safe_prefix();
  res.append("share/ube/");
  res.append(iResType);
  res.append("/");
  res.append(iResName);
  return res;
}
