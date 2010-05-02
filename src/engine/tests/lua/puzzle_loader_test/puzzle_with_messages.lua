set_puzzle_rows({"###",
		 "--I",
		 "O0-",
		 "###"})

set_puzzle_moves({Move.SINGLE})

after_start_message({en = "Hello, world !"})

add_move_at_position(0,Move.DOUBLE, {en = "You just picked a move. Good for you !"})

before_end_message({en = "Thanks for playing !"})
