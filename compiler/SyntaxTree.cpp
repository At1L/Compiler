#include "SyntaxTree.h"

bool noSpace(std::string str) {
	for (auto& symb : str)
		if (symb == ' ')
			return 0;
	return 1;
}

void SyntaxTree::addNode(std::string data, std::string father, TreeNode& node){
	if (node.getData() == father)
		node.addNode(data, node);
	else
		for (size_t i = 0; i < node.getChildren().size(); i++) {
			addNode(data, father, node.getChildren()[i]);
		}
}

void SyntaxTree::copy(TreeNode& from, TreeNode& to)
{
	to = from;
	for (size_t i = 0; i < from.getChildren().size(); i++)
		copy(from.getChildren()[i], to.getChildren()[i]);
}

void SyntaxTree::insertNode(SyntaxTree& tree, std::string add, TreeNode& curPos){
	if (curPos.getData().empty()) return;
	if (noSpace(curPos.getData()) && curPos.getChildren().size() == 0) {
		if (curPos.getData() == add) {
			curPos.setData("");
			curPos.getChildren().clear();
			copy(tree.root, curPos);
			return;
		}
	}
	for (auto& child : curPos.getChildren()) {
		insertNode(tree, add, child);
	}
}

void SyntaxTree::insertSon(SyntaxTree& tree, std::string add, TreeNode& curPos)
{
	if (curPos.getData().empty()) return;
	if (noSpace(curPos.getData()) && curPos.getChildren().size() == 0) {
		if (curPos.getData() == add) {
			curPos.getChildren().push_back(TreeNode());
			copy(tree.root, *curPos.getChildren().begin());
			return;
		}
	}
	for (auto& child : curPos.getChildren()) {
		insertSon(tree, add, child);
	}
}

void SyntaxTree::print(std::ofstream& out, TreeNode node, int level)
{
	for (int i = 0; i < level; i++)
	{
		out << '\t';
	}
	out << node.getData() << "\n";

	for (auto& n : node.getChildren())
	{
		print(out, n, level + 1);
	}
}

TreeNode SyntaxTree::getRoot()
{
	return root;
}