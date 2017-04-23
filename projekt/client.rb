require "socket"

class Client
	def initialize(server)
		@server   = server
		@request  = nil
		@response = nil
		connect
		# changeRoom
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

	def changeRoom
		puts "Wybierz jeden z pokoi:"
		# @serverClass.rooms().each do |room_nr, room_name|
			puts "#{room_nr}: #{room_name}"
		
	end

	def listen 
		@response = Thread.new do 
			loop {
				msg = @server.gets.chomp
				puts "#{msg}"
			}
		end
	end

	def send
		@request = Thread.new do
			loop {
				msg = $stdin.gets.chomp
				# q 	= getHeader(msg)[:header].to_s || q
				# msg = "#{q} #{msg}"
				@server.puts(msg)
			}
		end
	end
end

server = TCPSocket.open("localhost", 8000)
Client.new(server)