-- Move types
-- This should be in sync with the Cpp side, 
-- at least for the well-known ones...
Move = {
   SINGLE = 0,
   DOUBLE = 1
}

-- TODO : make this more dynamic
Move.move_types = {}
Move.move_types[Move.SINGLE] = {}
Move.move_types[Move.DOUBLE] = {}
 
Move.move_types[Move.SINGLE].sp = function (i,j) 
				     return { { i + 1, j}, 
					      {i-1, j} , 
					      {i, j+1}, 
					      {i, j-1}}
				  end

Move.move_types[Move.DOUBLE].sp = function (i,j) 
				     return { { i + 2, j}, 
					      {i-2, j} , 
					      {i, j+2}, 
					      {i, j-2}}
				  end

-- TODO : make it easier to reference a move (the function is
-- all that's neede, really ? 


Move.sp = function (move_type, i, j) 
	     return Move.move_types[move_type].sp(i,j)
	  end