-- First puzzle to load in the game
set_puzzle_dimensions(10,10)

set_puzzle_rows({"----------",
		 "----------",
		 "----------",
		 "--------O-",
		 "----------",
		 "-I--------",
		 "----------",
		 "----------",
		 "----------",
		 "----------"})

set_puzzle_moves({Move.SINGLE, Move.DOUBLE, Move.SINGLE})