-- First puzzle to load in the game
set_puzzle_rows({"______________________",
		 "__---____________---__",
		 "_--0----------_--1---_",
		 "_-----__________-----_",
		 "___-_____-----___-____",
		 "___-____---O---__-____",
		 "___-_____-----___-____",
		 "_-----__________----__",
		 "_--I--_____------2--__",
		 "__---____________--___",
		 "______________________"})

-- set_puzzle_moves({Move.SINGLE, Move.SINGLE}
set_puzzle_moves({Move.SINGLE, Move.SINGLE})


add_move_at_position(0, Move.DOUBLE)
add_move_at_position(1, Move.SINGLE)
add_move_at_position(2, Move.DOUBLE)

after_start_message({en = "Sometimes, there is more than one solution...",
		     fr = "Parfois, il y a plusieurs solutions..."})
