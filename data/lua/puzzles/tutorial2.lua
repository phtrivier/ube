-- First puzzle to load in the game
set_puzzle_rows({"----------____________",
		 "-I---------___________",
		 "--------------------__",
		 "----------------------",
		 "_---------____________",
		 "________--_-----------",
		 "________--_-----------",
		 "________--_-----------",
		 "________--_-----------",
		 "________--_---------O-",
		 "_________-_-----------"})

set_puzzle_moves({Move.SINGLE, Move.SINGLE, Move.DOUBLE})

after_start_message({en = "If you ever make a mistake, you can use the arrows at the bottom to undo or redo, as many times as you want_!",
		     fr = "Si vous pensez vous être trompé, pas de panique_! Les deux flèches en bas à gauche vous permettent de revenir en arrière autant de fois que vous voulez_!"})