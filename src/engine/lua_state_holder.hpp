/**
 * This is Free Software. See COPYING for information.
 */
#ifndef _LUA_STATE_HOLDER_HPP_
#define _LUA_STATE_HOLDER_HPP_

#include <iostream>
using namespace std;

#include <string>

class ResourceResolverInterface;
struct lua_State;

/**
 * A class that maintains a lua state and can perform lua operations
 */
class LuaStateHolder { 

public:

  LuaStateHolder(ResourceResolverInterface & dep_resolver) : 
    dep_resolver_(dep_resolver)
  {
    init_lua_state();
  }

  virtual ~LuaStateHolder() {
    close_lua_state();
  }

protected:

  lua_State * get_lua_state() {
    return pLuaState_;
  }

  ResourceResolverInterface & get_resolver() {
    return dep_resolver_;
  }

  /**
   * Die notifying a lua error.
   * TODO(pht) : kill if not used
   */
  void error(const char * fmt, ...);

  /**
   * Loads a lua file with its absolute path.
   */
  void load_lua_file(std::string iFilePath);

  /**
   * Try and load an engine lua file, using the resource resolver to find it.
   */
  void load_lua_engine_file(const char * iFileName);

private:

  ResourceResolverInterface & dep_resolver_;

  // Lua context
  lua_State * pLuaState_;

  /**
   * Init the lua state machine
   */
  void init_lua_state();

  /**
   * Shut down the lua state machine
   */
  void close_lua_state();

};

#endif // _LUA_STATE_HOLDER_HPP_