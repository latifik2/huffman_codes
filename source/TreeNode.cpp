#include "../headers/TreeNode.h"

TreeNode::TreeNode(int weigth, char character = 0, TreeNode *left = nullptr, TreeNode *right = nullptr) {
    this->weigth = weigth;
    this->left = left;
    this->right = right;
    this->character = character;
}