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

after_start_message({en = "Welcome to UBE ! You are the little blue ball. The exit is on the other side. Simply point and click to reach the exit. Easy enough, right_?", 
		     fr = "Bienvenue dans UBE ! Vous êtes la petite bille bleue. La sortie est de l'autre côté. Cliquez sur la sortie pour l'atteindre. Pas trop dur_?"})

before_end_message({en = "Well done ! Have you noticed how your path has been highlighted ? Now, go on and try another puzzle...",
		    fr = "Bien joué ! Vous avez remarqué que votre chemin était tracé au fur et à mesure ? Maintenant essayez un autre niveau..."})