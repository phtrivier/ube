/**
 * This is Free Software. See COPYING for information.
 */
#ifndef _SCRIPT_RUNNER_INTERFACE_HPP_
#define _SCRIPT_RUNNER_INTERFACE_HPP_

class Puzzle;

/**
 * Interface to run scripts
 */
class ScriptRunnerInterface { 

public:

  virtual ~ScriptRunnerInterface() {
  }

  virtual void do_script(int i_index, Puzzle * o_p_puzzle) = 0;

  virtual void undo_script(int i_index, Puzzle * o_p_puzzle) = 0;

  
};

#endif // _SCRIPT_RUNNER_INTERFACE_HPP_