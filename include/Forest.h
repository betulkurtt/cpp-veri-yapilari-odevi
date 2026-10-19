#ifndef FOREST_H
#define FOREST_H

#include "AVLTree.h"
#include "Stack.h"

class ForestRecord {
public:
    int originalNumber;
    AVLTree* tree;
    Stack* stack;

    ForestRecord();
};

class Forest {
private:
    ForestRecord* records;
    int count;
    int capacity;

    void grow();
    void addTree(AVLTree* tree, int originalNumber);
    void createStacks();
    int indexOfSmallestTop() const;
    int indexOfLargestTop() const;
    void removeRecord(int index);
    void printCharacters() const;

public:
    Forest();
    ~Forest();

    bool loadFromFile(const char* fileName);
    void solve();
};

#endif
