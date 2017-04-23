class Client
	def initialize(nick, room, client)
		@nick   = nick
		@room   = room
		@client = client
	end

	def room
		@room
	end

	def client
		@client
	end
end