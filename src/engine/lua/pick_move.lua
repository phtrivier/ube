package.path = ube_engine_lua_path or package.path

require 'i18n'

PickMoveScript = {}

function PickMoveScript:new(i,j,type, message_map) 
   o = {
      i = i,
      j = j,
      move_type = type,
      message_map = message_map,
      move_index = nil,
      message_displayed = false
   }
   -- NOte : move types and overlay types are
   -- supposed to be the same
   setmetatable(o, self)
   self.__index = self
   return o
end

function PickMoveScript:execute(puzzle)
   print("executing pickmove cmd at " .. self.i .. "," .. self.j)
   self.move_index = cpp_puzzle_add_move(puzzle, self.move_type)
   cpp_puzzle_set_overlay(puzzle, self.i, self.j, -1);

   if ((not self.message_displayed) and (self.message_map ~= nil)) then
      cpp_puzzle_set_script_message(puzzle, i18n(self.message_map))
      self.message_displayed = true
   end
end

function PickMoveScript:undo(puzzle)
   print("undoing pickmove cmd")
   cpp_puzzle_remove_move(puzzle, self.move_index)
   cpp_puzzle_set_overlay(puzzle, self.i, self.j, self.move_type);
end

function add_move(i,j,type, message_map)
   add_script(i,j,PickMoveScript:new(i,j,type, message_map))
   add_overlay(i,j,type)
end

function add_move_at_position(position_number, type, message_map)
   local pos = string.format("%d", position_number)
   if (g_numbered_cells[pos] ~= nil) then
      print("g_numbered_cells[pos][i] " .. position_number .. " : " .. g_numbered_cells[pos]["i"])
      print("g_numbered_cells[pos][i] " .. position_number .. " : " .. g_numbered_cells[pos]["j"])
      i = g_numbered_cells[pos]["i"]
      j = g_numbered_cells[pos]["j"]
      add_move(i,j,type, message_map)
   end
end