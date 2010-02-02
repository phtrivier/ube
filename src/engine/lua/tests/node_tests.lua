if ube_engine_lua_path then
   package.path = package.path .. ";../?;../?.lua" .. ube_engine_lua_path
else
   package.path = package.path .. ";../?;../?.lua"
end

require "move"
require "node"
require "luaunit"

TestNode = {}

function TestNode:testIsGoal()
   n = Node:new(1,2)
   assert(not n:is_goal(1,3))
   assert(n:is_goal(1,2))
end

function TestNode:testSuccessorPositions()
   n = Node:new(1,2)
   positions = n:successor_positions(Move.SINGLE)
   assertEquals(2, positions[1][1]);
   assertEquals(2, positions[1][2]);
   assertEquals(0, positions[2][1]);
   assertEquals(2, positions[2][2]);
   assertEquals(1, positions[3][1]);
   assertEquals(3, positions[3][2]);
   assertEquals(1, positions[4][1]);
   assertEquals(1, positions[4][2]);
end

function TestNode:testSuccessorPositionsForDouble()
   n = Node:new(1,2)
   positions = n:successor_positions(Move.DOUBLE)
   assertEquals(3, positions[1][1]);
   assertEquals(2, positions[1][2]);
   assertEquals(-1, positions[2][1]);
   assertEquals(2, positions[2][2]);
   assertEquals(1, positions[3][1]);
   assertEquals(4, positions[3][2]);
   assertEquals(1, positions[4][1]);
   assertEquals(0, positions[4][2]);
end

function cpp_is_cell_reachable(puzzle, i, j)
   return (i == 2 and j == 2) 
end

function TestNode:testComputeSuccessors()
   local n = Node:new(1,2)
   local succs = n:successors(nil, Move.SINGLE)

   local s = succs[1]
   assert(s ~= nil)
   assertEquals(2, s.i)
   assertEquals(2, s.j)
   assertEquals(n, s.parent) 
end

function TestNode:testWhetherNodeIsAncestor()

   n1 = Node:new(1,2)
   n2 = Node:new(3, 4, n1)
   n3 = Node:new(5, 6, n2)
   
   assertEquals(n2, n3.parent)
   assertEquals(n1, n3.parent.parent)
   assertEquals(1, n3.parent.parent.i)
   assertEquals(2, n3.parent.parent.j)

   assert(n3:has_ancestor_at(1,2))
   assert(n2:has_ancestor_at(1,2))
   assert(n3:has_ancestor_at(3,4))
   assert(not n3:has_ancestor_at(3,5))

end

function TestNode:testComputesEstimatedCostForNodes()

   n1 = Node:new(1,2)
   assertEquals(0, n1.cost_from_start)
   n2 = Node:new(3,4, n1)
   assertEquals(1, n2.cost_from_start)

   goal = Node:new(3,4)
   assertEquals(1, n2.cost_from_start)
   assertEquals(0, n2:heuristic_cost_to_goal(goal))
   assertEquals(1, n2:estimated_cost(goal))

   goal = Node:new(5,6)
   assertEquals(1, n2.cost_from_start)
   assertEquals(4, n2:heuristic_cost_to_goal(goal))
   assertEquals(5, n2:estimated_cost(goal))

   n3 = Node:new(5,6, n2)
   assertEquals(2, n3.cost_from_start)
   assertEquals(0, n3:heuristic_cost_to_goal(goal))
   assertEquals(2, n3:estimated_cost(goal))
  

end

LuaUnit:run()