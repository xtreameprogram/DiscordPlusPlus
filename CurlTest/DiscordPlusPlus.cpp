#include "DiscordPlusPlus.h"
#include "curl.h"
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "Structs.h"
#include "Request.h"


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

bool DiscordPlusPlus::DiscordPlusPlus::performRequest(std::map<std::string, std::string> *postfields, std::vector<std::string> *headers, std::string url, Request r)
{

	std::map<Request, const char*> methods;
	methods.insert(std::make_pair(GET, "GET"));
	methods.insert(std::make_pair(POST, "POST"));
	methods.insert(std::make_pair(PUT, "PUT"));

	

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



/*******************************************


PUBLIC


********************************************/


bool DiscordPlusPlus::DiscordPlusPlus::sendMessage(std::string mess, std::string id) {
	std::map<std::string, std::string> fields;
	fields.insert(std::pair<std::string, std::string>("content", mess));

	return DiscordPlusPlus::performRequest(&fields, NULL, "https://discordapp.com/api/v6/channels/" + id + "/messages");
}

bool DiscordPlusPlus::DiscordPlusPlus::setName(std::string name) {
	
	
	return true;
}


DiscordPlusPlus::DiscordPlusPlus::DiscordPlusPlus(std::string token)
{
	this->token = token;
}
