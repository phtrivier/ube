#include <gmock/gmock.h>
#include "abstract_file_checker.hpp"

class MockFileChecker : public AbstractFileChecker {
 public:
  MOCK_CONST_METHOD1(is_folder_present,
	       bool(const std::string iPath));
  MOCK_CONST_METHOD1(is_file_present,
	       bool(const std::string iPath));
};
