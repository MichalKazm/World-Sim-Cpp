#include "Grass.h"

Grass::Grass(int y, int x)
    : Plant(0, y, x, 'g') {}
std::string Grass::getName() const {
    return "Grass (" + std::to_string(y) + ", " + std::to_string(x) + ")";
}
Organism *Grass::createNew(int y, int x) {
    return new Grass(y, x);
}

