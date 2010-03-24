g_scripts = {};
g_next_script_index = 1;

function register_script(index, script)
   print("Registering script at index " .. index)
   g_scripts[index] = script;
end

function do_script(index, puzzle)
   print("Doing script at " .. index)
   if (g_scripts[index] ~= nil) then
      g_scripts[index]:execute(puzzle)
   end
end

function undo_script(index, puzzle)
   print("Undoing script at " .. index)
   if (g_scripts[index] ~= nil) then
      g_scripts[index]:undo(puzzle)
   end
end

function add_script(i,j,script)
   local script_index = g_next_script_index
   g_next_script_index = g_next_script_index + 1
   register_script(script_index, script)
   add_puzzle_script(i,j,script_index)
end