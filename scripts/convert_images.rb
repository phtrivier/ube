#!/usr/bin/ruby

if (ARGV.size < 1)
  puts "Usage : ./scripts/convert_images.rb data/images"
  exit(1)
end

def convert_file(filename)
  basename = File.basename(filename, '.xcf')
  newname = File.dirname(filename) + "/../png/" + basename + ".png"
  cmd = "convert -flatten -background none #{filename} #{newname}" 
  puts(cmd)
  system(cmd)
end

def convert_known_xcf(name)
  convert_file("#{ARGV[0]}/xcf/#{name}")
end

["cell", "path", "move", "overlay"].each do |image_type|
  Dir.glob("#{ARGV[0]}/xcf/#{image_type}_*.xcf").each do |filename|
    convert_file(filename)
  end
end

convert_known_xcf("player.xcf")
convert_known_xcf("banned_cell.xcf")
convert_known_xcf("msg_box.xcf")
