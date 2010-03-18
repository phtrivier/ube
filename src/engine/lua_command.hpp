#ifndef _LUA_COMMAND_HPP_
#define _LUA_COMMAND_HPP_

#include "mvc/command_interface.hpp"

class ScriptRunnerInterface;
class Puzzle;

/**
 * Commands that run lua scripts
 */
class LuaCommand :
  public CommandInterface
{ 

public:

  LuaCommand(int i_index, Puzzle & dep_puzzle, ScriptRunnerInterface & dep_runner):
    index_(i_index),
    dep_puzzle_(dep_puzzle),
    dep_runner_(dep_runner)
  {
  }

  ~LuaCommand() {
  }

  void execute();

  void undo();

  int get_index() {
    return index_;
  }
  
private:

  int index_;

  Puzzle & dep_puzzle_;
  ScriptRunnerInterface & dep_runner_;

};

#endif // _LUA_COMMAND_HPP_
