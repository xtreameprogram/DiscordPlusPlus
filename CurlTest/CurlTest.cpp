// CurlTest.cpp : Defines the entry point for the console application.
//

#include "DiscordPlusPlus.h"
#include <iostream>
#include "curl.h"

int main(void)
{
	DiscordPlusPlus::DiscordPlusPlus bot("Mzc3NjAxNzExODMwODU5Nzc2.DOPXPg._6FMVJHRBc9ddeJmLVK2Y4aFsB0");


	bot.sendMessage("Rowdy touty", DiscordPlusPlus::Channel("377601825194639376"));

	system("PAUSE");

	return 0;
}
