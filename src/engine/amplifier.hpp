#ifndef _AMPLIFIER_HPP_
#define _AMPLIFIER_HPP_

class Amplifier {

public:
  Amplifier() {
  }
  virtual ~Amplifier() {
  }
  virtual void amplify(const std::string & iStr) const = 0;
};

#endif // _AMPLIFIER_HPP_
