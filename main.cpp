#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "lexicalAnalysis.h"
#include "syntaxAnalysis.h"
#include <deque>

void transf(TreeNode* root);
void transf(generalTreeNode* root);

int main(int argc,char *argv[])
{
    //string filename = argv[1];
    std::string filename = "C:\\Users\\11814\\Desktop\\1.txt";
    std::string code;
    std::ifstream read;
    try
    {
        read = std::ifstream(filename, std::ios::in);
        if (!read) {
            read.close();
            throw std::runtime_error("无法打开文件:" + filename);
        }
        std::ostringstream buf;
        char ch;
        while (buf && read.get(ch))buf.put(ch);
        code = buf.str();
    }
    catch (const std::exception& e)
    {
        std::cerr << "ERROR:" << e.what() << std::endl;
        exit(0);
    }

    scanner sc;
    //预处理
    code = sc.preprocessing(code);
    std::cout << code << std::endl;
    //标识符识别
    auto table = sc.analysis(code);
    for (auto i : table) {
        std::cout << i.first << "     " << i.second << std::endl;
    }
    //语法分析 并生成树
    generic gc;
    generalTreeNode* root = gc.genericStatement(table.begin(), table.end());
    transf(root);
    read.close();
    return 0;
}
//二叉树层序遍历 主要用来观察表达式
void transf(TreeNode* root) {
    std::vector<std::string> tmp;
    std::deque<TreeNode*> queue;
    int floor(1), nextfloor(0);
    if (root)queue.push_back(root);
    while (!queue.empty()) {
        TreeNode* cur(queue.front());
        queue.pop_front();
        tmp.push_back(cur->val);
        if (cur->left) {
            queue.push_back(cur->left);
            nextfloor++;
        }
        if (cur->right) {
            queue.push_back(cur->right);
            nextfloor++;
        }
        if (tmp.size() == floor) {
            for (auto i : tmp) {
                std::cout << i << " ";
            }
            std::cout << std::endl;
            tmp.clear();
            floor = nextfloor;
            nextfloor = 0;
        }
    }
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



