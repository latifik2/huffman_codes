#pragma once

#include <map>
#include <queue>
#include <vector>
#include <string>

class Compare;
class Huffman;
class Debug;

class TreeNode {
public:
    TreeNode(int weigth, char character = 0, TreeNode *left = nullptr, TreeNode *right = nullptr);

    friend class Compare;
    friend class Huffman;
    friend class Debug;
    friend class App;

private:
    char character;
    int weigth;
    TreeNode *left;
    TreeNode *right;
};

using PQ = std::priority_queue<TreeNode *, std::vector<TreeNode *>, Compare>;