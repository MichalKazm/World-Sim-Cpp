#ifndef GUARANA_H
#define GUARANA_H
#include "Plant.h"

class Guarana : public Plant {
public:
    Guarana(int y, int x);

    Organism *createNew(int y, int x) override;

    void collision(Organism *other) override;

    ~Guarana() override = default;
};

#endif
