#pragma once
#include <iostream>
#include <map>
#include <vector>

namespace DiscordPlusPlus {
	class DiscordPlusPlus {
	private:
		std::string token;

		bool performRequest(std::map<std::string, std::string> *postfields, std::vector<std::string> *headers, std::string url);

	public:
		DiscordPlusPlus(std::string token);
		
		bool sendMessage(std::string message, std::string guildId);
		// TODO: Work on making objects for differnet types: Guilds, Client, etc...
		// For all, add return to see if error

		
	};
}