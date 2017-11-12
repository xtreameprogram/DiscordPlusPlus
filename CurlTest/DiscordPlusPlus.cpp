#include "DiscordPlusPlus.h"
#include "curl.h"
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "Structs.h"
#include "json.hpp"

/*******************************************


PRIVATE


********************************************/

using namespace std;
using namespace nlohmann;


size_t write_data(void *contents, size_t size, size_t nmemb, string *s)
{
	size_t newLength = size*nmemb;
	size_t oldLength = s->size();
	try
	{
		s->resize(oldLength + newLength);
	}
	catch (bad_alloc &e)
	{
		//handle memory problem
		return 0;
	}

	copy((char*)contents, (char*)contents + newLength, s->begin() + oldLength);
	return size*nmemb;
}

string DiscordPlusPlus::DiscordPlusPlus::performRequest(map<string, string> *postfields, vector<string> *headers, string url)
{
	CURL *curl;
	CURLcode res;
	string s;

	curl_global_init(CURL_GLOBAL_ALL);

	curl = curl_easy_init();
	if (curl) {

		struct curl_slist *chunk = NULL;

		string tokenAPI = string("Authorization: Bot ") + string(this->token);
		
		if (headers != nullptr) {
			for (string header : *headers) {
				chunk = curl_slist_append(chunk, header.c_str());
			}
		}

		string posts;

		if (postfields != nullptr) {
			map<string, string>::iterator it = (*postfields).begin();
			while (it != (*postfields).end())
			{
				string part1 = it->first;
				string part2 = it->second;

				posts += part1 + "=" + part2 + "&";

				it++;
			}


			//printf("%s\n", );
			curl_easy_setopt(curl, CURLOPT_COPYPOSTFIELDS, posts.c_str());
		}

		//cout << posts;
		
		chunk = curl_slist_append(chunk, tokenAPI.c_str());


		

		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, FALSE);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);



		res = curl_easy_perform(curl);

		if (res != CURLE_OK)
			return false;

		curl_easy_cleanup(curl);


	}
	curl_global_cleanup();
	return s;
}

string DiscordPlusPlus::DiscordPlusPlus::performRequest(map<string, string> *postfields, vector<string> *headers, string url, string r)
{

	CURL *curl;
	CURLcode res;
	string s;

	curl_global_init(CURL_GLOBAL_ALL);

	curl = curl_easy_init();
	if (curl) {

		struct curl_slist *chunk = NULL;

		string tokenAPI = string("Authorization: Bot ") + string(this->token);

		if (headers != nullptr) {
			for (string header : *headers) {
				chunk = curl_slist_append(chunk, header.c_str());
			}
		}

		string posts;

		if (postfields != nullptr) {
			map<string, string>::iterator it = (*postfields).begin();
			while (it != (*postfields).end())
			{
				string part1 = it->first;
				string part2 = it->second;

				posts += part1 + "=" + part2 + "&";

				it++;
			}


			//printf("%s\n", );
			curl_easy_setopt(curl, CURLOPT_COPYPOSTFIELDS, posts.c_str());
		}

		//cout << posts;

		chunk = curl_slist_append(chunk, tokenAPI.c_str());

		curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, r.c_str());
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, FALSE);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);


		res = curl_easy_perform(curl);

		if (res != CURLE_OK)
			return false;


		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();
	return s;
}



/*******************************************


PUBLIC


********************************************/


bool DiscordPlusPlus::DiscordPlusPlus::sendMessage(string mess, Channel channel) {
	std::map<std::string, std::string> fields;
	fields.insert(std::pair<std::string, std::string>("content", mess));

	string s = DiscordPlusPlus::performRequest(&fields, NULL, "https://discordapp.com/api/v6/channels/" + channel.id + "/messages");
	json j = json::parse(s);
	if (j["code"] == NULL) {
		return true;
	}

	return false;
}


