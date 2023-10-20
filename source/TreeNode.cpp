#include "../headers/TreeNode.h"

TreeNode::TreeNode(int weigth, char character, TreeNode *left, TreeNode *right, TreeNode *parent) {
    this->weigth = weigth;
    this->left = left;
    this->right = right;
    this->character = character;
    this->parent = parent;
}