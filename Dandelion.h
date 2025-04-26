#ifndef DANDELION_H
#define DANDELION_H
#include "Plant.h"

class Dandelion : public Plant {
public:
    Dandelion(int y, int x);

    std::string getName() const override;
    Organism *createNew(int y, int x) override;
    void action() override;

    ~Dandelion() override = default;
};

#endif
