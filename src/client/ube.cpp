#include <config.h>

#include <greeter.hpp>

#include <iostream>
#include <cstdio>
using namespace std;

int main(int argc, char ** argv) {
  
  // printf("This is %s. Thanks for watching\n", PACKAGE_STRING);
  
  Greeter g("PHT");
  g.greet();
  
}
