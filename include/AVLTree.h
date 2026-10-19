#ifndef AVL_TREE_H
#define AVL_TREE_H

class Stack;

class AVLNode {
public:
    int value;
    int height;
    AVLNode* left;
    AVLNode* right;

    AVLNode(int value);
};

class AVLTree {
private:
    AVLNode* root;

    int height(AVLNode* node) const;
    int larger(int first, int second) const;
    int balanceFactor(AVLNode* node) const;
    AVLNode* rotateRight(AVLNode* node);
    AVLNode* rotateLeft(AVLNode* node);
    AVLNode* insert(AVLNode* node, int value);
    void deleteTree(AVLNode* node);
    void addLeavesPostorder(AVLNode* node, Stack& stack) const;
    int sumNonLeaves(AVLNode* node) const;

public:
    AVLTree();
    ~AVLTree();

    void add(int value);
    void putLeavesInto(Stack& stack) const;
    int nonLeafSum() const;
};

#endif
