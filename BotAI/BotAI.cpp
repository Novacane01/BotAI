// BotAI.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "AI.h"
#include <iostream>
#include <string>

using namespace std;

void stringLower(string &str);

int main()
{
	AI bot;
	string response;
	while (response!="exit") {
		cout << "YOU: ";
		getline(cin,response);
		stringLower(response);
		cout << "COMPUTER: "<<bot.reply(response) << endl;
	}
    return 0;
}

void stringLower(string &str) {
	for (int i = 0; i < str.length();i++) {
		str[i] = tolower(str[i]);
	}
}

