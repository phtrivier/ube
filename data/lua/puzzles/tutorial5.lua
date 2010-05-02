-- First puzzle to load in the game
set_puzzle_rows({"######################",
		 "##---############---##",
		 "#--0----------#--1---#",
		 "#-----##########-----#",
		 "###-#####-----###-####",
		 "###-####---O---##-####",
		 "###-#####-----###-####",
		 "#-----##########----##",
		 "#--I--#####------2--##",
		 "##---############--###",
		 "######################"})

-- set_puzzle_moves({Move.SINGLE, Move.SINGLE}
set_puzzle_moves({Move.SINGLE, Move.SINGLE})


add_move_at_position(0, Move.DOUBLE)
add_move_at_position(1, Move.SINGLE)
add_move_at_position(2, Move.DOUBLE)

after_start_message({en = "Sometimes, there is more than one solution...",
		     fr = "Parfois, il y a plusieurs solutions..."})
