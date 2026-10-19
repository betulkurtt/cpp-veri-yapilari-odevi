#ifndef STACK_H
#define STACK_H

class StackNode {
public:
    int value;
    StackNode* next;

    StackNode(int value);
};

class Stack {
private:
    StackNode* topNode;
    int count;

public:
    Stack();
    ~Stack();

    void push(int value);
    bool pop(int& value);
    bool top(int& value) const;
    bool isEmpty() const;
    void clear();
};

#endif
