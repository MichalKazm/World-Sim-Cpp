#include "DeadlyNightshade.h"
#include "World.h"

DeadlyNightshade::DeadlyNightshade(int y, int x)
    : Plant(99, y, x, 'n') {}
std::string DeadlyNightshade::getName() const {
    return "Deadly Nightshade (" + std::to_string(y) + ", " + std::to_string(x) + ")";
}
Organism *DeadlyNightshade::createNew(int y, int x) {
    return new DeadlyNightshade(y, x);
}
void DeadlyNightshade::collision(Organism *other) {
    world->addLog(other->getName() + ": Ate " + getName());

    if (getStrength() <= other->getStrength()) {
        dies();
    }

    other->dies();
}


