package.path = package.path .. ";../?;../?.lua"

require "agenda"
require "luaunit"

TestAgenda = {}

function TestAgenda:testIsEmptyAtStart()
   a = Agenda:new()
   assert(a.elements ~= nil)
   assert(a:is_empty())
end

function TestAgenda:testElementsAreAddedInFront()
   a = Agenda:new()
   a:put("toto", 12)
   assertEquals(12, a.lower_cost)
   a:put("tata", 12)
   assertEquals(12, a.lower_cost)
   a:put("tutu", 15)
   assertEquals(12, a.lower_cost)
   assertEquals("toto", a.elements[12][1])
   assertEquals("tata", a.elements[12][2])
   assertEquals("tutu",a.elements[15][1])
   assertEquals(nil, a.elements[42])
end

function TestAgenda:testElementsArePopedFromFront()
   a = Agenda:new()
   a:put("toto", 12)
   a:put("tata", 15)
   a:put("tutu", 15)

   assert(not a:is_empty())

   f = a:front()
   assertEquals("toto",f)
   assertEquals(15, a.lower_cost)
   assertEquals(nil, a.elements[12])

   f = a:front()
   assertEquals("tata",f)
   
   f = a:front()
   assertEquals("tutu",f)

   assert(a:is_empty())

end

LuaUnit:run()
