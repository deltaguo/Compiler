#pragma once
#include<string>
#include<list>
class TreeNode
{
public:
	TreeNode(std::string val);
	TreeNode(char val);
	TreeNode();
	~TreeNode() {};
	std::string val;
	TreeNode* left;
	TreeNode* right;
};
class generalTreeNode {
public:
	generalTreeNode(std::string val);
	generalTreeNode();
	~generalTreeNode() {};
	std::string val;
	generalTreeNode* first_son;
	generalTreeNode* next_bro;
};
class generic{
public:
	bool priority(char a, char b);
	bool priority(size_t a, size_t b);
	TreeNode* genericExp(std::string str);
	TreeNode* genericExp(std::list<std::pair<size_t, std::string>> list);
	generalTreeNode* genericStatement(std::list<std::pair<size_t, std::string>> list);
};