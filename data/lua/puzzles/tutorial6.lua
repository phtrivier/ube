-- First puzzle to load in the game
set_puzzle_rows({"######################",
		 "##---############---##",
		 "#--I----------#--1---#",
		 "#-----##########-----#",
		 "###-#####-----###-####",
		 "###-####---O---##-####",
		 "###-#####-----###-####",
		 "#-----##########----##",
		 "#--0--#####------2--##",
		 "##---############--###",
		 "######################"})

-- set_puzzle_moves({Move.SINGLE, Move.SINGLE}
set_puzzle_moves({Move.SINGLE, Move.SINGLE})


add_move_at_position(0, Move.DOUBLE)
add_move_at_position(1, Move.SINGLE)
add_move_at_position(2, Move.DOUBLE)

