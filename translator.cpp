#include "translator.h"
#include<stack>
#include<queue>
#include<sstream>
#include <iostream>

translator::translator()
{
}

translator::~translator()
{
}

inline size_t translator::to_number(std::string str)
{
	if (!str.size() || !isdigit(str[0]))return 0;
	std::stringstream ss;
	size_t res;
	ss << str;
	ss >> res;
	return res;
}

std::vector<std::vector<std::pair<size_t, std::string>>> translator::getExpTuple(generalTreeNode* root)
{
	std::vector<std::vector<std::pair<size_t, std::string>>> res;
	std::stack<generalTreeNode*> father;
	std::stack<std::pair<size_t, std::string>> tmp;
	size_t count = 0;
	auto cur = root;
	auto genericQuaternion = [&]() {
		std::pair<size_t, std::string> parameter_1, parameter_2, parameter_3;
		if (cur->first_son->val.second == "运算符") {
			parameter_1 = tmp.top();
			tmp.pop();
		}
		else {
			parameter_1 = cur->first_son->val;
		}
		if (cur->val.first != 35) {
			if (cur->first_son->next_bro->val.second == "运算符") {
				parameter_2 = tmp.top();
				tmp.pop();
			}
			else {
				parameter_2 = cur->first_son->next_bro->val;
			}
		}
		else {
			parameter_2 = { 0,"-" };
		}

		if (cur->val.first == 32) {
			parameter_3 = parameter_1;
		}
		else {
			parameter_3 = { ++count,TEMPORARY };
			tmp.push(parameter_3);
		}
		std::vector<std::pair<size_t, std::string>> quaternion = { 
			cur->val,
			parameter_1,
			parameter_2,
			parameter_3
		};
		res.push_back(quaternion);
	};
	//搞一波迭代后序遍历
	while (cur || !father.empty()) {
		if (cur) {
			father.push(cur);
			cur = cur->first_son;
		}
		else {
			cur = father.top();
			father.pop();
			//访问
			if (cur->val.second == "运算符")genericQuaternion();
			//std::cout << "(" << cur->val.first << "," << cur->val.second << ")" << std::endl;
			cur = cur->next_bro;
		}
	}
	return res;
}


std::vector<std::vector<std::pair<size_t, std::string>>> translator::getTuple(generalTreeNode* root) {
	return { {} };
}