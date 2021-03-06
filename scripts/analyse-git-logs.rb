#! /usr/bin/env ruby
# 
# This is a silly script to extract some very rude timing information
# from bzr or git commit logs.
#
# Authors PH TRIVIER
#

require "fileutils"

days = { }

LOG_FILE_NAME = ".commit-logs"

SCM = ARGV[0] || "git"

if (SCM == "bzr")
  system('bzr log > ' + LOG_FILE_NAME)
else
  system('git log --pretty=format:"%ci" > ' + LOG_FILE_NAME)
end

File.open(LOG_FILE_NAME) do |file|

  file.each_line do |line|
    m = line.match("(20..-[0-9]{2}-[0-9]{2})\ ([0-9:]{8})")
    if (m!=nil)
      if (!days[m[1]])
        days[m[1]] = []
      end
      days[m[1]] << m[2]
    end
  end

end

global_commit_count = 0
HOURS_PER_COMMIT = 1
hours = 0
days_count = days.keys.size
days.keys.sort.each do |key|
  commits = days[key]
  puts "Worked on #{key}, made #{commits.size} commit(s)."
  hours = hours + HOURS_PER_COMMIT * commits.size
  global_commit_count = global_commit_count + commits.size
end

puts "------- Summary -----"
puts "Worked on #{days_count} different days, made #{global_commit_count} commits. (On average #{global_commit_count / days_count} commits / day.)"
puts "Averaging at #{HOURS_PER_COMMIT} hours / commit, that would make #{hours} hours of work ; and an average of #{hours / days_count} hours/day. \nAlthough it sure doesn't mean anything. \nWorking 7 hours a day, it could have been done in #{hours / 7} days."

FileUtils.rm_rf(LOG_FILE_NAME)
