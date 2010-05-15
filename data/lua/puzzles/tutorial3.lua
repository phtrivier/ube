-- First puzzle to load in the game
set_puzzle_rows({"I-___________----_____",
		 "----------___-------__",
		 "__--_________----__-__",
		 "___-_-----_________-__",
		 "___-_-----------___-__",
		 "___-_-----_________-__",
		 "___-___-_____----__-__",
		 "___-___----------__-__",
		 "___-___-_____----__-__",
		 "___-___-___________-__",
		 "___-----___________--O"})

set_puzzle_moves({Move.DOUBLE, Move.SINGLE, Move.SINGLE })

before_end_message({en="You're starting to get it_! Let's continue...",
		    fr="Vous avez compris le truc_! Continuons..."})