// CurlTest.cpp : Defines the entry point for the console application.
//

#include "DiscordPlusPlus.h"
#include <iostream>
#include "curl.h"

int main(void)
{
	DiscordPlusPlus::DiscordPlusPlus bot("Mzc3NjAxNzExODMwODU5Nzc2.DOPXPg._6FMVJHRBc9ddeJmLVK2Y4aFsB0");
	bot.sendMessage("Does this work?", "377601825194639376");

	CURL *hnd = curl_easy_init();

	curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "PUT");
	curl_easy_setopt(hnd, CURLOPT_URL, "http://google.com/");

	struct curl_slist *headers = NULL;
	headers = curl_slist_append(headers, "postman-token: e806a22c-10aa-9de1-e9f3-34b0cc6e203b");
	headers = curl_slist_append(headers, "cache-control: no-cache");
	headers = curl_slist_append(headers, "content-type: application/x-www-form-urlencoded");
	curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, headers);

	curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, "hi=ghello");

	CURLcode ret = curl_easy_perform(hnd);


	system("PAUSE");

	return 0;
}
