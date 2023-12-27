#pragma once
#include "SyntaxTree.h"
#include "Hash.h"
#include "syntaxAnalyzer.h"
#include <fstream>
#include <iostream>
#include <map>
using namespace std;
class semantica
{
public:
	SyntaxTree tree;
    map<string, string> mp;
    semantica() {};
    
    string Procedure(SyntaxTree& tree);
    string Begin(TreeNode& tree);
    string Descr(TreeNode& tree);
    string DescrList(TreeNode& tree);
    string Descriptions(TreeNode& tree);
    string VL(TreeNode& tree);
    string VarList(TreeNode& tree);
    string NumExprMain(TreeNode& tree);
    string NumExpr(TreeNode& tree);
    string StringExpr(TreeNode& tree);
    string StringExprMain(TreeNode& tree);
    string SimpleNumExpr(TreeNode& tree);
    string SimpleStringExpr(TreeNode& tree);
    string String(TreeNode& tree);
    string Op(TreeNode& tree);
    string Operators(TreeNode& tree);
    string Expr(TreeNode& tree);
    string SimpleExpr(TreeNode& tree);
    string End(TreeNode& tree);
};

