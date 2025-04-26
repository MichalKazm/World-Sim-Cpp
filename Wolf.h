#ifndef WOLF_H
#define WOLF_H
#include "Animal.h"

class Wolf : public Animal{
public:
    Wolf(int y, int x);

    std::string getName() const override;
    Organism *createNew(int y, int x) override;

    ~Wolf() override = default;
};

#endif
