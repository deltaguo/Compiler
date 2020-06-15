#pragma once
#include<vector>
#include<string>
#include"lexicalAnalysis.h"
#include"syntaxAnalysis.h"

#define TEMPORARY "通用寄存器"

#define DECLARE_TYPE "声明类型"
#define DECLARE_NUMBER "声明数量"
#define END_OF_PROGRAM "程序结束"
#define UNCONDITIONAL "无条件转移"
#define RESULT "结果寄存器"
#define IS_TRUE "结果寄存器为真则转移至"
#define IS_FALSE "结果寄存器为假则转移至"
#define OUTPUT "输出"
#define JUMP_TO "跳转至地址"

class translator
{
public:
	translator();
	~translator();
	size_t to_number(std::string str);
	std::vector<std::vector<std::pair<size_t,std::string>>> getExpTuple(generalTreeNode* root);
	std::vector<std::vector<std::pair<size_t, std::string>>> getTuple(generalTreeNode* root);
	size_t count_instruction(generalTreeNode* root);
private:
	std::pair<size_t, std::string > result;
};

