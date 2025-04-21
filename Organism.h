#ifndef ORGANISM_H
#define ORGANISM_H

class World;

class Organism {
protected:
    int strength, initiative, y, x, age;
    char symbol;
    bool alive;
    World* world;
public:
    Organism(int strength, int initiative, int y, int x, char symbol);

    int getStrength() const;
    int getInitiative() const;
    int getX() const;
    int getY() const;
    int getAge() const;
    char getSymbol() const;

    bool isDead() const;

    void dies();
    void print() const;
    void setWorld(World* world);

    virtual Organism* createNew(int y, int x) = 0;
    virtual void collision(Organism* other) = 0;
    virtual void action() = 0;

    virtual ~Organism() = default;
};

#endif
