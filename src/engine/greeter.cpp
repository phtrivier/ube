#include <greeter.hpp>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "gettext.h"
#define _(String) gettext (String)

#include <cstdio>
using namespace std;

#include <stdio.h>
#include <stdlib.h>

#include <amplifier.hpp>

void Greeter::greet() const {
  printf(_("Hello %s!!\n"), this->my_target.c_str());
}

void Greeter::shout(const Amplifier & iAmplifier) const {
  /* Note : in a real implementation, I would have to make sure that 
     the buffer is big enough, and do something in case of overflow. 
     Yeah, C string management suck.
  */
  char buffer[100];
  snprintf(buffer, 100, _("Hello %s!!\n"), this-> my_target.c_str());
  iAmplifier.amplify(buffer);
}
