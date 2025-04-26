#include "Wolf.h"
#include "World.h"

Wolf::Wolf(int y, int x)
    : Animal(9, 5, y, x, 'w') {}
std::string Wolf::getName() const {
    return "Wolf (" + std::to_string(y) + ", " + std::to_string(x) + ")";
}
Organism *Wolf::createNew(int y, int x) {
    return new Wolf(y, x);
}
