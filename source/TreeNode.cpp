#include "../headers/TreeNode.h"

TreeNode::TreeNode(int weigth, char character, TreeNode *left, TreeNode *right) {
    this->weigth = weigth;
    this->left = left;
    this->right = right;
    this->character = character;
}