-- First puzzle to load in the game
set_puzzle_dimensions(3,4)

set_puzzle_rows({"###",
		 "--I",
		 "O--",
		 "###"})

set_puzzle_moves({Move.SINGLE})

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

-- FIXME(pht) : of course, re-arrange this
register_script(1, PickMoveScript:new(Move.DOUBLE))
add_puzzle_script(0,2,1);