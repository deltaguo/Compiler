#include <iostream>
#include <string>
#include <ctype.h>
#include <utility>
#include "lexicalAnalysis.h"

std::string scanner::preprocessing(std::string code) {
	for (int i = 0; i < code.size(); i++)
	{	
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
		if (code[i] == '\n'||code[i]=='\t') {
			code.erase(i--, 1);
		}
	}
	return code;
}

size_t scanner::isKeyWord(const std::string& word)
{
	if (this->sym_table.find(word) != this->sym_table.end() && this->sym_table.at(word) < 12) {
		return this->sym_table.at(word);
	}
	return 0;
}

size_t scanner::isSeparater(const std::string& word)
{
	if (this->sym_table.find(word) != this->sym_table.end() && this->sym_table.at(word) >= 12 && this->sym_table.at(word) < 22) {
		return this->sym_table.at(word);
	}
	return 0;
}

size_t scanner::isOperator(const std::string& word)
{
	if (this->sym_table.find(word) != this->sym_table.end() && this->sym_table.at(word) >= 22) {
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
				return false;
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
		if (!iscsym(ch)) {
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
		try {
			if (!isascii(ch))throw std::runtime_error("非法字符!");
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
			else {
				insertWord();
			}
		}
		catch (const std::exception& e) {
			std::cerr << "ERROR:" << e.what() << std::endl;
			exit(0);
		}
		
	}
	std::list<std::pair<size_t, std::string>>::iterator iter = res.begin();
	while(iter!=res.end()) { //处理>=,<=,==,!=,
		size_t ch1 = 0,ch2 = 0;
		ch1 = iter->first;
		++iter;
		if (iter != res.end())ch2 = iter->first;
		--iter;
		if (ch2 == 32 && (ch1==26|| ch1 == 27 || ch1 == 32 || ch1 == 35)) {
			switch (ch1) {
			case 26:iter->first = 29;break;
			case 27:iter->first = 30;break;
			case 32:iter->first = 28;break;
			case 35:iter->first = 31;break;
			}
			iter = res.erase(++iter);
			continue;
		}
		size_t quotation = iter->first;
		if (quotation == 14 || quotation == 15) { //处理字符串常量
			std::string const_str;
			auto now = iter;
			++iter;
			while (iter != res.end() && iter->first != quotation) {
				const_str.append(iter->second);
				const_str.append(" ");
				++iter;
			}
			const_str.pop_back();
			now->first = 102;
			now->second = const_str;
			iter = res.erase(++now, ++iter);
		}//处理逻辑与逻辑或
		if (quotation == 33 || quotation == 34) {
			if ((++iter)->first == quotation) {
				iter->first = quotation + 3;
				iter = res.erase(--iter);
			}
		}
		++iter;
	}
	return res;
}