#!/usr/bin/ruby
require "fileutils"

# TODO(pht) : validate input, parse args, etc...
# This should be the name of the header file
old_file_name = ARGV[0]
new_file_name = ARGV[1]

def klass_underscored_name(klass_file_name)
  tokens = klass_file_name.split(".")
  klass_underscored_name = tokens[0]
end

def klass_name(klass_file_name)
  klass_underscored_name = klass_underscored_name(klass_file_name)
  elements = klass_underscored_name.split("_")
  res = elements.collect { |s| s.capitalize } .join("")
  res
end

def sysp(cmd)
  puts (cmd)
  system(cmd)
end

Dir.glob("src/**/*.*pp").each do |file_name|
  puts  "Replacing in #{file_name} ..."
  cmd = "sed -i.bak -e 's/#{old_file_name}/#{new_file_name}/g' #{file_name}"
  sysp(cmd)

  cmd = "sed -i.bak -e 's/#{klass_name(old_file_name)}/#{klass_name(new_file_name)}/g' #{file_name}"
  sysp(cmd)

  cmd = "sed -i.bak -e 's/#{klass_underscored_name(old_file_name).upcase}/#{klass_underscored_name(new_file_name).upcase}/g' #{file_name}"
  sysp(cmd)

  if File.basename(file_name) == old_file_name
    new_name = File.dirname(file_name) + "/" + new_file_name
    puts "Renaming : #{file_name} to #{new_name}"
    FileUtils.mv(file_name, new_name)
  end

end

