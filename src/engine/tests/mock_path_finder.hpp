#include <gmock/gmock.h>
#include "engine/path_finder_interface.hpp"

class MockPathFinder : public PathFinderInterface {
public:
  MOCK_METHOD6(find_path,
	       int(Puzzle * o_p_puzzle, 
		   int i_i0, int i_j0,
		   int i_i1, int i_j1,
		   int move_type));

};
