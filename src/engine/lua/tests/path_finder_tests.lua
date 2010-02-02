package.path = package.path .. ";../?;../?.lua"
require "tests/luaunit"

require "path_finder_lib"

TestPathFinder = {}

-- A custom cpp_mark_cell_in_path function will
-- ignore the puzzle and put stuff in this list.
-- In real life, it would act on the cpp side puzzle.
g_nodes_in_path = {}

-- Mock version of the function to act on the puzzle
function cpp_mark_cell_in_path(puzzle, i, j)
   table.insert(g_nodes_in_path, { i, j })
end

-- A custom cpp_is_cell_reachable will look in this table
g_reachable_nodes = {}
-- Mock version of the function to state which node is
-- reachable
function cpp_is_cell_reachable(puzzle, i, j)
   return has_position(g_reachable_nodes, i ,j)
end

function has_position(list, i, j)
   local res = false
   for idx,position in ipairs(list) do
      if (position ~= -1) then
	 if (position[1] == i and position[2] == j) then
	    res = true
	 end
      end
   end
   return res
end

function TestPathFinder:testMockMarkCellWorks()
   g_nodes_in_path = {}
   cpp_mark_cell_in_path(nil, 1, 2)
   cpp_mark_cell_in_path(nil, 3, 4)
   assert(has_position(g_nodes_in_path, 1, 2))
   assert(has_position(g_nodes_in_path, 3, 4))
   assert(not has_position(g_nodes_in_path, 3, 5))
end

function TestPathFinder:testMockReachableCellWorks()
   g_reachable_nodes = { { 0, 0} , {0 , 1 } , 
			 { 1, 0} , {1 , 1 } }
   
   assert(has_position(g_reachable_nodes, 0,0))
   assert(not has_position(g_reachable_nodes, 0,3))

end

function TestPathFinder:testFindsSimplePath()
   g_reachable_nodes = { { 0, 0} , 
			 { 1, 0} , {1 , 1 } }
   assertEquals(1, find_path(nil, 0, 0, 1, 1, 0))
   assert(has_position(g_nodes_in_path, 0, 0))
   assert(has_position(g_nodes_in_path, 1, 0))
   assert(has_position(g_nodes_in_path, 1, 1))
end

function TestPathFinder:testFindsMoreComplicatedPath()
   g_nodes_in_path = {}
   g_reachable_nodes = { { 0, 0} , {0 , 1},
			 { 1, 0} , {1 , 1 } , { 1, 2 } ,
			 { 2, 0} , -1,       { 2, 2 } ,
			 -1,      {3,  1 } , { 3, 2 } ,
			 -1,      {4, 1 }
		      }

   assertEquals(1, find_path(nil, 0, 0, 4, 1, 0))

   --for k,v in ipairs(g_nodes_in_path) do
   --   print("node " .. v[1] .. "," .. v[2])
   --end
  
   assert(has_position(g_nodes_in_path, 0, 0))
   assert(has_position(g_nodes_in_path, 0, 1))
   assert(has_position(g_nodes_in_path, 1, 1))
   assert(has_position(g_nodes_in_path, 1, 2))
   assert(has_position(g_nodes_in_path, 2, 2))
   assert(has_position(g_nodes_in_path, 3, 2))
   assert(has_position(g_nodes_in_path, 3, 1))
   assert(has_position(g_nodes_in_path, 4, 1))

end


function TestPathFinder:testFindsMoreComplicatedPathWithDoubleJumps()
   g_nodes_in_path = {}
   g_reachable_nodes = { { 0, 0} , {0 , 1},
			 { 1, 0} , {1 , 1 } , { 1, 2 } ,
			 { 2, 0} , -1,       { 2, 2 } ,
			 -1,      {3,  1 } , { 3, 2 } ,
			 -1,      {4, 1 }
		      }

   assertEquals(1, find_path(nil, 0, 0, 2, 2, 1))
   assert(has_position(g_nodes_in_path, 0, 0))
   assert(has_position(g_nodes_in_path, 2, 0))
   assert(has_position(g_nodes_in_path, 2, 2))
end



-- todo : something to test ? 
LuaUnit:run()