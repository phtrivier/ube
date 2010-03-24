#include <gmock/gmock.h>
#include "engine/script_runner_interface.hpp"

class Puzzle;

class MockScriptRunner : public ScriptRunnerInterface {
 public:
  MOCK_METHOD2(do_script,
      void(int i_index, Puzzle * o_p_puzzle));
  MOCK_METHOD2(undo_script,
      void(int i_index, Puzzle * o_p_puzzle));
};
