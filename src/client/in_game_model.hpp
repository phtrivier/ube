#ifndef _IN_GAME_MODEL_HPP_
#define _IN_GAME_MODEL_HPP_

class Puzzle;

/**
 * Model for the bulk of the game
 */
class InGameModel { 

public:

  InGameModel() {
  }

  ~InGameModel() {
  }
  
  Puzzle & get_puzzle() {
    return *dep_puzzle_;
  }

  void set_puzzle(Puzzle & dep_puzzle) {
    this->dep_puzzle_ = &dep_puzzle;
  }
  
private:
  Puzzle * dep_puzzle_;
};

#endif // _IN_GAME_MODEL_HPP_
