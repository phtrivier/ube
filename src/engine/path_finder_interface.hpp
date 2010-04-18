/**
 * This is Free Software. See COPYING for information.
 */
#ifndef _PATH_FINDER_INTERFACE_HPP_
#define _PATH_FINDER_INTERFACE_HPP_

class Puzzle;

/**
 * Computes path from cells in a puzzle
 */
class PathFinderInterface { 

public:

  virtual ~PathFinderInterface() {
  }
  
  virtual int find_path(Puzzle * o_p_puzzle, 
			int i_i0, int i_j0, 
			int i_i1, int i_j1,
			int move_type) = 0;

};

#endif // _PATH_FINDER_INTERFACE_HPP_