#include "Sheep.h"

Sheep::Sheep(int y, int x)
    : Animal(4, 4, y, x, 's'){}
Organism *Sheep::createNew(int y, int x) {
    return new Sheep(y,x);
}

