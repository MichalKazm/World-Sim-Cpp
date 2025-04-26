#include "Dandelion.h"

Dandelion::Dandelion(int y, int x)
    : Plant(0, y, x, 'd') {}
std::string Dandelion::getName() const {
    return  "Dandelion (" + std::to_string(y) + ", " + std::to_string(x) + ")";;
}
Organism *Dandelion::createNew(int y, int x) {
    return new Dandelion(y, x);
}
void Dandelion::action() {
    for (int i = 0; i < 3; i++) {
        Plant::action();
    }

    // Age is incremented 3 times in loop
    age = age - 2;
}


