#ifndef TURTLE_H
#define TURTLE_H
#include "Animal.h"

class Turtle : public Animal {
public:
    Turtle(int y, int x);

    bool didDeflectAttack(Organism *attacker) override;

    std::string getName() const override;
    Organism* createNew(int y, int x) override;
    void action() override;

    ~Turtle() override = default;
};

#endif
