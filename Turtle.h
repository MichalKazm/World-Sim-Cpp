#ifndef TURTLE_H
#define TURTLE_H
#include "Animal.h"

class Turtle : public Animal {
public:
    Turtle(int y, int x);

    Organism* createNew(int y, int x) override;
    bool didDeflectAttack(Organism *attacker) const override;

    void action() override;

    ~Turtle() override = default;
};

#endif
