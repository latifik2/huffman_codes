#pragma once

#include "TreeNode.h"


class Debug {
public:
    static void printBT(const TreeNode* node);
    static void printBT(const std::string& prefix, const TreeNode* node, bool isLeft);

    template <class T>
    static void DebugPrint(const T &text) { std::cout << text << std::endl; }
};