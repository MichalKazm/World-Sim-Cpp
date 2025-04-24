#include "Hogweed.h"
#include "Animal.h"
#include "World.h"

Hogweed::Hogweed(int y, int x)
    : Plant(10, y, x, 'h') {}
Organism *Hogweed::createNew(int y, int x) {
    return new Hogweed(y, x);
}
void Hogweed::collision(Organism *other) {
    if (getStrength() <= other->getStrength()) {
        dies();
    }

    other->dies();
}
void Hogweed::action() {
    // Kill animals adjacent to this plant
    Organism* other = world->getOrganism(y - 1, x);
    if ((other != nullptr) && (dynamic_cast<Animal*>(other))) {
        other->dies();
    }
    other = world->getOrganism(y + 1, x);
    if ((other != nullptr) && (dynamic_cast<Animal*>(other))) {
        other->dies();
    }
    other = world->getOrganism(y, x - 1);
    if ((other != nullptr) && (dynamic_cast<Animal*>(other))) {
        other->dies();
    }
    other = world->getOrganism(y, x + 1);
    if ((other != nullptr) && (dynamic_cast<Animal*>(other))) {
        other->dies();
    }

    Plant::action();
}


