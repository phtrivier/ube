#include <config.h>
#include <locale.h>
#include "gettext.h"
#define _(String) gettext (String)

#include <greeter.hpp>

#include <iostream>
#include <cstdio>
using namespace std;

int main(int argc, char ** argv) {
  
  // printf("This is %s. Thanks for watching\n", PACKAGE_STRING);

  cout << "For info : " << LOCALEDIR << endl;
  
  setlocale (LC_ALL, "");
  bindtextdomain (PACKAGE, LOCALEDIR);
  textdomain (PACKAGE);

  // Just for a lest ... normally I have done everything required ... 
  printf(_("Hello %s. What's the craic today ?\n"), "prout");

  Greeter g("PHT");
  g.greet();
  
}
