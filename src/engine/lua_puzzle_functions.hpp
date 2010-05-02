/**
 * This is Free Software. See COPYING for information.
 */

/**
 * Bridge functions between the Puzzle class and lua.
 * See also lua_puzzle_loader.cpp
 */

int lua_puzzle_set_dimensions(lua_State * ipLuaState) {
  Puzzle * pPuzzle = (Puzzle *) lua_touserdata(ipLuaState,1);
  int w = lua_tointeger(ipLuaState,2);
  int h = lua_tointeger(ipLuaState,3);
  // TODO(pht) : handle possible negative values here (we're not in the baricade yet !)
  pPuzzle->set_dimensions(w,h);
  return 0;
}

int lua_puzzle_loader_set_row(lua_State * ipLuaState) {
  Puzzle * pPuzzle = (Puzzle *) lua_touserdata(ipLuaState,1);
  LuaPuzzleLoader * pPuzzleLoader = (LuaPuzzleLoader *) lua_touserdata(ipLuaState,2);
  int i = lua_tointeger(ipLuaState,3);
  const char * row = lua_tostring(ipLuaState, 4);
  // TODO(pht) : handle possible bad chars in the row (untranslatable ones, we're not in the baricade yet !)
  pPuzzleLoader->set_row(i,pPuzzle,row);
  return 0;
}

int lua_puzzle_add_move(lua_State * i_p_lua_state) {
  Puzzle * p_puzzle = (Puzzle *) lua_touserdata(i_p_lua_state, 1);
  int move_type = lua_tointeger(i_p_lua_state,2);
  assert(p_puzzle != NULL);
  assert(move_type >= 0);
  p_puzzle->add_move(move_type);
  int res = (int) p_puzzle->moves().size() - 1;
  lua_pushinteger(i_p_lua_state, res);
  return 1;
}

int lua_puzzle_add_script(lua_State * i_p_lua_state) {
  Puzzle * p_puzzle = (Puzzle *) lua_touserdata(i_p_lua_state, 1);
  LuaPuzzleLoader * p_puzzle_loader = (LuaPuzzleLoader *) lua_touserdata(i_p_lua_state, 2);
  assert(p_puzzle_loader != NULL);

  int i = lua_tointeger(i_p_lua_state,3);
  int j = lua_tointeger(i_p_lua_state,4);
  int index = lua_tointeger(i_p_lua_state,5);
  
  LuaCommand * p_command = p_puzzle_loader->create_script(index, p_puzzle);
  p_puzzle->add_script(i,j,p_command);
  return 0;
}

int lua_puzzle_add_puzzle_move(lua_State * i_p_lua_state) {
  Puzzle * p_puzzle = (Puzzle *) lua_touserdata(i_p_lua_state, 1);
  int move_type = lua_tointeger(i_p_lua_state,2);
  p_puzzle->add_move(move_type);
  int res = (int) p_puzzle->moves().size() - 1;
  lua_pushinteger(i_p_lua_state, res);
  return 1;
}

int lua_puzzle_remove_move(lua_State * i_p_lua_state) {
  Puzzle * p_puzzle = (Puzzle *) lua_touserdata(i_p_lua_state, 1);
  int move_index = lua_tointeger(i_p_lua_state,2);
  assert(move_index < (int) p_puzzle->moves().size());
  p_puzzle->moves().erase( p_puzzle->moves().begin() + move_index);
  return 0;
}
  
int lua_puzzle_set_overlay(lua_State * i_p_lua_state) {
  Puzzle * p_puzzle = (Puzzle *) lua_touserdata(i_p_lua_state, 1);
  assert(p_puzzle != NULL);
  int i = lua_tointeger(i_p_lua_state,2);
  int j = lua_tointeger(i_p_lua_state,3);
  int type = lua_tointeger(i_p_lua_state,4);
  // FIXME(pht) : this is from outside, it should be checked
  p_puzzle->set_overlay(i,j,type);
  return 0;
}

int lua_puzzle_set_start_message(lua_State * i_p_lua_state) {
  Puzzle * p_puzzle = (Puzzle *) lua_touserdata(i_p_lua_state, 1);
  assert(p_puzzle != NULL);
  const char * s_msg = lua_tostring(i_p_lua_state, 2);
  std::string msg(s_msg);
  p_puzzle->set_start_message(msg);
  return 0;
}

int lua_puzzle_set_end_message(lua_State * i_p_lua_state) {
  Puzzle * p_puzzle = (Puzzle *) lua_touserdata(i_p_lua_state, 1);
  assert(p_puzzle != NULL);
  const char * s_msg = lua_tostring(i_p_lua_state, 2);
  std::string msg(s_msg);
  p_puzzle->set_end_message(msg);
  return 0;
}
