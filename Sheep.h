#ifndef SHEEP_H
#define SHEEP_H
#include "Animal.h"

class Sheep : public Animal {
public:
    Sheep(int y, int x);

    std::string getName() const override;
    Organism *createNew(int y, int x) override;

    ~Sheep() override = default;
};

#endif
