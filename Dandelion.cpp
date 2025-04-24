#include "Dandelion.h"

Dandelion::Dandelion(int y, int x)
    : Plant(0, y, x, 'd') {}
Organism *Dandelion::createNew(int y, int x) {
    return new Dandelion(y, x);
}
void Dandelion::action() {
    for (int i = 0; i < 3; i++) {
        Plant::action();
    }
}


