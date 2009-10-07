#include <greeter.hpp>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "gettext.h"
#define _(String) gettext (String)

#include <cstdio>
using namespace std;

void Greeter::greet() const {
  printf(_("Hello %s!!\n"), this->my_target.c_str());
}
