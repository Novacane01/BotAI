#pragma once

#include <string>
#include <unordered_map>
#include <vector>

class AI{
public:
	AI();
	std::string reply(std::string);
	bool compareString(std::string, std::string);
	std::vector<std::string> split(std::string, char);
private:
	std::unordered_map<std::string, std::string> responses;
	std::string responseFile = "responses.txt";
};