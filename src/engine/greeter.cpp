#include <greeter.hpp>

#include <cstdio>
using namespace std;

void Greeter::greet() const {
  printf("Hello %s. What's the craic today ? \n", this->my_target.c_str());
}
