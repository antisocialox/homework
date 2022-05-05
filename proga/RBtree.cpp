#include <iostream>

using namespace std;

struct tree{
    int inf;
    int color; // 0 - черный, 1 - красный
    tree* parent, *left, *right;
};

tree* root(int x) {
    tree* tr = new tree;
    tr->inf = x;
    tr->color = 0;
    tr->left = tr->right = tr->parent = NULL;
    return tr;
}

tree* node(tree* parent, int x) {
    tree* tmp = new tree;
    tmp->inf = x;
    tmp->color = 1;
    tmp->left = tmp->right = NULL;
    tmp->parent = parent;
    return tmp;
}

