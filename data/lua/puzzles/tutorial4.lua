-- First puzzle to load in the game
set_puzzle_rows({"___________-__________",
		 "________-__-__-_______",
		 "_________-_-_-________",
		 "__________---_________",
		 "______________-----___",
		 "I-----------_---O---__",
		 "______________-----___",
		 "__________---_________",
		 "_________-_-_-________",
		 "________-__-__-_______",
		 "___________-__________"})

set_puzzle_moves({Move.SINGLE, Move.SINGLE })

add_move(5,11,Move.DOUBLE, { en = "You picked another move. You can use it to reach the exit_!", 
			     fr = "Vous avez gagné un déplacement. Utilisez le pour atteindre la sortie_!"
			  })