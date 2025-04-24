#ifndef HOGWEED_H
#define HOGWEED_H
#include "Plant.h"

class Hogweed : public Plant {
public:
    Hogweed(int y, int x);

    Organism *createNew(int y, int x) override;

    void collision(Organism *other) override;
    void action() override;

    ~Hogweed() override = default;
};

#endif
