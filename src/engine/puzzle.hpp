#ifndef _PUZZLE_HPP_
#define _PUZZLE_HPP_

#include <iostream>
#include <string>

class Puzzle {
  std::string my_name;
public:
  Puzzle(std::string iName) : my_name(iName) {
  }
  ~Puzzle(){
  }
  void set_name(const std::string & iName) {
    my_name = iName;
  }
  std::string get_name() {
    return my_name;
  }
};

#endif //_PUZZLE_HPP_
