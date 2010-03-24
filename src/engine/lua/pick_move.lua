PickMoveScript = {}

function PickMoveScript:new(i,j,type) 
   o = {
      i = i,
      j = j,
      move_type = type,
      move_index = nil
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
end

function PickMoveScript:undo(puzzle)
   print("undoing pickmove cmd")
   cpp_puzzle_remove_move(puzzle, self.move_index)
   cpp_puzzle_set_overlay(puzzle, self.i, self.j, self.move_type);
end

function add_move(i,j,type)
   add_script(i,j,PickMoveScript:new(i,j,type))
   add_overlay(i,j,type)
end
