-- First puzzle to load in the game
set_puzzle_dimensions(3,4)

set_puzzle_rows({"###",
		 "--I",
		 "O--",
		 "###"})

set_puzzle_moves({Move.SINGLE})

add_puzzle_script(0,2,1);