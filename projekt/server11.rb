require "socket"
require_relative "client"

class Server
	def initialize
		# setConnectionData
		puts "siema"
		gets
		@server      = TCPServer.open("127.0.0.1", 8000)
		@connections = Hash.new
		@clients	 = Hash.new
		@rooms		 = Hash.new
		setRooms
		@connections[:rooms]   = @rooms
		@connections[:server]  = @server
		@connections[:clients] = @clients
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

	# public def rooms
		# @rooms
	# end

	def run 
		loop {
			Thread.start(@server.accept) do |client|
				nick_name = client.gets.chomp.to_sym
				@connections[:clients].each do |other_nick, other_client|
					if nick_name == other_nick || client == other_client
						client.puts "Nick #{nick_name} jest już zajęty"
						Thread.kill self
					end
				end
				puts "Polaczono z #{nick_name}"
				@connections[:clients][nick_name] = client
				client.puts "Witaj #{nick_name}! Wpisz 'konkret: {nick}', zeby polaczyc sie z konkretna osoba, lub pisz normalnie, zeby wyslac do wszystkich"
				listen_user_messages(nick_name, client)
			end
		}.join
	end

	def listen_user_messages(username, client)
		loop {
			msg = client.gets.chomp
			if msg.start_with?("konkret: ")
				@connections[:clients].each do |other_nick, other_client|
					if other_nick.to_s == messageVsReceiver(msg)[0].to_s
						other_client.puts "#{username.to_s} (tylko do Ciebie): #{messageVsReceiver(msg)[1]}"
					end
				end
			else
				@connections[:clients].each do |other_nick, other_client|
					unless other_nick == username
						other_client.puts "#{username.to_s}: #{msg}"
					end
				end
			end
		}
	end

	def messageVsReceiver(msg)
		recvr = msg.split(/[\s\:]/)[2]
		msg   = msg.split(/[\s\:]/).slice(3,9999).join(' ')
		return [recvr, msg]
	end
end