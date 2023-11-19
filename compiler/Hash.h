#pragma once
#include <vector>
#include <string>
#include "Automat.h"
using ll = long long;
using namespace std;

struct Node{
	Token val;
	Node* prev = NULL;
	Node* next = NULL;
};
class Hash
{
public:
	Hash();
	vector<Node> table;
	ll getTableId(string& word);
	void addToken(Token t);
};

