#include "lua_command.hpp"

#include "script_runner_interface.hpp"
#include "puzzle.hpp"

void
LuaCommand::execute()
{
  dep_runner_.do_script(index_, &dep_puzzle_);
}

void
LuaCommand::undo()
{
  dep_runner_.undo_script(index_, &dep_puzzle_);
}
