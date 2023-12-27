#include "syntaxAnalyzer.h"
#include <iostream>
#include <fstream>

bool syntaxAnalyzer::Procedure(SyntaxTree& tree)
{
    SyntaxTree temp("BEGIN");
    if (!Begin(temp)) return 0;
    tree.insertSon(temp, "PROCEDURE");
    temp.cleaner();

    temp.setRoot("DescrList");
	ourToken buff = lex.parse(in);
	if (buff.name != "var") {
		std::cout << "Var not found\n";
		return 0;
	}
	tree.addNode("DESCRIPTIONS", "PROCEDURE");
	tree.addNode("var", "DESCRIPTIONS");
	tree.addNode("DescrList", "DESCRIPTIONS");
    if (!Description(temp)) return 0;
	tree.insertNode(temp, "DescrList");
    temp.cleaner();

    temp.setRoot("OPERATORS");
    if (!Operators(temp)) return 0;
    tree.addNode("OPERATORS", "PROCEDURE");
    tree.insertNode(temp, "OPERATORS");
    temp.cleaner();

    temp.setRoot("END");
    if (!End(temp)) return 0;
    tree.addNode("END", "PROCEDURE");
    tree.insertNode(temp, "END");

    return (lex.parse(in).name == "None");
}

bool syntaxAnalyzer::Begin(SyntaxTree& tree)
{
    ourToken elem = lex.parse(in);
    if (elem.name != "procedure") {
        cout << "Wrong begin\n";
        return 0;
    }
    tree.addNode(elem.name + " " + elem.type, "BEGIN");
    elem = lex.parse(in);
    if (elem.type != "Id") {
        cout << "Wrong procedure name\n";
        return 0;
    }
	tree.addNode(elem.name + " " + elem.type, "BEGIN");
    elem = lex.parse(in);
    if (elem.name != ";") {
        cout << "Wrong line close\n";
        return 0;
    }
	tree.addNode(elem.name + " " + elem.type, "BEGIN");
	elem = lex.parse(in);
	if (elem.name != "begin") {
		cout << "begin not found\n";
		return 0;
	}
	tree.addNode(elem.name + " " + elem.type, "BEGIN");
    return 1;
}

bool syntaxAnalyzer::Description(SyntaxTree& tree)
{
    SyntaxTree temp("Descr");
    if (!Descr(temp))
        return 0;
    tree.insertSon(temp, "DescrList");
	SyntaxTree tmp("DescrList");
	//tree.addNode("DescrList", tree.getRoot().getData());
	ourToken buff = lex.parse(in);
	ourToken buff_ = lex.parse(in);
	if (buff.type == "Id" && buff_.name == ":=") {
		lex.backPos(in, buff_.name);
		lex.backPos(in, buff.name);

		return 1;
	}
	lex.backPos(in, buff_.name);
	lex.backPos(in, buff.name);
	tree.addNode("DescrList", tree.getRoot().getData());
	Description(tmp);
	tree.insertNode(tmp, tree.getRoot().getData());
    return 1;
}

bool syntaxAnalyzer::Descr(SyntaxTree& tree)
{
    SyntaxTree temp("VARLIST");
    if (!VarList(temp))
        return 0;
	ourToken buff = lex.parse(in);
	ourToken buff_ = lex.parse(in);
	if (buff.type == "Id" && buff_.name == ":=") {
		lex.backPos(in, buff_.name);
		lex.backPos(in, buff.name);
		return 1;
	}
	lex.backPos(in, buff_.name);
	lex.backPos(in, buff.name);
	tree.addNode("VARLIST", tree.getRoot().getData());
    tree.insertNode(temp, "VARLIST");
    temp.cleaner();
    ourToken elem = lex.parse(in);
    if (elem.name != ":") {
		return 0;
    }
    tree.addNode(elem.name + " " + elem.type, "Descr");
	elem = lex.parse(in);
	if (elem.name != "integer" && elem.name != "char") return 0;
	tree.addNode("Type", "Descr");
	tree.addNode(elem.name + " " + elem.type, "Type");
	elem = lex.parse(in);
	if (elem.name != ";") return 0;
	tree.addNode(elem.name + " " + elem.type, "Descr");
    return 1;
}

