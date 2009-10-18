-- Illustrate how a story event can be called from outside ...

-- This would go in a library of some sort ... 
g_story_events = {}

function story_clear_events()
   g_story_events = {}
end

-- Declare a event to happen when a given cell is visited.
function story_event(cell_name, callback)
   g_story_events[cell_name] = callback;
end

-- Visit a cell. If an event has been declared for this cell, 
-- the associated callback is called.
function story_visit_cell(cell_name, puzzle)
   if (g_story_events[cell_name] ~= nil) then
      g_story_events[cell_name](puzzle);
   end
end
