#pragma once
#include <fstream>
#include "lexicalAnalyzer.h"
#include "Hash.h"
#include "SyntaxTree.h"
#include <string>

class syntaxAnalyzer
{
	bool Procedure(SyntaxTree&);
	bool Begin(SyntaxTree&);
	bool Description(SyntaxTree&);
	bool Descr(SyntaxTree&);
	bool VarList(SyntaxTree&);
	bool Vlist(SyntaxTree&);
	bool Operators(SyntaxTree&);
	bool Op(SyntaxTree&);
	bool Expr(SyntaxTree&);
	bool SimplExpr(SyntaxTree&);
	bool End(SyntaxTree&);
public:
	lexicalAnalyzer lex;
	Hash hash;
	SyntaxTree tree;
	std::ifstream in;
	syntaxAnalyzer(std::string fileName) : in(fileName) {};
	bool analys(SyntaxTree&);
	void print(std::ofstream& out) { tree.print(out); }
	~syntaxAnalyzer() { in.close(); }

};

