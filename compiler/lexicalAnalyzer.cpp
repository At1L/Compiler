#include "lexicalAnalyzer.h"

lexicalAnalyzer::lexicalAnalyzer()
{
}
//take string parce it on tokens and add in vector of tokens
void lexicalAnalyzer::addTokens(string& line)
{
	Automat automat;
	vector<Token> buffTokens = automat.getTokens(line);
	for (auto t : buffTokens) {
		this->tokens.push_back(t);
	}
}
