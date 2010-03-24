#!/usr/bin/ruby

if (ARGV.size < 0)
  puts "Usage : ./scripts/convert_images.rb data/images move"
end

["path", "move", "overlay"].each do |image_type|
  
  Dir.glob("#{ARGV[0]}/#{image_type}_*.xcf").each do |filename|
    basename = File.basename(filename, '.xcf')
    newname = File.dirname(filename) + "/" + basename + ".png"
    cmd = "convert -flatten #{filename} #{newname}" 
    puts(cmd)
    system(cmd)
  end

end
