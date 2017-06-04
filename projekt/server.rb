require "socket"
require 'fileutils'
require_relative "ClientClass"

class Server
	SIZE = 1014*1024*10
	def initialize
		# setConnectionData
		@server      = TCPServer.open("127.0.0.1", 8000)
		@connections = Hash.new
		@clients		 = Hash.new
		@rooms		 	 = Hash.new
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
			msg = client.client.gets

			if check_if_file(msg)
				file_name = check_file_path(msg, false)
				path = check_file_path(msg, true)

				file = File.open(path, 'w')
				while (m = client.client.gets)
					if m.chomp != 'end'
						file.write m
					else
						file.close
						break
					end
				end
				#send file to clients in room

				@clients.each do |other_nick, other_client|
					if other_client.room == client.room
						unless other_nick == username
							other_client.client.puts "FILE: #{file_name}"
							file = File.open(path, 'rb')
							while chunk = file.read(SIZE)
								other_client.client.puts(chunk)
							end
							file.close
							other_client.client.puts "end"
						end
					end
				end

			else
				@clients.each do |other_nick, other_client|
					if other_client.room == client.room
						unless other_nick == username
							other_client.client.puts "#{username.to_s}: #{msg}"
						end
					end				
				end
			end
		}
	end

	def check_if_file(msg)
		return (/qqFILE:/ =~ msg.split[0]) == 0
	end

	def check_file_path(msg, flag)
		if flag
			'./server-files/' + msg.split.slice(1,1).join
		else
			msg.split.slice(1,1).join
		end
	end

end

Server.new