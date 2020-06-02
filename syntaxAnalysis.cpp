#include "syntaxAnalysis.h"
#include<iostream>
#include<ctype.h>
#include<stack>
#include<unordered_set>

TreeNode::TreeNode(std::string val)
{
	this->val = val;
	this->left = nullptr;
	this->right = nullptr;
	this->first_son = nullptr;
	this->next_bro = nullptr;
}
TreeNode::TreeNode(char val)
{
	this->val.push_back(val);
	this->left = nullptr;
	this->right = nullptr;
	this->first_son = nullptr;
	this->next_bro = nullptr;
}
TreeNode::TreeNode()
{
	this->val = "";
	this->left = nullptr;
	this->right = nullptr;
	this->first_son = nullptr;
	this->next_bro = nullptr;
}
generalTreeNode::generalTreeNode(std::string val)
{
	this->val = val;
	this->first_son = nullptr;
	this->next_bro = nullptr;
}
generalTreeNode::generalTreeNode()
{
	this->val = "";
	this->first_son = nullptr;
	this->next_bro = nullptr;
}
bool generic::priority(char a, char b)
{
	if (b == '*' || b == '/')return false;
	if (a == '*' || a == '/')return true;
	return false;
}
bool generic::priority(size_t a, size_t b) {
	if (b == 21 || b == 22)return false;
	if (a == 21 || a == 22)return true;
	return false;
}
TreeNode* generic::genericExp(std::string str) {
	std::stack<char> op;
	std::stack<TreeNode*> exp;
	auto genericMiniTree = [&]() {
		TreeNode* tmp = new TreeNode(op.top());
		op.pop();
		tmp->right = exp.top();
		exp.pop();
		tmp->left = exp.top();
		exp.pop();
		tmp->left->next_bro = tmp->right;
		tmp->first_son = tmp->left;
		exp.push(tmp);
	};
	for (auto i : str) {
		if (i == '+' || i == '-' || i == '*' || i == '/') {
			if (!op.empty() && op.top() != '(')
				if (!priority(i, op.top()))genericMiniTree();
			op.push(i);
		}
		else if (i == '(') {
			op.push(i);
		}
		else if (i == ')') {
			while (op.top() != '(')genericMiniTree();
			op.pop();
		}
		else if (isalpha(i) || isdigit(i)) {
			exp.push(new TreeNode(i));
		}
		else {
			std::cerr << "wrong expression!";
			return NULL;
		}
	}
	while (!op.empty())genericMiniTree();
	return exp.top();
}
TreeNode* generic::genericExp(std::list<std::pair<size_t, std::string>> list)
{	
	std::stack<size_t> op;
	std::stack<TreeNode*> exp;
	auto genericMiniTree = [&]() {
		TreeNode* tmp = new TreeNode(std::to_string(op.top()));
		op.pop();
		tmp->right = exp.top();
		exp.pop();
		tmp->left = exp.top();
		exp.pop();
		tmp->left->next_bro = tmp->right;
		tmp->first_son = tmp->left;
		exp.push(tmp);
	};
	for (auto i : list) {
		if (i.first == 22 || i.first == 23 || i.first == 24 || i.first == 25) {
			if (!op.empty() && op.top() != 20)
				if (!priority(i.first, op.top()))genericMiniTree();
			op.push(i.first);
		}
		else if (i.first == 20) {
			op.push(i.first);
		}
		else if (i.first == 21) {
			while (op.top() != 17)genericMiniTree();
			op.pop();
		}
		else if (i.first == 100 ||i.first == 101||i.first == 102) {
			exp.push(new TreeNode(i.second));
		}
		else {
			std::cerr << "wrong expression!";
			return nullptr;
		}
	}
	while (!op.empty())genericMiniTree();
	return exp.top();
}
TreeNode* generic::genericExp(std::list<std::pair<size_t, std::string>>::iterator start, std::list<std::pair<size_t, std::string>>::iterator end)
{
	auto i = start;
	std::stack<size_t> op;
	std::stack<TreeNode*> exp;
	auto genericMiniTree = [&]() {
		TreeNode* tmp = new TreeNode(std::to_string(op.top()));
		op.pop();
		tmp->right = exp.top();
		exp.pop();
		tmp->left = exp.top();
		exp.pop();
		tmp->left->next_bro = tmp->right;
		tmp->first_son = tmp->left;
		exp.push(tmp);
	};
	while (start != end) {
		size_t id = start->first;
		if (id == 22 || id == 23 || id == 24 || id == 25) {
			if (!op.empty() && op.top() != 20)
				if (!priority(id, op.top()))genericMiniTree();
			op.push(id);
		}
		else if (id == 20) {
			op.push(id);
		}
		else if (id == 21) {
			while (op.top() != 20)genericMiniTree();
			op.pop();
		}
		else if (id == 100 || id == 101 || id == 102) {
			exp.push(new TreeNode(start->second));
		}
		else {
			std::cout << id << "wrong expression!" << std::endl;
			return nullptr;
		}
		++start;
	}
	while (!op.empty())genericMiniTree();
	return exp.top();
}
TreeNode* generic::genericAssignment(std::list<std::pair<size_t, std::string>>::iterator start, std::list<std::pair<size_t, std::string>>::iterator end) {
	TreeNode* root = new TreeNode("32");
	root->left = new TreeNode(start->second);
	++(++start);
	root->right = genericExp(start,end);
	root->left->next_bro = root->right;
	root->first_son = root->left;
	return root;
}
TreeNode* generic::genericLogicExp(std::list<std::pair<size_t, std::string>>::iterator start, std::list<std::pair<size_t, std::string>>::iterator end)
{
	std::list<std::pair<size_t, std::string>>::iterator iter = start;
	while (iter != end) {
		if (iter->first > 25 && iter->first < 32) {
			TreeNode* root = new TreeNode(std::to_string(iter->first));
			root->left = genericExp(start, iter);
			root->right = genericExp(++iter, end);
			root->left->next_bro = root->right;
			root->first_son = root->left;
			return root;
		}
		++iter;
	}
	return nullptr;
}
generalTreeNode* generic::genericStatement(std::list<std::pair<size_t, std::string>>::iterator start,std::list<std::pair<size_t, std::string>>::iterator end)
{
	generalTreeNode* root = new generalTreeNode("main");
	std::stack<generalTreeNode*> statement;
	std::stack<size_t> edge;
	std::stack<std::string> var;
	statement.push(root);
	auto iter = start;
	while (iter != end) {
		std::cout <<"**********************"<< iter->first << " " << iter->second << std::endl;
		size_t id = iter->first;
		if (id && id < 12) { //处理关键字
			generalTreeNode* p = statement.top()->first_son;
			if (p) {
				while (p->next_bro)p = p->next_bro;
				p->next_bro = new generalTreeNode(std::to_string(id));
				p = p->next_bro;
			}
			else {
				statement.top()->first_son = new generalTreeNode(std::to_string(id));
				p = statement.top()->first_son;
			}
			statement.push(p);
			if (id == 6||id == 8||id == 11) { //if和while后紧跟逻辑表达式 print后紧跟算数表达式
				auto ed = ++iter;
				if (ed->first != 20) {
					std::cout << "表达式需要括号括起！";
					return nullptr;
				}
				while (ed->first != 21)++ed;
				if (id == 11) statement.top()->first_son = genericExp(++iter, ed);
				else statement.top()->first_son = genericLogicExp(++iter, ed);
				iter = ed;
			}
		}
		else if (id == 16 || id == 18 || id == 20) { //处理左括号
			edge.push(id);
		}
		else if (id == 17 || id == 19 || id == 21) { //处理右括号
			if (!edge.empty()&&edge.top() == id-1) {
				edge.pop();
				if(id == 17)statement.pop();
			}
			else {
				std::cout << "括号匹配错误" << std::endl;
				return nullptr;
			}
		}
		else if (id == 100) {//处理标识符
			auto last = --iter;
			auto ed = ++iter;
			if ((++ed)->first == 32) { //标识符后接等号说明这是一个赋值表达式
				if (last->first > 4) {
					generalTreeNode* p = statement.top()->first_son;
					if (p) {
						while (p->next_bro)p = p->next_bro;
						p->next_bro = new generalTreeNode("103");
						p = p->next_bro;
					}
					else {
						p = new generalTreeNode("103");
						statement.top()->first_son = p;
					}
					statement.push(p);
				}
				while (ed->first != 12 && ed->first != 13)++ed;
				generalTreeNode* p = statement.top()->first_son;
				if (p) {
					while (p->next_bro)p = p->next_bro;
					p->next_bro = genericAssignment(iter, ed);
				}
				else statement.top()->first_son = genericAssignment(iter, ed);
				iter = --ed;
			}
		}
		else if (id == 12) {//分号表示语句结束 可以出栈
			std::cout << "分号" << std::endl;
			statement.pop();
		}
		else if(id == 13){}
		else {
			std::cout <<iter->first<<" "<<iter->second<< "出现异常！" << std::endl;
			return nullptr;
		}
		++iter;
	}
	std::cout << "stack" << " " << statement.size() << std::endl;
	return root;
}
