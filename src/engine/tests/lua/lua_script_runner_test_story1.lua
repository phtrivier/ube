-- This would go in the individual script
story_event ("toto", function (puzzle) 
			print "Toto handler"
			-- Note that puzzle here is just
			-- a user data, not every thing
			-- can be called on it...
			print(puzzle)
			puzzle_set_name(puzzle, "Baz")
		     end)

story_event ("tata", function (puzzle) 
			print "Tata handler"
			puzzle_set_name(puzzle, "Bar")
		     end)
