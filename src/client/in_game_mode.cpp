#include "in_game_mode.hpp"

#include "engine/path_finder_interface.hpp"
#include "in_game_mode.hpp"

void
InGameMode::update_game(int iDelta)
{
  GameMode::update_game(iDelta);
  
  // ask the model to update its content
  dep_model_.update_path();
}
