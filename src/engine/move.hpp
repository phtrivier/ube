/**
 * This is Free Software. See COPYING for information.
 */
#ifndef _MOVE_HPP_
#define _MOVE_HPP_

namespace MoveType {
  static const int SINGLE = 0;
  static const int DOUBLE = 1;
  // Marker to help loops, should be increased
  // when elements are added
  static const int LAST = 1;
}

/**
 * A move that can be done in the maze
 */
class Move { 
  
public:

  explicit Move(int i_type) : 
    available_(true),
    type_(i_type)
  {
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