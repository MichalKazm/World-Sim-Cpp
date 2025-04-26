#include "Sheep.h"

Sheep::Sheep(int y, int x)
    : Animal(4, 4, y, x, 's'){}
std::string Sheep::getName() const {
    return "Sheep (" + std::to_string(y) + ", " + std::to_string(x) + ")";
}
Organism *Sheep::createNew(int y, int x) {
    return new Sheep(y,x);
}

