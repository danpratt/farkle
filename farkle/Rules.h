#pragma once
#include <string>
class Rules
{
private:
	const std::string rulesFilePath = "farkle_rules.txt";
public:
	void displayRulesFile() const;
};

