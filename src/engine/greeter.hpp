#ifndef _GREETER_HPP_
#define _GREETER_HPP_

#include <string>

class Amplifier;

class Greeter {
  std::string my_target;
public:
  Greeter(std::string iTarget) : my_target(iTarget) {
  }
  void greet() const;
  void shout(const Amplifier & iAmplifier) const;
};

#endif //_GREETER_HPP_
