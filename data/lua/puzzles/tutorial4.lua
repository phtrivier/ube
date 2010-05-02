-- First puzzle to load in the game
set_puzzle_rows({"###########-##########",
		 "########-##-##-#######",
		 "#########-#-#-########",
		 "##########---#########",
		 "##############-----###",
		 "I-----------#---O---##",
		 "##############-----###",
		 "##########---#########",
		 "#########-#-#-########",
		 "########-##-##-#######",
		 "###########-##########"})

set_puzzle_moves({Move.SINGLE, Move.SINGLE })

add_move(5,11,Move.DOUBLE, { en = "You picked another move. You can use it to reach the exit_!", 
			     fr = "Vous avez gagné un déplacement. Utilisez le pour atteindre la sortie_!"
			  })