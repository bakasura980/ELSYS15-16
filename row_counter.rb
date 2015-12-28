dir = ARGV[0].to_s
@rows = 0
@file = 0
MAX_ALL = 3000000
MAX_1 = 1000000

def input_check ext
	if ext.nil?
		ext = "rb cc cpp java"
		ext = ext.split
	else
		ext = ext.downcase.to_s
		if ext != 'rb' and ext != "cc" and ext != "cpp" and ext != "java"
			abort("You can search only for c++, ruby and java files!")
		end
	end
	ext
end
 
def row_counter file
	@file += 1
	counter = 0
	File.open(file, 'r').each do |line|
		counter += 1
	end
	return counter
end

input = input_check ARGV[1]

Dir.glob(dir + '*') do |e|
	se = e.split('/').last.split('.').last
	sum = 0
	if File.file? e
		if ARGV[1].nil?
			if input.include? se
				sum = row_counter e
				@rows += sum
				puts e.split('/').last+', >> '+sum.to_s
			end
		elsif se == input
			sum = row_counter e
			@rows += sum
			puts e.split('/').last+', >> '+sum.to_s
		end
	end
end

puts '------------------------------------'
puts 'Files checked: '+@file.to_s
if ARGV[1].nil?
	puts 'Rows '+input.join(' ')+' code: '+@rows.to_s
else
	puts 'Rows '+input+' code: '+@rows.to_s
end
puts '------------------------------------'
if input.kind_of?(Array) and @rows < MAX_ALL
	puts 'Rows left to 3M: '+(MAX_ALL - @rows).to_s
elsif @rows < MAX_1
	puts 'Rows left to 1M: '+(MAX_1 - @rows).to_s
end







