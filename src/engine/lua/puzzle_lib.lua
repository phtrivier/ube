-- Set the dimension of globaly available puzzle.
function set_puzzle_dimensions(w,h)
   cpp_puzzle_set_dimensions(cpp_puzzle,w,h)
end

-- Ask the globally available puzzle loader
-- to set a row on the globally available puzzle.
function set_puzzle_rows(rows)
   for i,row in ipairs(rows) do
      -- ipairs start indexing at 0. Pff. Whatever.
      cpp_puzzle_loader_set_row(cpp_puzzle, cpp_puzzle_loader, 
				i-1,row)
   end
end