#ifndef HUMAN_H
#define HUMAN_H
#include "Animal.h"

class Human : public Animal {
private:
    int nextMove;
    int abilityTimer;
public:
    Human(int y, int x);

    int getAbilityTimer() const;

    void setAbilityTimer(int abilityTimer);
    void setNextMove(int nextMove);

    Organism *createNew(int y, int x) override;

    void collision(Organism *other) override;
    void action() override;

    ~Human() override = default;
};

#endif
