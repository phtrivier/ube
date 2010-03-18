-- First puzzle to load in the game
set_puzzle_dimensions(3,4)

set_puzzle_rows({"###",
		 "--I",
		 "O--",
		 "###"})

set_puzzle_moves({Move.SINGLE})


-- FIXME(pht) : of course, re-arrange this
-- register_script(1, PickMoveScript:new(Move.DOUBLE))
-- add_puzzle_script(0,2,1);
add_move(0,2,Move.DOUBLE)
add_move(1,1,Move.SINGLE)
