-- First puzzle to load in the game
set_puzzle_rows({"I-###########----#####",
		 "----------###-------##",
		 "##--#########----##-##",
		 "###-#-----#########-##",
		 "###-#-----------###-##",
		 "###-#-----#########-##",
		 "###-###-#####----##-##",
		 "###-###----------##-##",
		 "###-###-#####----##-##",
		 "###-###-###########-##",
		 "###-----###########--O"})

set_puzzle_moves({Move.DOUBLE, Move.SINGLE, Move.SINGLE })

before_end_message({en="You're starting to get it_! Let's continue...",
		    fr="Vous avez compris le truc_! Continuons..."})