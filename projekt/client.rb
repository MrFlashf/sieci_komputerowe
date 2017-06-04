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
		@nick = gets.chomp
		@server.puts(@nick)
	end


	def listen 
		@response = Thread.new do 
			loop {
				msg = @server.gets.chomp
				if check_if_file(msg)
					path = check_file_path(msg)
					#tworzymy katalog użytkownika
					unless File.directory?("./#{@nick}_files")
						FileUtils::mkdir_p "./#{@nick}_files"
					end

					file = File.open("./#{@nick}_files/#{path}", 'w')
					while (m = @server.gets)
						if m.chomp != 'end'
							file.write m
						else
							file.close
							break
						end
					end
				else
					puts "#{msg}"
				end
			}
		end
	end

	def send
		@request = Thread.new do
			loop {
				puts "Podaj wiadomość: "
				msg = $stdin.gets.chomp
				if check_if_file(msg)
					path = check_file_path(msg)
					@server.puts "qqFILE: #{path}"
					file = File.open(path, 'rb')
					while chunk = file.read(SIZE)
						@server.puts(chunk)
					end
					file.close
					@server.puts "end"

				else
					@server.puts(msg)
				end
			}
		end
	end

	def check_if_file(msg)
		(/FILE:/ =~ msg.split[0]) == 0
	end

	def check_file_path(msg)
		msg.split.slice(1,1).join
	end

end

server = TCPSocket.open('127.0.0.1', 8000)
Client.new(server)