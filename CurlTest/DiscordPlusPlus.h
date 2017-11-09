#pragma once
#include <iostream>
#include <map>
#include <vector>
#include "Structs.h"

namespace DiscordPlusPlus {
	class DiscordPlusPlus {
	private:
		std::string token;

		bool performRequest(std::map<std::string, std::string> *postfields, std::vector<std::string> *headers, std::string url);
		bool performRequest(std::map<std::string, std::string> *postfields, std::vector<std::string> *headers, std::string url, std::string);

	public:

		DiscordPlusPlus(std::string token);

		bool sendMessage(std::string message, Channel);
		// TODO: Work on making objects for differnet types: Guilds, Client, etc...
		// For all, add return to see if error

		bool setName(std::string name);

		bool leaveGuild(Guild);

		std::vector<Guild> getGuilds();

	};
}