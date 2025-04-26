#ifndef ANTELOPE_H
#define ANTELOPE_H
#include "Animal.h"

class Antelope : public Animal {
public:
    Antelope(int y, int x);

    bool didDeflectAttack(Organism *attacker) override;

    std::string getName() const override;
    Organism* createNew(int y, int x) override;
    void action() override;

    ~Antelope() override = default;
};

#endif
