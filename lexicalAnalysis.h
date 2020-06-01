#pragma once
#include<unordered_map>

class scanner
{
public:
	scanner() {};
	~scanner() {};
	std::string preprocessing(std::string code);
	const std::unordered_map<std::string, size_t> sym_table {
		{"int",1},{"char",2},{"double",3},{"void",4},{"return",5},{"if",6},
		{"else",7},{"while",8},{"break",9},{"continue",10},{"print",11},
		{";",12},{",",13},{"'",14},{"\"",15}, {"{",16},{"}",17},{"[",18},
		{"]",19},{"(",20},{")",21},{"+",22},{"-",23},{"*",24},{"/",25},
		{">",26},{"<",27},{"==",28},{">=",29},{"<=",30},{"!=",31},{"=",32},
		{"&",33},{"|",34},{"!",35}
	};
	size_t isKeyWord(const std::string& word);
	size_t isSeparater(const std::string& word);
	size_t isOperator(const std::string& word);
	bool isNumber(const std::string& word);
	bool isVariaty(const std::string& word);
	std::list<std::pair<size_t, std::string>> analysis(const std::string& code);
};