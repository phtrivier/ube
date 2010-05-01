g_locale = nil

function compute_locale()
   g_locale = "en"
   -- Probably a very naïve way to compute the locale used by getext ... 
   -- Anyway, lets try it ! 
   potential_vars = {"LC_ALL", "LC_MESSAGES", "LANGUAGES", "LANG"}
   for i,var in ipairs(potential_vars) do
      if (os.getenv(var) ~= nil) then
	 g_locale = string.lower(string.sub(os.getenv(var), 0, 2))
	 break
      end
   end
end

function i18n(message_map)

   if (g_locale == nil) then
      compute_locale()
   end

   print("Computed locale : " .. g_locale)

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