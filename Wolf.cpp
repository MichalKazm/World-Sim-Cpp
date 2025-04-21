#include "Wolf.h"

#include "World.h"

Wolf::Wolf(int y, int x)
    : Animal(9, 5, y, x, 'w') {}
Organism *Wolf::createNew(int y, int x) {
    return new Wolf(y, x);
}
