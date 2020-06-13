#pragma once
#include<string>
#include<list>
#include <unordered_map>
class generalTreeNode {
public:
	generalTreeNode(std::pair<size_t, std::string> val);
	generalTreeNode();
	~generalTreeNode() {};
	//std::string val;
	std::pair<size_t, std::string> val;
	generalTreeNode* first_son;
	generalTreeNode* next_bro;
};
class TreeNode:public generalTreeNode
{
public:
	TreeNode(std::pair<size_t, std::string> val);
	TreeNode();
	~TreeNode() {};
	TreeNode* left;
	TreeNode* right;
};
class generic{
public:
	generalTreeNode* genericStatement(std::list<std::pair<size_t, std::string>>::iterator start, std::list<std::pair<size_t, std::string>>::iterator end);
private:
	const std::unordered_map<size_t,size_t> priority_table{
		{35,0},{24,1},{25,1},{38,1},{22,2},{23,2},{26,3},{27,3},{29,3},{30,3},{28,4},{31,4},
		{33,5},{34,6},{36,7},{37,8},{32,9}
	};
	const std::vector<std::string> re_sym_table{
	"","int","char","double","void","return","if","else","while","break","continue","print",
	";",",","'","\"","{","}","[","]","(",")","+","-","*","/",">","<","==",">=","<=","!=","=",
	"&","|","!","&&","||","%"
	};
	bool priority(size_t a, size_t b);
	TreeNode* genericExp(std::list<std::pair<size_t, std::string>>::iterator start, std::list<std::pair<size_t, std::string>>::iterator end);
};