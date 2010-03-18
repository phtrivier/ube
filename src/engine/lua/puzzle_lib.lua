-- Functions and stuff to compute paths in a puzzle
package.path = ube_engine_lua_path or package.path

require 'move'

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

function set_puzzle_moves(moves)
   for i,move in ipairs(moves) do 
      cpp_puzzle_add_move(cpp_puzzle, move)
   end
end

function add_puzzle_script(i,j,index)
   cpp_puzzle_add_script(cpp_puzzle, cpp_puzzle_loader, i,j,index)
end