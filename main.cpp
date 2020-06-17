#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <deque>
#include <windows.h>
#include "lexicalAnalysis.h"
#include "syntaxAnalysis.h"
#include "translator.h"

void transf(TreeNode* root);
void transf(generalTreeNode* root);
void printQuaternion(std::vector<std::vector<std::pair<size_t, std::string>>> list);

int main(int argc, char* argv[])
{
	//std::string filename = argv[1];
	std::string filename = "C:\\Users\\11814\\Desktop\\1.txt";
	std::string code;
	std::ifstream read;
	try
	{
		read = std::ifstream(filename, std::ios::in);
		if (!read)
		{
			read.close();
			throw std::runtime_error("无法打开文件:" + filename);
		}
		std::ostringstream buf;
		char ch;
		while (buf && read.get(ch))buf.put(ch);
		code = buf.str();
	}
	catch (const std::exception& e)
	{
		std::cerr << "ERROR:" << e.what() << std::endl;
		exit(0);
	}

	scanner sc;
	code = sc.preprocessing(code);
	std::cout << "预处理结果：" << std::endl;
	std::cout << code << std::endl;
	std::cout << "*******************************" << std::endl;
	auto table = sc.analysis(code);
	std::cout << "词法分析结果：（二元组双向链表）" << std::endl;
	for (auto i : table)
	{
		std::cout << "(" << i.first << "," << i.second << ")" << std::endl;
	}
	std::cout << "*******************************" << std::endl;
	generic gc;
	generalTreeNode* root = gc.genericStatement(table.begin(), table.end());
	std::cout << "语法分析树：(多叉树先根遍历)" << std::endl;
	transf(root);
	std::cout << "*******************************" << std::endl;
	translator t;
	auto res = t.getTuple(root);
	std::cout << "语义分析结果：(四元组向量--伪汇编)" << std::endl;
	printQuaternion(res);


	read.close();

	return 0;
}
//二叉树层序遍历 主要用来观察表达式
void transf(TreeNode* root)
{
	std::vector<std::pair<size_t, std::string>> tmp;
	std::deque<TreeNode*> queue;
	int floor(1), nextfloor(0);
	if (root)queue.push_back(root);
	while (!queue.empty())
	{
		TreeNode* cur(queue.front());
		queue.pop_front();
		tmp.push_back(cur->val);
		if (cur->left)
		{
			queue.push_back(cur->left);
			nextfloor++;
		}
		if (cur->right)
		{
			queue.push_back(cur->right);
			nextfloor++;
		}
		if (tmp.size() == floor)
		{
			for (auto i : tmp)
			{
				std::cout << "(" << i.first << "," << i.second << ")";
			}
			std::cout << std::endl;
			tmp.clear();
			floor = nextfloor;
			nextfloor = 0;
		}
	}
}

void transf(generalTreeNode* root)
{
	if (!root)return;
	std::cout << "(" << root->val.first << "," << root->val.second << ")" << std::endl;
	generalTreeNode* p = root->first_son;
	while (p)
	{
		transf(p);
		p = p->next_bro;
	}
}

void printQuaternion(std::vector<std::vector<std::pair<size_t, std::string>>> list)
{
	size_t add = 0;
	for (auto i : list)
	{
		std::cout << "地址编号: " << add++ << " " << "{";
		for (auto j : i)
		{
			std::cout << "(" << j.first << "," << j.second << ")";
		}
		std::cout << "}" << std::endl;
	}
}



