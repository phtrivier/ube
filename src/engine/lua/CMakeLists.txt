set(LUA_ENGINE_FILES agenda.lua archive.lua move.lua node.lua path_finder_lib.lua pick_move.lua puzzle_lib.lua queue.lua script.lua story_lib.lua)

install(FILES ${LUA_ENGINE_FILES}
        DESTINATION share/ube/lua/engine)