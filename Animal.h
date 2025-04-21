#ifndef ANIMAL_H
#define ANIMAL_H
#include "Organism.h"

class Animal : public Organism {
public:
    Animal(int strength, int initiative, int y, int x, char symbol);

    void collision(Organism *other) override;
    void action() override;

    ~Animal() override = default;
};

#endif
