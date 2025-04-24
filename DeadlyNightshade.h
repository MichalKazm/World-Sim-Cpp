#ifndef DEADLYNIGHTSHADE_H
#define DEADLYNIGHTSHADE_H
#include "Plant.h"

class DeadlyNightshade : public Plant {
public:
    DeadlyNightshade(int y, int x);

    Organism *createNew(int y, int x) override;

    void collision(Organism *other) override;

    ~DeadlyNightshade() override = default;
};

#endif
