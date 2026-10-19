
#include "Forest.h"
#include <iostream>

int main() {
    Forest forest;
    if (!forest.loadFromFile("Veri.txt")) {
        std::cout << "Veri.txt dosyasi acilamadi." << std::endl;
        return 1;
    }
    forest.solve();
    return 0;
}
