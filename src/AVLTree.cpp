
#include "AVLTree.h"
#include "Stack.h"

AVLNode::AVLNode(int value) : value(value), height(1), left(0), right(0) {
}

AVLTree::AVLTree() : root(0) {
}

AVLTree::~AVLTree() {
    deleteTree(root);
}

int AVLTree::height(AVLNode* node) const {
    return node == 0 ? 0 : node->height;
}

int AVLTree::larger(int first, int second) const {
    return first > second ? first : second;
}

int AVLTree::balanceFactor(AVLNode* node) const {
    return node == 0 ? 0 : height(node->left) - height(node->right);
}

AVLNode* AVLTree::rotateRight(AVLNode* node) {
    AVLNode* newRoot = node->left;
    AVLNode* movedSubtree = newRoot->right;
    newRoot->right = node;
    node->left = movedSubtree;
    node->height = larger(height(node->left), height(node->right)) + 1;
    newRoot->height = larger(height(newRoot->left), height(newRoot->right)) + 1;
    return newRoot;
}

AVLNode* AVLTree::rotateLeft(AVLNode* node) {
    AVLNode* newRoot = node->right;
    AVLNode* movedSubtree = newRoot->left;
    newRoot->left = node;
    node->right = movedSubtree;
    node->height = larger(height(node->left), height(node->right)) + 1;
    newRoot->height = larger(height(newRoot->left), height(newRoot->right)) + 1;
    return newRoot;
}

AVLNode* AVLTree::insert(AVLNode* node, int value) {
    if (node == 0) {
        return new AVLNode(value);
    }
    if (value < node->value) {
        node->left = insert(node->left, value);
    } else if (value > node->value) {
        node->right = insert(node->right, value);
    } else {
        return node;
    }

    node->height = larger(height(node->left), height(node->right)) + 1;
    int balance = balanceFactor(node);

    if (balance > 1 && value < node->left->value) return rotateRight(node);
    if (balance < -1 && value > node->right->value) return rotateLeft(node);
    if (balance > 1 && value > node->left->value) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (balance < -1 && value < node->right->value) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    return node;
}

void AVLTree::deleteTree(AVLNode* node) {
    if (node == 0) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

void AVLTree::addLeavesPostorder(AVLNode* node, Stack& stack) const {
    if (node == 0) return;
    addLeavesPostorder(node->left, stack);
    addLeavesPostorder(node->right, stack);
    if (node->left == 0 && node->right == 0) {
        stack.push(node->value);
    }
}

int AVLTree::sumNonLeaves(AVLNode* node) const {
    if (node == 0 || (node->left == 0 && node->right == 0)) return 0;
    return node->value + sumNonLeaves(node->left) + sumNonLeaves(node->right);
}

void AVLTree::add(int value) {
    root = insert(root, value);
}

void AVLTree::putLeavesInto(Stack& stack) const {
    addLeavesPostorder(root, stack);
}

int AVLTree::nonLeafSum() const {
    return sumNonLeaves(root);
}
