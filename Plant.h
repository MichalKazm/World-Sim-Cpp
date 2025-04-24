#ifndef PLANT_H
#define PLANT_H
#include "Organism.h"

class Plant : public Organism {
public:
    Plant(int strength, int y, int x, char symbol);

    void collision(Organism *other) override;
    void action() override;

    ~Plant() override = default;
};

#endif
