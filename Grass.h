#ifndef GRASS_H
#define GRASS_H
#include "Plant.h"

class Grass : public Plant {
public:
    Grass(int y, int x);

    std::string getName() const override;
    Organism *createNew(int y, int x) override;

    ~Grass() override = default;
};

#endif
