#pragma once
#include <string>
#include <vector>
#include <fstream>

class TreeNode {
private: 
	std::string data;
	std::vector<TreeNode> childrens;
public:
	std::string PolishCow;
	std::string Type;
	int cnt;
	TreeNode() : data(""), childrens(std::vector<TreeNode>()), PolishCow(""), cnt(0), Type("") {};
	TreeNode(std::string data) : data(data), childrens(std::vector<TreeNode>(0)), PolishCow(""), cnt(0), Type("") {};

	std::string getData() { return data; }
	std::vector<TreeNode>& getChildren() { return childrens; }
	void setData(std::string data) { this->data = data; }
	void addNode(std::string& data, TreeNode& father) {
		TreeNode buff(data);
		father.childrens.push_back(buff); 
	}

};
class SyntaxTree {
private:
	TreeNode root;
	void addNode(std::string, std::string, TreeNode&);
	void insertNode(SyntaxTree& tree, std::string add, TreeNode& curPos);
	void insertSon(SyntaxTree& tree, std::string add, TreeNode& curPos);
	void print(std::ofstream& out, TreeNode, int);
public:
	SyntaxTree() { root = TreeNode("PROCEDURE"); }
	SyntaxTree(std::string str) { root = TreeNode(str); }
	TreeNode getRoot();
	void setRoot(std::string str) { this->root.setData(str); }
	void addNode(std::string data, std::string father) {
		this->addNode(data, father, root);
	}
	void print(std::ofstream& out) {
		this->print(out, root, 0);
	}
	void insertNode(SyntaxTree& t, std::string insPos) { insertNode(t, insPos, root); }
	void insertSon(SyntaxTree & t, std::string insPos) { insertSon(t, insPos, root); }
	void copy(TreeNode& from, TreeNode& to);
	void cleaner() { this->root.getChildren().clear(); }
	
};

