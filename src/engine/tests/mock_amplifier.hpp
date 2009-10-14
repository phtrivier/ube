/*
#include <string.h>
namespace std {
class string;
}
*/
#include "amplifier.hpp"

class MockAmplifier : public Amplifier {
 public:
  MOCK_CONST_METHOD1(amplify, void(const std::string & iStr));
};
