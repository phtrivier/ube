#!/usr/bin/env ruby
require "fileutils"

if ARGV[0] == nil || ARGV[0].to_i == nil
  puts "Give a number to the move"
  exit(1)
end

nb = ARGV[0]

["move_X", "move_X_grayed", "overlay_move_X", "path_X"].each do |s|
  old = "data/images/xcf/#{s.gsub('X', '0')}.xcf"
  new = "data/images/xcf/#{s.gsub('X', nb)}.xcf"
  puts "old : #{old}"
  puts "new : #{new}"
  FileUtils.cp(old, new)
end

