#include "Grass.h"

Grass::Grass(int y, int x)
    : Plant(0, y, x, 'g') {}
Organism *Grass::createNew(int y, int x) {
    return new Grass(y, x);
}

