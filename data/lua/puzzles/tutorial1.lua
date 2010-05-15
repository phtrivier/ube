-- First puzzle to load in the game
set_puzzle_rows({"I----------___________",
		 "__________-___________",
		 "_________---__________",
		 "______________________",
		 "______---------_____O_",
		 "____________________-_",
		 "__________-_______-_-_",
		 "______________________",
		 "________-----_____-___",
		 "______________________",
		 "__________-_-_-_-_-___"})

set_puzzle_moves({Move.SINGLE, Move.DOUBLE})

after_start_message({en = "The buttons at the bottom are your possible moves. The yellow moves lets you move two cells at a time. You'll need it",
		     fr = "Les bouttons en bas de l'écran sont vos différents mouvements possibles. Avec le jaune, vous pouvez avancer de deux cases à la fois. Vous en aurez besoin..."})
