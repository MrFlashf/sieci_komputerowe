require "socket"
require 'fileutils'
require_relative "ClientClass"

class Server
	SIZE = 1014*1024*10
	def initialize
		# setConnectionData
		@server      = TCPServer.open("127.0.0.1", 8000)
		@connections = Hash.new
		@clients	 = Hash.new
		@rooms		 = Hash.new
		setRooms
		@fileCounter = 0
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

			# if checkIfFile(msg)
			# 	File.open('./serverFiles/plik.txt', 'w') do |file|
			# 		while filepart = client.client.gets
			# 			file.puts(filepart)
			# 		end
			# 		file.close
			# 	end
					
			# 	# File.open("./serverFiles/file#{@fileCounter}_#{checkFilePath(msg)}",'w') do |file|
			# 	# 	client.client.flush
			# 	# 	while chunki = client.client.read(SIZE)
			# 	# 		client.client.flush
			# 	# 		puts chunki
			# 	# 		file.write(chunki)						
			# 	# 	end
			# 	# 	file.close()
			# 	# end
				
			# 	# @clients.each do |other_nick, other_client|
			# 	# 	if other_client.room == client.room
			# 	# 		unless other_nick == username
			# 	# 			puts "Wysyłam pli9k do #{other_nick}"
			# 	# 			other_client.client.puts "qqFILE: {checkFilePath(msg)}"
			# 	# 			File.open("./serverFiles/file#{@fileCounter}_#{checkFilePath(msg)}", 'rb') do |file|
			# 	# 				while chunk = file.read(SIZE)
			# 	# 					@other_client.client.write(chunk)
			# 	# 				end
			# 	# 				file.close()
			# 	# 			end
			# 	# 		end
			# 	# 	end
			# 	# end		
			# else
				@clients.each do |other_nick, other_client|
					if other_client.room == client.room
						unless other_nick == username
							other_client.client.puts "#{username.to_s}: #{msg}"
						end
					end				
				end
			# end
		}
	end

	def checkIfFile(msg)
		return (/qqFILE:/ =~ msg.split[0]) == 0
	end

	def checkFilePath(msg)"./#{@nick}_files"
		return msg.split.slice(1,1).join
	end

end

Server.new