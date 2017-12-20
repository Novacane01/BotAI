#include "stdafx.h"
#include "AI.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

AI::AI() {
}

string AI::reply(string message) {
	fstream messages;
	string str = "";
	bool phraseFound = false;
	messages.open(responseFile, ios::app|ios::in|ios::out); //Opens file for both input and output
	if (messages.is_open()) {		//Checks if message opened properly
		string stuff = "";
		while (messages >> stuff) {		//Iterates through very word seprated by space in the file and assings it to "stuff"
			if(stuff != "|"&&stuff != ";") {		//Add each word to str as long as terminating character isnt reached
				str += stuff+" ";
			}
			if (compareString(message,str.substr(0,str.length()-1))&&stuff=="|") {		//If "str" minus whitespace at the end is equal to message, message is found
				phraseFound = true;
				str = "";
				while (messages >> stuff) {		//Get everything after "|" and before ";"
					if (stuff == ";") {
						break;
					}
					if (stuff == "|") {
						str = "";
						continue;
					}
					str += stuff+" ";
				}
				break;
			}
			if (stuff == "|" || stuff == ";") {		//If you encounter a "|" or ";" clear the "str" variable
				str = "";
			}
		}
		messages.close();
		if (!phraseFound) {		//Prompt user for entry and add new response to file if phrase isn't found
			string newreply;
			messages.open(responseFile, ios::app | ios::in | ios::out);
			cout<<"Sorry I don't understand you, how should I respond?";
			getline(cin, newreply);
			for (int i = 0; i < newreply.length();i++) {
				newreply[i] = tolower(newreply[i]);
			}
			responses.insert(pair<string, string>(message, newreply));
			messages << message << " | " << responses[message] << " ;\n";
			return newreply;
		}
		else {
			return str;
		}
	}
}

bool AI::compareString(string usermsg, string comphrase) {
	int count = 0;
	for (string s : split(usermsg, ' ')) {
		for (string str : split(comphrase, ' ')) {
			if (s == str) {
				count++;
			}
		}
	}
	if (count > split(usermsg, ' ').size() / 2&&count>split(comphrase,' ').size()/2) {
		return true;
	}
	return false;
}

vector<string> AI::split(string str, char delim) {
	string splitstr = "";
	vector<string> stringarray;
	for (char c : str) {
		if (c == delim) {
			stringarray.push_back(splitstr);
			splitstr = "";
		}
		else {
			splitstr += c;
		}
	}
	if (stringarray.size() == 0) {
		stringarray.push_back(splitstr);
	}
	return stringarray;
}