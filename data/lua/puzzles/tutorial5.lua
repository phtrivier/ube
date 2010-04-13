-- First puzzle to load in the game
set_puzzle_rows({"######################",
		 "#####-------#-----####",
		 "#####-###########-####",
		 "#####-###########-####",
		 "#####-###########-####",
		 "#####---I#####O---####",
		 "#####-###########-####",
		 "#####-###########-####",
		 "#####-###########-####",
		 "#####-----####----####",
		 "######################"})

set_puzzle_moves({Move.SINGLE, Move.DOUBLE })

add_move(9,9,Move.SINGLE)