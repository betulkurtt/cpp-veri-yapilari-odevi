
#include "Forest.h"
#include <fstream>
#include <iostream>

ForestRecord::ForestRecord() : originalNumber(0), tree(0), stack(0) {
}

Forest::Forest() : records(0), count(0), capacity(0) {
}

Forest::~Forest() {
    for (int i = 0; i < count; i++) {
        delete records[i].stack;
        delete records[i].tree;
    }
    delete[] records;
}

void Forest::grow() {
    int newCapacity = capacity == 0 ? 16 : capacity * 2;
    ForestRecord* newRecords = new ForestRecord[newCapacity];
    for (int i = 0; i < count; i++) newRecords[i] = records[i];
    delete[] records;
    records = newRecords;
    capacity = newCapacity;
}

void Forest::addTree(AVLTree* tree, int originalNumber) {
    if (count == capacity) grow();
    records[count].tree = tree;
    records[count].originalNumber = originalNumber;
    count++;
}

bool Forest::loadFromFile(const char* fileName) {
    std::ifstream file(fileName);
    if (!file) return false;

    AVLTree* currentTree = new AVLTree();
    int lineNumber = 1;
    bool hasNumber = false;
    int value = 0;
    char character;

    while (file.get(character)) {
        if (character >= '0' && character <= '9') {
            value = value * 10 + (character - '0');
            hasNumber = true;
        } else {
            if (hasNumber) {
                currentTree->add(value);
                value = 0;
                hasNumber = false;
            }
            if (character == '\n') {
                addTree(currentTree, lineNumber);
                currentTree = new AVLTree();
                lineNumber++;
            }
        }
    }
    if (hasNumber) currentTree->add(value);
    if (hasNumber || lineNumber == 1) {
        addTree(currentTree, lineNumber);
    } else {
        delete currentTree;
    }
    return true;
}

void Forest::createStacks() {
    for (int i = 0; i < count; i++) {
        delete records[i].stack;
        records[i].stack = new Stack();
        records[i].tree->putLeavesInto(*records[i].stack);
    }
}

int Forest::indexOfSmallestTop() const {
    int result = 0;
    int selectedValue = 0;
    records[0].stack->top(selectedValue);
    for (int i = 1; i < count; i++) {
        int candidate;
        records[i].stack->top(candidate);
        if (candidate < selectedValue) {
            selectedValue = candidate;
            result = i;
        }
    }
    return result;
}

int Forest::indexOfLargestTop() const {
    int result = 0;
    int selectedValue = 0;
    records[0].stack->top(selectedValue);
    for (int i = 1; i < count; i++) {
        int candidate;
        records[i].stack->top(candidate);
        if (candidate > selectedValue) {
            selectedValue = candidate;
            result = i;
        }
    }
    return result;
}

void Forest::removeRecord(int index) {
    delete records[index].stack;
    delete records[index].tree;
    for (int i = index; i < count - 1; i++) records[i] = records[i + 1];
    count--;
}

void Forest::printCharacters() const {
    for (int i = 0; i < count; i++) {
        int ascii = records[i].tree->nonLeafSum() % 26 + 65;
        std::cout << static_cast<char>(ascii);
    }
    std::cout << std::endl;
}

void Forest::solve() {
    if (count == 0) {
        std::cout << "Veri.txt icinde islenecek satir bulunamadi." << std::endl;
        return;
    }

    while (count > 1) {
        createStacks();
        printCharacters();
        bool removeSmallest = true;
        int unusedValue;
        while (true) {
            int selected = removeSmallest ? indexOfSmallestTop() : indexOfLargestTop();
            records[selected].stack->pop(unusedValue);
            if (records[selected].stack->isEmpty()) {
                removeRecord(selected);
                break;
            }
            removeSmallest = !removeSmallest;
        }
    }

    int ascii = records[0].tree->nonLeafSum() % 26 + 65;
    std::cout << "Son Karakter: " << static_cast<char>(ascii) << std::endl;
    std::cout << "AVL NO: " << records[0].originalNumber << std::endl;
}
