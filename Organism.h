#ifndef ORGANISM_H
#define ORGANISM_H

class World;

class Organism {
private:
    int strength, initiative, x, y;
    char symbol;
    bool alive;
    World* world;
public:
    Organism(int strength, int initiative, int x, int y, char symbol, World* world);

    int GetStrength() const;
    int GetInitiative() const;
    int GetX() const;
    int GetY() const;
    char GetSymbol() const;
    bool isDead() const;

    virtual void Action() = 0;
    virtual void Collision(Organism& other) = 0;
};

#endif
