#include "translator.h"
#include<stack>
#include<queue>
#include<sstream>
#include <iostream>

translator::translator()
{}

translator::~translator()
{}

std::vector<std::vector<std::pair<size_t, std::string>>> translator::getExpTuple(generalTreeNode* root)
{
	//return a constant
	if (root->val.first == 100 || root->val.first == 101 || root->val.first == 102 || root->val.first == 104)
	{
		this->result = root->val;
		return {
			{ root->val,{0,"-"},{0,"-"},{0,"-"} }
		};
	}
	std::vector<std::vector<std::pair<size_t, std::string>>> res;
	std::stack<generalTreeNode*> father;
	std::stack<std::pair<size_t, std::string>> tmp;
	size_t count = 0;
	generalTreeNode* cur = new generalTreeNode(root->val);
	cur->first_son = root->first_son;
	auto genericQuaternion = [&]() {
		std::pair<size_t, std::string> parameter_1, parameter_2, parameter_3;
		if (cur->first_son->val.second == OPERATOR)
		{
			parameter_1 = tmp.top();
			tmp.pop();
		}
		else
		{
			parameter_1 = cur->first_son->val;
		}
		if (cur->val.first != 35)
		{
			if (cur->first_son->next_bro->val.second == OPERATOR)
			{
				parameter_2 = tmp.top();
				tmp.pop();
			}
			else
			{
				parameter_2 = cur->first_son->next_bro->val;
			}
		}
		else
		{
			parameter_2 = { 0,"-" };
		}

		if (cur->val.first == 32)
		{
			parameter_3 = parameter_1;
		}
		else
		{
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
	//postorder traversal
	while (cur || !father.empty())
	{
		if (cur)
		{
			father.push(cur);
			cur = cur->first_son;
		}
		else
		{
			cur = father.top();
			father.pop();
			//visit
			if (cur->val.second == OPERATOR)genericQuaternion();
			cur = cur->next_bro;
		}
	}
	this->result = res.back()[3];
	delete cur;
	return res;
}

size_t translator::count_instruction(generalTreeNode* root)
{
	size_t count = 0;
	generalTreeNode* q = new generalTreeNode(root->val);
	q->first_son = root->first_son;
	std::stack<generalTreeNode*> s;
	while (q || !s.empty())
	{
		if (q)
		{
			s.push(q);
			q = q->first_son;
		}
		else
		{
			q = s.top();
			s.pop();
			if (q->val.second == KEYWORD || q->val.second == OPERATOR)
			{
				++count;
				if (q->val.first == 11 || q->val.first == 8)++count;
			}
			q = q->next_bro;
		}
	}
	delete q;
	return count;
}

std::vector<std::vector<std::pair<size_t, std::string>>> translator::getTuple(generalTreeNode* root)
{
	std::vector<std::vector<std::pair<size_t, std::string>>> res;
	auto p = root, last = p;
	std::stack<generalTreeNode*> father;
	std::stack<std::vector<size_t>> loop;
	std::stack<size_t> if_term;
	size_t esc = 0;
	bool output = false;
	while (p || !father.empty())
	{
		if (p)
		{
			if (p->val.second == KEYWORD)
			{
				if (p->val.first < 5)
				{
					auto q = p->first_son;
					size_t count = 0;
					while (q)
					{
						q = q->next_bro;
						++count;
					}
					res.push_back({
							{p->val.first,DECLARE_TYPE},
							{count,DECLARE_NUMBER},
							{0,"-"},
							{0,"-"}
						});
				}
				else if (p->val.first < 6)
				{
					//return -->meanless end of program
					res.push_back({
							{0,END_OF_PROGRAM},
							{0,"-"},
							{0,"-"},
							{0,"-"}
						});
				}
				else if (p->val.first < 7)
				{
					//if
					size_t have_else = p->next_bro && p->next_bro->val.first == 7 ? 1 : 0;
					if_term.push(count_instruction(p->first_son->next_bro) + have_else);
				}
				else if (p->val.first < 8)
				{
					//else
					res.push_back({
						{res.size() + count_instruction(p),UNCONDITIONAL},
						{0,"-"},
						{0,"-"},
						{0,"-"}
						});
				}
				else if (p->val.first < 9)
				{
					//while
					size_t sum = count_instruction(p);
					size_t judge = count_instruction(p->first_son);
					loop.push({ res.size(),judge,sum });

					if_term.push(sum - judge);
				}
				else if (p->val.first < 10)
				{
					//break
					res.push_back({
						{loop.top()[0] + loop.top()[2],UNCONDITIONAL},
						{0,"-"},
						{0,"-"},
						{0,"-"},
						});
				}
				else if (p->val.first < 11)
				{
					//continue
					res.push_back({
						{loop.top()[0] + loop.top()[2] - loop.top()[1],UNCONDITIONAL},
						{0,"-"},
						{0,"-"},
						{0,"-"},
						});
				}
				else if (p->val.first < 12)
				{
					//print
					output = true;
				}
				father.push(p);
				p = p->first_son;
			}
			else if (p->val.second == OPERATOR)
			{
				auto exp = getExpTuple(p);
				res.insert(res.end(), exp.begin(), exp.end());
				//exist conditional
				if (!if_term.empty())
				{
					//if
					if (father.top()->val.first == 6)
					{
						size_t length = if_term.top();
						if_term.pop();
						res.push_back({
							{length + res.size() + 2,CONDITIONAL},
							{0,IS_FALSE},
							{0,"-"},
							{0,"-"}
							});
					}
					//while
					else if (father.top()->val.first == 8)
					{
						size_t length = if_term.top();
						if_term.pop();
						res.push_back({
							{length + res.size(),CONDITIONAL},
							{0,IS_FALSE},
							{0,"-"},
							{0,"-"}
							});
					}
				}
				if (p->next_bro)
				{
					p = p->next_bro;
				}
				else
				{
					p = father.top();
					father.pop();
					p = p->next_bro;
				}
			}
			//expression
			else if (p->val.first > 99)
			{
				std::vector<std::vector<std::pair<size_t, std::string>>> exp;
				if (p->val.first == 103)exp = getExpTuple(p->first_son);
				else exp = getExpTuple(p);
				res.insert(res.end(), exp.begin(), exp.end());
				p = p->next_bro;
			}
			else if (p->val.second == "main")
			{
				father.push(p);
				p = p->first_son;
			}
			else
			{
				std::cerr << p->val.first << "," << p->val.second << "Óï·¨´íÎó" << std::endl;
				exit(0);
			}
		}
		else
		{
			//exist loop
			if (!loop.empty() && father.top()->val.first == 8)
			{
				size_t destination = loop.top()[0];
				loop.pop();
				res.push_back({
						{destination,UNCONDITIONAL},
						{0,"-"},
						{0,"-"},
						{0,"-"}
					});
			}
			//exist output
			if (output)
			{
				res.push_back({
					{0,OUTPUT},
					{0,RESULT},
					{0,"-"},
					{0,"-"}
					});
				output = false;
			}
			p = father.top();
			father.pop();
			p = p->next_bro;
		}
	}
	return res;
}
