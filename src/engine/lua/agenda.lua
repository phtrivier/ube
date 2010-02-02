-- Agenda class for the search
-- Elements should be nodes
Agenda = { 
}

-- Strange syntax for a constructor ... 
function Agenda:new()
   
   o = {
      lower_cost = nil,
      elements = {}
   }

   setmetatable(o, self)
   self.__index = self
   return o
end

function Agenda:clear()
   self.elements = {}
   self.lower_cost = nil
end

function Agenda:is_empty() 
   return next(self.elements) == nil;
end

function Agenda:put(item, cost)
   if (self.elements[cost] == nil) then
      self.elements[cost] = {}
   end

   if (self.lower_cost == nil or cost < self.lower_cost) then
      self.lower_cost = cost
   end

   table.insert(self.elements[cost],item)
end

function Agenda:front()

   res = table.remove(self.elements[self.lower_cost],1)

   if (next(self.elements[self.lower_cost]) == nil) then
      self:update_lower_cost()
   end
   return res
end

function Agenda:update_lower_cost()
   self.elements[self.lower_cost] = nil
   self.lower_cost = nil
   for cost, items in pairs(self.elements) do
      if (self.lower_cost == nil or cost < self.lower_cost) then
	 self.lower_cost = cost
      end
   end

end
