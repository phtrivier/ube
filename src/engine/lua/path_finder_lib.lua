-- Functions and stuff to compute paths in a puzzle
package.path = ube_engine_lua_path or package.path

require 'agenda'
require 'node'
-- require 'queue'

function mark_nodes_from_path(puzzle, goal)
   local current = goal
   while (current ~= nil) do
      cpp_mark_cell_in_path(puzzle, current.i, current.j)
      current = current.parent
   end
end

-- path finder algorithm
function find_path(puzzle, i0,j0, i1,j1, move_type)

   print("Finding path between " .. i0..","..j0.." and "..i1..","..j1)

   local res = -1;

   local agenda = Agenda:new()
   local root = Node:new(i0,j0)
   agenda:put(root, 0)

   local reached_goal = nil
   local expected_goal = Node:new(i1,j1)

   local current = nil

   while (res == -1 and not agenda:is_empty()) do
      current = agenda:front();
      -- print("Checking node " .. current.i .. ",".. current.j)
      if (current:is_goal(i1,j1)) then
   	 reached_goal = current
   	 res = 1
      else
   	 successors = current:successors(puzzle, move_type)
   	 for k,successor in ipairs(successors) do
   	    i = successor.i
   	    j = successor.j
	    -- print("Generated successor " .. successor.i .. "," .. successor.j)
	    -- print("Checking if node " .. current.i .. "," .. current.j .. " has ancestor " .. i .. "," .. j)
   	    if (not current:has_ancestor_at(i,j)) then
   	       -- todo : how do I compute the priority ? 
   	       -- using the manhattan distance, for example ? 
	       -- print("Ancestor not found, adding successor")
   	       agenda:put(successor,
   	    		  successor:estimated_cost(expected_goal))
	    else
	       -- print("Ancestor found, skipping node")
   	    end

   	 end
      end
   end

   if (reached_goal == nil) then
      res = 0
   else
      mark_nodes_from_path(puzzle, reached_goal)
   end

   return res

end