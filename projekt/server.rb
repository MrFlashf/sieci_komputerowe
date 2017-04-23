require "socket"
require_relative "ClientClass"
class Server
	def initialize
		# setConnectionData
		@server      = TCPServer.open("localhost", 8000)
		@connections = Hash.new
		@clients	 = Hash.new
		@rooms		 = Hash.new
		setRooms
		# @connections[:rooms]   = @rooms
		# @connections[:server]  = @server
		# @connections[:clients] = @clients
		run
	end
	attr_reader :rooms  

	def setConnectionData
		print "Podaj IP: "
		@ip   = gets.chomp
		print "Podaj port: "
		@port = gets.chomp
	end

	def setRooms
		@rooms[1] = "Pokoik dla dzieci"
		@rooms[2] = "Rozmowy o motoryzacji"
		@rooms[3] = "Pasjonaci wedkarstwa"
		@rooms[4] = "Funboye AMD"
	end

	def run 
		loop {
			Thread.start(@server.accept) do |client|
				nick_name = client.gets.chomp.to_sym
				@clients.each do |other_nick, other_client|
					if nick_name == other_nick || client == other_client
						client.puts "Nick #{nick_name} jest już zajęty"
						Thread.kill self
					end
				end
				puts "Polaczono z #{nick_name}"

				client.puts "Wybierz pokoj: "
				@rooms.each do |room, room_name|
					client.puts "#{room}: #{room_name}"
				end

				room = Integer(client.gets.chomp)
				@clients[nick_name] = Client.new(nick_name, room, client)
				client.puts "Witaj #{nick_name}! Znajdujesz się w pokoju #{@rooms[room]}"
				listen_user_messages(nick_name, @clients[nick_name])
			end
		}.join
	end

	def listen_user_messages(username, client)
		loop {
			msg = client.client.gets.chomp
			@clients.each do |other_nick, other_client|
				if other_client.room == client.room
					unless other_nick == username
						other_client.client.puts "#{username.to_s}: #{msg}"
					end
				end				
			end
		}
	end
end

Server.new