#include "Turtle.h"

#include <cstdlib>

Turtle::Turtle(int y, int x)
    : Animal(2, 1, y, x, 't') {}
Organism *Turtle::createNew(int y, int x) {
    return new Turtle(y, x);
}
bool Turtle::didDeflectAttack(Organism *attacker) const {
    if (attacker->getStrength() < 5) {
        return true;
    }
    else {
        return false;
    }
}
void Turtle::action() {
    // 25% chance
    if (rand() % 4 == 0) {
        Animal::action();
    }
}



