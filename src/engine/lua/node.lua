package.path = ube_engine_lua_path or package.path

require "move"

-- Node
Node = {
}

function Node:new(i,j,parent)
   o = {
      i = i or -1,
      j = j or -1,
      parent = parent or nil,
   }

   if (o.parent == nil) then
      o.cost_from_start = 0
   else
      o.cost_from_start = o.parent.cost_from_start + 1
   end
   
   setmetatable(o, self)
   self.__index = self
   return o
end

function Node:is_goal(i,j)
   return self.i == i and self.j == j
end

function Node:successor_positions(move_type)
   return Move.sp(move_type, self.i, self.j)
end

function Node:successors(puzzle, move_type)
   local res = {}
   for k,position in ipairs(self:successor_positions(move_type)) do
      i = position[1]
      j = position[2]
      if (cpp_is_cell_reachable(puzzle, i,j)) then
	 -- print("Sucessor found at "..i..","..j)
   	 table.insert(res, Node:new(i,j,self))
      else
	 -- print("Cell not reachabile at "..i..","..j)
      end
   end
   return res
end

-- Uses manhattan distance
function Node:heuristic_cost_to_goal(goal)
   return math.abs(goal.i - self.i) + math.abs(goal.j - self.j)
end

-- Sum of the cost to reach this node, 
-- and the estimation of the cost to the goal.
function Node:estimated_cost(goal)
   return self.cost_from_start + self:heuristic_cost_to_goal(goal)
end

-- True if we already have another
-- node with the same position
-- in our ancestors
function Node:has_ancestor_at(other_i, other_j)
   found = false
   finished = false
   current = self.parent
   while (not found and current ~= nil) do
      if (other_i == current.i and other_j == current.j) then
	 found = true
      else
	 current = current.parent
      end
   end
   return found
end

-- Still TODO : Add the estimated cost and the heuristic in 
-- the node, and compute the priority ; 
-- plus add the node with the proper cost, 
-- or something like that ... or generate the successors
-- with their heuristic values