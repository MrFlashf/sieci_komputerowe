require "socket"
require 'fileutils'

class Client

	SIZE = 1024*1024*10

	def initialize(server)
		@server   = server
		@request  = nil
		@response = nil
		connect
		listen
		send
		@request.join
		@response.join
	end

	def connect
		puts "Podaj swoj nick"
		nick = gets.chomp
		@server.puts(nick)
	end


	def listen 
		@response = Thread.new do 
			loop {
				msg = @server.gets.chomp
				# if checkIfFile(msg)
				# 	puts "Wysyła mi filea"
				# 	unless File.directory?("./#{@nick}_files")
				# 		fileutils.mkdir_p("./#{@nick}_files")
				# 	end
				# 	File.open("./#{@nick}_files/file#{@fileCounter}_#{checkFilePath(msg)}",'w')
				# 	while chunk = client.client.read(SIZE)
				# 		file.write(chunk)						
				# 	end
				# end
				puts "#{msg}"
			}
		end
	end

	def send
		@request = Thread.new do
			loop {
				msg = $stdin.gets.chomp
				# if checkIfFile(msg)
				# 	@server.puts "qqFILE: #{checkFilePath(msg)}"
				# 	puts readFile
				# 	@server.puts(readFile)
				# else
					@server.puts(msg)
				# end
			}
		end
	end

	# def readFile
	# 	ret = []
	# 	File.open("1.txt", "rb") do |file|
	# 		while chunk = file.read(SIZE)
	# 			ret.push(chunk)
	# 		end
	# 		file.close
	# 	end
	# 	return ret
	# end

	# def checkIfFile(msg)
	# 	return (/FILE:/ =~ msg.split[0]) == 0
	# end

	# def checkFilePath(msg)
	# 	return msg.split.slice(1,1).join
	# end

end

server = TCPSocket.open("localhost", 8000)
Client.new(server)