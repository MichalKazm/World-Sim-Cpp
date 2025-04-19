#include "Organism.h"

Organism::Organism(int strength, int initiative, int x, int y, char symbol, World* world)
    : strength(strength), initiative(initiative), x(x), y(y), age(0), symbol(symbol), alive(true), world(world) {}
int Organism::GetStrength() const {
    return strength;
}
int Organism::GetInitiative() const {
    return initiative;
}
int Organism::GetX() const {
    return x;
}
int Organism::GetY() const {
    return y;
}
int Organism::GetAge() const {
    return age;
}
char Organism::GetSymbol() const {
    return symbol;
}
bool Organism::isDead() const {
    return !alive;
}






