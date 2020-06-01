#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "lexicalAnalysis.h"
#include "syntaxAnalysis.h"

void transf(TreeNode* root);

int main(int argc,char *argv[])
{
    //string filename = argv[1];
    std::string filename = "C:\\Users\\11814\\Desktop\\1.txt";
    std::string code;
    std::ifstream read(filename, std::ios::in);
    if (!read) {
        std::cerr << "ERROR:no file names " + filename + "." << std::endl;
        read.close();
        exit(0);
    }
    std::ostringstream buf;
    char ch;
    while (buf && read.get(ch))buf.put(ch);
    code = buf.str();

    scanner sc;
    //预处理
    code = sc.preprocessing(code);
    std::cout << code << std::endl;
    //标识符识别
    std::list<std::pair<size_t, std::string>> table = sc.analysis(code);
    for (auto i : table) {
        std::cout << i.first << "     " << i.second << std::endl;
    }
    TreeNode* root = new TreeNode();
    generic gc;
    std::list<std::pair<size_t, std::string>> test = {
       {100,"i"},
       {19,"运算符"},
       {100,"j"},
       {21,"运算符"},
       {101,"8"},
       {20,"运算符"},
       {17,"分隔符"},
       {100,"i"},
       {19,"运算符"},
       {100,"j"},
       {21,"运算符"},
       {101,"7"},
       {18,"分隔符"}
    };
    transf(root);
    read.close();
    return 0;
}

void transf(TreeNode* root) {
    if (!root)return;
    transf(root->left);
    std::cout << root->val <<" ";
    transf(root->right);
}



