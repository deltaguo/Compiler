#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "lexicalAnalysis.h"
#include "syntaxAnalysis.h"

void transf(TreeNode* root);
void transf(generalTreeNode* root);

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
    /*for (auto i : table) {
        std::cout << i.first << "     " << i.second << std::endl;
    }
    std::cout << "***********************" << std::endl;*/
    generic gc;
    generalTreeNode* root = gc.genericStatement(table.begin(),table.end());
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

void transf(generalTreeNode* root) {
    if (!root)return;
    std::cout << root->val << " ";
    generalTreeNode* p = root->first_son;
    while (p) {
        transf(p);
        p = p->next_bro;
    }
}



