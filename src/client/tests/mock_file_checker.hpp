#include <gmock/gmock.h>
#include "abstract_file_checker.hpp"

class MockFileChecker : public AbstractFileChecker {
 public:
  MOCK_CONST_METHOD1(isFolderPresent,
	       bool(const std::string iPath));
  MOCK_CONST_METHOD1(isFilePresent,
	       bool(const std::string iPath));
};
