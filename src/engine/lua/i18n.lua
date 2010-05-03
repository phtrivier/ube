package.path = ube_engine_lua_path or package.path

g_locale = nil

require "pdebug"

function compute_locale()
   pdbg("Calling C to get the locale ...")
   local l = cpp_get_locale_name()
   pdbg("Recevied full locale name " .. l)
   g_locale = string.lower(string.sub(l, 0, 2))
end

function i18n(message_map)

   if (g_locale == nil) then
      compute_locale()
   end

   pdbg("Computed locale : " .. g_locale)

   local res = "[Missing translation]"
   if (message_map[g_locale] ~= nil) then
      res = message_map[g_locale]
   else
      if (message_map['en'] ~= nil) then
	 res = message_map['en']
      end
   end
   
   return res

end