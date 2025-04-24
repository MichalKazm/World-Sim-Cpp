#include "Guarana.h"

Guarana::Guarana(int y, int x)
    : Plant(0, y, x, '*') {}
Organism *Guarana::createNew(int y, int x) {
    return new Guarana(y, x);
}
void Guarana::collision(Organism *other) {
    int newStrength = other->getStrength() + 3;
    other->setStrength(newStrength);

    dies();
}


