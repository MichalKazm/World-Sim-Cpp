#ifndef ANTELOPE_H
#define ANTELOPE_H
#include "Animal.h"

class Antelope : public Animal {
public:
    Antelope(int y, int x);

    Organism* createNew(int y, int x) override;
    bool didDeflectAttack(Organism *attacker) override;

    void action() override;

    ~Antelope() override = default;
};

#endif
