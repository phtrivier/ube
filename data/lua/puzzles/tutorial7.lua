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
		 "#####----0####----####",
		 "######################"})

set_puzzle_moves({Move.SINGLE, Move.DOUBLE })

add_move_at_position(0,Move.SINGLE)

after_start_message({en = "It's time for the last puzzle...",
		     fr = "On en arrive au dernier niveau..."})

before_end_message({ en = "This tutorial is now over. Thanks for playing !",
		     fr = "Ce tutoriel est maintenant fini. Merci d'avoir joué !"})

