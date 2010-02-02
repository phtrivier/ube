#include "common/lua_helper.hpp"
#include "common/resource_resolver_interface.hpp"

#include "lua_state_holder.hpp"

#include <cstdlib>
#include "boost/format.hpp"
using boost::format;


void 
LuaStateHolder::init_lua_state() 
{
  pLuaState_ = lua_open();
  luaL_openlibs(pLuaState_);

  lua_pushstring(pLuaState_, dep_resolver_.get_engine_lua_path().c_str());
  lua_setglobal(pLuaState_, "ube_engine_lua_path");
		 
}

void
LuaStateHolder::close_lua_state()
{
  lua_close(pLuaState_);
}

void
LuaStateHolder::error(const char * fmt, ...)
{
  // TODO(pht) : throw instead of killing
  // The problem is formatting the message ... 
  va_list argp;
  va_start(argp, fmt);
  vfprintf(stderr, fmt, argp);
  va_end(argp);
  lua_close(pLuaState_);
  exit(-1);
}

void
LuaStateHolder::load_lua_file(std::string iFileName)
{
  if (luaL_loadfile(pLuaState_, iFileName.c_str()) || 
      lua_pcall(pLuaState_, 0, 0, 0)) {
    throw std::runtime_error(str(format("cannot run lua file: %1%") % lua_tostring(pLuaState_, -1)));
  }
}

void
LuaStateHolder::load_lua_engine_file(const char * iFileName)
{
  load_lua_file(dep_resolver_.get_engine_lua_file_name(iFileName));
}
