/**
 * This is Free Software. See COPYING for information.
 */
#include "in_game_model_loader.hpp"

#include "engine/cell_factory.hpp"
#include "client/in_game_model.hpp"

int
InGameModelLoader::load_puzzle_file(const char * i_file_name, InGameModel & o_model) 
{
  int res = LuaPuzzleLoader::load_puzzle_file(i_file_name, o_model.get_puzzle());
  if (res == 0) {
    o_model.get_puzzle().enters_player();
    o_model.set_first_available_move_as_current();
  }
  return res;
}
