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

void leftRotate(tree*& tr, tree* Node) {
    tree* tmp = Node->right;
    Node->right = tmp->left;
    if (tmp->left != NULL)
        tmp->left->parent = Node;
    tmp->parent = Node->parent;
    if (tmp->parent == NULL) {
        tr = tmp;
        tmp->color = 0;
    }
    else {
        if (Node == Node->parent->left)
            Node->parent->left = tmp;
        else
            Node->parent->right = tmp;
    }
    tmp->left = Node;
    Node->parent = tmp;
}

void rightRotate(tree*& tr, tree* Node) {
    tree* tmp = Node->left;
    Node->left = tmp->right;
    if (tmp->right != NULL)
        tmp->right->parent = Node;
    tmp->parent = Node->parent;
    if (tmp->parent == NULL) {
        tr = tmp;
        tmp->color = 0;
    }
    else {
        if (Node == Node->parent->left)
            Node->parent->left = tmp;
        else
            Node->parent->right = tmp;
    }
    tmp->right = Node;
    Node->parent = tmp;
}
