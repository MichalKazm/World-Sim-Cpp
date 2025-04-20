#ifndef ORGANISM_H
#define ORGANISM_H

class World;

class Organism {
protected:
    int strength, initiative, x, y, age;
    char symbol;
    bool alive;
    World* world;
public:
    Organism(int strength, int initiative, int x, int y, char symbol, World* world);

    int getStrength() const;
    int getInitiative() const;
    int getX() const;
    int getY() const;
    int getAge() const;
    char getSymbol() const;
    bool isDead() const;

    virtual void action() = 0;
    virtual void collision(Organism& other) = 0;

    virtual ~Organism() = default;
};

#endif
