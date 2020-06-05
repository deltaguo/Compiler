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
	//a的优先级比b高 return true
	return priority_table.at(a) < priority_table.at(b);
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
		else if (isalnum(i)) {
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
/*生成表达式树*/
TreeNode* generic::genericExp(std::list<std::pair<size_t, std::string>>::iterator start, std::list<std::pair<size_t, std::string>>::iterator end)
{
	auto i = start;
	std::stack<size_t> op;
	std::stack<TreeNode*> exp;
	auto genericMiniTree = [&]() {
		try {
			if (op.empty() || exp.size() < 2)throw std::runtime_error("表达式错误!");
			TreeNode* tmp = new TreeNode(std::to_string(op.top()));
			op.pop();
			tmp->right = exp.top();
			exp.pop();
			tmp->left = exp.top();
			exp.pop();
			tmp->left->next_bro = tmp->right;
			tmp->first_son = tmp->left;
			exp.push(tmp);
		}
		catch (const std::exception& e) {
			std::cerr << "ERROR:" << e.what() << std::endl;
			exit(0);
		}
	};
	auto genericNotMiniTree = [&]() {
		try {
			if (op.empty() || exp.size() < 1)throw std::runtime_error("表达式错误!");
			TreeNode* tmp = new TreeNode("35");
			op.pop();
			tmp->left = exp.top();
			exp.pop();
			tmp->first_son = tmp->left;
			exp.push(tmp);
		}
		catch (const std::exception& e) {
			std::cerr << "ERROR:" << e.what() << std::endl;
			exit(0);
		}
	};
	while (start != end) {
		size_t id = start->first;
		if (id >21 && id<100) {
			if (!op.empty() && op.top() != 20) {
				if (op.top() == 35) genericNotMiniTree();
				if (!priority(id, op.top()))genericMiniTree();
			}
			op.push(id);
		}
		else if (id == 20) {
			op.push(id);
		}
		else if (id == 21) {
			try {
				while (op.top() != 20) {
					if (op.top() != 35)genericMiniTree();
					else genericNotMiniTree();
					if (op.empty())throw std::runtime_error("表达式错误!");
				}
				op.pop();
			}
			catch (const std::exception& e) {
				std::cerr << "ERROR:" << e.what() << std::endl;
				exit(0);
			}

		}
		else if (id == 100 || id == 101 || id == 102) {
			exp.push(new TreeNode(start->second));
		}
		else {
			std::cerr << "ERROR:表达式错误！" << std::endl;
			exit(0);
		}
		++start;
	}
	try {
		while (!op.empty()) {
			if (op.top() == 20)throw std::runtime_error("表达式错误!");
			if (op.top() != 35)genericMiniTree();
			else genericNotMiniTree();
		}
	}
	catch(const std::exception& e){
		std::cerr << "ERROR:" << e.what() << std::endl;
		exit(0);
	}

	//std::cout << exp.top()->val << std::endl;
	return exp.empty() ? nullptr : exp.top();
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
/*生成语法树*/
generalTreeNode* generic::genericStatement(std::list<std::pair<size_t, std::string>>::iterator start,std::list<std::pair<size_t, std::string>>::iterator end)
{
	generalTreeNode* root = new generalTreeNode("main");
	std::stack<generalTreeNode*> statement;
	std::stack<size_t> edge;
	statement.push(root);
	auto iter = start;
	while (iter != end) {
		//std::cout <<"**********************"<< iter->first << " " << iter->second << std::endl;
		size_t id = iter->first;
		if (id && id < 12) { //处理关键字
			try {
				if (statement.empty())throw std::runtime_error("存在非法分隔符！");
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
			}
			catch (const std::exception& e) {
				std::cerr << "ERROR:" << e.what() << std::endl;
				exit(0);
			}
			if (id == 6||id == 8||id == 11) { //if和while和print后紧跟表达式
				auto ed = ++iter;
				try {
					if (ed->first != 20) throw std::runtime_error("缺少'('");
				}
				catch (const std::exception& e) {
					std::cerr << "ERROR:" << e.what() << std::endl;
				}
				while (1) {
					if (ed!=end && ed->first == 21) {
						auto next = ++ed;
						try {
							if (next == end) {
								throw std::runtime_error("缺少';'");
							}
							if (next->first == 12 || next->first == 16 || next->first == 100) {
								--ed;
								break;
							}
						}
						catch (const std::exception& e) {
							std::cout << "ERROR:" << e.what() << std::endl;
							exit(0);
						}
						continue;
					}
					try
					{
						if(ed == end)throw std::runtime_error("缺少';'");
						++ed;
					}
					catch (const std::exception& e)
					{
						std::cout << "ERROR:" << e.what() << std::endl;
						exit(0);
					}
					
				}
				statement.top()->first_son = genericExp(++iter, ed);
				iter = ed;
			}
		}
		else if (id == 16 || id == 18 || id == 20) { //处理左括号
			edge.push(id);
		}
		else if (id == 17 || id == 19 || id == 21) { //处理右括号
			try {
				if (edge.empty() || edge.top() != id - 1) throw std::runtime_error("缺少'{'");
				edge.pop();
				if (id == 17)statement.pop();
			}
			catch (const std::exception& e) {
				std::cerr << "ERROR:" << e.what() << std::endl;
				exit(0);
			}
		}
		else if (id == 100) {//处理标识符
			try {
				if (iter == start)throw std::runtime_error("未声明标识符!");
			}
			catch (const std::exception& e) {
				std::cerr << "ERROR:" << e.what() << std::endl;
				exit(0);
			}
			auto last = --iter;
			auto ed = ++iter;
			if (last->first > 4 && last->first != 13) { //新建哨兵节点
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
			while (ed->first != 12 && ed->first != 13) {
				try {
					++ed;
					if (ed == end)throw std::runtime_error("缺少';'");
				}
				catch (const std::exception& e) {
					std::cerr << "ERROR:" << e.what() << std::endl;
					exit(0);
				}
				
			}
			generalTreeNode* p = statement.top()->first_son;
			if (p) {
				while (p->next_bro)p = p->next_bro;
				p->next_bro = genericExp(iter, ed);
			}
			else statement.top()->first_son = genericExp(iter, ed);
			iter = --ed;
		}
		else if (id == 12) {//分号表示语句结束 可以出栈
			statement.pop();
		}
		else if(id == 13){
			//std::cout << "逗号" << std::endl;
		}
		else{
			std::cerr << "ERROR:非法语句！" << std::endl;
			exit(0);
		}
		++iter;
	}
	try {
		if (!edge.empty())throw std::runtime_error("缺少'}'");
	}
	catch (const std::exception& e)
	{
		std::cout << "ERROR:" << e.what() << std::endl;
		exit(0);
	}
	return root;
}
