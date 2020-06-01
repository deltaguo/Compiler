#include <iostream>
#include <string>
#include <ctype.h>
#include <utility>
#include "lexicalAnalysis.h"

std::string scanner::preprocessing(std::string code) {
	for (int i = 0; i < code.size(); i++)
	{	
		//delete all annotation
		if (code[i] == '/' && code[i + 1] == '/') {
			int j = i + 2;
			while (j < code.size() && code[j] != '\n')j++;
			code.erase(i, j - i + 1);
		}
		if (code[i] == '/' && code[i + 1] == '*') {
			int j = i + 2;
			for (; j < code.size(); j++)
				if (code[j - 1] == '*' && code[j] == '/') break;
			code.erase(i, j - i + 1);
		}
		//delete all useless ENTER and TAB
		if (code[i] == '\n'||code[i]=='\t') {
			code.erase(i--, 1);
		}
	}
	return code;
}
size_t scanner::isKeyWord(const std::string& word)
{
	if (this->sym_table.find(word) != this->sym_table.end() && this->sym_table.at(word) < 11) {
		return this->sym_table.at(word);
	}
	return 0;
}
size_t scanner::isSeparater(const std::string& word)
{
	if (this->sym_table.find(word) != this->sym_table.end() && this->sym_table.at(word) >= 11 && this->sym_table.at(word) < 19) {
		return this->sym_table.at(word);
	}
	return 0;
}
size_t scanner::isOperator(const std::string& word)
{
	if (this->sym_table.find(word) != this->sym_table.end() && this->sym_table.at(word) >= 19) {
		return this->sym_table.at(word);
	}
	return 0;
}
bool scanner::isNumber(const std::string& word)
{
	bool decimal = false;
	for (char ch : word) {
		if (ch == '.') {
			if (decimal) {
				return "";
			}
			else {
				decimal = true;
			}
		}
		else if (!isdigit(ch)) {
			return false;
		}
	}
	return true;
}
bool scanner::isVariaty(const std::string& word)
{
	if (!isalpha(word[0]) && word[0] != '_')return "";
	for (char ch : word) {
		if (!isalpha(ch) && !isdigit(ch) && ch != '_') {
			return false;
		}
	}
	return true;
}
std::list<std::pair<size_t, std::string>> scanner::analysis(const std::string& code)
{
	std::list<std::pair<size_t, std::string>> res;
	std::string word;
	auto insertWord = [&]() {
		size_t id = isKeyWord(word);
		if (id) {
			res.push_back(std::make_pair(id, "关键字"));
			word.clear();
		}
		else {
			if (isNumber(word)) {
				res.push_back(std::make_pair(101, word));
				word.clear();
			}
			else {
				if (isVariaty(word)) {
					res.push_back(std::make_pair(100, word));
					word.clear();
				}
				else {
					std::cout << "出现非法单词!" << std::endl;
				}
			}
		}
	};
	for (char ch : code) {
		if (ch != ' ') {
			std::string c;
			c.push_back(ch);
			size_t id = isSeparater(c);
			if (id) {
				if (word.size()) {
					insertWord();
					word.clear();
				}
				res.push_back(std::make_pair(id, "分隔符"));
			}
			else {
				id = isOperator(c);
				if (id) {
					if (word.size()) {
						insertWord();
						word.clear();
					}
					res.push_back(std::make_pair(id, "运算符"));
				}
				else {
					word.push_back(ch);
				}
			}
		}
		else{
			insertWord();
		}
	}
	std::list<std::pair<size_t, std::string>>::iterator iter = res.begin();
	while(iter!=res.end()) {
		size_t ch1 = 0,ch2 = 0;
		ch1 = iter->first;
		++iter;
		if (iter != res.end())ch2 = iter->first;
		--iter;
		if (ch2 == 29 && (ch1==23|| ch1 == 24 || ch1 == 29 || ch1 == 32)) {
			switch (ch1) {
			case 23:iter->first = 26;break;
			case 24:iter->first = 27;break;
			case 29:iter->first = 25;break;
			case 32:iter->first = 28;break;
			}
			iter = res.erase(++iter);
			continue;
		}
		++iter;
	}
	return res;
}