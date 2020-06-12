#include "translator.h"
#include<stack>
#include<sstream>

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
	//搞一波迭代后序遍历
	std::vector<std::vector<std::pair<size_t, std::string>>> quaternion;
	std::stack<generalTreeNode*> father;
	auto cur = root;
	while (cur || !father.empty()) {
		if (cur) {
			father.push(cur);
			cur = cur->first_son;
		}
		else {
			cur = father.top();
			father.pop();
		}
	}
	
	return quaternion;
}


std::vector<std::vector<std::pair<size_t, std::string>>> translator::getTuple(generalTreeNode* root) {
	return { {} };
}