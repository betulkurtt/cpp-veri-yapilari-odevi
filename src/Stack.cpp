#include "Stack.h"

StackNode::StackNode(int value) : value(value), next(0) {
}

Stack::Stack() : topNode(0), count(0) {
}

Stack::~Stack() {
    clear();
}

void Stack::push(int value) {
    StackNode* newNode = new StackNode(value);
    newNode->next = topNode;
    topNode = newNode;
    count++;
}

bool Stack::pop(int& value) {
    if (topNode == 0) {
        return false;
    }

    StackNode* deletedNode = topNode;
    value = deletedNode->value;
    topNode = topNode->next;
    delete deletedNode;
    count--;
    return true;
}

bool Stack::top(int& value) const {
    if (topNode == 0) {
        return false;
    }
    value = topNode->value;
    return true;
}

bool Stack::isEmpty() const {
    return topNode == 0;
}

void Stack::clear() {
    int ignoredValue;
    while (pop(ignoredValue)) {
    }
}
