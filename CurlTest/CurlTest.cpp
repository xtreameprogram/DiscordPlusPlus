// CurlTest.cpp : Defines the entry point for the console application.
//

#include "DiscordPlusPlus.h"
#include <iostream>

#include <map>
#include <string>
#include <iterator>
#include <algorithm>

int main(void)
{
	DiscordPlusPlus::DiscordPlusPlus bot("MzYyNjY1NzE5MjQwMDY1MDI0.DNljXQ.YBKNOk7YySMlfKXuPrcjMoB0XUo");
	bot.sendMessage("Does this work?", "349972164352409610");
	system("PAUSE");

	return 0;
}
