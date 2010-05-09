#ifndef _CHAPTER_HPP_
#define _CHAPTER_HPP_

#include <assert.h>

#include <string>
#include <vector>

/**
 * List of puzzle names and files for a chapter
 */
class Chapter { 
public:
  
  Chapter(std::string i_chapter_name):
    chapter_name_(i_chapter_name),
    puzzle_names_(),
    puzzle_file_names_()
  {
  }

  ~Chapter()
  {
  }

  /**
   * Add a puzzle to this chapter
   * @param name the string displayed to select this model
   * @param file_name the name of the lua puzzle file to load (eg "tutorial1.lua") 
   */
  void add_puzzle(std::string name, std::string file_name) {
    puzzle_names_.push_back(name);
    puzzle_file_names_.push_back(file_name);
  }

  int size() {
    return puzzle_names_.size();
  }

  std::vector<std::string> & puzzle_names() {
    return puzzle_names_;
  }

  std::string puzzle_file_name_at(int i_index) {
    assert(i_index < (int) puzzle_file_names_.size());
    return puzzle_file_names_[i_index];
  }

  std::string chapter_name() {
    return chapter_name_;
  }

  bool has_puzzle_file_name(std::string i_puzzle_file_name);
  
private:

  // Name of the chapter to be displayed
  std::string chapter_name_;
  // List of the "human readible" names of the puzzle
  std::vector<std::string> puzzle_names_;
  // List of the lua file names for puzzles
  std::vector<std::string> puzzle_file_names_;

};

#endif // _CHAPTER_HPP_
