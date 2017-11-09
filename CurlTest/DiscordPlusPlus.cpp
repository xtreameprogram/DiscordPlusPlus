#include "DiscordPlusPlus.h"
#include "curl.h"
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "Structs.h"


/*******************************************


PRIVATE


********************************************/

size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp)
{
	return size * nmemb;
}

bool DiscordPlusPlus::DiscordPlusPlus::performRequest(std::map<std::string, std::string> *postfields, std::vector<std::string> *headers, std::string url)
{
	CURL *curl;
	CURLcode res;


	curl_global_init(CURL_GLOBAL_ALL);

	curl = curl_easy_init();
	if (curl) {

		struct curl_slist *chunk = NULL;

		std::string tokenAPI = std::string("Authorization: Bot ") + std::string(this->token);
		
		if (headers != nullptr) {
			for (std::string header : *headers) {
				chunk = curl_slist_append(chunk, header.c_str());
			}
		}

		std::string posts;

		if (postfields != nullptr) {
			std::map<std::string, std::string>::iterator it = (*postfields).begin();
			while (it != (*postfields).end())
			{
				std::string part1 = it->first;
				std::string part2 = it->second;

				posts += part1 + "=" + part2 + "&";

				it++;
			}


			//printf("%s\n", );
			curl_easy_setopt(curl, CURLOPT_COPYPOSTFIELDS, posts.c_str());
		}

		//std::cout << posts;
		
		chunk = curl_slist_append(chunk, tokenAPI.c_str());

		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, FALSE);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);


		res = curl_easy_perform(curl);

		if (res != CURLE_OK)
			return false;


		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();
	return true;
}

bool DiscordPlusPlus::DiscordPlusPlus::performRequest(std::map<std::string, std::string> *postfields, std::vector<std::string> *headers, std::string url, std::string r)
{

	CURL *curl;
	CURLcode res;


	curl_global_init(CURL_GLOBAL_ALL);

	curl = curl_easy_init();
	if (curl) {

		struct curl_slist *chunk = NULL;

		std::string tokenAPI = std::string("Authorization: Bot ") + std::string(this->token);

		if (headers != nullptr) {
			for (std::string header : *headers) {
				chunk = curl_slist_append(chunk, header.c_str());
			}
		}

		std::string posts;

		if (postfields != nullptr) {
			std::map<std::string, std::string>::iterator it = (*postfields).begin();
			while (it != (*postfields).end())
			{
				std::string part1 = it->first;
				std::string part2 = it->second;

				posts += part1 + "=" + part2 + "&";

				it++;
			}


			//printf("%s\n", );
			curl_easy_setopt(curl, CURLOPT_COPYPOSTFIELDS, posts.c_str());
		}

		//std::cout << posts;

		chunk = curl_slist_append(chunk, tokenAPI.c_str());

		curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, r.c_str());
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, FALSE);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);


		res = curl_easy_perform(curl);

		if (res != CURLE_OK)
			return false;


		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();
	return true;
}



/*******************************************


PUBLIC


********************************************/


bool DiscordPlusPlus::DiscordPlusPlus::sendMessage(std::string mess, Channel channel) {
	std::map<std::string, std::string> fields;
	fields.insert(std::pair<std::string, std::string>("content", mess));

	return DiscordPlusPlus::performRequest(&fields, NULL, "https://discordapp.com/api/v6/channels/" + channel.id + "/messages");
}


//I could not for the life of me figure out a better way (in like 5 mins) so this is what I did
//TODO: Figure out how to utilize previous things because this is forsing JSON
//If there is another like this, maybe make a function sendJSON()
bool DiscordPlusPlus::DiscordPlusPlus::setName(std::string name) {
	CURL *curl;
	CURLcode res;


	curl_global_init(CURL_GLOBAL_ALL);

	curl = curl_easy_init();
	if (curl) {

		struct curl_slist *chunk = NULL;

		std::string tokenAPI = std::string("Authorization: Bot ") + std::string(this->token);

		chunk = curl_slist_append(chunk, tokenAPI.c_str());
		chunk = curl_slist_append(chunk, "Content-Type: application/json");

		curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PATCH");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
		curl_easy_setopt(curl, CURLOPT_URL,"https://discordapp.com/api/v6/users/@me");
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, FALSE);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);

		std::string go_to_hell = std::string("{\"username\":\"" + name + "\"}");

		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, go_to_hell.c_str());

		res = curl_easy_perform(curl);

		if (res != CURLE_OK)
			return false;


		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();
	return true;
}


bool DiscordPlusPlus::DiscordPlusPlus::leaveGuild(Guild guild)
{
	std::string str = std::string("https://discordapp.com/api/v6/users/@me/guilds/" + guild.id);

	return DiscordPlusPlus::performRequest(NULL, NULL, str.c_str(), "DELETE");
}

//TODO: Implmenet
std::vector<DiscordPlusPlus::Guild> DiscordPlusPlus::DiscordPlusPlus::getGuilds()
{
	return std::vector<Guild>();
}




DiscordPlusPlus::DiscordPlusPlus::DiscordPlusPlus(std::string token)
{
	this->token = token;
}
