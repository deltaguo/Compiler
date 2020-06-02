#pragma once
#include<string>
#include<list>
class generalTreeNode {
public:
	generalTreeNode(std::string val);
	generalTreeNode();
	~generalTreeNode() {};
	std::string val;
	generalTreeNode* first_son;
	generalTreeNode* next_bro;
};
class TreeNode:public generalTreeNode
{
public:
	TreeNode(std::string val);
	TreeNode(char val);
	TreeNode();
	~TreeNode() {};
	TreeNode* left;
	TreeNode* right;
};
class generic{
public:
	bool priority(char a, char b);
	bool priority(size_t a, size_t b);
	TreeNode* genericExp(std::string str);
	TreeNode* genericExp(std::list<std::pair<size_t, std::string>> list);
	TreeNode* genericExp(std::list<std::pair<size_t, std::string>>::iterator start, std::list<std::pair<size_t, std::string>>::iterator end);
	TreeNode* genericAssignment(std::list<std::pair<size_t, std::string>>::iterator start, std::list<std::pair<size_t, std::string>>::iterator end);
	TreeNode* genericLogicExp(std::list<std::pair<size_t, std::string>>::iterator start, std::list<std::pair<size_t, std::string>>::iterator end);
	generalTreeNode* genericStatement(std::list<std::pair<size_t, std::string>>::iterator start, std::list<std::pair<size_t, std::string>>::iterator end);
};