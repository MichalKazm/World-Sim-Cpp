#include "Organism.h"

#include <curses.h>

#include "World.h"

Organism::Organism(int strength, int initiative, int x, int y, char symbol, World* world)
    : strength(strength), initiative(initiative), x(x), y(y), age(0), symbol(symbol), alive(true), world(world) {}
int Organism::getStrength() const {
    return strength;
}
int Organism::getInitiative() const {
    return initiative;
}
int Organism::getX() const {
    return x;
}
int Organism::getY() const {
    return y;
}
int Organism::getAge() const {
    return age;
}
char Organism::getSymbol() const {
    return symbol;
}
bool Organism::isDead() const {
    return !alive;
}
void Organism::print() const {
    mvwprintw( world->getWindow(), y + 1, x + 1, "%c", symbol);
}







