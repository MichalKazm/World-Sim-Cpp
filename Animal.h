#ifndef ANIMAL_H
#define ANIMAL_H
#include "Organism.h"

class Animal : public Organism {
public:
    Animal(int strength, int initiative, int x, int y, char symbol, World* world);

    void Action() override;
    void Collision(Organism &other) override {};

    ~Animal() override = default;
};

#endif
