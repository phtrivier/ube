#ifndef _PUZZLE_LOADER_HPP_
#define _PUZZLE_LOADER_HPP_

class Puzzle;
class CellFactory;

/**
 * Helper class to populate the cells of a puzzle.
 *
 * It should be used in conjunction with a 
 * CellFactory to load rows. 
 * eg : 
 *    CellFactory factory;
 *    PuzzleLoader loader(factory);
 *    // Assuming p is a puzzle whith dimension 6,3
 *    loader.set_row(0,&puzzle, "######")
 *    loader.set_row(1,&puzzle, "#I--O#")
 *    loader.set_row(2,&puzzle, "######")
 */
class PuzzleLoader { 
  CellFactory * pFactory_;
public:
  PuzzleLoader(CellFactory * piFactory) : pFactory_(piFactory) {
  }
  ~PuzzleLoader() {
  }

  /**
   * Set a row on a puzzle, parsing a line of
   * letters representing the cells.
   *
   * @param i index of the row to fill
   * @param poPuzzle the puzzle to modify
   * @param row string representing the row
   */
  void set_row(int i, Puzzle * poPuzzle, const char * row);
  
};

#endif // _PUZZLE_LOADER_HPP_
