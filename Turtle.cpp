#include "Turtle.h"

#include <cstdlib>

#include "World.h"

Turtle::Turtle(int y, int x)
    : Animal(2, 1, y, x, 't') {}
bool Turtle::didDeflectAttack(Organism *attacker) {
    if (attacker->getStrength() < 5) {
        world->addLog(getName() + ": Pushed " + attacker->getName() + " back");
        return true;
    }
    else {
        return false;
    }
}
std::string Turtle::getName() const {
    return "Turtle (" + std::to_string(y) + ", " + std::to_string(x) + ")";
}
Organism *Turtle::createNew(int y, int x) {
    return new Turtle(y, x);
}
void Turtle::action() {
    // 25% chance
    if (rand() % 4 == 0) {
        Animal::action();
    }
}



