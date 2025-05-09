#ifndef ORGANISM_H
#define ORGANISM_H
#include <string>

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

    virtual bool didDeflectAttack(Organism* attacker);
    bool isDead() const;

    void dies();
    void print() const;
    void setWorld(World* world);
    void setStrength(int strength);
    void setAge (int age);

    virtual std::string getName() const = 0;
    virtual Organism* createNew(int y, int x) = 0;
    virtual void collision(Organism* other) = 0;
    virtual void action() = 0;

    virtual ~Organism() = default;
};

#endif
