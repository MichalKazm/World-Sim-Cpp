#include "Plant.h"
#include "World.h"

#include <cstdlib>

Plant::Plant(int strength, int y, int x, char symbol)
    : Organism(strength, 0, y, x, symbol) {}
void Plant::collision(Organism *other) {
    world->addLog(other->getName() + ": Ate " + getName());
    dies();
}
void Plant::action() {
    // 10% chance
    if (rand() % 10 == 0) {
        // Count available directions
        int available = 0;
        int newY = y;
        int newX = x;

        if ((y > 0) && (world->getOrganism(y - 1, x) == nullptr)) {
            available++;
        }
        if ((y < world->getRows() - 1) && (world->getOrganism(y + 1, x) == nullptr)) {
            available++;
        }
        if ((x > 0) && (world->getOrganism(y, x - 1) == nullptr)) {
            available++;
        }
        if ((x < world->getCols() - 1) && (world->getOrganism(y, x + 1) == nullptr)) {
            available++;
        }

        // Create a new plant in a random empty adjacent cell
        int chosenCell = 4;

        if (available != 0) {
            chosenCell = rand() % available;
        }

        // Cell above
        if ((y > 0) && (world->getOrganism(y - 1, x) == nullptr)) {
            if (chosenCell == 0) {
                newY = y - 1;
                world->addOrganism(createNew(newY, newX));
            }

            chosenCell--;
        }
        // Cell below
        if ((y < world->getRows() - 1) && (world->getOrganism(y + 1, x) == nullptr))  {
            if (chosenCell == 0) {
                newY = y + 1;
                world->addOrganism(createNew(newY, newX));
            }

            chosenCell--;
        }

        // Cell to the left
        if ((x > 0) && (world->getOrganism(y, x - 1) == nullptr)) {
            if (chosenCell == 0) {
                newX = x - 1;
                world->addOrganism(createNew(newY, newX));
            }

            chosenCell--;
        }
        // Cell to the right
        if ((x < world->getCols() - 1) && (world->getOrganism(y, x + 1) == nullptr)) {
            if (chosenCell == 0) {
                newX = x + 1;
                world->addOrganism(createNew(newY, newX));
            }

            chosenCell--;
        }

        if (chosenCell < 0) {
            world->addLog(getName() + ": Spread to (" + std::to_string(newY) + ", " + std::to_string(newX) + ")");
        }
    }

    age++;
}