bool syntaxAnalyzer::VarList(SyntaxTree& tree)
{
    ourToken elem = lex.parse(in);
    if (elem.type != "Id") {
		cout << "Varlist error\n";
		return 0;
    }
	ourToken buff = elem;
	elem = lex.parse(in);
	if (elem.name == ":=") {
		lex.backPos(in, elem.name);
		lex.backPos(in, buff.name);
		return 1;
	}
	lex.backPos(in, elem.name);
	elem = buff;
    tree.addNode(elem.name + " " + elem.type, "VARLIST");
    while (true) {
        elem = lex.parse(in);
		if (elem.name == ":") {
			lex.backPos(in, elem.name);
			return 1;
		}
        if (elem.name != ",") {
            lex.backPos(in, elem.name);
            return 1;
        }
        tree.addNode(elem.name + " " + elem.type, "VARLIST");
		SyntaxTree temp("VARLIST");
		if (!MaxVerstappen(temp)) return 0;
		tree.addNode("VARLIST", "VARLIST");
		tree.insertNode(temp, "VARLIST");
    }
    return 1;
}
bool syntaxAnalyzer::MaxVerstappen(SyntaxTree& tree)
{
	ourToken elem = lex.parse(in);
	if (elem.type != "Id") {
		cout << "Varlist error\n";
		return 0;
	}
	tree.addNode(elem.name + " " + elem.type, "VARLIST");
	while (true) {
		elem = lex.parse(in);
		if(elem.name == ":") {
			lex.backPos(in, elem.name);
			return 1;
		}
		if (elem.name != ",") {
			lex.backPos(in, elem.name);
			return 1;
		}
		
		tree.addNode(elem.name + " " + elem.type, "VARLIST");
		SyntaxTree temp("VARLIST");
		if (!MaxVerstappen(temp)) return 0;
		tree.addNode("VARLIST", "VARLIST");
		tree.insertNode(temp, "VARLIST");
	}
	return 1;
}

bool syntaxAnalyzer::Operators(SyntaxTree& tree)
{
	ourToken elem = lex.parse(in);
	if (elem.type != "Id") {
		lex.backPos(in, elem.name);
		tree.getRoot().setData("");
		return 1;
	}
	lex.backPos(in, elem.name);
    SyntaxTree temp("OP");
    if (!Op(temp)) return 0;
    tree.insertSon(temp, "OPERATORS");
	SyntaxTree buff("OPERATORS");
	Operators(buff);
	if (buff.getRoot().getChildren().size() != 0)
	{
		tree.addNode("OPERATORS", tree.getRoot().getData());
		tree.insertNode(buff, tree.getRoot().getData());
	}
    return 1;
}

bool syntaxAnalyzer::Op(SyntaxTree& tree)
{
	SyntaxTree temp;
	ourToken elem = lex.parse(in);
	if (elem.type == "Id") {
		tree.addNode(elem.name + " " + elem.type, "OP");
		elem = lex.parse(in);
		if (elem.name != ":=") {
			cout << "Wrong assign op\n";
			return 0;
		}
		tree.addNode(elem.name + " " + elem.type, "OP");
		temp.cleaner();
		temp.setRoot("EXPR");
		if (!Expr(temp))
			return 0;
		tree.addNode("EXPR", "OP");
		tree.insertNode(temp, "EXPR");
		temp.cleaner();
		elem = lex.parse(in);
		if (elem.name == ";") {
			tree.addNode(elem.name + " " + elem.type, "OP");
			return 1;
		}

		tree.addNode(elem.name + " " + elem.type, "OP");
		elem = lex.parse(in);
	}
	else {
		cout << "Waiting for Id\n";
		return 0;
	}
	return 1;
}

bool syntaxAnalyzer::Expr(SyntaxTree& tree)
{
	SyntaxTree temp;
	temp.cleaner();
	temp.setRoot("SIMPLE_EXPR");
	if (!SimplExpr(temp))
		return 0;
	tree.addNode("SIMPLE_EXPR", "EXPR");
	tree.insertNode(temp, "SIMPLE_EXPR");
	ourToken elem = lex.parse(in);
	if (elem.name != "+" && elem.name != "-") {
		lex.backPos(in, elem.name);
		return 1;
	}
	tree.addNode(elem.name + " " + elem.type, "EXPR");
	if (!Expr(tree))
		return 0;
	return 1;
}


bool syntaxAnalyzer::SimplExpr(SyntaxTree& tree)
{
	ourToken elem = lex.parse(in);
	if (elem.name == ";") {
		lex.backPos(in, elem.name);
		return 1;
	}
	SyntaxTree temp("EXPR");
	if (elem.name == "(") {
		tree.addNode(elem.name + " " + elem.type, "SIMPLE_EXPR");
		temp.cleaner();
		temp.setRoot("EXPR");
		if (!Expr(temp)) return 0;
		tree.addNode("EXPR", "SIMPLE_EXPR");
		tree.insertNode(temp, "EXPR");
		elem = lex.parse(in);
		if (elem.name != ")") {
			cout << ") not found\n";
			return 0;
		}
	}
	else if (elem.name == "+" || elem.name == "-") {
		lex.backPos(in, elem.name);
		return 1;
	}
	else if (elem.type != "Id" && elem.type != "Const" && elem.type != "strConst") return 0;
	tree.addNode(elem.name + " " + elem.type, "SIMPLE_EXPR");
	return 1;
}

bool syntaxAnalyzer::End(SyntaxTree& tree)
{
	ourToken elem = lex.parse(in);
	if (elem.name != "end") {
		return 0;
	}
	tree.addNode(elem.name + " " + elem.type, "END");
	return 1;
}

bool syntaxAnalyzer::analys(SyntaxTree& tree)
{
	return Procedure(tree);
}
