// CurlTest.cpp : Defines the entry point for the console application.
//

#include "DiscordPlusPlus.h"
#include <iostream>
#include "curl.h"

int main(void)
{
	//TODO Put fixed token
	DiscordPlusPlus::DiscordPlusPlus bot("Mzc3NjAxNzExODMwODU5Nzc2.DOf2Zg.usSCjR39G9vHLSdA64zy-leb-VQ");

	bot.sendMessage("Rowdy touty", DiscordPlusPlus::Channel("377601825194639376"));

	bot.getGuilds();


	system("PAUSE");

	return 0;
}
