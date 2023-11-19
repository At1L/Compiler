#pragma once
#include <iostream>
#include <vector>
#include <string>
using namespace std;
struct Token
{
	//save type and name of lex
	string type = "None";
	string name = "None";
};
class Automat
{
public:
	Automat();
	//in first array we save all operations
	vector<char> opExpr = { '+', '-', '=' };
	//in first array we save all delimiters
	vector<char> delExpr = { ';', ':', ','};
	//in second array we will save all keywords
	vector<string> keywords = { "begin", "end", "int", "char", "procedure"};

	vector<vector<int>> TransitTable;
	//func that will return tokens from given(current) line
	vector<Token> getTokens(string& line);
};

