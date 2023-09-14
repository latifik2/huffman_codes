#include "../headers/Compare.h"

bool Compare::operator()(const TreeNode *a, const TreeNode *b) {
    return a->weigth > b->weigth;
}