#include <iostream>
#include "../headers/Debug.h"

void Debug::printBT(const std::string& prefix, const TreeNode* node, bool isLeft)
{
    if( node != nullptr )
    {
        std::cout << prefix;

        std::cout << (isLeft ? "├──" : "└──" );

        // print the value of the node
        std::cout << node->weigth << std::endl;

        // enter the next tree level - left and right branch
        Debug::printBT( prefix + (isLeft ? "│   " : "    "), node->left, true);
        Debug::printBT( prefix + (isLeft ? "│   " : "    "), node->right, false);
    }
}

void Debug::printBT(const TreeNode* node)
{
    Debug::printBT("", node, false);    
}