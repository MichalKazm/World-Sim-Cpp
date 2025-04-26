#include "Organism.h"
#include "World.h"

#include <curses.h>

Organism::Organism(int strength, int initiative, int y, int x, char symbol)
    : strength(strength), initiative(initiative), y(y), x(x), age(0), symbol(symbol), alive(true), world(nullptr) {}
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
bool Organism::didDeflectAttack(Organism* attacker) {
    return false;
}
bool Organism::isDead() const {
    return !alive;
}
void Organism::dies() {
    world->addLog(getName() + ": Died");
    alive = false;
}
void Organism::print() const {
    mvwprintw( world->getGameWindow(), y + 1, x + 1, "%c", symbol);
}
void Organism::setWorld(World* world) {
    this->world = world;
}
void Organism::setStrength(int strength) {
    this->strength = strength;
}
void Organism::setAge(int age) {
    this->age = age;
}