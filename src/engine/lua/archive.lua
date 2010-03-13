Archive = {
}

function Archive:new()
   o = {
      nodes = {}
   }
   setmetatable(o, self)
   self.__index = self
   return o
end

function Archive:visited(node)
   local i = node.i
   local j = node.j
   return self.nodes[i] ~= nil and self.nodes[i][j] == true
end

function Archive:put(node)
   local i = node.i
   local j = node.j
   if (self.nodes[i] == nil) then
      self.nodes[i] = {}
   end
   if (self.nodes[i][j] ~= true) then
      self.nodes[i][j] = true
   end
end