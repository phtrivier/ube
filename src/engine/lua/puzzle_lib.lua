-- Functions and stuff to compute paths in a puzzle
package.path = ube_engine_lua_path or package.path

require 'move'
require 'script'
require 'pick_move'

g_numbered_cells = {}

-- Set the dimension of globaly available puzzle.
function set_puzzle_dimensions(w,h)
   cpp_puzzle_set_dimensions(cpp_puzzle,w,h)
end

-- Ask the globally available puzzle loader
-- to set a row on the globally available puzzle.
function set_puzzle_rows(rows)

   g_numbered_cells = {}

   -- height
   h = #rows

   -- hopefully, the puzzles have the proper dimensions
   w = string.len(rows[1])

   set_puzzle_dimensions(w,h)

   for i,row in ipairs(rows) do
      actual_row = ""
      -- Note the position of any digit, and replace it with a '-'
      for j = 1, #row do
	 local c = row:sub(j,j)
	 if (is_digit(c)) then
	    g_numbered_cells[c] = { i = i-1, j = j-1 }
	    actual_row = actual_row .. "-"
	 else
	    actual_row = actual_row .. c
	 end
      end
      
      -- ipairs start indexing at 0. Pff. Whatever.
      cpp_puzzle_loader_set_row(cpp_puzzle, cpp_puzzle_loader, 
				i-1,actual_row)
   end
end

-- TODO(pht) : fix this for other digits ;)
function is_digit(str)
   local converted = tonumber(str)
   return (converted ~= nil and converted >= 0 and converted <= 9)
end

function set_puzzle_moves(moves)
   for i,move in ipairs(moves) do 
      cpp_puzzle_add_move(cpp_puzzle, move)
   end
end

function add_puzzle_script(i,j,index)
   cpp_puzzle_add_script(cpp_puzzle, cpp_puzzle_loader, i,j,index)
end

function add_overlay(i,j,type)
   cpp_puzzle_set_overlay(cpp_puzzle, i, j , type);
end

