#ifndef WOLF_H
#define WOLF_H
#include "Animal.h"

class Wolf : public Animal{
public:
    Wolf(int y, int x);

    Organism *createNew(int y, int x) override;

    ~Wolf() override = default;
};

#endif
