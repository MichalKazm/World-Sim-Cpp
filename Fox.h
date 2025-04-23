#ifndef FOX_H
#define FOX_H
#include "Animal.h"

class Fox : public Animal {
public:
    Fox(int y, int x);

    Organism* createNew(int y, int x) override;

    void action() override;

    ~Fox() override = default;
};

#endif
