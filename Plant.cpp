#include "Plant.h"
#include "World.h"

#include <cstdlib>

Plant::Plant(int strength, int y, int x, char symbol)
    : Organism(strength, 0, y, x, symbol) {}
void Plant::collision(Organism *other) {
    dies();
}
void Plant::action() {
    // 10% chance
    if (rand() % 10 == 0) {
        int newX = x;
        int newY = y;

        // Count available directions
        int available = 0;

        if ((y > 0) && (world->getOrganism(y - 1, x)) == nullptr) {
            available++;
        }
        if ((y < world->getRows() - 1) && (world->getOrganism(y + 1, x)) == nullptr) {
            available++;
        }
        if ((x > 0) && (world->getOrganism(y, x - 1)) == nullptr) {
            available++;
        }
        if ((x < world->getCols() - 1) && (world->getOrganism(y, x + 1)) == nullptr) {
            available++;
        }

        // Create a new plant in a random empty adjacent cell
        int chosenCell = 4;

        if (available != 0) {
            chosenCell = rand() % available;
        }

        // Cell above
        if ((y > 0) && (world->getOrganism(y - 1, x)) == nullptr) {
            if (chosenCell == 0) {
                createNew(y - 1, x);
            }

            chosenCell--;
        }
        // Cell below
        if ((y < world->getRows() - 1) && (world->getOrganism(y + 1, x)) == nullptr)  {
            if (chosenCell == 0) {
                createNew(y + 1, x);
            }

            chosenCell--;
        }

        // Cell to the left
        if ((x > 0) && (world->getOrganism(y, x - 1)) == nullptr) {
            if (chosenCell == 0) {
                createNew(y, x - 1);
            }

            chosenCell--;
        }
        // Cell to the right
        if ((x < world->getCols() - 1) && (world->getOrganism(y, x + 1)) == nullptr) {
            if (chosenCell == 0) {
                createNew(y, x + 1);
            }

            chosenCell--;
        }
    }

    age++;
}

