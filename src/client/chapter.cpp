/**
 * This is Free Software. See COPYING for information.
 */
#include "chapter.hpp"

#include <algorithm>
#include <vector>
#include <string>

bool
Chapter::has_puzzle_file_name(std::string i_puzzle_file_name)
{
  int count = (int) std::count(puzzle_file_names_.begin(), puzzle_file_names_.end(), i_puzzle_file_name);
  return (count != 0);
}
