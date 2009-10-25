#include "resource_resolver.hpp"
#include "abstract_file_checker.hpp"
#include <cassert>
using namespace std;

void 
ResourceResolver::setPrefixes(const char* iPrefixes[], int iPrefixCount) 
{
  clearPrefixes();
  // Make sure prefixes are check next time getSafePrefix() is called.
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
ResourceResolver::checkPrefixes() {
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
ResourceResolver::getSafePrefix()
{
  string res = "";
  if (pPrefix_ != NULL || checkPrefixes()) {
    res = *pPrefix_;
    res.append("/");
  } 
  return res;
}

string 
ResourceResolver::getLocaleDir() 
{
  string res = getSafePrefix();
  res.append("share/locale");
  return res;
}

string 
ResourceResolver::getImageFileName(const char * iImageName) 
{
  string res = getSafePrefix();
  res.append("share/ube/images/");
  res.append(iImageName);
  return res;
}
