#pragma once
#include <vector>
#include <string>
#include "Automat.h"
#include "Hash.h"

class lexicalAnalyzer
{
public:
	lexicalAnalyzer();
	Hash hash;
	vector<Token> tokens;
	void addTokens(string& line);
};

