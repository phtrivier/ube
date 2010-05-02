-- First puzzle to load in the game
set_puzzle_rows({"######################",
		 "######################",
		 "######################",
		 "##-----########-----##",
		 "#-------######-------#",
		 "#---I------------O---#",
		 "#-------######-------#",
		 "##-----########-----##",
		 "######################",
		 "######################",
		 "######################"})

set_puzzle_moves({Move.SINGLE})

after_start_message({en = "Welcome to UBE ! Can you reach the exit ?", 
		     fr = "Bienvenue dans UBE ! Pouvez vous atteindre la sortie ?"})

before_end_message({en = "Well done ! Now you can try another puzzle...",
		    fr = "Bien joué ! Maintenant essayez un autre puzzle..."})