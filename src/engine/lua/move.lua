-- Move types
-- This should be in sync with the Cpp side, 
-- at least for the well-known ones...
Move = {
   SINGLE = 0,
   DOUBLE = 1,
   KNIGHT = 2,
}

Move.move_types = {}

Move.register_move = function (key, callback)
			Move.move_types[key] = {};
			Move.move_types[key].sp = callback
		     end

Move.sp = function (move_type, i, j) 
	     return Move.move_types[move_type].sp(i,j)
	  end

-- SINGLE MOVE (contiguous cells)
Move.register_move(Move.SINGLE, function (i,j) 
				     return { { i + 1, j}, 
					      {i-1, j} , 
					      {i, j+1}, 
					      {i, j-1}}
				  end)

-- DOUBLE MOVE (cells that are separated by only one cell)
Move.register_move(Move.DOUBLE, function (i,j) 
				     return { { i + 2, j}, 
					      {i-2, j} , 
					      {i, j+2}, 
					      {i, j-2}}
				  end)

Move.register_move(Move.KNIGHT, function (i,j) 
				     return { { i + 2, j + 1}, 
					      { i - 2, j + 1}, 
					      { i + 2, j - 1}, 
					      { i - 2, j - 1}, 
					      { i + 1, j + 2}, 
					      { i - 1, j + 2}, 
					      { i + 1, j - 2}, 
					      { i - 1, j - 2}}
				  end)


-- Move.move_types[Move.SINGLE] = {}
--Move.move_types[Move.DOUBLE] = {}
 
--Move.move_types[Move.SINGLE].sp = 
--Move.move_types[Move.DOUBLE].sp = 
-- TODO : make it easier to reference a move (the function is
-- all that's neede, really ? 

