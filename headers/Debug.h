#include "TreeNode.h"

class Debug {
    void printBT(const TreeNode* node);
    void printBT(const std::string& prefix, const TreeNode* node, bool isLeft);
};