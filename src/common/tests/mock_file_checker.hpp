#include <gmock/gmock.h>
#include "file_checker_interface.hpp"

class MockFileChecker : public FileCheckerInterface {
 public:
  MOCK_CONST_METHOD1(is_folder_present,
	       bool(const std::string iPath));
  MOCK_CONST_METHOD1(is_file_present,
	       bool(const std::string iPath));
};
