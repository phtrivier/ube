-- First puzzle to load in the game
set_puzzle_rows({"I_____________________",
		 "______________________",
		 "______________________",
		 "______________________",
		 "______________________",
		 "______________________",
		 "______________________",
		 "______________________",
		 "______________________",
		 "______________________",
		 "_____________________O"})

set_puzzle_moves({Move.SINGLE, Move.DOUBLE, Move.KNIGHT})

after_start_message({ en = "Hey, what are you doing here ? This is work in progress !!",
		      fr = "Hé, qu'est ce que vous faites là ? Ce niveau n'est pas fini !" })