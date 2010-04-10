-- Test of a puzzle file
set_puzzle_dimensions(3,4)

set_puzzle_rows({"###",
		 "#-O",
		 "I-#",
		 "###"})

set_puzzle_moves({Move.DOUBLE, Move.SINGLE})
