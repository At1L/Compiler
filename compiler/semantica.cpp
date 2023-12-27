#include "semantica.h"
string Name(string s) {
	string buff = "";
	for (char c : s) {
		if (c != ' ') buff += c;
		else return buff;
	}
	return buff;
}
string Type(string s) {
	string buff = "";
	bool flag = false;
	for (char c : s) {
		if (flag) buff += c;
		if (c == ' ') flag = true;
	}
	return buff;
}
string semantica::Procedure(SyntaxTree& tree)
{
	string PolsckaKorova = "";
	PolsckaKorova = Begin(tree.getRoot().getChildren()[0]) + '\n';
	PolsckaKorova += Descriptions(tree.getRoot().getChildren()[1]) + '\n';
	PolsckaKorova += Operators(tree.getRoot().getChildren()[2]) + '\n';


	/*tree.getRoot().PolishCow = tree.getRoot().getChildren()[0].PolishCow + '\n' +
		tree.getRoot().getChildren()[1].PolishCow + '\n' +
		tree.getRoot().getChildren()[2].PolishCow + '\n' +
		tree.getRoot().getChildren()[3].PolishCow + '\n';*/
	cout << PolsckaKorova;
	return tree.getRoot().PolishCow;
	
}

string semantica::Begin(TreeNode& tree)
{
	tree.PolishCow = Name(tree.getChildren()[1].getData()) + " DEFL";
	return tree.PolishCow;
}

string semantica::Descr(TreeNode& tree)
{
	tree.getChildren()[0].Type = Name(tree.getChildren()[2].getChildren()[0].getData());
	string sbf = VarList(tree.getChildren()[0]);
	int bf = tree.getChildren()[0].cnt + 1;
	tree.PolishCow = Name(tree.getChildren()[2].getChildren()[0].getData()) + " " + sbf + " " + to_string(bf) + " DECL";
	return tree.PolishCow;
}
string semantica::DescrList(TreeNode& tree)
{
	if (tree.getChildren().size() == 1) {
		tree.PolishCow = Descr(tree.getChildren()[0]);
	}
	else {
		Descr(tree.getChildren()[0]);
		DescrList(tree.getChildren()[1]);
		tree.PolishCow = tree.getChildren()[0].PolishCow + '\n' + tree.getChildren()[1].PolishCow;
	}
	return tree.PolishCow;
}
string semantica::Descriptions(TreeNode& tree)
{
	tree.PolishCow = DescrList(tree.getChildren()[1]);
	return tree.PolishCow;
}

string semantica::VarList(TreeNode& tree)
{
	if (tree.getChildren().size() == 1) {
		tree.cnt++;
		tree.PolishCow = Name(tree.getChildren()[0].getData());
		if(mp.find(tree.PolishCow) != mp.end()){
			cout << "Again Var\n";
		}
		else {
			tree.getChildren()[0].Type = tree.Type;
			mp.insert({ tree.PolishCow, tree.getChildren()[0].Type });
		}
	}
	else {
		tree.cnt++;
		tree.getChildren()[2].Type = tree.Type;
		tree.PolishCow += Name(tree.getChildren()[0].getData()) + " " + VarList(tree.getChildren()[2]);
		tree.cnt += tree.getChildren()[2].cnt;
		if (mp.find(Name(tree.getChildren()[0].getData())) != mp.end())
			cout << "Again Var\n";
		else {
			tree.getChildren()[0].Type = tree.Type;
			mp.insert({ Name(tree.getChildren()[0].getData()), tree.getChildren()[0].Type });
		}
	}
	return tree.PolishCow;
}



string semantica::Op(TreeNode& tree)
{
	tree.PolishCow = Name(tree.getChildren()[0].getData()) + " " + Expr(tree.getChildren()[2]) + " :=";
	if (mp.find(Name(tree.getChildren()[0].getData())) == mp.end()) cout << "Var not exist\n";
	else tree.getChildren()[0].Type = mp[Name(tree.getChildren()[0].getData())];
	if (tree.getChildren()[0].Type != tree.getChildren()[2].Type) cout << "Wrong op\n";
	return tree.PolishCow;
}

string semantica::Operators(TreeNode& tree)
{
	if (tree.getChildren().size() == 1)
		tree.PolishCow = Op(tree.getChildren()[0]);
	else
		tree.PolishCow = Op(tree.getChildren()[0]) + '\n' + Operators(tree.getChildren()[1]);
	return tree.PolishCow;
}

string semantica::Expr(TreeNode& tree)
{
	if (tree.getChildren().size() != 1)
	{
		tree.PolishCow += SimpleExpr(tree.getChildren()[0]) + ' ' + SimpleExpr(tree.getChildren()[2])
			+ " " + Name(tree.getChildren()[1].getData());
		if (tree.getChildren()[0].Type != tree.getChildren()[2].Type) {
			cout << "Wrong op\n";
		}
		
	}
	else
		tree.PolishCow += SimpleExpr(tree.getChildren()[0]);
	for (int i = 4; i < tree.getChildren().size(); i += 2) {
		tree.PolishCow += SimpleExpr(tree.getChildren()[i]) + Name(tree.getChildren()[i - 1].getData());
		if (tree.getChildren()[i - 2].Type != tree.getChildren()[i].Type) {
			cout << "Wrong op\n";
		}
	}
	tree.Type = tree.getChildren()[0].Type;
	return tree.PolishCow;
}

string semantica::SimpleExpr(TreeNode& tree)
{
	if (Type(tree.getChildren()[0].getData()) == "Id") {
		if (mp.find(Name(tree.getChildren()[0].getData())) == mp.end()) cout << "Var not exist\n";
		else tree.Type = mp[Name(tree.getChildren()[0].getData())];
		tree.PolishCow = Name(tree.getChildren()[0].getData());
		
	}
	else if (Type(tree.getChildren()[0].getData()) == "Const") {
		tree.Type = "integer";
		tree.PolishCow = Name(tree.getChildren()[0].getData());
	}
	else if (Type(tree.getChildren()[0].getData()) == "Del") {
		tree.PolishCow = Expr(tree.getChildren()[1]);
	}
	else {
		tree.Type = "char";
		tree.PolishCow = Name(tree.getChildren()[0].getData());
	}
	return tree.PolishCow;
}

string semantica::End(TreeNode& tree)
{
	return string();
}
