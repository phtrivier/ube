#ifndef _MOVE_HPP_
#define _MOVE_HPP_

namespace MoveType {
  static const int DOUBLE = 0;
  static const int KNIGHT = 1;
}

/**
 * A move that can be done in the maze
 */
class Move { 
  
public:

  Move() : available_(true) {
  }

  
  int type() const {
    return type_;
  }
  
  bool available() const {
    return available_;
  }

  void use() {
    available_ = false;
  }

  void revert() {
    available_ = true;
  }

private:

  bool available_;

  int type_;

};


#endif // _MOVE_HPP_
