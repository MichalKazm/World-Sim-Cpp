#include "DeadlyNightshade.h"

DeadlyNightshade::DeadlyNightshade(int y, int x)
    : Plant(99, y, x, 'n') {}
Organism *DeadlyNightshade::createNew(int y, int x) {
    return new DeadlyNightshade(y, x);
}
void DeadlyNightshade::collision(Organism *other) {
    if (getStrength() <= other->getStrength()) {
        dies();
    }

    other->dies();
}


