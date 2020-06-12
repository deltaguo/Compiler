#pragma once
#include<vector>
#include<string>
#include "syntaxAnalysis.h"

class translator
{
public:
	translator();
	~translator();
	size_t to_number(std::string str);
	std::vector<std::vector<std::pair<size_t,std::string>>> getExpTuple(generalTreeNode* root);
	std::vector<std::vector<std::pair<size_t, std::string>>> getTuple(generalTreeNode* root);
private:

};

translator::translator()
{
}

translator::~translator()
{
}

