#pragma once
#include <vector>
#include <string>
#include "Automat.h"
#include "Hash.h"
#include <fstream>

class lexicalAnalyzer
{
public:
	lexicalAnalyzer();
	Hash hash;
	vector<ourToken> tokens;
	void addTokens(string& line);
	void backPos(ifstream& in, string s);
	string curWord(ifstream& fin);
	void pushHash(string& str);
	ourToken parse(ifstream& in);
};

