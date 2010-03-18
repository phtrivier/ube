PickMoveScript = {}

function PickMoveScript:new(type) 
   o = {
      move_type = type,
      move_index = nil
   }
   setmetatable(o, self)
   self.__index = self
   return o
end

function PickMoveScript:execute(puzzle)
   print("executing pickmove cmd")
   self.move_index = cpp_puzzle_add_move(puzzle, self.move_type)
end

function PickMoveScript:undo(puzzle)
   print("undoing pickmove cmd")
   cpp_puzzle_remove_move(puzzle, self.move_index)
end

function add_move(i,j,type)
   add_script(i,j,PickMoveScript:new(type))
end