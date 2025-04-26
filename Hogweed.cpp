#include "Hogweed.h"
#include "Animal.h"
#include "World.h"

Hogweed::Hogweed(int y, int x)
    : Plant(10, y, x, 'h') {}
std::string Hogweed::getName() const {
    return "Hogweed (" + std::to_string(y) + ", " + std::to_string(x) + ")";
}
Organism *Hogweed::createNew(int y, int x) {
    return new Hogweed(y, x);
}
void Hogweed::collision(Organism *other) {
    world->addLog(other->getName() + ": Ate " + getName());

    if (getStrength() <= other->getStrength()) {
        dies();
    }

    other->dies();
}
void Hogweed::action() {
    // Kill animals adjacent to this plant
    int killed = 0;

    Organism* other = world->getOrganism(y - 1, x);
    if ((other != nullptr) && (dynamic_cast<Animal*>(other))) {
        other->dies();
        killed++;
    }
    other = world->getOrganism(y + 1, x);
    if ((other != nullptr) && (dynamic_cast<Animal*>(other))) {
        other->dies();
        killed++;
    }
    other = world->getOrganism(y, x - 1);
    if ((other != nullptr) && (dynamic_cast<Animal*>(other))) {
        other->dies();
        killed++;
    }
    other = world->getOrganism(y, x + 1);
    if ((other != nullptr) && (dynamic_cast<Animal*>(other))) {
        other->dies();
        killed++;
    }

    if (killed > 0) {
        world->addLog(getName() + ": Killed " + std::to_string(killed) + " animals adjacent to it");
    }

    Plant::action();
}


