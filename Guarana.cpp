#include "Guarana.h"

#include "World.h"

Guarana::Guarana(int y, int x)
    : Plant(0, y, x, '*') {}
std::string Guarana::getName() const {
    return "Guarana (" + std::to_string(y) + ", " + std::to_string(x) + ")";
}
Organism *Guarana::createNew(int y, int x) {
    return new Guarana(y, x);
}
void Guarana::collision(Organism *other) {
    world->addLog(other->getName() + ": Ate " + getName());

    int newStrength = other->getStrength() + 3;

    world->addLog(other->getName() + ": Strength increased from " + std::to_string(other->getStrength()) + " to " + std::to_string(newStrength));

    other->setStrength(newStrength);

    dies();
}