//I could not for the life of me figure out a better way (in like 5 mins) so this is what I did
//TODO: Figure out how to utilize previous things because this is forsing JSON
//If there is another like this, maybe make a function sendJSON()
bool DiscordPlusPlus::DiscordPlusPlus::setName(string name) {
	CURL *curl;
	CURLcode res;


	curl_global_init(CURL_GLOBAL_ALL);

	curl = curl_easy_init();
	if (curl) {

		struct curl_slist *chunk = NULL;

		string tokenAPI = string("Authorization: Bot ") + string(this->token);

		chunk = curl_slist_append(chunk, tokenAPI.c_str());
		chunk = curl_slist_append(chunk, "Content-Type: application/json");

		curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PATCH");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
		curl_easy_setopt(curl, CURLOPT_URL,"https://discordapp.com/api/v6/users/@me");
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, FALSE);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);

		string go_to_hell = string("{\"username\":\"" + name + "\"}");

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
	string str = string("https://discordapp.com/api/v6/users/@me/guilds/" + guild.id);
	DiscordPlusPlus::performRequest(NULL, NULL, str.c_str(), "DELETE");
	return true;
}

//TODO: Implmenet
//FIX: This doesn't return full guild informattion, so need to come up with some sort of method to get
//all required information. Maybe if a guild is accessed, a function receive the inromation then save it for furture reference, also a time 
//stamp so that it can update itself if it is past a threshold
vector<DiscordPlusPlus::Guild> DiscordPlusPlus::DiscordPlusPlus::getGuilds()
{
	vector<Guild> guilds;
	string s = DiscordPlusPlus::performRequest(NULL, NULL, "https://discordapp.com/api/v6/users/@me/guilds");
	json j = json::parse(s);

	for (json::iterator it = j.begin(); it != j.end(); ++it) {
		json r = *it;
		Guild g;
		//if (!r["owner"].is_null()) 
	}

	return vector<Guild>();
}


DiscordPlusPlus::User DiscordPlusPlus::DiscordPlusPlus::getUser()
{
	User u;
	string s = DiscordPlusPlus::performRequest(NULL, NULL, "https://discordapp.com/api/v6/users/@me");
	json j = json::parse(s);
	if (!j["bot"].is_null())	u.bot = j["bot"].get<bool>();
	if (!j["avatar"].is_null()) u.avatar = j["avatar"].get<string>();
	if (!j["discriminator"].is_null())u.discriminator = j["discriminator"].get<string>();
	if (!j["email"].is_null()) u.email = j["email"].get<string>();
	if (!j["id"].is_null())u.id = j["id"].get<string>();
	if (!j["mfa_enabled"].is_null())u.mfa_enabled = j["mfa_enabled"].get<bool>();
	if (!j["username"].is_null())u.username = j["username"].get<string>();
	if (!j["verified"].is_null())u.verified = j["verified"].get<bool>();

	return u;
}

DiscordPlusPlus::User DiscordPlusPlus::DiscordPlusPlus::getUser(string id)
{
	User u;
	string s = DiscordPlusPlus::performRequest(NULL, NULL, string("https://discordapp.com/api/v6/users/" + id));
	json j = json::parse(s);
	if (!j["bot"].is_null())	u.bot = j["bot"].get<bool>();
	if (!j["avatar"].is_null()) u.avatar = j["avatar"].get<string>();
	if (!j["discriminator"].is_null())u.discriminator = j["discriminator"].get<string>();
	if (!j["email"].is_null()) u.email = j["email"].get<string>();
	if (!j["id"].is_null())u.id = j["id"].get<string>();
	if (!j["mfa_enabled"].is_null())u.mfa_enabled = j["mfa_enabled"].get<bool>();
	if (!j["username"].is_null())u.username = j["username"].get<string>();
	if (!j["verified"].is_null())u.verified = j["verified"].get<bool>();

	return u;
}


DiscordPlusPlus::DiscordPlusPlus::DiscordPlusPlus(string token)
{
	this->token = token;
}
